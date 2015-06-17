#!/usr/bin/lua5.1

--======================================================================
--
-- meteor_shower.lua
-- by Thatcher Ulrich <tu@tulrich.com> November 2001
--
-- This source code has been donated to the Public Domain. Do whatever
-- you want with it. Sample SDL game written in Lua.
--
-- This file is part of LuaSDL.
--
-- Modified for Lua 5.1/LuaSDL by Kein-Hong Man <khman@users.sf.net> 2007
-- The changes are hereby donated into PUBLIC DOMAIN.
--
--======================================================================
-- NOTES:
-- * data files must be in the same directory as the script (using the
--   absolute path SDL.LuaSDL_DirApp)
--======================================================================

require 'LuaSDL'
local table = table     -- local references
local math = math
local tonumber = tonumber

local SDL = SDL
if not SDL or not SDL.LuaSDL_Version then       -- simple LuaSDL check
  error("LuaSDL library not present")
end

-- reliably get a resource by using LuaSDL's absolute path info
local function get_path(file_path)
  return SDL.LuaSDL_DirApp..file_path
end

------------------------------------------------------------------------
-- sprite handling
------------------------------------------------------------------------

-- Keep a table of previously-loaded sprites, to maximize sharing.
local sprite_cache = {}

-- Sprite constructor. Pass in a bitmap filename. Returns an SDL_Surface
-- which is ready to be blitted.
local function sprite(file)
  -- Quick lookup in cache
  if sprite_cache[file] then
    return sprite_cache[file]
  end
  -- Load the sprite image
  local s = SDL.SDL_LoadBMP(file)
  if not s then
    print("Couldn't load "..file..": "..SDL.SDL_GetError())
    return nil
  end
  -- Set transparent color to black (?)
  SDL.SDL_SetColorKey(s, SDL.Or(SDL.SDL_SRCCOLORKEY, SDL.SDL_RLEACCEL), 0)
  -- Convert sprite to video format, cache it
  local temp = SDL.SDL_DisplayFormat(s)
  SDL.SDL_FreeSurface(s)
  if not temp then
    print("Couldn't convert background: "..SDL.SDL_GetError())
    return nil
  end
  s = temp
  sprite_cache[file] = s
  return s
end

-- sprite blitting function
local function show_sprite(screen, sprite, x, y)
  local r = SDL.SDL_Rect_local()
  r.x, r.y = x - sprite.w / 2, y - sprite.h / 2
  r.w, r.h = sprite.w, sprite.h
  SDL.SDL_BlitSurface(sprite, nil, screen, r)
end

------------------------------------------------------------------------
-- vec2 type
------------------------------------------------------------------------

-- vec2 constructor
local function vec2(t)
  local v = {}
  if type(t) == 'table' or getmetatable(t) == vec2_mt then
    v.x = tonumber(t[1]) or tonumber(t.x) or 0
    v.y = tonumber(t[2]) or tonumber(t.y) or 0
  else
    v.x, v.y = 0, 0
  end
  setmetatable(v, vec2_mt)
  v.normalize = vec2_normalize
  return v
end

vec2_mt = {
  __add = function(a, b) return vec2{ a.x + b.x, a.y + b.y } end,
  __sub = function(a, b) return vec2{ a.x - b.x, a.y - b.y } end,
  __mul = function(a, b)
            if type(a) == 'number' then
              return vec2{ a * b.x, a * b.y }
            elseif type(b) == 'number' then
              return vec2{ a.x * b, a.y * b }
            else -- dot product
              return (a.x * b.x) + (a.y * b.y)
            end
          end,
  __unm = function(a) return vec2{ -a.x, -a.y } end,
}

-- Normalizes a. If a has 0 or near-zero length, sets a to an arbitrary
-- unit vector (go ahead and sue me!).
function vec2_normalize(a)
  local d2 = a * a
  if d2 < 0.000001 then
    -- infinitesimal vector.  Return arbitrary unit vector!
    a.x, a.y = 1, 0
  else
    -- divide by the length to get a unit vector
    local length = math.sqrt(d2)
    a.x, a.y = a.x / length, a.y / length
  end
