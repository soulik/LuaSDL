------------------------------------------------------------------------
--
-- image_demo.lua
-- Demonstrates loading and display of different types of image files.
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

SDL.SDL_WM_SetCaption("LuaSDL Image Demo", "LuaSDL Image Demo")

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
    "LuaSDL Image Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  -- files to cycle over
  local files = {
    "tongue-4b-rle.bmp",
    "tongue-8b-rle.bmp",
    "tongue-24b.bmp",
    "tongue.gif",
    "tongue.jpg",
    "tongue.pcx",
    "tongue.png",
    "tongue.tga",
    "tongue.tif",
    "tongue.xpm",
    "tongue-ascii.ppm",
    "tongue-raw.ppm",
  }
  local pos = #files

  -- return type of image
  local function FileType(rwop)
    local typ = "(unknown)"
    if SDL.Bool(SDL.IMG_isBMP(rwop)) then
      typ = "BMP"
    elseif SDL.Bool(SDL.IMG_isGIF(rwop)) then
      typ = "GIF"
    elseif SDL.Bool(SDL.IMG_isJPG(rwop)) then
      typ = "JPEG"
    elseif SDL.Bool(SDL.IMG_isLBM(rwop)) then
      typ = "LBM"
    elseif SDL.Bool(SDL.IMG_isPCX(rwop)) then
      typ = "PCX"
    elseif SDL.Bool(SDL.IMG_isPNG(rwop)) then
      typ = "PNG"
    elseif SDL.Bool(SDL.IMG_isPNM(rwop)) then
      typ = "PNM"
    elseif SDL.Bool(SDL.IMG_isTIF(rwop)) then
      typ = "TIFF"
    elseif SDL.Bool(SDL.IMG_isXCF(rwop)) then
      typ = "XCF"
    elseif SDL.Bool(SDL.IMG_isXPM(rwop)) then
      typ = "XPM"
    elseif SDL.Bool(SDL.IMG_isXV(rwop)) then
      typ = "XV"
    end
    return typ
  end

  local function ShowStuff(dest, reverse)
    if reverse then
      pos = pos - 1
      if pos <= 0 then pos = #files end
    else
      pos = pos + 1
      if pos > #files then pos = 1 end
    end
    local fname = files[pos]
    local rwop = SDL.SDL_RWFromFile(SDL.LuaSDL_DirApp..fname, "rb")
    MiniFont:SetWindow(10, 58, 550, 440)
    MiniFont:Clear()
    if not rwop then
      MiniFont:Print("Error: failed to build rwop for "..fname.."\n")
    else
      MiniFont:Print("Image filename:   "..fname.."\n"..
                     "Type detected as: "..FileType(rwop).."\n")
      local img = SDL.IMG_Load_RW(rwop, 1)
      if not img then
        MiniFont:Print("\nError: IMG_Load_RW failed to load image\n")
      else
        local rect = SDL.SDL_Rect_local()
        rect.x, rect.y = 20, 240
        rect.w, rect.h = 64, 64
        SDL.SDL_BlitSurface(img, nil, dest, rect)
      end
      SDL.SDL_FreeSurface(img)
    end
    MiniFont:Print(
[[

Press [Space] to cycle forward through images,
      [Backspace] to cycle backwards through images,
      [Escape] to exit...
]]
    )
    SDL.SDL_UpdateRect(dest, 0, 0, 0, 0)
  end

  -- display screen and event loop
  ShowStuff(screen)
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
        ShowStuff(screen)
      elseif key == SDL.SDLK_BACKSPACE then
        ShowStuff(screen, true)
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
