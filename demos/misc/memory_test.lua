------------------------------------------------------------------------
--
-- memory_test.lua
-- Various bits of code to look at memory usage behaviour.
--
-- This file is part of LuaSDL.
--
-- PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
--
------------------------------------------------------------------------

------------------------------------------------------------------------
-- NOTE: will probably try to add alloc/dealloc tracking later
------------------------------------------------------------------------

-- local ref to SDL library
local SDL = SDL

-- test initialization of SDL
if SDL.SDL_Init(SDL.SDL_INIT_EVERYTHING) < 0 then
  error("Couldn't initialize SDL: "..SDL.SDL_GetError().."\n")
  os.exit(1)
end

SDL.SDL_WM_SetCaption("Testing Memory", "Testing Memory")

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
    "Memory tests running on ", SDL.LuaSDL_Version, "\n\n"
  )

  MiniFont:Print(
[[

Press [1] use SDL_malloc to allocate some memory,
      [2] use SDL_free to release the memory,
      [3] use SDL_malloc_local to allocate,
      [4] release memory allocated in [3],
      [5] use SDL_strtomem to allocate,
      [6] release memory allocated in [5],
      [Escape] to exit...
]]
  )

  -- use a tool like Process Explorer in Win32 to check the change
  local BLOCK_SIZE = 1 * 1024*1024

  -- basic string-memory conversion testing
-- [=[
  local S = "1234567890"
  local p = SDL.SDL_strtomem(S, "Uint8[]")
  if not p then error("Failed to create usertype") end
  for i = 1, #S do
    if string.byte(S, i) ~= p[i-1] then
      error("Memory block allocated incorrect at "..i)
    end
  end
  p = nil
  collectgarbage("collect")
--]=]

  -- malloc testing
-- [=[
  local malloc_array = {}
  local function malloc_allocate()
    local top = #malloc_array + 1
    local p = SDL.SDL_malloc(BLOCK_SIZE)
    local q = tolua.cast(p, "Uint8[]")
    -- force commitment of pages
    for i = 0, BLOCK_SIZE - 1, 1024 do q[i] = 47 end
    malloc_array[top] = p
  end
  local function malloc_release()
    local top = #malloc_array
    if top > 0 then
      local p = malloc_array[top]
      SDL.SDL_free(p)
      malloc_array[top] = nil
      p = nil
    end
    collectgarbage("collect")
  end
--]=]

  -- local malloc testing
-- [=[
  local local_malloc_array = {}
  local function local_malloc_allocate()
    local top = #local_malloc_array + 1
    local p = SDL.SDL_malloc_local(BLOCK_SIZE, "Uint8[]")
    if not p then error("Failed to create usertype in local_malloc_allocate") end
    -- force commitment of pages
    for i = 0, BLOCK_SIZE - 1, 1024 do p[i] = 47 end
    local_malloc_array[top] = p
  end
  local function local_malloc_release()
    local top = #local_malloc_array
    if top > 0 then
      local_malloc_array[top] = nil
    end
    collectgarbage("collect")
  end
--]=]

  -- memory management by converting strings
-- [=[
  local SAMPLE = string.rep("1234567890", 10000)
  local string_array = {}
  local function string_allocate()
    local top = #string_array + 1
    local p = SDL.SDL_strtomem(SAMPLE)
    if not p then error("Failed to create usertype in string_allocate") end
    string_array[top] = p
  end
  local function string_release()
    local top = #string_array
    if top > 0 then
      local p = string_array[top]
      local s = SDL.SDL_memtostr(p, #SAMPLE)
      if s ~= SAMPLE then
        error("Memory block incorrectly converted to string")
      end
      string_array[top] = nil
      p = nil
    end
    collectgarbage("collect")
  end
--]=]

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
        malloc_allocate()
      elseif key == SDL.SDLK_2 then
        malloc_release()
      elseif key == SDL.SDLK_3 then
        local_malloc_allocate()
      elseif key == SDL.SDLK_4 then
        local_malloc_release()
      elseif key == SDL.SDLK_5 then
        string_allocate()
      elseif key == SDL.SDLK_6 then
        string_release()
      end
    elseif c == SDL.SDL_QUIT then
      break
    end
  end

end

------------------------------------------------------------------------

SDL.SDL_Quit()

-- end of script
