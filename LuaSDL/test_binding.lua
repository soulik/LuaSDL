------------------------------------------------------------------------
--
-- test_binding.lua
-- A primitive program to test a minimal binding.
--
-- This file is part of LuaSDL.
--
-- PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
--
------------------------------------------------------------------------

------------------------------------------------------------------------
--
-- Program should print a message to stdout[.txt] if successful.
-- Any error results in an exit code >0 and messages in stderr.txt.
--
------------------------------------------------------------------------

-- localize SDL library
local SDL = SDL

local result = 0

-- test initialization of SDL
if SDL.SDL_Init(SDL.SDL_INIT_AUDIO + SDL.SDL_INIT_VIDEO) < 0 then
  error("Couldn't initialize SDL: %s\n", SDL.SDL_GetError())
  os.exit(1)
end

-- test initialization of SDL_image
local image = SDL.IMG_Load("test_binding.lua")
if image then
  error("IMG_Load not supposed to work\n")
  result = 1
end

-- test initialization of SDL_mixer
if SDL.Mix_OpenAudio(44100, SDL.MIX_DEFAULT_FORMAT, 2, 2048) < 0 then
  error("Couldn't initialize SDL_mixer\n")
  result = 1
end
SDL.Mix_CloseAudio()

-- test initialization of SDL_net
if SDL.SDLNet_Init() == -1 then
  error("Couldn't initialize SDL_net: %s\n", SDL.SDLNet_GetError())
  result = 1
else
  SDL.SDLNet_Quit()
end

-- test initialization of SDL_ttf
if SDL.TTF_Init() == -1 then
  error("Couldn't initialize SDL_ttf: %s\n", SDL.TTF_GetError());
  result = 1
else
  SDL.TTF_Quit()
end

SDL.SDL_Quit()

print("Simple binding tester ran successfully.")

os.exit(result)
