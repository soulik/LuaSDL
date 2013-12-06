------------------------------------------------------------------------
--
-- videoinfo.lua
-- Displays default video information data.
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

SDL.SDL_WM_SetCaption("LuaSDL videoinfo", "LuaSDL videoinfo")

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

  -- grab some info for later display
  local info = SDL.SDL_GetVideoInfo()
  local vfmt = info.vfmt

  local flags = SDL.Or(SDL.SDL_FULLSCREEN, SDL.SDL_HWSURFACE)
  local result, listmodes = SDL.SDL_ListModes(nil, flags)
  if type(result) == "number" then
    if result == 0 then
      listmodes = "No dimensions available"
    elseif result == -1 then
      listmodes= "No dimensions restrictions"
    else
      listmodes = "Unknown return value "..result
    end
  else
    local i = 0
    listmodes = "Hardware modes of width >= 640 are\n\n"
    while true do
      local sz = result[i]
      if not sz then break end
      if sz.w >= 640 then
        listmodes = listmodes..sz.w .." x ".. sz.h.."\n"
      end
      i = i + 1
    end
  end

  MiniFont:Print(
    "Videoinfo running on ", SDL.LuaSDL_Version, "\n\n",
[[
Press [1] to display SDL_VideoInfo struct info,
      [2] to display SDL_PixelFormat struct info,
      [3] to display some SDL_ListModes results,
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
        MiniFont:SetWindow(10, 122, 550, 344)
        MiniFont:Clear()
        MiniFont:Print(
          "info.hw_available = "..info.hw_available.."\n",
          "info.wm_available = "..info.wm_available.."\n",
          "info.UnusedBits1 = "..info.UnusedBits1.."\n",
          "info.UnusedBits2 = "..info.UnusedBits2.."\n",
          "info.blit_hw = "..info.blit_hw.."\n",
          "info.blit_hw_CC = "..info.blit_hw_CC.."\n",
          "info.blit_hw_A = "..info.blit_hw_A.."\n",
          "info.blit_sw = "..info.blit_sw.."\n",
          "info.blit_sw_CC = "..info.blit_sw_CC.."\n",
          "info.blit_sw_A = "..info.blit_sw_A.."\n",
          "info.blit_fill = "..info.blit_fill.."\n",
          "info.UnusedBits3 = "..info.UnusedBits3.."\n",
          "info.video_mem = "..info.video_mem.."\n",
          "info.current_w = "..info.current_w.."\n",
          "info.current_h = "..info.current_h.."\n"
        )
        SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
      elseif key == SDL.SDLK_2 then
        MiniFont:SetWindow(10, 122, 550, 344)
        MiniFont:Clear()
        MiniFont:Print(
          "vfmt.BitsPerPixel = "..vfmt.BitsPerPixel.."\n",
          "vfmt.BytesPerPixel = "..vfmt.BytesPerPixel.."\n",
          "vfmt.Rloss = "..vfmt.Rloss.."\n",
          "vfmt.Gloss = "..vfmt.Gloss.."\n",
          "vfmt.Bloss = "..vfmt.Bloss.."\n",
          "vfmt.Aloss = "..vfmt.Aloss.."\n",
          "vfmt.Rshift = "..vfmt.Rshift.."\n",
          "vfmt.Gshift = "..vfmt.Gshift.."\n",
          "vfmt.Bshift = "..vfmt.Bshift.."\n",
          "vfmt.Ashift = "..vfmt.Ashift.."\n",
          "vfmt.Rmask = "..vfmt.Rmask.."\n",
          "vfmt.Gmask = "..vfmt.Gmask.."\n",
          "vfmt.Bmask = "..vfmt.Bmask.."\n",
          "vfmt.Amask = "..vfmt.Amask.."\n",
          "vfmt.colorkey = "..vfmt.colorkey.."\n",
          "vfmt.alpha = "..vfmt.alpha.."\n"
        )
        SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
      elseif key == SDL.SDLK_3 then
        MiniFont:SetWindow(10, 122, 550, 344)
        MiniFont:Clear()
        MiniFont:Print(listmodes)
        SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end
end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
