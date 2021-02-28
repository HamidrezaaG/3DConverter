#pragma once

#include <string>

class AssimpInterface
{
public:
	AssimpInterface();
	~AssimpInterface();
    
    bool LoadFBX();
    bool AssimpImport(const std::string& pFile);

private:

};