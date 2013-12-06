
  LuaSDL
  (DESCRIPTION TODO)

  Copyright (c) 2007 Kein-Hong Man <khman@users.sf.net>
  The COPYRIGHT-LuaSDL file describes the conditions under which this
  software may be distributed (basically a Lua 5-style license.)

  Website: 	(TODO)
  Project page: (TODO)

--

QUICKSTART FOR THE WIN32 BINARY RELEASE
=======================================

Double-clicking on the luasdl.exe executable starts the default script,
__init__.lua. A window should appear, with some basic information.
Follow the instructions in order to try the demo game, Meteor Shower.
You can also start the game from command-line.

--

WHAT'S NEW
==========

Please look in the file CHANGES.

--

COMMENTS IN LIEU OF A PROPER README
===================================

Undergoing heavy construction at the moment, sorry for the mess.

About the original LuaSDL...
----------------------------

I have gotten permission from Thatcher Ulrich to use the name LuaSDL,
and I am aware of other SDL bindings around. Generally, my rationale is
that I want to avoid writing custom binding code as far as possible, I
also want to use SDL_image and friends, and I want to have the whole
kaboodle released using the MIT license. The SDL-related libraries are
of course still under LGPL.

For now, all you will get is a bit of a mess, but hopefully, things will
get better soon. It won't hit 1.0 until the test coverage is close to
100%, and there are a few substantial demos.

Why LuaSDL isn't like PyGame?
-----------------------------

Why isn't LuaSDL being developed more aggressively? Because I don't
think I want to spend all my time and effort making LuaSDL into a
reasonably complete, cross-platform, well-supported rapid game
programming or prototyping system. For such a project to be successful,
one must look at it as a long-term project, with a strong push from the
main developer(s) over a few years. I am not prepared to do so.

If you have the right credentials, and really, really want LuaSDL to
compete in the PyGame niche, and is willing to push LuaSDL like PyGame
aggressively, and is capable of running this for the long term, I am
willing to cede control of this project. My aim is to have a baseline
MIT-licensed binding; if LuaSDL diverges too much from that in the
future, I will keep my code as a skeleton version of LuaSDL.

Platform Information
--------------------

Everything is on MinGW/MSYS for now, but I am trying to keep the code
platform-independent. I don't plan to use Visual C or any IDE, but
contributions are welcome. For editing, I use SciTE. I run Ubuntu too,
but that will have to wait till most things are done, or if there is
outside contribution. Also, the Makefile probably shouldn't be where it
is now.

I run WinXP Home, on a system which is a good approximation of an
average desktop system of 2006. I also have Ubuntu 6.10 and Kubuntu 6.10
installed. I don't plan to upgrade to Vista, ever, unless perhaps if
threatened with bodily harm. :-) I might also test on an old laptop with
WinME installed.

Binding Status and Documentation
--------------------------------

Bindings for SDL, SDL_image, SDL_mixer, SDL_net and SDL_ttf are almost
complete. In addition, there are a number of supplementary functions and
constants. Some services have to be implemented in a fixed way, for
example, interval timers in LuaSDL can generate events only.

For the current status of the bindings, please see the sources for now.
Proper documentation will be provided later.

Development Notes
-----------------

I'm just a beginner at binding libraries to Lua, so feedback is welcome.
Until LuaSDL hits version 1.0, everything must be considered to be in
flux. As you can see in the notes below, I'm still learning how to do a
lot of things. The advantage is, I'm also inclined to write a lot of
tests in the process. If there are better ways of implementing some of
the bindings, please let me know.

I'm not obsessed about performance, I just want an easy-to-hack
platform. If you have a problem with performance, drop down to C/C++.

If you plan to work on any part of LuaSDL, please let me know
immediately if you do not wish to run the risk of duplicating work. I
compile my own Lua and tolua++, while SDL-related libraries are from the
MinGW developer's packages.

Note that no security audit has been undertaken.

Copyright and Licensing
-----------------------

If you send me any code, I assume that you agree for it to be released
under my copyright license. You can also release your contributions
using other licenses, of course, but for the purposes of LuaSDL, there
will be a single copyright message only. I will take extreme care to
preserve author attributions, but do send me notice if your name is
left out in any way.

You can send me patches in the form of a set of the files you've changed
or added. I use WinMerge to handle contributions. I will try to be
responsive, but I can't guarantee anything.

I use SVN, hopefully LuaForge will support SVN in the future so that I
can set up a public SVN repo for LuaSDL.

--

DISTRIBUTION SIZES
==================

Here is some data on zipped sizes for a LuaSDL 0.1.0 distribution (KB =
KiB) with asserts compiled in:

LuaSDL executable w/debug info + all DLLs	1146KB
LuaSDL executable stripped + all DLLs		 988KB
LuaSDL executable stripped + mandatory DLLs	 520KB

520KB sounds pretty good to me, as I hope to prevent bloat. tolua++
asserts are still compiled in. LuaSDL should be kept simple. The
mandatory DLLs are SDL.dll, SDL_image.dll, SDL_mixer.dll, SDL_net.dll,
SDL_ttf.dll. If you want it to be smaller, you will need to write a
custom SDL.pkg and rebuild the generated sources.

