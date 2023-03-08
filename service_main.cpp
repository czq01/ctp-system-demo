#include "service_engine.h"

int main(int argc, char const *argv[]) {
   std::cout << "Hello world" << std::endl;
    ServerCTAEngine * serviceCTAEngine = new ServerCTAEngine;
    serviceCTAEngine->start();
    // wait until end.
    delete serviceCTAEngine;
    std::cout << "GoodBye world" << std::endl;
    getchar();
    return 0;
}