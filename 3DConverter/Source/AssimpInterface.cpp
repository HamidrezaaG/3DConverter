
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

    // ensure .fbx extension
    {
        size_t dotIndex = file.path().filename().string().find_last_of(".");
        std::string rawName = file.path().filename().string().substr(dotIndex, file.path().string().length());

        if (rawName != ".fbx") continue;
    }

    std::cout << file.path().filename().string() << '\n';

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
        aiProcess_Triangulate |
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
    WriteVertexDataToFile(rawName.append(k_OutputExtension), OutputDirectory.string(), vertData);
    vertData.clear();

    // We're done. Everything will be cleaned up by the importer destructor
    return true;

}

void AssimpInterface::WriteVertexDataToFile(const std::string& fileName, const std::string& outputDir, std::vector <struct VertexFormat*> vertexData)
{
    std::fstream file;

    std::string outpath = outputDir + fileName;

    // Delete duplicates
    if (std::filesystem::exists(outpath))
        std::filesystem::remove(outpath);

    file.open(outpath, std::ios::app | std::ios::binary);

    if (!file.fail()) {
        assert(sizeof(k_ConverterVersion) == 4);
        file.write(k_ConverterVersion, sizeof(uint32_t));
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

            vert->pos.x = pMesh->mVertices[i].x;
            vert->pos.y = pMesh->mVertices[i].y;
            vert->pos.z = pMesh->mVertices[i].z;

            vert->norm.x = pMesh->mNormals[i].x;
            vert->norm.y = pMesh->mNormals[i].y;
            vert->norm.z = pMesh->mNormals[i].z;

            if (pMesh->HasTextureCoords(0))
            {
                vert->uv.u = pMesh->mTextureCoords[0][i].x;
                vert->uv.v = pMesh->mTextureCoords[0][i].y;
            }
            // these are by default initialized to 0 so there's no real need to catch them on the way out.

            vertData.at(i) = vert;
        }


        // we're going to do face parsing here. return if no faces available 
        if (!pMesh->HasFaces())
        return;

        std::vector<VertexFormat*> finalVertData;
        finalVertData.resize(pMesh->mNumFaces * (uint32_t)3);

        for (size_t i = 0; i < pMesh->mNumFaces; i++)
        {
            for (size_t j = 0; j < 3; j++) // Forced Triangulation ensures only Tris exist here.
            {
                finalVertData.at(i*3 + j) = vertData.at(pMesh->mFaces[i].mIndices[j]);
            }
        }

        vertData = finalVertData;

}

void AssimpInterface::WriteVertex(std::fstream* file, VertexFormat* v)
{
    if (file->is_open())
    {
        std::streamsize sizeTemplate = sizeof(uint32_t);

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