From version 0.3.1, there are dummy DLLs for Win32, for SDL_mixer and
SDL_ttf. With these dummy replacements, a simple LuaSDL application that
does not need SDL_mixer and SDL_ttf can be as small as 245KB, which is
the overhead of luasdl.exe, SDL.dll, SDL_image.dll, SDL_net.dll, and the
two dummy DLLs, now renamed to SDL_mixer.dll and SDL_ttf.dll.

--

Libraries used  by LuaSDL
=========================

Here is a list of libraries that made LuaSDL possible. You can find most
of the files containing license information in the docs/ directory, or
you can get further information from their official websites.

==================================================================================
Module	      Official URL					License/README
==================================================================================
LuaSDL	      http://luaforge.net/projects/luasdl/		COPYRIGHT-LuaSDL
----------------------------------------------------------------------------------
SDL	      http://www.libsdl.org/				COPYING-SDL
----------------------------------------------------------------------------------
SDL_image     http://www.libsdl.org/projects/SDL_image/		COPYING-SDL
 - JPEG	      http://www.ijg.org/				README-JPEG
 - PNG	      http://www.libpng.org/pub/png/libpng.html		LICENSE-PNG
    - zlib    http://www.gzip.org/zlib/				README-zlib
 - TIFF	      http://www.libtiff.org/				COPYRIGHT-TIFF
----------------------------------------------------------------------------------
SDL_mixer     http://www.libsdl.org/projects/SDL_mixer/		COPYING-SDL
 - Ogg Vorbis http://www.vorbis.com/				COPYING-Ogg-Vorbis
 - SMPEG      http://www.lokigames.com/development/smpeg.php3	COPYING-SMPEG
 - MikMod     http://tfn.net/~amstpi/mikmod.html		license-mikmod.txt
 - Timidity   http://www.cgs.fi/~tt/discontinued.html		README-Timidity
              http://sca.uwaterloo.ca/www.cgs.fi/tt/timidity/ (mirror)
----------------------------------------------------------------------------------
SDL_net	      http://www.libsdl.org/projects/SDL_net/		COPYING-SDL
----------------------------------------------------------------------------------
SDL_ttf	      http://www.libsdl.org/projects/SDL_ttf/		COPYING-SDL
 - FreeType   http://www.freetype.org/				FTL.TXT
----------------------------------------------------------------------------------
Lua	      http://www.lua.org/				COPYRIGHT-Lua5
tolua++	      http://www.codenix.com/~tolua/			README-tolua++
==================================================================================

    Portions of this software are Copyright (c) 2006 The FreeType
    Project (www.freetype.org).  All rights reserved.

    Portions of this software are based in part on the work of
    the Independent JPEG Group.

These are the only two of all the libraries that requires an attribution
message, please see that you remember to put such a notice somewhere,
especially for FreeType, since it is compiled into SDL_ttf, which is
always needed in a Win32 binary distribution of LuaSDL.

--

Startup Options
===============

The following are notes on how LuaSDL's startup work on Win32. The
design is preliminary, and should not be considered final until LuaSDL
hits 1.0.

LuaSDL startup takes into consideration the following scenarios that
does not involve recompilation, in order to simplify prototyping:

(a) Start luasdl.exe by itself -- loads __init__.lua residing in the
same directory as the executable file. This allows the distribution of
the LuaSDL executable and support libraries along with your script,
without needing to touch a C compiler at any time.

(b) Start a Lua script -- use command line, a short cut, a batch file,
etc. A script can be specified using a full path name, or else it will
be found relative to the current working directory.

(c) Use a standard file extension, e.g. ".luasdl". luasdl.exe is called
with a full path to the script to be run. This needs a shell setting.
Lua scripts distributed without LuaSDL can use this method.

(d) If luasdl.exe is passed a directory path, ending in a '/' or '\',
the __init__.lua file in that directory will be executed.

In order to make it easy for scripts to find data, a number of absolute
paths are passed to the LuaSDL library for use of Lua scripts:
(a) the current working directory at the start of execution
(b) the directory where luasdl.exe resides
(c) the directory where the main script was found
(d) the name of the main script that is being executed

These paths can be manipulated so that a child script can properly find
its resources. A platform-dependent directory separator is provided, but
since Win32 understands '/', I think it should be safe to use.

--

Application Directories
-----------------------

LuaSDL provides a bunch of constants that describes the locations where
an application can place data. For convenience, a minimum Win32 model is
used. Code for the same in Unix has not been written.

SDL.LuaSDL_DirCfg is a table which contains the following paths (which
do not have trailing directory separators on Win32, but it would be
prudent to check for them, though):

    PERSONAL		per-user, usually the "My Documents" directory
    APPDATA		per-user, part of a profile that can roam
    LOCAL_APPDATA	per-user, machine-dependent (e.g. screen size)
    COMMON_APPDATA	common for all users

For Unix, PERSONAL would be "~" or "/home/<user>", APPDATA and
LOCAL_APPDATA are also the same, but the application's stuff should be
in a dot-prefixed directory, and COMMON_APPDATA should probably be in
"/etc".

