require("stuffy")
--[[-------------------------------------------------------------------------]]--
--%% DEFINES %%--
bin_dir = "bin/"
obj_dir = "obj/"
src_dir = "src/"
inc_dir = "inc/"
--[[-------------------------------------------------------------------------]]--
--%% ACTIONS %%--
newaction {
	trigger = "clean",
	description = "cleans the solution and the makefiles",
	execute = function()
		print("cleaning...")
		stuffy.safe.execute("make clean")
		stuffy.safe.rmdir("./obj")
		stuffy.safe.rmdir("./bin")
		stuffy.safe.remove("*.make")
		stuffy.safe.remove("Makefile")
	end
}
--[[-------------------------------------------------------------------------]]--
-- A solution contains projects, and defines the available configurations

solution "arpterm"
	configurations { "Debug", "Release" }

	configuration "Debug"
		objdir (obj_dir .. "debug")
		targetdir (bin_dir .. "debug")
		symbols "ON"
		defines { "DEBUG" }

	configuration "Release"
		objdir (obj_dir .. "release")
		targetdir (bin_dir .. "release")
		defines { "RELEASE" }
		flags { "Optimize" }


-- A project defines one build target
	project "arpterm"
		kind "ConsoleApp"
		language "C++"
		includedirs {
			inc_dir
		}
		files { 
			inc_dir .. "arpterm/**.hpp",
			src_dir .. "arpterm/**.cpp"
		}

		links { 
			"pthread",
		}

		buildoptions {
			"`pkg-config --cflags gtkmm-3.0`",
			"-std=c++14",
			"-Wall",
		}
		linkoptions {
			"`pkg-config --libs gtkmm-3.0`"
		}

		defines { "_XOPEN_SOURCE 600" }

--[[-------------------------------------------------------------------------]]--
	project "generic_parser"
		kind "consoleApp"
		language "C++"
		includedirs {
			inc_dir
		}


		files {
			inc_dir .. "generic_parser/**.hpp",
			src_dir .. "generic_parser/**.cpp",
		}

		excludes { 
		--	src_dir .. "generic_parser/main.cpp"
		}
--[[-------------------------------------------------------------------------]]--
	project "test"
	kind "consoleApp"
	language "C++"
	includedirs {
		inc_dir
	}

	files {
		src_dir .. "test/**.cpp",
	}

	excludes {

	}
