#include "AssimpInterface.h"

#include <iostream>
#include <fstream>

#include <filesystem>

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

bool AssimpInterface::GrabFBXFiles()
{
   
    std::filesystem::path p = std::filesystem::path(std::filesystem::current_path().string()).parent_path().parent_path().append("InputFiles\\");

    std::vector <std::string> inPaths;
    
    for (const auto& file : std::filesystem::directory_iterator(p))
        inPaths.push_back(file.path().string());// << std::endl;

    //std::filesystem::create_directories("sandbox/a/b");
    //std::ofstream("sandbox/file1.txt");
    //std::ofstream("sandbox/file2.txt");
    //std::filesystem::remove_all("sandbox");

    //for (auto& p : std::filesystem::directory_iterator("sandbox"))
    //    std::cout << p.path() << '\n';
    

    std::cout << "fileCount = " << inPaths.size() << std::endl;

    for (size_t i = 0; i < inPaths.size(); i++)
    {
        AssimpImport(inPaths.at(i));
    }

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
    std::cout << std::endl;
    std::cout << pFile << std::endl;

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
    std::cout << mesh->mNumFaces << std::endl;;
    FillVertexFormatWithMesh(mesh);

    // We're done. Everything will be cleaned up by the importer destructor
    return true;

}

void AssimpInterface::FillVertexFormatWithMesh(aiMesh* pMesh)
{
    // Deal with verts.
    {
        unsigned int numVerts = pMesh->mNumVertices;

        // Reserve enough space in our vector for the vertices.
        //pMeshChunk->m_Vertices.resize(numVerts);

        //for (unsigned int vi = 0; vi < numVerts; vi++)
        //{
        //    // Typecasting should be safe as long as aiVector3D is simply 3 floats in order.
        //    memset(&pMeshChunk->m_Vertices[vi], 0, sizeof(VertexFormat));
        //
        //    if (pMesh->HasPositions())
        //    {
        //        pMeshChunk->m_Vertices[vi].pos = *(Vector3*)&pMesh->mVertices[vi];
        //    }
        //    if (pMesh->HasNormals())
        //    {
        //        pMeshChunk->m_Vertices[vi].norm = *(Vector3*)&pMesh->mNormals[vi];
        //        m_HasNormals = true;
        //    }
        //    //if( pMesh->HasTangents() )
        //    //{
        //    //    pMeshChunk->m_Vertices[vi].tangent = *(Vector3*)&pMesh->mTangents[vi];
        //    //    m_HasTangents = true;
        //    //}
        //    if (pMesh->HasVertexColors(0))
        //    {
        //        pMeshChunk->m_Vertices[vi].color[0] = (unsigned char)(pMesh->mColors[0][vi].r * 255);
        //        pMeshChunk->m_Vertices[vi].color[1] = (unsigned char)(pMesh->mColors[0][vi].g * 255);
        //        pMeshChunk->m_Vertices[vi].color[2] = (unsigned char)(pMesh->mColors[0][vi].b * 255);
        //        pMeshChunk->m_Vertices[vi].color[3] = (unsigned char)(pMesh->mColors[0][vi].a * 255);
        //        m_HasColor = true;
        //    }
        //
        //    for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; i++)
        //    {
        //        if (pMesh->HasTextureCoords(i))
        //        {
        //            pMeshChunk->m_Vertices[vi].uv[i] = *(Vector2*)&pMesh->mTextureCoords[i][vi];
        //
        //            if (i + 1 > m_NumUVChannels)
        //                m_NumUVChannels = i + 1;
        //        }
        //    }
        //}
    }

    // Deal with indices.
    {
        unsigned int numFaces = pMesh->mNumFaces;
        unsigned int numIndices = numFaces * 3;
        //
        //pMeshChunk->m_Indices.resize(numIndices);
        //
        //for (unsigned int fi = 0; fi < numFaces; fi++)
        //{
        //    aiFace& Face = pMesh->mFaces[fi];
        //
        //    assert(Face.mNumIndices == 3);
        //
        //    pMeshChunk->m_Indices[fi * 3 + 0] = Face.mIndices[0];
        //    pMeshChunk->m_Indices[fi * 3 + 1] = Face.mIndices[1];
        //    pMeshChunk->m_Indices[fi * 3 + 2] = Face.mIndices[2];
        //}
    }
}