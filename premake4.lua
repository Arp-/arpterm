
bin_dir = "bin/"
obj_dir = "obj/"
src_dir = "src/"
inc_dir = "inc/"

-- A solution contains projects, and defines the available configurations
solution "arpterm"
	configurations { "Debug", "Release" }

	configuration "Debug"
		objdir (obj_dir .. "debug")
		targetdir (bin_dir .. "debug")

	configuration "Release"
		objdir (obj_dir .. "release")
		targetdir (bin_dir .. "release")



-- A project defines one build target
	project "arpterm"
		kind "ConsoleApp"
		language "C++"
		includedirs {
			inc_dir
		}
		files { 
			inc_dir .. "**.h",
			src_dir .. "**.cpp"
		}

		configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

		configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