end

--======================================================================
-- game event handling
--======================================================================

local gamestate = {
  event_buffer = SDL.SDL_Event_local(),
  last_update_ticks = 0,
  begin_time = 0,
  elapsed_ticks = 0,
  frames = 0,
  update_period = 33,   -- interval between calls to update_tick(), in ms
  active = 1,
  screen = nil,
  background = nil,
  new_actors = {},
  actors = {},
  add_actor = function(self, a)
    table.insert(self.new_actors, assert(a))
  end,
}

-- Called by main loop when it detects an SDL event.
local function handle_event(event)
  if event.type == SDL.SDL_KEYDOWN then
    local sym = event.key.keysym.sym
    if sym == SDL.SDLK_q or sym == SDL.SDLK_ESCAPE then
      gamestate.active = nil
    elseif sym == SDL.SDLK_s then
      -- take a screenshot...
      SDL.SDL_SaveBMP(gamestate.screen, "screenshot.bmp")
    end
  elseif event.type == SDL.SDL_QUIT then
    gamestate.active = nil
  end
end

-- Called at regular intervals, to update the game state.
local function update_tick()
  -- remove dead actors, and add in new actors
  for i = 1, #gamestate.actors do
    if gamestate.actors[i].active then
      -- add to the new list
      table.insert(gamestate.new_actors, gamestate.actors[i])
    end
  end
  gamestate.actors = gamestate.new_actors
  gamestate.new_actors = {}
  -- call the update handler for each actor
  for i = 1, #gamestate.actors do
    gamestate.actors[i]:update(gamestate)
  end
end

-- Called to render a new frame.
local function render_frame(screen, background)
  -- clear screen
  SDL.SDL_FillRect(screen, nil, background)
  -- draw the actors
  for i = 1, #gamestate.actors do
    gamestate.actors[i]:render(screen)
  end
  -- flip
  SDL.SDL_UpdateRect(screen, 0, 0, 0, 0)
end

------------------------------------------------------------------------
-- Call this to update the game state. Runs update ticks and renders
-- according to elapsed time.
------------------------------------------------------------------------

local function gameloop_iteration()

  -- consume any pending events
  while SDL.SDL_PollEvent(gamestate.event_buffer) ~= 0 do
    handle_event(gamestate.event_buffer)
  end

  -- run any necessary updates
  local time = SDL.SDL_GetTicks()
  local delta_ticks = time - gamestate.last_update_ticks
  local update_count = 0

  while delta_ticks > gamestate.update_period do
    update_tick()
    delta_ticks = delta_ticks - gamestate.update_period
    gamestate.last_update_ticks = gamestate.last_update_ticks + gamestate.update_period
    update_count = update_count + 1
    -- don't let more than 3 update ticks pile up before a render
    if update_count >= 3 then
      gamestate.last_update_ticks = time
      break
    end
  end

  -- if we did any updates, then render a frame
  if update_count > 0 then
    render_frame(gamestate.screen, gamestate.background)
    gamestate.frames = gamestate.frames + 1
  end
end

--======================================================================
-- SDL engine initialization and main function
--======================================================================

function engine_init(argv)

  -- Initialize SDL
  if SDL.SDL_Init(SDL.SDL_INIT_VIDEO) < 0 then
    print("Couldn't initialize SDL: ", SDL.SDL_GetError())
    os.exit(1)
  end

  local videoflags = SDL.Or(SDL.SDL_SWSURFACE, SDL.SDL_ANYFORMAT)
  local width, height = 800, 600
  local video_bpp = 16
  local i = 1
  while i <= #argv do
    if argv[i] == "-width" then
      i = i + 1
      width = tonumber(argv[i])
    elseif argv[i] == "-height" then
      i = i + 1
      height = tonumber(argv[i])
    elseif argv[i] == "-fullscreen" then
      videoflags = SDL.Or(videoflags, SDL.SDL_FULLSCREEN)
    elseif argv[i] == "-bpp" then
      i = i + 1
      video_bpp = tonumber(argv[i])
      videoflags = SDL.And(videoflags, SDL.Not(SDL.SDL_ANYFORMAT))
