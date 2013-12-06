------------------------------------------------------------------------
--
-- keyboard.lua
-- Keyboard event demo.
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

SDL.SDL_WM_SetCaption("Keyboard Demo", "Keyboard Demo")

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
    "Keyboard Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
[[

This demo will display key press and release events.
Press shift with a key to test repeat capability.
Press [Escape] to exit...
]]
  )

  -- display some information about modifier state
  local function DoKeyMods(keymod)
    local mod = ""
    if SDL.Bool(SDL.And(keymod, SDL.KMOD_CTRL)) then
      mod = mod.."(ctrl) "
    end
    if SDL.Bool(SDL.And(keymod, SDL.KMOD_SHIFT)) then
      mod = mod.."(shift) "
    end
    if SDL.Bool(SDL.And(keymod, SDL.KMOD_ALT)) then
      mod = mod.."(alt) "
    end
    if SDL.Bool(SDL.And(keymod, SDL.KMOD_META)) then
      mod = mod.."(meta) "
    end
    return mod
  end

  -- display key states for multiple keys
  local klist = {
    ["0"] = SDL.SDLK_0,
    ["1"] = SDL.SDLK_1,
    ["2"] = SDL.SDLK_2,
    ["3"] = SDL.SDLK_3,
    ["4"] = SDL.SDLK_4,
    ["5"] = SDL.SDLK_5,
    ["6"] = SDL.SDLK_6,
    ["7"] = SDL.SDLK_7,
    ["8"] = SDL.SDLK_8,
    ["9"] = SDL.SDLK_9,
  }
  local function DoKeyState()
    local keys = SDL.SDL_GetKeyState()
    local info = ""
    for sym, code in pairs(klist) do
      if keys[code] == SDL.SDL_PRESSED then
        info = info.."("..sym..") "
      else
        info = info.." "..sym.."  "
      end
    end
    MiniFont:Print(
      "States of digit keys:\n",
      "---------------------\n",
      info.."\n",
      "\n"
    )
  end

  -- display detailed mod state
  local mlist = {
    ["(lshift)"] = SDL.KMOD_LSHIFT,
    ["(rshift)"] = SDL.KMOD_RSHIFT,
    ["(lctrl)"] = SDL.KMOD_LCTRL,
    ["(rcrtl)"] = SDL.KMOD_RCTRL,
    ["(lalt)"] = SDL.KMOD_LALT,
    ["(ralt)"] = SDL.KMOD_RALT,
    ["(lmeta)"] = SDL.KMOD_LMETA,
    ["(rmeta)"] = SDL.KMOD_RMETA,
    ["(num)"] = SDL.KMOD_NUM,
    ["(caps)"] = SDL.KMOD_CAPS,
  }
  local function DoModState()
    local mod = SDL.SDL_GetModState()
    local info = ""
    for sym, code in pairs(mlist) do
      if SDL.Bool(SDL.And(mod, code)) then
        info = info..sym.." "
      end
    end
    MiniFont:Print(
      "Detailed state of key modifiers:\n",
      "--------------------------------\n",
      info.."\n",
      "\n"
    )
  end

  -- demonstration of key repeat
  local function DoKeyRepeat(keyEvent)
    local key = keyEvent.keysym
    if key.sym == SDL.SDLK_RSHIFT or key.sym == SDL.SDLK_LSHIFT then
      if keyEvent.state == SDL.SDL_PRESSED then
        SDL.SDL_EnableKeyRepeat(SDL.SDL_DEFAULT_REPEAT_DELAY, SDL.SDL_DEFAULT_REPEAT_INTERVAL)
      else
        SDL.SDL_EnableKeyRepeat(0, 0)
      end
    end
  end

  -- display some information about a keyboard event
  local c = 0
  local function DoKeyEvent(keyEvent)
    MiniFont:SetWindow(10, 138, 550, 360)
    MiniFont:Clear()
    local state = (keyEvent.state == SDL.SDL_PRESSED) and "(pressed)" or "(released)"
    local key = keyEvent.keysym
    c = c + 1
    MiniFont:Print(
      "Information about key event:\n",
      "----------------------------\n",
      "Event count: "..c.."\n",
      "Name: "..SDL.SDL_GetKeyName(key.sym).."\n",
      "State: "..state.."\n",
      "Modifiers: "..DoKeyMods(key.mod).."\n",
      "\n"
    )
    DoKeyState()
    DoModState()
    DoKeyRepeat(keyEvent)
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  end

  -- display screen and event loop
  SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  local event = SDL.SDL_Event_local()
  while true do
    if SDL.SDL_WaitEvent(event) ~= 0 then
      local c = event.type
      if c == SDL.SDL_KEYDOWN or c == SDL.SDL_KEYUP then
        local key = event.key.keysym.sym
        if key == SDL.SDLK_ESCAPE then
          break
        else
          DoKeyEvent(event.key)
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
