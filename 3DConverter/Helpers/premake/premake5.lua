-----------------------------------------------------
-- Workspace
-----------------------------------------------------
workspace "Workspace"
	configurations	{ "Debug", "Release" }
	platforms		{ "x64" }
	location		"../../build"
	characterset	"MBCS"
	startproject	"3DConverter"

	filter "configurations:Debug"
		symbols		"on"

-----------------------------------------------------
-- 3DConverter
-----------------------------------------------------
project "3DConverter"
	kind		"ConsoleApp"
	location	"../../build/3DConverter"
	debugdir	"$(SolutionDir)"
	cppdialect "C++17"
	
	configurations	{ "Debug" }
		
	files {
		"../../Source/**.h",
		"../../Source/**.cpp",
		"premake5.lua",
	}
	
	libdirs { "$(SolutionDir)Assimp" }
	
	includedirs {
		"../configs",
		"$(SolutionDir)../../Source",
		"$(SolutionDir)../Libraries/assimp/include"
	}
	
	links {
		"Assimp"
	}
-----------------------------------------------------
-- 3DConverter
-----------------------------------------------------
project "Assimp"
	kind		"StaticLib"
	location	"../../build/Assimp"
	debugdir	"$(SolutionDir)"
	cppdialect "C++17"

	configurations	{ "Debug", "Release" }
	
	targetdir ("../../build/Assimp")
	objdir ("../../build/Assimp")

	
	defines {

		"_CRT_SECURE_NO_WARNINGS",
		
		"ASSIMP_BUILD_NO_EXPORT",
		"ASSIMP_BUILD_NO_OWN_ZLIB",
	
		"ASSIMP_BUILD_NO_X_IMPORTER",
		"ASSIMP_BUILD_NO_3DS_IMPORTER",
		"ASSIMP_BUILD_NO_MD3_IMPORTER",
		"ASSIMP_BUILD_NO_M3D_IMPORTER",
		"ASSIMP_BUILD_NO_MDL_IMPORTER",
		"ASSIMP_BUILD_NO_MD2_IMPORTER",
		"ASSIMP_BUILD_NO_PLY_IMPORTER",
		"ASSIMP_BUILD_NO_ASE_IMPORTER",
		-- "ASSIMP_BUILD_NO_OBJ_IMPORTER",
		"ASSIMP_BUILD_NO_AMF_IMPORTER",
		"ASSIMP_BUILD_NO_HMP_IMPORTER",
		"ASSIMP_BUILD_NO_SMD_IMPORTER",
		"ASSIMP_BUILD_NO_MDC_IMPORTER",
		"ASSIMP_BUILD_NO_MD5_IMPORTER",
		"ASSIMP_BUILD_NO_STL_IMPORTER",
		"ASSIMP_BUILD_NO_LWO_IMPORTER",
		"ASSIMP_BUILD_NO_DXF_IMPORTER",
		"ASSIMP_BUILD_NO_NFF_IMPORTER",
		"ASSIMP_BUILD_NO_RAW_IMPORTER",
		"ASSIMP_BUILD_NO_OFF_IMPORTER",
		"ASSIMP_BUILD_NO_AC_IMPORTER",
		"ASSIMP_BUILD_NO_BVH_IMPORTER",
		"ASSIMP_BUILD_NO_IRRMESH_IMPORTER",
		"ASSIMP_BUILD_NO_IRR_IMPORTER",
		"ASSIMP_BUILD_NO_Q3D_IMPORTER",
		"ASSIMP_BUILD_NO_B3D_IMPORTER",
		-- "ASSIMP_BUILD_NO_COLLADA_IMPORTER",
		"ASSIMP_BUILD_NO_TERRAGEN_IMPORTER",
		"ASSIMP_BUILD_NO_CSM_IMPORTER",
		"ASSIMP_BUILD_NO_3D_IMPORTER",
		"ASSIMP_BUILD_NO_LWS_IMPORTER",
		"ASSIMP_BUILD_NO_OGRE_IMPORTER",
		"ASSIMP_BUILD_NO_OPENGEX_IMPORTER",
		"ASSIMP_BUILD_NO_MS3D_IMPORTER",
		"ASSIMP_BUILD_NO_COB_IMPORTER",
		"ASSIMP_BUILD_NO_BLEND_IMPORTER",
		"ASSIMP_BUILD_NO_Q3BSP_IMPORTER",
		"ASSIMP_BUILD_NO_NDO_IMPORTER",
		"ASSIMP_BUILD_NO_IFC_IMPORTER",
		"ASSIMP_BUILD_NO_XGL_IMPORTER",
		--"ASSIMP_BUILD_NO_FBX_IMPORTER",
		"ASSIMP_BUILD_NO_ASSBIN_IMPORTER",
		"ASSIMP_BUILD_NO_GLTF_IMPORTER",
		"ASSIMP_BUILD_NO_C4D_IMPORTER",
		"ASSIMP_BUILD_NO_3MF_IMPORTER",
		"ASSIMP_BUILD_NO_X3D_IMPORTER",
		"ASSIMP_BUILD_NO_MMD_IMPORTER",
		
		"ASSIMP_BUILD_NO_STEP_EXPORTER",
		"ASSIMP_BUILD_NO_SIB_IMPORTER",
	
		-- "ASSIMP_BUILD_NO_MAKELEFTHANDED_PROCESS",
		-- "ASSIMP_BUILD_NO_FLIPUVS_PROCESS",
		-- "ASSIMP_BUILD_NO_FLIPWINDINGORDER_PROCESS",
		-- "ASSIMP_BUILD_NO_CALCTANGENTS_PROCESS",
		"ASSIMP_BUILD_NO_JOINVERTICES_PROCESS",
		-- "ASSIMP_BUILD_NO_TRIANGULATE_PROCESS",
		"ASSIMP_BUILD_NO_GENFACENORMALS_PROCESS",
		-- "ASSIMP_BUILD_NO_GENVERTEXNORMALS_PROCESS",
		"ASSIMP_BUILD_NO_REMOVEVC_PROCESS",
		"ASSIMP_BUILD_NO_SPLITLARGEMESHES_PROCESS",
		"ASSIMP_BUILD_NO_PRETRANSFORMVERTICES_PROCESS",
		"ASSIMP_BUILD_NO_LIMITBONEWEIGHTS_PROCESS",
		-- "ASSIMP_BUILD_NO_VALIDATEDS_PROCESS",
		"ASSIMP_BUILD_NO_IMPROVECACHELOCALITY_PROCESS",
		"ASSIMP_BUILD_NO_FIXINFACINGNORMALS_PROCESS",
		"ASSIMP_BUILD_NO_REMOVE_REDUNDANTMATERIALS_PROCESS",
		"ASSIMP_BUILD_NO_FINDINVALIDDATA_PROCESS",
		"ASSIMP_BUILD_NO_FINDDEGENERATES_PROCESS",
		"ASSIMP_BUILD_NO_SORTBYPTYPE_PROCESS",
		"ASSIMP_BUILD_NO_GENUVCOORDS_PROCESS",
		"ASSIMP_BUILD_NO_TRANSFORMTEXCOORDS_PROCESS",
		"ASSIMP_BUILD_NO_FINDINSTANCES_PROCESS",
		"ASSIMP_BUILD_NO_OPTIMIZEMESHES_PROCESS",
		"ASSIMP_BUILD_NO_OPTIMIZEGRAPH_PROCESS",
		"ASSIMP_BUILD_NO_SPLITBYBONECOUNT_PROCESS",
		"ASSIMP_BUILD_NO_DEBONE_PROCESS",
		"ASSIMP_BUILD_NO_EMBEDTEXTURES_PROCESS",
		"ASSIMP_BUILD_NO_GLOBALSCALE_PROCESS",
		
	}
	
	
	files {
	
	--"../../Source/**.h",
	--"../../Source/**.cpp",
	--"premake5.lua",
		
	"../../Libraries/assimp/include/assimp/*.h",
	"../../Libraries/assimp/include/assimp/*.cpp",

    "../../Libraries/assimp/code/AssetLib/Collada/*.h",
	"../../Libraries/assimp/code/AssetLib/Collada/*.cpp",
	"../../Libraries/assimp/code/AssetLib/FBX/*.h",
	"../../Libraries/assimp/code/AssetLib/FBX/*.cpp",
	"../../Libraries/assimp/code/AssetLib/Obj/*.h",
	"../../Libraries/assimp/code/AssetLib/Obj/*.cpp",
	"../../Libraries/assimp/code/AssetLib/glTF/*.h",
	"../../Libraries/assimp/code/AssetLib/glTF/*.cpp",
    "../../Libraries/assimp/code/AssetLib/glTF2/*.h",
	"../../Libraries/assimp/code/AssetLib/glTF2/*.cpp",
    
    "../../Libraries/assimp/contrib/irrXML/*.h",
	"../../Libraries/assimp/contrib/irrXML/*.cpp",
	"../../Libraries/assimp/contrib/pugixml/src/*.h",
	"../../Libraries/assimp/contrib/pugixml/src/*.cpp",
	"../../Libraries/assimp/code/Common/*.h",
	"../../Libraries/assimp/code/Common/*.cpp",
	"../../Libraries/assimp/code/Material/*.h",
	"../../Libraries/assimp/code/Material/*.cpp",
	
	"../../Libraries/assimp/code/PostProcessing/*.cpp",
	"../../Libraries/assimp/code/PostProcessing/*.h",
	
	"../../Libraries/assimp/contrib/unzip/*.h",
	"../../Libraries/assimp/contrib/unzip/*.c",
	"../../Libraries/assimp/contrib/zip/src/*.h",
	"../../Libraries/assimp/contrib/zip/src/*.c",
	"../../Libraries/assimp/contrib/zlib/*.h",
	"../../Libraries/assimp/contrib/zlib/*.c",
	}
	excludes { 
	"../../Libraries/assimp/contrib/zlib/gzlib.c",
	"../../Libraries/assimp/contrib/zlib/gzread.c",
	"../../Libraries/assimp/contrib/zlib/gzwrite.c"
	}

	includedirs {
		--"$(SolutionDir)../../Source",
		"../configs",
		"$(SolutionDir)Assimp",
		"$(SolutionDir)../Libraries/assimp/code",
		"$(SolutionDir)../Libraries/assimp/include",
		"$(SolutionDir)../Libraries/assimp/contrib/irrXML",
		"$(SolutionDir)../Libraries/assimp/contrib/pugixml/src",
		"$(SolutionDir)../Libraries/assimp/contrib/zip/src",
		"$(SolutionDir)../Libraries/assimp/contrib/unzip",
		"$(SolutionDir)../Libraries/assimp/contrib/zlib",
		"$(SolutionDir)../Libraries/assimp/contrib/rapidjson/include"
	}

	filter "system:windows"
      systemversion "latest"

	filter  "configurations:Debug"
       runtime "Debug"
       symbols "on"

	filter  "configurations:Release"
       runtime "Release"
       optimize "on"
