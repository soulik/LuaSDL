Meteor Shower

A prototype of a 2D sprite game, written entirely in Lua, with SDL.

by Thatcher Ulrich <tu@tulrich.com>


USAGE
-----

Type "lua40lm meteor_shower.lua" to start the game.  Use the mouse to
play.  Press ESC or Q to exit.  This game relies on luaSDL; see the
luaSDL README.txt for notes about the luaSDL module.


LEGAL
-----

The content and source code of this game has been donated by me to the
Public Domain.  Do whatever you want with it.  This covers the files
meteor_shower.lua and the *.bmp files.  THIS SOFTWARE COMES WITH
ABSOLUTELY NO WARRANTY.


FUN STUFF
---------

Asteroids is one of my all-time favorite games.  I still play fairly
often via emulation.  For a long time I've wondered what it would be
like if the rocks had gravity and collision detection.  Meanwhile,
lately I've been messing around with the Lua scripting language, SWIG,
etc.  So as a test of Lua, I thought I'd prototype a variation on
Asteroids and try some of those ideas.  The result might be a better
screen-saver than a game, but it's probably good for a few yuks.

The high-concept back story is that you're piloting one of those enemy
flying saucers from Asteroids, and you've been caught in a meteor
shower.  Use the mouse to drop your saucer into realspace, and then
fly around the screen and avoid the rocks.  You get points every time
a rock breaks apart.  You get free ships at various score intervals.
There's no gun or anything; the game is pure avoidance/survival.  When
you're sick of it, press ESC or Q to quit.

For fullscreen mode, different resolutions, etc, you're welcome to
hack the source code in meteor_shower.lua .


Notes:

* I made virtually no concession to execution speed.  Everything down
to the API layer is written in Lua, which is dynamically typed and
interpreted.  So the 2d vector math does type-checking and
heap-allocates intermediate garbage values all over the place.  It'll
probably run like crap on anything slower than 1GHz.  Plus I didn't
think much about speeding up the algorithms -- it does N^2 searches
for collision detection & gravity interactions.  You'll probably see
it bog down when a lot of asteroids get spawned at once.

* Lua, and dynamically-typed languages in general, don't do as much
compile-time checking of code as e.g. C++.  This is bad because it
lets mistakes lurk for longer before they're discovered.  Lua also has
a wart (also common to many other scripting languages) in that it
implicitly creates global variables if you use a variable name without
declaring it.  This is great for very short code snippets and scripts,
but it's bad for real programs, since it's easy to create functions
that are mistakenly coupled together via globals, or misspell variable
names, etc.  There's a way to disable that behavior, and make you
declare globals explicitly, but I didn't do that in this program,
which later caused some bugs for me.

* Lua could really use a good source-level debugger.  The hooks are
all there, and there are some debuggers available, but they're not
very slick yet.  I don't think many people write big programs in Lua.
When Lua hits a run-time error or assert, it spits out a stack trace,
which usually has the necessary info, so I didn't have too much
trouble with my little program.  But there is some great latent
capability in there, a la edit-and-continue, which isn't quite
accessible without some more glue or tools or something.  (NOTE: wxLua
shows lots of promise here.)

* Lua makes a lot of things stupidly easy.  Like, a table of shared
sprites was trivial to retrofit.  Hacking on this little game was
really pleasant; the coding felt very immediate, and once I got going
I didn't have to think much about a lot of details.  The syntax in
general is very clean and straightforward, IMO.

On balance I'd have to say Lua + luaSDL made a really nice environment
for prototyping a 2D game.  I'll probably use it again to try other
game ideas.  If you're interested in Lua I'd recommend playing around
with the meteor_shower.lua source.
