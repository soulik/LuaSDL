------------------------------------------------------------------------
--
-- tcp_client_demo.lua
-- TCP client demos.
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

SDL.SDL_WM_SetCaption("TCP Client Demo", "TCP Client Demo")

------------------------------------------------------------------------

--
-- startup
--
local screen = SDL.SDL_SetVideoMode(640, 480, 32, 0)
if not screen then
  error("Couldn't set video mode: "..SDL.SDL_GetError().."\n")
else

  if SDL.SDLNet_Init() ~= 0 then
    error("SDLNet_Init: "..SDL.SDLNet_GetError().."\n")
  end

  -- create a server type IPaddress
  local addr = SDL.IPaddress_local()
  if SDL.SDLNet_ResolveHost(addr, "localhost", 80) ~= 0 then
    error("SDLNet_ResolveHost: "..SDL.SDLNet_GetError().."\n")
  end

  if not MiniFont_New then
    MiniFont_New = loadfile(SDL.LuaSDL_DirExe.."minifont.lua")
  end
  local MiniFont = MiniFont_New()
  MiniFont:SetSurface(screen)
  MiniFont:SetWindow(10, 10, 550, 440)
  MiniFont:Clear()
-- [=[
  MiniFont:Print(
    "TCP Client Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
    "To connect, with IPaddress parameters of:\n\n",
    "addr.host = "..string.format("%08X", addr.host).."\n",
    "addr.port = "..string.format("%04X", addr.port).."\n"
  )
  MiniFont:Print(
[[

Press [Space] to make a connection,
      [Escape] to exit...

]]
  )

  local data = SDL.SDL_malloc_local(4, "Uint8[]")

  -- function to handle connections
  local function ConnectServer()
    -- open a socket for connecting
    local tcpsock = SDL.SDLNet_TCP_Open(addr)
    if not tcpsock then
      MiniFont:Print("Failed to open socket...\n")
    else
      local value = string.format("%04d", math.random(1, 9999))
      for i = 1, 4 do
        data[i-1] = string.byte(value, i)
      end
      MiniFont:Print("Connected, sent number ["..value.."]...")
      local actual = SDL.SDLNet_TCP_Send(tcpsock, data, 4)
      if actual ~= 4 then
        MiniFont:Print("FAIL("..actual..")\n")
        MiniFont:Print("SDLNet_TCP_Send: "..SDL.SDLNet_GetError().."\n")
      else
        MiniFont:Print("OK\n")
      end
      SDL.SDLNet_TCP_Close(tcpsock)
    end
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
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
      elseif key == SDL.SDLK_SPACE then
        ConnectServer()
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

  -- clean up SDL_net stuff
  SDL.SDLNet_Quit()

end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
