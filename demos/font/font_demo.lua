------------------------------------------------------------------------
--
-- font_demo.lua
-- Demonstrates TTF font rendering and display.
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

SDL.SDL_WM_SetCaption("LuaSDL TTF Demo", "LuaSDL TTF Template")

------------------------------------------------------------------------

--
-- startup
--
local screen = SDL.SDL_SetVideoMode(640, 480, 32, 0)
if not screen then
  error("Couldn't set video mode: "..SDL.SDL_GetError().."\n")
else

  if SDL.TTF_Init() ~= 0 then
    SDL.SDL_Quit()
    error("TTF_Init: "..SDL.TTF_GetError().."\n")
  end

  -- constants for font display
  local SIZE = 32
  local TEXT = {
    "0123456789",
    "!\"#$%&'()*+,-./:;<=>?@ [\\]^_`{|}~",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyz",
  }

  -- open font files
  local Font = {}
  local FontFile = {
    "Tuffy.ttf",
    "Tuffy_Bold.ttf",
    "Tuffy_Italic.ttf",
    "Tuffy_Bold_Italic.ttf",
  }
  for i = 1, #FontFile do
    local f = SDL.TTF_OpenFont(SDL.LuaSDL_DirApp..FontFile[i], SIZE)
    if not f then
      error("TTF_OpenFont: "..SDL.TTF_GetError().."\n")
    end
    Font[i] = f
  end

  -- function to turn style information into a string
  local function FontStyle(font)
    local style = SDL.TTF_GetFontStyle(font)
    local str = ""
    if style == SDL.TTF_STYLE_NORMAL then
      str = str.." normal"
    else
      if SDL.Bool(SDL.And(style, SDL.TTF_STYLE_BOLD)) then str = str.." bold" end
      if SDL.Bool(SDL.And(style, SDL.TTF_STYLE_ITALIC)) then str = str.." italic" end
      if SDL.Bool(SDL.And(style, SDL.TTF_STYLE_UNDERLINE)) then str = str.." underline" end
    end
    return str
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
    "LuaSDL TTF Demo running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
[[
Press [Space] to cycle between fonts,
      [Escape] to exit...
]]
  )

  -- cycle through fonts in the font list
  local pos = 1
  local function SwitchFont()
    if pos == #Font then
      pos = 1
    else
      pos = pos + 1
    end
  end

  -- demonstration of font parameters and rendering
  local function ShowFont()
    local f = Font[pos]
    MiniFont:SetWindow(10, 90, 550, 440)
    MiniFont:Clear()

    -- font informations
    MiniFont:Print(
      "File: "..FontFile[pos].."  Style: "..FontStyle(f).."\n",
      "Size: "..SIZE.."  Fixed: "..SDL.TTF_FontFaceIsFixedWidth(f).."\n",
      "Height: "..SDL.TTF_FontHeight(f).."  Leading: "..SDL.TTF_FontLineSkip(f).."\n",
      "Ascent: "..SDL.TTF_FontAscent(f).."  Descent: "..SDL.TTF_FontDescent(f).."\n",
      "Family: "..SDL.TTF_FontFaceFamilyName(f).."  Style: "..SDL.TTF_FontFaceStyleName(f).."\n"
    )

    -- text colours
    local bg = SDL.SDL_Color_local()
    bg.r, bg.g, bg.b = 0x00, 0x00, 0x00
    local fg = SDL.SDL_Color_local()
    fg.r, fg.g, fg.b = 0x00, 0xFF, 0x00

    -- render and blit
    local rect = SDL.SDL_Rect_local()
    rect.x, rect.y = 10, 200
    for i = 1, #TEXT do
      local txt = SDL.TTF_RenderText_Shaded(f, TEXT[i], fg, bg)
      rect.w, rect.h = txt.w, txt.h
      SDL.SDL_BlitSurface(txt, nil, screen, rect)
      rect.y = rect.y + SDL.TTF_FontLineSkip(f)
      SDL.SDL_FreeSurface(txt)
    end

    -- show result
    SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
  end

  -- display screen and event loop
  ShowFont()
  local event = SDL.SDL_Event_local()
  while true do
    while (SDL.SDL_PollEvent(event) == 0) do
      SDL.SDL_Delay(10)
    end
    local c = event.type
    if c == SDL.SDL_KEYDOWN then
      local key = event.key.keysym.sym
      if key == SDL.SDLK_SPACE then
        SwitchFont()
        ShowFont()
        collectgarbage("collect")
      elseif key == SDL.SDLK_ESCAPE then
        break
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

  -- free fonts
  for i = 1, #Font do
    SDL.TTF_CloseFont(Font[i])
  end
  SDL.TTF_Quit()

end


------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
