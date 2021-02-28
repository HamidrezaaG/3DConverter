#include "AssimpInterface.h"


#include <iostream>
#include <filesystem>

#include "assimp/Importer.hpp"      // C++ importer interface 
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags
#include "assimp/mesh.h"


AssimpInterface::AssimpInterface()
{

}

AssimpInterface::~AssimpInterface()
{

}

bool AssimpInterface::LoadFBX()
{
   
    std::filesystem::path p = std::filesystem::path(std::filesystem::current_path().string()).parent_path().parent_path().append("InputFiles\\");

    for (const auto& file : std::filesystem::directory_iterator(p))
        std::cout << file.path() << std::endl;

    //for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
    //{
      //std::cout << entry.path().string();
      //AssimpImport(entry.path().string());
    //}

    //std::cout << (AssimpInterface::AssimpImport(directory) ? "Success\n" : "Fail\n");
    //std::cout << FolderName + " request recieved." << std::endl;

    //std::cout << "---------------\n";
    //std::cout << "Attempted to read file.\n";
    //std::cout << AssimpImport(a.c_str());
    //std::cout << (AssimpImport(a.c_str()) ? "Success\n":"Fail\n");

    return false;
}

bool AssimpInterface::AssimpImport(const std::string& pFile)
{

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        //aiProcess_Triangulate |
        //aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    // If the import failed, report it
    if (!scene)
    {
        return false;
    }
    // Now we can access the file's contents.
    aiMesh* cube = scene->mMeshes[0];
    std::cout << cube->mNumFaces;

    // We're done. Everything will be cleaned up by the importer destructor
    return true;

}
