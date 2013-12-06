------------------------------------------------------------------------
--
-- timer.lua
-- Timer demo.
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

SDL.SDL_WM_SetCaption("Timer Demo", "Timer Demo")

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
    "Timer Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
[[

Press [1] to show current tick value
      [2] to cause a 2 second delay
      [Escape] to exit...
]]
  )
  MiniFont:SetWindow(10, 122, 550, 344)

  -- initialize interval timer, create special user event first
  local E_TIMER, E_INTERVAL, E_MAX = 99, 100, 99
  local c_data = E_MAX
  local c_event = SDL.SDL_Event_local()
  c_event.type = SDL.SDL_USEREVENT
  c_event.user.code = E_TIMER
  -- start up interval timer
  local c_handle = SDL.SDL_AddTimer(E_INTERVAL, c_event)

  -- display current tick value
  local function ShowTicks()
    MiniFont:GotoXY(0, 0)
    MiniFont:Print("Tick value: "..string.format("%-12d", SDL.SDL_GetTicks()))
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  end

  -- demonstrate delay call
  local function ShowDelay()
    MiniFont:GotoXY(0, 2)
    MiniFont:Print(string.rep(" ", 30))
    MiniFont:GotoXY(0, 2)
    MiniFont:Print("SDL_Delay: start... ")
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
    -- disable interval timer, then do delay, and finally re-enable timer
    SDL.SDL_RemoveTimer(c_handle)
    SDL.SDL_Delay(2000)
    c_handle = SDL.SDL_AddTimer(E_INTERVAL, c_event)
    MiniFont:Print("done.")
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  end

  -- event 'callback' function to display counting
  local function Callback1()
    MiniFont:GotoXY(0, 4)
    MiniFont:Print("Interval timer test: "..string.format("%-12d", c_data))
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
    if c_data == 0 then
      c_data = E_MAX
    else
      c_data = c_data - 1
    end
  end

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
        ShowTicks()
      elseif key == SDL.SDLK_2 then
        ShowDelay()
      end
    elseif c == SDL.SDL_USEREVENT then
      if c_event.user.code == E_TIMER then
        Callback1()
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
