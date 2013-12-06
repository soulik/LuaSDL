------------------------------------------------------------------------
--
-- http_reflector.lua
-- TCP server demo, sends back HTTP request to client.
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

SDL.SDL_WM_SetCaption("HTTP Reflector Demo", "HTTP Reflector Demo")

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
    "HTTP Reflector Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
[[

Listening to port 80, try "http://localhost/" on a browser...
Press [Escape] to exit...

]]
  )

  -- small buffer to force multiple reads, for testing
  local SIZE = 20
  local data = SDL.SDL_malloc_local(SIZE, "Uint8[]")

  -- function to handle HTTP reflection, note that no effort has
  -- been made to implement RFC2616 properly
  local function CheckSocket()
    local client = SDL.SDLNet_TCP_Accept(server)
    if client then
      local recv, send = ""
      -- receive HTTP header
      while true do
        local actual = SDL.SDLNet_TCP_Recv(client, data, SIZE)
        if actual <= 0 then break end -- error or end of connection
        recv = recv..SDL.SDL_memtostr(data, actual)
        -- stop receiving if at end of HTTP header
        if string.match(recv, "\r\n\r\n$") then break end
      end
      -- reflect HTTP header stuff back to client
      rcv2 = "<html><body><pre>\n"..
             recv..
             "</pre></body><html>\n"
      send = "HTTP/1.1 200 OK\r\n"..
             "Connection: close\r\n"..
             "Content-Length: "..#rcv2.."\r\n"..
             "Content-Type: text/html\r\n"..
             "\r\n"..
             rcv2
      local dat2 = SDL.SDL_strtomem(send)
      SDL.SDLNet_TCP_Send(client, dat2, #send)
      -- end of connection
      SDL.SDLNet_TCP_Close(client)
      -- display received data on server
      MiniFont:SetWindow(10, 122, 550, 344)
      MiniFont:Clear()
      MiniFont:Print("[BEGIN]\n"..recv.."[END]\n")
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
