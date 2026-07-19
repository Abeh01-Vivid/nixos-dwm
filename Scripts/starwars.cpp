#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Helper function to sleep for a specific number of milliseconds
void wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// Mimics a typewriter effect by printing character by character
void scrollText(const std::string& text, int charDelayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        wait(charDelayMs);
    }
    std::cout << "\n";
}

int main() {
    // 1. Clear screen and reset cursor to the top-left
    std::cout << "\033[2J\033[1;1H"; 
    wait(1000);

    // 2. The famous blue opening text
    std::cout << "\033[1;36m"; // Set text color to bright cyan/blue
    scrollText("A long time ago in a galaxy far, far away....", 90);
    wait(3000); // Hold it on screen just like the film

    // Clear screen for the main title blast
    std::cout << "\033[2J\033[1;1H"; 
    wait(1000);

    // 3. The Star Wars Title Blast (Bright Yellow)
    std::cout << "\033[1;33m"; // Set text color to bright yellow
    std::cout << "                  ____ _____  _    ____   \n";
    std::cout << "                 / ___|_   _|/ \\  |  _ \\  \n";
    std::cout << "                 \\___ \\ | | / _ \\ | |_) | \n";
    std::cout << "                  ___) || |/ ___ \\|  _ <  \n";
    std::cout << "                 |____/ |_/_/   \\_\\_| \\_\\ \n\n";
    std::cout << "                  _     _  _    ____  ____  \n";
    std::cout << "                 | |   | |/ \\  |  _ \\/ ___| \n";
    std::cout << "                 | | _ | / _ \\ | |_) \\___ \\ \n";
    std::cout << "                 | |/ \| / ___ \\|  _ < ___) |\n";
    std::cout << "                 |___/\\_/_/   \\_\\_| \\_\\____/ \n\n";
    wait(2500);

    // 4. The Episode Title
    std::cout << "                          EPISODE C++\n";
    std::cout << "                       THE AMATEUR CODER\n\n";
    wait(2000);

    // 5. The Crawl Text
    std::string crawl = 
        "        It is a period of desktop rebellion. Cryptic compiler\n"
        "        errors strike from the shadows, threatening the sanity\n"
        "        of aspiring software developers everywhere.\n\n"
        "        During a late-night coding session, a brave programmer\n"
        "        managed to bypass an infinite loop, securing the key\n"
        "        to understanding pointers and memory allocation.\n\n"
        "        Pursued by the Empire's sinister automated test suites,\n"
        "        our hero races home, custodian of the stolen scripts\n"
        "        that can save the repository and restore freedom to the\n"
        "        local branch....";

    scrollText(crawl, 55); // Slightly faster scrolling for the main body block

    // Reset terminal color back to normal when finished
    std::cout << "\033[0m\n\n[End of Transmission]\n";
    return 0;
}