For Win9x (I tested on WinME), APPDATA and LOCAL_APPDATA is the same, so
your files should not have names that may clash. The recommended Win32
API call is used to get these paths; they may not be the same as the
equivalents defined in environment variables. Currently, I am not using
UCS-2 calls, a patch that is not too invasive is welcome. Still, I think
that non-ASCII file names and path names should be avoided, period.

The usual procedure for storing application data, I suppose, is to
create a subdirectory in APPDATA (or equivalent), and place your
configuration data in that location. In Unix, dot-prefixed directory
names are common, but in Win32, it is probably better to use standard
names with no prefix dots.

For configuration and file management, LuaSDL provides a minimum set of
directory handling functions in the SDL module: LuaSDL_lsdir,
LuaSDL_chdir, LuaSDL_mkdir and LuaSDL_rmdir.

--

Memory Management
=================

For object (or struct) creation and deletion, names of calls have been
standardized. Say, for SDL_Rect, the calls are:

	SDL.SDL_Rect_new() returns obj
	* C-style object creation (needs explicit deletion)

	SDL.SDL_Rect_delete(obj)
	* C-style object deletion

	SDL.SDL_Rect_local() returns obj
	* Lua-managed object (garbaged collected if there are
	  no more references to object)

If memory management debugging is needed, you can wrap these functions
within a Lua function that tracks objects.

For some structures, you never need to actually build them, for example,
SDL_Surface. They are returned in SDL API calls and SDL may have special
API calls to delete these structures.

For creating general blocks of memory, you can use explicit memory
management with SDL_malloc and SDL_free. For Lua-managed memory objects,
LuaSDL provides SDL_malloc_local. SDL_malloc_local can create a zeroed
memory block, or you can supply a string in order to turn it into a
memory block. In order to track the object and for access, the block is
a "Uint8[]" data type by default (the tolua++ mechanism does not work
with a pure light usertype).

So for a "Uint8[]" memory block, this means that you can index (from 0)
a variable holding the object, in order to do processing. You can also
supply another data type name, any one of the data types that have been
initialized in tolua++. "Uint16[]" and "Uint32[]" have been provided;
the access functions have not been tested, though.

For converting a memory block to a string, you can use SDL_memtostr.
This is the opposite of SDL_malloc_local, and indeed, SDL_malloc_local
is aliased as SDL_strtomem for convenience.

--

Related Links
=============

There are many game programming environments that has scripting, and
some use Lua and SDL. LuaSDL is closer to PyGame, being a wrapper around
SDL libraries. You may prefer a richer development environment, if so,
do check out other projects. Many projects seems to be under GPL.

LuaSDL isn't because LuaSDL is much smaller in scope and ambition, so
releasing LuaSDL as GPL or even LGPL would be a bad idea, as there are
already so many Open Source scripting engines or game engines on the
Internet. If you need heavy duty facilities, a more complete engine is
probably more suitable.

* Allegro - famous library ("giftware", more or less MIT license)
* Freya - roughly Lua 5 + Allegro (Perl Artistic License)
* Pygame - Python, SDL and SDL_* libraries (LGPL)
* Apocalyx - 3D, incorporates everything you can think of, including
  several scripting languages (Lua, small, tcc, etc.) (GPL)

--

Tips (or, mistakes I have made)
===============================

* Remember the "SDL." prefixing all SDL calls and constants.

* Initialize SDL before loading resources. It is easy to forget this
  rule and begin initializing resources too early.

* SDL_Surface object are only created by SDL. Always remember to
  delete or free SDL_Surface objects that are no longer needed.

* Beware of booleans, use SDL.Bool() if you want to test boolean
  values instead of numbers (especially when porting.)

* To access Uint8 data in a void*, cast to "Uint8[]" and use
  array access, can read or write.

--

TODO TODO TODO
==============

* set it up on Linux (I have Ubuntu up, but lazy, lazy, lazy...)
* main library/application:
  - standard icon, to draw as SVG, export to PNG (64x64?), later
    (Win32 ico file can be edited nicely by The GIMP)
  - move test programs to new location
  - standard Lua init/quit for test programs, trap and report errors
  - OpenGL functionality is low-priority, many competitors in the
    OSS market (dynamic binding, using code generated on-the-fly?)
  - minimum support for UCS-2 (e.g. in standard paths, etc.)
  - zip library (low-priority), hooking to PNG's zlib DLL
* supplemental library:
  - how to interface to vararg api calls (in stdinc, etc.)
* test suite
  - exercise memory management, try to break LuaSDL
  - incremental testing of packages
  - exercise function calls, etc.
* demo suite
  - call demos using protected call, stack traceback if demo borks
  - proper demo selector? (using cursor keys)
  - look at meteor shower collision slowdown
  - more demos
* tolua++ (based on tolua++ 1.0.92, got workarounds)
  - types like Uint8* may be handled incorrectly
  - types with double pointer (**) may be handled incorrectly

--

khman@users.sf.net 20070730
KL, MY
