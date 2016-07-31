--[[
----STUFFY_LUA----

Description:

This thing is a function bundle for a premake4.lua file, that allows
a programmer, to copy, and remove (aka. install and uninstall) files
to a folder and remove them.

Usage:

stuffy.install(my_table)

--	or

stuffy.uninstall(my_table)

--	where my_table is a table like:

my_table = {
	{"FROM_PATH","STATIC_PATH","DYNAMIC_PATH"},		--or
	{"FROM_PATH","STATIC_PATH"}		--third option will work like there's an empty string given as DYNAMIC_PATH

--examples:
	{"$HOME/asd.txt", "/usr/include/", "my_stuff/asd.txt"}	 -- install creates /usr/include/my_stuff 
															 -- and copies
															 -- asd.txt into
															 -- my_stuff

	{"$HOME/some_dir/*","/usr/bin/mydir/", "my_dir/"		 -- install copies everything
															 -- from
															 -- $HOME/some_dir
															 -- to
															 -- /usr/bin/mydir/my_dir
															 -- and creates
															 -- /usr/bin/mydir/my_dir
															 -- along the path.

	{"$HOME/somedir/stg","/usr/bin/"} is equivalent to {"$HOME/somedir/stg","/usr/bin/", ""}

	-- which copies 'stg' file into '/usr/bin'

	-- the uninstall action only deletes, the DYNAMIC_PATH 
	-- so if you have something like

	{"$HOME/somedir/stg", "/usr/bin/", "mydir/stg" }

	-- then only mydir and everything it contains gets deleted.
	-- THE FOLLOWING BEHAVIOUR IS AVOIDABLE

	-- {"$HOME/somedir/*", "/usr/bin/", "" }

	-- copies everything from $HOME/somedir into /usr/bin, BUT
	-- when we call uninstall it'll fail, because it'll try to call
	-- os.remove("/usr/bin/*"), and you can't delete like this
	-- and that's the why the uninstall will FAIL
	-- THEREFORE: It is NOT RECOMMENDED to use FROM_PATH like this.
}

Requirements:
	it has to be called from a premake4.lua file, and
	obviously premake4 has to be installed on your system.

--]]

stuffy = {

	safe = {

		mkdir = function(pth)
			print ("mkdir: `" .. pth .. "´")
			local result,msg = os.mkdir(pth)
			if not result then
				error(msg)
			end
		end,


		copyfile = function(from,to)
			print ("copy: `" .. from .. "´-->`" .. to .. "´")
			local result,msg = os.copyfile(from,to)
			if not result then
				error(msg)
			end
		end,


		remove = function(path)
			print ("remove: `" .. path .. "´")
			local result,msg=os.remove(path)
			if not result then
				print(msg)
			end
		end,


		rmdir = function(path)
			print("rmdir: `" .. path .. "´")
			local result,msg=os.rmdir(path)
			if stuffy.safe.exists(path) then
				print("rmdir failed on: ",path)
			end
		end,


		exists=function (name)
			if type(name)~="string" then return false end
			return os.rename(name,name) and true or false
		end,


		link=function(what,to)
			print("link: `" .. what .. " --> " .. to .. "´")
			local result,msg=os.execute("ln -s " .. what .. " " .. to)
			if not result then
				error(msg)
			end
		end,

		execute=function(what)
			print("executing: `" .. what .. "'")
			local result,msg=os.execute(what)
			if not result then
				error(msg)
			end
		end

	},


	mkpath = function(s)
		rv = {}
		local two = true
		local one = nil
		while two do
			one,two = s:match("([^/]*)/(.*)")
			if not one and not two then
				rv[#rv+1] = s
			else
				s = two
				rv[#rv+1] = one
			end
		end
		return rv
	end,


	make_dirs = function(t)
		local tab=stuffy.mkpath(t)
		local path=tab[1]
		local s=1
		if path == "" then
			path="/" .. tab[2]
			s=2
		end
		for j=s+1,(#tab-1) do 
			if not stuffy.safe.exists(path) then
				stuffy.safe.mkdir(path)
			end
			path = path .. "/" .. tab[j]
		end
		stuffy.safe.mkdir(path)
		if tab[#tab] ~= "" then
			path = path .. tab[#tab]
		end
	end,


	install = function(tab)
		for i=1,#tab do
			tab[i][3] = tab[i][3] or ""
			tab[i].link = tab[i].link or false
			if not stuffy.safe.exists(tab[i][2] .. tab[i][3]) then
				stuffy.make_dirs(tab[i][2] .. tab[i][3])
			end
			if not tab[i].link then
				stuffy.safe.copyfile(tab[i][1],tab[i][2] .. tab[i][3])
			else
				stuffy.safe.link(tab[i][1],tab[i][2] .. tab[i][3])
			end
		end
	end,


	uninstall = function(tab)
		for i=1,#tab do
			tab[i][3] = tab[i][3] or ""
			local dyn_dirs=stuffy.mkpath(tab[i][3])
			local from_dirs=stuffy.mkpath(tab[i][1])
			if((#dyn_dirs==1) and (dyn_dirs[1] == "")) then
				stuffy.safe.remove(tab[i][2] .. from_dirs[#from_dirs])
			elseif(#dyn_dirs==1) then
				stuffy.safe.remove(tab[i][2] .. dyn_dirs[1])
			else
				stuffy.safe.rmdir(tab[i][2] .. dyn_dirs[1])
			end
		end
	end,

	archive = function(tab,name)
		local tar_comm="tar czfv " .. name .. ".tar.gz "
		local file_list=""
		for i=1,#tab do
			file_list = file_list .. tab[i][1] .. " "
		end
		file_list=file_list .. "stuffy.lua "
		file_list=file_list .. "premake4.lua"
		os.execute(tar_comm .. file_list)
	end,

	make_version_hpp = function(version, copyright_text, incdir, project_headers, maintainer)
		for i,p in ipairs(project_headers) do
			-- p[1] is the name of the main project folder
			-- p[2] is the name of the project in its include directory
			local f = assert(io.open(p[1].."/"..incdir..p[2].."/version.hpp","w+"))
			local project_name = string.gsub(p[2],"-","_")
			local pcap = project_name:upper()
			local maintainerStr = "";
			if #maintainer == 1 then
				maintainerStr = "Maintainer: "
			else
				maintainerStr = "Maintainers: "
			end
			for i=1,#maintainer do
				maintainerStr = maintainerStr .. maintainer[i] .. ", "
			end
			maintainerStr = maintainerStr:gsub(", $", ".");

			f:write(
				"/**\n"..
				" * @file "..p[2].."/version.hpp\n"..
				" * @brief Auto-generated version header for '"..p[2].."'. Please do not change this file directly.\n"..
				" */\n"..
				"\n"..
				"#ifndef "..pcap.."_VERSION_HPP\n"..
				"#define "..pcap.."_VERSION_HPP\n"..
				"\n"..
				"#define "..pcap.."_VERSION_MAJOR "..version.Major.."\n"..
				"#define "..pcap.."_VERSION_MINOR "..version.Minor.."\n"..
				"#define "..pcap.."_VERSION_REVISION "..version.Revision.."\n"..
				"\n"..
				"static constexpr const char* " .. project_name .. "_version(void) {\n"..
				"\treturn \""..version.Major.."."..version.Minor.."."..version.Revision.."\";\n"..
				"}\n" ..
				"\n" ..
				"static constexpr const char* " .. project_name .. "_copyright(void) {\n" ..
				"\treturn \"" .. copyright_text .."\";\n" ..
				"}\n" ..
				"static constexpr const char* " .. project_name .. "_maintainer(void) {\n" ..
				"\treturn \"" .. maintainerStr .. "\";\n" ..
				"}\n" ..
				"\n"..
				"#endif // " .. pcap .. "_VERSION_HPP\n"
			);
			f:close()
		end
	end

}
