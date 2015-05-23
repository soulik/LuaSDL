local lfs = require 'lfs'
local apinames_exec = [[""./../../../../build/dependencies/sdl_ttf/external/freetype-2.5.5/build/Debug/apinames.exe""]]
local def_file = [[src/freetype.def]]

local hdr_files = {}
for fn in lfs.dir('include') do
	if fn:match('.+%.h$') then
		local path = 'include/'..fn
		if not fn:match('ftmac') then
			table.insert(hdr_files, path)
		end
	end
end

os.execute(('%s -dfreetype.dll -w -o%s %s'):format(apinames_exec, def_file, table.concat(hdr_files, ' ')))
local df = assert(io.open(def_file, 'a'))
df:write(
[[TT_New_Context
TT_RunIns
]])

df:close()
