------------------------------------------------------------------------
--
-- tcp_server_demo.lua
-- TCP server demos.
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

SDL.SDL_WM_SetCaption("TCP Server Demo", "TCP Server Demo")

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
  if SDL.SDLNet_ResolveHost(addr, nil, 80) ~= 0 then
    error("SDLNet_ResolveHost: "..SDL.SDLNet_GetError().."\n")
  end

  -- open a socket for listening
  local server = SDL.SDLNet_TCP_Open(addr)
  if not server then
    error("SDLNet_TCP_Open: "..SDL.SDLNet_GetError().."\n")
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
    "TCP Server Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
    "Listening, with IPaddress parameters of:\n\n",
    "addr.host = "..string.format("%08X", addr.host).."\n",
    "addr.port = "..string.format("%04X", addr.port).."\n"
  )
  MiniFont:Print(
[[

Press [Escape] to exit...

]]
  )

  local data = SDL.SDL_malloc_local(4, "Uint8[]")

  -- function to handle connections
  local function CheckSocket()
    local client = SDL.SDLNet_TCP_Accept(server)
    if client then
      MiniFont:Print("Connected, ")
      local actual = SDL.SDLNet_TCP_Recv(client, data, 4)
      if actual ~= 4 then
        MiniFont:Print("receive FAIL("..actual..")\n");
        MiniFont:Print("SDLNet_TCP_Recv: "..SDL.SDLNet_GetError().."\n")
      else
        local value = string.char(data[0], data[1], data[2], data[3])
        MiniFont:Print("received number ["..value.."]\n")
      end
      SDL.SDLNet_TCP_Close(client)
      SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
    end
  end

  -- display screen and event loop
  SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  local event = SDL.SDL_Event_local()
  while true do
    while (SDL.SDL_PollEvent(event) == 0) do
      CheckSocket()
      SDL.SDL_Delay(10)
    end
    local c = event.type
    if c == SDL.SDL_KEYDOWN then
      local key = event.key.keysym.sym
      if key == SDL.SDLK_ESCAPE then
        break
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

  -- clean up SDL_net stuff
  SDL.SDLNet_TCP_Close(server)
  SDL.SDLNet_Quit()

end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