-- NOTE: incomplete, FastestFlags() missing
--  elseif argv[i] == "-fast" then
--    videoflags = FastestFlags(videoflags, width, height, video_bpp)
    elseif argv[i] == "-hw" then
      videoflags = SDL.Xor(videoflags, SDL.SDL_HWSURFACE)
    elseif argv[i] == "-flip" then
      videoflags = SDL.Xor(videoflags, SDL.SDL_DOUBLEBUF)
    elseif string.match(argv[i], "^%d+$") then
      numsprites = tonumber(argv[i])
    else
      print("Usage: main_program [-bpp N] [-hw] [-flip] [-fast] [-fullscreen] [numsprites]\n")
      os.exit(1)
    end
    i = i + 1
  end--while

  -- Set video mode
  gamestate.screen = SDL.SDL_SetVideoMode(width, height, video_bpp, videoflags)
  if not gamestate.screen then
    print("Couldn't set ", width, "x", height, " video mode: ", SDL.SDL_GetError())
    os.exit(2)
  end

  gamestate.background = SDL.SDL_MapRGB(gamestate.screen.format, 0, 0, 0)
  SDL.SDL_ShowCursor(0)

  SDL.SDL_WM_SetCaption("Meteor Shower", "Meteor Shower") -- window title

  -- Print out information about our surfaces
  print("Screen is at ", gamestate.screen.format.BitsPerPixel, " bits per pixel\n")
  if SDL.And(gamestate.screen.flags, SDL.SDL_HWSURFACE) == SDL.SDL_HWSURFACE then
    print("Screen is in video memory")
  else
    print("Screen is in system memory")
  end
  if SDL.And(gamestate.screen.flags, SDL.SDL_DOUBLEBUF) == SDL.SDL_DOUBLEBUF then
    print("Screen has double-buffering enabled")
  end

  -- init timer
  gamestate.begin_time = SDL.SDL_GetTicks()
  gamestate.last_update_ticks = gamestate.begin_time;
end

-- Loop, blitting sprites and waiting for a keystroke
function engine_loop()
  while gamestate.active do
    gameloop_iteration()
  end
  -- Print out some timing information
  local current_time = SDL.SDL_GetTicks()
  if current_time > gamestate.begin_time then
    print((gamestate.frames * 1000) / (current_time - gamestate.begin_time), " frames per second\n")
  end
  SDL.SDL_Quit()
end

--======================================================================
-- game-specific stuff
--======================================================================

------------------------------------------------------------------------
-- actor type
------------------------------------------------------------------------

-- Update this actor. Default does linear motion according to velocity.
-- gs is the gamestate
function actor_update(self, gs)
  local dt = gamestate.update_period / 1000.0
  local pos = self.position

  -- update according to velocity & time
  local delta = self.velocity * dt
  pos = pos + delta

  -- wrap around at screen edge
  if pos.x < -self.radius and self.velocity.x <= 0 then
    pos.x = pos.x + (gs.screen.w + self.radius * 2)
  end
  if pos.x > gs.screen.w + self.radius and self.velocity.x >= 0 then
    pos.x = pos.x - (gs.screen.w + self.radius * 2)
  end
  if pos.y < -self.radius and self.velocity.y <= 0 then
    pos.y = pos.y + (gs.screen.h + self.radius * 2)
  end
  if pos.y > gs.screen.h + self.radius and self.velocity.y >= 0 then
    pos.y = pos.y - (gs.screen.h + self.radius * 2)
  end
  self.position = pos
end

