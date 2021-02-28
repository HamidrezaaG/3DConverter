#include <iostream>
#include "AssimpInterface.h"

int main(int argc, char* argv[])
{

    std::cout << "CODE BEGIN";
    std::cout << std::endl;


    AssimpInterface _assimpinterface;

    if(argc > 0)
        _assimpinterface.ConvertFBXFiles(argv[1]);

    std::cout << "CODE END <<<<<<<<<<<<<<<<<<";
    std::cout << std::endl;
    return 0;
}
