------------------------------------------------------------------------
--
-- audio_demo.lua
-- Demonstrates playing of WAV samples.
--
-- This file is part of LuaSDL.
--
-- PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
--
------------------------------------------------------------------------

------------------------------------------------------------------------
-- NOTE: memory deallocation is haphazard
------------------------------------------------------------------------

-- local ref to SDL library
local SDL = SDL

-- test initialization of SDL
if SDL.SDL_Init(SDL.SDL_INIT_EVERYTHING) < 0 then
  error("Couldn't initialize SDL: "..SDL.SDL_GetError().."\n")
  os.exit(1)
end

SDL.SDL_WM_SetCaption("LuaSDL Audio Demo", "LuaSDL Audio Demo")

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
    "Audio demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  -- function to load clip
  local function LoadClip(name)
    local spec = SDL.SDL_AudioSpec_local()
    local cliplen, clip = 0
    spec, clip, cliplen = SDL.SDL_LoadWAV(SDL.LuaSDL_DirApp..name, spec, clip, cliplen)
    if not spec then
      MiniFont:Print("Loading WAV failed: "..SDL.SDL_GetError().."\n\n")
      return
    end
    return spec, clip, cliplen
  end

  -- load clips
  local file1 = "Apollo_11_landing.wav"
  local file2 = "Apollo_11_quip1.wav"
  local file3 = "Apollo_11_quip2.wav"
  local spec1, clip1, clip1len = LoadClip(file1)
  if spec1 then
    MiniFont:Print("Clip #1 = "..file1.."\n")
  end
  local spec2, clip2, clip2len = LoadClip(file2)
  if spec2 then
    MiniFont:Print("Clip #2 = "..file2.."\n")
  end
  local spec3, clip3, clip3len = LoadClip(file3)
  if spec3 then
    MiniFont:Print("Clip #3 = "..file3.."\n")
  end

  -- WARNING here we use spec1, note that this gives problems if clip are
  -- on different WAV formats, assume clip 2 has the same sample rate
  local spec = spec1 or spec2

  -- coded to ignore audio operations if files are missing
  if spec then
    spec.callback = SDL.LuaSDL_AudioCallback
    if SDL.SDL_OpenAudio(spec) < 0 then
      MiniFont:Print("Couldn't open audio: "..SDL.SDL_GetError().."\n")
      if clip1 then SDL.SDL_FreeWAV(clip1) clip1 = nil end
      if clip2 then SDL.SDL_FreeWAV(clip2) clip2 = nil end
      spec = nil
    end
  end
  if spec then
    SDL.SDL_PauseAudio(0)       -- start audio
  else
    MiniFont:Print("Cannot operate audio without clips!\n")
  end

  -- sample rate conversion test
  -- note that SDL_audio probably does not support non-powers-of-two
  -- sample rate conversion at the moment
  local clip4, clip4len
  if spec and spec3 then
    local cvt = SDL.SDL_AudioCVT_local()
    -- build converter struct
    local result = SDL.SDL_BuildAudioCVT(cvt,
      spec3.format, spec3.channels, spec3.freq,
      spec.format, spec.channels, spec.freq)
    -- conversion is needed
    if result == 1 then
      -- create buffer, put data in
      clip4 = SDL.SDL_malloc(clip3len * cvt.len_mult)
      SDL.SDL_memcpy(clip4, clip3, clip3len)
      cvt.buf = clip4
      cvt.len = clip3len
      -- finally, perform the conversion
      if SDL.SDL_ConvertAudio(cvt) < 0 then
        clip4 = nil
      else
        clip4len = cvt.len * cvt.len_ratio
      end
    end
  end

  MiniFont:Print(
[[

The audio samples were ripped from the NASA video archives.
Clip 1 is about 35 seconds of the landing sequence, at 11025Hz.
Clip 2 is the famous quote by Neil Armstrong, 11025Hz.
Clip 3 is the words of Buzz Aldrin upon stepping out, 22050Hz.

Press [1] to play clip #1 on channel 1 continuously,
      [2] to play clip #1 on channel 1, once only,
      [3] to stop audio on channel 1,
      [4] to play clip #2 on channel 2 continuously,
      [5] to play clip #2 on channel 2, once only,
      [6] to stop audio on channel 2,
      [7] to play clip #3 on channel 1, unconverted, once
      [8] to play clip #3 on channel 2, converted, once
      [9] to stop audio on channels 1 and 2,
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
        if clip1 then SDL.LuaSDL_AudioCh1(clip1, clip1len, 1) end
      elseif key == SDL.SDLK_2 then
        if clip1 then SDL.LuaSDL_AudioCh1(clip1, clip1len) end
      elseif key == SDL.SDLK_3 then
        SDL.LuaSDL_AudioCh1(clip1, 0)
      elseif key == SDL.SDLK_4 then
        if clip2 then SDL.LuaSDL_AudioCh2(clip2, clip2len, 1) end
      elseif key == SDL.SDLK_5 then
        if clip2 then SDL.LuaSDL_AudioCh2(clip2, clip2len) end
      elseif key == SDL.SDLK_6 then
        SDL.LuaSDL_AudioCh2(clip2, 0)
      elseif key == SDL.SDLK_7 then
        if clip3 then SDL.LuaSDL_AudioCh1(clip3, clip3len) end
      elseif key == SDL.SDLK_8 then
        if clip4 then SDL.LuaSDL_AudioCh2(clip4, clip4len) end
      elseif key == SDL.SDLK_9 then
        SDL.LuaSDL_AudioCh1(clip1, 0)   -- any zero length will do
        SDL.LuaSDL_AudioCh2(clip2, 0)
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

  -- clear up memory
  if spec then SDL.SDL_CloseAudio() end
  if clip1 then SDL.SDL_FreeWAV(clip1) end
  if clip2 then SDL.SDL_FreeWAV(clip2) end
  if clip3 then SDL.SDL_FreeWAV(clip3) end
  if clip4 then SDL.SDL_FreeWAV(clip4) end
end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
