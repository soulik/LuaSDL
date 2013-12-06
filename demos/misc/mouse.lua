------------------------------------------------------------------------
--
-- mouse.lua
-- Mouse event demo.
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

SDL.SDL_WM_SetCaption("Mouse Demo", "Mouse Demo")

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
    "Mouse Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
[[

Do something with the mouse to see event information.
Press [Escape] to exit...
]]
  )

  -- decode button event value for verbose display
  local blist = {
    [SDL.SDL_BUTTON_LEFT] = "left",
    [SDL.SDL_BUTTON_MIDDLE] = "middle",
    [SDL.SDL_BUTTON_RIGHT] = "right",
    [SDL.SDL_BUTTON_WHEELUP] = "wheelup",
    [SDL.SDL_BUTTON_WHEELDOWN] = "wheeldown",
  }
  local function GetButtonName(b)
    return blist[b] or "unknown"
  end
  local function GetButtonState(s)
    if s == SDL.SDL_PRESSED then return "pressed" else return "released" end
  end

  -- decode motion event value for verbose display
  local function GetButtons(s)
    local info = ""
    if SDL.Bool(SDL.And(s, SDL.SDL_BUTTON_LMASK)) then
      info = info.."(left) "
    end
    if SDL.Bool(SDL.And(s, SDL.SDL_BUTTON_MMASK)) then
      info = info.."(middle) "
    end
    if SDL.Bool(SDL.And(s, SDL.SDL_BUTTON_RMASK)) then
      info = info.."(right) "
    end
    return info
  end

  -- display information about mouse event
  local function DoMouseEvent(typ, event)
    -- common information
    local info = "Device index: "..event.which.."\n"..
                 "X coords: "..event.x.."\n"..
                 "Y coords: "..event.y.."\n"
    if typ == "motion" then
      info = info.."Button state: "..GetButtons(event.state).."\n"..
                   "X relative: "..event.xrel.."\n"..
                   "Y relative: "..event.yrel.."\n"
    elseif typ == "button" then
      info = info.."Button state: "..GetButtonState(event.state).."\n"..
                   "Button index: "..GetButtonName(event.button).."\n"
    end
    MiniFont:SetWindow(10, 122, 550, 344)
    MiniFont:Clear()
    MiniFont:Print(
      "Information about mouse event:\n",
      "------------------------------\n",
      info,
      "\n"
    )
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  end

  -- display screen and event loop
  SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  local event = SDL.SDL_Event_local()
  while true do
    if SDL.SDL_WaitEvent(event) ~= 0 then
      local c = event.type
      if c == SDL.SDL_MOUSEMOTION then
        DoMouseEvent("motion", event.motion)
      elseif c == SDL.SDL_MOUSEBUTTONDOWN or
             c == SDL.SDL_MOUSEBUTTONUP then
        DoMouseEvent("button", event.button)
      elseif c == SDL.SDL_KEYDOWN then
        local key = event.key.keysym.sym
        if key == SDL.SDLK_ESCAPE then
          break
        end
      elseif c == SDL.SDL_QUIT then
        break
      end
    end
  end--while

end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
