------------------------------------------------------------------------
--
-- audio_demo.lua
-- Demonstrates playing of samples using SDL_mixer.
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

SDL.SDL_WM_SetCaption("LuaSDL Mixer Demo", "LuaSDL Mixer Demo")

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
    "Mixer demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  -- functions to load clips
  local function LoadClip(name)
    local clip = SDL.Mix_LoadWAV(SDL.LuaSDL_DirApp..name)
    if not clip then
      MiniFont:Print("Loading WAV failed: "..SDL.Mix_GetError().."\n\n")
    end
    return clip
  end
  local function LoadMusic(name)
    local clip = SDL.Mix_LoadMUS(SDL.LuaSDL_DirApp..name)
    if not clip then
      MiniFont:Print("Loading music failed: "..SDL.Mix_GetError().."\n\n")
    end
    return clip
  end

  -- initialize mixer first
  if SDL.Mix_OpenAudio(22050, SDL.MIX_DEFAULT_FORMAT, 2, 4096) ~= 0 then
    MiniFont:Print("Couldn't open mixer: "..SDL.Mix_GetError().."\n")
  end

  -- load clips, audio is converted automatically
  local file1 = "Apollo_11_quip1.wav"
  local file2 = "Apollo_11_quip2.wav"
  local file3 = "Apollo_11_plaque.ogg"
  local clip1 = LoadClip(file1)
  local clip2 = LoadClip(file2)
  local music = LoadMusic(file3)
  if clip1 then
    MiniFont:Print("Clip #1 = "..file1.."\n")
  end
  if clip2 then
    MiniFont:Print("Clip #2 = "..file2.."\n")
  end
  if music then
    MiniFont:Print("Clip #3 = "..file3.."\n")
  end

  MiniFont:Print(
[[

Mixer output set at 22050Hz, MIX_DEFAULT_FORMAT, stereo.

The audio samples were ripped from the NASA video archives.
Clip 1 is the famous quote by Neil Armstrong, 11025Hz.
Clip 2 is the words of Buzz Aldrin upon stepping out, 22050Hz.
Clip 3 is the text of the plaque being read aloud, 11025Hz, OGG.

Press [1] to play clip #1 on channel 0 (loops),
      [2] to play clip #1 on channel 0, (once),
      [3] to stop audio on channel 0,
      [4] to play clip #2 on channel 1 (loops),
      [5] to play clip #2 on channel 1, (once),
      [6] to stop audio on channel 1,
      [7] to play clip #3 as music (loops)
      [8] to stop audio on music channel,
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
        SDL.Mix_PlayChannel(0, clip1, -1)
      elseif key == SDL.SDLK_2 then
        SDL.Mix_PlayChannel(0, clip1, 0)
      elseif key == SDL.SDLK_3 then
        SDL.Mix_HaltChannel(0)
      elseif key == SDL.SDLK_4 then
        SDL.Mix_PlayChannel(1, clip2, -1)
      elseif key == SDL.SDLK_5 then
        SDL.Mix_PlayChannel(1, clip2, 0)
      elseif key == SDL.SDLK_6 then
        SDL.Mix_HaltChannel(1)
      elseif key == SDL.SDLK_7 then
        SDL.Mix_PlayMusic(music, -1)
      elseif key == SDL.SDLK_8 then
        SDL.Mix_HaltMusic()
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

  -- doesn't bother with freeing stuff for now
  if spec then SDL.Mix_CloseAudio() end
end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