-- Draw this actor. Default implementation blits the actor's sprite
-- to the screen at the actor's position.
function actor_render(self, screen)
  show_sprite(screen, self.sprite, self.position.x, self.position.y)
end

-- Actor constructor. Pass in the name of a sprite bitmap.
function actor(t)
  local a = {}
  -- copy elements of t
  for k,v in pairs(t) do a[k] = v end

  a.type = "actor"
  a.active = 1
  a.sprite = (t[1] or t.sprite and sprite(t[1] or t.sprite)) or nil
  a.position = vec2(t.position)
  a.velocity = vec2(t.velocity)
  a.radius = a.radius or (a.sprite and a.sprite.w / 2) or 0
  a.update = actor_update
  a.render = actor_render
  return a
end

------------------------------------------------------------------------
-- particle type
------------------------------------------------------------------------

-- Update this particle. Do linear motion, and expire after a while.
-- gs is the gamestate
function particle_update(self, gs)
  local dt = gamestate.update_period / 1000.0

  -- update according to velocity & time
  local delta = self.velocity * dt
  self.position = self.position + delta

  self.countdown = self.countdown - gamestate.update_period
  if self.countdown <= 0 then
    -- kill ourself
    self.active = nil
  end
end

-- Draw this actor. Default implementation blits the actor's sprite
-- to the screen at the actor's position.
function particle_render(self, screen)
  show_sprite(screen, self.sprite, self.position.x, self.position.y)
end

-- Shared particle sprite.
particle_sprite = nil

-- Particle constructor.
local function particle(t)
  -- start with actor defaults.
  local a = actor(t)

  if not particle_sprite then
    particle_sprite = sprite(get_path("particle.bmp"))
  end

  a.sprite = particle_sprite
  a.countdown = a.countdown or 500

  -- attach particle handlers
  a.update = particle_update
  a.render = particle_render
  return a
end

-- Make a spray of count particles at the given location. The given
-- velocity will be applied to all particles. The spray_speed determines
-- the average dispersion speed. average_life determines the average
-- lifetime of the particle in ms.
local function particle_spray(position, velocity, count, spray_speed, average_life)
  local random = math.random
  for i = 1, count do
    local p = particle{}

    -- need to generate a dispersion vector, of length <= 1
    -- generate random vectors until we get a good one. @@ could also try a table.
    local dir
    repeat
      dir = vec2{ random() * 2 - 1, random() * 2 - 1 }
    until dir * dir <= 1

    p.position = position
    p.velocity = velocity + dir * spray_speed
    p.countdown = (random() + random() + random()) / 3 * average_life

    gamestate:add_actor(p)
  end--for
end

------------------------------------------------------------------------
-- asteroid actor type
------------------------------------------------------------------------

local GRAVITY_CONSTANT = 100000

-- Update this asteroid. Watch for collisions with other actors.
function asteroid_update(self, gs)
  -- move ourself
  actor_update(self, gs)

  local dt = gamestate.update_period / 1000
  local accel = vec2()

  -- check for collisions against all other actors
  for i = 1, #gs.actors do
    local a = gs.actors[i]

    -- if the actor has mass and isn't the player, then compute a
    -- gravitational acceleration towards it
    if a.mass and a.type ~= 'player' then
      local r = a.position - self.position
      local d2 = r * r
      if d2 < 100 * 100 then
        local d = math.sqrt(d2)
        if d * 2 > self.radius then
          accel = accel + r * ((GRAVITY_CONSTANT * a.mass) / (d2 * d))
        end
      end
    end

    -- check for collisions, and respond
    if a and a ~= self and a.collidable then
      local disp = a.position - self.position
      local distance_squared = disp * disp
      local sum_radius_squared = (a.radius + self.radius) ^ 2
      if distance_squared < sum_radius_squared then
        -- We have a collision; call the collision handler.
        handle_collision(self, a)
      end
    end
  end

  self.velocity = self.velocity + accel * dt
end

