solution "opentp"
    configurations {"debug", "release"}
    language "C++"

    includedirs {
        "src/include"
    }

    project "gameoflife"
        kind "ConsoleApp"

        files {
            "src/source/**.cpp"
        }
