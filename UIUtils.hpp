#pragma once
#include <iostream>
#include <string>

namespace UI {
// ANSI Color Codes
const std::string RESET = "\033[0m";
const std::string CYAN = "\033[96m";
const std::string MAGENTA = "\033[95m";
const std::string BLUE = "\033[94m";
const std::string GREEN = "\033[92m";
const std::string RED = "\033[91m";
const std::string GRAY = "\033[90m";
const std::string WHITE = "\033[97m";
const std::string BOLD = "\033[1m";

inline void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

inline void printBanner() {
  std::cout << CYAN << BOLD << R"(
    ___    _   __________  _______  ___ _    _____________  __
   /   |  / | / /_  __/  |/  / __ \/   | |  / /  _/_  __/\ \/ /
  / /| | /  |/ / / / / /|_/ / /_/ / /| | | / // /  / /    \  / 
 / ___ |/ /|  / / / / /  / / _, _/ ___ | |/ // /  / /     / /  
/_/  |_/_/ |_/ /_/ /_/  /_/_/ |_/_/  |_|___/___/ /_/     /_/   
        )" << RESET
            << std::endl;
  std::cout << MAGENTA << "            >> MACHINE ROOM RESERVATION SYSTEM <<"
            << RESET << "\n\n";
}

inline void printHeader(const std::string &title) {
  std::cout << BLUE << "------------------ " << WHITE << BOLD << title << RESET
            << BLUE << " ------------------" << RESET << "\n\n";
}

inline void printDash(const std::string& title)
{
    std::cout << GRAY << "-------- "  << BOLD << title << RESET
        << GRAY << " --------" << RESET << "\n\n";
}

inline void printOption(int key, const std::string &label) {
  std::cout << CYAN << "  [" << key << "] " << RESET << label << "\n";
}

inline void printInputPrompt() {
  std::cout << "\n" << MAGENTA << "  > " << RESET << "Select option: ";
}

inline void printTextInputPrompt() {
    std::cout << "\n" << MAGENTA << "  > " << RESET << "Input Required:  ";
}
} // namespace UI
