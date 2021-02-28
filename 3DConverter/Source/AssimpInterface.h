#pragma once

#include <string>
#include <vector>
#include <filesystem>

struct aiMesh;
struct VertexFormat;

class AssimpInterface
{
public:
	AssimpInterface();
	~AssimpInterface();
    
    bool ConvertFBXFiles(char* exeFolderLocation);

    std::vector <VertexFormat*> vertData;
    std::vector <std::string> fileNames;

    std::filesystem::path rootpath;

private:

    void WriteVertex(std::fstream* file, VertexFormat* v);
    void FillVertexDataWithMesh(aiMesh* pMesh);
    void WriteVertexDataToFile(const std::string& fileName, const std::string& outputDir, const std::vector <struct VertexFormat*> vertexData);
    bool AssimpImport(std::filesystem::path filepath);
};