-- table of masses for the different asteroid sizes
asteroid_masses = { 25, 50, 100 }

local ASTEROID_RESTITUTION = 0.3

-- soft speed-limit on asteroids
local SPEED_TURNOVER_THRESHOLD = 500

-- Handles a collision between two asteroids, a and b.
function handle_asteroid_collision(a, b)
  -- impulse will be along the displacement vector between the two asteroids
  local normal = b.position - a.position
  normal:normalize()

  local relative_vel = b.velocity - a.velocity
  if relative_vel * normal >= 0 then
    -- don't do collision response if asteroids are moving away from each other
    return
  end

  -- Separate the colliding asteroids by making them bounce
  -- away from each other a la billiard balls.
  local impulse_mag = (1 + ASTEROID_RESTITUTION) * (relative_vel * normal)
                      / (1 / a.mass + 1 / b.mass)
  a.velocity = a.velocity + normal * (impulse_mag / a.mass)
  b.velocity = b.velocity - normal * (impulse_mag / b.mass)

  -- split each asteroid into two pieces
  local collision_energy = 0.5 * (relative_vel * relative_vel) * (a.mass + b.mass)
  local split_dir = vec2{ normal.y, -normal.x }
  asteroid_take_damage(a, split_dir, -normal, collision_energy)
  asteroid_take_damage(b, split_dir, normal, collision_energy)

  -- spray some particles at the split point
  local avg_velocity = (a.velocity + b.velocity) * 0.5
  local avg_position = (a.position + b.position) * 0.5
  particle_spray(avg_position, avg_velocity, (a.size + b.size) * 2, 100 + (a.size + b.size) * 20, 300)
end

-- Damage the asteroid; if it's damaged enough, split the asteroid a
-- into two pieces, along the given split_direction and along the
-- given collision normal.
function asteroid_take_damage(a, split_direction, collision_normal, collision_energy)
  local split_speed = math.sqrt(2 * collision_energy / a.mass) * 0.35

  -- Asteroid takes damage; when its damage reaches 0 then it splits in two.
  a.hitpoints = a.hitpoints - collision_energy / 2000
  if a.hitpoints > 0 then
    -- collision is not violent enough to split this 'roid
    return
  end

  local new_size = a.size - 1
  if new_size < 1 then
    -- can't split the smallest asteroid -- it just disintegrates.
    a.active = nil
    particle_spray(a.position, a.velocity, 6, 100, 300)
    add_score(100)
    return
  end

  -- spawn child asteroids
  local dir = (collision_normal + split_direction) * (1 / 1.414)
  local child1 = asteroid{
    size = new_size,
    position = a.position,
    velocity = a.velocity + dir * split_speed
  }
  child1.position = child1.position + dir * child1.radius * 2
  gamestate:add_actor(child1)

  dir = (collision_normal - split_direction) * (1 / 1.414)
  local child2 = asteroid{
    size = new_size,
    position = a.position,
    velocity = a.velocity + dir * split_speed
  }
  child2.position = child2.position + dir * child2.radius * 2
  gamestate:add_actor(child2)

  -- make some particles at the split point
  particle_spray(a.position, a.velocity, 5 + a.size * 2, 100 + a.size * 20, 300)

  -- kill a
  a.active = nil
  if a.size == 2 then
    add_score(30)
  else
    add_score(10)
  end
end

asteroid_images = {
  { "ast1.bmp" },
  { "ast2.bmp" },
  { "ast3.bmp" },
}

