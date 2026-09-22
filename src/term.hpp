#pragma once

#include <termios.h>

#include <string>
#include <string_view>

namespace term {

inline constexpr std::string_view reset = "\x1b[0m";
inline constexpr std::string_view bold = "\x1b[1m";
inline constexpr std::string_view underline = "\x1b[4m";
inline constexpr std::string_view no_underline = "\x1b[24m";
inline constexpr std::string_view reverse = "\x1b[7m";
inline constexpr std::string_view red = "\x1b[31m";
inline constexpr std::string_view green = "\x1b[32m";
inline constexpr std::string_view yellow = "\x1b[33m";
inline constexpr std::string_view blue = "\x1b[34m";
inline constexpr std::string_view magenta = "\x1b[35m";
inline constexpr std::string_view cyan = "\x1b[36m";
inline constexpr std::string_view default_fg = "\x1b[39m";
inline constexpr std::string_view hide_cursor = "\x1b[?25l";
inline constexpr std::string_view show_cursor = "\x1b[?25h";

struct Size {
    int width;
    int height;
};

void write_stdout(std::string_view text);
bool stdout_is_terminal();
Size size();

void clear(std::string& out);
void progress_bar(std::string& out, int progress, int total, int term_width);
// Writes `path` wrapped in an OSC 8 hyperlink when `canonical_path` isn't empty.
void file_link(std::string& out, std::string_view path, std::string_view canonical_path);
std::string canonicalize(const std::string& path);
void press_enter_prompt();

// Returns true once after the terminal has been resized.
bool take_resize_event();
// Restores the terminal on SIGINT, SIGTERM and SIGHUP, and records SIGWINCH.
void install_signal_handlers();

enum class KeyCode { None, Char, Enter, Esc, Backspace, Up, Down, Home, End, ScrollUp, ScrollDown };

struct Key {
    KeyCode code = KeyCode::None;
    char ch = 0;
};

// Waits up to `timeout_ms` for a key press. Returns KeyCode::None on timeout or
// when interrupted by a signal.
Key read_key(int timeout_ms);
void discard_pending_input();

// Disables line buffering and echo for the lifetime of the object. `Raw` also
// turns keys like Ctrl+C into plain input instead of signals.
class InputMode {
public:
    enum class Kind { Cbreak, Raw };
    explicit InputMode(Kind kind);
    ~InputMode();
    InputMode(const InputMode&) = delete;
    InputMode& operator=(const InputMode&) = delete;

private:
    termios previous_{};
    bool active_ = false;
    bool outermost_ = false;
};

// Alternate screen with hidden cursor, no line wrapping and mouse wheel reporting.
class FullScreen {
public:
    FullScreen();
    ~FullScreen();
    FullScreen(const FullScreen&) = delete;
    FullScreen& operator=(const FullScreen&) = delete;
};

} // namespace term
