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
	cppdialect "C++17"

    buildoptions "-g -O2 -ffile-prefix-map=/build/graphicsmagick-jeuA19/graphicsmagick-1.4+really1.3.36+hg16481=. -fstack-protector-strong -Wformat -Werror=format-security -pthread"

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
   }

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/json/single_include",
		"%{prj.name}/vendor/rpi-rgb-led-matrix/include",
		"%{prj.name}/vendor/spdlog/include",
    }

	links
	{
        "RGBMatrix",
        "pthread",
        "GraphicsMagick++",
        "GraphicsMagick",
        "jbig",
        "webp",
        "webpmux",
        "lcms2",
        "tiff",
        "freetype",
        "jpeg",
        "png16",
        "wmflite",
        "Xext",
        "SM",
        "ICE",
        "X11",
        "lzma",
        "bz2",
        "xml2",
        "z",
        "zstd",
        "m",
        "gomp",
        "oatpp::oatpp",
        "oatpp::oatpp-swagger"
	}

	defines {
	    "OATPP_SWAGGER_RES_PATH=\"${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res\"",
	}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "DEBUG" }
      optimize "On"

project "RGBMatrix"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/%{prj.name}")
	objdir ("bin/obj")

    files
    {
        "ProtOS/vendor/rpi-rgb-led-matrix/include/**.h",
        "ProtOS/vendor/rpi-rgb-led-matrix/lib/**.h",
        "ProtOS/vendor/rpi-rgb-led-matrix/lib/**.c",
        "ProtOS/vendor/rpi-rgb-led-matrix/lib/**.cc",
    }

	includedirs
	{
		"ProtOS/vendor/rpi-rgb-led-matrix/include",
    }

    defines { "DEBUG" }
    optimize "On"