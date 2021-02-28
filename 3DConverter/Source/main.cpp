#include <iostream>
#include "AssimpInterface.h"

int main(int argc, char* argv[])
{
    AssimpInterface _assimpinterface;

    if(argc > 0)
        _assimpinterface.ConvertFBXFiles(argv[1]);

    return 0;
}
