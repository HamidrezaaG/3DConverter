
#include "AssimpInterface.h"
#include "Constants.h"

#include <iostream>
#include <fstream>
#include <assert.h>


#include "assimp/Importer.hpp"      // C++ importer interface 
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags
#include "assimp/mesh.h"

struct vec3 
{
    float x, y, z = 0;
};

struct vec2
{
    float u, v = 0;
};

struct VertexFormat
{
    uint32_t index = 0;
    vec3 pos, norm;
    vec2 uv;
};

AssimpInterface::AssimpInterface()
{
}

AssimpInterface::~AssimpInterface()
{

}

bool AssimpInterface::ConvertFBXFiles(char* exeFolderLocation)
{
    rootpath = std::filesystem::path(std::filesystem::current_path());
    
    // account for whether or not we're running through Visual Studio vs the .Bat file.
    if (exeFolderLocation != nullptr)
    {
        std::string _text = exeFolderLocation;
        _text = _text.substr(0, _text.size() - 1);
        rootpath = _text.c_str(); //rootpath.parent_path().parent_path().parent_path().parent_path().parent_path().parent_path();
    }
    else
    {
        rootpath = rootpath.parent_path().parent_path();
    }

    std::filesystem::path inputDirectory = rootpath;
    inputDirectory.append("InputFiles\\");

    std::filesystem::path outputDirectory = rootpath;
    outputDirectory.append("OutputFiles\\");

    { // add input and output dirs if they don't exist.
        std::filesystem::create_directory(outputDirectory);
        std::filesystem::create_directory(inputDirectory);
    }

    std::vector <std::string> inPaths;

    for (auto& file : std::filesystem::directory_iterator(inputDirectory))
    {
    std::cout << file.path().string() << '\n';

    AssimpImport(file.path());
    fileNames.push_back(file.path().filename().string());
    inPaths.push_back(file.path().string());// << std::endl;
    }
    
    return false;
}

bool AssimpInterface::AssimpImport(std::filesystem::path filepath)
{

    std::string pFile = filepath.string();

    std::filesystem::path OutputDirectory = rootpath;
    OutputDirectory.append("OutputFiles\\");

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
    aiMesh* mesh = scene->mMeshes[0];

    // remove the .fbx from the file names and swap it for .bin.
    size_t dotIndex = filepath.filename().string().find_last_of(".");
    std::string rawName = filepath.filename().string().substr(0, dotIndex);

    FillVertexDataWithMesh(mesh);
    WriteVertexDataToFile(rawName.append(".bin"), OutputDirectory.string(), vertData);
    vertData.clear();

    // We're done. Everything will be cleaned up by the importer destructor
    return true;

}

void AssimpInterface::WriteVertexDataToFile(const std::string& fileName, const std::string& outputDir, std::vector <struct VertexFormat*> vertexData)
{
    std::fstream file;

    VertexFormat vertformatTemplate;

    std::string outpath = outputDir + fileName;

    // Delete duplicates
    if (std::filesystem::exists(outpath))
        std::filesystem::remove(outpath);

    file.open(outpath, std::ios::app | std::ios::binary);

    if (!file.fail()) {
        assert(sizeof(ConverterVersion) == 4);
        file.write(ConverterVersion, sizeof(uint32_t));
        for (size_t i = 0; i < vertexData.size(); i++)
        {
            WriteVertex(&file, vertexData[i]);
        }
        file.close();
    }

}

void AssimpInterface::FillVertexDataWithMesh(aiMesh* pMesh)
{
        uint32_t numVerts = pMesh->mNumVertices;
        vertData.resize(numVerts);

        for (uint32_t i = 0; i < numVerts; i++)
        {
            VertexFormat* vert = new VertexFormat();
            vert->index = i;

            vert->pos.x = pMesh->mVertices[i].x;
            vert->pos.y = pMesh->mVertices[i].y;
            vert->pos.z = pMesh->mVertices[i].z;

            vert->norm.x = pMesh->mNormals[i].x;
            vert->norm.y = pMesh->mNormals[i].y;
            vert->norm.z = pMesh->mNormals[i].z;

            vert->uv.u = pMesh->mTextureCoords[0][i].x;
            vert->uv.v = pMesh->mTextureCoords[0][i].y;

            vertData.at(i) = vert;
        }
}

void AssimpInterface::WriteVertex(std::fstream* file, VertexFormat* v)
{
    if (file->is_open())
    {
        std::streamsize sizeTemplate = sizeof(uint32_t);

        file->write( reinterpret_cast <char*> (&(v->index))   , sizeTemplate);

        file->write( reinterpret_cast <char*> (&(v->pos.x))   , sizeTemplate);
        file->write( reinterpret_cast <char*> (&(v->pos.y))   , sizeTemplate);
        file->write( reinterpret_cast <char*> (&(v->pos.z))   , sizeTemplate);

        file->write( reinterpret_cast <char*> (&(v->norm.x))  , sizeTemplate);
        file->write( reinterpret_cast <char*> (&(v->norm.y))  , sizeTemplate);
        file->write( reinterpret_cast <char*> (&(v->norm.z))  , sizeTemplate);

        file->write( reinterpret_cast <char*> (&(v->uv.u))    , sizeTemplate);
        file->write( reinterpret_cast <char*> (&(v->uv.v))    , sizeTemplate);

    }
}