function pick_asteroid_image(size)
  local image_table = asteroid_images[size]
  -- pick one of the asteroid images at random
  return get_path(image_table[math.random(#image_table)])
end

-- constructor
function asteroid(t)
  -- start with a regular actor
  local a = actor(t)

  a.type = "asteroid"
  a.collidable = 1
  a.size = a.size or 3  -- make sure caller defined one of the three sizes of asteroid
  a.sprite = sprite(pick_asteroid_image(a.size))
  a.radius = 0.5 * a.sprite.w
  a.mass = asteroid_masses[a.size]
  a.hitpoints = a.mass * a.mass

  -- implement a soft speed-limit on asteroids
  local speed = math.sqrt(a.velocity * a.velocity)
  if speed > SPEED_TURNOVER_THRESHOLD then
    local new_speed = SPEED_TURNOVER_THRESHOLD + math.sqrt(speed - SPEED_TURNOVER_THRESHOLD)
    a.velocity = a.velocity * (new_speed / speed)
  end

  -- attach the behavior handlers
  a.update = asteroid_update
  return a
end

------------------------------------------------------------------------
-- random asteroid spewer
------------------------------------------------------------------------

-- constructs an actor that randomly spawns a new asteroid periodically
function asteroid_spewer(t)
  a = {}
  a.active = 1
  a.type = "asteroid_spewer"
  a.collidable = nil
  a.position = vec2{ 0, 0 }
  a.velocity = vec2{ 0, 0 }
  a.sprite = nil

  a.period = t.period or t[0] or 1000   -- period, in ms, between spawning asteroids
  a.countdown = a.period

  a.render =
    function () end
  a.update =
    function (self, gs)
      self.countdown = self.countdown - gs.update_period
      if self.countdown < 0 then
        -- timer has expired; spawn an asteroid
        -- pick a random spot around the edge of the screen
        local w, h = gs.screen.w, gs.screen.h
        local edge = math.random(w * 2 + h * 2)
        local pos
        if edge < w then pos = vec2{ edge, 0 }
        elseif edge < w*2 then pos = vec2{ edge - w, h }
        elseif edge < w*2 + h then pos = vec2{ 0, edge - w*2 }
        else pos = vec2{ w, edge - (w*2 + h) }
        end

        -- aim at the middle of the screen
        local vel = vec2{ w/2, h/2 } - pos
        vel:normalize()
        vel = vel * (math.random(50) + 50)

        gs:add_actor(
          asteroid{
            size = 3,
            position = pos,
            velocity = vel
          }
        )
        -- reset the timer
        self.countdown = self.period
      end--if
    end--function
  return a
end

------------------------------------------------------------------------
-- player actor type
------------------------------------------------------------------------

-- Update this asteroid. Watch for collisions with other actors.
function player_update(self, gs)
  local dt = gamestate.update_period / 1000

  -- get the mouse position, and move the player position towards the mouse position
  local buttons, x, y = SDL.SDL_GetMouseState(0, 0)
  local mpos = vec2{ x, y }

  local delta = mpos - self.position
  local accel = delta * 50              -- move towards the mouse cursor
                - self.velocity * 10    -- damping
  self.velocity = self.velocity + accel * dt

  -- spray some particles according to the acceleration
  particle_spray(self.position, accel * -0.10, math.floor(math.sqrt(accel * accel) * 0.0015), 150, 200)

  -- move ourself
  actor_update(self, gs)

  -- check for collisions against all other actors
  for i = 1, #gs.actors do
    local a = gs.actors[i]

    -- check for collisions, and respond
    if a and a ~= self and a.collidable then
      local disp = a.position - self.position
      local distance_squared = disp * disp
      local sum_radius_squared = (a.radius + self.radius) ^ 2

      if distance_squared < sum_radius_squared then
        -- we have a collision
        -- call the collision handler.
        handle_player_collision(self, a)
      end
    end
  end--for
end

-- handles a collision between a player, a, and some other object, b
function handle_player_collision(a, b)
  -- impulse will be along the displacement vector between the two asteroids
  local normal = b.position - a.position
  normal:normalize()

  local relative_vel = b.velocity - a.velocity
  if relative_vel * normal >= 0 then
    -- don't do collision response if asteroids are moving away from each other
    return
  end

  -- separate the colliding objects by making them bounce
  -- away from each other a la billiard balls.
  local impulse_mag = (1 + ASTEROID_RESTITUTION) * (relative_vel * normal)
                      / (1 / a.mass + 1 / b.mass)
  if a.mass and a.mass > 0 then
    a.velocity = a.velocity + normal * (impulse_mag / a.mass)
  end
  if b.mass and b.mass > 0 then
    b.velocity = b.velocity - normal * (impulse_mag / b.mass)
  end

  if b.type == "asteroid" then
    -- split asteroid 'b' into two pieces
    local collision_energy = 0.5 * (relative_vel * relative_vel) * (a.mass + b.mass)
    local split_dir = vec2{ normal.y, -normal.x }
    asteroid_take_damage(b, split_dir, normal, collision_energy)
  end

  -- kill off the player
  a.active = nil
end

-- constructor
function player(t)
  -- start with a regular actor
  local a = actor(t)

  a.type = "player"
  a.collidable = 1
  a.sprite = sprite(get_path("saucer.bmp")) -- or error("can't load ....")
  a.radius = 0.5 * a.sprite.w
  a.mass = 10

  -- attach the behavior handlers
  a.update = player_update
  return a
end

------------------------------------------------------------------------
-- cursor actor type
------------------------------------------------------------------------

-- Update the cursor. Follow the mouse.
function cursor_update(self, gs)
  local buttons, x, y = SDL.SDL_GetMouseState(0, 0)
  self.position.x = x
  self.position.y = y

  if buttons ~= 0 then
    -- player has clicked
    self.active = nil
  end
end

-- constructor
function cursor(t)
  -- start with a regular actor
  local a = actor(t)

  a.type = "cursor"
  a.sprite = sprite(get_path("cursor.bmp")) -- or error("can't load ....")
  a.radius = 0.5 * a.sprite.w

  -- attach the behavior handlers
  a.update = cursor_update
  return a
end

------------------------------------------------------------------------
-- player manager actor
------------------------------------------------------------------------

local SHIPS_PER_GAME = 3
local BASE_SPEW_PERIOD = 2000

-- keep track of game functions
function player_manager_update(self, gs)

  if self.state == "pre-setup" then
    -- delay, and then enter setup mode.
    self.countdown = self.countdown - gamestate.update_period
    if self.countdown <= 0 then
      self.state = "setup"
      self.cursor.active = 1
      gamestate:add_actor(self.cursor)
    end

  elseif self.state == "setup" then
    if not self.cursor.active then
      -- player has placed her ship.  start playing.
      self.player.active = 1
      self.player.position = self.cursor.position
      gamestate:add_actor(self.player)
      -- deduct the ship that we just placed.
      self.ships = self.ships - 1
      self.state = "playing"
    end

  elseif self.state == "playing" then
    if not self.player.active then
      -- player has died.
      if self.ships <= 0 then
        -- game is over
        self.state = "pre-attract"
        self.countdown = 1000
      else
        -- set up for next ship
        self.state = "pre-setup"
        self.countdown = 1000
      end
      -- slow down the asteroid spawning
      self.asteroid_spewer.period = BASE_SPEW_PERIOD
    end

  elseif self.state == "pre-attract" then
    -- delay, and then enter attract mode
    self.countdown = self.countdown - gamestate.update_period
    if self.countdown <= 0 then
      self.state = "attract"
    end

  elseif self.state == "attract" then
    local buttons, x, y = SDL.SDL_GetMouseState(0, 0)
    if buttons > 0 then
      -- start a new game.
      self.state = "pre-setup"
      self.ships = SHIPS_PER_GAME
      self.score = 0
      self.countdown = 1000
    end

--elseif self.state == "" then

  end
end

digit_sprites = nil

function player_manager_render(self, screen)
  if self.state == "attract" then
    show_sprite(screen, self.game_over_sprite, screen.w / 2, screen.h / 2)
  else
    -- show the ships remaining
    local sprite = self.player.sprite
    local x = sprite.w
    local y = screen.h - sprite.h
    for i = 1, self.ships do
      show_sprite(screen, sprite, x, y)
      x = x + sprite.w
    end
  end

  -- show the score
  if not digit_sprites then
    digit_sprites = {}
    for i = 0, 9 do
      digit_sprites[i] = sprite(get_path("d" .. i .. ".bmp"))
    end
  end

  local x = screen.w - digit_sprites[0].w
  local y = 0 + digit_sprites[0].h
  local score = self.score
  repeat
    local digit = score % 10
    x = x - digit_sprites[digit].w
    show_sprite(screen, digit_sprites[digit], x, y)
    score = math.floor(score / 10)
  until score <= 0
end

manager = nil

-- constructor
function player_manager(t)
  local a = {}
  for k, v in pairs(t) do a[k] = v end  -- copy values from t

  a.active = 1
  a.ships = SHIPS_PER_GAME
  a.state = "setup"
  a.score = 0

  a.cursor = cursor{
  }
  gamestate:add_actor(a.cursor)

  a.player = player{
    position = { gamestate.screen.w / 2, gamestate.screen.h / 2 },
    velocity = { 0, 0 },
  }

  a.asteroid_spewer.period = BASE_SPEW_PERIOD

  a.game_over_sprite = sprite(get_path("gameover.bmp"))

  a.update = player_manager_update
  a.render = player_manager_render

  -- keep a global pointer to the player_manager, for score management.  @@ this is a bit grody.
  if not manager then
    manager = a
  end
  return a
end

free_ship_schedule = {
  -- { threshold, interval }
  { 0, 10000 },
  { 20000, 20000 },
  { 100000, 50000 },
  { 200000, 100000 }
}

-- increase the score by x
function add_score(x)
  if manager and manager.state == "playing" then
    local score0 = manager.score

    -- increment the score
    manager.score = manager.score + x

    -- award free ships at various intervals
    local threshold = 0
    local interval = 10000
    for i = 1, #free_ship_schedule do
      if score0 >= free_ship_schedule[i][1] then
        threshold = free_ship_schedule[i][1]
        interval = free_ship_schedule[i][2]
      end
    end

    local delta = math.floor((manager.score - threshold) / interval)
                  - math.floor((score0 - threshold) / interval)
    if delta > 0 then
      -- award ships
      manager.ships = manager.ships + delta
    end

    -- adjust asteroid spewing rate
    local ramp = math.exp(-manager.score / 10000) + 0.5
    manager.asteroid_spewer.period = (1 + math.sin(manager.score / 500) * 0.25) * ramp * BASE_SPEW_PERIOD
  end
end

------------------------------------------------------------------------
-- game collision handler
--
-- I'm sidestepping the double-dispatch problem by just putting
-- the game-specific collision smarts in this function.
------------------------------------------------------------------------

function handle_collision(a, b)
-- Handles a collision between actors a and b.
-- Uses the actor's "type" attributes to help decide what to do.
-- disp is the displacement vector; (b.position - a.position)
  if a.type == "asteroid" and b.type == "asteroid" then
    handle_asteroid_collision(a, b, disp)
  end
  -- @@ handle more collision cases here...
end

--======================================================================
-- initialize the game
--======================================================================

-- grab options from command-line, or insert them here
engine_init{...}
--engine_init{"-fullscreen"}

-- Generate a bunch of asteroids
for i = 1, 10 do
  gamestate:add_actor(
    asteroid{
      position = { math.random(gamestate.screen.w), math.random(gamestate.screen.h) },
      velocity = { (math.random()*2 - 1) * 100, (math.random()*2 - 1) * 100 },  -- pixels/sec
      size = math.random(3)
    }
  )
end

-- create an asteroid spewer
spewer = asteroid_spewer{}
gamestate:add_actor(spewer)

-- create a player manager
gamestate:add_actor(
  player_manager{
    asteroid_spewer = spewer
  }
)

-- run the game
engine_loop()
