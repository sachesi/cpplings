#include "cmd.hpp"

#include <fcntl.h>
#include <poll.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <mutex>
#include <system_error>

extern char** environ;

namespace {

// Programs that loop forever while printing would otherwise fill the memory.
constexpr std::size_t max_output_size = 1 << 20;

// Pipes are created and handed to posix_spawn under this lock, so a child spawned
// from another thread can't inherit a write end and keep the pipe open.
std::mutex spawn_mutex;

void set_cloexec(int fd) {
    ::fcntl(fd, F_SETFD, ::fcntl(fd, F_GETFD) | FD_CLOEXEC);
}

class SpawnFileActions {
public:
    SpawnFileActions() { ::posix_spawn_file_actions_init(&actions_); }
    ~SpawnFileActions() { ::posix_spawn_file_actions_destroy(&actions_); }
    SpawnFileActions(const SpawnFileActions&) = delete;
    SpawnFileActions& operator=(const SpawnFileActions&) = delete;
    posix_spawn_file_actions_t* get() { return &actions_; }

private:
    posix_spawn_file_actions_t actions_;
};

} // namespace

CmdResult run_cmd(const std::vector<std::string>& argv, std::string* output,
                  std::optional<std::chrono::milliseconds> timeout) {
    std::vector<char*> c_argv;
    c_argv.reserve(argv.size() + 1);
    for (const std::string& arg : argv) {
        c_argv.push_back(const_cast<char*>(arg.c_str()));
    }
    c_argv.push_back(nullptr);

    int pipe_fds[2];
    pid_t pid = 0;
    {
        std::lock_guard lock(spawn_mutex);
        if (::pipe(pipe_fds) != 0) {
            throw std::system_error(errno, std::generic_category(), "Failed to create a pipe");
        }
        set_cloexec(pipe_fds[0]);
        set_cloexec(pipe_fds[1]);

        SpawnFileActions actions;
        ::posix_spawn_file_actions_addopen(actions.get(), STDIN_FILENO, "/dev/null", O_RDONLY, 0);
        ::posix_spawn_file_actions_adddup2(actions.get(), pipe_fds[1], STDOUT_FILENO);
        ::posix_spawn_file_actions_adddup2(actions.get(), pipe_fds[1], STDERR_FILENO);

        int err = ::posix_spawnp(&pid, c_argv[0], actions.get(), nullptr, c_argv.data(), environ);
        ::close(pipe_fds[1]);
        if (err != 0) {
            ::close(pipe_fds[0]);
            throw std::system_error(err, std::generic_category(), "Failed to run `" + argv[0] + "`");
        }
    }

    CmdResult result;
    auto deadline = timeout ? std::optional(std::chrono::steady_clock::now() + *timeout) : std::nullopt;
    char buf[4096];
    while (true) {
        int wait_ms = -1;
        if (deadline) {
            auto left = std::chrono::duration_cast<std::chrono::milliseconds>(
                *deadline - std::chrono::steady_clock::now());
            if (left.count() <= 0) {
                result.timed_out = true;
                ::kill(pid, SIGKILL);
                break;
            }
            wait_ms = static_cast<int>(left.count());
        }

        pollfd pfd{pipe_fds[0], POLLIN, 0};
        int ready = ::poll(&pfd, 1, wait_ms);
        if (ready < 0 && errno == EINTR) {
            continue;
        }
        if (ready <= 0) {
            continue;
        }

        ssize_t n = ::read(pipe_fds[0], buf, sizeof buf);
        if (n < 0 && errno == EINTR) {
            continue;
        }
        if (n <= 0) {
            break;
        }
        if (output != nullptr) {
            if (output->size() < max_output_size) {
                output->append(buf, static_cast<std::size_t>(n));
            } else {
                result.output_truncated = true;
            }
        }
    }
    ::close(pipe_fds[0]);

    int status = 0;
    while (::waitpid(pid, &status, 0) < 0 && errno == EINTR) {
    }
    if (WIFEXITED(status)) {
        result.exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        result.signal = WTERMSIG(status);
    }
    return result;
}
