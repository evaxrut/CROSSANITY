#pragma once

namespace color {

constexpr char BLUE_BACKGROUND_START[] = "\033[44m";
constexpr char RED_BACKGROUND_START[] = "\033[41m";
constexpr char GREEN_BACKGROUND_START[] = "\033[42m";
constexpr char YELLOW_BACKGROUND_START[] = "\033[43m";
constexpr char MAGENTA_BACKGROUND_START[] = "\033[45m";
constexpr char CYAN_BACKGROUND_START[] = "\033[46m";
constexpr char WHITE_BACKGROUND_START[] = "\033[47m";
constexpr char BLACK_BACKGROUND_START[] = "\033[40m";

constexpr char BLUE_FOREGROUND_START[] = "\033[34m";
constexpr char RED_FOREGROUND_START[] = "\033[31m";
constexpr char GREEN_FOREGROUND_START[] = "\033[32m";
constexpr char YELLOW_FOREGROUND_START[] = "\033[33m";
constexpr char MAGENTA_FOREGROUND_START[] = "\033[35m";
constexpr char CYAN_FOREGROUND_START[] = "\033[36m";
constexpr char WHITE_FOREGROUND_START[] = "\033[37m";
constexpr char BLACK_FOREGROUND_START[] = "\033[30m";

constexpr char COLOR_END[] = "\033[0m";

} // namespace color

