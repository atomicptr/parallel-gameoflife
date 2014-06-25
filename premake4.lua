solution "opentp"
    configurations {"debug", "release"}
    language "C++"

    includedirs {
        "src/include"
    }

    buildoptions "-std=c++11"

    configuration "debug"
        flags { "Symbols" }

    project "gameoflife"
        kind "ConsoleApp"

        links {
            "pthread"
        }

        files {
            "src/source/**.cpp"
        }
