#include <iostream>
#include <string>
#include "tests/ControllerScenarioTests.h"

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--self-test") {
            int failures = RunControllerScenarioTests();
            if (failures == 0) {
                std::cout << "OK" << std::endl;
                return 0;
            }
            std::cerr << failures << " test(s) failed" << std::endl;
            return 1;
        }
    }

    std::cout << "ConsoleMVC" << std::endl;
    return 0;
}
