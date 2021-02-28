#pragma once

#include <string>

class AssimpInterface
{
public:
	AssimpInterface();
	~AssimpInterface();
    
    bool GrabFBXFiles();
    void FillVertexFormatWithMesh(struct aiMesh* pMesh);

private:

    bool AssimpImport(const std::string& pFile);
};