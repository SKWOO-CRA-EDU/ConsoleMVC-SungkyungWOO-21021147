#include <iostream>
#include <string>
#include "tests/ControllerScenarioTests.h"
#include "src/app/AppController.h"
#include "src/infra/repository/InMemorySampleRepository.h"
#include "src/infra/repository/InMemoryOrderRepository.h"
#include "src/infra/console/ConsoleInputAdapter.h"
#include "src/infra/console/ConsoleOutputAdapter.h"

// Composition Root: 구체 구현체를 생성해 AppController에 주입한다.
// Model/Controller가 아닌 이 파일만 어떤 어댑터를 쓸지 안다.
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

    InMemorySampleRepository samples;
    InMemoryOrderRepository orders;
    ConsoleInputAdapter input;
    ConsoleOutputAdapter output;

    AppController controller(input, output, samples, orders);
    controller.Run();
    return 0;
}
