solution "opentp"
    configurations {"debug", "release"}
    language "C++"

    includedirs {
        "src/include"
    }

    buildoptions "-std=c++11 -stdlib=libc++"

    project "gameoflife"
        kind "ConsoleApp"

        files {
            "src/source/**.cpp"
        }
