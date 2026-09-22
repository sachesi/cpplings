#pragma once

class AppState;

// Reruns the current exercise whenever its file changes and handles the keys of
// the watch mode. `manual_run` replaces file change detection with the `r` key.
void watch(AppState& app_state, bool manual_run);
