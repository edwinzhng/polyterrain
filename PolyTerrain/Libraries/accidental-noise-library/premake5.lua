-- Accidental Noise Library
-- premake5.lua

local usethread=true 

workspace "ANL"
	configurations {"Debug", "Release"}
	platforms {"x32", "x64", "Universal"}
	location "build"
	
	if usethread then defines { "USETHREAD" } end
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		flags "Symbols"
		optimize "Off"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "Speed"
		
	filter "platforms:x32"
    targetdir "build/ANL/x86"
    
  filter "platforms:x64"
    targetdir "build/ANL/x64"
    
  filter "platforms:Universal"
    targetdir "build/ANL/Universal"
	
	project "ANL"
		kind "StaticLib"
		location "build/ANL"
		language "C++"
		vectorextensions "SSE2"
		if _ACTION=="gmake" then
			buildoptions "-std=c++11"
		end
		
		files {"VM/*.h", "VM/*.cpp", "Imaging/*.h", "Imaging/*.cpp", "Imaging/*.c", "Expression/*.h", "Expression/*.cpp", "templates/*.h", "vectortypes.h"}