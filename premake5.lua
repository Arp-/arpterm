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
			inc_dir .. "**.hpp",
			src_dir .. "**.cpp"
		}

		buildoptions {
			"`pkg-config --cflags gtkmm-3.0`",
		}
		linkoptions {
			"`pkg-config --libs gtkmm-3.0`"
		}

		configuration "Debug"
		symbols "ON"
		defines { "DEBUG" }

		configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
