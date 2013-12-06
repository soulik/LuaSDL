------------------------------------------------------------------------
--
-- directories.lua
-- Directories demos.
--
-- This file is part of LuaSDL.
--
-- PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
--
------------------------------------------------------------------------

-- local ref to SDL library
local SDL = SDL

-- test initialization of SDL
if SDL.SDL_Init(SDL.SDL_INIT_EVERYTHING) < 0 then
  error("Couldn't initialize SDL: "..SDL.SDL_GetError().."\n")
  os.exit(1)
end

SDL.SDL_WM_SetCaption("Directories Demo", "Directories Demo")

------------------------------------------------------------------------

--
-- startup
--
local screen = SDL.SDL_SetVideoMode(640, 480, 32, 0)
if not screen then
  error("Couldn't set video mode: "..SDL.SDL_GetError().."\n")
else

  if not MiniFont_New then
    MiniFont_New = loadfile(SDL.LuaSDL_DirExe.."minifont.lua")
  end
  local MiniFont = MiniFont_New()
  MiniFont:SetSurface(screen)
  MiniFont:SetWindow(10, 10, 550, 440)
  MiniFont:Clear()
-- [=[
  MiniFont:Print(
    "Directories Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  -- test absolute path constants
  MiniFont:Print(
    "Paths passed to LuaSDL:\n",
    "DirCwd = ", SDL.LuaSDL_DirCwd, "\n",
    "DirExe = ", SDL.LuaSDL_DirExe, "\n",
    "DirApp = ", SDL.LuaSDL_DirApp, "\n",
    "AppName = ", SDL.LuaSDL_AppName, "\n",
    "\n"
  )
  -- test application configuration path constants
  MiniFont:Print(
    "Application paths:\n",
    "PERSONAL = ", SDL.LuaSDL_DirCfg.PERSONAL, "\n",
    "APPDATA = ", SDL.LuaSDL_DirCfg.APPDATA, "\n",
    "LOCAL_APPDATA = ", SDL.LuaSDL_DirCfg.LOCAL_APPDATA, "\n",
    "COMMON_APPDATA = ", SDL.LuaSDL_DirCfg.COMMON_APPDATA, "\n",
    "\n"
  )

  -- for this, go to your APPDATA directory and monitor the results
  -- configuration
  local APPDIR = "LuaSDL"
  if not SDL.__WIN32__ then APPDIR = ".luasdl" end
  local CFGFILE = "/dir_demo_config.dat"
  local CFGPATH = SDL.LuaSDL_DirCfg.APPDATA.."/"..APPDIR
  -- support functions
  local function file_exists(path)
    local h = io.open(path)
    if h then h:close(); return true end
    return false
  end

  -- create sample application data directory in APPDATA
  local function  config_create()
    if not file_exists(CFGPATH) then
      -- but CFGPATH may be already created, so ignore errors...
      SDL.LuaSDL_mkdir(CFGPATH)
    end
    -- write a sample file, needs more error checking if you want it to
    -- be more robust or more bullet-proof
    local h = io.open(CFGPATH..CFGFILE, "w")
    if not h then
      error("cannot create configuration file for writing")
    else
      h:write("this is a sample configuration file for an application\n")
      h:close()
    end
  end

  -- remove sample application data directory from APPDATA
  local function config_delete()
    -- alternatively, we can do this via absolute paths...
    if not SDL.LuaSDL_chdir(CFGPATH) then
      error("cannot chdir to application data directory, missing?")
    end
    -- indiscriminately remove all files, will fail for subdirectories
    local dirlist = SDL.LuaSDL_lsdir("*")
    for i = 1, #dirlist do
      os.remove(dirlist[i])
    end
    -- in WinNT versions of Win32, rmdir will fail if the current working
    -- directory is within the path to be deleted, hence, we must chdir
    -- out of the area before deleting
    SDL.LuaSDL_chdir(SDL.LuaSDL_DirCfg.PERSONAL)
    SDL.LuaSDL_rmdir(CFGPATH)
  end

  MiniFont:Print(
[[

Press [1] create an application data directory
      [2] remove an application data directory
      (go to your APPDATA folder to see the changes)
      [Escape] to exit...
]]
  )

  -- display screen and event loop
  SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  local event = SDL.SDL_Event_local()
  while true do
    while (SDL.SDL_PollEvent(event) == 0) do
      SDL.SDL_Delay(10)
    end
    local c = event.type
    if c == SDL.SDL_KEYDOWN then
      local key = event.key.keysym.sym
      if key == SDL.SDLK_ESCAPE then
        break
      elseif key == SDL.SDLK_1 then
        config_create()
      elseif key == SDL.SDLK_2 then
        config_delete()
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
