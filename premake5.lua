workspace "ProtOS"
	configurations
	{
		"Debug",
		"Release",
	}

	flags
	{
		"MultiProcessorCompile"
	}

project "ProtOS"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/%{prj.name}")
	objdir ("bin/obj")

	pchheader "%{prj.name}/src/PCH.h"
	pchsource "%{prj.name}/src/PCH.cpp"

   files
   {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/vendor/rpi-rgb-led-matrix/include/**.h",
        "%{prj.name}/vendor/rpi-rgb-led-matrix/lib/**.h",
        "%{prj.name}/vendor/rpi-rgb-led-matrix/lib/**.c",
        "%{prj.name}/vendor/rpi-rgb-led-matrix/lib/**.cc",
   }

	includedirs
	{
		"%{prj.name}/src",

		"%{prj.name}/vendor/CImg",
		"%{prj.name}/vendor/json/single_include",
		"%{prj.name}/vendor/rpi-rgb-led-matrix/include",
		"%{prj.name}/vendor/spdlog/include",
    }

	links
	{
	    "pthread",
	    "X11"
	}

	defines
	{
	}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "DEBUG" }
      optimize "On"
