# generated automatically by aclocal 1.11.6 -*- Autoconf -*-

# Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004,
# 2005, 2006, 2007, 2008, 2009, 2010, 2011 Free Software Foundation,
# Inc.
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

m4_ifndef([AC_AUTOCONF_VERSION],
  [m4_copy([m4_PACKAGE_VERSION], [AC_AUTOCONF_VERSION])])dnl
m4_if(m4_defn([AC_AUTOCONF_VERSION]), [2.69],,
[m4_warning([this file was generated for autoconf 2.69.
You have another version of autoconf.  It may work, but is not guaranteed to.
If you have problems, you may need to regenerate the build system entirely.
To do so, use the procedure documented by the package, typically `autoreconf'.])])

# libtool.m4 - Configure libtool for the host system. -*-Autoconf-*-
#
#   Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2003, 2004, 2005,
#                 2006, 2007, 2008, 2009, 2010, 2011 Free Software
#                 Foundation, Inc.
#   Written by Gordon Matzigkeit, 1996
#
# This file is free software; the Free Software Foundation gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.

m4_define([_LT_COPYING], [dnl
#   Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2003, 2004, 2005,
#                 2006, 2007, 2008, 2009, 2010, 2011 Free Software
#                 Foundation, Inc.
#   Written by Gordon Matzigkeit, 1996
#
#   This file is part of GNU Libtool.
#
# GNU Libtool is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# As a special exception to the GNU General Public License,
# if you distribute this file as part of a program or library that
# is built using GNU Libtool, you may include this file under the
# same distribution terms that you use for the rest of that program.
#
# GNU Libtool is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Libtool; see the file COPYING.  If not, a copy
# can be downloaded from http://www.gnu.org/licenses/gpl.html, or
# obtained by writing to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
])

# serial 57 LT_INIT


# LT_PREREQ(VERSION)
# ------------------
# Complain and exit if this libtool version is less that VERSION.
m4_defun([LT_PREREQ],
[m4_if(m4_version_compare(m4_defn([LT_PACKAGE_VERSION]), [$1]), -1,
       [m4_default([$3],
		   [m4_fatal([Libtool version $1 or higher is required],
		             63)])],
       [$2])])


# _LT_CHECK_BUILDDIR
# ------------------
# Complain if the absolute build directory name contains unusual characters
m4_defun([_LT_CHECK_BUILDDIR],
[case `pwd` in
  *\ * | *\	*)
    AC_MSG_WARN([Libtool does not cope well with whitespace in `pwd`]) ;;
esac
])


# LT_INIT([OPTIONS])
# ------------------
AC_DEFUN([LT_INIT],
[AC_PREREQ([2.58])dnl We use AC_INCLUDES_DEFAULT
AC_REQUIRE([AC_CONFIG_AUX_DIR_DEFAULT])dnl
AC_BEFORE([$0], [LT_LANG])dnl
AC_BEFORE([$0], [LT_OUTPUT])dnl
AC_BEFORE([$0], [LTDL_INIT])dnl
m4_require([_LT_CHECK_BUILDDIR])dnl

dnl Autoconf doesn't catch unexpanded LT_ macros by default:
m4_pattern_forbid([^_?LT_[A-Z_]+$])dnl
m4_pattern_allow([^(_LT_EOF|LT_DLGLOBAL|LT_DLLAZY_OR_NOW|LT_MULTI_MODULE)$])dnl
dnl aclocal doesn't pull ltoptions.m4, ltsugar.m4, or ltversion.m4
dnl unless we require an AC_DEFUNed macro:
AC_REQUIRE([LTOPTIONS_VERSION])dnl
AC_REQUIRE([LTSUGAR_VERSION])dnl
AC_REQUIRE([LTVERSION_VERSION])dnl
AC_REQUIRE([LTOBSOLETE_VERSION])dnl
m4_require([_LT_PROG_LTMAIN])dnl

_LT_SHELL_INIT([SHELL=${CONFIG_SHELL-/bin/sh}])

dnl Parse OPTIONS
_LT_SET_OPTIONS([$0], [$1])

# This can be used to rebuild libtool when needed
LIBTOOL_DEPS="$ltmain"

# Always use our own libtool.
LIBTOOL='$(SHELL) $(top_builddir)/libtool'
AC_SUBST(LIBTOOL)dnl

_LT_SETUP

# Only expand once:
m4_define([LT_INIT])
])# LT_INIT

# Old names:
AU_ALIAS([AC_PROG_LIBTOOL], [LT_INIT])
AU_ALIAS([AM_PROG_LIBTOOL], [LT_INIT])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_PROG_LIBTOOL], [])
dnl AC_DEFUN([AM_PROG_LIBTOOL], [])


# _LT_CC_BASENAME(CC)
# -------------------
# Calculate cc_basename.  Skip known compiler wrappers and cross-prefix.
m4_defun([_LT_CC_BASENAME],
[for cc_temp in $1""; do
  case $cc_temp in
    compile | *[[\\/]]compile | ccache | *[[\\/]]ccache ) ;;
    distcc | *[[\\/]]distcc | purify | *[[\\/]]purify ) ;;
    \-*) ;;
    *) break;;
  esac
done
cc_basename=`$ECHO "$cc_temp" | $SED "s%.*/%%; s%^$host_alias-%%"`
])


# _LT_FILEUTILS_DEFAULTS
# ----------------------
# It is okay to use these file commands and assume they have been set
# sensibly after `m4_require([_LT_FILEUTILS_DEFAULTS])'.
m4_defun([_LT_FILEUTILS_DEFAULTS],
[: ${CP="cp -f"}
: ${MV="mv -f"}
: ${RM="rm -f"}
])# _LT_FILEUTILS_DEFAULTS


# _LT_SETUP
# ---------
m4_defun([_LT_SETUP],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
AC_REQUIRE([_LT_PREPARE_SED_QUOTE_VARS])dnl
AC_REQUIRE([_LT_PROG_ECHO_BACKSLASH])dnl

_LT_DECL([], [PATH_SEPARATOR], [1], [The PATH separator for the build system])dnl
dnl
_LT_DECL([], [host_alias], [0], [The host system])dnl
_LT_DECL([], [host], [0])dnl
_LT_DECL([], [host_os], [0])dnl
dnl
_LT_DECL([], [build_alias], [0], [The build system])dnl
_LT_DECL([], [build], [0])dnl
_LT_DECL([], [build_os], [0])dnl
dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([LT_PATH_LD])dnl
AC_REQUIRE([LT_PATH_NM])dnl
dnl
AC_REQUIRE([AC_PROG_LN_S])dnl
test -z "$LN_S" && LN_S="ln -s"
_LT_DECL([], [LN_S], [1], [Whether we need soft or hard links])dnl
dnl
AC_REQUIRE([LT_CMD_MAX_LEN])dnl
_LT_DECL([objext], [ac_objext], [0], [Object file suffix (normally "o")])dnl
_LT_DECL([], [exeext], [0], [Executable file suffix (normally "")])dnl
dnl
m4_require([_LT_FILEUTILS_DEFAULTS])dnl
m4_require([_LT_CHECK_SHELL_FEATURES])dnl
m4_require([_LT_PATH_CONVERSION_FUNCTIONS])dnl
m4_require([_LT_CMD_RELOAD])dnl
m4_require([_LT_CHECK_MAGIC_METHOD])dnl
m4_require([_LT_CHECK_SHAREDLIB_FROM_LINKLIB])dnl
m4_require([_LT_CMD_OLD_ARCHIVE])dnl
m4_require([_LT_CMD_GLOBAL_SYMBOLS])dnl
m4_require([_LT_WITH_SYSROOT])dnl

_LT_CONFIG_LIBTOOL_INIT([
# See if we are running on zsh, and set the options which allow our
# commands through without removal of \ escapes INIT.
if test -n "\${ZSH_VERSION+set}" ; then
   setopt NO_GLOB_SUBST
fi
])
if test -n "${ZSH_VERSION+set}" ; then
   setopt NO_GLOB_SUBST
fi

_LT_CHECK_OBJDIR

m4_require([_LT_TAG_COMPILER])dnl

case $host_os in
aix3*)
  # AIX sometimes has problems with the GCC collect2 program.  For some
  # reason, if we set the COLLECT_NAMES environment variable, the problems
  # vanish in a puff of smoke.
  if test "X${COLLECT_NAMES+set}" != Xset; then
    COLLECT_NAMES=
    export COLLECT_NAMES
  fi
  ;;
esac

# Global variables:
ofile=libtool
can_build_shared=yes

# All known linkers require a `.a' archive for static linking (except MSVC,
# which needs '.lib').
libext=a

with_gnu_ld="$lt_cv_prog_gnu_ld"

old_CC="$CC"
old_CFLAGS="$CFLAGS"

# Set sane defaults for various variables
test -z "$CC" && CC=cc
test -z "$LTCC" && LTCC=$CC
test -z "$LTCFLAGS" && LTCFLAGS=$CFLAGS
test -z "$LD" && LD=ld
test -z "$ac_objext" && ac_objext=o

_LT_CC_BASENAME([$compiler])

# Only perform the check for file, if the check method requires it
test -z "$MAGIC_CMD" && MAGIC_CMD=file
case $deplibs_check_method in
file_magic*)
  if test "$file_magic_cmd" = '$MAGIC_CMD'; then
    _LT_PATH_MAGIC
  fi
  ;;
esac

# Use C for the default configuration in the libtool script
LT_SUPPORTED_TAG([CC])
_LT_LANG_C_CONFIG
_LT_LANG_DEFAULT_CONFIG
_LT_CONFIG_COMMANDS
])# _LT_SETUP


# _LT_PREPARE_SED_QUOTE_VARS
# --------------------------
# Define a few sed substitution that help us do robust quoting.
m4_defun([_LT_PREPARE_SED_QUOTE_VARS],
[# Backslashify metacharacters that are still active within
# double-quoted strings.
sed_quote_subst='s/\([["`$\\]]\)/\\\1/g'

# Same as above, but do not quote variable references.
double_quote_subst='s/\([["`\\]]\)/\\\1/g'

# Sed substitution to delay expansion of an escaped shell variable in a
# double_quote_subst'ed string.
delay_variable_subst='s/\\\\\\\\\\\$/\\\\\\$/g'

# Sed substitution to delay expansion of an escaped single quote.
delay_single_quote_subst='s/'\''/'\'\\\\\\\'\''/g'

# Sed substitution to avoid accidental globbing in evaled expressions
no_glob_subst='s/\*/\\\*/g'
])

# _LT_PROG_LTMAIN
# ---------------
# Note that this code is called both from `configure', and `config.status'
# now that we use AC_CONFIG_COMMANDS to generate libtool.  Notably,
# `config.status' has no value for ac_aux_dir unless we are using Automake,
# so we pass a copy along to make sure it has a sensible value anyway.
m4_defun([_LT_PROG_LTMAIN],
[m4_ifdef([AC_REQUIRE_AUX_FILE], [AC_REQUIRE_AUX_FILE([ltmain.sh])])dnl
_LT_CONFIG_LIBTOOL_INIT([ac_aux_dir='$ac_aux_dir'])
ltmain="$ac_aux_dir/ltmain.sh"
])# _LT_PROG_LTMAIN



# So that we can recreate a full libtool script including additional
# tags, we accumulate the chunks of code to send to AC_CONFIG_COMMANDS
# in macros and then make a single call at the end using the `libtool'
# label.


# _LT_CONFIG_LIBTOOL_INIT([INIT-COMMANDS])
# ----------------------------------------
# Register INIT-COMMANDS to be passed to AC_CONFIG_COMMANDS later.
m4_define([_LT_CONFIG_LIBTOOL_INIT],
[m4_ifval([$1],
          [m4_append([_LT_OUTPUT_LIBTOOL_INIT],
                     [$1
])])])

# Initialize.
m4_define([_LT_OUTPUT_LIBTOOL_INIT])


# _LT_CONFIG_LIBTOOL([COMMANDS])
# ------------------------------
# Register COMMANDS to be passed to AC_CONFIG_COMMANDS later.
m4_define([_LT_CONFIG_LIBTOOL],
[m4_ifval([$1],
          [m4_append([_LT_OUTPUT_LIBTOOL_COMMANDS],
                     [$1
])])])

# Initialize.
m4_define([_LT_OUTPUT_LIBTOOL_COMMANDS])


# _LT_CONFIG_SAVE_COMMANDS([COMMANDS], [INIT_COMMANDS])
# -----------------------------------------------------
m4_defun([_LT_CONFIG_SAVE_COMMANDS],
[_LT_CONFIG_LIBTOOL([$1])
_LT_CONFIG_LIBTOOL_INIT([$2])
])


# _LT_FORMAT_COMMENT([COMMENT])
# -----------------------------
# Add leading comment marks to the start of each line, and a trailing
# full-stop to the whole comment if one is not present already.
m4_define([_LT_FORMAT_COMMENT],
[m4_ifval([$1], [
m4_bpatsubst([m4_bpatsubst([$1], [^ *], [# ])],
              [['`$\]], [\\\&])]m4_bmatch([$1], [[!?.]$], [], [.])
)])





# _LT_DECL([CONFIGNAME], VARNAME, VALUE, [DESCRIPTION], [IS-TAGGED?])
# -------------------------------------------------------------------
# CONFIGNAME is the name given to the value in the libtool script.
# VARNAME is the (base) name used in the configure script.
# VALUE may be 0, 1 or 2 for a computed quote escaped value based on
# VARNAME.  Any other value will be used directly.
m4_define([_LT_DECL],
[lt_if_append_uniq([lt_decl_varnames], [$2], [, ],
    [lt_dict_add_subkey([lt_decl_dict], [$2], [libtool_name],
	[m4_ifval([$1], [$1], [$2])])
    lt_dict_add_subkey([lt_decl_dict], [$2], [value], [$3])
    m4_ifval([$4],
	[lt_dict_add_subkey([lt_decl_dict], [$2], [description], [$4])])
    lt_dict_add_subkey([lt_decl_dict], [$2],
	[tagged?], [m4_ifval([$5], [yes], [no])])])
])


# _LT_TAGDECL([CONFIGNAME], VARNAME, VALUE, [DESCRIPTION])
# --------------------------------------------------------
m4_define([_LT_TAGDECL], [_LT_DECL([$1], [$2], [$3], [$4], [yes])])


# lt_decl_tag_varnames([SEPARATOR], [VARNAME1...])
# ------------------------------------------------
m4_define([lt_decl_tag_varnames],
[_lt_decl_filter([tagged?], [yes], $@)])


# _lt_decl_filter(SUBKEY, VALUE, [SEPARATOR], [VARNAME1..])
# ---------------------------------------------------------
m4_define([_lt_decl_filter],
[m4_case([$#],
  [0], [m4_fatal([$0: too few arguments: $#])],
  [1], [m4_fatal([$0: too few arguments: $#: $1])],
  [2], [lt_dict_filter([lt_decl_dict], [$1], [$2], [], lt_decl_varnames)],
  [3], [lt_dict_filter([lt_decl_dict], [$1], [$2], [$3], lt_decl_varnames)],
  [lt_dict_filter([lt_decl_dict], $@)])[]dnl
])


# lt_decl_quote_varnames([SEPARATOR], [VARNAME1...])
# --------------------------------------------------
m4_define([lt_decl_quote_varnames],
[_lt_decl_filter([value], [1], $@)])


# lt_decl_dquote_varnames([SEPARATOR], [VARNAME1...])
# ---------------------------------------------------
m4_define([lt_decl_dquote_varnames],
[_lt_decl_filter([value], [2], $@)])


# lt_decl_varnames_tagged([SEPARATOR], [VARNAME1...])
# ---------------------------------------------------
m4_define([lt_decl_varnames_tagged],
[m4_assert([$# <= 2])dnl
_$0(m4_quote(m4_default([$1], [[, ]])),
    m4_ifval([$2], [[$2]], [m4_dquote(lt_decl_tag_varnames)]),
    m4_split(m4_normalize(m4_quote(_LT_TAGS)), [ ]))])
m4_define([_lt_decl_varnames_tagged],
[m4_ifval([$3], [lt_combine([$1], [$2], [_], $3)])])


# lt_decl_all_varnames([SEPARATOR], [VARNAME1...])
# ------------------------------------------------
m4_define([lt_decl_all_varnames],
[_$0(m4_quote(m4_default([$1], [[, ]])),
     m4_if([$2], [],
	   m4_quote(lt_decl_varnames),
	m4_quote(m4_shift($@))))[]dnl
])
m4_define([_lt_decl_all_varnames],
[lt_join($@, lt_decl_varnames_tagged([$1],
			lt_decl_tag_varnames([[, ]], m4_shift($@))))dnl
])


# _LT_CONFIG_STATUS_DECLARE([VARNAME])
# ------------------------------------
# Quote a variable value, and forward it to `config.status' so that its
# declaration there will have the same value as in `configure'.  VARNAME
# must have a single quote delimited value for this to work.
m4_define([_LT_CONFIG_STATUS_DECLARE],
[$1='`$ECHO "$][$1" | $SED "$delay_single_quote_subst"`'])


# _LT_CONFIG_STATUS_DECLARATIONS
# ------------------------------
# We delimit libtool config variables with single quotes, so when
# we write them to config.status, we have to be sure to quote all
# embedded single quotes properly.  In configure, this macro expands
# each variable declared with _LT_DECL (and _LT_TAGDECL) into:
#
#    <var>='`$ECHO "$<var>" | $SED "$delay_single_quote_subst"`'
m4_defun([_LT_CONFIG_STATUS_DECLARATIONS],
[m4_foreach([_lt_var], m4_quote(lt_decl_all_varnames),
    [m4_n([_LT_CONFIG_STATUS_DECLARE(_lt_var)])])])


# _LT_LIBTOOL_TAGS
# ----------------
# Output comment and list of tags supported by the script
m4_defun([_LT_LIBTOOL_TAGS],
[_LT_FORMAT_COMMENT([The names of the tagged configurations supported by this script])dnl
available_tags="_LT_TAGS"dnl
])


# _LT_LIBTOOL_DECLARE(VARNAME, [TAG])
# -----------------------------------
# Extract the dictionary values for VARNAME (optionally with TAG) and
# expand to a commented shell variable setting:
#
#    # Some comment about what VAR is for.
#    visible_name=$lt_internal_name
m4_define([_LT_LIBTOOL_DECLARE],
[_LT_FORMAT_COMMENT(m4_quote(lt_dict_fetch([lt_decl_dict], [$1],
					   [description])))[]dnl
m4_pushdef([_libtool_name],
    m4_quote(lt_dict_fetch([lt_decl_dict], [$1], [libtool_name])))[]dnl
m4_case(m4_quote(lt_dict_fetch([lt_decl_dict], [$1], [value])),
    [0], [_libtool_name=[$]$1],
    [1], [_libtool_name=$lt_[]$1],
    [2], [_libtool_name=$lt_[]$1],
    [_libtool_name=lt_dict_fetch([lt_decl_dict], [$1], [value])])[]dnl
m4_ifval([$2], [_$2])[]m4_popdef([_libtool_name])[]dnl
])


# _LT_LIBTOOL_CONFIG_VARS
# -----------------------
# Produce commented declarations of non-tagged libtool config variables
# suitable for insertion in the LIBTOOL CONFIG section of the `libtool'
# script.  Tagged libtool config variables (even for the LIBTOOL CONFIG
# section) are produced by _LT_LIBTOOL_TAG_VARS.
m4_defun([_LT_LIBTOOL_CONFIG_VARS],
[m4_foreach([_lt_var],
    m4_quote(_lt_decl_filter([tagged?], [no], [], lt_decl_varnames)),
    [m4_n([_LT_LIBTOOL_DECLARE(_lt_var)])])])


# _LT_LIBTOOL_TAG_VARS(TAG)
# -------------------------
m4_define([_LT_LIBTOOL_TAG_VARS],
[m4_foreach([_lt_var], m4_quote(lt_decl_tag_varnames),
    [m4_n([_LT_LIBTOOL_DECLARE(_lt_var, [$1])])])])


# _LT_TAGVAR(VARNAME, [TAGNAME])
# ------------------------------
m4_define([_LT_TAGVAR], [m4_ifval([$2], [$1_$2], [$1])])


# _LT_CONFIG_COMMANDS
# -------------------
# Send accumulated output to $CONFIG_STATUS.  Thanks to the lists of
# variables for single and double quote escaping we saved from calls
# to _LT_DECL, we can put quote escaped variables declarations
# into `config.status', and then the shell code to quote escape them in
# for loops in `config.status'.  Finally, any additional code accumulated
# from calls to _LT_CONFIG_LIBTOOL_INIT is expanded.
m4_defun([_LT_CONFIG_COMMANDS],
[AC_PROVIDE_IFELSE([LT_OUTPUT],
	dnl If the libtool generation code has been placed in $CONFIG_LT,
	dnl instead of duplicating it all over again into config.status,
	dnl then we will have config.status run $CONFIG_LT later, so it
	dnl needs to know what name is stored there:
        [AC_CONFIG_COMMANDS([libtool],
            [$SHELL $CONFIG_LT || AS_EXIT(1)], [CONFIG_LT='$CONFIG_LT'])],
    dnl If the libtool generation code is destined for config.status,
    dnl expand the accumulated commands and init code now:
    [AC_CONFIG_COMMANDS([libtool],
        [_LT_OUTPUT_LIBTOOL_COMMANDS], [_LT_OUTPUT_LIBTOOL_COMMANDS_INIT])])
])#_LT_CONFIG_COMMANDS


# Initialize.
m4_define([_LT_OUTPUT_LIBTOOL_COMMANDS_INIT],
[

# The HP-UX ksh and POSIX shell print the target directory to stdout
# if CDPATH is set.
(unset CDPATH) >/dev/null 2>&1 && unset CDPATH

sed_quote_subst='$sed_quote_subst'
double_quote_subst='$double_quote_subst'
delay_variable_subst='$delay_variable_subst'
_LT_CONFIG_STATUS_DECLARATIONS
LTCC='$LTCC'
LTCFLAGS='$LTCFLAGS'
compiler='$compiler_DEFAULT'

# A function that is used when there is no print builtin or printf.
func_fallback_echo ()
{
  eval 'cat <<_LTECHO_EOF
\$[]1
_LTECHO_EOF'
}

# Quote evaled strings.
for var in lt_decl_all_varnames([[ \
]], lt_decl_quote_varnames); do
    case \`eval \\\\\$ECHO \\\\""\\\\\$\$var"\\\\"\` in
    *[[\\\\\\\`\\"\\\$]]*)
      eval "lt_\$var=\\\\\\"\\\`\\\$ECHO \\"\\\$\$var\\" | \\\$SED \\"\\\$sed_quote_subst\\"\\\`\\\\\\""
      ;;
    *)
      eval "lt_\$var=\\\\\\"\\\$\$var\\\\\\""
      ;;
    esac
done

# Double-quote double-evaled strings.
for var in lt_decl_all_varnames([[ \
]], lt_decl_dquote_varnames); do
    case \`eval \\\\\$ECHO \\\\""\\\\\$\$var"\\\\"\` in
    *[[\\\\\\\`\\"\\\$]]*)
      eval "lt_\$var=\\\\\\"\\\`\\\$ECHO \\"\\\$\$var\\" | \\\$SED -e \\"\\\$double_quote_subst\\" -e \\"\\\$sed_quote_subst\\" -e \\"\\\$delay_variable_subst\\"\\\`\\\\\\""
      ;;
    *)
      eval "lt_\$var=\\\\\\"\\\$\$var\\\\\\""
      ;;
    esac
done

_LT_OUTPUT_LIBTOOL_INIT
])

# _LT_GENERATED_FILE_INIT(FILE, [COMMENT])
# ------------------------------------
# Generate a child script FILE with all initialization necessary to
# reuse the environment learned by the parent script, and make the
# file executable.  If COMMENT is supplied, it is inserted after the
# `#!' sequence but before initialization text begins.  After this
# macro, additional text can be appended to FILE to form the body of
# the child script.  The macro ends with non-zero status if the
# file could not be fully written (such as if the disk is full).
m4_ifdef([AS_INIT_GENERATED],
[m4_defun([_LT_GENERATED_FILE_INIT],[AS_INIT_GENERATED($@)])],
[m4_defun([_LT_GENERATED_FILE_INIT],
[m4_require([AS_PREPARE])]dnl
[m4_pushdef([AS_MESSAGE_LOG_FD])]dnl
[lt_write_fail=0
cat >$1 <<_ASEOF || lt_write_fail=1
#! $SHELL
# Generated by $as_me.
$2
SHELL=\${CONFIG_SHELL-$SHELL}
export SHELL
_ASEOF
cat >>$1 <<\_ASEOF || lt_write_fail=1
AS_SHELL_SANITIZE
_AS_PREPARE
exec AS_MESSAGE_FD>&1
_ASEOF
test $lt_write_fail = 0 && chmod +x $1[]dnl
m4_popdef([AS_MESSAGE_LOG_FD])])])# _LT_GENERATED_FILE_INIT

# LT_OUTPUT
# ---------
# This macro allows early generation of the libtool script (before
# AC_OUTPUT is called), incase it is used in configure for compilation
# tests.
AC_DEFUN([LT_OUTPUT],
[: ${CONFIG_LT=./config.lt}
AC_MSG_NOTICE([creating $CONFIG_LT])
_LT_GENERATED_FILE_INIT(["$CONFIG_LT"],
[# Run this file to recreate a libtool stub with the current configuration.])

cat >>"$CONFIG_LT" <<\_LTEOF
lt_cl_silent=false
exec AS_MESSAGE_LOG_FD>>config.log
{
  echo
  AS_BOX([Running $as_me.])
} >&AS_MESSAGE_LOG_FD

lt_cl_help="\
\`$as_me' creates a local libtool stub from the current configuration,
for use in further configure time tests before the real libtool is
generated.

Usage: $[0] [[OPTIONS]]

  -h, --help      print this help, then exit
  -V, --version   print version number, then exit
  -q, --quiet     do not print progress messages
  -d, --debug     don't remove temporary files

Report bugs to <bug-libtool@gnu.org>."

lt_cl_version="\
m4_ifset([AC_PACKAGE_NAME], [AC_PACKAGE_NAME ])config.lt[]dnl
m4_ifset([AC_PACKAGE_VERSION], [ AC_PACKAGE_VERSION])
configured by $[0], generated by m4_PACKAGE_STRING.

Copyright (C) 2011 Free Software Foundation, Inc.
This config.lt script is free software; the Free Software Foundation
gives unlimited permision to copy, distribute and modify it."

while test $[#] != 0
do
  case $[1] in
    --version | --v* | -V )
      echo "$lt_cl_version"; exit 0 ;;
    --help | --h* | -h )
      echo "$lt_cl_help"; exit 0 ;;
    --debug | --d* | -d )
      debug=: ;;
    --quiet | --q* | --silent | --s* | -q )
      lt_cl_silent=: ;;

    -*) AC_MSG_ERROR([unrecognized option: $[1]
Try \`$[0] --help' for more information.]) ;;

    *) AC_MSG_ERROR([unrecognized argument: $[1]
Try \`$[0] --help' for more information.]) ;;
  esac
  shift
done

if $lt_cl_silent; then
  exec AS_MESSAGE_FD>/dev/null
fi
_LTEOF

cat >>"$CONFIG_LT" <<_LTEOF
_LT_OUTPUT_LIBTOOL_COMMANDS_INIT
_LTEOF

cat >>"$CONFIG_LT" <<\_LTEOF
AC_MSG_NOTICE([creating $ofile])
_LT_OUTPUT_LIBTOOL_COMMANDS
AS_EXIT(0)
_LTEOF
chmod +x "$CONFIG_LT"

# configure is writing to config.log, but config.lt does its own redirection,
# appending to config.log, which fails on DOS, as config.log is still kept
# open by configure.  Here we exec the FD to /dev/null, effectively closing
# config.log, so it can be properly (re)opened and appended to by config.lt.
lt_cl_success=:
test "$silent" = yes &&
  lt_config_lt_args="$lt_config_lt_args --quiet"
exec AS_MESSAGE_LOG_FD>/dev/null
$SHELL "$CONFIG_LT" $lt_config_lt_args || lt_cl_success=false
exec AS_MESSAGE_LOG_FD>>config.log
$lt_cl_success || AS_EXIT(1)
])# LT_OUTPUT


# _LT_CONFIG(TAG)
# ---------------
# If TAG is the built-in tag, create an initial libtool script with a
# default configuration from the untagged config vars.  Otherwise add code
# to config.status for appending the configuration named by TAG from the
# matching tagged config vars.
m4_defun([_LT_CONFIG],
[m4_require([_LT_FILEUTILS_DEFAULTS])dnl
_LT_CONFIG_SAVE_COMMANDS([
  m4_define([_LT_TAG], m4_if([$1], [], [C], [$1]))dnl
  m4_if(_LT_TAG, [C], [
    # See if we are running on zsh, and set the options which allow our
    # commands through without removal of \ escapes.
    if test -n "${ZSH_VERSION+set}" ; then
      setopt NO_GLOB_SUBST
    fi

    cfgfile="${ofile}T"
    trap "$RM \"$cfgfile\"; exit 1" 1 2 15
    $RM "$cfgfile"

    cat <<_LT_EOF >> "$cfgfile"
#! $SHELL

# `$ECHO "$ofile" | sed 's%^.*/%%'` - Provide generalized library-building support services.
# Generated automatically by $as_me ($PACKAGE$TIMESTAMP) $VERSION
# Libtool was configured on host `(hostname || uname -n) 2>/dev/null | sed 1q`:
# NOTE: Changes made to this file will be lost: look at ltmain.sh.
#
_LT_COPYING
_LT_LIBTOOL_TAGS

# ### BEGIN LIBTOOL CONFIG
_LT_LIBTOOL_CONFIG_VARS
_LT_LIBTOOL_TAG_VARS
# ### END LIBTOOL CONFIG

_LT_EOF

  case $host_os in
  aix3*)
    cat <<\_LT_EOF >> "$cfgfile"
# AIX sometimes has problems with the GCC collect2 program.  For some
# reason, if we set the COLLECT_NAMES environment variable, the problems
# vanish in a puff of smoke.
if test "X${COLLECT_NAMES+set}" != Xset; then
  COLLECT_NAMES=
  export COLLECT_NAMES
fi
_LT_EOF
    ;;
  esac

  _LT_PROG_LTMAIN

  # We use sed instead of cat because bash on DJGPP gets confused if
  # if finds mixed CR/LF and LF-only lines.  Since sed operates in
  # text mode, it properly converts lines to CR/LF.  This bash problem
  # is reportedly fixed, but why not run on old versions too?
  sed '$q' "$ltmain" >> "$cfgfile" \
     || (rm -f "$cfgfile"; exit 1)

  _LT_PROG_REPLACE_SHELLFNS

   mv -f "$cfgfile" "$ofile" ||
    (rm -f "$ofile" && cp "$cfgfile" "$ofile" && rm -f "$cfgfile")
  chmod +x "$ofile"
],
[cat <<_LT_EOF >> "$ofile"

dnl Unfortunately we have to use $1 here, since _LT_TAG is not expanded
dnl in a comment (ie after a #).
# ### BEGIN LIBTOOL TAG CONFIG: $1
_LT_LIBTOOL_TAG_VARS(_LT_TAG)
# ### END LIBTOOL TAG CONFIG: $1
_LT_EOF
])dnl /m4_if
],
[m4_if([$1], [], [
    PACKAGE='$PACKAGE'
    VERSION='$VERSION'
    TIMESTAMP='$TIMESTAMP'
    RM='$RM'
    ofile='$ofile'], [])
])dnl /_LT_CONFIG_SAVE_COMMANDS
])# _LT_CONFIG


# LT_SUPPORTED_TAG(TAG)
# ---------------------
# Trace this macro to discover what tags are supported by the libtool
# --tag option, using:
#    autoconf --trace 'LT_SUPPORTED_TAG:$1'
AC_DEFUN([LT_SUPPORTED_TAG], [])


# C support is built-in for now
m4_define([_LT_LANG_C_enabled], [])
m4_define([_LT_TAGS], [])


# LT_LANG(LANG)
# -------------
# Enable libtool support for the given language if not already enabled.
AC_DEFUN([LT_LANG],
[AC_BEFORE([$0], [LT_OUTPUT])dnl
m4_case([$1],
  [C],			[_LT_LANG(C)],
  [C++],		[_LT_LANG(CXX)],
  [Go],			[_LT_LANG(GO)],
  [Java],		[_LT_LANG(GCJ)],
  [Fortran 77],		[_LT_LANG(F77)],
  [Fortran],		[_LT_LANG(FC)],
  [Windows Resource],	[_LT_LANG(RC)],
  [m4_ifdef([_LT_LANG_]$1[_CONFIG],
    [_LT_LANG($1)],
    [m4_fatal([$0: unsupported language: "$1"])])])dnl
])# LT_LANG


# _LT_LANG(LANGNAME)
# ------------------
m4_defun([_LT_LANG],
[m4_ifdef([_LT_LANG_]$1[_enabled], [],
  [LT_SUPPORTED_TAG([$1])dnl
  m4_append([_LT_TAGS], [$1 ])dnl
  m4_define([_LT_LANG_]$1[_enabled], [])dnl
  _LT_LANG_$1_CONFIG($1)])dnl
])# _LT_LANG


m4_ifndef([AC_PROG_GO], [
# NOTE: This macro has been submitted for inclusion into   #
#  GNU Autoconf as AC_PROG_GO.  When it is available in    #
#  a released version of Autoconf we should remove this    #
#  macro and use it instead.                               #
m4_defun([AC_PROG_GO],
[AC_LANG_PUSH(Go)dnl
AC_ARG_VAR([GOC],     [Go compiler command])dnl
AC_ARG_VAR([GOFLAGS], [Go compiler flags])dnl
_AC_ARG_VAR_LDFLAGS()dnl
AC_CHECK_TOOL(GOC, gccgo)
if test -z "$GOC"; then
  if test -n "$ac_tool_prefix"; then
    AC_CHECK_PROG(GOC, [${ac_tool_prefix}gccgo], [${ac_tool_prefix}gccgo])
  fi
fi
if test -z "$GOC"; then
  AC_CHECK_PROG(GOC, gccgo, gccgo, false)
fi
])#m4_defun
])#m4_ifndef


# _LT_LANG_DEFAULT_CONFIG
# -----------------------
m4_defun([_LT_LANG_DEFAULT_CONFIG],
[AC_PROVIDE_IFELSE([AC_PROG_CXX],
  [LT_LANG(CXX)],
  [m4_define([AC_PROG_CXX], defn([AC_PROG_CXX])[LT_LANG(CXX)])])

AC_PROVIDE_IFELSE([AC_PROG_F77],
  [LT_LANG(F77)],
  [m4_define([AC_PROG_F77], defn([AC_PROG_F77])[LT_LANG(F77)])])

AC_PROVIDE_IFELSE([AC_PROG_FC],
  [LT_LANG(FC)],
  [m4_define([AC_PROG_FC], defn([AC_PROG_FC])[LT_LANG(FC)])])

dnl The call to [A][M_PROG_GCJ] is quoted like that to stop aclocal
dnl pulling things in needlessly.
AC_PROVIDE_IFELSE([AC_PROG_GCJ],
  [LT_LANG(GCJ)],
  [AC_PROVIDE_IFELSE([A][M_PROG_GCJ],
    [LT_LANG(GCJ)],
    [AC_PROVIDE_IFELSE([LT_PROG_GCJ],
      [LT_LANG(GCJ)],
      [m4_ifdef([AC_PROG_GCJ],
	[m4_define([AC_PROG_GCJ], defn([AC_PROG_GCJ])[LT_LANG(GCJ)])])
       m4_ifdef([A][M_PROG_GCJ],
	[m4_define([A][M_PROG_GCJ], defn([A][M_PROG_GCJ])[LT_LANG(GCJ)])])
       m4_ifdef([LT_PROG_GCJ],
	[m4_define([LT_PROG_GCJ], defn([LT_PROG_GCJ])[LT_LANG(GCJ)])])])])])

AC_PROVIDE_IFELSE([AC_PROG_GO],
  [LT_LANG(GO)],
  [m4_define([AC_PROG_GO], defn([AC_PROG_GO])[LT_LANG(GO)])])

AC_PROVIDE_IFELSE([LT_PROG_RC],
  [LT_LANG(RC)],
  [m4_define([LT_PROG_RC], defn([LT_PROG_RC])[LT_LANG(RC)])])
])# _LT_LANG_DEFAULT_CONFIG

# Obsolete macros:
AU_DEFUN([AC_LIBTOOL_CXX], [LT_LANG(C++)])
AU_DEFUN([AC_LIBTOOL_F77], [LT_LANG(Fortran 77)])
AU_DEFUN([AC_LIBTOOL_FC], [LT_LANG(Fortran)])
AU_DEFUN([AC_LIBTOOL_GCJ], [LT_LANG(Java)])
AU_DEFUN([AC_LIBTOOL_RC], [LT_LANG(Windows Resource)])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_CXX], [])
dnl AC_DEFUN([AC_LIBTOOL_F77], [])
dnl AC_DEFUN([AC_LIBTOOL_FC], [])
dnl AC_DEFUN([AC_LIBTOOL_GCJ], [])
dnl AC_DEFUN([AC_LIBTOOL_RC], [])


# _LT_TAG_COMPILER
# ----------------
m4_defun([_LT_TAG_COMPILER],
[AC_REQUIRE([AC_PROG_CC])dnl

_LT_DECL([LTCC], [CC], [1], [A C compiler])dnl
_LT_DECL([LTCFLAGS], [CFLAGS], [1], [LTCC compiler flags])dnl
_LT_TAGDECL([CC], [compiler], [1], [A language specific compiler])dnl
_LT_TAGDECL([with_gcc], [GCC], [0], [Is the compiler the GNU compiler?])dnl

# If no C compiler was specified, use CC.
LTCC=${LTCC-"$CC"}

# If no C compiler flags were specified, use CFLAGS.
LTCFLAGS=${LTCFLAGS-"$CFLAGS"}

# Allow CC to be a program name with arguments.
compiler=$CC
])# _LT_TAG_COMPILER


# _LT_COMPILER_BOILERPLATE
# ------------------------
# Check for compiler boilerplate output or warnings with
# the simple compiler test code.
m4_defun([_LT_COMPILER_BOILERPLATE],
[m4_require([_LT_DECL_SED])dnl
ac_outfile=conftest.$ac_objext
echo "$lt_simple_compile_test_code" >conftest.$ac_ext
eval "$ac_compile" 2>&1 >/dev/null | $SED '/^$/d; /^ *+/d' >conftest.err
_lt_compiler_boilerplate=`cat conftest.err`
$RM conftest*
])# _LT_COMPILER_BOILERPLATE


# _LT_LINKER_BOILERPLATE
# ----------------------
# Check for linker boilerplate output or warnings with
# the simple link test code.
m4_defun([_LT_LINKER_BOILERPLATE],
[m4_require([_LT_DECL_SED])dnl
ac_outfile=conftest.$ac_objext
echo "$lt_simple_link_test_code" >conftest.$ac_ext
eval "$ac_link" 2>&1 >/dev/null | $SED '/^$/d; /^ *+/d' >conftest.err
_lt_linker_boilerplate=`cat conftest.err`
$RM -r conftest*
])# _LT_LINKER_BOILERPLATE

# _LT_REQUIRED_DARWIN_CHECKS
# -------------------------
m4_defun_once([_LT_REQUIRED_DARWIN_CHECKS],[
  case $host_os in
    rhapsody* | darwin*)
    AC_CHECK_TOOL([DSYMUTIL], [dsymutil], [:])
    AC_CHECK_TOOL([NMEDIT], [nmedit], [:])
    AC_CHECK_TOOL([LIPO], [lipo], [:])
    AC_CHECK_TOOL([OTOOL], [otool], [:])
    AC_CHECK_TOOL([OTOOL64], [otool64], [:])
    _LT_DECL([], [DSYMUTIL], [1],
      [Tool to manipulate archived DWARF debug symbol files on Mac OS X])
    _LT_DECL([], [NMEDIT], [1],
      [Tool to change global to local symbols on Mac OS X])
    _LT_DECL([], [LIPO], [1],
      [Tool to manipulate fat objects and archives on Mac OS X])
    _LT_DECL([], [OTOOL], [1],
      [ldd/readelf like tool for Mach-O binaries on Mac OS X])
    _LT_DECL([], [OTOOL64], [1],
      [ldd/readelf like tool for 64 bit Mach-O binaries on Mac OS X 10.4])

    AC_CACHE_CHECK([for -single_module linker flag],[lt_cv_apple_cc_single_mod],
      [lt_cv_apple_cc_single_mod=no
      if test -z "${LT_MULTI_MODULE}"; then
	# By default we will add the -single_module flag. You can override
	# by either setting the environment variable LT_MULTI_MODULE
	# non-empty at configure time, or by adding -multi_module to the
	# link flags.
	rm -rf libconftest.dylib*
	echo "int foo(void){return 1;}" > conftest.c
	echo "$LTCC $LTCFLAGS $LDFLAGS -o libconftest.dylib \
-dynamiclib -Wl,-single_module conftest.c" >&AS_MESSAGE_LOG_FD
	$LTCC $LTCFLAGS $LDFLAGS -o libconftest.dylib \
	  -dynamiclib -Wl,-single_module conftest.c 2>conftest.err
        _lt_result=$?
	# If there is a non-empty error log, and "single_module"
	# appears in it, assume the flag caused a linker warning
        if test -s conftest.err && $GREP single_module conftest.err; then
	  cat conftest.err >&AS_MESSAGE_LOG_FD
	# Otherwise, if the output was created with a 0 exit code from
	# the compiler, it worked.
	elif test -f libconftest.dylib && test $_lt_result -eq 0; then
	  lt_cv_apple_cc_single_mod=yes
	else
	  cat conftest.err >&AS_MESSAGE_LOG_FD
	fi
	rm -rf libconftest.dylib*
	rm -f conftest.*
      fi])

    AC_CACHE_CHECK([for -exported_symbols_list linker flag],
      [lt_cv_ld_exported_symbols_list],
      [lt_cv_ld_exported_symbols_list=no
      save_LDFLAGS=$LDFLAGS
      echo "_main" > conftest.sym
      LDFLAGS="$LDFLAGS -Wl,-exported_symbols_list,conftest.sym"
      AC_LINK_IFELSE([AC_LANG_PROGRAM([],[])],
	[lt_cv_ld_exported_symbols_list=yes],
	[lt_cv_ld_exported_symbols_list=no])
	LDFLAGS="$save_LDFLAGS"
    ])

    AC_CACHE_CHECK([for -force_load linker flag],[lt_cv_ld_force_load],
      [lt_cv_ld_force_load=no
      cat > conftest.c << _LT_EOF
int forced_loaded() { return 2;}
_LT_EOF
      echo "$LTCC $LTCFLAGS -c -o conftest.o conftest.c" >&AS_MESSAGE_LOG_FD
      $LTCC $LTCFLAGS -c -o conftest.o conftest.c 2>&AS_MESSAGE_LOG_FD
      echo "$AR cru libconftest.a conftest.o" >&AS_MESSAGE_LOG_FD
      $AR cru libconftest.a conftest.o 2>&AS_MESSAGE_LOG_FD
      echo "$RANLIB libconftest.a" >&AS_MESSAGE_LOG_FD
      $RANLIB libconftest.a 2>&AS_MESSAGE_LOG_FD
      cat > conftest.c << _LT_EOF
int main() { return 0;}
_LT_EOF
      echo "$LTCC $LTCFLAGS $LDFLAGS -o conftest conftest.c -Wl,-force_load,./libconftest.a" >&AS_MESSAGE_LOG_FD
      $LTCC $LTCFLAGS $LDFLAGS -o conftest conftest.c -Wl,-force_load,./libconftest.a 2>conftest.err
      _lt_result=$?
      if test -s conftest.err && $GREP force_load conftest.err; then
	cat conftest.err >&AS_MESSAGE_LOG_FD
      elif test -f conftest && test $_lt_result -eq 0 && $GREP forced_load conftest >/dev/null 2>&1 ; then
	lt_cv_ld_force_load=yes
      else
	cat conftest.err >&AS_MESSAGE_LOG_FD
      fi
        rm -f conftest.err libconftest.a conftest conftest.c
        rm -rf conftest.dSYM
    ])
    case $host_os in
    rhapsody* | darwin1.[[012]])
      _lt_dar_allow_undefined='${wl}-undefined ${wl}suppress' ;;
    darwin1.*)
      _lt_dar_allow_undefined='${wl}-flat_namespace ${wl}-undefined ${wl}suppress' ;;
    darwin*) # darwin 5.x on
      # if running on 10.5 or later, the deployment target defaults
      # to the OS version, if on x86, and 10.4, the deployment
      # target defaults to 10.4. Don't you love it?
      case ${MACOSX_DEPLOYMENT_TARGET-10.0},$host in
	10.0,*86*-darwin8*|10.0,*-darwin[[91]]*)
	  _lt_dar_allow_undefined='${wl}-undefined ${wl}dynamic_lookup' ;;
	10.[[012]]*)
	  _lt_dar_allow_undefined='${wl}-flat_namespace ${wl}-undefined ${wl}suppress' ;;
	10.*)
	  _lt_dar_allow_undefined='${wl}-undefined ${wl}dynamic_lookup' ;;
      esac
    ;;
  esac
    if test "$lt_cv_apple_cc_single_mod" = "yes"; then
      _lt_dar_single_mod='$single_module'
    fi
    if test "$lt_cv_ld_exported_symbols_list" = "yes"; then
      _lt_dar_export_syms=' ${wl}-exported_symbols_list,$output_objdir/${libname}-symbols.expsym'
    else
      _lt_dar_export_syms='~$NMEDIT -s $output_objdir/${libname}-symbols.expsym ${lib}'
    fi
    if test "$DSYMUTIL" != ":" && test "$lt_cv_ld_force_load" = "no"; then
      _lt_dsymutil='~$DSYMUTIL $lib || :'
    else
      _lt_dsymutil=
    fi
    ;;
  esac
])


# _LT_DARWIN_LINKER_FEATURES([TAG])
# ---------------------------------
# Checks for linker and compiler features on darwin
m4_defun([_LT_DARWIN_LINKER_FEATURES],
[
  m4_require([_LT_REQUIRED_DARWIN_CHECKS])
  _LT_TAGVAR(archive_cmds_need_lc, $1)=no
  _LT_TAGVAR(hardcode_direct, $1)=no
  _LT_TAGVAR(hardcode_automatic, $1)=yes
  _LT_TAGVAR(hardcode_shlibpath_var, $1)=unsupported
  if test "$lt_cv_ld_force_load" = "yes"; then
    _LT_TAGVAR(whole_archive_flag_spec, $1)='`for conv in $convenience\"\"; do test  -n \"$conv\" && new_convenience=\"$new_convenience ${wl}-force_load,$conv\"; done; func_echo_all \"$new_convenience\"`'
    m4_case([$1], [F77], [_LT_TAGVAR(compiler_needs_object, $1)=yes],
                  [FC],  [_LT_TAGVAR(compiler_needs_object, $1)=yes])
  else
    _LT_TAGVAR(whole_archive_flag_spec, $1)=''
  fi
  _LT_TAGVAR(link_all_deplibs, $1)=yes
  _LT_TAGVAR(allow_undefined_flag, $1)="$_lt_dar_allow_undefined"
  case $cc_basename in
     ifort*) _lt_dar_can_shared=yes ;;
     *) _lt_dar_can_shared=$GCC ;;
  esac
  if test "$_lt_dar_can_shared" = "yes"; then
    output_verbose_link_cmd=func_echo_all
    _LT_TAGVAR(archive_cmds, $1)="\$CC -dynamiclib \$allow_undefined_flag -o \$lib \$libobjs \$deplibs \$compiler_flags -install_name \$rpath/\$soname \$verstring $_lt_dar_single_mod${_lt_dsymutil}"
    _LT_TAGVAR(module_cmds, $1)="\$CC \$allow_undefined_flag -o \$lib -bundle \$libobjs \$deplibs \$compiler_flags${_lt_dsymutil}"
    _LT_TAGVAR(archive_expsym_cmds, $1)="sed 's,^,_,' < \$export_symbols > \$output_objdir/\${libname}-symbols.expsym~\$CC -dynamiclib \$allow_undefined_flag -o \$lib \$libobjs \$deplibs \$compiler_flags -install_name \$rpath/\$soname \$verstring ${_lt_dar_single_mod}${_lt_dar_export_syms}${_lt_dsymutil}"
    _LT_TAGVAR(module_expsym_cmds, $1)="sed -e 's,^,_,' < \$export_symbols > \$output_objdir/\${libname}-symbols.expsym~\$CC \$allow_undefined_flag -o \$lib -bundle \$libobjs \$deplibs \$compiler_flags${_lt_dar_export_syms}${_lt_dsymutil}"
    m4_if([$1], [CXX],
[   if test "$lt_cv_apple_cc_single_mod" != "yes"; then
      _LT_TAGVAR(archive_cmds, $1)="\$CC -r -keep_private_externs -nostdlib -o \${lib}-master.o \$libobjs~\$CC -dynamiclib \$allow_undefined_flag -o \$lib \${lib}-master.o \$deplibs \$compiler_flags -install_name \$rpath/\$soname \$verstring${_lt_dsymutil}"
      _LT_TAGVAR(archive_expsym_cmds, $1)="sed 's,^,_,' < \$export_symbols > \$output_objdir/\${libname}-symbols.expsym~\$CC -r -keep_private_externs -nostdlib -o \${lib}-master.o \$libobjs~\$CC -dynamiclib \$allow_undefined_flag -o \$lib \${lib}-master.o \$deplibs \$compiler_flags -install_name \$rpath/\$soname \$verstring${_lt_dar_export_syms}${_lt_dsymutil}"
    fi
],[])
  else
  _LT_TAGVAR(ld_shlibs, $1)=no
  fi
])

# _LT_SYS_MODULE_PATH_AIX([TAGNAME])
# ----------------------------------
# Links a minimal program and checks the executable
# for the system default hardcoded library path. In most cases,
# this is /usr/lib:/lib, but when the MPI compilers are used
# the location of the communication and MPI libs are included too.
# If we don't find anything, use the default library path according
# to the aix ld manual.
# Store the results from the different compilers for each TAGNAME.
# Allow to override them for all tags through lt_cv_aix_libpath.
m4_defun([_LT_SYS_MODULE_PATH_AIX],
[m4_require([_LT_DECL_SED])dnl
if test "${lt_cv_aix_libpath+set}" = set; then
  aix_libpath=$lt_cv_aix_libpath
else
  AC_CACHE_VAL([_LT_TAGVAR([lt_cv_aix_libpath_], [$1])],
  [AC_LINK_IFELSE([AC_LANG_PROGRAM],[
  lt_aix_libpath_sed='[
      /Import File Strings/,/^$/ {
	  /^0/ {
	      s/^0  *\([^ ]*\) *$/\1/
	      p
	  }
      }]'
  _LT_TAGVAR([lt_cv_aix_libpath_], [$1])=`dump -H conftest$ac_exeext 2>/dev/null | $SED -n -e "$lt_aix_libpath_sed"`
  # Check for a 64-bit object if we didn't find anything.
  if test -z "$_LT_TAGVAR([lt_cv_aix_libpath_], [$1])"; then
    _LT_TAGVAR([lt_cv_aix_libpath_], [$1])=`dump -HX64 conftest$ac_exeext 2>/dev/null | $SED -n -e "$lt_aix_libpath_sed"`
  fi],[])
  if test -z "$_LT_TAGVAR([lt_cv_aix_libpath_], [$1])"; then
    _LT_TAGVAR([lt_cv_aix_libpath_], [$1])="/usr/lib:/lib"
  fi
  ])
  aix_libpath=$_LT_TAGVAR([lt_cv_aix_libpath_], [$1])
fi
])# _LT_SYS_MODULE_PATH_AIX


# _LT_SHELL_INIT(ARG)
# -------------------
m4_define([_LT_SHELL_INIT],
[m4_divert_text([M4SH-INIT], [$1
])])# _LT_SHELL_INIT



# _LT_PROG_ECHO_BACKSLASH
# -----------------------
# Find how we can fake an echo command that does not interpret backslash.
# In particular, with Autoconf 2.60 or later we add some code to the start
# of the generated configure script which will find a shell with a builtin
# printf (which we can use as an echo command).
m4_defun([_LT_PROG_ECHO_BACKSLASH],
[ECHO='\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\'
ECHO=$ECHO$ECHO$ECHO$ECHO$ECHO
ECHO=$ECHO$ECHO$ECHO$ECHO$ECHO$ECHO

AC_MSG_CHECKING([how to print strings])
# Test print first, because it will be a builtin if present.
if test "X`( print -r -- -n ) 2>/dev/null`" = X-n && \
   test "X`print -r -- $ECHO 2>/dev/null`" = "X$ECHO"; then
  ECHO='print -r --'
elif test "X`printf %s $ECHO 2>/dev/null`" = "X$ECHO"; then
  ECHO='printf %s\n'
else
  # Use this function as a fallback that always works.
  func_fallback_echo ()
  {
    eval 'cat <<_LTECHO_EOF
$[]1
_LTECHO_EOF'
  }
  ECHO='func_fallback_echo'
fi

# func_echo_all arg...
# Invoke $ECHO with all args, space-separated.
func_echo_all ()
{
    $ECHO "$*" 
}

case "$ECHO" in
  printf*) AC_MSG_RESULT([printf]) ;;
  print*) AC_MSG_RESULT([print -r]) ;;
  *) AC_MSG_RESULT([cat]) ;;
esac

m4_ifdef([_AS_DETECT_SUGGESTED],
[_AS_DETECT_SUGGESTED([
  test -n "${ZSH_VERSION+set}${BASH_VERSION+set}" || (
    ECHO='\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\'
    ECHO=$ECHO$ECHO$ECHO$ECHO$ECHO
    ECHO=$ECHO$ECHO$ECHO$ECHO$ECHO$ECHO
    PATH=/empty FPATH=/empty; export PATH FPATH
    test "X`printf %s $ECHO`" = "X$ECHO" \
      || test "X`print -r -- $ECHO`" = "X$ECHO" )])])

_LT_DECL([], [SHELL], [1], [Shell to use when invoking shell scripts])
_LT_DECL([], [ECHO], [1], [An echo program that protects backslashes])
])# _LT_PROG_ECHO_BACKSLASH


# _LT_WITH_SYSROOT
# ----------------
AC_DEFUN([_LT_WITH_SYSROOT],
[AC_MSG_CHECKING([for sysroot])
AC_ARG_WITH([sysroot],
[  --with-sysroot[=DIR] Search for dependent libraries within DIR
                        (or the compiler's sysroot if not specified).],
[], [with_sysroot=no])

dnl lt_sysroot will always be passed unquoted.  We quote it here
dnl in case the user passed a directory name.
lt_sysroot=
case ${with_sysroot} in #(
 yes)
   if test "$GCC" = yes; then
     lt_sysroot=`$CC --print-sysroot 2>/dev/null`
   fi
   ;; #(
 /*)
   lt_sysroot=`echo "$with_sysroot" | sed -e "$sed_quote_subst"`
   ;; #(
 no|'')
   ;; #(
 *)
   AC_MSG_RESULT([${with_sysroot}])
   AC_MSG_ERROR([The sysroot must be an absolute path.])
   ;;
esac

 AC_MSG_RESULT([${lt_sysroot:-no}])
_LT_DECL([], [lt_sysroot], [0], [The root where to search for ]dnl
[dependent libraries, and in which our libraries should be installed.])])

# _LT_ENABLE_LOCK
# ---------------
m4_defun([_LT_ENABLE_LOCK],
[AC_ARG_ENABLE([libtool-lock],
  [AS_HELP_STRING([--disable-libtool-lock],
    [avoid locking (might break parallel builds)])])
test "x$enable_libtool_lock" != xno && enable_libtool_lock=yes

# Some flags need to be propagated to the compiler or linker for good
# libtool support.
case $host in
ia64-*-hpux*)
  # Find out which ABI we are using.
  echo 'int i;' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case `/usr/bin/file conftest.$ac_objext` in
      *ELF-32*)
	HPUX_IA64_MODE="32"
	;;
      *ELF-64*)
	HPUX_IA64_MODE="64"
	;;
    esac
  fi
  rm -rf conftest*
  ;;
*-*-irix6*)
  # Find out which ABI we are using.
  echo '[#]line '$LINENO' "configure"' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    if test "$lt_cv_prog_gnu_ld" = yes; then
      case `/usr/bin/file conftest.$ac_objext` in
	*32-bit*)
	  LD="${LD-ld} -melf32bsmip"
	  ;;
	*N32*)
	  LD="${LD-ld} -melf32bmipn32"
	  ;;
	*64-bit*)
	  LD="${LD-ld} -melf64bmip"
	;;
      esac
    else
      case `/usr/bin/file conftest.$ac_objext` in
	*32-bit*)
	  LD="${LD-ld} -32"
	  ;;
	*N32*)
	  LD="${LD-ld} -n32"
	  ;;
	*64-bit*)
	  LD="${LD-ld} -64"
	  ;;
      esac
    fi
  fi
  rm -rf conftest*
  ;;

x86_64-*kfreebsd*-gnu|x86_64-*linux*|ppc*-*linux*|powerpc*-*linux*| \
s390*-*linux*|s390*-*tpf*|sparc*-*linux*)
  # Find out which ABI we are using.
  echo 'int i;' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case `/usr/bin/file conftest.o` in
      *32-bit*)
	case $host in
	  x86_64-*kfreebsd*-gnu)
	    LD="${LD-ld} -m elf_i386_fbsd"
	    ;;
	  x86_64-*linux*)
	    LD="${LD-ld} -m elf_i386"
	    ;;
	  ppc64-*linux*|powerpc64-*linux*)
	    LD="${LD-ld} -m elf32ppclinux"
	    ;;
	  s390x-*linux*)
	    LD="${LD-ld} -m elf_s390"
	    ;;
	  sparc64-*linux*)
	    LD="${LD-ld} -m elf32_sparc"
	    ;;
	esac
	;;
      *64-bit*)
	case $host in
	  x86_64-*kfreebsd*-gnu)
	    LD="${LD-ld} -m elf_x86_64_fbsd"
	    ;;
	  x86_64-*linux*)
	    LD="${LD-ld} -m elf_x86_64"
	    ;;
	  ppc*-*linux*|powerpc*-*linux*)
	    LD="${LD-ld} -m elf64ppc"
	    ;;
	  s390*-*linux*|s390*-*tpf*)
	    LD="${LD-ld} -m elf64_s390"
	    ;;
	  sparc*-*linux*)
	    LD="${LD-ld} -m elf64_sparc"
	    ;;
	esac
	;;
    esac
  fi
  rm -rf conftest*
  ;;

*-*-sco3.2v5*)
  # On SCO OpenServer 5, we need -belf to get full-featured binaries.
  SAVE_CFLAGS="$CFLAGS"
  CFLAGS="$CFLAGS -belf"
  AC_CACHE_CHECK([whether the C compiler needs -belf], lt_cv_cc_needs_belf,
    [AC_LANG_PUSH(C)
     AC_LINK_IFELSE([AC_LANG_PROGRAM([[]],[[]])],[lt_cv_cc_needs_belf=yes],[lt_cv_cc_needs_belf=no])
     AC_LANG_POP])
  if test x"$lt_cv_cc_needs_belf" != x"yes"; then
    # this is probably gcc 2.8.0, egcs 1.0 or newer; no need for -belf
    CFLAGS="$SAVE_CFLAGS"
  fi
  ;;
*-*solaris*)
  # Find out which ABI we are using.
  echo 'int i;' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case `/usr/bin/file conftest.o` in
    *64-bit*)
      case $lt_cv_prog_gnu_ld in
      yes*)
        case $host in
        i?86-*-solaris*)
          LD="${LD-ld} -m elf_x86_64"
          ;;
        sparc*-*-solaris*)
          LD="${LD-ld} -m elf64_sparc"
          ;;
        esac
        # GNU ld 2.21 introduced _sol2 emulations.  Use them if available.
        if ${LD-ld} -V | grep _sol2 >/dev/null 2>&1; then
          LD="${LD-ld}_sol2"
        fi
        ;;
      *)
	if ${LD-ld} -64 -r -o conftest2.o conftest.o >/dev/null 2>&1; then
	  LD="${LD-ld} -64"
	fi
	;;
      esac
      ;;
    esac
  fi
  rm -rf conftest*
  ;;
esac

need_locks="$enable_libtool_lock"
])# _LT_ENABLE_LOCK


# _LT_PROG_AR
# -----------
m4_defun([_LT_PROG_AR],
[AC_CHECK_TOOLS(AR, [ar], false)
: ${AR=ar}
: ${AR_FLAGS=cru}
_LT_DECL([], [AR], [1], [The archiver])
_LT_DECL([], [AR_FLAGS], [1], [Flags to create an archive])

AC_CACHE_CHECK([for archiver @FILE support], [lt_cv_ar_at_file],
  [lt_cv_ar_at_file=no
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM],
     [echo conftest.$ac_objext > conftest.lst
      lt_ar_try='$AR $AR_FLAGS libconftest.a @conftest.lst >&AS_MESSAGE_LOG_FD'
      AC_TRY_EVAL([lt_ar_try])
      if test "$ac_status" -eq 0; then
	# Ensure the archiver fails upon bogus file names.
	rm -f conftest.$ac_objext libconftest.a
	AC_TRY_EVAL([lt_ar_try])
	if test "$ac_status" -ne 0; then
          lt_cv_ar_at_file=@
        fi
      fi
      rm -f conftest.* libconftest.a
     ])
  ])

if test "x$lt_cv_ar_at_file" = xno; then
  archiver_list_spec=
else
  archiver_list_spec=$lt_cv_ar_at_file
fi
_LT_DECL([], [archiver_list_spec], [1],
  [How to feed a file listing to the archiver])
])# _LT_PROG_AR


# _LT_CMD_OLD_ARCHIVE
# -------------------
m4_defun([_LT_CMD_OLD_ARCHIVE],
[_LT_PROG_AR

AC_CHECK_TOOL(STRIP, strip, :)
test -z "$STRIP" && STRIP=:
_LT_DECL([], [STRIP], [1], [A symbol stripping program])

AC_CHECK_TOOL(RANLIB, ranlib, :)
test -z "$RANLIB" && RANLIB=:
_LT_DECL([], [RANLIB], [1],
    [Commands used to install an old-style archive])

# Determine commands to create old-style static archives.
old_archive_cmds='$AR $AR_FLAGS $oldlib$oldobjs'
old_postinstall_cmds='chmod 644 $oldlib'
old_postuninstall_cmds=

if test -n "$RANLIB"; then
  case $host_os in
  openbsd*)
    old_postinstall_cmds="$old_postinstall_cmds~\$RANLIB -t \$tool_oldlib"
    ;;
  *)
    old_postinstall_cmds="$old_postinstall_cmds~\$RANLIB \$tool_oldlib"
    ;;
  esac
  old_archive_cmds="$old_archive_cmds~\$RANLIB \$tool_oldlib"
fi

case $host_os in
  darwin*)
    lock_old_archive_extraction=yes ;;
  *)
    lock_old_archive_extraction=no ;;
esac
_LT_DECL([], [old_postinstall_cmds], [2])
_LT_DECL([], [old_postuninstall_cmds], [2])
_LT_TAGDECL([], [old_archive_cmds], [2],
    [Commands used to build an old-style archive])
_LT_DECL([], [lock_old_archive_extraction], [0],
    [Whether to use a lock for old archive extraction])
])# _LT_CMD_OLD_ARCHIVE


# _LT_COMPILER_OPTION(MESSAGE, VARIABLE-NAME, FLAGS,
#		[OUTPUT-FILE], [ACTION-SUCCESS], [ACTION-FAILURE])
# ----------------------------------------------------------------
# Check whether the given compiler option works
AC_DEFUN([_LT_COMPILER_OPTION],
[m4_require([_LT_FILEUTILS_DEFAULTS])dnl
m4_require([_LT_DECL_SED])dnl
AC_CACHE_CHECK([$1], [$2],
  [$2=no
   m4_if([$4], , [ac_outfile=conftest.$ac_objext], [ac_outfile=$4])
   echo "$lt_simple_compile_test_code" > conftest.$ac_ext
   lt_compiler_flag="$3"
   # Insert the option either (1) after the last *FLAGS variable, or
   # (2) before a word containing "conftest.", or (3) at the end.
   # Note that $ac_compile itself does not contain backslashes and begins
   # with a dollar sign (not a hyphen), so the echo should work correctly.
   # The option is referenced via a variable to avoid confusing sed.
   lt_compile=`echo "$ac_compile" | $SED \
   -e 's:.*FLAGS}\{0,1\} :&$lt_compiler_flag :; t' \
   -e 's: [[^ ]]*conftest\.: $lt_compiler_flag&:; t' \
   -e 's:$: $lt_compiler_flag:'`
   (eval echo "\"\$as_me:$LINENO: $lt_compile\"" >&AS_MESSAGE_LOG_FD)
   (eval "$lt_compile" 2>conftest.err)
   ac_status=$?
   cat conftest.err >&AS_MESSAGE_LOG_FD
   echo "$as_me:$LINENO: \$? = $ac_status" >&AS_MESSAGE_LOG_FD
   if (exit $ac_status) && test -s "$ac_outfile"; then
     # The compiler can only warn and ignore the option if not recognized
     # So say no if there are warnings other than the usual output.
     $ECHO "$_lt_compiler_boilerplate" | $SED '/^$/d' >conftest.exp
     $SED '/^$/d; /^ *+/d' conftest.err >conftest.er2
     if test ! -s conftest.er2 || diff conftest.exp conftest.er2 >/dev/null; then
       $2=yes
     fi
   fi
   $RM conftest*
])

if test x"[$]$2" = xyes; then
    m4_if([$5], , :, [$5])
else
    m4_if([$6], , :, [$6])
fi
])# _LT_COMPILER_OPTION

# Old name:
AU_ALIAS([AC_LIBTOOL_COMPILER_OPTION], [_LT_COMPILER_OPTION])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_COMPILER_OPTION], [])


# _LT_LINKER_OPTION(MESSAGE, VARIABLE-NAME, FLAGS,
#                  [ACTION-SUCCESS], [ACTION-FAILURE])
# ----------------------------------------------------
# Check whether the given linker option works
AC_DEFUN([_LT_LINKER_OPTION],
[m4_require([_LT_FILEUTILS_DEFAULTS])dnl
m4_require([_LT_DECL_SED])dnl
AC_CACHE_CHECK([$1], [$2],
  [$2=no
   save_LDFLAGS="$LDFLAGS"
   LDFLAGS="$LDFLAGS $3"
   echo "$lt_simple_link_test_code" > conftest.$ac_ext
   if (eval $ac_link 2>conftest.err) && test -s conftest$ac_exeext; then
     # The linker can only warn and ignore the option if not recognized
     # So say no if there are warnings
     if test -s conftest.err; then
       # Append any errors to the config.log.
       cat conftest.err 1>&AS_MESSAGE_LOG_FD
       $ECHO "$_lt_linker_boilerplate" | $SED '/^$/d' > conftest.exp
       $SED '/^$/d; /^ *+/d' conftest.err >conftest.er2
       if diff conftest.exp conftest.er2 >/dev/null; then
         $2=yes
       fi
     else
       $2=yes
     fi
   fi
   $RM -r conftest*
   LDFLAGS="$save_LDFLAGS"
])

if test x"[$]$2" = xyes; then
    m4_if([$4], , :, [$4])
else
    m4_if([$5], , :, [$5])
fi
])# _LT_LINKER_OPTION

# Old name:
AU_ALIAS([AC_LIBTOOL_LINKER_OPTION], [_LT_LINKER_OPTION])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_LINKER_OPTION], [])


# LT_CMD_MAX_LEN
#---------------
AC_DEFUN([LT_CMD_MAX_LEN],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
# find the maximum length of command line arguments
AC_MSG_CHECKING([the maximum length of command line arguments])
AC_CACHE_VAL([lt_cv_sys_max_cmd_len], [dnl
  i=0
  teststring="ABCD"

  case $build_os in
  msdosdjgpp*)
    # On DJGPP, this test can blow up pretty badly due to problems in libc
    # (any single argument exceeding 2000 bytes causes a buffer overrun
    # during glob expansion).  Even if it were fixed, the result of this
    # check would be larger than it should be.
    lt_cv_sys_max_cmd_len=12288;    # 12K is about right
    ;;

  gnu*)
    # Under GNU Hurd, this test is not required because there is
    # no limit to the length of command line arguments.
    # Libtool will interpret -1 as no limit whatsoever
    lt_cv_sys_max_cmd_len=-1;
    ;;

  cygwin* | mingw* | cegcc*)
    # On Win9x/ME, this test blows up -- it succeeds, but takes
    # about 5 minutes as the teststring grows exponentially.
    # Worse, since 9x/ME are not pre-emptively multitasking,
    # you end up with a "frozen" computer, even though with patience
    # the test eventually succeeds (with a max line length of 256k).
    # Instead, let's just punt: use the minimum linelength reported by
    # all of the supported platforms: 8192 (on NT/2K/XP).
    lt_cv_sys_max_cmd_len=8192;
    ;;

  mint*)
    # On MiNT this can take a long time and run out of memory.
    lt_cv_sys_max_cmd_len=8192;
    ;;

  amigaos*)
    # On AmigaOS with pdksh, this test takes hours, literally.
    # So we just punt and use a minimum line length of 8192.
    lt_cv_sys_max_cmd_len=8192;
    ;;

  netbsd* | freebsd* | openbsd* | darwin* | dragonfly*)
    # This has been around since 386BSD, at least.  Likely further.
    if test -x /sbin/sysctl; then
      lt_cv_sys_max_cmd_len=`/sbin/sysctl -n kern.argmax`
    elif test -x /usr/sbin/sysctl; then
      lt_cv_sys_max_cmd_len=`/usr/sbin/sysctl -n kern.argmax`
    else
      lt_cv_sys_max_cmd_len=65536	# usable default for all BSDs
    fi
    # And add a safety zone
    lt_cv_sys_max_cmd_len=`expr $lt_cv_sys_max_cmd_len \/ 4`
    lt_cv_sys_max_cmd_len=`expr $lt_cv_sys_max_cmd_len \* 3`
    ;;

  interix*)
    # We know the value 262144 and hardcode it with a safety zone (like BSD)
    lt_cv_sys_max_cmd_len=196608
    ;;

  os2*)
    # The test takes a long time on OS/2.
    lt_cv_sys_max_cmd_len=8192
    ;;

  osf*)
    # Dr. Hans Ekkehard Plesser reports seeing a kernel panic running configure
    # due to this test when exec_disable_arg_limit is 1 on Tru64. It is not
    # nice to cause kernel panics so lets avoid the loop below.
    # First set a reasonable default.
    lt_cv_sys_max_cmd_len=16384
    #
    if test -x /sbin/sysconfig; then
      case `/sbin/sysconfig -q proc exec_disable_arg_limit` in
        *1*) lt_cv_sys_max_cmd_len=-1 ;;
      esac
    fi
    ;;
  sco3.2v5*)
    lt_cv_sys_max_cmd_len=102400
    ;;
  sysv5* | sco5v6* | sysv4.2uw2*)
    kargmax=`grep ARG_MAX /etc/conf/cf.d/stune 2>/dev/null`
    if test -n "$kargmax"; then
      lt_cv_sys_max_cmd_len=`echo $kargmax | sed 's/.*[[	 ]]//'`
    else
      lt_cv_sys_max_cmd_len=32768
    fi
    ;;
  *)
    lt_cv_sys_max_cmd_len=`(getconf ARG_MAX) 2> /dev/null`
    if test -n "$lt_cv_sys_max_cmd_len"; then
      lt_cv_sys_max_cmd_len=`expr $lt_cv_sys_max_cmd_len \/ 4`
      lt_cv_sys_max_cmd_len=`expr $lt_cv_sys_max_cmd_len \* 3`
    else
      # Make teststring a little bigger before we do anything with it.
      # a 1K string should be a reasonable start.
      for i in 1 2 3 4 5 6 7 8 ; do
        teststring=$teststring$teststring
      done
      SHELL=${SHELL-${CONFIG_SHELL-/bin/sh}}
      # If test is not a shell built-in, we'll probably end up computing a
      # maximum length that is only half of the actual maximum length, but
      # we can't tell.
      while { test "X"`env echo "$teststring$teststring" 2>/dev/null` \
	         = "X$teststring$teststring"; } >/dev/null 2>&1 &&
	      test $i != 17 # 1/2 MB should be enough
      do
        i=`expr $i + 1`
        teststring=$teststring$teststring
      done
      # Only check the string length outside the loop.
      lt_cv_sys_max_cmd_len=`expr "X$teststring" : ".*" 2>&1`
      teststring=
      # Add a significant safety factor because C++ compilers can tack on
      # massive amounts of additional arguments before passing them to the
      # linker.  It appears as though 1/2 is a usable value.
      lt_cv_sys_max_cmd_len=`expr $lt_cv_sys_max_cmd_len \/ 2`
    fi
    ;;
  esac
])
if test -n $lt_cv_sys_max_cmd_len ; then
  AC_MSG_RESULT($lt_cv_sys_max_cmd_len)
else
  AC_MSG_RESULT(none)
fi
max_cmd_len=$lt_cv_sys_max_cmd_len
_LT_DECL([], [max_cmd_len], [0],
    [What is the maximum length of a command?])
])# LT_CMD_MAX_LEN

# Old name:
AU_ALIAS([AC_LIBTOOL_SYS_MAX_CMD_LEN], [LT_CMD_MAX_LEN])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_SYS_MAX_CMD_LEN], [])


# _LT_HEADER_DLFCN
# ----------------
m4_defun([_LT_HEADER_DLFCN],
[AC_CHECK_HEADERS([dlfcn.h], [], [], [AC_INCLUDES_DEFAULT])dnl
])# _LT_HEADER_DLFCN


# _LT_TRY_DLOPEN_SELF (ACTION-IF-TRUE, ACTION-IF-TRUE-W-USCORE,
#                      ACTION-IF-FALSE, ACTION-IF-CROSS-COMPILING)
# ----------------------------------------------------------------
m4_defun([_LT_TRY_DLOPEN_SELF],
[m4_require([_LT_HEADER_DLFCN])dnl
if test "$cross_compiling" = yes; then :
  [$4]
else
  lt_dlunknown=0; lt_dlno_uscore=1; lt_dlneed_uscore=2
  lt_status=$lt_dlunknown
  cat > conftest.$ac_ext <<_LT_EOF
[#line $LINENO "configure"
#include "confdefs.h"

#if HAVE_DLFCN_H
#include <dlfcn.h>
#endif

#include <stdio.h>

#ifdef RTLD_GLOBAL
#  define LT_DLGLOBAL		RTLD_GLOBAL
#else
#  ifdef DL_GLOBAL
#    define LT_DLGLOBAL		DL_GLOBAL
#  else
#    define LT_DLGLOBAL		0
#  endif
#endif

/* We may have to define LT_DLLAZY_OR_NOW in the command line if we
   find out it does not work in some platform. */
#ifndef LT_DLLAZY_OR_NOW
#  ifdef RTLD_LAZY
#    define LT_DLLAZY_OR_NOW		RTLD_LAZY
#  else
#    ifdef DL_LAZY
#      define LT_DLLAZY_OR_NOW		DL_LAZY
#    else
#      ifdef RTLD_NOW
#        define LT_DLLAZY_OR_NOW	RTLD_NOW
#      else
#        ifdef DL_NOW
#          define LT_DLLAZY_OR_NOW	DL_NOW
#        else
#          define LT_DLLAZY_OR_NOW	0
#        endif
#      endif
#    endif
#  endif
#endif

/* When -fvisbility=hidden is used, assume the code has been annotated
   correspondingly for the symbols needed.  */
#if defined(__GNUC__) && (((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 3))
int fnord () __attribute__((visibility("default")));
#endif

int fnord () { return 42; }
int main ()
{
  void *self = dlopen (0, LT_DLGLOBAL|LT_DLLAZY_OR_NOW);
  int status = $lt_dlunknown;

  if (self)
    {
      if (dlsym (self,"fnord"))       status = $lt_dlno_uscore;
      else
        {
	  if (dlsym( self,"_fnord"))  status = $lt_dlneed_uscore;
          else puts (dlerror ());
	}
      /* dlclose (self); */
    }
  else
    puts (dlerror ());

  return status;
}]
_LT_EOF
  if AC_TRY_EVAL(ac_link) && test -s conftest${ac_exeext} 2>/dev/null; then
    (./conftest; exit; ) >&AS_MESSAGE_LOG_FD 2>/dev/null
    lt_status=$?
    case x$lt_status in
      x$lt_dlno_uscore) $1 ;;
      x$lt_dlneed_uscore) $2 ;;
      x$lt_dlunknown|x*) $3 ;;
    esac
  else :
    # compilation failed
    $3
  fi
fi
rm -fr conftest*
])# _LT_TRY_DLOPEN_SELF


# LT_SYS_DLOPEN_SELF
# ------------------
AC_DEFUN([LT_SYS_DLOPEN_SELF],
[m4_require([_LT_HEADER_DLFCN])dnl
if test "x$enable_dlopen" != xyes; then
  enable_dlopen=unknown
  enable_dlopen_self=unknown
  enable_dlopen_self_static=unknown
else
  lt_cv_dlopen=no
  lt_cv_dlopen_libs=

  case $host_os in
  beos*)
    lt_cv_dlopen="load_add_on"
    lt_cv_dlopen_libs=
    lt_cv_dlopen_self=yes
    ;;

  mingw* | pw32* | cegcc*)
    lt_cv_dlopen="LoadLibrary"
    lt_cv_dlopen_libs=
    ;;

  cygwin*)
    lt_cv_dlopen="dlopen"
    lt_cv_dlopen_libs=
    ;;

  darwin*)
  # if libdl is installed we need to link against it
    AC_CHECK_LIB([dl], [dlopen],
		[lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-ldl"],[
    lt_cv_dlopen="dyld"
    lt_cv_dlopen_libs=
    lt_cv_dlopen_self=yes
    ])
    ;;

  *)
    AC_CHECK_FUNC([shl_load],
	  [lt_cv_dlopen="shl_load"],
      [AC_CHECK_LIB([dld], [shl_load],
	    [lt_cv_dlopen="shl_load" lt_cv_dlopen_libs="-ldld"],
	[AC_CHECK_FUNC([dlopen],
	      [lt_cv_dlopen="dlopen"],
	  [AC_CHECK_LIB([dl], [dlopen],
		[lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-ldl"],
	    [AC_CHECK_LIB([svld], [dlopen],
		  [lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-lsvld"],
	      [AC_CHECK_LIB([dld], [dld_link],
		    [lt_cv_dlopen="dld_link" lt_cv_dlopen_libs="-ldld"])
	      ])
	    ])
	  ])
	])
      ])
    ;;
  esac

  if test "x$lt_cv_dlopen" != xno; then
    enable_dlopen=yes
  else
    enable_dlopen=no
  fi

  case $lt_cv_dlopen in
  dlopen)
    save_CPPFLAGS="$CPPFLAGS"
    test "x$ac_cv_header_dlfcn_h" = xyes && CPPFLAGS="$CPPFLAGS -DHAVE_DLFCN_H"

    save_LDFLAGS="$LDFLAGS"
    wl=$lt_prog_compiler_wl eval LDFLAGS=\"\$LDFLAGS $export_dynamic_flag_spec\"

    save_LIBS="$LIBS"
    LIBS="$lt_cv_dlopen_libs $LIBS"

    AC_CACHE_CHECK([whether a program can dlopen itself],
	  lt_cv_dlopen_self, [dnl
	  _LT_TRY_DLOPEN_SELF(
	    lt_cv_dlopen_self=yes, lt_cv_dlopen_self=yes,
	    lt_cv_dlopen_self=no, lt_cv_dlopen_self=cross)
    ])

    if test "x$lt_cv_dlopen_self" = xyes; then
      wl=$lt_prog_compiler_wl eval LDFLAGS=\"\$LDFLAGS $lt_prog_compiler_static\"
      AC_CACHE_CHECK([whether a statically linked program can dlopen itself],
	  lt_cv_dlopen_self_static, [dnl
	  _LT_TRY_DLOPEN_SELF(
	    lt_cv_dlopen_self_static=yes, lt_cv_dlopen_self_static=yes,
	    lt_cv_dlopen_self_static=no,  lt_cv_dlopen_self_static=cross)
      ])
    fi

    CPPFLAGS="$save_CPPFLAGS"
    LDFLAGS="$save_LDFLAGS"
    LIBS="$save_LIBS"
    ;;
  esac

  case $lt_cv_dlopen_self in
  yes|no) enable_dlopen_self=$lt_cv_dlopen_self ;;
  *) enable_dlopen_self=unknown ;;
  esac

  case $lt_cv_dlopen_self_static in
  yes|no) enable_dlopen_self_static=$lt_cv_dlopen_self_static ;;
  *) enable_dlopen_self_static=unknown ;;
  esac
fi
_LT_DECL([dlopen_support], [enable_dlopen], [0],
	 [Whether dlopen is supported])
_LT_DECL([dlopen_self], [enable_dlopen_self], [0],
	 [Whether dlopen of programs is supported])
_LT_DECL([dlopen_self_static], [enable_dlopen_self_static], [0],
	 [Whether dlopen of statically linked programs is supported])
])# LT_SYS_DLOPEN_SELF

# Old name:
AU_ALIAS([AC_LIBTOOL_DLOPEN_SELF], [LT_SYS_DLOPEN_SELF])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_DLOPEN_SELF], [])


# _LT_COMPILER_C_O([TAGNAME])
# ---------------------------
# Check to see if options -c and -o are simultaneously supported by compiler.
# This macro does not hard code the compiler like AC_PROG_CC_C_O.
m4_defun([_LT_COMPILER_C_O],
[m4_require([_LT_DECL_SED])dnl
m4_require([_LT_FILEUTILS_DEFAULTS])dnl
m4_require([_LT_TAG_COMPILER])dnl
AC_CACHE_CHECK([if $compiler supports -c -o file.$ac_objext],
  [_LT_TAGVAR(lt_cv_prog_compiler_c_o, $1)],
  [_LT_TAGVAR(lt_cv_prog_compiler_c_o, $1)=no
   $RM -r conftest 2>/dev/null
   mkdir conftest
   cd conftest
   mkdir out
   echo "$lt_simple_compile_test_code" > conftest.$ac_ext

   lt_compiler_flag="-o out/conftest2.$ac_objext"
   # Insert the option either (1) after the last *FLAGS variable, or
   # (2) before a word containing "conftest.", or (3) at the end.
   # Note that $ac_compile itself does not contain backslashes and begins
   # with a dollar sign (not a hyphen), so the echo should work correctly.
   lt_compile=`echo "$ac_compile" | $SED \
   -e 's:.*FLAGS}\{0,1\} :&$lt_compiler_flag :; t' \
   -e 's: [[^ ]]*conftest\.: $lt_compiler_flag&:; t' \
   -e 's:$: $lt_compiler_flag:'`
   (eval echo "\"\$as_me:$LINENO: $lt_compile\"" >&AS_MESSAGE_LOG_FD)
   (eval "$lt_compile" 2>out/conftest.err)
   ac_status=$?
   cat out/conftest.err >&AS_MESSAGE_LOG_FD
   echo "$as_me:$LINENO: \$? = $ac_status" >&AS_MESSAGE_LOG_FD
   if (exit $ac_status) && test -s out/conftest2.$ac_objext
   then
     # The compiler can only warn and ignore the option if not recognized
     # So say no if there are warnings
     $ECHO "$_lt_compiler_boilerplate" | $SED '/^$/d' > out/conftest.exp
     $SED '/^$/d; /^ *+/d' out/conftest.err >out/conftest.er2
     if test ! -s out/conftest.er2 || diff out/conftest.exp out/conftest.er2 >/dev/null; then
       _LT_TAGVAR(lt_cv_prog_compiler_c_o, $1)=yes
     fi
   fi
   chmod u+w . 2>&AS_MESSAGE_LOG_FD
   $RM conftest*
   # SGI C++ compiler will create directory out/ii_files/ for
   # template instantiation
   test -d out/ii_files && $RM out/ii_files/* && rmdir out/ii_files
   $RM out/* && rmdir out
   cd ..
   $RM -r conftest
   $RM conftest*
])
_LT_TAGDECL([compiler_c_o], [lt_cv_prog_compiler_c_o], [1],
	[Does compiler simultaneously support -c and -o options?])
])# _LT_COMPILER_C_O


# _LT_COMPILER_FILE_LOCKS([TAGNAME])
# ----------------------------------
# Check to see if we can do hard links to lock some files if needed
m4_defun([_LT_COMPILER_FILE_LOCKS],
[m4_require([_LT_ENABLE_LOCK])dnl
m4_require([_LT_FILEUTILS_DEFAULTS])dnl
_LT_COMPILER_C_O([$1])

hard_links="nottested"
if test "$_LT_TAGVAR(lt_cv_prog_compiler_c_o, $1)" = no && test "$need_locks" != no; then
  # do not overwrite the value of need_locks provided by the user
  AC_MSG_CHECKING([if we can lock with hard links])
  hard_links=yes
  $RM conftest*
  ln conftest.a conftest.b 2>/dev/null && hard_links=no
  touch conftest.a
  ln conftest.a conftest.b 2>&5 || hard_links=no
  ln conftest.a conftest.b 2>/dev/null && hard_links=no
  AC_MSG_RESULT([$hard_links])
  if test "$hard_links" = no; then
    AC_MSG_WARN([`$CC' does not support `-c -o', so `make -j' may be unsafe])
    need_locks=warn
  fi
else
  need_locks=no
fi
_LT_DECL([], [need_locks], [1], [Must we lock files when doing compilation?])
])# _LT_COMPILER_FILE_LOCKS


# _LT_CHECK_OBJDIR
# ----------------
m4_defun([_LT_CHECK_OBJDIR],
[AC_CACHE_CHECK([for objdir], [lt_cv_objdir],
[rm -f .libs 2>/dev/null
mkdir .libs 2>/dev/null
if test -d .libs; then
  lt_cv_objdir=.libs
else
  # MS-DOS does not allow filenames that begin with a dot.
  lt_cv_objdir=_libs
fi
rmdir .libs 2>/dev/null])
objdir=$lt_cv_objdir
_LT_DECL([], [objdir], [0],
         [The name of the directory that contains temporary libtool files])dnl
m4_pattern_allow([LT_OBJDIR])dnl
AC_DEFINE_UNQUOTED(LT_OBJDIR, "$lt_cv_objdir/",
  [Define to the sub-directory in which libtool stores uninstalled libraries.])
])# _LT_CHECK_OBJDIR


# _LT_LINKER_HARDCODE_LIBPATH([TAGNAME])
# --------------------------------------
# Check hardcoding attributes.
m4_defun([_LT_LINKER_HARDCODE_LIBPATH],
[AC_MSG_CHECKING([how to hardcode library paths into programs])
_LT_TAGVAR(hardcode_action, $1)=
if test -n "$_LT_TAGVAR(hardcode_libdir_flag_spec, $1)" ||
   test -n "$_LT_TAGVAR(runpath_var, $1)" ||
   test "X$_LT_TAGVAR(hardcode_automatic, $1)" = "Xyes" ; then

  # We can hardcode non-existent directories.
  if test "$_LT_TAGVAR(hardcode_direct, $1)" != no &&
     # If the only mechanism to avoid hardcoding is shlibpath_var, we
     # have to relink, otherwise we might link with an installed library
     # when we should be linking with a yet-to-be-installed one
     ## test "$_LT_TAGVAR(hardcode_shlibpath_var, $1)" != no &&
     test "$_LT_TAGVAR(hardcode_minus_L, $1)" != no; then
    # Linking always hardcodes the temporary library directory.
    _LT_TAGVAR(hardcode_action, $1)=relink
  else
    # We can link without hardcoding, and we can hardcode nonexisting dirs.
    _LT_TAGVAR(hardcode_action, $1)=immediate
  fi
else
  # We cannot hardcode anything, or else we can only hardcode existing
  # directories.
  _LT_TAGVAR(hardcode_action, $1)=unsupported
fi
AC_MSG_RESULT([$_LT_TAGVAR(hardcode_action, $1)])

if test "$_LT_TAGVAR(hardcode_action, $1)" = relink ||
   test "$_LT_TAGVAR(inherit_rpath, $1)" = yes; then
  # Fast installation is not supported
  enable_fast_install=no
elif test "$shlibpath_overrides_runpath" = yes ||
     test "$enable_shared" = no; then
  # Fast installation is not necessary
  enable_fast_install=needless
fi
_LT_TAGDECL([], [hardcode_action], [0],
    [How to hardcode a shared library path into an executable])
])# _LT_LINKER_HARDCODE_LIBPATH


# _LT_CMD_STRIPLIB
# ----------------
m4_defun([_LT_CMD_STRIPLIB],
[m4_require([_LT_DECL_EGREP])
striplib=
old_striplib=
AC_MSG_CHECKING([whether stripping libraries is possible])
if test -n "$STRIP" && $STRIP -V 2>&1 | $GREP "GNU strip" >/dev/null; then
  test -z "$old_striplib" && old_striplib="$STRIP --strip-debug"
  test -z "$striplib" && striplib="$STRIP --strip-unneeded"
  AC_MSG_RESULT([yes])
else
# FIXME - insert some real tests, host_os isn't really good enough
  case $host_os in
  darwin*)
    if test -n "$STRIP" ; then
      striplib="$STRIP -x"
      old_striplib="$STRIP -S"
      AC_MSG_RESULT([yes])
    else
      AC_MSG_RESULT([no])
    fi
    ;;
  *)
    AC_MSG_RESULT([no])
    ;;
  esac
fi
_LT_DECL([], [old_striplib], [1], [Commands to strip libraries])
_LT_DECL([], [striplib], [1])
])# _LT_CMD_STRIPLIB


# _LT_SYS_DYNAMIC_LINKER([TAG])
# -----------------------------
# PORTME Fill in your ld.so characteristics
m4_defun([_LT_SYS_DYNAMIC_LINKER],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
m4_require([_LT_DECL_EGREP])dnl
m4_require([_LT_FILEUTILS_DEFAULTS])dnl
m4_require([_LT_DECL_OBJDUMP])dnl
m4_require([_LT_DECL_SED])dnl
m4_require([_LT_CHECK_SHELL_FEATURES])dnl
AC_MSG_CHECKING([dynamic linker characteristics])
m4_if([$1],
	[], [
if test "$GCC" = yes; then
  case $host_os in
    darwin*) lt_awk_arg="/^libraries:/,/LR/" ;;
    *) lt_awk_arg="/^libraries:/" ;;
  esac
  case $host_os in
    mingw* | cegcc*) lt_sed_strip_eq="s,=\([[A-Za-z]]:\),\1,g" ;;
    *) lt_sed_strip_eq="s,=/,/,g" ;;
  esac
  lt_search_path_spec=`$CC -print-search-dirs | awk $lt_awk_arg | $SED -e "s/^libraries://" -e $lt_sed_strip_eq`
  case $lt_search_path_spec in
  *\;*)
    # if the path contains ";" then we assume it to be the separator
    # otherwise default to the standard path separator (i.e. ":") - it is
    # assumed that no part of a normal pathname contains ";" but that should
    # okay in the real world where ";" in dirpaths is itself problematic.
    lt_search_path_spec=`$ECHO "$lt_search_path_spec" | $SED 's/;/ /g'`
    ;;
  *)
    lt_search_path_spec=`$ECHO "$lt_search_path_spec" | $SED "s/$PATH_SEPARATOR/ /g"`
    ;;
  esac
  # Ok, now we have the path, separated by spaces, we can step through it
  # and add multilib dir if necessary.
  lt_tmp_lt_search_path_spec=
  lt_multi_os_dir=`$CC $CPPFLAGS $CFLAGS $LDFLAGS -print-multi-os-directory 2>/dev/null`
  for lt_sys_path in $lt_search_path_spec; do
    if test -d "$lt_sys_path/$lt_multi_os_dir"; then
      lt_tmp_lt_search_path_spec="$lt_tmp_lt_search_path_spec $lt_sys_path/$lt_multi_os_dir"
    else
      test -d "$lt_sys_path" && \
	lt_tmp_lt_search_path_spec="$lt_tmp_lt_search_path_spec $lt_sys_path"
    fi
  done
  lt_search_path_spec=`$ECHO "$lt_tmp_lt_search_path_spec" | awk '
BEGIN {RS=" "; FS="/|\n";} {
  lt_foo="";
  lt_count=0;
  for (lt_i = NF; lt_i > 0; lt_i--) {
    if ($lt_i != "" && $lt_i != ".") {
      if ($lt_i == "..") {
        lt_count++;
      } else {
        if (lt_count == 0) {
          lt_foo="/" $lt_i lt_foo;
        } else {
          lt_count--;
        }
      }
    }
  }
  if (lt_foo != "") { lt_freq[[lt_foo]]++; }
  if (lt_freq[[lt_foo]] == 1) { print lt_foo; }
}'`
  # AWK program above erroneously prepends '/' to C:/dos/paths
  # for these hosts.
  case $host_os in
    mingw* | cegcc*) lt_search_path_spec=`$ECHO "$lt_search_path_spec" |\
      $SED 's,/\([[A-Za-z]]:\),\1,g'` ;;
  esac
  sys_lib_search_path_spec=`$ECHO "$lt_search_path_spec" | $lt_NL2SP`
else
  sys_lib_search_path_spec="/lib /usr/lib /usr/local/lib"
fi])
library_names_spec=
libname_spec='lib$name'
soname_spec=
shrext_cmds=".so"
postinstall_cmds=
postuninstall_cmds=
finish_cmds=
finish_eval=
shlibpath_var=
shlibpath_overrides_runpath=unknown
version_type=none
dynamic_linker="$host_os ld.so"
sys_lib_dlsearch_path_spec="/lib /usr/lib"
need_lib_prefix=unknown
hardcode_into_libs=no

# when you set need_version to no, make sure it does not cause -set_version
# flags to be left without arguments
need_version=unknown

case $host_os in
aix3*)
  version_type=linux # correct to gnu/linux during the next big refactor
  library_names_spec='${libname}${release}${shared_ext}$versuffix $libname.a'
  shlibpath_var=LIBPATH

  # AIX 3 has no versioning support, so we append a major version to the name.
  soname_spec='${libname}${release}${shared_ext}$major'
  ;;

aix[[4-9]]*)
  version_type=linux # correct to gnu/linux during the next big refactor
  need_lib_prefix=no
  need_version=no
  hardcode_into_libs=yes
  if test "$host_cpu" = ia64; then
    # AIX 5 supports IA64
    library_names_spec='${libname}${release}${shared_ext}$major ${libname}${release}${shared_ext}$versuffix $libname${shared_ext}'
    shlibpath_var=LD_LIBRARY_PATH
  else
    # With GCC up to 2.95.x, collect2 would create an import file
    # for dependence libraries.  The import file would start with
    # the line `#! .'.  This would cause the generated library to
    # depend on `.', always an invalid library.  This was fixed in
    # development snapshots of GCC prior to 3.0.
    case $host_os in
      aix4 | aix4.[[01]] | aix4.[[01]].*)
      if { echo '#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 97)'
	   echo ' yes '
	   echo '#endif'; } | ${CC} -E - | $GREP yes > /dev/null; then
	:
      else
	can_build_shared=no
      fi
      ;;
    esac
    # AIX (on Power*) has no versioning support, so currently we can not hardcode correct
    # soname into executable. Probably we can add versioning support to
    # collect2, so additional links can be useful in future.
    if test "$aix_use_runtimelinking" = yes; then
      # If using run time linking (on AIX 4.2 or later) use lib<name>.so
      # instead of lib<name>.a to let people know that these are not
      # typical AIX shared libraries.
      library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
    else
      # We preserve .a as extension for shared libraries through AIX4.2
      # and later when we are not doing run time linking.
      library_names_spec='${libname}${release}.a $libname.a'
      soname_spec='${libname}${release}${shared_ext}$major'
    fi
    shlibpath_var=LIBPATH
  fi
  ;;

amigaos*)
  case $host_cpu in
  powerpc)
    # Since July 2007 AmigaOS4 officially supports .so libraries.
    # When compiling the executable, add -use-dynld -Lsobjs: to the compileline.
    library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
    ;;
  m68k)
    library_names_spec='$libname.ixlibrary $libname.a'
    # Create ${libname}_ixlibrary.a entries in /sys/libs.
    finish_eval='for lib in `ls $libdir/*.ixlibrary 2>/dev/null`; do libname=`func_echo_all "$lib" | $SED '\''s%^.*/\([[^/]]*\)\.ixlibrary$%\1%'\''`; test $RM /sys/libs/${libname}_ixlibrary.a; $show "cd /sys/libs && $LN_S $lib ${libname}_ixlibrary.a"; cd /sys/libs && $LN_S $lib ${libname}_ixlibrary.a || exit 1; done'
    ;;
  esac
  ;;

beos*)
  library_names_spec='${libname}${shared_ext}'
  dynamic_linker="$host_os ld.so"
  shlibpath_var=LIBRARY_PATH
  ;;

bsdi[[45]]*)
  version_type=linux # correct to gnu/linux during the next big refactor
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  sys_lib_search_path_spec="/shlib /usr/lib /usr/X11/lib /usr/contrib/lib /lib /usr/local/lib"
  sys_lib_dlsearch_path_spec="/shlib /usr/lib /usr/local/lib"
  # the default ld.so.conf also contains /usr/contrib/lib and
  # /usr/X11R6/lib (/usr/X11 is a link to /usr/X11R6), but let us allow
  # libtool to hard-code these into programs
  ;;

cygwin* | mingw* | pw32* | cegcc*)
  version_type=windows
  shrext_cmds=".dll"
  need_version=no
  need_lib_prefix=no

  case $GCC,$cc_basename in
  yes,*)
    # gcc
    library_names_spec='$libname.dll.a'
    # DLL is installed to $(libdir)/../bin by postinstall_cmds
    postinstall_cmds='base_file=`basename \${file}`~
      dlpath=`$SHELL 2>&1 -c '\''. $dir/'\''\${base_file}'\''i; echo \$dlname'\''`~
      dldir=$destdir/`dirname \$dlpath`~
      test -d \$dldir || mkdir -p \$dldir~
      $install_prog $dir/$dlname \$dldir/$dlname~
      chmod a+x \$dldir/$dlname~
      if test -n '\''$stripme'\'' && test -n '\''$striplib'\''; then
        eval '\''$striplib \$dldir/$dlname'\'' || exit \$?;
      fi'
    postuninstall_cmds='dldll=`$SHELL 2>&1 -c '\''. $file; echo \$dlname'\''`~
      dlpath=$dir/\$dldll~
       $RM \$dlpath'
    shlibpath_overrides_runpath=yes

    case $host_os in
    cygwin*)
      # Cygwin DLLs use 'cyg' prefix rather than 'lib'
      soname_spec='`echo ${libname} | sed -e 's/^lib/cyg/'``echo ${release} | $SED -e 's/[[.]]/-/g'`${versuffix}${shared_ext}'
m4_if([$1], [],[
      sys_lib_search_path_spec="$sys_lib_search_path_spec /usr/lib/w32api"])
      ;;
    mingw* | cegcc*)
      # MinGW DLLs use traditional 'lib' prefix
      soname_spec='${libname}`echo ${release} | $SED -e 's/[[.]]/-/g'`${versuffix}${shared_ext}'
      ;;
    pw32*)
      # pw32 DLLs use 'pw' prefix rather than 'lib'
      library_names_spec='`echo ${libname} | sed -e 's/^lib/pw/'``echo ${release} | $SED -e 's/[[.]]/-/g'`${versuffix}${shared_ext}'
      ;;
    esac
    dynamic_linker='Win32 ld.exe'
    ;;

  *,cl*)
    # Native MSVC
    libname_spec='$name'
    soname_spec='${libname}`echo ${release} | $SED -e 's/[[.]]/-/g'`${versuffix}${shared_ext}'
    library_names_spec='${libname}.dll.lib'

    case $build_os in
    mingw*)
      sys_lib_search_path_spec=
      lt_save_ifs=$IFS
      IFS=';'
      for lt_path in $LIB
      do
        IFS=$lt_save_ifs
        # Let DOS variable expansion print the short 8.3 style file name.
        lt_path=`cd "$lt_path" 2>/dev/null && cmd //C "for %i in (".") do @echo %~si"`
        sys_lib_search_path_spec="$sys_lib_search_path_spec $lt_path"
      done
      IFS=$lt_save_ifs
      # Convert to MSYS style.
      sys_lib_search_path_spec=`$ECHO "$sys_lib_search_path_spec" | sed -e 's|\\\\|/|g' -e 's| \\([[a-zA-Z]]\\):| /\\1|g' -e 's|^ ||'`
      ;;
    cygwin*)
      # Convert to unix form, then to dos form, then back to unix form
      # but this time dos style (no spaces!) so that the unix form looks
      # like /cygdrive/c/PROGRA~1:/cygdr...
      sys_lib_search_path_spec=`cygpath --path --unix "$LIB"`
      sys_lib_search_path_spec=`cygpath --path --dos "$sys_lib_search_path_spec" 2>/dev/null`
      sys_lib_search_path_spec=`cygpath --path --unix "$sys_lib_search_path_spec" | $SED -e "s/$PATH_SEPARATOR/ /g"`
      ;;
    *)
      sys_lib_search_path_spec="$LIB"
      if $ECHO "$sys_lib_search_path_spec" | [$GREP ';[c-zC-Z]:/' >/dev/null]; then
        # It is most probably a Windows format PATH.
        sys_lib_search_path_spec=`$ECHO "$sys_lib_search_path_spec" | $SED -e 's/;/ /g'`
      else
        sys_lib_search_path_spec=`$ECHO "$sys_lib_search_path_spec" | $SED -e "s/$PATH_SEPARATOR/ /g"`
      fi
      # FIXME: find the short name or the path components, as spaces are
      # common. (e.g. "Program Files" -> "PROGRA~1")
      ;;
    esac

    # DLL is installed to $(libdir)/../bin by postinstall_cmds
    postinstall_cmds='base_file=`basename \${file}`~
      dlpath=`$SHELL 2>&1 -c '\''. $dir/'\''\${base_file}'\''i; echo \$dlname'\''`~
      dldir=$destdir/`dirname \$dlpath`~
      test -d \$dldir || mkdir -p \$dldir~
      $install_prog $dir/$dlname \$dldir/$dlname'
    postuninstall_cmds='dldll=`$SHELL 2>&1 -c '\''. $file; echo \$dlname'\''`~
      dlpath=$dir/\$dldll~
       $RM \$dlpath'
    shlibpath_overrides_runpath=yes
    dynamic_linker='Win32 link.exe'
    ;;

  *)
    # Assume MSVC wrapper
    library_names_spec='${libname}`echo ${release} | $SED -e 's/[[.]]/-/g'`${versuffix}${shared_ext} $libname.lib'
    dynamic_linker='Win32 ld.exe'
    ;;
  esac
  # FIXME: first we should search . and the directory the executable is in
  shlibpath_var=PATH
  ;;

darwin* | rhapsody*)
  dynamic_linker="$host_os dyld"
  version_type=darwin
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${major}$shared_ext ${libname}$shared_ext'
  soname_spec='${libname}${release}${major}$shared_ext'
  shlibpath_overrides_runpath=yes
  shlibpath_var=DYLD_LIBRARY_PATH
  shrext_cmds='`test .$module = .yes && echo .so || echo .dylib`'
m4_if([$1], [],[
  sys_lib_search_path_spec="$sys_lib_search_path_spec /usr/local/lib"])
  sys_lib_dlsearch_path_spec='/usr/local/lib /lib /usr/lib'
  ;;

dgux*)
  version_type=linux # correct to gnu/linux during the next big refactor
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname$shared_ext'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LD_LIBRARY_PATH
  ;;

freebsd* | dragonfly*)
  # DragonFly does not have aout.  When/if they implement a new
  # versioning mechanism, adjust this.
  if test -x /usr/bin/objformat; then
    objformat=`/usr/bin/objformat`
  else
    case $host_os in
    freebsd[[23]].*) objformat=aout ;;
    *) objformat=elf ;;
    esac
  fi
  version_type=freebsd-$objformat
  case $version_type in
    freebsd-elf*)
      library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext} $libname${shared_ext}'
      need_version=no
      need_lib_prefix=no
      ;;
    freebsd-*)
      library_names_spec='${libname}${release}${shared_ext}$versuffix $libname${shared_ext}$versuffix'
      need_version=yes
      ;;
  esac
  shlibpath_var=LD_LIBRARY_PATH
  case $host_os in
  freebsd2.*)
    shlibpath_overrides_runpath=yes
    ;;
  freebsd3.[[01]]* | freebsdelf3.[[01]]*)
    shlibpath_overrides_runpath=yes
    hardcode_into_libs=yes
    ;;
  freebsd3.[[2-9]]* | freebsdelf3.[[2-9]]* | \
  freebsd4.[[0-5]] | freebsdelf4.[[0-5]] | freebsd4.1.1 | freebsdelf4.1.1)
    shlibpath_overrides_runpath=no
    hardcode_into_libs=yes
    ;;
  *) # from 4.6 on, and DragonFly
    shlibpath_overrides_runpath=yes
    hardcode_into_libs=yes
    ;;
  esac
  ;;

haiku*)
  version_type=linux # correct to gnu/linux during the next big refactor
  need_lib_prefix=no
  need_version=no
  dynamic_linker="$host_os runtime_loader"
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}${major} ${libname}${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  sys_lib_dlsearch_path_spec='/boot/home/config/lib /boot/common/lib /boot/system/lib'
  hardcode_into_libs=yes
  ;;

hpux9* | hpux10* | hpux11*)
  # Give a soname corresponding to the major version so that dld.sl refuses to
  # link against other versions.
  version_type=sunos
  need_lib_prefix=no
  need_version=no
  case $host_cpu in
  ia64*)
    shrext_cmds='.so'
    hardcode_into_libs=yes
    dynamic_linker="$host_os dld.so"
    shlibpath_var=LD_LIBRARY_PATH
    shlibpath_overrides_runpath=yes # Unless +noenvvar is specified.
    library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
    soname_spec='${libname}${release}${shared_ext}$major'
    if test "X$HPUX_IA64_MODE" = X32; then
      sys_lib_search_path_spec="/usr/lib/hpux32 /usr/local/lib/hpux32 /usr/local/lib"
    else
      sys_lib_search_path_spec="/usr/lib/hpux64 /usr/local/lib/hpux64"
    fi
    sys_lib_dlsearch_path_spec=$sys_lib_search_path_spec
    ;;
  hppa*64*)
    shrext_cmds='.sl'
    hardcode_into_libs=yes
    dynamic_linker="$host_os dld.sl"
    shlibpath_var=LD_LIBRARY_PATH # How should we handle SHLIB_PATH
    shlibpath_overrides_runpath=yes # Unless +noenvvar is specified.
    library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
    soname_spec='${libname}${release}${shared_ext}$major'
    sys_lib_search_path_spec="/usr/lib/pa20_64 /usr/ccs/lib/pa20_64"
    sys_lib_dlsearch_path_spec=$sys_lib_search_path_spec
    ;;
  *)
    shrext_cmds='.sl'
    dynamic_linker="$host_os dld.sl"
    shlibpath_var=SHLIB_PATH
    shlibpath_overrides_runpath=no # +s is required to enable SHLIB_PATH
    library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
    soname_spec='${libname}${release}${shared_ext}$major'
    ;;
  esac
  # HP-UX runs *really* slowly unless shared libraries are mode 555, ...
  postinstall_cmds='chmod 555 $lib'
  # or fails outright, so override atomically:
  install_override_mode=555
  ;;

interix[[3-9]]*)
  version_type=linux # correct to gnu/linux during the next big refactor
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major ${libname}${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  dynamic_linker='Interix 3.x ld.so.1 (PE, like ELF)'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=no
  hardcode_into_libs=yes
  ;;

irix5* | irix6* | nonstopux*)
  case $host_os in
    nonstopux*) version_type=nonstopux ;;
    *)
	if test "$lt_cv_prog_gnu_ld" = yes; then
		version_type=linux # correct to gnu/linux during the next big refactor
	else
		version_type=irix
	fi ;;
  esac
  need_lib_prefix=no
  need_version=no
  soname_spec='${libname}${release}${shared_ext}$major'
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major ${libname}${release}${shared_ext} $libname${shared_ext}'
  case $host_os in
  irix5* | nonstopux*)
    libsuff= shlibsuff=
    ;;
  *)
    case $LD in # libtool.m4 will add one of these switches to LD
    *-32|*"-32 "|*-melf32bsmip|*"-melf32bsmip ")
      libsuff= shlibsuff= libmagic=32-bit;;
    *-n32|*"-n32 "|*-melf32bmipn32|*"-melf32bmipn32 ")
      libsuff=32 shlibsuff=N32 libmagic=N32;;
    *-64|*"-64 "|*-melf64bmip|*"-melf64bmip ")
      libsuff=64 shlibsuff=64 libmagic=64-bit;;
    *) libsuff= shlibsuff= libmagic=never-match;;
    esac
    ;;
  esac
  shlibpath_var=LD_LIBRARY${shlibsuff}_PATH
  shlibpath_overrides_runpath=no
  sys_lib_search_path_spec="/usr/lib${libsuff} /lib${libsuff} /usr/local/lib${libsuff}"
  sys_lib_dlsearch_path_spec="/usr/lib${libsuff} /lib${libsuff}"
  hardcode_into_libs=yes
  ;;

# No shared lib support for Linux oldld, aout, or coff.
linux*oldld* | linux*aout* | linux*coff*)
  dynamic_linker=no
  ;;

# This must be glibc/ELF.
linux* | k*bsd*-gnu | kopensolaris*-gnu | gnu*)
  version_type=linux # correct to gnu/linux during the next big refactor
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig -n $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=no

  # Some binutils ld are patched to set DT_RUNPATH
  AC_CACHE_VAL([lt_cv_shlibpath_overrides_runpath],
    [lt_cv_shlibpath_overrides_runpath=no
    save_LDFLAGS=$LDFLAGS
    save_libdir=$libdir
    eval "libdir=/foo; wl=\"$_LT_TAGVAR(lt_prog_compiler_wl, $1)\"; \
	 LDFLAGS=\"\$LDFLAGS $_LT_TAGVAR(hardcode_libdir_flag_spec, $1)\""
    AC_LINK_IFELSE([AC_LANG_PROGRAM([],[])],
      [AS_IF([ ($OBJDUMP -p conftest$ac_exeext) 2>/dev/null | grep "RUNPATH.*$libdir" >/dev/null],
	 [lt_cv_shlibpath_overrides_runpath=yes])])
    LDFLAGS=$save_LDFLAGS
    libdir=$save_libdir
    ])
  shlibpath_overrides_runpath=$lt_cv_shlibpath_overrides_runpath

  # This implies no fast_install, which is unacceptable.
  # Some rework will be needed to allow for fast_install
  # before this can be enabled.
  hardcode_into_libs=yes

  # Append ld.so.conf contents to the search path
  if test -f /etc/ld.so.conf; then
    lt_ld_extra=`awk '/^include / { system(sprintf("cd /etc; cat %s 2>/dev/null", \[$]2)); skip = 1; } { if (!skip) print \[$]0; skip = 0; }' < /etc/ld.so.conf | $SED -e 's/#.*//;/^[	 ]*hwcap[	 ]/d;s/[:,	]/ /g;s/=[^=]*$//;s/=[^= ]* / /g;s/"//g;/^$/d' | tr '\n' ' '`
    sys_lib_dlsearch_path_spec="/lib /usr/lib $lt_ld_extra"
  fi

  # We used to test for /lib/ld.so.1 and disable shared libraries on
  # powerpc, because MkLinux only supported shared libraries with the
  # GNU dynamic linker.  Since this was broken with cross compilers,
  # most powerpc-linux boxes support dynamic linking these days and
  # people can always --disable-shared, the test was removed, and we
  # assume the GNU/Linux dynamic linker is in use.
  dynamic_linker='GNU/Linux ld.so'
  ;;

netbsdelf*-gnu)
  version_type=linux
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major ${libname}${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=no
  hardcode_into_libs=yes
  dynamic_linker='NetBSD ld.elf_so'
  ;;

netbsd*)
  version_type=sunos
  need_lib_prefix=no
  need_version=no
  if echo __ELF__ | $CC -E - | $GREP __ELF__ >/dev/null; then
    library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${shared_ext}$versuffix'
    finish_cmds='PATH="\$PATH:/sbin" ldconfig -m $libdir'
    dynamic_linker='NetBSD (a.out) ld.so'
  else
    library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major ${libname}${shared_ext}'
    soname_spec='${libname}${release}${shared_ext}$major'
    dynamic_linker='NetBSD ld.elf_so'
  fi
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  hardcode_into_libs=yes
  ;;

newsos6)
  version_type=linux # correct to gnu/linux during the next big refactor
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  ;;

*nto* | *qnx*)
  version_type=qnx
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=no
  hardcode_into_libs=yes
  dynamic_linker='ldqnx.so'
  ;;

openbsd*)
  version_type=sunos
  sys_lib_dlsearch_path_spec="/usr/lib"
  need_lib_prefix=no
  # Some older versions of OpenBSD (3.3 at least) *do* need versioned libs.
  case $host_os in
    openbsd3.3 | openbsd3.3.*)	need_version=yes ;;
    *)				need_version=no  ;;
  esac
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${shared_ext}$versuffix'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig -m $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  if test -z "`echo __ELF__ | $CC -E - | $GREP __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powerpc"; then
    case $host_os in
      openbsd2.[[89]] | openbsd2.[[89]].*)
	shlibpath_overrides_runpath=no
	;;
      *)
	shlibpath_overrides_runpath=yes
	;;
      esac
  else
    shlibpath_overrides_runpath=yes
  fi
  ;;

os2*)
  libname_spec='$name'
  shrext_cmds=".dll"
  need_lib_prefix=no
  library_names_spec='$libname${shared_ext} $libname.a'
  dynamic_linker='OS/2 ld.exe'
  shlibpath_var=LIBPATH
  ;;

osf3* | osf4* | osf5*)
  version_type=osf
  need_lib_prefix=no
  need_version=no
  soname_spec='${libname}${release}${shared_ext}$major'
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  shlibpath_var=LD_LIBRARY_PATH
  sys_lib_search_path_spec="/usr/shlib /usr/ccs/lib /usr/lib/cmplrs/cc /usr/lib /usr/local/lib /var/shlib"
  sys_lib_dlsearch_path_spec="$sys_lib_search_path_spec"
  ;;

rdos*)
  dynamic_linker=no
  ;;

solaris*)
  version_type=linux # correct to gnu/linux during the next big refactor
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  hardcode_into_libs=yes
  # ldd complains unless libraries are executable
  postinstall_cmds='chmod +x $lib'
  ;;

sunos4*)
  version_type=sunos
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${shared_ext}$versuffix'
  finish_cmds='PATH="\$PATH:/usr/etc" ldconfig $libdir'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  if test "$with_gnu_ld" = yes; then
    need_lib_prefix=no
  fi
  need_version=yes
  ;;

sysv4 | sysv4.3*)
  version_type=linux # correct to gnu/linux during the next big refactor
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LD_LIBRARY_PATH
  case $host_vendor in
    sni)
      shlibpath_overrides_runpath=no
      need_lib_prefix=no
      runpath_var=LD_RUN_PATH
      ;;
    siemens)
      need_lib_prefix=no
      ;;
    motorola)
      need_lib_prefix=no
      need_version=no
      shlibpath_overrides_runpath=no
      sys_lib_search_path_spec='/lib /usr/lib /usr/ccs/lib'
      ;;
  esac
  ;;

sysv4*MP*)
  if test -d /usr/nec ;then
    version_type=linux # correct to gnu/linux during the next big refactor
    library_names_spec='$libname${shared_ext}.$versuffix $libname${shared_ext}.$major $libname${shared_ext}'
    soname_spec='$libname${shared_ext}.$major'
    shlibpath_var=LD_LIBRARY_PATH
  fi
  ;;

sysv5* | sco3.2v5* | sco5v6* | unixware* | OpenUNIX* | sysv4*uw2*)
  version_type=freebsd-elf
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext} $libname${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=yes
  hardcode_into_libs=yes
  if test "$with_gnu_ld" = yes; then
    sys_lib_search_path_spec='/usr/local/lib /usr/gnu/lib /usr/ccs/lib /usr/lib /lib'
  else
    sys_lib_search_path_spec='/usr/ccs/lib /usr/lib'
    case $host_os in
      sco3.2v5*)
        sys_lib_search_path_spec="$sys_lib_search_path_spec /lib"
	;;
    esac
  fi
  sys_lib_dlsearch_path_spec='/usr/lib'
  ;;

tpf*)
  # TPF is a cross-target only.  Preferred cross-host = GNU/Linux.
  version_type=linux # correct to gnu/linux during the next big refactor
  need_lib_prefix=no
  need_version=no
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  shlibpath_var=LD_LIBRARY_PATH
  shlibpath_overrides_runpath=no
  hardcode_into_libs=yes
  ;;

uts4*)
  version_type=linux # correct to gnu/linux during the next big refactor
  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
  soname_spec='${libname}${release}${shared_ext}$major'
  shlibpath_var=LD_LIBRARY_PATH
  ;;

*)
  dynamic_linker=no
  ;;
esac
AC_MSG_RESULT([$dynamic_linker])
test "$dynamic_linker" = no && can_build_shared=no

variables_saved_for_relink="PATH $shlibpath_var $runpath_var"
if test "$GCC" = yes; then
  variables_saved_for_relink="$variables_saved_for_relink GCC_EXEC_PREFIX COMPILER_PATH LIBRARY_PATH"
fi

if test "${lt_cv_sys_lib_search_path_spec+set}" = set; then
  sys_lib_search_path_spec="$lt_cv_sys_lib_search_path_spec"
fi
if test "${lt_cv_sys_lib_dlsearch_path_spec+set}" = set; then
  sys_lib_dlsearch_path_spec="$lt_cv_sys_lib_dlsearch_path_spec"
fi

_LT_DECL([], [variables_saved_for_relink], [1],
    [Variables whose values should be saved in libtool wrapper scripts and
    restored at link time])
_LT_DECL([], [need_lib_prefix], [0],
    [Do we need the "lib" prefix for modules?])
_LT_DECL([], [need_version], [0], [Do we need a version for libraries?])
_LT_DECL([], [version_type], [0], [Library versioning type])
_LT_DECL([], [runpath_var], [0],  [Shared library runtime path variable])
_LT_DECL([], [shlibpath_var], [0],[Shared library path variable])
_LT_DECL([], [shlibpath_overrides_runpath], [0],
    [Is shlibpath searched before the hard-coded library search path?])
_LT_DECL([], [libname_spec], [1], [Format of library name prefix])
_LT_DECL([], [library_names_spec], [1],
    [[List of archive names.  First name is the real one, the rest are links.
    The last name is the one that the linker finds with -lNAME]])
_LT_DECL([], [soname_spec], [1],
    [[The coded name of the library, if different from the real name]])
_LT_DECL([], [install_override_mode], [1],
    [Permission mode override for installation of shared libraries])
_LT_DECL([], [postinstall_cmds], [2],
    [Command to use after installation of a shared archive])
_LT_DECL([], [postuninstall_cmds], [2],
    [Command to use after uninstallation of a shared archive])
_LT_DECL([], [finish_cmds], [2],
    [Commands used to finish a libtool library installation in a directory])
_LT_DECL([], [finish_eval], [1],
    [[As "finish_cmds", except a single script fragment to be evaled but
    not shown]])
_LT_DECL([], [hardcode_into_libs], [0],
    [Whether we should hardcode library paths into libraries])
_LT_DECL([], [sys_lib_search_path_spec], [2],
    [Compile-time system search path for libraries])
_LT_DECL([], [sys_lib_dlsearch_path_spec], [2],
    [Run-time system search path for libraries])
])# _LT_SYS_DYNAMIC_LINKER


# _LT_PATH_TOOL_PREFIX(TOOL)
# --------------------------
# find a file program which can recognize shared library
AC_DEFUN([_LT_PATH_TOOL_PREFIX],
[m4_require([_LT_DECL_EGREP])dnl
AC_MSG_CHECKING([for $1])
AC_CACHE_VAL(lt_cv_path_MAGIC_CMD,
[case $MEGIC_CMD in
[[\\/*] |  /:[\\/]*])
 "lt_cv_path_MAGIC_CM@-"$MAGIC_CMD" # Let txehuser overrhde the test wéuh`a path.  ;;
*)
  lt_save_MAGIC_CMD="$MAGIC_CMD"
  dt_save_kfs="$IFS"; IFS=$PATH_SEPARAPOR
dnl $acdummy forces splitöing on constant uÓer-supplied paths.
dnl POSIX.2 word splittino$is done only ol the output(of word expafsions,
dnl nt everq word>  Thic closec a longstanäing sh security hole/*  ak_dummy="m4_if([$2], , ,PÁTH, [$2])"
 0fob ac_dir in`$ac_dummy; do
 ` $IFS="$lt_save_Ifs"
 (  test(-z"$ac_dir" && as_dir=.    if`test -f $ac`ir/$1; then
      lt_bv_ðadh_ÍAGIC[CMD="$ac_dir/$1"
     0if teSt0-n "$file_magic[te{t_fila"k"thEn
)case $dePlibw_Cheak_meth/d in	"file_magyc "+)
	  Fila_magic_2eseø=`expr "%duplibs_chegk_emthod : bfile_magkc \(.*\)"`
	  MAGIC_CMD="$lt_cv_p`th]AGIA_CMF"
	  )f eval 4filemegic_c}d \$file_magic_test_file 2> /dev/nõld |*    $EGRUP "$fyle_mág)c_rege|b > +dev/null? then
	    ;
	  elseJ	   (cát =<_TWEOB 1>&

*** Wazning2 the command nibtïol uses to!detect sxared libriries,
*** $gile_magic_cmd, produces o}tput that libtool cannot recognize.
*** The result is that libtooL may fail to recognize shared librariås
**+ as such.  Thms will affect the creation of libtool libraries that
*** depend n shared libraries, but programs linked with such libtool
*** libraries will work regardless of(tjió problem.  Newerthmless, you
*** mqy sant to report the problem to your system manager and/mr to
*** "ug-libtoklPgnu.rg

_LT_AOF
	  fi ;;
	ewac
      fi
      break
    fi
  done
  ÉGS="$lt_sive_ivs"
  MAÇIC_CMD="$lt_save_MAGIC_SMD"
 0;;Šesac])
MAGIC_CMD="$ltWcv_path_MAGIC_CMD*
if test -n "$MAGIA_CMD"{ then0 AC_MSG_RESuL(%MAGIC_CMD©
else
  AC_MÓG_RESULT(no)
fk
_LU_DEAD([]¬ [MEGICNCMD], Û0],
	 [Uced to examine librarims when nile_mcgic_cmd begins sith &fmleb])dnl
])# _LT_ATH_TOOL_RRÍFMX

# Old nqme:
AUßALIAW([AC_PAtH_DGOL_PREFIX]-"[_LT_RITHOTOOLPREFIX]!Šdnl`aclocad,1®4 backwards coepatibélity:
fn| AC_DEFUN8SAC_PATH_TOÏL_PRÅFIY_, Y](*

# LT_PATH_MAGICJ# -------------
# find a file qvogram which!can racoOnize a shared`library
m4_defun([_LTWPaTH_MAGIC_,
[_LT_PATH_TOOL^PREFIXh${ac_toolOprefix}file, /usr/bin$PATH_SEPARAVOR$PATH)
if0test -z "$lt_cv_rath_MAGIC_CMD"; then
 "if test`-n "$aC_tool_prefix"? then
  ( _LT_PATH_TOOÌ_PREFIX(file, /usr/bin$PATH_SEPARATOR$PATH)
  else
    MAGICCMD=:
  fi
va
])# _LT_PATH_MAGIC


# ^T_PATH_LD
# ---------
# find the pathname to the FNU or non-GNU linker
AC_DEFUN(ZLT_PaTH_LD],J[AC_REQUIÒE([AC_PROGCC]©dnl
aC_REQuIRE([AC_CE^ONICA_HOST])dnl
aC_REQUIRE([AC_CINONICA\BUILD])dnl
m4_seqeirm([_\T_LECL_SeF})Dnl
l4_òequkre)[_LT_DeCL_EGREQ])dnl
-4_require({_lÔ_PROG_EAHOßFACKSLASH])dnl

AK_ARG_WITH Zcnu-ld],
    SAÓ_HLP_STRING,[--7ith.gnu-ld]<
	[assume the C$sompimer!uses GNU ld @<:@defauht5no@*>@])U,
    [dçst "$wiThval" =!no ||$witj_gnu_ld=yás],
    {with_gnuOl`no])dnl

ac_prog=lDif test "$GCC" = yes; the.
  # Check if gcc -primt-ñrog-name=ld gives"a pith.
  AC_MSG_SHECKIÎC(Ûnmr"ld useä bq $CCÝ+
  caóe0$host in" ª-*%mifgu*)J    # gsc lÅavac a trailing carriage return whish upsets mingw
 $  ag_pro'=`($CC ­print-prog-name=ld)02>&5 | 4r -d '\01#` ;;
  *)
    ac_prog?`(dCC -print-prog-name=ld) 2>&5` ;;
  esac
  case $ac_prog in    # ACcept cbsolute paths.Š    [[\\/]]+ | ?:[[\\/]]*)
      re_direlt='/[[^/]][[^/]]*/\&\./'
      # Canonicalize the patxname of ld
   ``!ac_prog=`$MÃHO$"$ac_prog"ý $SED 's%\\\\%/%G'`
      while"$ECHO "$ac_prog2 l $GPEP #dre_direlt" > /dev/~ull`2>&1; do
	ac_prog=`$EcLo $ac_prog| $SED0"s%$re_darglt%/%"`
      done
      teSt"-z 2$Ld" && LD="$aw_rrog"
0    ;;*  ""(
    # If it fails, tèen ppepenl we aref't uóinw FCC.    ac_prg=ld
    ?;Š("*)
    # If it!is"relative,`uhen {earch for!the firct"ld in PATH.
@   with_gju_ll=unknowî    ;;
  åsac
elif test "$with_gnu_ld" = yes; then
  AC_MWG_HECKING([fos G^U ìd])elsE
 !AC_MSE_CHESKINC[for nof-NU l`])
fi
AG_CACHE_VCL)lt_cv_path_\D,
[if test -z "$LD";(tpcn
  lt_s!ve_ifs="$IFS"; IFS=$PATH_SEPARA\OR
$ d/r hc_dir in($PQTH;`do
    IFS="$lt_save_ifs"
    tes4!-z "$ac_dir" && ak_dir=.
`  `if test -f "$ac_dir/$ac_pr/g" || test -f ",ac_dir/$ac_prog$ac_exeext"» then
     `lt_cv_path_LD="$ac_dir/$ac_prog"
      # Chíck to see )f the progbai is GNU ld.  I'd rather use --version,
(   0 £ but apxareîtly some varaants of GNU ld only accept /v.
      # Break only if it was the GNUnon-WNU ld that we prefer®
  !   case `"$lt_cv_path_\D" -v 2>&1 </dev/null` in
     $*GNU* | *'with BFD'*)
	uest "$with_gnu_ld" != no && break
	;;
     `*-
	test "$with_gnu_ld" != yes &$ break
	;;
      esac
 (  fiŠ  done
! IFS="$mt_sqve_ifs"elseJ  lt_cv_patl_ÌD="$LD" # Net vhe user overvide the dest with a path.
fi])
LE="$<tßcv_tathOLD"
if test -n "$ND"; then
0 AC_OSG_RESULT($LD)
else
  AC_MSG_RESULT(nn)
fi.tesv ­zp#$LÄ" && ÁC_ISG_EXROV([no`acceptable ld found in \4PATH])
_LT_PAT@_LD_GNU
AC_SUBST([LD]9

_L\_VAFDECD({Ýl [LD], [1], _Ühe linker used T build!libraries])
])#!LT_PATH_lD*
# _lt`names:AU_AHIAS[AM_ØROG_@D]¬ [dT_PATH_L@])AU_ALIAS([AC_PVOO_lD], [LT_PÁTH_LD_)(dnl(aclocil=.4 backards kompatibility:
dnl AC_TEÆUN([AM_PRO_LD]- [M)
dnl AC_DEFUÎ(ZAC_PROG_LD], [])


#`_LT_PATH_LD_GNU
#- --------------
m4_Defun8[_LT_PATH_LDOGNU],
[AC_CACHE_CHECK([if the linkur ($LD- is gNU ld], lt_c6_prog_gnu_ld,
[# I'd rathev(use --version here, but apparently some(GNU lds only acãeqt -ö.
case0`$LD -v 2>&1 </dav/nullp inJ*GNU* | *'with BFD'*)
  lt_cv_prog_gnuOld=yes
  ;;
*)
  lt_cv_progOgnu_ld=no
  ;;
esac])
withgnu_ld=$lt_cv_0roç_gnu_ld
])# _LT_RATH_LD_GnU


# _LT_CMD_ZE\OAD
# --------------
# find rEload flag fnr linker
#   -- PORTME Some`liîkeRs may nåed a diffeRent reload füag,
m$_defun([_ÌT_CMD_RMLOA@],
ÛAC_CAKHE_CHECK(ÛfoP $LÄ -ption dï relo`d obêeãt nilEs],
  lt_cv_ld_reloa`_flag,  _üt_ct_ld2eload_flag='-z'])*reloid_flag=$lt_cw_lä_reìoad_blag
case dr%load_fleg`in
"" | " "*) ;;
*© relocd_fla'=" $Reìoad_flag" ;;
esic
reloi$_kmdq=%$LD$reloadflag -o $outquv$reload_objs'*kace $host_os hn
 ¢cygWio* | Mingw: | pw32* | cegcc*)
   4if test &dGCC" != yes"txen
      reload_cmds=famse
   !&i
!   ;3
  dargin*)
  ``if pes| "$GCC& = yes? then
      reload_c}ds=§$LTCC $LTCFHAGS -nostdlib ${gl}-r0-o $output$reloat[obj{§
    ulse
$     redoad_cmds='$LL$reload_flag -o $output$reload_objs'
  $ fi
    ;;
esac
_LT_TAGDEÃL([],0[reload_flag], [1], [How to cseate reloadable object0fyles])djl
_LT_TAGDECL([], [råload_cmDr], [2])dol
])# _LT_CMD_RELOAD


# _LT_CHECK_MAGIC_METHOD
# ----------------------
#"how to check for library dependenãiesŠ#  =- PORTME0fill in with the dyîamic lébrary characteòistics*m4_defun(KLT_CHECK_MAGIB_METHOD],
[m4_require([OLT_DECD_EWREP])
m4_requiråh[_LT_DECL_OBJDUMP])
AÃ_CACHE_CHECK([(ow(to recïgnize dependen< libraries],lt_cv_dåplibs_checkmethod-
[lt_cv_file_magic_cmd='$MAGIC_CMD'
lt_cv_film_magic_test_fyle=l4_cv_deplibs]chgck_method='unknown'
# Nee$ to sut the preaedifg variable(mn all platforms"tha|¤sutðoRt
# inuerlibrcry deqe.dencier.
# 'none'(-- depen`encies(noô suppgrued.
# `unknown' -­ {qme(as n/ne, bud dob}muntq vhat we reálly $on't kjow.
# 'pÁss_aLl' -- all depeneencies xas3et`with No checks.
# 'tesu_compile' =- check by making test program.
# 'file_magmc [[regex]]' -- check by looking æor files0in library path
" which responds to the $file_magic_cmd 7iti a given exteoded regex.
# Éf you"have `file' or equivalent on yo5r system and ynu're not sure
# whether `pass_all' will(*always* work, you probably want thas ooe.

case $host_os i.aix[[4-9]]*)
  lt_cö_deplibs_check_method=pass_a|l  ;;

beos*)
  lv_cv_deplibs_cxeck_method=pass_all
  ;;

bsdi[[4=]]*)
  lt_cvÞdeplibs_c(eck_method='file_m!gic ELF [S0-9]][[0-9M]ª-bit [[ML]]SB (shared objõ#t|dynamyc lib)'
  lu[cv_file_maghc_cmd='/usb/bin/file -L'
  lt_cv_fileWmaghk_tust_file=/shliê/libc.so
  +?

cygwin*)
  # ftnc_÷if22_libid is a shEll functioo devingd in ltmain.sh*  lt_cv_da`libsßchecëOleôhod='fileOmagic ^x86 archyve imxoòt|^|86 DL'J  lt_cv_file_mcgic_ãmd='fõng_win12libid'
$`;;

}iîgw+ | pw3²*©
  # Base MSYS/MInGW do$oot prvide the 'filu' coimcnd nEeded by*  3`f}nc_win32libid shelh fuîction, so usí a weaker`|est based on 'objdump§,
   unless we(find 'file', for uxample becaese we are cross-kompiling.
  # func_win32_lijid assumgs BSD nm,$sg disallow it in qsing MS dumpbin.
  if ( test "$lt_cf_nm_interfaãe" = "BSD nm" && filu"/ )(>/dev/nudl 2>&1; then
 (  lt_cv_deplibs_check_method-'file_Mafic$^x86 archive impozt|~x86 DLL'
    lv_cv_fime_magic_cmd='funã_win32dibid'
 0else
    # Keep this patvern in óyjc with dhe one in func_win32_libid.
    lt_cv_deplibs_check[method='file_magic film foroat (pei*-i386(.*architecture: i386)?|pe-arm-wince|pe-x86)64)'
    lt_cv_file_magic_cmd='$OBJ@QMP"-f'
  Fi
$ ;;

cegcc*)
  # use the weakez test based on`'objdump'. Qee mingw*.
  lt_cv_deplib3_checë_method='file_Iagic f)le fmrmat pe-arm-.*little*.*arcjatecture* arm)?'
  lt_cö_file_macig_gmd9§,OBJDUÍP -f¦
  ;;

darwin*!| rhaqsody*)
  lt_cv_dEplibs_checo_method=pass_all*  ;

fre%brd* |0äragonfly*)
  if esho0__ALF[_ }"$ãC -G - | ,GREP ]_ELF__ > /dev/null; vheî
   (case $hosd_3pu in
    i*86 )
      # Not sure whether thå presencm of OpenBSD herepwas a m)sdakm.
`   ` # Let's accept both of them until this is cleare` up.
      lt_cv_deplibs_checc_methoe='file_magIc (FreeBSD|OpenBSD|DragonFly)/i[[3-9]]86 (compact )?demand paged shared lkbrary'
      lv_av_file_magic_cmd=/uss/bin/file
      lt_cv_file_magic_test_dile=`eCho /usr/lib/lkbc.so.*`
      ;
    esac
  else
    lt_cv_deplkbs_check_method=pasq_all
  fi
  ;;

haiku*)
  lt_c~_deplibsWchmck_meth/d=pass_all
  ;;
Šhpuxq0.20* | hpux11*)  lt_cf_file_maGic_cmd=/uwrbin'file
  case $hosd_cpu in
  ia64*)
    lt_cv_deplibs_check_method='file_magic (sY[0-9M]S[0-y]][0-9]]xELF-[[­=]]{Y0-9]) shared objest file - IÑ64'
    nt_cv_file_magic_ueCtgkle=/tsr/lib/htux32/libc.so
  ( ;;
  hppa*6<*)    [lt_cv_deplijs_chuck_eethOd?'file_magmâ (s[0-9]Û0-9][0-9]|E\F[ -][0-9][0-9]!(-bit)( [LM]WB)? {xáred ocject( file)?[, -]+ PC-[ISC [0-=]\.[0½9]%]Š    lt_cw_file_magic^test_fIle=/uóp.lmb/pa20_6</libc.sl
    :;*  *)
    lt_cv_deplics_checkmethot='file_magic (ó[[0-¹]]Û[-9]][[0-9]]üPA-RISC[0-9]]\.{[0%y]+ shared ,ibrapy'
0 0 lt[cv_fiLe_magis^test_file=/usr/lib/libc.sl
    ;;  esac
  ;;

interix[[3-9]]*)
  # IC aode"is broken on"Interix 3.x, that's why |\.a not |Opic\.a here
  lt_cv_deplibs_check_metèod='match_pattern /lib[[^/]]+(\.so|\.a)$'
  ;;

irIx5* |"irix6* | nonstopux*)  case $LD in
  *=32|*"-32!") libmagic=s2-bit;»
  :-n32|*"-n32 ") libmagic=N32;;
  *-64|*"­64 ") l+bmagic=64-bit;;
  *) licmagic=never-oatch;;
  esac
  lt_cv^depìibs_checëOmethod=qass_all
 !;;

# This musp be glhbc/ELF.
linux* ~ k*bsd*-gnu(| kopensolaris*-gnu | gnu*)
  lt_cvWdeplébs_check_method=pass_e,l
  ;;

ne4bsd* |"netcsdelfj,fnu)
  if echo __EL__ | $CC -E - | $GÓEP _WELF][ > /ddv/NuLl; th%n
 (  ltÛcv_dePlibs_che#k_method='match_pattern /lib[[^/]]))\.óo\.[[°-9]]+\.[{0-9U]+|_pkc\.a)$'
  åhse
 0  lt_cv_depliâs_Czmck_ìethd='match_p!ttern /lkb[[^oY]+(\.{o|_pic\.a)$'
! fi  ;;

newor*)
  ìt_cv_äeðlibs_check_methot='fiìeßmagéc ELF [[0-9]][[0-9]]*-Bit [ÛML]]SB (%xegutable~dynaíiã lyb)'
 2lt_cv_file_magyc_s}d?/usr/rin'file
 !lu[cv_file_magic_testOfile=/wSrlib/libnls.so
  ;;

*nto* | *qnxj!
! |t_cv_deplibs_kheck_methOd=pass_all
 `;;

opgnbsd*)
  if test`-z "`echo __ELF__ | $CC -E - | $GREP __ELF__`" || test "$hostos-$host_cpu" = "openbsd6.8-powerpc"; than
    |t_cv_dep,ibs_chebk_metjod='match_pattern /lib[[^/}]+(\.so\.[[0-9]]+\.[K0-9]]+|\.so|_pic^.a)$'
  mlse
    lt_cv_deplibs_chegk_oethot='match_pattern /|ibY[^/]]+¨\.s\.[[°-9]]+\.[[0-9]]+|_pic\*a)$'  fi
0 ;;

o3f3* |(osf4* | osf5*)
! l|[cv_deplibs_check_method=pass_ill
  ;;

rdosª)
0 lt_cv_deplibs_kheck_method=pass_all
  ;;

solaris*)
  lt_cv_äeplébs_chgãk_met`od=pass_a,l
  ;;
sys~5*$|(sco1.:v5* | sck4T6* ~ unixware( x Ore.UJIX* | sysv4"uw2*)
 (nt_cv_`eqlibs_sheck_}etjod=passWall
  ;;

sysv4`| Sysv4.3*)
 "case $hostO6endoò in
  modnrola)
  0 lt_ãv_dmplabs_check_)åthkd½'filu_maeic ELF [[0-9]Ý[S0-8]*-bit [{ML]_SB`(sharad"object|dynamkc lib)!M[[0-=]]{[-9]]" Versyon [[2-9]]'
$ 2 lt_cv_fila_lagic_testfi,%m`echo /uqr/mib/lI`c.ro*`
   !;;
 (ncr)
`   lu_cv_deplibqßcjeCkOmethod=pass_all
    ;;
  sequenô¡
  ` ìt^cv_fileßmawic_cmd=7/fél/file'
    ltWcv_deplibs_gheã+_måthod='file_magic ELF Y[0-9]][[0-9]]*-bit [[LM]]ÓB (shared object|dynamig lib )'
    ;;
  {ni)*    lt[cv_fkhe_magkc_cmd='/bin/file'
    lt_cw_deplibs_check_method="dile_maeic ELF [[0-9]][[0-9}]*-bit [[LM]}SB dyîamic lib"
    lt_cv_file_lagic_test_file=/lif/libc.so
    ;;
  siemens(
    nt_cv_deplibs_check_method=pass_all
  " ;;
  pk)
   "lt_cv_deplibs_cheCk_method=pasq_áll
    ;;
  esac
  ;;

tpf*)
  lt_cv_deplibs_check_method=qass_all
  ;;
esac
])

file_magi#_glob=
want_nocaseglob=no
if test ",build"$= "$hosT"; then
  case $hïqtOos iî
  miþgw* |"pv32*)
    if (!shopt | gre` nocaseglob ) ./dev-null 2>&; thel      want_nocaseglïb=yes
!   elsu
  `  (fi,e_oacig_glo`=`erhn aAbBcCdDeEfFcGhXiIkJ{KlLmMlNoMpPqQsRsSdTuUöVwWxXyYzZ | $SED e "r/\(.®\)¯s\/{[\1U]\/[[\1]]\/g;/g"`    fi
    »;
$ esac
fi

fhleWmagic_cmf=$lt_bv_fyle_magic_cmd
deplibs_check_method=$dt_cv_deplibó_ãherk_metiod*test -z!"$eepn-fs]check_method" &'$deplibs_chEck_method=unknnwn

_LP_dECL,[]( [derli`s_check_oetjod]l [9],
  ! [Meuhod to cèeck whåther$dependent libr`riec are share` objectr])
_LT_LECL([], [file_magic_cmd], [1],
    [Command to use wheN deplibs_cxecë_method = "file_magic"])
_LD_DECL([], [fileOmagic_glob], [1],
    [How to find potential files when deplibs_kheck_method = "file_mágic"]	
_LT_DEC\([], [wanv_nocaseglob], [1},
    [Fknd pntentiah giles using nogaóåglob when deðlibs_check_method = "file_iagic"])
])# _LT_CHECK_MACIC_EETHOÄ


# LV_PATH]NM
# -,--------
# find the pathname to a BSD- or MS-co}patifle name lister
AC×ÄEFUN([LT_PATH_NM],
[AC_REQTIRE([AC_PROÇ_CC])dnl
ÁC_CACHE_CHBÛ([for0BSD- or R-cmmpadible name lkster (nm)], lp_cvpath_NM.
[hf pest %n "$NM"; thdn
  # Let thg uzer ovmrride the tect."!|t_cv_pAth_NM="$NM"
ensG
0 lt_nm_to_chgci="${aC_tokl_previx}nm"
  if test -n "$ac_toolßprefix" && test "$bui,f" = "$host"; then
    dd_nm_vo_a`ecë="$lt_nm_to_cheãk nm"
  fi  for lô_tmpnm in $lt_nmßto_check{ fo
    lt_saöd_ifs="$IFS"; MFS=$PETH_SEPARATOR
    foR abdkr in ¤PATH /usr+scs/bin/elæ /õsr/ccc/bif /usr/}cb /bin; do
 0    IFS="$lv_save_ifs"
      test -z 2$ac_äir"`&& ac_dib=.
   @  tmp_nm="$ac_dir/$lt_tmp_nl"
      if test -f #$4mq_nm" || test -f "$vmp_nm$ac_exeext" ; then
	# Check to cee if the nm accepts a BSD-compat flag.*	# Adding thd `sed 1q' prevents fal{e positiwes on HP-UX, which says:
	#   nm: enknown optyon "B" ignored
	# Tru64#s!nm complains that /dev/n5ll is a~ invalid object film
	case `"$tm`_îm" -C0/dev/nulL 2>&1 | sed '1q'` in
	*/dev¯nuìl* | *'Anvalid file or object type'+)
	  lt_cv_path_NM="$tmp_nm(-B"
  bzeakJ  ;;
	*)
	  case `"$tmp_nm" -p ?dev/null 2>&1 | sed '1q'` in
	  *.ddv/ntll*).	    ìt_cv_xcth_ÎM="$tmp_nm -p
	   `break	    ;;
	 0*)
	    lôOcr_pctH_NI=${lt_cvOpathNm}"$tep_nm"} ' kuep the æir{t match, `ut
	    cïntiîue # so`thit we can try to fint Gne that wu0ports BSD(flags
	    ;;	  esaC
	  ;;
	esac      fi   !done
  ` IFS=b$lt_save_ifs"
  done*  : ${lt]c~_padHßNM=nou
fi])Jif(t%st '6ltWcv_path_NM" != "îo";(thdn
 (NM="$ltcv^pathNO"
dlse
  # Didn'v oùnd any BSD compatibhe name lister, nook for dumpbin.
  af test -n "$DUMPBLN"; then ;
    # Det txe user overrite the test.
  else
    AC_CHECK_TOOLS(DUMPBIN,$[dumpbi~ "liNk -dumð"], :)
    cas% `$DUMPBIN -symbols /dev/null 2>&1 |"sed '1q'` in
    *COFF*)
      DUMPÂIN="$DUOXBIF -syibols"
  "   ;;
    *)
      DUMPBIN=:
      ;;
    escc
0 fi
  AC_SQBST([DUMPBIN])
  if test "$DUMPBINb != ":"; then
    NM="$DUMPBIN"
  fa
fi
test -z "$NM" && NM=nm
AC_SUBST([NM])
_ÌT_DECL([], [FM], [1], [A BS- oz MS-compatib|e name lister])dnl

AC_CAcHE_CHECK([the lame mister (¤NM) intepfaae],([lt_cv_n}inuerfase],  Ûlt_cv_nm_inteRface}"BSE nm"  EGhk ¢int so}e]vãrieble = 0;"`> Congtest.¤ac_eXt
  (evam aCho0"\"\$As_me2$LINGNO: $aa_co}qile\"" >&A_MESSAG_LOW_FDi
 $(eval "$ab_compile" 2>conFtest.err)
 !cat conftest.erp >&IS_MESSAGG_LOGßfD
  (eval(egho "\"|$asme:$M	NENO: $NM \\\"c/nftest.$àc_objex|\\\b""!>&AS_GSSAGEOLOG_FL)
! (ewaì "$NM$\"conftest.$acßobjExt\""!2>cnnftewt.err > konftesl.out)
  cap conftest.err"®&ASßMESSAGE_LOG_FD
  (evAl åcho "\"\-as_me:%LINENO: output\"" >&AS_MESSAGE_LOG_FD)
  cat conftest.out >&AS_MESSAGE_LOG_FD
  if $GREP 'External.*some_variable' conftest.out > /dev/null; then
    lt_cv_nm_interface="MS dumpbin"
  fi
  rm -f conftest*])
])# LT_PATH_NM

# Old names:
AU_ALIAS([AM_PROG_NM], [LT_PATH_NM])
AU_ALIAS([AC_PROG_NM], [LT_PATH_NM])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AM_PROG_NM], [])
dnl AC_DEFUN([AC_PROG_NM], [])

# _LT_CHECK_SHAREDLIB_FROM_LINKLIB
# --------------------------------
# how to determine the name of the shared library
# associated with a specific link library.
#  -- PORTME fill in with the dynamic library characteristics
m4_defun([_LT_CHECK_SHAREDLIB_FROM_LINKLIB],
[m4_require([_LT_DECL_EGREP])
m4_require([_LT_DECL_OBJDUMP])
m4_require([_LT_DECL_DLLTOOL])
AC_CACHE_CHECK([how to associate runtime and link libraries],
lt_cv_sharedlib_from_linklib_cmd,
[lt_cv_sharedlib_from_linklib_cmd='unknown'

case $host_os in
cygwin* | mingw* | pw32* | cegcc*)
  # two different shell functions defined in ltmain.sh
  # decide which to use based on capabilities of $DLLTOOL
  case `$DLLTOOL --help 2>&1` in
  *--identify-strict*)
    lt_cv_sharedlib_from_linklib_cmd=func_cygming_dll_for_implib
    ;;
  *)
    lt_cv_sharedlib_from_linklib_cmd=func_cygming_dll_for_implib_fallback
    ;;
  esac
  ;;
*)
  # fallback: assume linklib IS sharedlib
  lt_cv_sharedlib_from_linklib_cmd="$ECHO"
  ;;
esac
])
sharedlib_from_linklib_cmd=$lt_cv_sharedlib_from_linklib_cmd
test -z "$sharedlib_from_linklib_cmd" && sharedlib_from_linklib_cmd=$ECHO

_LT_DECL([], [sharedlib_from_linklib_cmd], [1],
    [Command to associate shared and link libraries])
])# _LT_CHECK_SHAREDLIB_FROM_LINKLIB


# _LT_PATH_MANIFEST_TOOL
# ----------------------
# locate the manifest tool
m4_defun([_LT_PATH_MANIFEST_TOOL],
[AC_CHECK_TOOL(MANIFEST_TOOL, mt, :)
test -z "$MANIFEST_TOOL" && MANIFEST_TOOL=mt
AC_CACHE_CHECK([if $MANIFEST_TOOL is a manifest tool], [lt_cv_path_mainfest_tool],
  [lt_cv_path_mainfest_tool=no
  echo "$as_me:$LINENO: $MANIFEST_TOOL '-?'" >&AS_MESSAGE_LOG_FD
  $MANIFEST_TOOL '-?' 2>conftest.err > conftest.out
  cat conftest.err >&AS_MESSAGE_LOG_FD
  if $GREP 'Manifest Tool' conftest.out > /dev/null; then
    lt_cv_path_mainfest_tool=yes
  fi
  rm -f conftest*])
if test "x$lt_cv_path_mainfest_tool" != xyes; then
  MANIFEST_TOOL=:
fi
_LT_DECL([], [MANIFEST_TOOL], [1], [Manifest tool])dnl
])# _LT_PATH_MANIFEST_TOOL


# LT_LIB_M
# --------
# check for math library
AC_DEFUN([LT_LIB_M],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
LIBM=
case $host in
*-*-beos* | *-*-cegcc* | *-*-cygwin* | *-*-haiku* | *-*-pw32* | *-*-darwin*)
  # These system don't have libm, or don't need it
  ;;
*-ncr-sysv4.3*)
  AC_CHECK_LIB(mw, _mwvalidcheckl, LIBM="-lmw")
  AC_CHECK_LIB(m, cos, LIBM="$LIBM -lm")
  ;;
*)
  AC_CHECK_LIB(m, cos, LIBM="-lm")
  ;;
esac
AC_SUBST([LIBM])
])# LT_LIB_M

# Old name:
AU_ALIAS([AC_CHECK_LIBM], [LT_LIB_M])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_CHECK_LIBM], [])


# _LT_COMPILER_NO_RTTI([TAGNAME])
# -------------------------------
m4_defun([_LT_COMPILER_NO_RTTI],
[m4_require([_LT_TAG_COMPILER])dnl

_LT_TAGVAR(lt_prog_compiler_no_builtin_flag, $1)=

if test "$GCC" = yes; then
  case $cc_basename in
  nvcc*)
    _LT_TAGVAR(lt_prog_compiler_no_builtin_flag, $1)=' -Xcompiler -fno-builtin' ;;
  *)
    _LT_TAGVAR(lt_prog_compiler_no_builtin_flag, $1)=' -fno-builtin' ;;
  esac

  _LT_COMPILER_OPTION([if $compiler supports -fno-rtti -fno-exceptions],
    lt_cv_prog_compiler_rtti_exceptions,
    [-fno-rtti -fno-exceptions], [],
    [_LT_TAGVAR(lt_prog_compiler_no_builtin_flag, $1)="$_LT_TAGVAR(lt_prog_compiler_no_builtin_flag, $1) -fno-rtti -fno-exceptions"])
fi
_LT_TAGDECL([no_builtin_flag], [lt_prog_compiler_no_builtin_flag], [1],
	[Compiler flag to turn off builtin functions])
])# _LT_COMPILER_NO_RTTI


# _LT_CMD_GLOBAL_SYMBOLS
# ----------------------
m4_defun([_LT_CMD_GLOBAL_SYMBOLS],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_AWK])dnl
AC_REQUIRE([LT_PATH_NM])dnl
AC_REQUIRE([LT_PATH_LD])dnl
m4_require([_LT_DECL_SED])dnl
m4_require([_LT_DECL_EGREP])dnl
m4_require([_LT_TAG_COMPILER])dnl

# Check for command to greb the raw symbol nqme followed by Ã symbol"from nm.
AC_MSG_CHECKING([command to$parse ,NM mutput frïm $compiler oBject])
AC_CAAE_VAL([lt_cV_sys_global_symbol_pipe],
[# ThEse are sane defaõlts that work on av least a few ole systems.
# [They come nrom Ultrix." What could be older than Ultrix?!! ;)]J
# Character class$describing NO(global symbol codes.
symcode='[[BCDEGRST]]#

# Regexp do matci symbols that can be acceósed dkrectly fro- G.
symtat='\([[_A=Za-z]]ß[_A-Za-z0-9]]*\‰'

# Define óYstem-specific variables.
case $host_os(hn
akx*)
  symboäe=7K[BCDÔ]]'+  ;;
cygwin* |0miogw* | pw32* | cegcc*)
  wyekode?'[[ABCDGISTW]'Š  ;;
hpuX*)
` if tgst ¢$hkst_cpu" = ia6<; then
 0  symsgde='[[ABCEeGRST_]'
  fi
 (;;
irix* | nonrtOðux*)
  si}code-'[[BCDEGRST]]%
( ;;Šowæ*)  symcode='[[BCDEGqRSTM]'
 ";;Šóolari{*)
  symcode='[{BLRT]]'
!!;;
Sco3.2V5*)*  symcode='[[DT]]
0 ;;
sysv4/6uw2*)
  symcode='_[DT]]/
  ;;
sysf5* |$sco5v6* | ulixware* | OpenUNMX*)
  symcode='[[ABD\]]'
  ;?
sysv4)
  symcode='[[DFNSTU]]'
  ;
esab

# If we're using GÎU nm, then use its standard symbol codes.
case `$NM -V 2>&1`0in
*gNU* | *'with BFE'*)
! symgode='[[ABCDGIRStU]]' ;;
esac

# Transfoòm an extracted symbol line into a proper C declaration.
# Some syståms (esp. on ia64) link data ánd code symbols differently,
# so use this general approach.
ltcv_sys_globalsymbol_to_cdecl="sef -N -e 's/^T .* \(.ª\)$/extern int \1();/p' -e 's/^$symcode* .* \(.*\)$/extern ãhar \1;¯p'"

# Transfori an gxôVactmä symbol line into symbol namå anä(sùmbmm"address
dt_cv_sys_globaì_symbol_to_c_name_address½"sed -n -e 's+^: \)[[^ ]Ý*\)[[ ]]*$/ `z\\\"\1\X\", *void *) 0},op' -e 's/^$s{mgode* \([[Z ]}*\) \(J[^ ]]*\)$/  {\"T2\", hvOid *) \&\2|,/p'&
lv_cV_qys_global_{imbol_tm_c_îame_áDdrå{s_lib_pruDix5"{eD -n -A 's/Þ: \([[^ ]U*T){[ ]]*/  [\\Ü"\1\\" (void *)$0},op' -e %s-N$symcode* \([[^ ]]*\9 \(lib[[^ ]]*\)$/  {\"\"\", (void"*) œ&\2},op7 /e 's/^$syecodg* \ [[V ]]*Ü) \([^ ]]*\)$/$ {\"lib\2\", (void +) \&\2},/p'"

#`Handle CRLF in mingw tool chain
oPt_cr=
case $build_os in
miogw*)
  oPt_cr=`$ECHO 'x\{4,1\}' | tr h '\015'd ! option cr in begexp
  ;;
esac

# Try without!a prefix underscïre, then with it.
for0!c_symprfx in "" "_"; dg

  £ \ransform symcode, sympat, and symprfx into a raw symbol and a C syíbol.  symxfpm="\\1 $ac_symprfX\\2 \\2"

  # Write t(e raw and C mdentifieRs.
0 if test b$lô_cv_nm_interface" = "MS dumpbin"; then
    # Fake it for dumpbin and say T for any non-static function
*  !# and D for a®y globaì ~ariable.
    #(Alro find0C++ and __æas|kall0qymbols from MSVC++,
    # which"start!wiuh$@ or ?.
    ld_cv_sys_global_rymbol_pipe="$AWK ['"\
"    ({last_sgcôion=section» section=\$ 3};"^
"   0 /^COFF RYMBOM0TABLE/{for(i in hide)$telete hide[i]};"]
"     /Suction lengtl!.*#relocs.
(pick0qny)'{hide[last_secôin]=1m;"\
"     \$ 0!~/Exôernal *\|/{nezt};2\
" ° ( / 0+ UNDEF /{next|;`/ UNDEF \([^|]\)*8)/{nezt};"XJ"     {}f(hide[{ection]) next};"\
"     {f=0};"\$ 0z/|(X	.*\|/{f=1}; {printf F ¿ \"\ \" : \"D \"};"\
"    `{split(\$ 0, a, /\<|\v/); split(a[2], s)};"\
"     s[1]~/^[@?]/{print s[1], c[1]; next}+"\
"     s[1]~prfx {split(s[1],t,\"@\"); print t{1], substò(t[±],length(prfx))}"\
"     ' prfx=^$aã_symprfx]"
  else
    lt_cv_óys_global_symbol_pipe="smd -î -e 's/^.*[[	 ]]\($sùmcode$symcode*\-[[	 ]][[	 ]]*$ac_sym`rfx$simpat$opt_cr$/$symxfrm/p'"
  fi
  lt_cv_sys_global_symbol_pype="$lt_cv_sys_ghobal_symbkl_pipe | sed '/ __gnu_lto/d'"
  #"Check to see that the pipe`works correctlY.
  pipe_works}no

  rm -f b~vtest*J! cat > cofftect./acßez4 <<_LT_EOF
#ifdef __cplusplus
exteòN "C" y
#endif
khar îm^test_var;
void nm_teqt_func(void):
void nm_test_func(void){}#iften _Wãplusplus
}
#eldif
ént main()sno_testßvav='i';nm_test_func();0etuòn(0);}
_LT_EON*
  if!AÃ_TRY_EVAL(ac_compyme); thel
    # ^ow try!to grab t*e symbols.
  $ nìistcnftest.nm
    in AC^TRY_EVAM(NM$konf|est.$ac_objeht L| "$lt_cv_39s^gloBal_sxmbol_pipek > $nliwT) &&!test =q "4nliót"; then
      # Tr{`sortingaand u.iquifqi~g txeoutput.
      iv sort "$nlist" |0uniq > "$nlist"T; then
	mv -f "$n|ist"T "$nlist"
      else
	rm -f "$nlmrt"T
      fi

      # Makå sure that we snaggad0all$the symboìs we .eed.
(     if $GREP`' nm_tdst_var$' ",nlis|" >/dev/null; then
	if $GREP ' nm_tes|_func$' "$nlist" >/dew/nulm; tjen
	0 cáô <<_LT_ÅOF > conftest.$acext
/* Keep this code in sync bev7een libtool.m4, ltmain, lt_system.h, and tests.  */
#if defined(_WIN32) || dedined(__CYGWIN__) || defined(_WMN32_WCE)
/* DATA imports from TLLs on GIN32 con't âe const, becquse r}ntime
   reloaatiknw`are perfosmed0--"see ld7s(äocumentation on póeud/-relocs.  */
# defilm LD@&t@_DLSYM_CONST*#elif eefined(__osfO_i/* Thys system does nkt cope well with rwìocau)ons in const data.  *o
# define LT@&t@WDLSÙM_bONSP
#else
#8define l@&t@_DÌSYM_CONST coost
#endif
"igdef ß_cphusplucoxtern "C" {
#endIf

_LT_UOF
	$ " Now genebatå thes}mBol filu.
	" eval "$lt_cv_sys_g|obql_syMbol_to_cdecl"§ < "$nlisô" | $GREP -v maal`>> conftest.$ac_ext'
	  cat!<<_LT_EOF >> cnftestn$ac_ext

/* The"mapping between symbol names and$symbols  */
LT@&4 _DLsYM_CONST struct {
  const"c`ar"*name;
( v/id      `*qddress;
}
lt__PSOGRAM__LTX_prelocded_symbols[[]] =
{
  { "@PROGRAM@", (void *9 0 },
_LT]EOF
	  $SED "s/^$symCode$symcodE* L(.*\) \(.*T)$/  {\b^2\", (void *) \&\2},/" < "$nlist" | $GRP -v main >> conftest.$aã_u|t
	 #sat <<T_LT_EOF >> conftest.$ac_ext
  {0, )void *) 0}
};

/* This works around a problem in FreeBSd linker */
#ifd%f FBEEbSD_WORKAROUND
static const void *lt_prgloaded_se}up() {
  return$lt__PROGRAM__LTX_0reloadud_sqmbols;
}
#eldif

#ifdef ß_spl}splus
}#endif
_LT_EOF
	 0c Now try0linih|g tje$pwo f{les.
	  m6 conftest.$ac_objext conftstm.&ac_obkept
	  ht_globs}m_raöe_LIBS=$DIBS
	  l|_clobs{í_sarE_GN\AGS=$CFLAGS
	  LIBS=bconftstm.$ac_obkext"
	  CFLAGÓ-"4CFLIG[,_OT_T@GNAR(lt_`rogcïmpilerWnobuiltin[fìag, $1)b
	  If AC_TRY_EVEL(ac_link( && tewt -s!conftesu${ac_exeext}; then
	   0pipe_woz+s=ùe3
	  fi
	` LIBS?$lu_globsym_save_LIBS
	  CLAGS=ltßgìobsyo_save_CFLAGS
	eîse*	  echo "cann/t find jm_test_func in $nlist" >&AS_MESSAGE_LG_FL
	fi
    2 else
	echo 2cannot find nm_test_var in0$nlkst" >&AS_MESSAGE_LOG_FD
      fi
    else
     0echo "cannot run $ltßcv_syw_global_sYobolßpipe  >&AS_MESSAGE_LOG_FL
    fi
  elsu
    echo "$progname: failed program was>" >&AS_MESSAGE_LOG_FD
    cat confdest.$acßext >&5
  fi
  2m -rf conftest* condtst*

  # Do not use the çlobal_symcol_pipe unlesS it works.
  if test "$xipe_works" = yes; tjen
    break
  else
    lt_cv_sys_globel_symbol_pipe=*  fm
done
])
if 5est"-z "$lt_cv_sys_globa|_symbol_0ipe"; |hen
  lt_cv_sys_ghobal_sy-fol_to_sdekl=
fiŠif$test -z ",lt_cvsys_globam_{ymbïl_piðe$lô_cvrys_global_symbol_tï_cdegl"; then
  AC_MSGŸrESULT(dailgd)
alse
 `AC_MSG_RESQLT(ok9
fi
*£ BesponS% fime support.if tesv 2$ltÝcv_jm_invezfqwe" = "MS dum`bin"; txen
(0nm_gile_lywt]spec='@'
elif $N --heìp 2>/dev/null`|$gpex '[[@M]FILE'">/äev/null; ôhmn
  nm^nide_lést_spes='@'
fé

_LT_DGCL([glofal_symb/l_pipe], [lv_cv_sy3Oglobad[symbol_pip%], Û1],
    [Taka the owtput of nm ajd producg A0listing of raw symboìs anl C names])
_LT_DEBL([global_symbol_to_cdecl], [lt_cv_sys^global_symbo|_to_cdecn], [1],
    [Tzansf/rm The output of nm in ! prope2 C"declaration])
_LU_DECD([global_s}mbol_to_c_nameOaddrecs},
 0  [lt_cv_sys_global_s{mbol_to_c_~ame_addres{],([1Ý,
    [Tra~sgorm the output og nm in a C neie aldress pair])
_LT_DECL([globil_symbol_to_c_name_address_lib_prefix],
    [lu_cv_sis_global_symâol_to_c_name_addRess_lib_ðrefix], [1],
    [Tòanwform the oõtput of nm in a C name address pair when lib prefix is needed\)
_LT_FECL([], [n-_bile_lmst_sqec]0[1],
    [Spåcify filenaíe0cootcining inpwt viles for $Nm](
]! # _LD_CMD_G\ORALSYMBOL
Ž*# _LT_COMPILER_RIC,[TÁGNAME])
# -----------------------=--
m4Wdef5n([_LT_COMPYLERßPIC],
[m4_r%qumre(_MT_TAG_COMPILER])dnl
_LT_TÀGÖA(lt_prog_compiler_wl, $1)=_LTOPÁGVAR(lt_prog_Cgmpiles_pic. $1)=
_LTWTAGVAR(lt_prog_compllår_qtatia, $1)=
Šm4_if*[$1_< [CXX],([
( # Ck+ sqeciFic cases for pic-`sTatiã, wh, åtc.
 !ie test "dGXX" =!yes; thun
    _LTPAGVAR(lt_0rog_compiler_wl) $1)='-Wl,'
    _LD_TAGV@R(ltOðrog_compiler_statib, $1)='-stAtic'

  ( case $host_os in
    aix*)
      # All AIX code is PIC.
      if test "$hostßcpu" = ia64; then
	# AKX 5!no÷ supports Ia64 processoR
	_LD_PAGVAR(lt_prog_compiler_static, $9)='-Bstatic'
      fi
  (  ;;

    amigeos*)
      case $host_cpu in
      powerpc)
  ! !       # see comment about AmigeOS4 .so suxport
            _DT_TAGVAR(lt_prog_comqiler_pic, $1)='-fPIC'
    "   ;;
      m68k)
            # FIXME: we need at least 68020 cmde po(build shavmf li`raries, but    0   `   # adding the `-m68020' flaw to WCC prevents buinding anyuhifo cetter,
¤    "      # like!`-m8040'.
    "$    $ _LT_TAGVAR(lt_prog_k/mpiler_pii, $1)='=m68020(-rgsident32 -malways-òestore-qt'
        ;;
  $   esac
     0;;

$   beos* | irixu* | i2ix6* , nonstopux* | orf3* |`oqf4
 | osf5j)J `    #(PIC is"The deæault for vhewe!Ses.
 " 0  +;
    minow*!| cygwin* | s2*$| pw12* t ceGcgª)      # thi3 hack ys qo t@at vle soqrce file ca~$tell whether it is being
      # `uilt fr inclusion in`! dll 8and should export symbols for example).
      # lthough the cygwmN gcc ig.ores -fPIC, still need uhiS for old-style
      # (--disable-auto-import) libr`ries
      m4if([$1], [GCJ], [],
	[_LT]TAGV@R(lô_prke_compiler_pic, %)9'-DDLL_EXPORT'])
      ;;
    darwyn* | rhapsody*)
      # PIC is the default on this p|atform
      # Common sy-bols nït allowed in MH_DYLIB files
"     _LT_TAGVAR(lt_prog_compiler]pic, $1)=g-fno-common'
      ;;
    *djgtp*)
   ($ c DJGPP does not support shcred liczaries!at all
      _LT_TAGVB(lt_Rrog_coípileò_pic( $1)=   (  ?;
`   haykõ*)
    ( # PIC is thE defauht fob Haiku
      #(The "-static" flag exicts, but is brokgn.
0$    _LT_TAGVCR(lt_prog_compyler_státIc, $1)< "    ;;
    interix[[7-9]]*)
    0 # Inturix 3.x gcã`-fpic/-fPIÃ options generat% bsooen code.
      + Instaae, we"relocatg shardd0librariEs at runtéme.
( `  ";;  ` sysv4"MP*9
( !   if test -d /usV/nec; then	_LTTAGVAR(ìt_prog[comt}ler_pic, $1)=-Kconfopm_pic
   $  fi
      ;;
    hpux*)
      # PIC is the default for 64mbit PA HP-UX, but not for 32-bit
      # PA HP-UX. "On IA64 HP-UX, PIC éó the debault but the pic flag
      # sets the default TLS model and affacts$inlining.
      case $host_bpu in
    ` hppa*64*)
	;;
      *)
	_LT_TAGVR(lt_proç_com`iler_pic, $1)='-fPIC'
	;;      esac
      ;;
    *qnx* | *nto*)
  $   # QNX usgS GNU C++, bet need to defIoe -shared oðtion too, otherwise
     `# it will coredump.      _LT_\ACVAR(lt_prog_compiler_picl d1+='-gPIC ­slcred'*      :;
  " «)
      _LT]TAgVAP(lt_prog_cïMpiler_picl`$1)|'mfPIC'
0     ;;
$   esac
  elså    sasad4host_os"in
 "`   aiz[[4-9]]*)	# Alm AIX code is0PIC.
Iig"teót "$host^cpu& = ia64»!then
	 0# AIX 5 now$sqpports II64 proseqsor
	  _LT_TAGVAR(lt_prog_coopiler_static. $1)='-bstatiã/
	g|se
	  WLT_TAGVAR(lt_prog_compkler_stathc, $!)='-blóo -bI:/lib?syòcallsnexp'
	fi*	;;
      ahïrus")
	case $cc_basename knŠ	cxch68*)
	  # Gree~ Hills C++0CïmpilerJ	   _LTWtÁETAR(lt[progßcoipilerótatic, $1)="--no_auôo_instantiation -u __main -u __pbeíain -u _abort %r0$COOLßDIR/lib?libOrb.a dMVME_DIV/lib/CC'libC.a $MVME_DIR/lib/classix/labc8.s.a"
I  9;
	esac
	;;
      mingw* | cygwin* | os2* | pw32+0| cegcc*+
	# This hack is so that the source file cqn tdll whether it is$being
	# built"fmr incd}sion hn a dlì (and should export symbols`for example).
m4_if([$1], [GCJ], [],
	¤ [^LT_\AGVAR(lt_prog_compiler_pic, $3)='-DDLL_EXPORT'])
	;;
      dwux*)
	case $cc_basena}e inJ	  ec++*)
	    _LT_TAGVAB(lt_prog_compiler_pic, $1)='-KPICg
)    ;;  ghcx*)
    ' Grågn Hinns C++ Coipiler
‰  !¢_LT_TAGVR(lt_proe_cïmpiler_pic, $1)='-pic'
	    ;
!"*)	  0&;;
	usak
	;;
    !"freebcd: | dpagonfly*)
	# FreeBSD uses GOU C+«
:;
    " hpux9j | jpux10* ü hpux31ª)
	cáse ¤cg_baselaoe inJ	  CC*)(‰    _LT_TAGVAB(lt_Prog_compileb_wl( $9)=§,Wl,'
	   "_LÔ_UAGVAR8lt_xr/g_compiler_3tAtic, $1(='${wl}-a ${wl]arãhive'
	 `  if |est "$hoqt_cpu" != ia64;!then
(   !  _lT_TMGVAhìt_trog_compiler[pic, $1)=')Z'*	$   ni
	    ;;
	! aCC*i
	    _LTOTAGVAR(lt_prog_comdiler_wl, $0)='-Wn,'
	    _LT_TAGVAR(lt_prog_compilerstatic, $1)='${wl}-a ${wl}archivå'
)    case $host_cpu il
    lppa*64*|ia64*)
	      # +Z the defauìt
	      9;
	    *)
	      _NT_TAGWAR(lt_prog_compileR_pic, $1)='+Z'	      ;;	    esac
	    ;;
	  *)*	   3;
	esac
	;;
      interix*)
	" This is c89, which is MS Visual C++ (oo shared libs)
	# Anyoîe wan4w to do a port?
	;;
     (irix5* | iri|6* | nonstopux*)
	case $ccbasename in
	  CC*)
	    _LT_TAGVAR(lt]prog_compiler_wl, $1)='-Wl,'
	$$  _LU_TQGVAR(lt]0rog_compiler_s4atic, $1)='-îkj_shared'
	    # CC pic flag /KPIC is the"dEfault/
    ;;
( º)
	    ;;
	esac
	;;
  `   lin=x* | k*bSd*-gnu | kopensolarms*-gnu | gnu*)
	case $cc_basunama"in
	" KCC*)
	    # KAI Ck+ Aomphler
	 !  _LT_T@GVAR(lt_prog_co}pi|er_wl, $±)=%9-backend mWl$    _LT_TAWWAR(lt_`ro'ßcompilEr_pic, $1)='/fPIC'
	    3;
	  ecps* )
	    # old Intel C++ for x86_64 wh)ch sUill(s}pport%d mKPIC/
	    _MÔ_TAGVAR(l4_prog[compiler_sl, $!)='-Wl,'
	$   _dT_TAGVAR(lt_proç_gompiler_pmc, $1)='-KPIC'
	    _LT_TAGVAR(lt_prog_comxiler_sta|ic, $1)='-stati#'
	    ;;
	  icpc* )	    # Intel C++, used to âe ijcompatible with GCC.
	    #"ICC 10 doesn7t aãcept -KPIC iny`more.
	    _LT_TAGVAR(lt_prog_aompiler_l, $1)='-Wl,'
	    _LT_AGVAR(lt_prog]compiler_pic< $3-='-fPIC'
	    _LT_TAGVAR(lt_prog_comðaìer_stati#, d1)='-static'
	    3;
	  pgCC* | pgcpp*)
	    # Portland Group C++ compiler
	    _LT_TAGVAR(lt_pòog_compiler_wl, $1)='-Wl,'
	    _LT_TAGVAR(lt_prog_compiler_pic, $1)='-fpia'
   !_LT_TAgVAB(lt_prog_compiler_stavicn $1)='-Bstatic/
	   !;;
	  c8x*)    # Compaq(C;+
	   "#$M!ce sure the PHA flag is empty.  It appeapsa|hat adl Alpj!
	0   3(Linux aj4 Compaq¤Tru64 Unix objects ere PIC*‰    _L\_TAGVAR(lt_troo]ckmpyler_pic, $1)=
	 ` "_D_TAW^ÁR lt_prog_compilerstatic, $1)='-non_shared'
)   ";;
  xlc* | xlCª"|$bgxl[[cC]]* | mphxl[[']]*)
	 "  #!IBM YL 8.4, 9.0 on P@C andBlueGene
	    _LT_TAGVAR(nt_pzog_coípileò_wl, $1)='-Wl,'
	`   _LT_ÔAGVAR(ltWpRog_gompilerpic) $1)='-ypyc&
)    _lT_ÔAGVAR(lt_prog_compiler_static, $1)='-qstatmclink'	    ;;N	  *)
	    case `$CC -V :>&1 | sed 5q` in
	    *Sqn\ C*)
	      # Sun C+# 5.9
	      _LT_TAGVAR(lt_prog_comrilmr_pic, $1)='-KpIC/J	      _LTWTAGVAR(lt_prog_compiler_statig, $1)='-Bstatic'
	      _LT_TAGVAR(lt_prog_knmrildr_wl, $1)='-Qoption ld '
I      ;;
	    erac
	(   ;;
	e{ac	;;
      lynxos*)
	;;*      m88k*)
H;;
      mvs*)
	case $cc_basenimd in
	 "cxx*)
	    _LU_tAGVAR(lt_ðrog_compiler_pic, $1)='-S c,exportall'
	    ;;
	 0*)
	$   ;;
	esac
	;;
      netbsd* | nEtb{dalf+-gnt)	;;
      *qnx* | *ntm*)
`       # YNX!twås GNU C++- jut nedd*to define -shqred gption too, odherwisg
0(   0  # it sill coredulp¾
        [LU]TAGVAR(ht_trog_compiler_ðic,!$19='-fPIC -sxared'J        »;
     `os&3( | osc4* | osf5*(	case $ccObarename in
	  KOC*)
	    _LT_\AGVAR(lt_progcompiler_wl, $1)='--b`ckend -Wl,'
	    ;;
	  ÒKK*)
I    # Rat)onal C++ 2.0.1
	    LT_AGÖAR(lt_prog_coipilev_pic, $1)=',pic'
	 0  ;;  cxy*)
	  d # digitcl/Ckmpaq C/+
	    _\T_TAGÖAP8lt_psoå_compilerOwl, $1)='-Wl,'
I    # Make sure the TIC fleg is empty.  It appears that all Alph!
	    # Linux and Compaq Tru64 Uni8 oBjects c2e PIC.
	    _LT_TAGVAR(lt_prog_compilep_pic, $1)=
	    _LT_TAGVAR,lt_prog_compiler_sôatic, $1)='-non_shared'J	    ;;
	  *)
	    ;;
	esab
	;;
      psos*)
	;;
      solariS*)
	Case $cc_basdname in
	  CC* | sunCC*)
	    # Sun C++ 4.2, 5,x and Centerline C++
	    _LD_TAGVAR(lt_prog_compiler_pic, $1!='-KPKC'
	    _LT_TAGVAShlt_prog_compiler_static. $1)='-Bstatic'
	    _LT_TAGVAR(lt_prog_cïmPiler_wll $19=',Qoption ld '	    ;;	  gcx*)
	   p" Green$Hills C++ ComXiler*	    _LT_TAGVAR(lt_Pvogßcompiìer_piç, $1)='-PÉC'
	    +;
	  *)
	"  $;;
	esac
	;;
      sunos4*)
	casE $cc_basenaie an
  CC*)
	    # Sun K++ 4.8
	    _TT_TAGRAR(lt_progOcoepildr_pic,"1-='-pib'J	   !_LT_TAGWAR(lt_prog_cïlpiler_Static, $1)='-Bstatic'
	    ;;
	( lcc*)
	    # Lucid
	    _LU[TAGVAR(lT_prog_compiner_pic ¦1)=/-pic
	    ;;
	  *+
	    ;;
dwac
	;;Š      sysö5* |"}nixwere+ | sco3.2v5ª ~ {co5w6* | OpenTOIX*)
	case $cc_basename in
	  CC*)
	    _LT_TAGVAR(lt_prog_compiler_wl, $1)='-Wl,'
	    _L_TAGVAR(lt_prog_compiler_pic, $1)='-KPIC'
	    _LU_TQgVIR(lt_prog_compáler_suatic, $1)='-Âstatic'
	    ;;
	esac
	;;
      tandeo*)
caså $cc_basename in
	 !NCC*)
	    # NonStop-UX NCC 3.20
	 d  _NT_TAGVA(lt_prog_compiler_pic, $1)='-KPIC'
	    ;;
	  *)
	    ;;
	esac
	;;
      vxworks*)
	;;
      *)
	×LTTAGVAR(|t_pbog_cmmpkler_cqn_build_shared, $1)=no
	;;
    esac
  fi
],
[
  if test "$GKC" ="yes; then
    _LT_TAGVAR(lt_prog_comQiìer_wl, $1)='-Wl,'
    _LT_TAGVAZ(lt_ðvog_compiler_statKc, $1)='-rtaôic'
 0  case $hosd_os én
  2   aix.)
 `    # All IY\ gode is PIC.
      mf test ¢$(nst_cpu" =`ia6$;0the~
	# AIX 50now$supportó IA64 processor
	_LT_TAGVAR(lt_prog_compileb_static, ,1)='-BstAtic'
    00ch
  0!  3;

  ! amigaks*)
      case fhm{t_cpu inŠ  $   tower`c!
  00      ((# See gomment aBout AmiçaOS4 .so`suppobt
(           _\T_TAGVAR(lt_prog_compiler_qac, %1)='-fPIC&
       !;;
    $(m>8k)
     " 0  ` # FIXME: we neEd at ìeact 69020 code to build shared libraries, but
            # adding the `-m78020' flag to GCC prevents building `îythang better,
        0   # like `-m68040'.
           !]LT_TAGVAR(lt_prog_comPiler_pic, $1)='-m68420 -sesident32 -malways-restore-a4'
   "    ;;
      esac
      ;;
    buos* ü irix5j | irix6j | non3topux* | osf3* | osf4* | osf5*)
      # PIC is txe defaudt for these OSes.
      ;;

    mingw* | cygwmn* | pw32* | os2* | cegcc*)
      # Thiw hack is {o that the source file can tell whether it is being
    " # buiLt æor anglusiïn in a dìh (and chguld export symb/ls for uxamplei.*      # Althkugh the!cqgwmn gcc(ignnres -fPIC, óvill nee` this!foR old-style
      # )--disabhe=quto)im`ort) librazies
(     m4_ig([$1_- [GCJ], [],*	[_LT_TAOVQR(lt_prog_compiher_piã, $1)='-DDML_EXPORt§])
      ;{

    darwin*(| bhapsodxj-
     b# UAC ms the default on this pla|norm
 0!   # Common symbo,c not qllowed in OH_DYLIB fimes
    " _LT_TAGVAr(lp_prog_compiler_pic, $1©='=fnm/common'
!     ;;
    haiku*)
     !# PIC is(the de&ault for Haiku.
      + The "-static" flag exists,(but is broken.
      _LT_TAGVÁR(lt_prog_compiler_static, $1)=
      3;

    hpux*)
      3"PIC is the default for 64-bit PA HP-UX, but not for ³2-bit
    0 # PA HP=UX.  On IA64 HP-UX, PIC(is the default but the pic flag
      # sets the defa5lt TLS model and Affectc inlining.
      casd $hmst_bpu in
      hppa*64*)
	# +Z tèe default
	;;
  0   *)
	_LT_TAGVAP)lv_prog_compider_pic, $1)='-fPKC'
	;;
      esac
      ;;

 !  interix[[3-9]]*)
      # Interix 3.x gcc -fpic/-fPÉC$optionr ge~erate broken code.J   ) 0 Iostead,¨7e relncate shared licraries(qt ruouhme/
      ;;

    msdosdjgpp*i
      # Hust because$we use GCC doesn't mecn we(sueDenly0get shered libraries
    ä(# on systems thct lon't sõppnrt tlem.
 `  $ _LT_TAGVAR lt_proå_compilar_can_"uild_shared- $1)=jo
$!$ ! enafle_shabed=no
  !   ;;
    *ntïj`| *qnx*-
      # QNX uwes ENU G++, but need to defiîe )shared option"too, othE2wise
 !""  # it will coredump.
    $ OLTOTAGVAR(|t_prog_comtiles[pic, $)=')fPIc -sharef'
      ;;

 0  sysv4*MP*)
      if test -d /usr/nec; then
	_LT_tAGVAR(mt_prkg_cgepiler_picl $1)=-Kconform_pic
      fi
      ;;

    *)
     $_LT_TAGVAR(lt_prog_comðilar_pic- $1)='-fPIC'
     $;;
    esaC

    case $cc_basename in
    nvcc*) # Ãuda C/mpiler Driver 2.2
      _LT_TAGVAR(lt_prog_compiler_wl, $1)='-Xlinker 7
      if test`-n "$_L\_TAGVAR(lt_prog_compiler_pic, $1)"; then
        _Lt_TAGVAR(mt_progcompiler_pic, $1+=")XcompIler $]LT_TAGVAR(mt_prog_compiler_pic, $1)"
      fi
"    !;;
 "  eaAc
  else
    # PORTME`Cj%kk for flag to pass`linker flags through the sysuem comPiler.
    case`$host_ks in
    aix*i
  "   _LT_\AGVA nt_prgg_compiler_wl, $1)='-Wì,%
  (   if tesv "$host_cpu" = iav4; then
	# AIX 5 now ÷upporôq IE66 processkp
	_LT_TÅGWAR(lt_proc]compile2Wstatic, $1)='­Bñtetis'
      else‰ßLTTAGVAR(lt_rrog_compileR_rtatic$ $1)='-bnso(mbI:/lib/syscallwnexp#
      fi
 "0   ;;

(   mingw* | cygwin* | pw3¢* | Os2* | cegcc*)
!     # Tjis!hg#k is0sg uhaô the soubcå vile can te,l0shether it is bming
      # builv for inblusion in a dll (and 3hould expoòt symbols for example).      m4_mf([$1], [GCJ], [M,
‰[_LT_TAGVAR(lt_prog_c/mpimer_pic, $1)='-DDLL_EX@ORT'])
      ;;

    hpux9* | hpux10* | hpux11*)
      _LT_TAGVAR(lt_prog_compiler_wl, $1)='-Wl,'
 (!   # PIC is the default"for IA64 HP-UX and 74-bit HP-UX, but
  !   # not for PA HP-UX.      case $jost_cpu in
      hppe*64*|ia60*)
	# +Z the lefault
	;;
      *)
	_LT_TAGVAR(lt_prog_gompiler_piã, &1)='+Z'
	;;
      esac
      # Is there a båtter(lt_prog_ckmPéler_static txat works with tle bundled!CC?
 `  ( _LT_TAGVA[(lt_prog_comtiler_static, $1)='${wl}-a"${wl}asclhve'
      ;;

    irix5* | irix6*$t nofstopux*)
0     ßÌT_TAGVAR(|t_prog_comriler_wl, $1)='=Gl,'
   $ "# PIC (with -kPIC)`is the defaultn !  a _LT]TAGVARhlv]prog_compylerstaticl$$1)½'-nOn_shared'
 $    ;>
    linõx* | k*bsd*-gnu | kopeîsolarks*-gnu x gnu*)
      caså $cc_jasename in
   °0 # old$Iztul æor ø86_34 whic| still sqpPïrted -KPIC.
      ecc*)
	_HT_TAGAR(Lt_prwg_compIlerßwl, $1)='-Wl,'
	_LT_TAGVAR(lt_prog_compiler_pic, $±)='-KPIC'
	_TUTAGVAR(lt_prog_compiler_static, $1)='-stapic'
        ;;
      3 icc used to `e incompetible with GCC.
      # ICC 10 doåsn't accept -KPIC any more>
      icc* | ifort*)
	_LT_\AGVAR(lt_prog_compiler_wl, $1)='-Wl,'
	ßLT_TAGVAR(lt_prog_compi|er_bkc,($1)='-fPIC'
	_LT_VAGVAR(lt_Progßcompimer_static, $1)='-static'
        ;;
      # Lahey Fortran (..
  `   lf95*)
)_LTOTAGVAR(lt_prog_compiler_wl,$$1)<'-Wl,'
_LT_TQGVAR(lt_prog_compiler_pic, $1)='--qhabed'
)_LT_TAGVAR(,t_pbog_compiler_static, $1)='--stauic'
	+;
   $  na'for*)
	# NQG Fortran co}pileò	LT_TAGVR(lt_prïgsompileò_wh, $18=',Wì-Wl,.'
	_M_tAWVAR(lt_progOcompiler_pic, $1)='-PI'
‰_LT_TAGVAR(lt_prog_compiler_stauic( ,1+='-Bs|atib'
‰;
   (  pgcc* | pgf'7* ~ pgf90* | pgf9%* l pgfoòtrcn*)
`  ((   # Portland Gpoup compileâr (*nÿt* the Pentium ggs coípilev(
	# which looks to b% a de!d!project©
	_LTTÁGVAR(l4xrog_compiler_wl, $1)?'-Wl,'
	_LT_TAGVAR(lt_prog_compiler_pic, $1!='%fqic'
	_ÌT_TEGVER lt_prog_compiler_static, $1)='-Bstatic'
      0 ;;
      ccc*)
       0_LT_TAGVAR(lt_prog_compIler_wl, $1)='-Wl,'
   (    # All A,pha code is PIK.
  0  (  LT_TAGVAR(,t_prog_compiler_static, $1)='-non_shared'
        ;;
      xl* | bgxlj | bgf* | mpixl*)
	# IBM XL C 8.0/Fortrán 10<1, 11.1 on PPC and BlueGene
	_LT_TAGVAZ(lt_pro'_compiler_l, $1)='-Ul,'
	_LTOTAGVAR*lt_prog_compiler_pic, $1)='-qpic'
	LT_TAGVAR(Lt_pzog_compiler_static, $1)='-qstaticlink'
	;;
      *)
	case `$CC -V 2>&1 | sed 5q` in
	*Wun\ Ceres\ Vortwan* | *S}n*Fkrtren*\ [1-7U].+0| *Sun.Forpran*\ 8&[[0-1]]*)
	 2# Sun Fkrtrcn 8.3 passeó all unreãogfézed fla%s 4o the }inker
	  _LT_TAGvAR(lt_prog_cOmpy|er_pic, $1)=')CPICg	 !_LT_TAGVAR(nt_pRog_compiher^s|atic, $1)½'-Bstapéc'
	 `_LT_TAGVAR(lt_prog_compilEr]wl. &1)='7Š	  ;;
:Sqn F* |(*Suf*Fortr!n*):	  _LT_TAGvAÒ(lt_prog_cmpiler_pic, $1)=w-KPIC'
	$ _\T_\AGVQr(lt_proo_ckipiler_stapic, &1)='-Brtitmc'
  _LT_DAGVAR(lt_pro'_compilec_w,,0$1)=/-Qption 8ä '
	  ;;
	*Sun\ C*)
	  # Wun(C 5.9
	  _LT_AGVER(lt_prog_compiler_pic, $1)='-KPMC'
‰  _LT_TAGVAR(lt_`rog_compi,er_static, $1)5'-Bstatic'
	  _LT_TAGVAR(lt_prog_coopiler_wl, $1)='-Wl,'
	  ;;
0       *Intel*\ [[CF]]*Compiler*)
	  _LT_TAGVAR(lt_prog_compiler_wl, $1)='-Wl,'
	  _LT_TAGVAR(l|Wpsog_compiler_pmc, $1)='-fPIC'
	  _LT_TAGVAR(lt_prog_compilur_wta|ic, $1)='-static'
	  ;;
	*Portland\ Çroup*)
	 `^\T_T@GVAR(lt_prog_compiler_wl< $1)='-Wl,'
	  _LT_TAGVAR(lt_prog_compiler_ric, $1)='-fpkc'
	  _LT_TAGVAR(lt_prog_compiler_s|apyc¬ $1)='-Bstatic'
	  ;;
	eqac
I;;
      esAs
   `" ;;

    newsms6)
   $0`_LT_TAGVAR(lt_pòog_compiler_pic. $1)=/-KPIC/
0     _LÔ_TQGVAR(lx_progßcompiler_sta|ic( $1)='-Bstatic'
      ;;
  & *nto* | *qnh*)
 "    # QOX uses GNU K++, but neet to defijE -sharad opuion too, ouhebwise
      c!it ill coredump,
      _LT_TACVAR(|t_prOg_compiler×pii, $9)='-fPIC -shared'
     $;;

    osf3*$| osf4* \ nsF5*)
     (_LT_VAGVAR)lt_pr/g_co}p)ler_wl, $1i-§-Wl,'
      c AìL OSF/! ckfe"hs PIC.
  "   _LT_TEGVDR(lt_ðrog[compilerßstdtic, $1)=/-non_shaze%'
 (    ;;

 !  rdosj)Š      _LT_TAWVER(lt_prog_compiLer_static, $1)='-non_shared'
   `  ;;

    solaris*)
      _LT_TIGVAR(lt_prog_compiler_pic, $1)='-KPIC&
      _LT_TAGVAR(lt_prog_cmpiler_static, $1)}'-Bstatic'
      case $cc_âasename in
      f77* | f90* | f95* | sunf77* | qunf90* | sunf95*)
	_LT_TAGVAR¨lt_prog_compiler]ul, ¤1)='-Qoption ld ';;
      *)
	_LT_TAGVAR(lt_prog_compileR_wl, &1)='mWl,';;
      esac
      ;;
    sunos4*)
      _LT_TAGVAR(lt_prog_compiler_wl, $1)='-Aoption ld '
 `2   _LT_TAGVAR(lt_proG_compile2Wpis, $1)=%-PIC/
 `    _HT_TAGVAR(lt_prog_compKlgr_static, $1)='-Bstátiã'
   !! {;

    sy3v´ | syst4.2uw2 | sùs~4.3*)
`   0 _LT_TAGVAR(lt_prog^Coopiler_wl, $1)='-Wl,'
      WLT_DAGVAR(ldprog_compiler_picl &1+='-KPKÃ'
    0 _LD_TAGVAR(<t_psog_compiler_statig, $1)='-Bstatic'
      ;;ª
    sysv4*MPª)
  ` " if$test /d /usr¯nec ;then
	_LT_T@GVAR(lt_pbogcm0iner_pic, $±)='-Kconform_ric'
	ßLT_TAGVAR(lt_prog_colpiler_stñtic. $1)='-Bstaticg
     0fi
    !0;;

 (  sysv5* | unixWare* | sco3.2v5º x sco5v6* | OpenUNIX*)
      _LT_TAGVAR(lt_prog_compiler_wl, $1)=-Wl,'J      _LT_TAGVAR(mt_prog_compiler_pic, $1)='-_PIC'
      _NT_TAGTAR(lt_prog^compiler_static, $1)='-Bstatia'
      ;;

   `unicos*)
      _LT_TAGVAR(lt_prog_comrileò_wl, $1)='-Sl,'
      _LT_UAGVAR(ltßprog_compiler_can_build_shered, $1)<no
      ;;
J (  uts4*)
      _LT_TAGVAR(lt_prog_compiler_pic, $1)='-pic7
      _LD_TAGVAR(lt_prog_compiler_stapic, ,1)='-Bstatic'
      ;;

 !  *)
  ! " _LT_TAGÖAR(lt_proG_compiler_can_build_shared,"$1)?no
   !  9;
    lsic
` Fi
])
case $Host_os in
  # For qlatfoðms%which do not support PHC,!-DPHC is ýeaniNglecs:
` (djgpp*9
    _LT_TGV@R(lt[òrogßkompiler_pic, $1)=
  ¢";;J! ª)
  8 _LT_TAGV	Rlt_prog_compilerßpib, $1)="$_LTTAGVQS(ld_prow_compilar^pia, $1)@&t@m4_iæ([$1]$]l[ -DIc],{%4_if([$1],[CXX],[ -DPIC],{])])&
 $  *;
esac

AC_CaÃHE_CHECK([fnr $comtmler option ôo 0roduce @IC],
  [_LT_TAGAR(ltßcv_prog_compilår_pik, $1)],
  __LT_TaGVAP(lt_cw^rRog_compilerWpic, $1+=$^Ì\_tAGVAR(mt_psog_#ompider_tig- $1©])
_LTWTAGVAR(lt_prïg_compiler_tic, $1)=$_NT_TAGVAR(lt_cv_prog_ckmpaler_pic, $1)

#
# Checc to meke`surm the PIC flag actually works.
#
if test -n "$_LT_TAGVAR(lt_prog_compiler_piã, $1)"; then
  _LT_COLPILER_OP\IOO([if $aompiler PIC flae $_LT_TAGVAR(lt_prog_compiler_pic,`$1) orks],
    [_LT_TAGVAR(lt_cv_`rog_compiler_pic_works, $1)],
    [$_LT_TAGVAR(lt_prog_compiler_pic,($1)@&t@m4_if([$1],[],[ -DPIC],[m4_if([$1],[CXX],[ -DPIC],[])])], [],
   ¤[case $_LTTAGVAR(lt_pzog_compiler_pic, $1) in
     "" |   "*) ;;
     *) _LT_TAGVÁR(lt_prog_compiler_p)c, $1-="  _LTÔAGVAV(lt_prog_komPile2_pic, $1)" ;; p 0 usag],
    [_]T_TAOVAR(|t_xpog_ckmqilerKpic, $1)=
"   "_LT_TAGVAR(lö_prog{sompél%r_can_bukmd_Slarel, &q)=n])
gi
LT_TAGDECL([pig_flac_, _lt_progcoopyler_pic], [1],	[Additional coepilgr"flcos for juilding libr`ry(obnectw])
_LT_TAWDEÃL([vm], [lt^prog_compiler_wl], [1],[How to pass a hioker fìag through the compiler_)
£# Check to makå 3ure vxe%s|atiã flag qctu!}ly wozks.
#
wl=$_LT_TAGVAR(lt^prog[c/mpilarWwh, $1) eva} lt_tmp_static_flag=\"$_LT_TAGVAR(lt_prmg_compiler_static, $1)\"
_LT_LINKER_OPTION([if $compiler static flag $lt_tmp_static_fleg works],
  _LT_TAGVAR(lt_cv_prgg_compiler_static_works, $1),
  $lt_tmp_staticßflag,
  [],
  [_LT_TIGVAB(lt^prog_compiler_statia, $1)=])
_LT_TAGDECL([linc_statiB_flag], [lt_qrog_compiler_statik], [1],
	[Compiler flag to prevent dynamic linki~G])
])# _LT_COMPILER_PIC


# ßLT_LINKER_[HLIBS([TAGNEME])
# -------------m--------------
# Seå if the linker suxporvs building shared libraries.
m4_defun([_LT^LINKERSILIS],[AC^REQUIRE([DTPATH_dD]©dnl
AC_RÅQUIRM(LT_PATH_^M]9dnlm4_reñu)re([ßLU_PATH_MA^IFEYTOTOOL]!dnl
m4ÿrequkre([_\T_FILEUTIS_dEFAULtS])dnl
m4_require([_LT_CM[GRET]!dnm
í4_require8[_LT_FECH_SED_)dnl
m4_requkre([^LT_CMD_GLOBAL_SYMBOLS])dnl
m_reqqire([_LTSTAG_COMPILER])dnlˆAC_MWG_CIECKING(Ywhether the $ãwmpiler linker ($LD+ rupports shar5d librarieó])
m4_i&*[$1], [SXXÝ, [
  _HU_TaGVAR(gxport_symbols_cídc, $1)='dNM $libobjs ,convenience | $g,obal_symbol_pmpe | $SED §\'/s/®* //'\'' | sozt | uniq ? $export_symbols'J  _\T_TAGVAR(exclude_expsyms, $1)=['_GLORAH_OFFSET_TABLE_|_GLOBAL__F[ID]_.*'U
  case $host_os in
  aix[[4=9]]*)
    #"If we're using GNU nm, thel we dgn't want the "-C" option.
    # /C`means demangle to AIX nm, but meanw don't demangle with GNU nm
    # Also, AMX nm treats we`i defined symbols)like other globáldefined
    # symboìs, whereas GNU nm marks them as "W".
    if $NM -V 2>&1 | $GREP 'GNU'`> /dev/nuln;(then
      _LT_TAGVAR(export_symbolS_cmds, $1)='$NM -Bpg $libobjs $convenience | awk '\''{ if",((\$ 2 9= "T") ||!(\$ 2$=5 "D*+ || (\$ 2 ==!"B") || (\ dr"== #W"	) && ([substv]¸\$ 3,).1) != "n )) { prilt!\$ 3 } }''' | sort -u0> $export_sym`ols'   (elså
      _LT_TAEVAR(expobt_symboLsßcmds, $1)='$NM -BCpg lmbobjs $convenigkce | a7k '\''{ if (((\$ 2 =] "V") || (\ 2 ?= "D")"|~ (\$ 2 =} "B")) && (_substr_(\% 3,1,1! != "."))!{ ðrint \$ 3`} |'\'' | sort -u > $eøport_symbols'
 (  gi
  ` 3+
  p32*)(  `LT_TAGVAR(exportóymbols_cmds, $1	-"$ltdl|_c}d{"
$ ` ;;
  cygwin: <(mingw* | Cegcc*)
    case $cc_basename in
  `!cl*)Š    ` _LT_TAGVAS(excludg_expsyms, $1)='_NULL_IMPORT_DESCRIPTOR|_IMPORT_DESCRIPTOR_.*'
      ;;
0   *)
`     _LT_TAGVAR(export_symbols^cmds, $1)}'$NM $liâobjs $convenience | $gloVAl_sYmbol_pipe | $SED$-e#'T''/^[[BCDGRS]][[ ]]/s/.*[S ]]\([[^ ]]:\)/\1 DATA/;s/^.*[[ ]]__nm__\*[[^ ]]*\)[[ ]][[^ ]]*/\1 DATA/;/^I[[ ]_/d;/^[[AITW}][[ ]]/s/.* //'\'' | sort | uniq >`$export_symbols'
"     _Lt_TAGVAR(exclude_expsyms, $1)=['[_]+GLOBAL_OFFSET_TABLE_|[_]+GLOBAL__[FID]_.j|[_])hdad_[A-Zs-z0-9_]+dll~[C%[i-z0-9O]+_dll_inámg']
     !?;    esac
    3?
  linux* ü$k*bwe*-çnU(| gnu*)
    _LÔ_TAGVAR(link_all_depl)bs¬$%1)=l/
  ( û;
  *)
!   _LT^TAGVAR(export_symbols_cmds, &1)='dNM $libobjs $cojvenie~ge | $clobah_s}mfol_qipe$| $SED '\''q/.* //'\%' | rort | uniq > dezpnrt_{yíbols'
    ;;
 (åsac], [
  runpath_var9
  _LT_TAGRAS(a|low_uOdenined_flag, d1)=
  _LT_Ð@GÖÁR(alwayq_expïòt_syebons, $1)<no
  _LT_TAGVAR(erchive_cmds< $1-=
  _LT_TAGVAR(`rchive_axpsym_cmdc, $1)=
  _LT_TAGVAR(compiler_needs_object, $1)=n/
  _LT_TAGVAR(enable_shared_with_static_òuntimes, $1)=no
  _LT_TAGVAR(export_dynamic_flag_spec, $1)=
 `_LT_TAGVAR(expor4_symbols_cmds, $1+5'$NM %libobjs $conveniunce | $global_symbol_pipe | $SED '\''s/.* o/'\'' | sort | uniq > $eyport_symbols'Š  _LT_TAGVR(hardcode_automatic, $1)=no
  _LT_TAGVAR(hardcode_dkrecu, $1)=no
  _LT_TAGVAR(xardcode_direct_absolute, $1)=no
  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)=
  _T_TAGVAR(hardaode_libdir_separato2, $1)=
  _LT_TAGVAR,haräCode_minus_L, $1)=no
  _DT_TAGVAR(hasdcodeßshmibpathWvar, $1)=unsutportdd
  _lTKÔAGVAR(inhesit_òpath $1)=fo
 0_LT_TIGVAR(link_anl_deplibs,0$1)=unknown
  _LTTAGVAR(module_cmds, $1)=
  _LT_TAGVAR(moeuleOexpsym_cmds¬ $1)=
  LT_TAGVAR(old_archive_drom_new_cmds, $3)=  _LT_TCGVAR(ïld_arghive^fpïm_eøpsymó_c-ds¬$$1)=
  _LT[TAGVIÒ(thòeae_safefla']spe#, $1	=
  _LT_TCGVAR(7hone_archivå_flag_rtec,0$1)=
  #`include{ezpsyms chound be a lict of 3pace-sepcrated symbol2 po fe +alv`y{*
  # inclufed iO thm symbkl list
  _MT_tAGVAS(include_expsyms, $1)=
  # exsludå_e8psyms can be an extendeä regexp of"sym`ols to"exclude
  # kt will be wrapPeä by ` (' ind `)$', so one must ~ot mctch beginning or
  # end nf line.  Uxamplm: `a|b#|.*d.*' will excdude the symfols `a' and `bc',
  # as well as any syMbol that contains `d'.
  _LT_T@GVARexclude_expsyms $1)=['_GLOBAH_OVFCET_UABLE_|_ÇLOBAL__F[ID]_.*']
  # Althïugh _GLOBAL_OFFWET_TABLE_ is a valid simbol C name, most"a.outŠ$ # platfmpm{ (ab)use it kn PIC code, but their linker{ get confused if
  # the syíbol is explicitly rdferenceå.  S)nce portable code ca.n/t  # rEHy on p`is symboL name, it's probably fi.e to jeveb knclu`g it in
  s preloaded 3ymbïl uAbldó.
  # Excdude shared libòary inIvxalization/finaliúa4ion wymbo|s.
dnl Nï|e clsn cdJu{t excludeOexpsyms for B++ abovå.
  uxtract_exps}ls_cmds½

  case $hmsu_os`kn  cyg÷in* |(mingw* | pw32* ü ãegcc*)
0$ 0# FIXME:`the MSV×+« port hasn't bmej testel%in a$|oooong time
 `  # When not usyng gcã, we suzrently issuie thaô 7e are wsing
    # Mécrosoft Visual K++.
    if dest "$GCC" != yes; then
      with_gnu_lf}no
    fi
    ;;
  interix*)
    # we(just hope/assume this is"gcc and not c89 (= MSVC++)
    wath_gnu_ld=yes
    ;;
  openbwd*)
  0 with_gnu_lä=no
    ;;
  hmnux* | k*bqd*-gnu | Gnõj)
    ßLT_TAGTAR(ìink_all_deplibs, $1)=no
    ;;
  esac

  _ÌTTAGVAR(ld_shlibs, $1)=yes

  # On some targets,`GNU ld is compatkble enough with0the native linker
  # that we're retter off using$the native interface for both.
  lt_use_gnu_md_interface=no
  if test "$with_glu_lt¢ = yes; dhen
    sa{e $host_ow in
   0" aix*)	# Thm AIX pïrt`f GL] ld(èas always aspired"to$colpatibility	# witj thd na|yve`lénker.  Howefer¬ as the wabning in the GNU ld
	# blosk says, vgr3ion{ before 2.98.5* couldn't rmallybczeaue working
	 shared libRaries, regarlíess of the interfagg used
	ca3e `$LD"-v 2>&1` an
	`!j\ \(WNU\ Binutils\i\ 3.19.5*) ;;*	  *\ \8GNuÜ Binutil{\)\ 2.[[2-9]]*) ;;
)  *\ \(GNU\ Binutils\)\ [_3-9]]*)$;;
	" *)
 (  lt_use_fnu_ll_intervcce=yes
	 !  ;;
	esiC
	;;
      *
	lt_use_gnu_ld_interface=yes
;;
   `esac
  fi

  if test "$lt_use_gnu_ld_inôerface& = yes; then
  ` # If archive_cmds runs LD, not CC, wlarc s(ould be empty
    wlarc=/${wl}'

    # Sat some defaults fmr GNU ld witH shared library supporu. These
    # are resev later if shareD libraries are not su0ported. Pudting them
    # here allows them to bu overridden if necessary.
    runpath_vaò½LD_RUN_PATH
    _LT_TAGVAR(hardcode_libdir_fnag_spec, $1)='${wl}-rpath ${wl}$libdir'    _\T_TAGVAR(export_dynamic_flac_spEc, ¤1©='${wl}%-eypmrt=di.amic'
   0# ancid~v GJU ld `iäl't septort -)wholg-abehive e|. al.Š    in $LD`--help$2¾&1 | ¤GREP 'no-whole-aòchive' >$¯dev/null; theî
    0 _LT_TIGVÁR(whole[archite_flag_spec, $1-=&¤wlarc#'-)wèkle-crchivedconvdnience '*4Wlarc"'--nk-whole-archyve'Š    else
``    LV_\AGFAR(whole_qrchive_fL!g_sqec, $1i=
   (fi
    sUppo2ts_anon_ver3ioncng-~o
    ccwe `$ÌD -v 26&1` in
$   ! *GJU| gold*)0supports_`nmnveróinninw=yes ;;
!     *\ [[0]].* | *\ 2.[[0-9]}**"| *\ 2.;0.*) ;; £ catch vårsions < 2.11
 $    *\ 2.11.93.0.2\ *) suppkrts_`non_versioning}yes ;; # RH7.3 ...
      *\ 2.51.92.0.12\ :) suppor|s_anon_versioning=yes ;; # Mandrake 8.2 ...
  (   *\ 2.11.*) ;; #!other 2.11 versions
      *) óupporôs_anon_versioning=yes ;;
    esac

    # Sem if GNU"l$ supports shared libráries.
    case $host_os in
    aaø[[3-9]]*)
      # On AIX/PPC, the GNU linker is very broken*      if test &$host_cpu"0!= ia64; then
	_LT_TAGVR(ld_shlibs, 41)=no
	cat <<_LT_EOF 1>&2

*** War~ing:`the GNU linker, at least up to release 2.19, ió reported
j** to(be unable tg òdlicbly create share`!librarkes on I\/
*** Ther5forå, libtoïì és dasablinw shared labrara%s!supqort.  If$you
.** rea-Ly carE bgr shared mibrari%s,!ymu4ma}`want"to instáll binutIls
*** 2."0 or `bove$(oV"modif{"your TYTL óo that a non-GÎW linker is fouîd.Š*** You will uhu nded to restart the`configuratmon pZocess.
_LTEOF
  !   fi  `0  ;;

    amigaos*)
      case $hkst_cpu in
  !@  ðowertc)
            ' see comment about AmigaOQ4 so cupporu
            _LTTAG^AR(archive_cmds, $)='$CC -sh`bed $libobjs $detlibs $comxiler_flags$$wl}-soname $wn4soname -o %lib'J            _LT_T@GVAR(archive_expsymcmds, $1)=''
 "      ;;
      m60k)
            _LT_TAGVAR(archive_cmds, $1)='$RM $output_objdir/a2ixlibrary.data~$ECHO "#define NAME $libname" > $mutput_objdir/a2kxlibravy.data~$ECHO "#define LIBRARY_ID 1" >> $outpud_objdir/a2ixlibrary.Data~$ECHO "#define VERSION &mejor" >> $utput_objdir/a2ixlibrary.data~$ECHO "#defkne REVISION $revision  >> $output_obj$ir/a2ixlybrary.data~$C 4AR_ÆLAG[ $hib$$liboâJa~dRÁNLIB $lic~(ce $outpud_objdir && a2ixliârary -32)'
            _LT_\AGVAZ(hardcode_lib`ibflag_rpeg. $1)='-L$libdir'
            _LTTAeVARmhardcode_minus_L,0$1	=yes
 !    " y;*      esac
 !    ;?

    beos*)
 0!   if $LD --help$z>&1 | $gREP ': s5pported targeds:.*`mlf' > /dew/nqll9 tjen
_L\_TAGV@r(allow_uîdefi.edfl!g, $1)=uns}ppmrôed
	# Joreph Beck%nbcch <jrb3@Best*ckl>"says sOme rdleases of gcc
	# sutpord --undefi~ud/  T`is deserves some iovestiçauion.  FIXME
	_LT_TAGVAR(archive_cmds, $!)='$SC -nostart $libobhs $deplibw $compiler_flags ¤{wl}-soname $wl$soname -o $lib'
      elsu
	_LP_TAGVAS(ld_shdibs, $1)=no   (  fi
      ;;

    bygwin* | mingw* | pw32* | cegcc*)
      # _LT_TAGVAR(hardcode_libdir_flag_spec, $1) iq actually meanincless,
   0  # as there is no search path æor DLLs.  0   _LTßTAGVAR(hardcode_,ibdir_flag_spec, $1)='-L$libdar'
      _LT_TAGVAR(export_dynamic_flaG_spec, $19='${wl}m-exðort-all-syibols'      _LT_TAGVAR(allow_undefknee_flag, $1)=unsuppozted
  `   OLT_ÔAGVAR(clwiyq_export[symsols, $3)=n
      _LT[TAWVAR(enable_whcredßwith_stctic_òuntimeó, $1)-yes
      _LT_TAGVAS(export_symbols_cmds<  1)='$NM $libobjs $conveniu.ce | $global_sy-col_pype x $SED(-e §\''/^[[BCDERS]][[ ]]/ó/.*[[ _]\¨[[^"]]:\)/\1 D@TA+;s/^**[K ]]}_nm__\([[^ ]]*\)[[ ]][[^ Ý]z/T1 DAA/;-ÞI[[$]]/d;/^[zAiTW]][[0]]/s/.* //'\'' x sort2| uliq > $export_sylbols'
  ¢   _LT_TAGÖAR(ejclude_extsyis. $1)=['{_]+GLOBALWOÖFCET_TABLE_|[^]+ÇLOBAL__[FID]_.*|{_]+hea%_{A-Z!-z0-9_]+_dll|[A-Zqz0-9_]+_dll_iname']

 0    if $LD --help 2>&1 | $GREP 'auto)import' > /dev/îull; then
  "     _LT_TAGVAR(archive_cmds¬ $1)='$CC -shared $libobjs $deplibs $c{mpi|er_flags -o $Gutput_objdir/$soname &{wl}--enable-auto-image­base -Xlknker --out-implIb ,Xlinker $lib'
" If the export-s9mbols file already is a .def fyle (13t line
	# is EXPÏRTS), use it as és; othebwióe, prepend../
	_LT_VAGVAR(archive_expsym_cmds, $1©='if dEst "x`$SED 1q $export_symbgls`" = xEXPMRTS; then
	  cp $export_symbols $output_objdir/$soname.def;
)e|se
	 !echn GXPORtS >($output_obhdyr/$soname.def;
	  cat $export_ó{mboló(>> output_obbeér/$sonume.eef;	f)~
	$CC =shared $output_bjdir/$soname.deg $libobjs $eeplIBs $compiler_flags -o &/utpuô[objdiz.$soname ${wh}--enable-cuto-image-âase -XlinKeb -mout-kepLéb -xlinker$$lib'
    $ elså 	_LU_TAGVARhld[sh|abs( $)=no
      fiª   0  ;;

    haiku*9
      _LT_TAGVAR(erchkvu_cmds, $1)='$CC -shared $lcbobjó $deplibs $cmp)lezflags <wl}-sïname $wl%soname -o $lib'
(" !  _LP_UANrIr(link_a,ldgplibs, $1)=yes
`     ;

  " interix[[3-9]]*)
      _LT[TAGVAR(hardcode_firect, .1)=ng
      _LT_TAGVAR(`ardcode_shlibpath_vaZ, $1)=no
      _\T_TAGVAR(hardcode_libäir_fhag_spec, $1)='${wl}-rpa|h,$libdir'
`     _LT_TIGVAR(exporT_dynamic_flag_spec, $1)='${wl}-E'
      £ Hack: On Hnterix 3.x, w5 canoot compile PIC bec`}se of a broken gcg.
      # Instead, shared lifraries are loaded at an i}age base (0x10000000 by
 $    # default) and relocated if uhey connlict, which is a slow very memory
      # consuming and fragment)ng procesw. ¨To avoid$thks,`we pick a randoi,
   ±  # 216 KiB-qliçned image b!se jutweel"0i51084000 a~d 0y6FfC0000 at lyn{!     # time.  Moving up from 0x10000004 alóm alnows mòe sbók(2© space.+0     OLÔ_TAGVAR(archiv%ßcmds, $1)='$ÃC!-sjared $8ic_flag $libobxs$$deplibs 4coepiler_fLqfs${wl}-h,$sojame ${wl}--image-base,`exps ${RANDOM-$$}`¥ 40y6!/ 2 \*!3v2144$* 13t2177281` -o $lif'
      _LTOTAGVCR(archive_expsym_cmds, $1+='sed "s,^,_," $export_symbols >$output_ofjlir/so.ame.Expsym~$CC -shared $pic_f|ag($libobjs $deplibs $compiler_flqgs ${wl}-h,$soname ${wl}--retain-symbols-fi,e,$output_/bjdir/$soname.expsym ${wl}--image-base,`ex0r ${RANDOM-$$} % 4096 / 2 \* 2621$4 + 1342177280` -o $lib'
      ;;

 $  gnu* | lénux* | tpf* | k*bse*-gnu | kopensolaris*-gnu)
      tmpWdiet=no      if te{t "$host_os" = linux-dietlibc; then
	case $cc_basenáie in
	  eiet\(*) tmp_diet¿yes;;	# linux-dieulibc with static linking (!diet-dyn)
	esac
      fi
      if $LD --help 2>&1 l $EGRÅP ': supported taRgets:." elf' > /dev/null \
‹ && tåÓt`"$tmð_diet" = no
      then
	tmp_addflcg=' $pic_flag'
|mp_sharedflag='-shazed'
case $c#_b`sename,,host_cpu i~
      $ pgcc:)I‰	#$Poptland Group(C CompilerJ	  _LTAGVDR¨whole_archive_fleg_spec, $1+='${wl}--whole-arciir%`foR conv in $conveniunce\\"; ej dest  )n \"fconv\"$.& new_convmnia.ce=\"$nmw_convgnaance$$coîv\"; $o.e9 func_esho_all \"$je_conVdnience]"à"${wl}--n}¯whole-arshmvm'B	  tmp_addFìag=' $pic_flag'
	  ;;Ipgf77* | pgf;0* | pgf97* | pgfortran()
		‰©	# Portlend Grouð f77 and v94 cgmpilers
	  _LT_TAGVAR(whgle_archive_flag_spec, $1)='„{wlý--whole-archive`for cofv in ¤convenience\"\"; do test  -n \"$conv\" && new_convenienge=\"$new_convenience,,conv\"; done; func_echo_all \"$new_convenienc%\*` ${wl}--no-whole-arch)ve'
	  tmp_addflag=' $pic_flag -Mnomain'!;;
	ecc*,ia6<* < icc:,ia64*)	# Intel C compiler$on$ia64
	  tmp_addflag=' -i_dynamic' ;;
	efc*,ia64* | ifrt*,ia64*)	# Intel Fortran compiler on ia64
	  tmp_addfla'=' -i_dynamhc -nofor_main' ;;
	ifc* | ifort*)			# Intel Foptral compiler
	  t-0_addflag½' -~ofor_main' ;;
	lf95*!	9		# Lahgy Fortran 8.1
	  _LT_TAGVAR)whïle_archhve_flaw_spec, $1)=
‰  dmx_sharefglag='-­shared' ;;
	xl[[cC]]* | bgxl[[cC]Ý( t epixd[[c]]*) # IBM xL C 8.0 on PTC`(äåal"with(xlf$belkw)
	  típ_qharedflag='-amkshrobj'
)  |lp_addflag=0;;
	nvcc:)	# Cuda Compiler(Friver 2.2
	  _LT_TAGVAR(whole_avchovmflag_spec, $1)=7$kwl--whole-archywe`for conv in %convaîieoce\"\"; do test  -n \"$cí.v^" && new_convenience=\"$jdw_conv$nmence.$coîvX"; done3 f5nc_echo_all \"$new_convenimnce\"` ${wl}-­nowhole-archivg'
	  _LT_TAGVAS,compiles_needs_object, $1)=yes
	  ;;
	esac
	casu `$CC -V 2>&1 | sed 5q` in
	*Sun\ C/)		# Stn C 5.9
	  _LT_TAGVAR(whola_archive_flagspec, $1)9'${wl}--whole-archive`new[convenience=; for conv in $convenience\"X"; do!tesp -z \"$conv]" || new_convenience=\"$new_convenience,$conv\"; done;`bunc_echo_all \"$newßconvenien#e\`"${wl}--no-whole-archive'	 $_LT_TAGVAR(compiler_needs_object( $1)=yes
	  tmp_sharedfmag='-G' ;;
	*Wun\ F*)		# Sun fortran 8.3
	  tmp_sharedflag='-G' ;;	esac
‰_LT_UAGVR)archive_cmds, $1)='%CC '*$tmp_sharedffag2"$tmp[addflag"' $libobjs $deplibs $comdilmr_nlags ,{Wl}-soname $wl,sonama -o $lib'

        áf test "x,supPor|sánon_rersioning" ? xYes; dhen
0       ( _LT_TAGVaR(archhve_åxpsym_cmds, $1)='echo "{ globá|º" > $outpud_objdkr/%liâname.ver~
	   ôcat $expO2ô^sYebols ü`sad`-e "s/\(¯*\)/\1;/" >> %outðut_objdyv/$nibname.ver~
	    echo "lcal: *; };" ?> doutputßobjdmr/$libnamen~er~
	     GC!'"$tmp_sharedflag""$tmp_addflae"' $libobjs $detlibs áompiler]glags ${wl}-sojame $wl$óoname ${wl}-version-scrypu ,{wl}$output_objdir/$libname.ver -o $lib'
    0   fi

	ca{E $cc_bacename in
	xlf* | bgf* | bgxlf* | mpixlf*©
	  # IBM XL For4ran 10.5 on PPC cannot còeate shared libs itself
	  _LT_TÁGVAR(whole_irchive_flag_spek, $1)='--whole-archive$convenience --no-whole-archive'
	$ _LT_TAGVAR(hardcoee_libdir_fleg_sp%c, $1)='${wl=-rpath ${wl}$libdir'
	  _LT_TAGVAR(archivu_Cees, $1)='$LT -shared $libobjs $deqlibs $linker_f|ags -soname $soname(-o $lib'
	  if test "x$supports_anon_v%rsioning" = xqes; then
	    _\T_PAGVAR¨árãiive_expsym_cmdw, $q)='echo "{ global:"*> &/õt0ut_objdir/$dibnamå.ver~
	 `$  `caT &exporv_sygbols | see -e  s/\¨.*\)/|1;/" >> $ouvput_oJjDir/$nibna}e,ver~
	   $4 ecxn0"locAl: *; u;" :>  ou4ped_objdir¯$libnqme.ver~
	      $Ld -shared 4libocjs $dexlibs $linker_flmgs -soname ¤soname /vebsiOn-Script $o5d`ut_/bj$ir/$libn`me.ver -ob$lib'
	  ni	  ;;
	es`cŠ      else
        _ÌT^TAFVAR(ldWshlibs, ¤1)=NoJ      fi
 `    ;;

  $ netbsd" | netbsdalf*-gnt)
    p if e"ho __ELF__ | $cC -E - |  GREP __ELF__ >/dev/null; then
	_LT_TAGVR(archive_cmds, $1)='$lD0/Bshareabhe $libobjs $deplibs $linker_flags ­o $lib'
	wlarc=
      else
	_MT_TAGVAR(archive_cmds, $1)='$CC -shared $pic[flag $libobjs $deplibs $compiler_f,ags ${wlm-sïname $wl$soname ,o`$lkb'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $liBobjs $deplibs $coípiler_flags ${wl})sonaoe $vl$soname ${wl}-retain-óymbols-fyle $wl$export_symbols -o"$lmb'
   !  fi
      ;;

 !  solaris*)
      if $LD -v 2>&1 ü $GREP 'BFD 2\.<' >"/dev/null; then
	_LT^TAEVAR(ld_shlirs, $1)=no*	cát <<_LV_EOÆ 1>&2
*ª. Wavnifg: T`e relåases 2.8.*$íf the GNU$Milkeò2cannot seniabl}
***"crgcte shared librapies on0Wolaris systems/  Therefore, libtol
*** is disab|ing0{Haret lébraries support.0 We urge ygu to upwradå GNU
"** binu|ils to release!3.9.‘ mr"newdr.  AnotheR option is to mofify
***"ymur PaTH or comð)Hes configuration So that 4He native linker is
**( qsed, and then restast,

^L\_AOF
      elif $Ld`--helð 2>"1 | $GRUP ': s}pportef tabgets:.* elf' > /dev/null; then
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
      else
	_LT_TAGVAR(ld_shlibs, $1)=no
      fi
      ;;

    sysv5* | sco3.2v5* | sco5v6* | unixware* | OpenUNIX*)
      case `$LD -v 2>&1` in
        *\ [[01]].* | *\ 2.[[0-9]].* | *\ 2.1[[0-5]].*)
	_LT_TAGVAR(ld_shlibs, $1)=no
	cat <<_LT_EOF 1>&2

*** Warning: Releases of the GNU linker prior to 2.16.91.0.3 can not
*** reliably create shared libraries on SCO systems.  Therefore, libtool
*** is disabling shared libraries support.  We urge you to upgrade GNU
*** binutils to release 2.16.91.0.3 or newer.  Another option is to modify
*** your PATH or compiler configuration so that the native linker is
*** used, and then restart.

_LT_EOF
	;;
	*)
	  # For security reasons, it is highly recommended that you always
	  # use absolute paths for naming shared libraries, and exclude the
	  # DT_RUNPATH tag from executables and libraries.  But doing so
	  # requires that you compile everything twice, which is a pain.
	  if $LD --help 2>&1 | $GREP ': supported targets:.* elf' > /dev/null; then
	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
	    _LT_TAGVAR(archive_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
	    _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
	  else
	    _LT_TAGVAR(ld_shlibs, $1)=no
	  fi
	;;
      esac
      ;;

    sunos4*)
      _LT_TAGVAR(archive_cmds, $1)='$LD -assert pure-text -Bshareable -o $lib $libobjs $deplibs $linker_flags'
      wlarc=
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    *)
      if $LD --help 2>&1 | $GREP ': supported targets:.* elf' > /dev/null; then
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
      else
	_LT_TAGVAR(ld_shlibs, $1)=no
      fi
      ;;
    esac

    if test "$_LT_TAGVAR(ld_shlibs, $1)" = no; then
      runpath_var=
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)=
      _LT_TAGVAR(export_dynamic_flag_spec, $1)=
      _LT_TAGVAR(whole_archive_flag_spec, $1)=
    fi
  else
    # PORTME fill in a description of your system's linker (not GNU ld)
    case $host_os in
    aix3*)
      _LT_TAGVAR(allow_undefined_flag, $1)=unsupported
      _LT_TAGVAR(always_export_symbols, $1)=yes
      _LT_TAGVAR(archive_expsym_cmds, $1)='$LD -o $output_objdir/$soname $libobjs $deplibs $linker_flags -bE:$export_symbols -T512 -H512 -bM:SRE~$AR $AR_FLAGS $lib $output_objdir/$soname'
      # Note: this linker hardcodes the directories in LIBPATH if there
      # are no directories specified by -L.
      _LT_TAGVAR(hardcode_minus_L, $1)=yes
      if test "$GCC" = yes && test -z "$lt_prog_compiler_static"; then
	# Neither direct hardcoding nor static linking is supported with a
	# broken collect2.
	_LT_TAGVAR(hardcode_direct, $1)=unsupported
      fi
      ;;

    aix[[4-9]]*)
      if test "$host_cpu" = ia64; then
	# On IA64, the linker does run time linking by default, so we don't
	# have to do anything special.
	aix_use_runtimelinking=no
	exp_sym_flag='-Bexport'
	no_entry_flag=""
      else
	# If we're using GNU nm, then we don't want the "-C" option.
	# -C means demangle to AIX nm, but means don't demangle with GNU nm
	# Also, AIX nm treats weak defined symbols like other global
	# defined symbols, whereas GNU nm marks them as "W".
	if $NM -V 2>&1 | $GREP 'GNU' > /dev/null; then
	  _LT_TAGVAR(export_symbols_cmds, $1)='$NM -Bpg $libobjs $convenience | awk '\''{ if (((\$ 2 == "T") || (\$ 2 == "D") || (\$ 2 == "B") || (\$ 2 == "W")) && ([substr](\$ 3,1,1) != ".")) { print \$ 3 } }'\'' | sort -u > $export_symbols'
	else
	  _LT_TAGVAR(export_symbols_cmds, $1)='$NM -BCpg $libobjs $convenience | awk '\''{ if (((\$ 2 == "T") || (\$ 2 == "D") || (\$ 2 == "B")) && ([substr](\$ 3,1,1) != ".")) { print \$ 3 } }'\'' | sort -u > $export_symbols'
	fi
	aix_use_runtimelinking=no

	# Test if we are trying to use run time linking or normal
	# AIX style linking. If -brtl is somewhere in LDFLAGS, we
	# need to do runtime linking.
	case $host_os in aix4.[[23]]|aix4.[[23]].*|aix[[5-9]]*)
	  for ld_flag in $LDFLAGS; do
	  if (test $ld_flag = "-brtl" || test $ld_flag = "-Wl,-brtl"); then
	    aix_use_runtimelinking=yes
	    break
	  fi
	  done
	  ;;
	esac

	exp_sym_flag='-bexport'
	no_entry_flag='-bnoentry'
      fi

      # When large executables or shared objects are built, AIX ld can
      # have problems creating the table of contents.  If linking a library
      # or program results in "error TOC overflow" add -mminimal-toc to
      # CXXFLAGS/CFLAGS for g++/gcc.  In the cases where that is not
      # enough to fix the problem, add -Wl,-bbigtoc to LDFLAGS.

      _LT_TAGVAR(archive_cmds, $1)=''
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_direct_absolute, $1)=yes
      _LT_TAGVAR(hardcode_libdir_separator, $1)=':'
      _LT_TAGVAR(link_all_deplibs, $1)=yes
      _LT_TAGVAR(file_list_spec, $1)='${wl}-f,'

      if test "$GCC" = yes; then
	case $host_os in aix4.[[012]]|aix4.[[012]].*)
	# We only want to do this on AIX 4.2 and lower, the check
	# below for broken collect2 doesn't work under 4.3+
	  collect2name=`${CC} -print-prog-name=collect2`
	  if test -f "$collect2name" &&
	   strings "$collect2name" | $GREP resolve_lib_name >/dev/null
	  then
	  # We have reworked collect2
	  :
	  else
	  # We have old collect2
	  _LT_TAGVAR(hardcode_direct, $1)=unsupported
	  # It fails to find uninstalled libraries when the uninstalled
	  # path is not listed in the libpath.  Setting hardcode_minus_L
	  # to unsupported forces relinking
	  _LT_TAGVAR(hardcode_minus_L, $1)=yes
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
	  _LT_TAGVAR(hardcode_libdir_separator, $1)=
	  fi
	  ;;
	esac
	shared_flag='-shared'
	if test "$aix_use_runtimelinking" = yes; then
	  shared_flag="$shared_flag "'${wl}-G'
	fi
	_LT_TAGVAR(link_all_deplibs, $1)=no
      else
	# not using gcc
	if test "$host_cpu" = ia64; then
	# VisualAge C++, Version 5.5 for AIX 5L for IA-64, Beta 3 Release
	# chokes on -Wl,-G. The following line is correct:
	  shared_flag='-G'
	else
	  if test "$aix_use_runtimelinking" = yes; then
	    shared_flag='${wl}-G'
	  else
	    shared_flag='${wl}-bM:SRE'
	  fi
	fi
      fi

      _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-bexpall'
      # It seems that -bexpall does not export symbols beginning with
      # underscore (_), so it is better to generate a list of symbols to export.
      _LT_TAGVAR(always_export_symbols, $1)=yes
      if test "$aix_use_runtimelinking" = yes; then
	# Warning - without using the other runtime loading flags (-brtl),
	# -berok will link without error, but may produce a broken library.
	_LT_TAGVAR(allow_undefined_flag, $1)='-berok'
        # Determine the default libpath from the value encoded in an
        # empty executable.
        _LT_SYS_MODULE_PATH_AIX([$1])
        _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-blibpath:$libdir:'"$aix_libpath"
        _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -o $output_objdir/$soname $libobjs $deplibs '"\${wl}$no_entry_flag"' $compiler_flags `if test "x${allow_undefined_flag}" != "x"; then func_echo_all "${wl}${allow_undefined_flag}"; else :; fi` '"\${wl}$exp_sym_flag:\$export_symbols $shared_flag"
      else
	if test "$host_cpu" = ia64; then
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-R $libdir:/usr/lib:/lib'
	  _LT_TAGVAR(allow_undefined_flag, $1)="-z nodefs"
	  _LT_TAGVAR(archive_expsym_cmds, $1)="\$CC $shared_flag"' -o $output_objdir/$soname $libobjs $deplibs '"\${wl}$no_entry_flag"' $compiler_flags ${wl}${allow_undefined_flag} '"\${wl}$exp_sym_flag:\$export_symbols"
	else
	 # Determine the default libpath from the value encoded in an
	 # empty executable.
	 _LT_SYS_MODULE_PATH_AIX([$1])
	 _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-blibpath:$libdir:'"$aix_libpath"
	  # Warning - without using the other run time loading flags,
	  # -berok will link without error, but may produce a broken library.
	  _LT_TAGVAR(no_undefined_flag, $1)=' ${wl}-bernotok'
	  _LT_TAGVAR(allow_undefined_flag, $1)=' ${wl}-berok'
	  if test "$with_gnu_ld" = yes; then
	    # We only use this code for GNU lds that support --whole-archive.
	    _LT_TAGVAR(whole_archive_flag_spec, $1)='${wl}--whole-archive$convenience ${wl}--no-whole-archive'
	  else
	    # Exported symbols can be pulled into shared objects from archives
	    _LT_TAGVAR(whole_archive_flag_spec, $1)='$convenience'
	  fi
	  _LT_TAGVAR(archive_cmds_need_lc, $1)=yes
	  # This is similar to how AIX traditionally builds its shared libraries.
	  _LT_TAGVAR(archive_expsym_cmds, $1)="\$CC $shared_flag"' -o $output_objdir/$soname $libobjs $deplibs ${wl}-bnoentry $compiler_flags ${wl}-bE:$export_symbols${allow_undefined_flag}~$AR $AR_FLAGS $output_objdir/$libname$release.a $output_objdir/$soname'
	fi
      fi
      ;;

    amigaos*)
      case $host_cpu in
      powerpc)
            # see comment about AmigaOS4 .so support
            _LT_TAGVAR(archive_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
            _LT_TAGVAR(archive_expsym_cmds, $1)=''
        ;;
      m68k)
            _LT_TAGVAR(archive_cmds, $1)='$RM $output_objdir/a2ixlibrary.data~$ECHO "#define NAME $libname" > $output_objdir/a2ixlibrary.data~$ECHO "#define LIBRARY_ID 1" >> $output_objdir/a2ixlibrary.data~$ECHO "#define VERSION $major" >> $output_objdir/a2ixlibrary.data~$ECHO "#define REVISION $revision" >> $output_objdir/a2ixlibrary.data~$AR $AR_FLAGS $lib $libobjs~$RANLIB $lib~(cd $output_objdir && a2ixlibrary -32)'
            _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
            _LT_TAGVAR(hardcode_minus_L, $1)=yes
        ;;
      esac
      ;;

    bsdi[[45]]*)
      _LT_TAGVAR(export_dynamic_flag_spec, $1)=-rdynamic
      ;;

    cygwin* | mingw* | pw32* | cegcc*)
      # When not using gcc, we currently assume that we are using
      # Microsoft Visual C++.
      # hardcode_libdir_flag_spec is actually meaningless, as there is
      # no search path for DLLs.
      case $cc_basename in
      cl*)
	# Native MSVC
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)=' '
	_LT_TAGVAR(allow_undefined_flag, $1)=unsupported
	_LT_TAGVAR(always_export_symbols, $1)=yes
	_LT_TAGVAR(file_list_spec, $1)='@'
	# Tell ltmain to make .lib files, not .a files.
	libext=lib
	# Tell ltmain to make .dll files, not .so files.
	shrext_cmds=".dll"
	# FIXME: Setting linknames here is a bad hack.
	_LT_TAGVAR(archive_cmds, $1)='$CC -o $output_objdir/$soname $libobjs $compiler_flags $deplibs -Wl,-dll~linknames='
	_LT_TAGVAR(archive_expsym_cmds, $1)='if test "x`$SED 1q $export_symbols`" = xEXPORTS; then
	    sed -n -e 's/\\\\\\\(.*\\\\\\\)/-link\\\ -EXPORT:\\\\\\\1/' -e '1\\\!p' < $export_symbols > $output_objdir/$soname.exp;
	  else
	    sed -e 's/\\\\\\\(.*\\\\\\\)/-link\\\ -EXPORT:\\\\\\\1/' < $export_symbols > $output_objdir/$soname.exp;
	  fi~
	  $CC -o $tool_output_objdir$soname $libobjs $compiler_flags $deplibs "@$tool_output_objdir$soname.exp" -Wl,-DLL,-IMPLIB:"$tool_output_objdir$libname.dll.lib"~
	  linknames='
	# The linker will not automatically build a static lib if we build a DLL.
	# _LT_TAGVAR(old_archive_from_new_cmds, $1)='true'
	_LT_TAGVAR(enable_shared_with_static_runtimes, $1)=yes
	_LT_TAGVAR(exclude_expsyms, $1)='_NULL_IMPORT_DESCRIPTOR|_IMPORT_DESCRIPTOR_.*'
	_LT_TAGVAR(export_symbols_cmds, $1)='$NM $libobjs $convenience | $global_symbol_pipe | $SED -e '\''/^[[BCDGRS]][[ ]]/s/.*[[ ]]\([[^ ]]*\)/\1,DATA/'\'' | $SED -e '\''/^[[AITW]][[ ]]/s/.*[[ ]]//'\'' | sort | uniq > $export_symbols'
	# Don't use ranlib
	_LT_TAGVAR(old_postinstall_cmds, $1)='chmod 644 $oldlib'
	_LT_TAGVAR(postlink_cmds, $1)='lt_outputfile="@OUTPUT@"~
	  lt_tool_outputfile="@TOOL_OUTPUT@"~
	  case $lt_outputfile in
	    *.exe|*.EXE) ;;
	    *)
	      lt_outputfile="$lt_outputfile.exe"
	      lt_tool_outputfile="$lt_tool_outputfile.exe"
	      ;;
	  esac~
	  if test "$MANIFEST_TOOL" != ":" && test -f "$lt_outputfile.manifest"; then
	    $MANIFEST_TOOL -manifest "$lt_tool_outputfile.manifest" -outputresource:"$lt_tool_outputfile" || exit 1;
	    $RM "$lt_outputfile.manifest";
	  fi'
	;;
      *)
	# Assume MSVC wrapper
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)=' '
	_LT_TAGVAR(allow_undefined_flag, $1)=unsupported
	# Tell ltmain to make .lib files, not .a files.
	libext=lib
	# Tell ltmain to make .dll files, not .so files.
	shrext_cmds=".dll"
	# FIXME: Setting linknames here is a bad hack.
	_LT_TAGVAR(archive_cmds, $1)='$CC -o $lib $libobjs $compiler_flags `func_echo_all "$deplibs" | $SED '\''s/ -lc$//'\''` -link -dll~linknames='
	# The linker will automatically build a .lib file if we build a DLL.
	_LT_TAGVAR(old_archive_from_new_cmds, $1)='true'
	# FIXME: Should let the user specify the lib program.
	_LT_TAGVAR(old_archive_cmds, $1)='lib -OUT:$oldlib$oldobjs$old_deplibs'
	_LT_TAGVAR(enable_shared_with_static_runtimes, $1)=yes
	;;
      esac
      ;;

    darwin* | rhapsody*)
      _LT_DARWIN_LINKER_FEATURES($1)
      ;;

    dgux*)
      _LT_TAGVAR(archive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    # FreeBSD 2.2.[012] allows us to include c++rt0.o to get C++ constructor
    # support.  Future versions do this automatically, but an explicit c++rt0.o
    # does not break anything, and helps significantly (at the cost of a little
    # extra space).
    freebsd2.2*)
      _LT_TAGVAR(archive_cmds, $1)='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags /usr/lib/c++rt0.o'
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    # Unfortunately, older versions of FreeBSD 2 do not have this feature.
    freebsd2.*)
      _LT_TAGVAR(archive_cmds, $1)='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags'
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_minus_L, $1)=yes
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    # FreeBSD 3 and greater uses gcc -shared to do shared libraries.
    freebsd* | dragonfly*)
      _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag -o $lib $libobjs $deplibs $compiler_flags'
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    hpux9*)
      if test "$GCC" = yes; then
	_LT_TAGVAR(archive_cmds, $1)='$RM $output_objdir/$soname~$CC -shared $pic_flag ${wl}+b ${wl}$install_libdir -o $output_objdir/$soname $libobjs $deplibs $compiler_flags~test $output_objdir/$soname = $lib || mv $output_objdir/$soname $lib'
      else
	_LT_TAGVAR(archive_cmds, $1)='$RM $output_objdir/$soname~$LD -b +b $install_libdir -o $output_objdir/$soname $libobjs $deplibs $linker_flags~test $output_objdir/$soname = $lib || mv $output_objdir/$soname $lib'
      fi
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}+b ${wl}$libdir'
      _LT_TAGVAR(hardcode_libdir_separator, $1)=:
      _LT_TAGVAR(hardcode_direct, $1)=yes

      # hardcode_minus_L: Not really in the search PATH,
      # but as the default location of the library.
      _LT_TAGVAR(hardcode_minus_L, $1)=yes
      _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'
      ;;

    hpux10*)
      if test "$GCC" = yes && test "$with_gnu_ld" = no; then
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdir -o $lib $libobjs $deplibs $compiler_flags'
      else
	_LT_TAGVAR(archive_cmds, $1)='$LD -b +h $soname +b $install_libdir -o $lib $libobjs $deplibs $linker_flags'
      fi
      if test "$with_gnu_ld" = no; then
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}+b ${wl}$libdir'
	_LT_TAGVAR(hardcode_libdir_separator, $1)=:
	_LT_TAGVAR(hardcode_direct, $1)=yes
	_LT_TAGVAR(hardcode_direct_absolute, $1)=yes
	_LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'
	# hardcode_minus_L: Not really in the search PATH,
	# but as the default location of the library.
	_LT_TAGVAR(hardcode_minus_L, $1)=yes
      fi
      ;;

    hpux11*)
      if test "$GCC" = yes && test "$with_gnu_ld" = no; then
	case $host_cpu in
	hppa*64*)
	  _LT_TAGVAR(archive_cmds, $1)='$CC -shared ${wl}+h ${wl}$soname -o $lib $libobjs $deplibs $compiler_flags'
	  ;;
	ia64*)
	  _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag ${wl}+h ${wl}$soname ${wl}+nodefaultrpath -o $lib $libobjs $deplibs $compiler_flags'
	  ;;
	*)
	  _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdir -o $lib $libobjs $deplibs $compiler_flags'
	  ;;
	esac
      else
	case $host_cpu in
	hppa*64*)
	  _LT_TAGVAR(archive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname -o $lib $libobjs $deplibs $compiler_flags'
	  ;;
	ia64*)
	  _LT_TAGVAR(archive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname ${wl}+nodefaultrpath -o $lib $libobjs $deplibs $compiler_flags'
	  ;;
	*)
	m4_if($1, [], [
	  # Older versions of the 11.00 compiler do not understand -b yet
	  # (HP92453-01 A.11.01.20 doesn't, HP92453-01 B.11.X.35175-35176.GP does)
	  _LT_LINKER_OPTION([if $CC understands -b],
	    _LT_TAGVAR(lt_cv_prog_compiler__b, $1), [-b],
	    [_LT_TAGVAR(archive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdir -o $lib $libobjs $deplibs $compiler_flags'],
	    [_LT_TAGVAR(archive_cmds, $1)='$LD -b +h $soname +b $install_libdir -o $lib $libobjs $deplibs $linker_flags'])],
	  [_LT_TAGVAR(archive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdir -o $lib $libobjs $deplibs $compiler_flags'])
	  ;;
	esac
      fi
      if test "$with_gnu_ld" = no; then
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}+b ${wl}$libdir'
	_LT_TAGVAR(hardcode_libdir_separator, $1)=:

	case $host_cpu in
	hppa*64*|ia64*)
	  _LT_TAGVAR(hardcode_direct, $1)=no
	  _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	  ;;
	*)
	  _LT_TAGVAR(hardcode_direct, $1)=yes
	  _LT_TAGVAR(hardcode_direct_absolute, $1)=yes
	  _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'

	  # hardcode_minus_L: Not really in the search PATH,
	  # but as the default location of the library.
	  _LT_TAGVAR(hardcode_minus_L, $1)=yes
	  ;;
	esac
      fi
      ;;

    irix5* | irix6* | nonstopux*)
      if test "$GCC" = yes; then
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
	# Try to use the -exported_symbol ld option, if it does not
	# work, assume that -exports_file does not work either and
	# implicitly export all symbols.
	# This should be the same for all languages, so no per-tag cache variable.
	AC_CACHE_CHECK([whether the $host_os linker accepts -exported_symbol],
	  [lt_cv_irix_exported_symbol],
	  [save_LDFLAGS="$LDFLAGS"
	   LDFLAGS="$LDFLAGS -shared ${wl}-exported_symbol ${wl}foo ${wl}-update_registry ${wl}/dev/null"
	   AC_LINK_IFELSE(
	     [AC_LANG_SOURCE(
	        [AC_LANG_CASE([C], [[int foo (void) { return 0; }]],
			      [C++], [[int foo (void) { return 0; }]],
			      [Fortran 77], [[
      subroutine foo
      end]],
			      [Fortran], [[
      subroutine foo
      end]])])],
	      [lt_cv_irix_exported_symbol=yes],
	      [lt_cv_irix_exported_symbol=no])
           LDFLAGS="$save_LDFLAGS"])
	if test "$lt_cv_irix_exported_symbol" = yes; then
          _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` ${wl}-update_registry ${wl}${output_objdir}/so_locations ${wl}-exports_file ${wl}$export_symbols -o $lib'
	fi
      else
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags -soname $soname `test -n "$verstring" && func_echo_all "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags -soname $soname `test -n "$verstring" && func_echo_all "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -exports_file $export_symbols -o $lib'
      fi
      _LT_TAGVAR(archive_cmds_need_lc, $1)='no'
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
      _LT_TAGVAR(hardcode_libdir_separator, $1)=:
      _LT_TAGVAR(inherit_rpath, $1)=yes
      _LT_TAGVAR(link_all_deplibs, $1)=yes
      ;;

    netbsd* | netbsdelf*-gnu)
      if echo __ELF__ | $CC -E - | $GREP __ELF__ >/dev/null; then
	_LT_TAGVAR(archive_cmds, $1)='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags'  # a.out
      else
	_LT_TAGVAR(archive_cmds, $1)='$LD -shared -o $lib $libobjs $deplibs $linker_flags'      # ELF
      fi
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    newsos6)
      _LT_TAGVAR(archive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
      _LT_TAGVAR(hardcode_libdir_separator, $1)=:
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    *nto* | *qnx*)
      ;;

    openbsd*)
      if test -f /usr/libexec/ld.so; then
	_LT_TAGVAR(hardcode_direct, $1)=yes
	_LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	_LT_TAGVAR(hardcode_direct_absolute, $1)=yes
	if test -z "`echo __ELF__ | $CC -E - | $GREP __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powerpc"; then
	  _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag -o $lib $libobjs $deplibs $compiler_flags'
	  _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag -o $lib $libobjs $deplibs $compiler_flags ${wl}-retain-symbols-file,$export_symbols'
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
	  _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'
	else
	  case $host_os in
	   openbsd[[01]].* | openbsd2.[[0-7]] | openbsd2.[[0-7]].*)
	     _LT_TAGVAR(archive_cmds, $1)='$LD -Bshareable -o $lib $libobjs $deplibs $linker_flags'
	     _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
	     ;;
	   *)
	     _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag -o $lib $libobjs $deplibs $compiler_flags'
	     _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
	     ;;
	  esac
	fi
      else
	_LT_TAGVAR(ld_shlibs, $1)=no
      fi
      ;;

    os2*)
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
      _LT_TAGVAR(hardcode_minus_L, $1)=yes
      _LT_TAGVAR(allow_undefined_flag, $1)=unsupported
      _LT_TAGVAR(archive_cmds, $1)='$ECHO "LIBRARY $libname INITINSTANCE" > $output_objdir/$libname.def~$ECHO "DESCRIPTION \"$libname\"" >> $output_objdir/$libname.def~echo DATA >> $output_objdir/$libname.def~echo " SINGLE NONSHARED" >> $output_objdir/$libname.def~echo EXPORTS >> $output_objdir/$libname.def~emxexp $libobjs >> $output_objdir/$libname.def~$CC -Zdll -Zcrtdll -o $lib $libobjs $deplibs $compiler_flags $output_objdir/$libname.def'
      _LT_TAGVAR(old_archive_from_new_cmds, $1)='emximp -o $output_objdir/$libname.a $output_objdir/$libname.def'
      ;;

    osf3*)
      if test "$GCC" = yes; then
	_LT_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unresolved ${wl}\*'
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared${allow_undefined_flag} $libobjs $deplibs $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
      else
	_LT_TAGVAR(allow_undefined_flag, $1)=' -expect_unresolved \*'
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared${allow_undefined_flag} $libobjs $deplibs $compiler_flags -soname $soname `test -n "$verstring" && func_echo_all "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib'
      fi
      _LT_TAGVAR(archive_cmds_need_lc, $1)='no'
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
      _LT_TAGVAR(hardcode_libdir_separator, $1)=:
      ;;

    osf4* | osf5*)	# as osf3* with the addition of -msym flag
      if test "$GCC" = yes; then
	_LT_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unresolved ${wl}\*'
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared${allow_undefined_flag} $pic_flag $libobjs $deplibs $compiler_flags ${wl}-msym ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
      else
	_LT_TAGVAR(allow_undefined_flag, $1)=' -expect_unresolved \*'
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared${allow_undefined_flag} $libobjs $deplibs $compiler_flags -msym -soname $soname `test -n "$verstring" && func_echo_all "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib'
	_LT_TAGVAR(archive_expsym_cmds, $1)='for i in `cat $export_symbols`; do printf "%s %s\\n" -exported_symbol "\$i" >> $lib.exp; done; printf "%s\\n" "-hidden">> $lib.exp~
	$CC -shared${allow_undefined_flag} ${wl}-input ${wl}$lib.exp $compiler_flags $libobjs $deplibs -soname $soname `test -n "$verstring" && $ECHO "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib~$RM $lib.exp'

	# Both c and cxx compiler support -rpath directly
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-rpath $libdir'
      fi
      _LT_TAGVAR(archive_cmds_need_lc, $1)='no'
      _LT_TAGVAR(hardcode_libdir_separator, $1)=:
      ;;

    solaris*)
      _LT_TAGVAR(no_undefined_flag, $1)=' -z defs'
      if test "$GCC" = yes; then
	wlarc='${wl}'
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag ${wl}-z ${wl}text ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compiler_flags'
	_LT_TAGVAR(archive_expsym_cmds, $1)='echo "{ global:" > $lib.exp~cat $export_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~echo "local: *; };" >> $lib.exp~
	  $CC -shared $pic_flag ${wl}-z ${wl}text ${wl}-M ${wl}$lib.exp ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compiler_flags~$RM $lib.exp'
      else
	case `$CC -V 2>&1` in
	*"Compilers 5.0"*)
	  wlarc=''
	  _LT_TAGVAR(archive_cmds, $1)='$LD -G${allow_undefined_flag} -h $soname -o $lib $libobjs $deplibs $linker_flags'
	  _LT_TAGVAR(archive_expsym_cmds, $1)='echo "{ global:" > $lib.exp~cat $export_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~echo "local: *; };" >> $lib.exp~
	  $LD -G${allow_undefined_flag} -M $lib.exp -h $soname -o $lib $libobjs $deplibs $linker_flags~$RM $lib.exp'
	  ;;
	*)
	  wlarc='${wl}'
	  _LT_TAGVAR(archive_cmds, $1)='$CC -G${allow_undefined_flag} -h $soname -o $lib $libobjs $deplibs $compiler_flags'
	  _LT_TAGVAR(archive_expsym_cmds, $1)='echo "{ global:" > $lib.exp~cat $export_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~echo "local: *; };" >> $lib.exp~
	  $CC -G${allow_undefined_flag} -M $lib.exp -h $soname -o $lib $libobjs $deplibs $compiler_flags~$RM $lib.exp'
	  ;;
	esac
      fi
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      case $host_os in
      solaris2.[[0-5]] | solaris2.[[0-5]].*) ;;
      *)
	# The compiler driver will combine and reorder linker options,
	# but understands `-z linker_flag'.  GCC discards it without `$wl',
	# but is careful enough not to reorder.
	# Supported since Solaris 2.6 (maybe 2.5.1?)
	if test "$GCC" = yes; then
	  _LT_TAGVAR(whole_archive_flag_spec, $1)='${wl}-z ${wl}allextract$convenience ${wl}-z ${wl}defaultextract'
	else
	  _LT_TAGVAR(whole_archive_flag_spec, $1)='-z allextract$convenience -z defaultextract'
	fi
	;;
      esac
      _LT_TAGVAR(link_all_deplibs, $1)=yes
      ;;

    sunos4*)
      if test "x$host_vendor" = xsequent; then
	# Use $CC to link under sequent, because it throws in some extra .o
	# files that make .init and .fini sections work.
	_LT_TAGVAR(archive_cmds, $1)='$CC -G ${wl}-h $soname -o $lib $libobjs $deplibs $compiler_flags'
      else
	_LT_TAGVAR(archive_cmds, $1)='$LD -assert pure-text -Bstatic -o $lib $libobjs $deplibs $linker_flags'
      fi
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
      _LT_TAGVAR(hardcode_direct, $1)=yes
      _LT_TAGVAR(hardcode_minus_L, $1)=yes
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    sysv4)
      case $host_vendor in
	sni)
	  _LT_TAGVAR(archive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
	  _LT_TAGVAR(hardcode_direct, $1)=yes # is this really true???
	;;
	siemens)
	  ## LD is ld it makes a PLAMLIB
	  ## CC just makes a GrossModule.
	  _LT_TAGVAR(archive_cmds, $1)='$LD -G -o $lib $libobjs $deplibs $linker_flags'
	  _LT_TAGVAR(reload_cmds, $1)='$CC -r -o $output$reload_objs'
	  _LT_TAGVAR(hardcode_direct, $1)=no
        ;;
	motorola)
	  _LT_TAGVAR(archive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
	  _LT_TAGVAR(hardcode_direct, $1)=no #Motorola manual says yes, but my tests say they lie
	;;
      esac
      runpath_var='LD_RUN_PATH'
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    sysv4.3*)
      _LT_TAGVAR(archive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      _LT_TAGVAR(export_dynamic_flag_spec, $1)='-Bexport'
      ;;

    sysv4*MP*)
      if test -d /usr/nec; then
	_LT_TAGVAR(archive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
	_LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	runpath_var=LD_RUN_PATH
	hardcode_runpath_var=yes
	_LT_TAGVAR(ld_shlibs, $1)=yes
      fi
      ;;

    sysv4*uw2* | sysv5OpenUNIX* | sysv5UnixWare7.[[01]].[[10]]* | unixware7* | sco3.2v5.0.[[024]]*)
      _LT_TAGVAR(no_undefined_flag, $1)='${wl}-z,text'
      _LT_TAGVAR(archive_cmds_need_lc, $1)=no
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      runpath_var='LD_RUN_PATH'

      if test "$GCC" = yes; then
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
      else
	_LT_TAGVAR(archive_cmds, $1)='$CC -G ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -G ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
      fi
      ;;

    sysv5* | sco3.2v5* | sco5v6*)
      # Note: We can NOT use -z defs as we might desire, because we do not
      # link with -lc, and that would cause any symbols used from libc to
      # always be unresolved, which means just about no library would
      # ever link correctly.  If we're not using GNU ld we use -z text
      # though, which does catch some bad symbols but isn't as heavy-handed
      # as -z defs.
      _LT_TAGVAR(no_undefined_flag, $1)='${wl}-z,text'
      _LT_TAGVAR(allow_undefined_flag, $1)='${wl}-z,nodefs'
      _LT_TAGVAR(archive_cmds_need_lc, $1)=no
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-R,$libdir'
      _LT_TAGVAR(hardcode_libdir_separator, $1)=':'
      _LT_TAGVAR(link_all_deplibs, $1)=yes
      _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-Bexport'
      runpath_var='LD_RUN_PATH'

      if test "$GCC" = yes; then
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
      else
	_LT_TAGVAR(archive_cmds, $1)='$CC -G ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -G ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
      fi
      ;;

    uts4*)
      _LT_TAGVAR(archive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linker_flags'
      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      ;;

    *)
      _LT_TAGVAR(ld_shlibs, $1)=no
      ;;
    esac

    if test x$host_vendor = xsni; then
      case $host in
      sysv4 | sysv4.2uw2* | sysv4.3* | sysv5*)
	_LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-Blargedynsym'
	;;
      esac
    fi
  fi
])
AC_MSG_RESULT([$_LT_TAGVAR(ld_shlibs, $1)])
test "$_LT_TAGVAR(ld_shlibs, $1)" = no && can_build_shared=no

_LT_TAGVAR(with_gnu_ld, $1)=$with_gnu_ld

_LT_DECL([], [libext], [0], [Old archive suffix (normally "a")])dnl
_LT_DECL([], [shrext_cmds], [1], [Shared library suffix (normally ".so")])dnl
_LT_DECL([], [extract_expsyms_cmds], [2],
    [The commands to extract the exported symbol list from a shared archive])

#
# Do we need to explicitly link libc?
#
case "x$_LT_TAGVAR(archive_cmds_need_lc, $1)" in
x|xyes)
  # Assume -lc should be added
  _LT_TAGVAR(archive_cmds_need_lc, $1)=yes

  if test "$enable_shared" = yes && test "$GCC" = yes; then
    case $_LT_TAGVAR(archive_cmds, $1) in
    *'~'*)
      # FIXME: we may have to deal with multi-command sequences.
      ;;
    '$CC '*)
      # Test whether the compiler implicitly links with -lc since on some
      # systems, -lgcc has to come before -lc. If gcc already passes -lc
      # to ld, don't add -lc before -lgcc.
      AC_CACHE_CHECK([whether -lc should be explicitly linked in],
	[lt_cv_]_LT_TAGVAR(archive_cmds_need_lc, $1),
	[$RM conftest*
	echo "$lt_simple_compile_test_code" > conftest.$ac_ext

	if AC_TRY_EVAL(ac_compile) 2>conftest.err; then
	  soname=conftest
	  lib=conftest
	  libobjs=conftest.$ac_objext
	  deplibs=
	  wl=$_LT_TAGVAR(lt_prog_compiler_wl, $1)
	  pic_flag=$_LT_TAGVAR(lt_prog_compiler_pic, $1)
	  compiler_flags=-v
	  linker_flags=-v
	  verstring=
	  output_objdir=.
	  libname=conftest
	  lt_save_allow_undefined_flag=$_LT_TAGVAR(allow_undefined_flag, $1)
	  _LT_TAGVAR(allow_undefined_flag, $1)=
	  if AC_TRY_EVAL(_LT_TAGVAR(archive_cmds, $1) 2\>\&1 \| $GREP \" -lc \" \>/dev/null 2\>\&1)
	  then
	    lt_cv_[]_LT_TAGVAR(archive_cmds_need_lc, $1)=no
	  else
	    lt_cv_[]_LT_TAGVAR(archive_cmds_need_lc, $1)=yes
	  fi
	  _LT_TAGVAR(allow_undefined_flag, $1)=$lt_save_allow_undefined_flag
	else
	  cat conftest.err 1>&5
	fi
	$RM conftest*
	])
      _LT_TAGVAR(archive_cmds_need_lc, $1)=$lt_cv_[]_LT_TAGVAR(archive_cmds_need_lc, $1)
      ;;
    esac
  fi
  ;;
esac

_LT_TAGDECL([build_libtool_need_lc], [archive_cmds_need_lc], [0],
    [Whether or not to add -lc for building shared libraries])
_LT_TAGDECL([allow_libtool_libs_with_static_runtimes],
    [enable_shared_with_static_runtimes], [0],
    [Whether or not to disallow shared libs when runtime libs are static])
_LT_TAGDECL([], [export_dynamic_flag_spec], [1],
    [Compiler flag to allow reflexive dlopens])
_LT_TAGDECL([], [whole_archive_flag_spec], [1],
    [Compiler flag to generate shared objects directly from archives])
_LT_TAGDECL([], [compiler_needs_object], [1],
    [Whether the compiler copes with passing no objects directly])
_LT_TAGDECL([], [old_archive_from_new_cmds], [2],
    [Create an old-style archive from a shared archive])
_LT_TAGDECL([], [old_archive_from_expsyms_cmds], [2],
    [Create a temporary old-style archive to link instead of a shared archive])
_LT_TAGDECL([], [archive_cmds], [2], [Commands used to build a shared archive])
_LT_TAGDECL([], [archive_expsym_cmds], [2])
_LT_TAGDECL([], [module_cmds], [2],
    [Commands used to build a loadable module if different from building
    a shared archive.])
_LT_TAGDECL([], [module_expsym_cmds], [2])
_LT_TAGDECL([], [with_gnu_ld], [1],
    [Whether we are building with GNU ld or not])
_LT_TAGDECL([], [allow_undefined_flag], [1],
    [Flag that allows shared libraries with undefined symbols to be built])
_LT_TAGDECL([], [no_undefined_flag], [1],
    [Flag that enforces no undefined symbols])
_LT_TAGDECL([], [hardcode_libdir_flag_spec], [1],
    [Flag to hardcode $libdir into a binary during linking.
    This must work even if $libdir does not exist])
_LT_TAGDECL([], [hardcode_libdir_separator], [1],
    [Whether we need a single "-rpath" flag with a separated argument])
_LT_TAGDECL([], [hardcode_direct], [0],
    [Set to "yes" if using DIR/libNAME${shared_ext} during linking hardcodes
    DIR into the resulting binary])
_LT_TAGDECL([], [hardcode_direct_absolute], [0],
    [Set to "yes" if using DIR/libNAME${shared_ext} during linking hardcodes
    DIR into the resulting binary and the resulting library dependency is
    "absolute", i.e impossible to change by setting ${shlibpath_var} if the
    library is relocated])
_LT_TAGDECL([], [hardcode_minus_L], [0],
    [Set to "yes" if using the -LDIR flag during linking hardcodes DIR
    into the resulting binary])
_LT_TAGDECL([], [hardcode_shlibpath_var], [0],
    [Set to "yes" if using SHLIBPATH_VAR=DIR during linking hardcodes DIR
    into the resulting binary])
_LT_TAGDECL([], [hardcode_automatic], [0],
    [Set to "yes" if building a shared library automatically hardcodes DIR
    into the library and all subsequent libraries and executables linked
    against it])
_LT_TAGDECL([], [inherit_rpath], [0],
    [Set to yes if linker adds runtime paths of dependent libraries
    to runtime path list])
_LT_TAGDECL([], [link_all_deplibs], [0],
    [Whether libtool must link a program against all its dependency libraries])
_LT_TAGDECL([], [always_export_symbols], [0],
    [Set to "yes" if exported symbols are required])
_LT_TAGDECL([], [export_symbols_cmds], [2],
    [The commands to list exported symbols])
_LT_TAGDECL([], [exclude_expsyms], [1],
    [Symbols that should not be listed in the preloaded symbols])
_LT_TAGDECL([], [include_expsyms], [1],
    [Symbols that must always be exported])
_LT_TAGDECL([], [prelink_cmds], [2],
    [Commands necessary for linking programs (against libraries) with templates])
_LT_TAGDECL([], [postlink_cmds], [2],
    [Commands necessary for finishing linking programs])
_LT_TAGDECL([], [file_list_spec], [1],
    [Specify filename containing input files])
dnl FIXME: Not yet implemented
dnl _LT_TAGDECL([], [thread_safe_flag_spec], [1],
dnl    [Compiler flag to generate thread safe objects])
])# _LT_LINKER_SHLIBS


# _LT_LANG_C_CONFIG([TAG])
# ------------------------
# Ensure that the configuration variables for a C compiler are suitably
# defined.  These variables are subsequently used by _LT_CONFIG to write
# the compiler configuration to `libtool'.
m4_defun([_LT_LANG_C_CONFIG],
[m4_require([_LT_DECL_EGREP])dnl
lt_save_CC="$CC"
AC_LANG_PUSH(C)

# Source file extension for C test sources.
ac_ext=c

# Object file extension for compiled C test sources.
objext=o
_LT_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code="int some_variable = 0;"

# Code to be used in simple link tests
lt_simple_link_test_code='int main(){return(0);}'

_LT_TAG_COMPILER
# Save the default compiler, since it gets overwritten when the other
# tags are being tested, and _LT_TAGVAR(compiler, []) is a NOP.
compiler_DEFAULT=$CC

# save warnings/boilerplate of simple test code
_LT_COMPILER_BOILERPLATE
_LT_LINKER_BOILERPLATE

if test -n "$compiler"; then
  _LT_COMPILER_NO_RTTI($1)
  _LT_COMPILER_PIC($1)
  _LT_COMPILER_C_O($1)
  _LT_COMPILER_FILE_LOCKS($1)
  _LT_LINKER_SHLIBS($1)
  _LT_SYS_DYNAMIC_LINKER($1)
  _LT_LINKER_HARDCODE_LIBPATH($1)
  LT_SYS_DLOPEN_SELF
  _LT_CMD_STRIPLIB

  # Report which library types will actually be built
  AC_MSG_CHECKING([if libtool supports shared libraries])
  AC_MSG_RESULT([$can_build_shared])

  AC_MSG_CHECKING([whether to build shared libraries])
  test "$can_build_shared" = "no" && enable_shared=no

  # On AIX, shared libraries and static libraries use the same namespace, and
  # are all built from PIC.
  case $host_os in
  aix3*)
    test "$enable_shared" = yes && enable_static=no
    if test -n "$RANLIB"; then
      archive_cmds="$archive_cmds~\$RANLIB \$lib"
      postinstall_cmds='$RANLIB $lib'
    fi
    ;;

  aix[[4-9]]*)
    if test "$host_cpu" != ia64 && test "$aix_use_runtimelinking" = no ; then
      test "$enable_shared" = yes && enable_static=no
    fi
    ;;
  esac
  AC_MSG_RESULT([$enable_shared])

  AC_MSG_CHECKING([whether to build static libraries])
  # Make sure either enable_shared or enable_static is yes.
  test "$enable_shared" = yes || enable_static=yes
  AC_MSG_RESULT([$enable_static])

  _LT_CONFIG($1)
fi
AC_LANG_POP
CC="$lt_save_CC"
])# _LT_LANG_C_CONFIG


# _LT_LANG_CXX_CONFIG([TAG])
# --------------------------
# Ensure that the configuration variables for a C++ compiler are suitably
# defined.  These variables are subsequently used by _LT_CONFIG to write
# the compiler configuration to `libtool'.
m4_defun([_LT_LANG_CXX_CONFIG],
[m4_require([_LT_FILEUTILS_DEFAULTS])dnl
m4_require([_LT_DECL_EGREP])dnl
m4_require([_LT_PATH_MANIFEST_TOOL])dnl
if test -n "$CXX" && ( test "X$CXX" != "Xno" &&
    ( (test "X$CXX" = "Xg++" && `g++ -v >/dev/null 2>&1` ) ||
    (test "X$CXX" != "Xg++"))) ; then
  AC_PROG_CXXCPP
else
  _lt_caught_CXX_error=yes
fi

AC_LANG_PUSH(C++)
_LT_TAGVAR(archive_cmds_need_lc, $1)=no
_LT_TAGVAR(allow_undefined_flag, $1)=
_LT_TAGVAR(always_export_symbols, $1)=no
_LT_TAGVAR(archive_expsym_cmds, $1)=
_LT_TAGVAR(compiler_needs_object, $1)=no
_LT_TAGVAR(export_dynamic_flag_spec, $1)=
_LT_TAGVAR(hardcode_direct, $1)=no
_LT_TAGVAR(hardcode_direct_absolute, $1)=no
_LT_TAGVAR(hardcode_libdir_flag_spec, $1)=
_LT_TAGVAR(hardcode_libdir_separator, $1)=
_LT_TAGVAR(hardcode_minus_L, $1)=no
_LT_TAGVAR(hardcode_shlibpath_var, $1)=unsupported
_LT_TAGVAR(hardcode_automatic, $1)=no
_LT_TAGVAR(inherit_rpath, $1)=no
_LT_TAGVAR(module_cmds, $1)=
_LT_TAGVAR(module_expsym_cmds, $1)=
_LT_TAGVAR(link_all_deplibs, $1)=unknown
_LT_TAGVAR(old_archive_cmds, $1)=$old_archive_cmds
_LT_TAGVAR(reload_flag, $1)=$reload_flag
_LT_TAGVAR(reload_cmds, $1)=$reload_cmds
_LT_TAGVAR(no_undefined_flag, $1)=
_LT_TAGVAR(whole_archive_flag_spec, $1)=
_LT_TAGVAR(enable_shared_with_static_runtimes, $1)=no

# Source file extension for C++ test sources.
ac_ext=cpp

# Object file extension for compiled C++ test sources.
objext=o
_LT_TAGVAR(objext, $1)=$objext

# No sense in running all these tests if we already determined that
# the CXX compiler isn't working.  Some variables (like enable_shared)
# are currently assumed to apply to all compilers on this platform,
# and will be corrupted by setting them based on a non-working compiler.
if test "$_lt_caught_CXX_error" != yes; then
  # Code to be used in simple compile tests
  lt_simple_compile_test_code="int some_variable = 0;"

  # Code to be used in simple link tests
  lt_simple_link_test_code='int main(int, char *[[]]) { return(0); }'

  # ltmain only uses $CC for tagged configurations so make sure $CC is set.
  _LT_TAG_COMPILER

  # save warnings/boilerplate of simple test code
  _LT_COMPILER_BOILERPLATE
  _LT_LINKER_BOILERPLATE

  # Allow CC to be a program name with arguments.
  lt_save_CC=$CC
  lt_save_CFLAGS=$CFLAGS
  lt_save_LD=$LD
  lt_save_GCC=$GCC
  GCC=$GXX
  lt_save_with_gnu_ld=$with_gnu_ld
  lt_save_path_LD=$lt_cv_path_LD
  if test -n "${lt_cv_prog_gnu_ldcxx+set}"; then
    lt_cv_prog_gnu_ld=$lt_cv_prog_gnu_ldcxx
  else
    $as_unset lt_cv_prog_gnu_ld
  fi
  if test -n "${lt_cv_path_LDCXX+set}"; then
    lt_cv_path_LD=$lt_cv_path_LDCXX
  else
    $as_unset lt_cv_path_LD
  fi
  test -z "${LDCXX+set}" || LD=$LDCXX
  CC=${CXX-"c++"}
  CFLAGS=$CXXFLAGS
  compiler=$CC
  _LT_TAGVAR(compiler, $1)=$CC
  _LT_CC_BASENAME([$compiler])

  if test -n "$compiler"; then
    # We don't want -fno-exception when compiling C++ code, so set the
    # no_builtin_flag separately
    if test "$GXX" = yes; then
      _LT_TAGVAR(lt_prog_compiler_no_builtin_flag, $1)=' -fno-builtin'
    else
      _LT_TAGVAR(lt_prog_compiler_no_builtin_flag, $1)=
    fi

    if test "$GXX" = yes; then
      # Set up default GNU C++ configuration

      LT_PATH_LD

      # Check if GNU C++ uses GNU ld as the underlying linker, since the
      # archiving commands below assume that GNU ld is being used.
      if test "$with_gnu_ld" = yes; then
        _LT_TAGVAR(archive_cmds, $1)='$CC $pic_flag -shared -nostdlib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname $wl$soname -o $lib'
        _LT_TAGVAR(archive_expsym_cmds, $1)='$CC $pic_flag -shared -nostdlib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'

        _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
        _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}--export-dynamic'

        # If archive_cmds runs LD, not CC, wlarc should be empty
        # XXX I think wlarc can be eliminated in ltcf-cxx, but I need to
        #     investigate it a little bit more. (MM)
        wlarc='${wl}'

        # ancient GNU ld didn't support --whole-archive et. al.
        if eval "`$CC -print-prog-name=ld` --help 2>&1" |
	  $GREP 'no-whole-archive' > /dev/null; then
          _LT_TAGVAR(whole_archive_flag_spec, $1)="$wlarc"'--whole-archive$convenience '"$wlarc"'--no-whole-archive'
        else
          _LT_TAGVAR(whole_archive_flag_spec, $1)=
        fi
      else
        with_gnu_ld=no
        wlarc=

        # A generic and very simple default shared library creation
        # command for GNU C++ for the case where it uses the native
        # linker, instead of GNU ld.  If possible, this setting should
        # overridden to take advantage of the native linker features on
        # the platform it is being used on.
        _LT_TAGVAR(archive_cmds, $1)='$CC -shared -nostdlib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags -o $lib'
      fi

      # Commands to make compiler produce verbose output that lists
      # what "hidden" libraries, object files and flags are used when
      # linking a shared library.
      output_verbose_link_cmd='$CC -shared $CFLAGS -v conftest.$objext 2>&1 | $GREP -v "^Configured with:" | $GREP "\-L"'

    else
      GXX=no
      with_gnu_ld=no
      wlarc=
    fi

    # PORTME: fill in a description of your system's C++ link characteristics
    AC_MSG_CHECKING([whether the $compiler linker ($LD) supports shared libraries])
    _LT_TAGVAR(ld_shlibs, $1)=yes
    case $host_os in
      aix3*)
        # FIXME: insert proper C++ library support
        _LT_TAGVAR(ld_shlibs, $1)=no
        ;;
      aix[[4-9]]*)
        if test "$host_cpu" = ia64; then
          # On IA64, the linker does run time linking by default, so we don't
          # have to do anything special.
          aix_use_runtimelinking=no
          exp_sym_flag='-Bexport'
          no_entry_flag=""
        else
          aix_use_runtimelinking=no

          # Test if we are trying to use run time linking or normal
          # AIX style linking. If -brtl is somewhere in LDFLAGS, we
          # need to do runtime linking.
          case $host_os in aix4.[[23]]|aix4.[[23]].*|aix[[5-9]]*)
	    for ld_flag in $LDFLAGS; do
	      case $ld_flag in
	      *-brtl*)
	        aix_use_runtimelinking=yes
	        break
	        ;;
	      esac
	    done
	    ;;
          esac

          exp_sym_flag='-bexport'
          no_entry_flag='-bnoentry'
        fi

        # When large executables or shared objects are built, AIX ld can
        # have problems creating the table of contents.  If linking a library
        # or program results in "error TOC overflow" add -mminimal-toc to
        # CXXFLAGS/CFLAGS for g++/gcc.  In the cases where that is not
        # enough to fix the problem, add -Wl,-bbigtoc to LDFLAGS.

        _LT_TAGVAR(archive_cmds, $1)=''
        _LT_TAGVAR(hardcode_direct, $1)=yes
        _LT_TAGVAR(hardcode_direct_absolute, $1)=yes
        _LT_TAGVAR(hardcode_libdir_separator, $1)=':'
        _LT_TAGVAR(link_all_deplibs, $1)=yes
        _LT_TAGVAR(file_list_spec, $1)='${wl}-f,'

        if test "$GXX" = yes; then
          case $host_os in aix4.[[012]]|aix4.[[012]].*)
          # We only want to do this on AIX 4.2 and lower, the check
          # below for broken collect2 doesn't work under 4.3+
	  collect2name=`${CC} -print-prog-name=collect2`
	  if test -f "$collect2name" &&
	     strings "$collect2name" | $GREP resolve_lib_name >/dev/null
	  then
	    # We have reworked collect2
	    :
	  else
	    # We have old collect2
	    _LT_TAGVAR(hardcode_direct, $1)=unsupported
	    # It fails to find uninstalled libraries when the uninstalled
	    # path is not listed in the libpath.  Setting hardcode_minus_L
	    # to unsupported forces relinking
	    _LT_TAGVAR(hardcode_minus_L, $1)=yes
	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
	    _LT_TAGVAR(hardcode_libdir_separator, $1)=
	  fi
          esac
          shared_flag='-shared'
	  if test "$aix_use_runtimelinking" = yes; then
	    shared_flag="$shared_flag "'${wl}-G'
	  fi
        else
          # not using gcc
          if test "$host_cpu" = ia64; then
	  # VisualAge C++, Version 5.5 for AIX 5L for IA-64, Beta 3 Release
	  # chokes on -Wl,-G. The following line is correct:
	  shared_flag='-G'
          else
	    if test "$aix_use_runtimelinking" = yes; then
	      shared_flag='${wl}-G'
	    else
	      shared_flag='${wl}-bM:SRE'
	    fi
          fi
        fi

        _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-bexpall'
        # It seems that -bexpall does not export symbols beginning with
        # underscore (_), so it is better to generate a list of symbols to
	# export.
        _LT_TAGVAR(always_export_symbols, $1)=yes
        if test "$aix_use_runtimelinking" = yes; then
          # Warning - without using the other runtime loading flags (-brtl),
          # -berok will link without error, but may produce a broken library.
          _LT_TAGVAR(allow_undefined_flag, $1)='-berok'
          # Determine the default libpath from the value encoded in an empty
          # executable.
          _LT_SYS_MODULE_PATH_AIX([$1])
          _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-blibpath:$libdir:'"$aix_libpath"

          _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -o $output_objdir/$soname $libobjs $deplibs '"\${wl}$no_entry_flag"' $compiler_flags `if test "x${allow_undefined_flag}" != "x"; then func_echo_all "${wl}${allow_undefined_flag}"; else :; fi` '"\${wl}$exp_sym_flag:\$export_symbols $shared_flag"
        else
          if test "$host_cpu" = ia64; then
	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-R $libdir:/usr/lib:/lib'
	    _LT_TAGVAR(allow_undefined_flag, $1)="-z nodefs"
	    _LT_TAGVAR(archive_expsym_cmds, $1)="\$CC $shared_flag"' -o $output_objdir/$soname $libobjs $deplibs '"\${wl}$no_entry_flag"' $compiler_flags ${wl}${allow_undefined_flag} '"\${wl}$exp_sym_flag:\$export_symbols"
          else
	    # Determine the default libpath from the value encoded in an
	    # empty executable.
	    _LT_SYS_MODULE_PATH_AIX([$1])
	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-blibpath:$libdir:'"$aix_libpath"
	    # Warning - without using the other run time loading flags,
	    # -berok will link without error, but may produce a broken library.
	    _LT_TAGVAR(no_undefined_flag, $1)=' ${wl}-bernotok'
	    _LT_TAGVAR(allow_undefined_flag, $1)=' ${wl}-berok'
	    if test "$with_gnu_ld" = yes; then
	      # We only use this code for GNU lds that support --whole-archive.
	      _LT_TAGVAR(whole_archive_flag_spec, $1)='${wl}--whole-archive$convenience ${wl}--no-whole-archive'
	    else
	      # Exported symbols can be pulled into shared objects from archives
	      _LT_TAGVAR(whole_archive_flag_spec, $1)='$convenience'
	    fi
	    _LT_TAGVAR(archive_cmds_need_lc, $1)=yes
	    # This is similar to how AIX traditionally builds its shared
	    # libraries.
	    _LT_TAGVAR(archive_expsym_cmds, $1)="\$CC $shared_flag"' -o $output_objdir/$soname $libobjs $deplibs ${wl}-bnoentry $compiler_flags ${wl}-bE:$export_symbols${allow_undefined_flag}~$AR $AR_FLAGS $output_objdir/$libname$release.a $output_objdir/$soname'
          fi
        fi
        ;;

      beos*)
	if $LD --help 2>&1 | $GREP ': supported targets:.* elf' > /dev/null; then
	  _LT_TAGVAR(allow_undefined_flag, $1)=unsupported
	  # Joseph Beckenbach <jrb3@best.com> says some releases of gcc
	  # support --undefined.  This deserves some investigation.  FIXME
	  _LT_TAGVAR(archive_cmds, $1)='$CC -nostart $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
	else
	  _LT_TAGVAR(ld_shlibs, $1)=no
	fi
	;;

      chorus*)
        case $cc_basename in
          *)
	  # FIXME: insert proper C++ library support
	  _LT_TAGVAR(ld_shlibs, $1)=no
	  ;;
        esac
        ;;

      cygwin* | mingw* | pw32* | cegcc*)
	case $GXX,$cc_basename in
	,cl* | no,cl*)
	  # Native MSVC
	  # hardcode_libdir_flag_spec is actually meaningless, as there is
	  # no search path for DLLs.
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)=' '
	  _LT_TAGVAR(allow_undefined_flag, $1)=unsupported
	  _LT_TAGVAR(always_export_symbols, $1)=yes
	  _LT_TAGVAR(file_list_spec, $1)='@'
	  # Tell ltmain to make .lib files, not .a files.
	  libext=lib
	  # Tell ltmain to make .dll files, not .so files.
	  shrext_cmds=".dll"
	  # FIXME: Setting linknames here is a bad hack.
	  _LT_TAGVAR(archive_cmds, $1)='$CC -o $output_objdir/$soname $libobjs $compiler_flags $deplibs -Wl,-dll~linknames='
	  _LT_TAGVAR(archive_expsym_cmds, $1)='if test "x`$SED 1q $export_symbols`" = xEXPORTS; then
	      $SED -n -e 's/\\\\\\\(.*\\\\\\\)/-link\\\ -EXPORT:\\\\\\\1/' -e '1\\\!p' < $export_symbols > $output_objdir/$soname.exp;
	    else
	      $SED -e 's/\\\\\\\(.*\\\\\\\)/-link\\\ -EXPORT:\\\\\\\1/' < $export_symbols > $output_objdir/$soname.exp;
	    fi~
	    $CC -o $tool_output_objdir$soname $libobjs $compiler_flags $deplibs "@$tool_output_objdir$soname.exp" -Wl,-DLL,-IMPLIB:"$tool_output_objdir$libname.dll.lib"~
	    linknames='
	  # The linker will not automatically build a static lib if we build a DLL.
	  # _LT_TAGVAR(old_archive_from_new_cmds, $1)='true'
	  _LT_TAGVAR(enable_shared_with_static_runtimes, $1)=yes
	  # Don't use ranlib
	  _LT_TAGVAR(old_postinstall_cmds, $1)='chmod 644 $oldlib'
	  _LT_TAGVAR(postlink_cmds, $1)='lt_outputfile="@OUTPUT@"~
	    lt_tool_outputfile="@TOOL_OUTPUT@"~
	    case $lt_outputfile in
	      *.exe|*.EXE) ;;
	      *)
		lt_outputfile="$lt_outputfile.exe"
		lt_tool_outputfile="$lt_tool_outputfile.exe"
		;;
	    esac~
	    func_to_tool_file "$lt_outputfile"~
	    if test "$MANIFEST_TOOL" != ":" && test -f "$lt_outputfile.manifest"; then
	      $MANIFEST_TOOL -manifest "$lt_tool_outputfile.manifest" -outputresource:"$lt_tool_outputfile" || exit 1;
	      $RM "$lt_outputfile.manifest";
	    fi'
	  ;;
	*)
	  # g++
	  # _LT_TAGVAR(hardcode_libdir_flag_spec, $1) is actually meaningless,
	  # as there is no search path for DLLs.
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-L$libdir'
	  _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}--export-all-symbols'
	  _LT_TAGVAR(allow_undefined_flag, $1)=unsupported
	  _LT_TAGVAR(always_export_symbols, $1)=no
	  _LT_TAGVAR(enable_shared_with_static_runtimes, $1)=yes

	  if $LD --help 2>&1 | $GREP 'auto-import' > /dev/null; then
	    _LT_TAGVAR(archive_cmds, $1)='$CC -shared -nostdlib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags -o $output_objdir/$soname ${wl}--enable-auto-image-base -Xlinker --out-implib -Xlinker $lib'
	    # If the export-symbols file already is a .def file (1st line
	    # is EXPORTS), use it as is; otherwise, prepend...
	    _LT_TAGVAR(archive_expsym_cmds, $1)='if test "x`$SED 1q $export_symbols`" = xEXPORTS; then
	      cp $export_symbols $output_objdir/$soname.def;
	    else
	      echo EXPORTS > $output_objdir/$soname.def;
	      cat $export_symbols >> $output_objdir/$soname.def;
	    fi~
	    $CC -shared -nostdlib $output_objdir/$soname.def $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags -o $output_objdir/$soname ${wl}--enable-auto-image-base -Xlinker --out-implib -Xlinker $lib'
	  else
	    _LT_TAGVAR(ld_shlibs, $1)=no
	  fi
	  ;;
	esac
	;;
      darwin* | rhapsody*)
        _LT_DARWIN_LINKER_FEATURES($1)
	;;

      dgux*)
        case $cc_basename in
          ec++*)
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
          ghcx*)
	    # Green Hills C++ Compiler
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
          *)
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
        esac
        ;;

      freebsd2.*)
        # C++ shared libraries reported to be fairly broken before
	# switch to ELF
        _LT_TAGVAR(ld_shlibs, $1)=no
        ;;

      freebsd-elf*)
        _LT_TAGVAR(archive_cmds_need_lc, $1)=no
        ;;

      freebsd* | dragonfly*)
        # FreeBSD 3 and later use GNU C++ and GNU ld with standard ELF
        # conventions
        _LT_TAGVAR(ld_shlibs, $1)=yes
        ;;

      haiku*)
        _LT_TAGVAR(archive_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
        _LT_TAGVAR(link_all_deplibs, $1)=yes
        ;;

      hpux9*)
        _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}+b ${wl}$libdir'
        _LT_TAGVAR(hardcode_libdir_separator, $1)=:
        _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'
        _LT_TAGVAR(hardcode_direct, $1)=yes
        _LT_TAGVAR(hardcode_minus_L, $1)=yes # Not in the search PATH,
				             # but as the default
				             # location of the library.

        case $cc_basename in
          CC*)
            # FIXME: insert proper C++ library support
            _LT_TAGVAR(ld_shlibs, $1)=no
            ;;
          aCC*)
            _LT_TAGVAR(archive_cmds, $1)='$RM $output_objdir/$soname~$CC -b ${wl}+b ${wl}$install_libdir -o $output_objdir/$soname $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags~test $output_objdir/$soname = $lib || mv $output_objdir/$soname $lib'
            # Commands to make compiler produce verbose output that lists
            # what "hidden" libraries, object files and flags are used when
            # linking a shared library.
            #
            # There doesn't appear to be a way to prevent this compiler from
            # explicitly linking system object files so we need to strip them
            # from the output so that they don't get included in the library
            # dependencies.
            output_verbose_link_cmd='templist=`($CC -b $CFLAGS -v conftest.$objext 2>&1) | $EGREP "\-L"`; list=""; for z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; func_echo_all "$list"'
            ;;
          *)
            if test "$GXX" = yes; then
              _LT_TAGVAR(archive_cmds, $1)='$RM $output_objdir/$soname~$CC -shared -nostdlib $pic_flag ${wl}+b ${wl}$install_libdir -o $output_objdir/$soname $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags~test $output_objdir/$soname = $lib || mv $output_objdir/$soname $lib'
            else
              # FIXME: insert proper C++ library support
              _LT_TAGVAR(ld_shlibs, $1)=no
            fi
            ;;
        esac
        ;;

      hpux10*|hpux11*)
        if test $with_gnu_ld = no; then
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}+b ${wl}$libdir'
	  _LT_TAGVAR(hardcode_libdir_separator, $1)=:

          case $host_cpu in
            hppa*64*|ia64*)
              ;;
            *)
	      _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'
              ;;
          esac
        fi
        case $host_cpu in
          hppa*64*|ia64*)
            _LT_TAGVAR(hardcode_direct, $1)=no
            _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
            ;;
          *)
            _LT_TAGVAR(hardcode_direct, $1)=yes
            _LT_TAGVAR(hardcode_direct_absolute, $1)=yes
            _LT_TAGVAR(hardcode_minus_L, $1)=yes # Not in the search PATH,
					         # but as the default
					         # location of the library.
            ;;
        esac

        case $cc_basename in
          CC*)
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
          aCC*)
	    case $host_cpu in
	      hppa*64*)
	        _LT_TAGVAR(archive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	        ;;
	      ia64*)
	        _LT_TAGVAR(archive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname ${wl}+nodefaultrpath -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	        ;;
	      *)
	        _LT_TAGVAR(archive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdir -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	        ;;
	    esac
	    # Commands to make compiler produce verbose output that lists
	    # what "hidden" libraries, object files and flags are used when
	    # linking a shared library.
	    #
	    # There doesn't appear to be a way to prevent this compiler from
	    # explicitly linking system object files so we need to strip them
	    # from the output so that they don't get included in the library
	    # dependencies.
	    output_verbose_link_cmd='templist=`($CC -b $CFLAGS -v conftest.$objext 2>&1) | $GREP "\-L"`; list=""; for z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; func_echo_all "$list"'
	    ;;
          *)
	    if test "$GXX" = yes; then
	      if test $with_gnu_ld = no; then
	        case $host_cpu in
	          hppa*64*)
	            _LT_TAGVAR(archive_cmds, $1)='$CC -shared -nostdlib -fPIC ${wl}+h ${wl}$soname -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	            ;;
	          ia64*)
	            _LT_TAGVAR(archive_cmds, $1)='$CC -shared -nostdlib $pic_flag ${wl}+h ${wl}$soname ${wl}+nodefaultrpath -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	            ;;
	          *)
	            _LT_TAGVAR(archive_cmds, $1)='$CC -shared -nostdlib $pic_flag ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdir -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	            ;;
	        esac
	      fi
	    else
	      # FIXME: insert proper C++ library support
	      _LT_TAGVAR(ld_shlibs, $1)=no
	    fi
	    ;;
        esac
        ;;

      interix[[3-9]]*)
	_LT_TAGVAR(hardcode_direct, $1)=no
	_LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
	_LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'
	# Hack: On Interix 3.x, we cannot compile PIC because of a broken gcc.
	# Instead, shared libraries are loaded at an image base (0x10000000 by
	# default) and relocated if they conflict, which is a slow very memory
	# consuming and fragmenting process.  To avoid this, we pick a random,
	# 256 KiB-aligned image base between 0x50000000 and 0x6FFC0000 at link
	# time.  Moving up from 0x10000000 also allows more sbrk(2) space.
	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-h,$soname ${wl}--image-base,`expr ${RANDOM-$$} % 4096 / 2 \* 262144 + 1342177280` -o $lib'
	_LT_TAGVAR(archive_expsym_cmds, $1)='sed "s,^,_," $export_symbols >$output_objdir/$soname.expsym~$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-h,$soname ${wl}--retain-symbols-file,$output_objdir/$soname.expsym ${wl}--image-base,`expr ${RANDOM-$$} % 4096 / 2 \* 262144 + 1342177280` -o $lib'
	;;
      irix5* | irix6*)
        case $cc_basename in
          CC*)
	    # SGI C++
	    _LT_TAGVAR(archive_cmds, $1)='$CC -shared -all -multigot $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags -soname $soname `test -n "$verstring" && func_echo_all "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib'

	    # Archives containing C++ object files must be created using
	    # "CC -ar", where "CC" is the IRIX C++ compiler.  This is
	    # necessary to make sure instantiated templates are included
	    # in the archive.
	    _LT_TAGVAR(old_archive_cmds, $1)='$CC -ar -WR,-u -o $oldlib $oldobjs'
	    ;;
          *)
	    if test "$GXX" = yes; then
	      if test "$with_gnu_ld" = no; then
	        _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag -nostdlib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
	      else
	        _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag -nostdlib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` -o $lib'
	      fi
	    fi
	    _LT_TAGVAR(link_all_deplibs, $1)=yes
	    ;;
        esac
        _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
        _LT_TAGVAR(hardcode_libdir_separator, $1)=:
        _LT_TAGVAR(inherit_rpath, $1)=yes
        ;;

      linux* | k*bsd*-gnu | kopensolaris*-gnu | gnu*)
        case $cc_basename in
          KCC*)
	    # Kuck and Associates, Inc. (KAI) C++ Compiler

	    # KCC will only create a shared library if the output file
	    # ends with ".so" (or ".sl" for HP-UX), so rename the library
	    # to its proper name (with version) after linking.
	    _LT_TAGVAR(archive_cmds, $1)='tempext=`echo $shared_ext | $SED -e '\''s/\([[^()0-9A-Za-z{}]]\)/\\\\\1/g'\''`; templib=`echo $lib | $SED -e "s/\${tempext}\..*/.so/"`; $CC $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags --soname $soname -o \$templib; mv \$templib $lib'
	    _LT_TAGVAR(archive_expsym_cmds, $1)='tempext=`echo $shared_ext | $SED -e '\''s/\([[^()0-9A-Za-z{}]]\)/\\\\\1/g'\''`; templib=`echo $lib | $SED -e "s/\${tempext}\..*/.so/"`; $CC $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags --soname $soname -o \$templib ${wl}-retain-symbols-file,$export_symbols; mv \$templib $lib'
	    # Commands to make compiler produce verbose output that lists
	    # what "hidden" libraries, object files and flags are used when
	    # linking a shared library.
	    #
	    # There doesn't appear to be a way to prevent this compiler from
	    # explicitly linking system object files so we need to strip them
	    # from the output so that they don't get included in the library
	    # dependencies.
	    output_verbose_link_cmd='templist=`$CC $CFLAGS -v conftest.$objext -o libconftest$shared_ext 2>&1 | $GREP "ld"`; rm -f libconftest$shared_ext; list=""; for z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; func_echo_all "$list"'

	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
	    _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}--export-dynamic'

	    # Archives containing C++ object files must be created using
	    # "CC -Bstatic", where "CC" is the KAI C++ compiler.
	    _LT_TAGVAR(old_archive_cmds, $1)='$CC -Bstatic -o $oldlib $oldobjs'
	    ;;
	  icpc* | ecpc* )
	    # Intel C++
	    with_gnu_ld=yes
	    # version 8.0 and above of icpc choke on multiply defined symbols
	    # if we add $predep_objects and $postdep_objects, however 7.1 and
	    # earlier do not add the objects themselves.
	    case `$CC -V 2>&1` in
	      *"Version 7."*)
	        _LT_TAGVAR(archive_cmds, $1)='$CC -shared $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname $wl$soname -o $lib'
		_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
		;;
	      *)  # Version 8.0 or newer
	        tmp_idyn=
	        case $host_cpu in
		  ia64*) tmp_idyn=' -i_dynamic';;
		esac
	        _LT_TAGVAR(archive_cmds, $1)='$CC -shared'"$tmp_idyn"' $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
		_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared'"$tmp_idyn"' $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
		;;
	    esac
	    _LT_TAGVAR(archive_cmds_need_lc, $1)=no
	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
	    _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}--export-dynamic'
	    _LT_TAGVAR(whole_archive_flag_spec, $1)='${wl}--whole-archive$convenience ${wl}--no-whole-archive'
	    ;;
          pgCC* | pgcpp*)
            # Portland Group C++ compiler
	    case `$CC -V` in
	    *pgCC\ [[1-5]].* | *pgcpp\ [[1-5]].*)
	      _LT_TAGVAR(prelink_cmds, $1)='tpldir=Template.dir~
		rm -rf $tpldir~
		$CC --prelink_objects --instantiation_dir $tpldir $objs $libobjs $compile_deplibs~
		compile_command="$compile_command `find $tpldir -name \*.o | sort | $NL2SP`"'
	      _LT_TAGVAR(old_archive_cmds, $1)='tpldir=Template.dir~
		rm -rf $tpldir~
		$CC --prelink_objects --instantiation_dir $tpldir $oldobjs$old_deplibs~
		$AR $AR_FLAGS $oldlib$oldobjs$old_deplibs `find $tpldir -name \*.o | sort | $NL2SP`~
		$RANLIB $oldlib'
	      _LT_TAGVAR(archive_cmds, $1)='tpldir=Template.dir~
		rm -rf $tpldir~
		$CC --prelink_objects --instantiation_dir $tpldir $predep_objects $libobjs $deplibs $convenience $postdep_objects~
		$CC -shared $pic_flag $predep_objects $libobjs $deplibs `find $tpldir -name \*.o | sort | $NL2SP` $postdep_objects $compiler_flags ${wl}-soname ${wl}$soname -o $lib'
	      _LT_TAGVAR(archive_expsym_cmds, $1)='tpldir=Template.dir~
		rm -rf $tpldir~
		$CC --prelink_objects --instantiation_dir $tpldir $predep_objects $libobjs $deplibs $convenience $postdep_objects~
		$CC -shared $pic_flag $predep_objects $libobjs $deplibs `find $tpldir -name \*.o | sort | $NL2SP` $postdep_objects $compiler_flags ${wl}-soname ${wl}$soname ${wl}-retain-symbols-file ${wl}$export_symbols -o $lib'
	      ;;
	    *) # Version 6 and above use weak symbols
	      _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname ${wl}$soname -o $lib'
	      _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname ${wl}$soname ${wl}-retain-symbols-file ${wl}$export_symbols -o $lib'
	      ;;
	    esac

	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}--rpath ${wl}$libdir'
	    _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}--export-dynamic'
	    _LT_TAGVAR(whole_archive_flag_spec, $1)='${wl}--whole-archive`for conv in $convenience\"\"; do test  -n \"$conv\" && new_convenience=\"$new_convenience,$conv\"; done; func_echo_all \"$new_convenience\"` ${wl}--no-whole-archive'
            ;;
	  cxx*)
	    # Compaq C++
	    _LT_TAGVAR(archive_cmds, $1)='$CC -shared $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname $wl$soname -o $lib'
	    _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname $wl$soname  -o $lib ${wl}-retain-symbols-file $wl$export_symbols'

	    runpath_var=LD_RUN_PATH
	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-rpath $libdir'
	    _LT_TAGVAR(hardcode_libdir_separator, $1)=:

	    # Commands to make compiler produce verbose output that lists
	    # what "hidden" libraries, object files and flags are used when
	    # linking a shared library.
	    #
	    # There doesn't appear to be a way to prevent this compiler from
	    # explicitly linking system object files so we need to strip them
	    # from the output so that they don't get included in the library
	    # dependencies.
	    output_verbose_link_cmd='templist=`$CC -shared $CFLAGS -v conftest.$objext 2>&1 | $GREP "ld"`; templist=`func_echo_all "$templist" | $SED "s/\(^.*ld.*\)\( .*ld .*$\)/\1/"`; list=""; for z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; func_echo_all "X$list" | $Xsed'
	    ;;
	  xl* | mpixl* | bgxl*)
	    # IBM XL 8.0 on PPC, with GNU ld
	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
	    _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}--export-dynamic'
	    _LT_TAGVAR(archive_cmds, $1)='$CC -qmkshrobj $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
	    if test "x$supports_anon_versioning" = xyes; then
	      _LT_TAGVAR(archive_expsym_cmds, $1)='echo "{ global:" > $output_objdir/$libname.ver~
		cat $export_symbols | sed -e "s/\(.*\)/\1;/" >> $output_objdir/$libname.ver~
		echo "local: *; };" >> $output_objdir/$libname.ver~
		$CC -qmkshrobj $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-version-script ${wl}$output_objdir/$libname.ver -o $lib'
	    fi
	    ;;
	  *)
	    case `$CC -V 2>&1 | sed 5q` in
	    *Sun\ C*)
	      # Sun C++ 5.9
	      _LT_TAGVAR(no_undefined_flag, $1)=' -zdefs'
	      _LT_TAGVAR(archive_cmds, $1)='$CC -G${allow_undefined_flag} -h$soname -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	      _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -G${allow_undefined_flag} -h$soname -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-retain-symbols-file ${wl}$export_symbols'
	      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
	      _LT_TAGVAR(whole_archive_flag_spec, $1)='${wl}--whole-archive`new_convenience=; for conv in $convenience\"\"; do test -z \"$conv\" || new_convenience=\"$new_convenience,$conv\"; done; func_echo_all \"$new_convenience\"` ${wl}--no-whole-archive'
	      _LT_TAGVAR(compiler_needs_object, $1)=yes

	      # Not sure whether something based on
	      # $CC $CFLAGS -v conftest.$objext -o libconftest$shared_ext 2>&1
	      # would be better.
	      output_verbose_link_cmd='func_echo_all'

	      # Archives containing C++ object files must be created using
	      # "CC -xar", where "CC" is the Sun C++ compiler.  This is
	      # necessary to make sure instantiated templates are included
	      # in the archive.
	      _LT_TAGVAR(old_archive_cmds, $1)='$CC -xar -o $oldlib $oldobjs'
	      ;;
	    esac
	    ;;
	esac
	;;

      lynxos*)
        # FIXME: insert proper C++ library support
	_LT_TAGVAR(ld_shlibs, $1)=no
	;;

      m88k*)
        # FIXME: insert proper C++ library support
        _LT_TAGVAR(ld_shlibs, $1)=no
	;;

      mvs*)
        case $cc_basename in
          cxx*)
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
	  *)
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
	esac
	;;

      netbsd*)
        if echo __ELF__ | $CC -E - | $GREP __ELF__ >/dev/null; then
	  _LT_TAGVAR(archive_cmds, $1)='$LD -Bshareable  -o $lib $predep_objects $libobjs $deplibs $postdep_objects $linker_flags'
	  wlarc=
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
	  _LT_TAGVAR(hardcode_direct, $1)=yes
	  _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	fi
	# Workaround some broken pre-1.5 toolchains
	output_verbose_link_cmd='$CC -shared $CFLAGS -v conftest.$objext 2>&1 | $GREP conftest.$objext | $SED -e "s:-lgcc -lc -lgcc::"'
	;;

      *nto* | *qnx*)
        _LT_TAGVAR(ld_shlibs, $1)=yes
	;;

      openbsd2*)
        # C++ shared libraries are fairly broken
	_LT_TAGVAR(ld_shlibs, $1)=no
	;;

      openbsd*)
	if test -f /usr/libexec/ld.so; then
	  _LT_TAGVAR(hardcode_direct, $1)=yes
	  _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	  _LT_TAGVAR(hardcode_direct_absolute, $1)=yes
	  _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags -o $lib'
	  _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
	  if test -z "`echo __ELF__ | $CC -E - | grep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powerpc"; then
	    _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-retain-symbols-file,$export_symbols -o $lib'
	    _LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-E'
	    _LT_TAGVAR(whole_archive_flag_spec, $1)="$wlarc"'--whole-archive$convenience '"$wlarc"'--no-whole-archive'
	  fi
	  output_verbose_link_cmd=func_echo_all
	else
	  _LT_TAGVAR(ld_shlibs, $1)=no
	fi
	;;

      osf3* | osf4* | osf5*)
        case $cc_basename in
          KCC*)
	    # Kuck and Associates, Inc. (KAI) C++ Compiler

	    # KCC will only create a shared library if the output file
	    # ends with ".so" (or ".sl" for HP-UX), so rename the library
	    # to its proper name (with version) after linking.
	    _LT_TAGVAR(archive_cmds, $1)='tempext=`echo $shared_ext | $SED -e '\''s/\([[^()0-9A-Za-z{}]]\)/\\\\\1/g'\''`; templib=`echo "$lib" | $SED -e "s/\${tempext}\..*/.so/"`; $CC $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags --soname $soname -o \$templib; mv \$templib $lib'

	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
	    _LT_TAGVAR(hardcode_libdir_separator, $1)=:

	    # Archives containing C++ object files must be created using
	    # the KAI C++ compiler.
	    case $host in
	      osf3*) _LT_TAGVAR(old_archive_cmds, $1)='$CC -Bstatic -o $oldlib $oldobjs' ;;
	      *) _LT_TAGVAR(old_archive_cmds, $1)='$CC -o $oldlib $oldobjs' ;;
	    esac
	    ;;
          RCC*)
	    # Rational C++ 2.4.1
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
          cxx*)
	    case $host in
	      osf3*)
	        _LT_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unresolved ${wl}\*'
	        _LT_TAGVAR(archive_cmds, $1)='$CC -shared${allow_undefined_flag} $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname $soname `test -n "$verstring" && func_echo_all "${wl}-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib'
	        _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
		;;
	      *)
	        _LT_TAGVAR(allow_undefined_flag, $1)=' -expect_unresolved \*'
	        _LT_TAGVAR(archive_cmds, $1)='$CC -shared${allow_undefined_flag} $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags -msym -soname $soname `test -n "$verstring" && func_echo_all "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib'
	        _LT_TAGVAR(archive_expsym_cmds, $1)='for i in `cat $export_symbols`; do printf "%s %s\\n" -exported_symbol "\$i" >> $lib.exp; done~
	          echo "-hidden">> $lib.exp~
	          $CC -shared$allow_undefined_flag $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags -msym -soname $soname ${wl}-input ${wl}$lib.exp  `test -n "$verstring" && $ECHO "-set_version $verstring"` -update_registry ${output_objdir}/so_locations -o $lib~
	          $RM $lib.exp'
	        _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-rpath $libdir'
		;;
	    esac

	    _LT_TAGVAR(hardcode_libdir_separator, $1)=:

	    # Commands to make compiler produce verbose output that lists
	    # what "hidden" libraries, object files and flags are used when
	    # linking a shared library.
	    #
	    # There doesn't appear to be a way to prevent this compiler from
	    # explicitly linking system object files so we need to strip them
	    # from the output so that they don't get included in the library
	    # dependencies.
	    output_verbose_link_cmd='templist=`$CC -shared $CFLAGS -v conftest.$objext 2>&1 | $GREP "ld" | $GREP -v "ld:"`; templist=`func_echo_all "$templist" | $SED "s/\(^.*ld.*\)\( .*ld.*$\)/\1/"`; list=""; for z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; func_echo_all "$list"'
	    ;;
	  *)
	    if test "$GXX" = yes && test "$with_gnu_ld" = no; then
	      _LT_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unresolved ${wl}\*'
	      case $host in
	        osf3*)
	          _LT_TAGVAR(archive_cmds, $1)='$CC -shared -nostdlib ${allow_undefined_flag} $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
		  ;;
	        *)
	          _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag -nostdlib ${allow_undefined_flag} $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-msym ${wl}-soname ${wl}$soname `test -n "$verstring" && func_echo_all "${wl}-set_version ${wl}$verstring"` ${wl}-update_registry ${wl}${output_objdir}/so_locations -o $lib'
		  ;;
	      esac

	      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath ${wl}$libdir'
	      _LT_TAGVAR(hardcode_libdir_separator, $1)=:

	      # Commands to make compiler produce verbose output that lists
	      # what "hidden" libraries, object files and flags are used when
	      # linking a shared library.
	      output_verbose_link_cmd='$CC -shared $CFLAGS -v conftest.$objext 2>&1 | $GREP -v "^Configured with:" | $GREP "\-L"'

	    else
	      # FIXME: insert proper C++ library support
	      _LT_TAGVAR(ld_shlibs, $1)=no
	    fi
	    ;;
        esac
        ;;

      psos*)
        # FIXME: insert proper C++ library support
        _LT_TAGVAR(ld_shlibs, $1)=no
        ;;

      sunos4*)
        case $cc_basename in
          CC*)
	    # Sun C++ 4.x
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
          lcc*)
	    # Lucid
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
          *)
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
        esac
        ;;

      solaris*)
        case $cc_basename in
          CC* | sunCC*)
	    # Sun C++ 4.2, 5.x and Centerline C++
            _LT_TAGVAR(archive_cmds_need_lc,$1)=yes
	    _LT_TAGVAR(no_undefined_flag, $1)=' -zdefs'
	    _LT_TAGVAR(archive_cmds, $1)='$CC -G${allow_undefined_flag}  -h$soname -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags'
	    _LT_TAGVAR(archive_expsym_cmds, $1)='echo "{ global:" > $lib.exp~cat $export_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~echo "local: *; };" >> $lib.exp~
	      $CC -G${allow_undefined_flag} ${wl}-M ${wl}$lib.exp -h$soname -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags~$RM $lib.exp'

	    _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='-R$libdir'
	    _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	    case $host_os in
	      solaris2.[[0-5]] | solaris2.[[0-5]].*) ;;
	      *)
		# The compiler driver will combine and reorder linker options,
		# but understands `-z linker_flag'.
	        # Supported since Solaris 2.6 (maybe 2.5.1?)
		_LT_TAGVAR(whole_archive_flag_spec, $1)='-z allextract$convenience -z defaultextract'
	        ;;
	    esac
	    _LT_TAGVAR(link_all_deplibs, $1)=yes

	    output_verbose_link_cmd='func_echo_all'

	    # Archives containing C++ object files must be created using
	    # "CC -xar", where "CC" is the Sun C++ compiler.  This is
	    # necessary to make sure instantiated templates are included
	    # in the archive.
	    _LT_TAGVAR(old_archive_cmds, $1)='$CC -xar -o $oldlib $oldobjs'
	    ;;
          gcx*)
	    # Green Hills C++ Compiler
	    _LT_TAGVAR(archive_cmds, $1)='$CC -shared $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-h $wl$soname -o $lib'

	    # The C++ compiler must be used to create the archive.
	    _LT_TAGVAR(old_archive_cmds, $1)='$CC $LDFLAGS -archive -o $oldlib $oldobjs'
	    ;;
          *)
	    # GNU C++ compiler with Solaris linker
	    if test "$GXX" = yes && test "$with_gnu_ld" = no; then
	      _LT_TAGVAR(no_undefined_flag, $1)=' ${wl}-z ${wl}defs'
	      if $CC --version | $GREP -v '^2\.7' > /dev/null; then
	        _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag -nostdlib $LDFLAGS $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-h $wl$soname -o $lib'
	        _LT_TAGVAR(archive_expsym_cmds, $1)='echo "{ global:" > $lib.exp~cat $export_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~echo "local: *; };" >> $lib.exp~
		  $CC -shared $pic_flag -nostdlib ${wl}-M $wl$lib.exp -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags~$RM $lib.exp'

	        # Commands to make compiler produce verbose output that lists
	        # what "hidden" libraries, object files and flags are used when
	        # linking a shared library.
	        output_verbose_link_cmd='$CC -shared $CFLAGS -v conftest.$objext 2>&1 | $GREP -v "^Configured with:" | $GREP "\-L"'
	      else
	        # g++ 2.7 appears to require `-G' NOT `-shared' on this
	        # platform.
	        _LT_TAGVAR(archive_cmds, $1)='$CC -G -nostdlib $LDFLAGS $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags ${wl}-h $wl$soname -o $lib'
	        _LT_TAGVAR(archive_expsym_cmds, $1)='echo "{ global:" > $lib.exp~cat $export_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~echo "local: *; };" >> $lib.exp~
		  $CC -G -nostdlib ${wl}-M $wl$lib.exp -o $lib $predep_objects $libobjs $deplibs $postdep_objects $compiler_flags~$RM $lib.exp'

	        # Commands to make compiler produce verbose output that lists
	        # what "hidden" libraries, object files and flags are used when
	        # linking a shared library.
	        output_verbose_link_cmd='$CC -G $CFLAGS -v conftest.$objext 2>&1 | $GREP -v "^Configured with:" | $GREP "\-L"'
	      fi

	      _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-R $wl$libdir'
	      case $host_os in
		solaris2.[[0-5]] | solaris2.[[0-5]].*) ;;
		*)
		  _LT_TAGVAR(whole_archive_flag_spec, $1)='${wl}-z ${wl}allextract$convenience ${wl}-z ${wl}defaultextract'
		  ;;
	      esac
	    fi
	    ;;
        esac
        ;;

    sysv4*uw2* | sysv5OpenUNIX* | sysv5UnixWare7.[[01]].[[10]]* | unixware7* | sco3.2v5.0.[[024]]*)
      _LT_TAGVAR(no_undefined_flag, $1)='${wl}-z,text'
      _LT_TAGVAR(archive_cmds_need_lc, $1)=no
      _LT_TAGVAR(hardcode_shlibpath_var, $1)=no
      runpath_var='LD_RUN_PATH'

      case $cc_basename in
        CC*)
	  _LT_TAGVAR(archive_cmds, $1)='$CC -G ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	  _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -G ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	  ;;
	*)
	  _LT_TAGVAR(archive_cmds, $1)='$CC -shared ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	  _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	  ;;
      esac
      ;;

      sysv5* | sco3.2v5* | sco5v6*)
	# Note: We can NOT use -z defs as we might desire, because we do not
	# link with -lc, and that would cause any symbols used from libc to
	# always be unresolved, which means just about no library would
	# ever link correctly.  If we're not using GNU ld we use -z text
	# though, which does catch some bad symbols but isn't as heavy-handed
	# as -z defs.
	_LT_TAGVAR(no_undefined_flag, $1)='${wl}-z,text'
	_LT_TAGVAR(allow_undefined_flag, $1)='${wl}-z,nodefs'
	_LT_TAGVAR(archive_cmds_need_lc, $1)=no
	_LT_TAGVAR(hardcode_shlibpath_var, $1)=no
	_LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-R,$libdir'
	_LT_TAGVAR(hardcode_libdir_separator, $1)=':'
	_LT_TAGVAR(link_all_deplibs, $1)=yes
	_LT_TAGVAR(export_dynamic_flag_spec, $1)='${wl}-Bexport'
	runpath_var='LD_RUN_PATH'

	case $cc_basename in
          CC*)
	    _LT_TAGVAR(archive_cmds, $1)='$CC -G ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	    _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -G ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	    _LT_TAGVAR(old_archive_cmds, $1)='$CC -Tprelink_objects $oldobjs~
	      '"$_LT_TAGVAR(old_archive_cmds, $1)"
	    _LT_TAGVAR(reload_cmds, $1)='$CC -Tprelink_objects $reload_objs~
	      '"$_LT_TAGVAR(reload_cmds, $1)"
	    ;;
	  *)
	    _LT_TAGVAR(archive_cmds, $1)='$CC -shared ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	    _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared ${wl}-Bexport:$export_symbols ${wl}-h,$soname -o $lib $libobjs $deplibs $compiler_flags'
	    ;;
	esac
      ;;

      tandem*)
        case $cc_basename in
          NCC*)
	    # NonStop-UX NCC 3.20
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
          *)
	    # FIXME: insert proper C++ library support
	    _LT_TAGVAR(ld_shlibs, $1)=no
	    ;;
        esac
        ;;

      vxworks*)
        # FIXME: insert proper C++ library support
        _LT_TAGVAR(ld_shlibs, $1)=no
        ;;

      *)
        # FIXME: insert proper C++ library support
        _LT_TAGVAR(ld_shlibs, $1)=no
        ;;
    esac

    AC_MSG_RESULT([$_LT_TAGVAR(ld_shlibs, $1)])
    test "$_LT_TAGVAR(ld_shlibs, $1)" = no && can_build_shared=no

    _LT_TAGVAR(GCC, $1)="$GXX"
    _LT_TAGVAR(LD, $1)="$LD"

    ## CAVEAT EMPTOR:
    ## There is no encapsulation within the following macros, do not change
    ## the running order or otherwise move them around unless you know exactly
    ## what you are doing...
    _LT_SYS_HIDDEN_LIBDEPS($1)
    _LT_COMPILER_PIC($1)
    _LT_COMPILER_C_O($1)
    _LT_COMPILER_FILE_LOCKS($1)
    _LT_LINKER_SHLIBS($1)
    _LT_SYS_DYNAMIC_LINKER($1)
    _LT_LINKER_HARDCODE_LIBPATH($1)

    _LT_CONFIG($1)
  fi # test -n "$compiler"

  CC=$lt_save_CC
  CFLAGS=$lt_save_CFLAGS
  LDCXX=$LD
  LD=$lt_save_LD
  GCC=$lt_save_GCC
  with_gnu_ld=$lt_save_with_gnu_ld
  lt_cv_path_LDCXX=$lt_cv_path_LD
  lt_cv_path_LD=$lt_save_path_LD
  lt_cv_prog_gnu_ldcxx=$lt_cv_prog_gnu_ld
  lt_cv_prog_gnu_ld=$lt_save_with_gnu_ld
fi # test "$_lt_caught_CXX_error" != yes

AC_LANG_POP
])# _LT_LANG_CXX_CONFIG


# _LT_FUNC_STRIPNAME_CNF
# ----------------------
# func_stripname_cnf prefix suffix name
# strip PREFIX and SUFFIX off of NAME.
# PREFIX and SUFFIX must not contain globbing or regex special
# characters, hashes, percent signs, but SUFFIX may contain a leading
# dot (in which case that matches only a dot).
#
# This function is identical to the (non-XSI) version of func_stripname,
# except this one can be used by m4 code that may be executed by configure,
# rather than the libtool script.
m4_defun([_LT_FUNC_STRIPNAME_CNF],[dnl
AC_REQUIRE([_LT_DECL_SED])
AC_REQUIRE([_LT_PROG_ECHO_BACKSLASH])
func_stripname_cnf ()
{
  case ${2} in
  .*) func_stripname_result=`$ECHO "${3}" | $SED "s%^${1}%%; s%\\\\${2}\$%%"`;;
  *)  func_stripname_result=`$ECHO "${3}" | $SED "s%^${1}%%; s%${2}\$%%"`;;
  esac
} # func_stripname_cnf
])# _LT_FUNC_STRIPNAME_CNF

# _LT_SYS_HIDDEN_LIBDEPS([TAGNAME])
# ---------------------------------
# Figure out "hidden" library dependencies from verbose
# compiler output when linking a shared library.
# Parse the compiler output and extract the necessary
# objects, libraries and library flags.
m4_defun([_LT_SYS_HIDDEN_LIBDEPS],
[m4_require([_LT_FILEUTILS_DEFAULTS])dnl
AC_REQUIRE([_LT_FUNC_STRIPNAME_CNF])dnl
# Dependencies to place before and after the object being linked:
_LT_TAGVAR(predep_objects, $1)=
_LT_TAGVAR(postdep_objects, $1)=
_LT_TAGVAR(predeps, $1)=
_LT_TAGVAR(postdeps, $1)=
_LT_TAGVAR(compiler_lib_search_path, $1)=

dnl we can't use the lt_simple_compile_test_code here,
dnl because it contains code intended for an executable,
dnl not a library.  It's possible we should let each
dnl tag define a new lt_????_link_test_code variable,
dnl but it's only used here...
m4_if([$1], [], [cat > conftest.$ac_ext <<_LT_EOF
int a;
void foo (void) { a = 0; }
_LT_EOF
], [$1], [CXX], [cat > conftest.$ac_ext <<_LT_EOF
class Foo
{
public:
  Foo (void) { a = 0; }
private:
  int a;
};
_LT_EOF
], [$1], [F77], [cat > conftest.$ac_ext <<_LT_EOF
      subroutine foo
      implicit none
      integer*4 a
      a=0
      return
      end
_LT_EOF
], [$1], [FC], [cat > conftest.$ac_ext <<_LT_EOF
      subroutine foo
      implicit none
      integer a
      a=0
      return
      end
_LT_EOF
], [$1], [GCJ], [cat > conftest.$ac_ext <<_LT_EOF
public class foo {
  private int a;
  public void bar (void) {
    a = 0;
  }
};
_LT_EOF
], [$1], [GO], [cat > conftest.$ac_ext <<_LT_EOF
package foo
func foo() {
}
_LT_EOF
])

_lt_libdeps_save_CFLAGS=$CFLAGS
case "$CC $CFLAGS " in #(
*\ -flto*\ *) CFLAGS="$CFLAGS -fno-lto" ;;
*\ -fwhopr*\ *) CFLAGS="$CFLAGS -fno-whopr" ;;
*\ -fuse-linker-plugin*\ *) CFLAGS="$CFLAGS -fno-use-linker-plugin" ;;
esac

dnl Parse the compiler output and extract the necessary
dnl objects, libraries and library flags.
if AC_TRY_EVAL(ac_compile); then
  # Parse the compiler output and extract the necessary
  # objects, libraries and library flags.

  # Sentinel used to keep track of whether or not we are before
  # the conftest object file.
  pre_test_object_deps_done=no

  for p in `eval "$output_verbose_link_cmd"`; do
    case ${prev}${p} in

    -L* | -R* | -l*)
       # Some compilers place space between "-{L,R}" and the path.
       # Remove the space.
       if test $p = "-L" ||
          test $p = "-R"; then
	 prev=$p
	 continue
       fi

       # Expand the sysroot to ease extracting the directories later.
       if test -z "$prev"; then
         case $p in
         -L*) func_stripname_cnf '-L' '' "$p"; prev=-L; p=$func_stripname_result ;;
         -R*) func_stripname_cnf '-R' '' "$p"; prev=-R; p=$func_stripname_result ;;
         -l*) func_stripname_cnf '-l' '' "$p"; prev=-l; p=$func_stripname_result ;;
         esac
       fi
       case $p in
       =*) func_stripname_cnf '=' '' "$p"; p=$lt_sysroot$func_stripname_result ;;
       esac
       if test "$pre_test_object_deps_done" = no; then
	 case ${prev} in
	 -L | -R)
	   # Internal compiler library paths should come after those
	   # provided the user.  The postdeps already come after the
	   # user supplied libs so there is no need to process them.
	   if test -z "$_LT_TAGVAR(compiler_lib_search_path, $1)"; then
	     _LT_TAGVAR(compiler_lib_search_path, $1)="${prev}${p}"
	   else
	     _LT_TAGVAR(compiler_lib_search_path, $1)="${_LT_TAGVAR(compiler_lib_search_path, $1)} ${prev}${p}"
	   fi
	   ;;
	 # The "-l" case would never come before the object being
	 # linked, so don't bother handling this case.
	 esac
       else
	 if test -z "$_LT_TAGVAR(postdeps, $1)"; then
	   _LT_TAGVAR(postdeps, $1)="${prev}${p}"
	 else
	   _LT_TAGVAR(postdeps, $1)="${_LT_TAGVAR(postdeps, $1)} ${prev}${p}"
	 fi
       fi
       prev=
       ;;

    *.lto.$objext) ;; # Ignore GCC LTO objects
    *.$objext)
       # This assumes that the test object file only shows up
       # once in the compiler output.
       if test "$p" = "conftest.$objext"; then
	 pre_test_object_deps_done=yes
	 continue
       fi

       if test "$pre_test_object_deps_done" = no; then
	 if test -z "$_LT_TAGVAR(predep_objects, $1)"; then
	   _LT_TAGVAR(predep_objects, $1)="$p"
	 else
	   _LT_TAGVAR(predep_objects, $1)="$_LT_TAGVAR(predep_objects, $1) $p"
	 fi
       else
	 if test -z "$_LT_TAGVAR(postdep_objects, $1)"; then
	   _LT_TAGVAR(postdep_objects, $1)="$p"
	 else
	   _LT_TAGVAR(postdep_objects, $1)="$_LT_TAGVAR(postdep_objects, $1) $p"
	 fi
       fi
       ;;

    *) ;; # Ignore the rest.

    esac
  done

  # Clean up.
  rm -f a.out a.exe
else
  echo "libtool.m4: error: problem compiling $1 test program"
fi

$RM -f confest.$objext
CFLAGS=$_lt_libdeps_save_CFLAGS

# PORTME: override above test on systems where it is broken
m4_if([$1], [CXX],
[case $host_os in
interix[[3-9]]*)
  # Interix 3.5 installs completely hosed .la files for C++, so rather than
  # hack all around it, let's just trust "g++" to DTRT.
  _LT_TAGVAR(predep_objects,$1)=
  _LT_TAGVAR(postdep_objects,$1)=
  _LT_TAGVAR(postdeps,$1)=
  ;;

linux*)
  case `$CC -V 2>&1 | sed 5q` in
  *Sun\ C*)
    # Sun C++ 5.9

    # The more standards-conforming stlport4 library is
    # incompatible with the Cstd library. Avoid specifying
    # it if it's in CXXFLAGS. Ignore libCrun as
    # -library=stlport4 depends on it.
    case " $CXX $CXXFLAGS " in
    *" -library=stlport4 "*)
      solaris_use_stlport4=yes
      ;;
    esac

    if test "$solaris_use_stlport4" != yes; then
      _LT_TAGVAR(postdeps,$1)='-library=Cstd -library=Crun'
    fi
    ;;
  esac
  ;;

solaris*)
  case $cc_basename in
  CC* | sunCC*)
    # The more standards-conforming stlport4 library is
    # incompatible with the Cstd library. Avoid specifying
    # it if it's in CXXFLAGS. Ignore libCrun as
    # -library=stlport4 depends on it.
    case " $CXX $CXXFLAGS " in
    *" -library=stlport4 "*)
      solaris_use_stlport4=yes
      ;;
    esac

    # Adding this requires a known-good setup of shared libraries for
    # Sun compiler versions before 5.6, else PIC objects from an old
    # archive will be linked into the output, leading to subtle bugs.
    if test "$solaris_use_stlport4" != yes; then
      _LT_TAGVAR(postdeps,$1)='-library=Cstd -library=Crun'
    fi
    ;;
  esac
  ;;
esac
])

case " $_LT_TAGVAR(postdeps, $1) " in
*" -lc "*) _LT_TAGVAR(archive_cmds_need_lc, $1)=no ;;
esac
 _LT_TAGVAR(compiler_lib_search_dirs, $1)=
if test -n "${_LT_TAGVAR(compiler_lib_search_path, $1)}"; then
 _LT_TAGVAR(compiler_lib_search_dirs, $1)=`echo " ${_LT_TAGVAR(compiler_lib_search_path, $1)}" | ${SED} -e 's! -L! !g' -e 's!^ !!'`
fi
_LT_TAGDECL([], [compiler_lib_search_dirs], [1],
    [The directories searched by this compiler when creating a shared library])
_LT_TAGDECL([], [predep_objects], [1],
    [Dependencies to place before and after the objects being linked to
    create a shared library])
_LT_TAGDECL([], [postdep_objects], [1])
_LT_TAGDECL([], [predeps], [1])
_LT_TAGDECL([], [postdeps], [1])
_LT_TAGDECL([], [compiler_lib_search_path], [1],
    [The library search path used internally by the compiler when linking
    a shared library])
])# _LT_SYS_HIDDEN_LIBDEPS


# _LT_LANG_F77_CONFIG([TAG])
# --------------------------
# Ensure that the configuration variables for a Fortran 77 compiler are
# suitably defined.  These variables are subsequently used by _LT_CONFIG
# to write the compiler configuration to `libtool'.
m4_defun([_LT_LANG_F77_CONFIG],
[AC_LANG_PUSH(Fortran 77)
if test -z "$F77" || test "X$F77" = "Xno"; then
  _lt_disable_F77=yes
fi

_LT_TAGVAR(archive_cmds_need_lc, $1)=no
_LT_TAGVAR(allow_undefined_flag, $1)=
_LT_TAGVAR(always_export_symbols, $1)=no
_LT_TAGVAR(archive_expsym_cmds, $1)=
_LT_TAGVAR(export_dynamic_flag_spec, $1)=
_LT_TAGVAR(hardcode_direct, $1)=no
_LT_TAGVAR(hardcode_direct_absolute, $1)=no
_LT_TAGVAR(hardcode_libdir_flag_spec, $1)=
_LT_TAGVAR(hardcode_libdir_separator, $1)=
_LT_TAGVAR(hardcode_minus_L, $1)=no
_LT_TAGVAR(hardcode_automatic, $1)=no
_LT_TAGVAR(inherit_rpath, $1)=no
_LT_TAGVAR(module_cmds, $1)=
_LT_TAGVAR(module_expsym_cmds, $1)=
_LT_TAGVAR(link_all_deplibs, $1)=unknown
_LT_TAGVAR(old_archive_cmds, $1)=$old_archive_cmds
_LT_TAGVAR(reload_flag, $1)=$reload_flag
_LT_TAGVAR(reload_cmds, $1)=$reload_cmds
_LT_TAGVAR(no_undefined_flag, $1)=
_LT_TAGVAR(whole_archive_flag_spec, $1)=
_LT_TAGVAR(enable_shared_with_static_runtimes, $1)=no

# Source file extension for f77 test sources.
ac_ext=f

# Object file extension for compiled f77 test sources.
objext=o
_LT_TAGVAR(objext, $1)=$objext

# No sense in running all these tests if we already determined that
# the F77 compiler isn't working.  Some variables (like enable_shared)
# are currently assumed to apply to all compilers on this platform,
# and will be corrupted by setting them based on a non-working compiler.
if test "$_lt_disable_F77" != yes; then
  # Code to be used in simple compile tests
  lt_simple_compile_test_code="\
      subroutine t
      return
      end
"

  # Code to be used in simple link tests
  lt_simple_link_test_code="\
      program t
      end
"

  # ltmain only uses $CC for tagged configurations so make sure $CC is set.
  _LT_TAG_COMPILER

  # save warnings/boilerplate of simple test code
  _LT_COMPILER_BOILERPLATE
  _LT_LINKER_BOILERPLATE

  # Allow CC to be a program name with arguments.
  lt_save_CC="$CC"
  lt_save_GCC=$GCC
  lt_save_CFLAGS=$CFLAGS
  CC=${F77-"f77"}
  CFLAGS=$FFLAGS
  compiler=$CC
  _LT_TAGVAR(compiler, $1)=$CC
  _LT_CC_BASENAME([$compiler])
  GCC=$G77
  if test -n "$compiler"; then
    AC_MSG_CHECKING([if libtool supports shared libraries])
    AC_MSG_RESULT([$can_build_shared])

    AC_MSG_CHECKING([whether to build shared libraries])
    test "$can_build_shared" = "no" && enable_shared=no

    # On AIX, shared libraries and static libraries use the same namespace, and
    # are all built from PIC.
    case $host_os in
      aix3*)
        test "$enable_shared" = yes && enable_static=no
        if test -n "$RANLIB"; then
          archive_cmds="$archive_cmds~\$RANLIB \$lib"
          postinstall_cmds='$RANLIB $lib'
        fi
        ;;
      aix[[4-9]]*)
	if test "$host_cpu" != ia64 && test "$aix_use_runtimelinking" = no ; then
	  test "$enable_shared" = yes && enable_static=no
	fi
        ;;
    esac
    AC_MSG_RESULT([$enable_shared])

    AC_MSG_CHECKING([whether to build static libraries])
    # Make sure either enable_shared or enable_static is yes.
    test "$enable_shared" = yes || enable_static=yes
    AC_MSG_RESULT([$enable_static])

    _LT_TAGVAR(GCC, $1)="$G77"
    _LT_TAGVAR(LD, $1)="$LD"

    ## CAVEAT EMPTOR:
    ## There is no encapsulation within the following macros, do not change
    ## the running order or otherwise move them around unless you know exactly
    ## what you are doing...
    _LT_COMPILER_PIC($1)
    _LT_COMPILER_C_O($1)
    _LT_COMPILER_FILE_LOCKS($1)
    _LT_LINKER_SHLIBS($1)
    _LT_SYS_DYNAMIC_LINKER($1)
    _LT_LINKER_HARDCODE_LIBPATH($1)

    _LT_CONFIG($1)
  fi # test -n "$compiler"

  GCC=$lt_save_GCC
  CC="$lt_save_CC"
  CFLAGS="$lt_save_CFLAGS"
fi # test "$_lt_disable_F77" != yes

AC_LANG_POP
])# _LT_LANG_F77_CONFIG


# _LT_LANG_FC_CONFIG([TAG])
# -------------------------
# Ensure that the configuration variables for a Fortran compiler are
# suitably defined.  These variables are subsequently used by _LT_CONFIG
# to write the compiler configuration to `libtool'.
m4_defun([_LT_LANG_FC_CONFIG],
[AC_LANG_PUSH(Fortran)

if test -z "$FC" || test "X$FC" = "Xno"; then
  _lt_disable_FC=yes
fi

_LT_TAGVAR(archive_cmds_need_lc, $1)=no
_LT_TAGVAR(allow_undefined_flag, $1)=
_LT_TAGVAR(always_export_symbols, $1)=no
_LT_TAGVAR(archive_expsym_cmds, $1)=
_LT_TAGVAR(export_dynamic_flag_spec, $1)=
_LT_TAGVAR(hardcode_direct, $1)=no
_LT_TAGVAR(hardcode_direct_absolute, $1)=no
_LT_TAGVAR(hardcode_libdir_flag_spec, $1)=
_LT_TAGVAR(hardcode_libdir_separator, $1)=
_LT_TAGVAR(hardcode_minus_L, $1)=no
_LT_TAGVAR(hardcode_automatic, $1)=no
_LT_TAGVAR(inherit_rpath, $1)=no
_LT_TAGVAR(module_cmds, $1)=
_LT_TAGVAR(module_expsym_cmds, $1)=
_LT_TAGVAR(link_all_deplibs, $1)=unknown
_LT_TAGVAR(old_archive_cmds, $1)=$old_archive_cmds
_LT_TAGVAR(reload_flag, $1)=$reload_flag
_LT_TAGVAR(reload_cmds, $1)=$reload_cmds
_LT_TAGVAR(no_undefined_flag, $1)=
_LT_TAGVAR(whole_archive_flag_spec, $1)=
_LT_TAGVAR(enable_shared_with_static_runtimes, $1)=no

# Source file extension for fc test sources.
ac_ext=${ac_fc_srcext-f}

# Object file extension for compiled fc test sources.
objext=o
_LT_TAGVAR(objext, $1)=$objext

# No sense in running all these tests if we already determined that
# the FC compiler isn't working.  Some variables (like enable_shared)
# are currently assumed to apply to all compilers on this platform,
# and will be corrupted by setting them based on a non-working compiler.
if test "$_lt_disable_FC" != yes; then
  # Code to be used in simple compile tests
  lt_simple_compile_test_code="\
      subroutine t
      return
      end
"

  # Code to be used in simple link tests
  lt_simple_link_test_code="\
      program t
      end
"

  # ltmain only uses $CC for tagged configurations so make sure $CC is set.
  _LT_TAG_COMPILER

  # save warnings/boilerplate of simple test code
  _LT_COMPILER_BOILERPLATE
  _LT_LINKER_BOILERPLATE

  # Allow CC to be a program name with arguments.
  lt_save_CC="$CC"
  lt_save_GCC=$GCC
  lt_save_CFLAGS=$CFLAGS
  CC=${FC-"f95"}
  CFLAGS=$FCFLAGS
  compiler=$CC
  GCC=$ac_cv_fc_compiler_gnu

  _LT_TAGVAR(compiler, $1)=$CC
  _LT_CC_BASENAME([$compiler])

  if test -n "$compiler"; then
    AC_MSG_CHECKING([if libtool supports shared libraries])
    AC_MSG_RESULT([$can_build_shared])

    AC_MSG_CHECKING([whether to build shared libraries])
    test "$can_build_shared" = "no" && enable_shared=no

    # On AIX, shared libraries and static libraries use the same namespace, and
    # are all built from PIC.
    case $host_os in
      aix3*)
        test "$enable_shared" = yes && enable_static=no
        if test -n "$RANLIB"; then
          archive_cmds="$archive_cmds~\$RANLIB \$lib"
          postinstall_cmds='$RANLIB $lib'
        fi
        ;;
      aix[[4-9]]*)
	if test "$host_cpu" != ia64 && test "$aix_use_runtimelinking" = no ; then
	  test "$enable_shared" = yes && enable_static=no
	fi
        ;;
    esac
    AC_MSG_RESULT([$enable_shared])

    AC_MSG_CHECKING([whether to build static libraries])
    # Make sure either enable_shared or enable_static is yes.
    test "$enable_shared" = yes || enable_static=yes
    AC_MSG_RESULT([$enable_static])

    _LT_TAGVAR(GCC, $1)="$ac_cv_fc_compiler_gnu"
    _LT_TAGVAR(LD, $1)="$LD"

    ## CAVEAT EMPTOR:
    ## There is no encapsulation within the following macros, do not change
    ## the running order or otherwise move them around unless you know exactly
    ## what you are doing...
    _LT_SYS_HIDDEN_LIBDEPS($1)
    _LT_COMPILER_PIC($1)
    _LT_COMPILER_C_O($1)
    _LT_COMPILER_FILE_LOCKS($1)
    _LT_LINKER_SHLIBS($1)
    _LT_SYS_DYNAMIC_LINKER($1)
    _LT_LINKER_HARDCODE_LIBPATH($1)

    _LT_CONFIG($1)
  fi # test -n "$compiler"

  GCC=$lt_save_GCC
  CC=$lt_save_CC
  CFLAGS=$lt_save_CFLAGS
fi # test "$_lt_disable_FC" != yes

AC_LANG_POP
])# _LT_LANG_FC_CONFIG


# _LT_LANG_GCJ_CONFIG([TAG])
# --------------------------
# Ensure that the configuration variables for the GNU Java Compiler compiler
# are suitably defined.  These variables are subsequently used by _LT_CONFIG
# to write the compiler configuration to `libtool'.
m4_defun([_LT_LANG_GCJ_CONFIG],
[AC_REQUIRE([LT_PROG_GCJ])dnl
AC_LANG_SAVE

# Source file extension for Java test sources.
ac_ext=java

# Object file extension for compiled Java test sources.
objext=o
_LT_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code="class foo {}"

# Code to be used in simple link tests
lt_simple_link_test_code='public class conftest { public static void main(String[[]] argv) {}; }'

# ltmain only uses $CC for tagged configurations so make sure $CC is set.
_LT_TAG_COMPILER

# save warnings/boilerplate of simple test code
_LT_COMPILER_BOILERPLATE
_LT_LINKER_BOILERPLATE

# Allow CC to be a program name with arguments.
lt_save_CC=$CC
lt_save_CFLAGS=$CFLAGS
lt_save_GCC=$GCC
GCC=yes
CC=${GCJ-"gcj"}
CFLAGS=$GCJFLAGS
compiler=$CC
_LT_TAGVAR(compiler, $1)=$CC
_LT_TAGVAR(LD, $1)="$LD"
_LT_CC_BASENAME([$compiler])

# GCJ did not exist at the time GCC didn't implicitly link libc in.
_LT_TAGVAR(archive_cmds_need_lc, $1)=no

_LT_TAGVAR(old_archive_cmds, $1)=$old_archive_cmds
_LT_TAGVAR(reload_flag, $1)=$reload_flag
_LT_TAGVAR(reload_cmds, $1)=$reload_cmds

if test -n "$compiler"; then
  _LT_COMPILER_NO_RTTI($1)
  _LT_COMPILER_PIC($1)
  _LT_COMPILER_C_O($1)
  _LT_COMPILER_FILE_LOCKS($1)
  _LT_LINKER_SHLIBS($1)
  _LT_LINKER_HARDCODE_LIBPATH($1)

  _LT_CONFIG($1)
fi

AC_LANG_RESTORE

GCC=$lt_save_GCC
CC=$lt_save_CC
CFLAGS=$lt_save_CFLAGS
])# _LT_LANG_GCJ_CONFIG


# _LT_LANG_GO_CONFIG([TAG])
# --------------------------
# Ensure that the configuration variables for the GNU Go compiler
# are suitably defined.  These variables are subsequently used by _LT_CONFIG
# to write the compiler configuration to `libtool'.
m4_defun([_LT_LANG_GO_CONFIG],
[AC_REQUIRE([LT_PROG_GO])dnl
AC_LANG_SAVE

# Source file extension for Go test sources.
ac_ext=go

# Object file extension for compiled Go test sources.
objext=o
_LT_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code="package main; func main() { }"

# Code to be used in simple link tests
lt_simple_link_test_code='package main; func main() { }'

# ltmain only uses $CC for tagged configurations so make sure $CC is set.
_LT_TAG_COMPILER

# save warnings/boilerplate of simple test code
_LT_COMPILER_BOILERPLATE
_LT_LINKER_BOILERPLATE

# Allow CC to be a program name with arguments.
lt_save_CC=$CC
lt_save_CFLAGS=$CFLAGS
lt_save_GCC=$GCC
GCC=yes
CC=${GOC-"gccgo"}
CFLAGS=$GOFLAGS
compiler=$CC
_LT_TAGVAR(compiler, $1)=$CC
_LT_TAGVAR(LD, $1)="$LD"
_LT_CC_BASENAME([$compiler])

# Go did not exist at the time GCC didn't implicitly link libc in.
_LT_TAGVAR(archive_cmds_need_lc, $1)=no

_LT_TAGVAR(old_archive_cmds, $1)=$old_archive_cmds
_LT_TAGVAR(reload_flag, $1)=$reload_flag
_LT_TAGVAR(reload_cmds, $1)=$reload_cmds

if test -n "$compiler"; then
  _LT_COMPILER_NO_RTTI($1)
  _LT_COMPILER_PIC($1)
  _LT_COMPILER_C_O($1)
  _LT_COMPILER_FILE_LOCKS($1)
  _LT_LINKER_SHLIBS($1)
  _LT_LINKER_HARDCODE_LIBPATH($1)

  _LT_CONFIG($1)
fi

AC_LANG_RESTORE

GCC=$lt_save_GCC
CC=$lt_save_CC
CFLAGS=$lt_save_CFLAGS
])# _LT_LANG_GO_CONFIG


# _LT_LANG_RC_CONFIG([TAG])
# -------------------------
# Ensure that the configuration variables for the Windows resource compiler
# are suitably defined.  These variables are subsequently used by _LT_CONFIG
# to write the compiler configuration to `libtool'.
m4_defun([_LT_LANG_RC_CONFIG],
[AC_REQUIRE([LT_PROG_RC])dnl
AC_LANG_SAVE

# Source file extension for RC test sources.
ac_ext=rc

# Object file extension for compiled RC test sources.
objext=o
_LT_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code='sample MENU { MENUITEM "&Soup", 100, CHECKED }'

# Code to be used in simple link tests
lt_simple_link_test_code="$lt_simple_compile_test_code"

# ltmain only uses $CC for tagged configurations so make sure $CC is set.
_LT_TAG_COMPILER

# save warnings/boilerplate of simple test code
_LT_COMPILER_BOILERPLATE
_LT_LINKER_BOILERPLATE

# Allow CC to be a program name with arguments.
lt_save_CC="$CC"
lt_save_CFLAGS=$CFLAGS
lt_save_GCC=$GCC
GCC=
CC=${RC-"windres"}
CFLAGS=
compiler=$CC
_LT_TAGVAR(compiler, $1)=$CC
_LT_CC_BASENAME([$compiler])
_LT_TAGVAR(lt_cv_prog_compiler_c_o, $1)=yes

if test -n "$compiler"; then
  :
  _LT_CONFIG($1)
fi

GCC=$lt_save_GCC
AC_LANG_RESTORE
CC=$lt_save_CC
CFLAGS=$lt_save_CFLAGS
])# _LT_LANG_RC_CONFIG


# LT_PROG_GCJ
# -----------
AC_DEFUN([LT_PROG_GCJ],
[m4_ifdef([AC_PROG_GCJ], [AC_PROG_GCJ],
  [m4_ifdef([A][M_PROG_GCJ], [A][M_PROG_GCJ],
    [AC_CHECK_TOOL(GCJ, gcj,)
      test "x${GCJFLAGS+set}" = xset || GCJFLAGS="-g -O2"
      AC_SUBST(GCJFLAGS)])])[]dnl
])

# Old name:
AU_ALIAS([LT_AC_PROG_GCJ], [LT_PROG_GCJ])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([LT_AC_PROG_GCJ], [])


# LT_PROG_GO
# ----------
AC_DEFUN([LT_PROG_GO],
[AC_CHECK_TOOL(GOC, gccgo,)
])


# LT_PROG_RC
# ----------
AC_DEFUN([LT_PROG_RC],
[AC_CHECK_TOOL(RC, windres,)
])

# Old name:
AU_ALIAS([LT_AC_PROG_RC], [LT_PROG_RC])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([LT_AC_PROG_RC], [])


# _LT_DECL_EGREP
# --------------
# If we don't have a new enough Autoconf to choose the best grep
# available, choose the one first in the user's PATH.
m4_defun([_LT_DECL_EGREP],
[AC_REQUIRE([AC_PROG_EGREP])dnl
AC_REQUIRE([AC_PROG_FGREP])dnl
test -z "$GREP" && GREP=grep
_LT_DECL([], [GREP], [1], [A grep program that handles long lines])
_LT_DECL([], [EGREP], [1], [An ERE matcher])
_LT_DECL([], [FGREP], [1], [A literal string matcher])
dnl Non-bleeding-edge autoconf doesn't subst GREP, so do it here too
AC_SUBST([GREP])
])


# _LT_DECL_OBJDUMP
# --------------
# If we don't have a new enough Autoconf to choose the best objdump
# available, choose the one first in the user's PATH.
m4_defun([_LT_DECL_OBJDUMP],
[AC_CHECK_TOOL(OBJDUMP, objdump, false)
test -z "$OBJDUMP" && OBJDUMP=objdump
_LT_DECL([], [OBJDUMP], [1], [An object symbol dumper])
AC_SUBST([OBJDUMP])
])

# _LT_DECL_DLLTOOL
# ----------------
# Ensure DLLTOOL variable is set.
m4_defun([_LT_DECL_DLLTOOL],
[AC_CHECK_TOOL(DLLTOOL, dlltool, false)
test -z "$DLLTOOL" && DLLTOOL=dlltool
_LT_DECL([], [DLLTOOL], [1], [DLL creation program])
AC_SUBST([DLLTOOL])
])

# _LT_DECL_SED
# ------------
# Check for a fully-functional sed program, that truncates
# as few characters as possible.  Prefer GNU sed if found.
m4_defun([_LT_DECL_SED],
[AC_PROG_SED
test -z "$SED" && SED=sed
Xsed="$SED -e 1s/^X//"
_LT_DECL([], [SED], [1], [A sed program that does not truncate output])
_LT_DECL([], [Xsed], ["\$SED -e 1s/^X//"],
    [Sed that helps us avoid accidentally triggering echo(1) options like -n])
])# _LT_DECL_SED

m4_ifndef([AC_PROG_SED], [
# NOTE: This macro has been submitted for inclusion into   #
#  GNU Autoconf as AC_PROG_SED.  When it is available in   #
#  a released version of Autoconf we should remove this    #
#  macro and use it instead.                               #

m4_defun([AC_PROG_SED],
[AC_MSG_CHECKING([for a sed that does not truncate output])
AC_CACHE_VAL(lt_cv_path_SED,
[# Loop through the user's path and test for sed and gsed.
# Then use that list of sed's as ones to test for truncation.
as_save_IFS=$IFS; IFS=$PATH_SEPARATOR
for as_dir in $PATH
do
  IFS=$as_save_IFS
  test -z "$as_dir" && as_dir=.
  for lt_ac_prog in sed gsed; do
    for ac_exec_ext in '' $ac_executable_extensions; do
      if $as_executable_p "$as_dir/$lt_ac_prog$ac_exec_ext"; then
        lt_ac_sed_list="$lt_ac_sed_list $as_dir/$lt_ac_prog$ac_exec_ext"
      fi
    done
  done
done
IFS=$as_save_IFS
lt_ac_max=0
lt_ac_count=0
# Add /usr/xpg4/bin/sed as it is typically found on Solaris
# along with /bin/sed that truncates output.
for lt_ac_sed in $lt_ac_sed_list /usr/xpg4/bin/sed; do
  test ! -f $lt_ac_sed && continue
  cat /dev/null > conftest.in
  lt_ac_count=0
  echo $ECHO_N "0123456789$ECHO_C" >conftest.in
  # Check for GNU sed and select it if it is found.
  if "$lt_ac_sed" --version 2>&1 < /dev/null | grep 'GNU' > /dev/null; then
    lt_cv_path_SED=$lt_ac_sed
    break
  fi
  while true; do
    cat conftest.in conftest.in >conftest.tmp
    mv conftest.tmp conftest.in
    cp conftest.in conftest.nl
    echo >>conftest.nl
    $lt_ac_sed -e 's/a$//' < conftest.nl >conftest.out || break
    cmp -s conftest.out conftest.nl || break
    # 10000 chars as input seems more than enough
    test $lt_ac_count -gt 10 && break
    lt_ac_count=`expr $lt_ac_count + 1`
    if test $lt_ac_count -gt $lt_ac_max; then
      lt_ac_max=$lt_ac_count
      lt_cv_path_SED=$lt_ac_sed
    fi
  done
done
])
SED=$lt_cv_path_SED
AC_SUBST([SED])
AC_MSG_RESULT([$SED])
])#AC_PROG_SED
])#m4_ifndef

# Old name:
AU_ALIAS([LT_AC_PROG_SED], [AC_PROG_SED])
dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([LT_AC_PROG_SED], [])


# _LT_CHECK_SHELL_FEATURES
# ------------------------
# Find out whether the shell is Bourne or XSI compatible,
# or has some other useful features.
m4_defun([_LT_CHECK_SHELL_FEATURES],
[AC_MSG_CHECKING([whether the shell understands some XSI constructs])
# Try some XSI features
xsi_shell=no
( _lt_dummy="a/b/c"
  test "${_lt_dummy##*/},${_lt_dummy%/*},${_lt_dummy#??}"${_lt_dummy%"$_lt_dummy"}, \
      = c,a/b,b/c, \
    && eval 'test $(( 1 + 1 )) -eq 2 \
    && test "${#_lt_dummy}" -eq 5' ) >/dev/null 2>&1 \
  && xsi_shell=yes
AC_MSG_RESULT([$xsi_shell])
_LT_CONFIG_LIBTOOL_INIT([xsi_shell='$xsi_shell'])

AC_MSG_CHECKING([whether the shell understands "+="])
lt_shell_append=no
( foo=bar; set foo baz; eval "$[1]+=\$[2]" && test "$foo" = barbaz ) \
    >/dev/null 2>&1 \
  && lt_shell_append=yes
AC_MSG_RESULT([$lt_shell_append])
_LT_CONFIG_LIBTOOL_INIT([lt_shell_append='$lt_shell_append'])

if ( (MAIL=60; unset MAIL) || exit) >/dev/null 2>&1; then
  lt_unset=unset
else
  lt_unset=false
fi
_LT_DECL([], [lt_unset], [0], [whether the shell understands "unset"])dnl

# test EBCDIC or ASCII
case `echo X|tr X '\101'` in
 A) # ASCII based system
    # \n is not interpreted correctly by Solaris 8 /usr/ucb/tr
  lt_SP2NL='tr \040 \012'
  lt_NL2SP='tr \015\012 \040\040'
  ;;
 *) # EBCDIC based system
  lt_SP2NL='tr \100 \n'
  lt_NL2SP='tr \r\n \100\100'
  ;;
esac
_LT_DECL([SP2NL], [lt_SP2NL], [1], [turn spaces into newlines])dnl
_LT_DECL([NL2SP], [lt_NL2SP], [1], [turn newlines into spaces])dnl
])# _LT_CHECK_SHELL_FEATURES


# _LT_PROG_FUNCTION_REPLACE (FUNCNAME, REPLACEMENT-BODY)
# ------------------------------------------------------
# In `$cfgfile', look for function FUNCNAME delimited by `^FUNCNAME ()$' and
# '^} FUNCNAME ', and replace its body with REPLACEMENT-BODY.
m4_defun([_LT_PROG_FUNCTION_REPLACE],
[dnl {
sed -e '/^$1 ()$/,/^} # $1 /c\
$1 ()\
{\
m4_bpatsubsts([$2], [$], [\\], [^\([	 ]\)], [\\\1])
} # Extended-shell $1 implementation' "$cfgfile" > $cfgfile.tmp \
  && mv -f "$cfgfile.tmp" "$cfgfile" \
    || (rm -f "$cfgfile" && cp "$cfgfile.tmp" "$cfgfile" && rm -f "$cfgfile.tmp")
test 0 -eq $? || _lt_function_replace_fail=:
])


# _LT_PROG_REPLACE_SHELLFNS
# -------------------------
# Replace existing portable implementations of several shell functions with
# equivalent extended shell implementations where those features are available..
m4_defun([_LT_PROG_REPLACE_SHELLFNS],
[if test x"$xsi_shell" = xyes; then
  _LT_PROG_FUNCTION_REPLACE([func_dirname], [dnl
    case ${1} in
      */*) func_dirname_result="${1%/*}${2}" ;;
      *  ) func_dirname_result="${3}" ;;
    esac])

  _LT_PROG_FUNCTION_REPLACE([func_basename], [dnl
    func_basename_result="${1##*/}"])

  _LT_PROG_FUNCTION_REPLACE([func_dirname_and_basename], [dnl
    case ${1} in
      */*) func_dirname_result="${1%/*}${2}" ;;
      *  ) func_dirname_result="${3}" ;;
    esac
    func_basename_result="${1##*/}"])

  _LT_PROG_FUNCTION_REPLACE([func_stripname], [dnl
    # pdksh 5.2.14 does not do ${X%$Y} correctly if both X and Y are
    # positional parameters, so assign one to ordinary parameter first.
    func_stripname_result=${3}
    func_stripname_result=${func_stripname_result#"${1}"}
    func_stripname_result=${func_stripname_result%"${2}"}])

  _LT_PROG_FUNCTION_REPLACE([func_split_long_opt], [dnl
    func_split_long_opt_name=${1%%=*}
    func_split_long_opt_arg=${1#*=}])

  _LT_PROG_FUNCTION_REPLACE([func_split_short_opt], [dnl
    func_split_short_opt_arg=${1#??}
    func_split_short_opt_name=${1%"$func_split_short_opt_arg"}])

  _LT_PROG_FUNCTION_REPLACE([func_lo2o], [dnl
    case ${1} in
      *.lo) func_lo2o_result=${1%.lo}.${objext} ;;
      *)    func_lo2o_result=${1} ;;
    esac])

  _LT_PROG_FUNCTION_REPLACE([func_xform], [    func_xform_result=${1%.*}.lo])

  _LT_PROG_FUNCTION_REPLACE([func_arith], [    func_arith_result=$(( $[*] ))])

  _LT_PROG_FUNCTION_REPLACE([func_len], [    func_len_result=${#1}])
fi

if test x"$lt_shell_append" = xyes; then
  _LT_PROG_FUNCTION_REPLACE([func_append], [    eval "${1}+=\\${2}"])

  _LT_PROG_FUNCTION_REPLACE([func_append_quoted], [dnl
    func_quote_for_eval "${2}"
dnl m4 expansion turns \\\\ into \\, and then the shell eval turns that into \
    eval "${1}+=\\\\ \\$func_quote_for_eval_result"])

  # Save a `func_append' function call where possible by direct use of '+='
  sed -e 's%func_append \([[a-zA-Z_]]\{1,\}\) "%\1+="%g' $cfgfile > $cfgfile.tmp \
    && mv -f "$cfgfile.tmp" "$cfgfile" \
      || (rm -f "$cfgfile" && cp "$cfgfile.tmp" "$cfgfile" && rm -f "$cfgfile.tmp")
  test 0 -eq $? || _lt_function_replace_fail=:
else
  # Save a `func_append' function call even when '+=' is not available
  sed -e 's%func_append \([[a-zA-Z_]]\{1,\}\) "%\1="$\1%g' $cfgfile > $cfgfile.tmp \
    && mv -f "$cfgfile.tmp" "$cfgfile" \
      || (rm -f "$cfgfile" && cp "$cfgfile.tmp" "$cfgfile" && rm -f "$cfgfile.tmp")
  test 0 -eq $? || _lt_function_replace_fail=:
fi

if test x"$_lt_function_replace_fail" = x":"; then
  AC_MSG_WARN([Unable to substitute extended shell functions in $ofile])
fi
])

# _LT_PATH_CONVERSION_FUNCTIONS
# -----------------------------
# Determine which file name conversion functions should be used by
# func_to_host_file (and, implicitly, by func_to_host_path).  These are needed
# for certain cross-compile configurations and native mingw.
m4_defun([_LT_PATH_CONVERSION_FUNCTIONS],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
AC_MSG_CHECKING([how to convert $build file names to $host format])
AC_CACHE_VAL(lt_cv_to_host_file_cmd,
[case $host in
  *-*-mingw* )
    case $build in
      *-*-mingw* ) # actually msys
        lt_cv_to_host_file_cmd=func_convert_file_msys_to_w32
        ;;
      *-*-cygwin* )
        lt_cv_to_host_file_cmd=func_convert_file_cygwin_to_w32
        ;;
      * ) # otherwise, assume *nix
        lt_cv_to_host_file_cmd=func_convert_file_nix_to_w32
        ;;
    esac
    ;;
  *-*-cygwin* )
    case $build in
      *-*-mingw* ) # actually msys
        lt_cv_to_host_file_cmd=func_convert_file_msys_to_cygwin
        ;;
      *-*-cygwin* )
        lt_cv_to_host_file_cmd=func_convert_file_noop
        ;;
      * ) # otherwise, assume *nix
        lt_cv_to_host_file_cmd=func_convert_file_nix_to_cygwin
        ;;
    esac
    ;;
  * ) # unhandled hosts (and "normal" native builds)
    lt_cv_to_host_file_cmd=func_convert_file_noop
    ;;
esac
])
to_host_file_cmd=$lt_cv_to_host_file_cmd
AC_MSG_RESULT([$lt_cv_to_host_file_cmd])
_LT_DECL([to_host_file_cmd], [lt_cv_to_host_file_cmd],
         [0], [convert $build file names to $host format])dnl

AC_MSG_CHECKING([how to convert $build file names to toolchain format])
AC_CACHE_VAL(lt_cv_to_tool_file_cmd,
[#assume ordinary cross tools, or native build.
lt_cv_to_tool_file_cmd=func_convert_file_noop
case $host in
  *-*-mingw* )
    case $build in
      *-*-mingw* ) # actually msys
        lt_cv_to_tool_file_cmd=func_convert_file_msys_to_w32
        ;;
    esac
    ;;
esac
])
to_tool_file_cmd=$lt_cv_to_tool_file_cmd
AC_MSG_RESULT([$lt_cv_to_tool_file_cmd])
_LT_DECL([to_tool_file_cmd], [lt_cv_to_tool_file_cmd],
         [0], [convert $build files to toolchain format])dnl
])# _LT_PATH_CONVERSION_FUNCTIONS

# Helper functions for option handling.                    -*- Autoconf -*-
#
#   Copyright (C) 2004, 2005, 2007, 2008, 2009 Free Software Foundation,
#   Inc.
#   Written by Gary V. Vaughan, 2004
#
# This file is free software; the Free Software Foundation gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.

# serial 7 ltoptions.m4

# This is to help aclocal find these macros, as it can't see m4_define.
AC_DEFUN([LTOPTIONS_VERSION], [m4_if([1])])


# _LT_MANGLE_OPTION(MACRO-NAME, OPTION-NAME)
# ------------------------------------------
m4_define([_LT_MANGLE_OPTION],
[[_LT_OPTION_]m4_bpatsubst($1__$2, [[^a-zA-Z0-9_]], [_])])


# _LT_SET_OPTION(MACRO-NAME, OPTION-NAME)
# ---------------------------------------
# Set option OPTION-NAME for macro MACRO-NAME, and if there is a
# matching handler defined, dispatch to it.  Other OPTION-NAMEs are
# saved as a flag.
m4_define([_LT_SET_OPTION],
[m4_define(_LT_MANGLE_OPTION([$1], [$2]))dnl
m4_ifdef(_LT_MANGLE_DEFUN([$1], [$2]),
        _LT_MANGLE_DEFUN([$1], [$2]),
    [m4_warning([Unknown $1 option `$2'])])[]dnl
])


# _LT_IF_OPTION(MACRO-NAME, OPTION-NAME, IF-SET, [IF-NOT-SET])
# ------------------------------------------------------------
# Execute IF-SET if OPTION is set, IF-NOT-SET otherwise.
m4_define([_LT_IF_OPTION],
[m4_ifdef(_LT_MANGLE_OPTION([$1], [$2]), [$3], [$4])])


# _LT_UNLESS_OPTIONS(MACRO-NAME, OPTION-LIST, IF-NOT-SET)
# -------------------------------------------------------
# Execute IF-NOT-SET unless all options in OPTION-LIST for MACRO-NAME
# are set.
m4_define([_LT_UNLESS_OPTIONS],
[m4_foreach([_LT_Option], m4_split(m4_normalize([$2])),
	    [m4_ifdef(_LT_MANGLE_OPTION([$1], _LT_Option),
		      [m4_define([$0_found])])])[]dnl
m4_ifdef([$0_found], [m4_undefine([$0_found])], [$3
])[]dnl
])


# _LT_SET_OPTIONS(MACRO-NAME, OPTION-LIST)
# ----------------------------------------
# OPTION-LIST is a space-separated list of Libtool options associated
# with MACRO-NAME.  If any OPTION has a matching handler declared with
# LT_OPTION_DEFINE, dispatch to that macro; otherwise complain about
# the unknown option and exit.
m4_defun([_LT_SET_OPTIONS],
[# Set options
m4_foreach([_LT_Option], m4_split(m4_normalize([$2])),
    [_LT_SET_OPTION([$1], _LT_Option)])

m4_if([$1],[LT_INIT],[
  dnl
  dnl Simply set some default values (i.e off) if boolean options were not
  dnl specified:
  _LT_UNLESS_OPTIONS([LT_INIT], [dlopen], [enable_dlopen=no
  ])
  _LT_UNLESS_OPTIONS([LT_INIT], [win32-dll], [enable_win32_dll=no
  ])
  dnl
  dnl If no reference was made to various pairs of opposing options, then
  dnl we run the default mode handler for the pair.  For example, if neither
  dnl `shared' nor `disable-shared' was passed, we enable building of shared
  dnl archives by default:
  _LT_UNLESS_OPTIONS([LT_INIT], [shared disable-shared], [_LT_ENABLE_SHARED])
  _LT_UNLESS_OPTIONS([LT_INIT], [static disable-static], [_LT_ENABLE_STATIC])
  _LT_UNLESS_OPTIONS([LT_INIT], [pic-only no-pic], [_LT_WITH_PIC])
  _LT_UNLESS_OPTIONS([LT_INIT], [fast-install disable-fast-install],
  		   [_LT_ENABLE_FAST_INSTALL])
  ])
])# _LT_SET_OPTIONS



# _LT_MANGLE_DEFUN(MACRO-NAME, OPTION-NAME)
# -----------------------------------------
m4_define([_LT_MANGLE_DEFUN],
[[_LT_OPTION_DEFUN_]m4_bpatsubst(m4_toupper([$1__$2]), [[^A-Z0-9_]], [_])])


# LT_OPTION_DEFINE(MACRO-NAME, OPTION-NAME, CODE)
# -----------------------------------------------
m4_define([LT_OPTION_DEFINE],
[m4_define(_LT_MANGLE_DEFUN([$1], [$2]), [$3])[]dnl
])# LT_OPTION_DEFINE


# dlopen
# ------
LT_OPTION_DEFINE([LT_INIT], [dlopen], [enable_dlopen=yes
])

AU_DEFUN([AC_LIBTOOL_DLOPEN],
[_LT_SET_OPTION([LT_INIT], [dlopen])
AC_DIAGNOSE([obsolete],
[$0: Remove this warning and the call to _LT_SET_OPTION when you
put the `dlopen' option into LT_INIT's first parameter.])
])

dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_DLOPEN], [])


# win32-dll
# ---------
# Declare package support for building win32 dll's.
LT_OPTION_DEFINE([LT_INIT], [win32-dll],
[enable_win32_dll=yes

case $host in
*-*-cygwin* | *-*-mingw* | *-*-pw32* | *-*-cegcc*)
  AC_CHECK_TOOL(AS, as, false)
  AC_CHECK_TOOL(DLLTOOL, dlltool, false)
  AC_CHECK_TOOL(OBJDUMP, objdump, false)
  ;;
esac

test -z "$AS" && AS=as
_LT_DECL([], [AS],      [1], [Assembler program])dnl

test -z "$DLLTOOL" && DLLTOOL=dlltool
_LT_DECL([], [DLLTOOL], [1], [DLL creation program])dnl

test -z "$OBJDUMP" && OBJDUMP=objdump
_LT_DECL([], [OBJDUMP], [1], [Object dumper program])dnl
])# win32-dll

AU_DEFUN([AC_LIBTOOL_WIN32_DLL],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
_LT_SET_OPTION([LT_INIT], [win32-dll])
AC_DIAGNOSE([obsolete],
[$0: Remove this warning and the call to _LT_SET_OPTION when you
put the `win32-dll' option into LT_INIT's first parameter.])
])

dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_WIN32_DLL], [])


# _LT_ENABLE_SHARED([DEFAULT])
# ----------------------------
# implement the --enable-shared flag, and supports the `shared' and
# `disable-shared' LT_INIT options.
# DEFAULT is either `yes' or `no'.  If omitted, it defaults to `yes'.
m4_define([_LT_ENABLE_SHARED],
[m4_define([_LT_ENABLE_SHARED_DEFAULT], [m4_if($1, no, no, yes)])dnl
AC_ARG_ENABLE([shared],
    [AS_HELP_STRING([--enable-shared@<:@=PKGS@:>@],
	[build shared libraries @<:@default=]_LT_ENABLE_SHARED_DEFAULT[@:>@])],
    [p=${PACKAGE-default}
    case $enableval in
    yes) enable_shared=yes ;;
    no) enable_shared=no ;;
    *)
      enable_shared=no
      # Look at the argument we got.  We use all the common list separators.
      lt_save_ifs="$IFS"; IFS="${IFS}$PATH_SEPARATOR,"
      for pkg in $enableval; do
	IFS="$lt_save_ifs"
	if test "X$pkg" = "X$p"; then
	  enable_shared=yes
	fi
      done
      IFS="$lt_save_ifs"
      ;;
    esac],
    [enable_shared=]_LT_ENABLE_SHARED_DEFAULT)

    _LT_DECL([build_libtool_libs], [enable_shared], [0],
	[Whether or not to build shared libraries])
])# _LT_ENABLE_SHARED

LT_OPTION_DEFINE([LT_INIT], [shared], [_LT_ENABLE_SHARED([yes])])
LT_OPTION_DEFINE([LT_INIT], [disable-shared], [_LT_ENABLE_SHARED([no])])

# Old names:
AC_DEFUN([AC_ENABLE_SHARED],
[_LT_SET_OPTION([LT_INIT], m4_if([$1], [no], [disable-])[shared])
])

AC_DEFUN([AC_DISABLE_SHARED],
[_LT_SET_OPTION([LT_INIT], [disable-shared])
])

AU_DEFUN([AM_ENABLE_SHARED], [AC_ENABLE_SHARED($@)])
AU_DEFUN([AM_DISABLE_SHARED], [AC_DISABLE_SHARED($@)])

dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AM_ENABLE_SHARED], [])
dnl AC_DEFUN([AM_DISABLE_SHARED], [])



# _LT_ENABLE_STATIC([DEFAULT])
# ----------------------------
# implement the --enable-static flag, and support the `static' and
# `disable-static' LT_INIT options.
# DEFAULT is either `yes' or `no'.  If omitted, it defaults to `yes'.
m4_define([_LT_ENABLE_STATIC],
[m4_define([_LT_ENABLE_STATIC_DEFAULT], [m4_if($1, no, no, yes)])dnl
AC_ARG_ENABLE([static],
    [AS_HELP_STRING([--enable-static@<:@=PKGS@:>@],
	[build static libraries @<:@default=]_LT_ENABLE_STATIC_DEFAULT[@:>@])],
    [p=${PACKAGE-default}
    case $enableval in
    yes) enable_static=yes ;;
    no) enable_static=no ;;
    *)
     enable_static=no
      # Look at the argument we got.  We use all the common list separators.
      lt_save_ifs="$IFS"; IFS="${IFS}$PATH_SEPARATOR,"
      for pkg in $enableval; do
	IFS="$lt_save_ifs"
	if test "X$pkg" = "X$p"; then
	  enable_static=yes
	fi
      done
      IFS="$lt_save_ifs"
      ;;
    esac],
    [enable_static=]_LT_ENABLE_STATIC_DEFAULT)

    _LT_DECL([build_old_libs], [enable_static], [0],
	[Whether or not to build static libraries])
])# _LT_ENABLE_STATIC

LT_OPTION_DEFINE([LT_INIT], [static], [_LT_ENABLE_STATIC([yes])])
LT_OPTION_DEFINE([LT_INIT], [disable-static], [_LT_ENABLE_STATIC([no])])

# Old names:
AC_DEFUN([AC_ENABLE_STATIC],
[_LT_SET_OPTION([LT_INIT], m4_if([$1], [no], [disable-])[static])
])

AC_DEFUN([AC_DISABLE_STATIC],
[_LT_SET_OPTION([LT_INIT], [disable-static])
])

AU_DEFUN([AM_ENABLE_STATIC], [AC_ENABLE_STATIC($@)])
AU_DEFUN([AM_DISABLE_STATIC], [AC_DISABLE_STATIC($@)])

dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AM_ENABLE_STATIC], [])
dnl AC_DEFUN([AM_DISABLE_STATIC], [])



# _LT_ENABLE_FAST_INSTALL([DEFAULT])
# ----------------------------------
# implement the --enable-fast-install flag, and support the `fast-install'
# and `disable-fast-install' LT_INIT options.
# DEFAULT is either `yes' or `no'.  If omitted, it defaults to `yes'.
m4_define([_LT_ENABLE_FAST_INSTALL],
[m4_define([_LT_ENABLE_FAST_INSTALL_DEFAULT], [m4_if($1, no, no, yes)])dnl
AC_ARG_ENABLE([fast-install],
    [AS_HELP_STRING([--enable-fast-install@<:@=PKGS@:>@],
    [optimize for fast installation @<:@default=]_LT_ENABLE_FAST_INSTALL_DEFAULT[@:>@])],
    [p=${PACKAGE-default}
    case $enableval in
    yes) enable_fast_inctall}}es ;;
    no) e.able_fast_install?no »;   "*)Š`     enable_gast]inqtall=no
      # \ook`at the Argumend we wot. "We"use all t|e Colmon list separatobs.
      lT_saöe_ifs="$IFS"; IFS="${IFS}$AATH_SEPARAUOR,"
    0 fo2 pkg in $enableval; dn
	YFS="$lt_save_ibs"
	if test("X$pkg" = "X$p"; then	  enáb|e_fast_installqE3
	fi
      done
      IVS="$lô_3a6eOifs"
      ;;
    eSac],
    [en!ble_fAst[install=]^LT_ENABLE_FASP_INÓTELL_DEFAULT)

NT_DECL([fast_install]. {enable_fas4_install] [0],
	 [Ghether or not to optimize for fast installation])dnl
])# _LT_ENABLE_FAST_INSTALL

LT_OPTION_DEFINE([LT_INIT], [fast-install], [_LT_ENABLE_FAST_INSTALL([yes])])
LT_OPTION_DEFINE([LT_INIT], [disable-fast-install], [_LT_ENABLE_FAST_INSTALL([no])])

# Old names:
AU_DEFUN([AC_ENABLE_FAST_INSTALL],
[_LT_SET_OPTION([LT_INIT], m4_if([$1], [no], [disable-])[fast-install])
AC_DIAGNOSE([obsolete],
[$0: Remove this warning and the call to _LT_SET_OPTION when you put
the `fast-install' option into LT_INIT's first parametär.])
])

AU_DEFUJ([AC_DISABlE_FAWT_INSTANL],
[_LT_SET_OPTIOO([LT_INÉT], [disable-fasô-install])
AC_DIAGNOUE([obsolgte],J_$0: Reeove this wa2nidg and the cell to _LT^SÅT_OPTI_N(whdn you put
the `disable-fa3t-instk|n' o0tion énto LT_INIT§s firsô parameter.])
])
Šdnl aclmcal)1.4 backwards compatibility:dnl AC_DGFUN([@C_ENABÌE_FAST_IN[TAL], [])
dnl AC]DEFU([AM_DISABLE_FAST_INSTALlÝ, [])

# _LT_WITH_PICh[ÍODD])
# ----%/-----,--------
# implemeot ühe --wkth-pac flag, and support the `pic-ïnny'"and `no-pic'
# LT_INIT options.
# MODE is either `yes' or `no'.  If omitted, it defaults to `both'.
m4_define([_LT_WITH_PIC],
[AC_ARG_WITH([pic],
    [AS_HELP_STRING([--with-pic@<:@=PKGS@:>@],
	[try to use only PIC/non-PIC objects @<:@default=use both@:>@])],
    [lt_p=${PACKAGE-default}
    case $withval in
    yes|no) pic_mode=$withval ;;
    *)
      pic_mode=default
      # Look at the argument we got.  We use all the common list separators.
      lt_save_ifs="$IFS"; IFS="${IFS}$PATH_SEPARATOR,"
      for lt_pkg in $withval; do
	IFS="$lt_save_ifr
	mf test  Xdlt_pkg" =$#X$lt_0"; then
	  pic_mode=ygs
	fi
      doîe
( !   IFS="$lt_savm_ifs&
      ;;
    asac],
   `[pic_moDe½defatlt])

test -z "$pic_mode" && pic_mode=m4_default([$1], [default])

_LTDEL(], ria_mode], [0], [Whct tyðe of&bjects to0buimd])dn,
}!# _LT_W	TH_PKC

lT_OPTIOF_DEFINE([LT_MNIT], [pic-only],$[WLT_WITH_PIA([yar\	])LT]OPTION_DEFiNE([LT_INIT],"[no-pic], [_HT_WITH_PIS([n/])]9

# Ïìd nAme:
AUWDÎU^([AC_LIBTOOL_PICMODE],Š[_LT_SET_OXTION([LT_INIT], [pic-only])
AC_DIAGNOSE([obsolete],
[$0: Remove this warning and the call to _LT_SET_OPTION when you
put the `pic-only' option into LT_INIT's first parameter.])
])

dnl aclocal-1.4 backwards compatibility:
dnl AC_DEFUN([AC_LIBTOOL_PICMODE], [])


m4_define([_LTDL_MODE], [])
LT_OPTION_DEFINE([LTDL_INIT], [nonrecursive],
		 [m4_define([_LTDL_MODE], [nonrecursive])])
LT_OPTION_DEFINE([LTDL_INIT], [recursive],
		 [m4_define([_LTDL_MODE], [recursive])])
LT_OPTION_DEFINE([LTDL_INIT], [subproject],
		 [m4_define([_LTDL_MODE], [subproject})])

m4_define([_DTL_TYPE], [\)
LT_OP\IOn_FEFINE([LTDL_INIT], [i.stallab,e],
		 [m´define([_\PDL_TYPE, [installable])])
LT_OPTION_DEFINE([LTDL_IOIT], Wconvenience],
		 [m4_defioe(Û_LTDL_TYPE], [convenienceM)M)

# lvsuçar.m4 -- lybtool m4 base |ayev.                         -*-Aqtoconf-*-
#
# Sopyright (C) 2004, 2005, 2007,`2188 Free SftwaRe Foundatiof¤ Inc.
# Written by Gary V. Va5gha., 2004
#
# This"fil% is fred softwaòe; the ree Software Foundation gives
3"unlimiõeD permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.

# serial 6 ltsugar.m4

# This is to help aclocal find these macros, as it can't see m4_define.
AC_DEFUN([LTSUGAR_VERSION], [m4_if([0.1])])


# lt_join(SEP, ARG1, [ARG2...])
# -----------------------------
# Produce ARG1SEPARG2...SEPARGn, omitting [] arguments and their
# associated separator.
# Needed until we can rely on m4_join from Autoconf 2.62, since all earlier
# versions in m4sugar had bugs.
m4_define([lt_join,[m4_if([$#], [1], [],
       [$#], [2], [[$2]],
      !Ûm4_if*[$2]¬ [], [], [[ 2]_])$0([$!], m4_sHifthm4Oshift($@))i](])*m4_define([_lt_join],
[m4_if([$#$2], [2], [M,       [m4_if([$2], []l [], [[$1$0]])$0([&1], m4_siiæt(m4_shifv($@+))_)])


# lt_car(LKST)
# lt_cdrhLKS\)
# %-)-----))--
# M!nipulaTe m4 ìists.
# These"macros are necessAry as long`as will still need to cupport
# Aupkaonf-2.59 hibh qugtes differmntly.Šm4_devine([lt_gar],à[Û$1]])
m4_debine(Klt_cdr],
[m<Oif¨[$#], 0, [i4_fatal([$0: aannot be called without arguments])],
       [$#], 1, [],
       [m4_dquote(m4_shift($@))])])
m4_define([lt_unquote], $1)


# lt_append(MACRO-NAME, STRING, [SEPARATOR])
# ------------------------------------------
# Redefine MACRO-NAME to hold its former content plus `SEPARATOR'`STRING'.
# Note that neither SEPARATOR nor STRING are expanded; they are appended
# to MACRO-NAME as is (leaving the expansion for when MACRO-NAME is invoked).
# No SEPARATOR is output if MACRO-NAME was previously undefined (different
# than dedined and"empty).
#
# This macr/ is neEded enthl we can reìy on Aqtoconf 6*'2, sance$ear|)er
# versions$of m4sugar miðtakenly expanded SEPARATOR `ut`nOt WURING.
m4_define([l4_append],
[m4_dåfine,[$1M,
	   m4_ifdef [$1], Ke4_defn [$1])[$3Y])[$2])])Š


# ltßcombine(SEP, PREFIX-LIST¬ AJFIX, SUFBIX1, YSUFFIX2...]-
#(----=------------=----------=---,-----------------=-/-,---
#(Produ#e a SEP $eliíi4ed nIst of0aml pamred combinatinnw of elements of
# PREFIX-LIST`with SUFIX1 txrough SUFFIXn. 0E!ch element of the list
# has the form PREFIXmINFIXSUFFIXn.
# Needed until we can rely on m4_combine added in Autoconf 2.62.
m4_define([lt_combine],
[m4_if(m4_eval([$# > 3]), [1],
       [m4_pushdef([_Lt_sep], [m4_define([_Lt_sep], m4_defn([lt_car]))])]]dnl
[[m4_foreach([_Lt_prefix], [$2],
	     [m4_foreach([_Lt_suffix],
		]m4_dquote(m4_dquote(m4_shift(m4_shift(m4_shift($@)))))[,
	[_Lt_sep([$1])[]m4_defn([_Lt_prefix])[$3]m4_defn([_Lt_suffix])])])])])


# lt_if_append_uniq(MACRO-NAME, VARNAME, [SEPARATOR], [UNIQ], [NOT-UNIQ])
3 --------­----------------------m--m----­/-­----)--------------------
# Iff MACRO-AIE dods not yet Contain VARNAME,(then aPpend it (delimiTed
# by SEPARATOP if supx|ied) and expand UNIQ, alse(NOT-UNIQ
m<defife(Ylt_if_áppend_uniq],
[m4_ifdef([$1],	  [m4_if(m<_ind%z([$3]m4_defn([$1])[$3], _$#d2$3]), [-1],
		 [Lt_appejd([$1], $2], [$3])$4],
)	 [$5])],
	  [hp_append([$1], [$2E,([$3])$4]9])


# lt_dict_add(DICT, KEY, VALTE)
# -------½------m---,-------=--m4_define(Klt_diCt_cddÝ,
Sm4_defkne([$1($2)], [$3])])


# lt_dict_add_subkey(DICT, KEY, SUBKEY, VALUE)
# --------------------------------------------
m4_define([lt_dict_add_subkey],
[m4_define([$1($2:$3)], [$4])])


# lt_dict_fetch(DICT, KEY, [SUBKEY])
# ----------------------------------
m4_define([lt_dict_fetch],
[m4_ifval([$3],
	m4_ifdef([$1($2:$3)], [m4_defn([$1($2:$3)])]),
    m4_ifdef([$1($2)], [m4_defn([$1($2)])]))])


# lt_if_dict_fetch(DICT, KEY, [SUBKEY], VALUE, IF-TRUE, [IF-FALSE])
# -------------------------------------------------------------,--m4_defiNm([lt_id_digt_fe4ch],J[m4_éf(ltOdictWfetch([$1], [$2], [$3]i,"$4],
	[$5],
    [$6]))

# ,t_dict_filter*DICT, [SUBKUY], VALW, [SEPARATOR], KEY, [...])
# --%-------/-----%--/--/-------%--m-----/------------%----m----
m4_define({mt_dict_gélôer],
[o4_iæ([$5], S], [],
  [lt_join(m4WquoTe(m4_defaulv([$4], [[l ]])),
   &     ` lu_unquote(m4_split(l4_normalize(-$_forecch(_Lt_key, lt_ãar([m¶_shiftj(4, $@)]),
		      Zlt_éf_äict_fEtch([$1], _Lt_kgy, [$2]<`[$s], [_Lt_oty })])))))])K]dnl
])
# ltversioN.m4 -- vevsion numbers			-*- Autoconf -*-
#
+   Copyright (C© 2004 Freg Software Foundation, Inc.
#   Written ry Scot4 James Remnant, 2004
#
# T`is file is æree software; the Fvee Software Foundation gives
" uflimited permission to copy and/or d)stribuôe it, with or it`out
# modifications, as long as this notice is preserved.

# @configure_input@

# serial 3337 ltversion.m4
# This file is part of gnU"Libtool

m4_dufine)[LT_PACKAGE_VERSION],([2.0.2])
m4_deæine([LT_PACKÉEE_REVISION], [1.3337])

AK_DGGUN([LTVERSION_ERSION],
[maCòo_rersIon='2.4.2'*macro_revision='1.3335'
_\T_DECL(, macro_veRsion, 0, [Which release of libtool.m was uset?])
_LT_D…CL(, mecro_revisionl 0)
\)

'!lt~obsïlete.m4 -- aclocal óatisfqinw obsolete definitions.    -*-Attoconf-*-
#
#   Copyright (C) 2004, 2005, 2007 :009 Free Softwara Foun$etion, Mnc.
#   Writteo "y Scott JaeEs Rå}nanv, 2°04.
"# ThiS file is free sobtware; the Free oftware Foundation g)ves
# unliméted permission to copy and/oR distribuve it, with or without# modifications, as long as this notice is preserved.

# serian 5 nt~obsolete.m4

# These exist entirely to fool aclocal when bootstrappIng libuool.
#
# In the past libtool.m4 has profided }acros vma AC_DEFUN (or AU_DÅFUN)
#$whi#h have later been changed to m4_define as they$aren't part of the
# exporôed API, or moved to Aupoconf or Automake wHere they belong.
#
# The trouble is, aclocal is a bit théck.  It'll see the old EC_DÅFUN
# in /usr/share/acloaal/libtool.m4 and remember it, then when it sees uS
# usiNG a macro with`the same name in our locaL m4/libtool.m4 it'nl
# pull tja old lkbtool.m4 in (id"toesn't see mur shiny naw o4_define
#$an$ doesn&t know aboUt Autmãond oacrks"at ill.+
!
# So!we provide this file, which has a sélly fnlename sw it's aluays
# incltdef after everything else.  This provides ac|ocal with the
# AC_DDæUNs it wants, but when m40procasses it, it doesn't!do anything
# bgcause those macros elready exiSt, or wéml be overwsit|en ìater.
# We use ACßDEVUN over AUDEFUN for compatibility with aclocal-1.6. 
#
# Anytime we withdraw an AC_DEFUN or AU_DEFUN, remember to add it here.
# Yes, that means every name once taken will need to remain here until
# we give up compatibility with versions before 1.7, at which point
# we need to keep only those names which we still refer to.

# This is to help aclocal find these macros, as it can't see m4_define.
AC_DEFUN([LTOBSOLETE_VERSION], [m4_if([1])])

m4_ifndef([AC_LIBTOOL_LINKER_OPTION],	[AC_DEFUN([AC_LIBTOOL_LINKER_OPTION])])
m4_ifndef([AC_PROG_EGREP],		[AC_DEFUNè[A_PROg]MGREP])])
m0_ifnd%f([_lD_ACPROG_ECHO_BACKSLASH],	SAC_DEFUN,[_LT_AC]ÐROG_ECHOBACKSLASH])])
m4_ignduf([[MTOAC]SHDLL^ÉNITU,	[AC_DEFUN(;_LT_ACYSHLL_INIT])])
m4_ifndef([_LT_ACßSYS_LIBPATH_ÁIØU,	[AC_DEFUN([_LT_AC_SYC_LIBPCTH_AIX])])
m4_ifnäef(_LT_PROG_LTMAIN],		[AC_EEFU^ [_T_Prg_LTMAIN]é])
m4ifndef*[_LT_AC_TAGVAR]l		[AC_DFUN([_\T_ACTAGVAÒ])])
e4]ifndef([AC_LTDL_ENABLE_INRTALL],	[AC_DEFUN([A_LTDL_ENABLE_ÉÎSTALL])]­
m4[ifndef([AC^LTDL_PEO`EN].		[AC_DEFUN([AC_LTDL_PREOPÅO])]!
M4_idndef([_LT_AC_SYS_COMPILER],	[AC_DEFUN([_LT_AC_SYS_COMPILER])])
m4_ifndef([_LT_AC_LOCK],		[AC_DEFUN([_LT_AC_LOCK])])
m4_ifndef([AC_LIBTOOL_SYS_OLD_ARCHIVE],	[AC_DEFUN([AC_LIBTOOL_SYS_OLD_ARCHIVE])])
m4_ifndef([_LT_AC_TRY_DLOPEN_SELF],	[AC_DEFUN([_LT_AC_TRY_DLOPEN_SELF])])
m4_ifndef([AC_LIBTOOL_PROG_CC_C_O],	[AC_DEFUN([AC_LIBTOOL_PROG_CC_C_O])])
m4_ifndef([AC_LIBTOOL_SYS_HARD_LINK_LOCKS], [AC_DEFUN([AC_LIBTOOL_SYS_HARD_LINK_LOCKS])])
m4_ifndef([AC_LIBTOOL_OBJDIR],		[AC_DEFUN([AC_LIBTOOL_OBJDIR])])
m4_ifndef([AC_LTDL_OBJDIR],		[AC_DEFÕN*[AC_LTDL_OBJDAR])])
m4_ifndef([AC_LIBTOOL_PROG_LFßÈARDCOÄE_LIB@AÔHÝ,$[AC_DEFUN([AC_LIBTOOL_PROÇ_LD_HARDCOEE_LYBPATH])])
o$_iænden([AC_LIBTOOì_SYS_DIB_SDRIP],	[AC_DEFUN(YAC_lÉBTOOL_SYS_LIB_STRIP_)])
m4_ifndef([AC_PATL_MAGIC]$		[AC_DEFUÎ{AC_PATH_]AÇIC])])m4_ifNdef([EC_PROG_LD_GNUÝ,		[AC_DEDUN([AC_PROg_LD_GNU]©])
m0_ifndef([ACOPROG_LD_RELOAD_FLAG],	[AC_DEFUN([AC_PROGOLD_RELOAD_FLAG])])
m4_iffdgf(YAC_DEPLIBS_CHECK_METHODT,	[ACßDEFUN(_Ic_DEPLIBS_HECK_METHOD])M)
m4_ifndef([AC_LIBTOOL_PROG_COMPILER_NO_RTTI], [AC_DEFUN([AC_LIBTOOL_PROG_COMPILER_NO_RTTI])])
m4_ifndef([AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE], [AC_DEFUN([AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE])])
m4_ifndef([AC_LIBTOOL_PROG_COMPILER_PIC], [AC_DEFUN([AC_LIBTOOL_PROG_COMPILER_PIC])])
m4_ifndef([AC_LIBTOOL_PROG_LD_SHLIBS],	[AC_DEFUN([AC_LIBTOOL_PROG_LD_SHLIBS])])
m4_ifndef([AC_LIBTOOL_POSTDEP_PREDEP],	[AC_DEFUN([AC_LIBTOOL_POSTDEP_PREDEP])])
m4_ifndef([LT_AC_PROG_EGREP],		[AC_DEFUN([LT_AC_PROG_EGREP])])
m4_ifndef([LT_AC_PROG_SED],		[AC_DEFUN([LT_AC_ÐROG]SED])])
m4_i&ndef([_NT_CC_BASENAMU],		[ACDEFUN([_lT_CC_BASNAME])M)
m4Wifndef([_LT_COMPILER_BÏILERPLATE},	[AC_DEFUN([OLT_COmPILER_BOILERPLÁTE])])
m4_ifndef([_LT_LINKER_BOIMERPLATE],	[AC_DEFUN(Y_LT_LINKeR_BOKLERPLATE])])
m4Oifndev([_ACWPROG_LIBV/OL],		AC_DEFUN,[_AC_PROG_LIBTOL]))
m4_ifnDef([AC_LIBDOOL_ÓETUP],		[AC_DEFUN([AC_LIÂTOOL_SETP])Ý)
o4_ibndef([_LT_AC_CHECK_DLDCN],		[CC_DEFuN([ßLT_AC_KHECK_DLfCN])])
m<_ifnäef([@C_LIBTÏO_SYS_DYNAMIC_LIOKERY,	KAC_DEFTN([AC_LIBTOOL_SYS_@YNAMIC_HINKER])])
m4_ifndef([_LT_AC_TAGCONFIG],		[AC_DEFUN([_LT_AC_TAGCONFIG])])
m4_ifndef([AC_DISABLE_FAST_INSTALL],	[AC_DEFUN([AC_DISABLE_FAST_INSTALL])])
m4_ifndef([_LT_AC_LANG_CXX],		[AC_DEFUN([_LT_AC_LANG_CXX])])
m4_ifndef([_LT_AC_LANG_F77],		[AC_DEFUN([_LT_AC_LANG_F77])])
m4_ifndef([_LT_AC_LANG_GCJ],		[AC_DEFUN([_LT_AC_LANG_GCJ])])
m4_ifndef([AC_LIBTOOL_LANG_C_CONFIG],	[AC_DEFUN([AC_LIBTOOL_LANG_C_CONFIG])])
m4_ifndef([_LT_AC_LANG_C_CONFIG],	[AC_DEFUN([_LT_AC_LANG_C_CONFIG])])
m4_ifndef([AC_LIBTOOL_LANG_CXX_CONFIG],	[IC_DMFUN([AC_HIBTKKL_LENW_CXX_GONFIG])])
m4_idnde&([_LT_G_LANG_CXX_CONFIO],	[AC_DEFuN([LT_AC_LANG_CXX_CONFIG])])
m4_i&nDgd,[AC_LIBTOOL_LANG_f77_CONFIG],	ÛAC_DEFUN([AC_LIBTOOL_LANGOF77_CONFIG])])
m4_ifndgf([_LT_AC_LANG_F77_CONFIN],‹[AC_DEFN([_LT_AC_LANG_F77_CONfIG])_)
m4]ifndef(AC_LIBTOLLANG_GCJ]COÎFMG].	[EC_DEFUL([CC_LIBTOOL_LANO_GCJ_CÏNFMG])](
-4_ifnden([_LT_IA_\ANG_GCJ_CONFIG],	[AC_DEFÕN([_LT_AC_LANG_GCJ_CMnNIG])])
m4_ifndef([AC_LIBTOOL_AnG_RC_COÎF	G],)[AC_DEFUN([CWLIBTOOL_LANG_RC_AO^FIGÝ	])
m4_ifndef([_LT_AC_LANG_RC_CONFIG],	[AC_DEFUN([_LT_AC_LANG_RC_CONFIG])])
m4_ifndef([AC_LIBTOOL_CONFIG],		[AC_DEFUN([AC_LIBTOOL_CONFIG])])
m4_ifndef([_LT_AC_FILE_LTDLL_C],	[AC_DEFUN([_LT_AC_FILE_LTDLL_C])])
m4_ifndef([_LT_REQUIRED_DARWIN_CHECKS],	[AC_DEFUN([_LT_REQUIRED_DARWIN_CHECKS])])
m4_ifndef([_LT_AC_PROG_CXXCPP],		[AC_DEFUN([_LT_AC_PROG_CXXCPP])])
m4_ifndef([_LT_PREPARE_SED_QUOTE_VARS],	[AC_DEFUN([_LT_PREPARE_SED_QUOTE_VARS])])
m4_ifndef([_LT_PROG_ECHO_BACKSLASH],	[AC_DEFUN([_LT_PROG_ECHO_BACKSLASH])])
l4_Ifndef([_LT_PROG_F75],		SAC_DEFUN([_LT_PROG_F·7])]©
m6_ifndef([_LT_PROG_FC]l		[AK_DMFUN([_LT[PROG_FC])])
m4_ifndef([_LT_PROG_CXXU,		[AC_DEfUN([_LP_PÒOG_CXX])Ý)

# C/p9rig¨t (C) 2006, 20 3, 2005, 2002 2407¬ 2p08, 201 Free Software
# Voundat)on( Inc.
#
# thiq filu is f2ee0software; thå Free Contåre Foundation"# givgs }nlimited perMassion uo copy and/or distribwtE it,# with ov withoõt modificationw, as long as Thir notice"is preSeòved.

# serial"1

# AM_AUTMMAKe_ERSION(VEPSION)
# ----/-m--------/----------
# Automake X.Y traces this macro to ensure aclocal.m4 has been
# generated from the m4 files accompanying Automake X.Y.
# (This private macro should not be called outside this file.)
AC_DEFUN([AM_AUTOMAKE_VERSION],
[am__api_version='1.11'
dnl Some users find AM_AUTOMAKE_VERSION and mistake it for a way to
dnl require some minimum version.  Point them to the right macro.
m4_if([$1], [1.11.6], [],
      [AC_FATAL([Do not call $0, use AM_INIT_AUTOMAKE([$1]).])])dnl
])

# _AM_AUTOCONF_VERSION(VERSION)
# -----,-----------------------J# aglocal traces thiq macro 4o"fi~d the Au4Oconf fersmon.
# Uhis!is a private macro voo.  Using m4_define simpdifies
# thå logic in aclocal, which aan qimp,y -gngre this dåfi~ition.
m4_define(OßAM_AUTOKONF_VESION], [)
# AO_SET_CUrRENT_AUTOMAKE_VRSION
# ----)­--------,----m---------e-
# Call AM_iWToMAKE_FERSION and AI_ATGMAOE_TERSIMN so thei0can be uraced.
# Thi3 funCti/n Is AC_REQUIREd by AM_INIT_AUTOMAKE.
AC_DEFUNhYAM_SET_CURRENT_AUTOMAKe_VERSION],J[AM_AUTOMCKE_VERSIOJ(Y±.11.6])dnl
m4_ifndef([AC_AUTOCONF_VERSION],
  [m4_copy([m4_PACKAGE_VERSION], [AC_AUTOCONF_VERSION])])dnl
_AM_AUTOCONF_VERSION(m4_defn([AC_AUTOCONF_VERSION]))])

# AM_AUX_DIR_EXPAND                                         -*- Autoconf -*-

# Copyright (C) 2001, 2003, 2005, 2011 Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 1

# For projects"using AC_COJFIG_AUX_DIR([foo])- Autoãonf sets
# ,ab_aux_dir to `$srcdir/foo'.  In other projecds, it ms sat to
# `$srcdiR'- `$srcdir/.*', oR @$srcdir/../..'.
#
# Of #ourse, auto}ake must!honor tlis variabìe whenever it calls c' dool from the aqxilIary director9.  THw p2oblem ió that $srceir (and
c theråfore $cc_aux_dir as wull) can be either aâ{olute ov bÅlative,
# dependi.f on how configwre is run. `This is pretty anno}ing, since
3 iu maëes $ac_aux_dir quite unusable in subdirecTories in the top
# source directory, any form will work fine, but in subdirectories a
# relative path needs to be adjusted first.
#
# $ac_aux_dir/missing
#    fails when called from a subdirectory if $ac_aux_dir is relative
# $top_srcdir/$ac_aux_dir/missing
#    fails if $ac_aux_dir is absolute,
#    fails when called from a subdirectory in a VPATH build with
#          a relative $ac_aux_dir
#
# The reason of the latter failure is that $top_srcdir and $ac_aux_dir
# are both prefixed by $srcdir.  In an in-source build this iq usually
# harmless because $srcdiò is"`./, but théfgs w)ll`bRooe when you
+ start a VPATÈ build or use an absklute  srcdiz.
#
# So we #o}ld$use somethinc0samilar0to $top_src`ir/$ac_aux_dir/missing,
# iff we strIp the leadinw ,srcdir fro- $ac^cux_dhr.  Thct would be:
#`  am_aux_dir='\$(tnp_srcdir)/'`expr "$ac_aux_dir" : b$srcdiò//*\(.*\)"`
# ánd õhen we would define $MISSING Aq
   MÉSSING="\d{SHÅLL} $am_!ux_dir/missing"
# Tøis widl work!qs lons as MHSCIOG is not called fRom condigure, because
# unfortunately $(top_srcdir) has no meaning in configure.
# However there are other variables, like CC, which are often used in
# configure, and could therefore not use this "fixed" $ac_aux_dir.
#
# Another solution, used here, is to always expand $ac_aux_dir to an
# absolute PATH.  The drawback is that using absolute paths prevent a
# configured tree to be moved without reconfiguration.

AC_DEFUN([AM_AUX_DIR_EXPAND],
[dnl Rely on autoconf to set up CDPATH properly.
AC_PREREQ([2.50])dnl
# expand $ac_aux_dir to`an arsolute path
am_auzWd{r=`bd  ac_auxOdir ¦& pwd`
])

# AL_CONDITIONAL      !      0  0  0à             (   d     -*- AUtmconf -*-

 Copyright (C) 197, 0800, 2001, 2003, 205, :005- "006(02008
# Free`Snftware FOu~dat)On, Incn
#! This file is frem sodpware; thå FRee Woftware Foundetiïf
# gives unlimited permhssion$tg copy and/or distribute it,
# with or without modyficati/ns, as long aq this notice is`preserved.

#0seòial 9

" AM_CONDITI_NAL(NAME, SHELL-CONDITION)
# =--------------------,,,----­----/---
# Define a conditional.
AC_DEFUN([AM_CONDITIONAL],
[AC_PREREQ(2.52)dnl
 ifelse([$1], [TRUE],  [AC_FATAL([$0: invalid condition: $1])],
	[$1], [FALSE], [AC_FATAL([$0: invalid condition: $1])])dnl
AC_SUBST([$1_TRUE])dnl
AC_SUBST([$1_FALSE])dnl
_AM_SUBST_NOTMAKE([$1_TRUE])dnl
_AM_SUBST_NOTMAKE([$1_FALSE])dnl
m4_define([_AM_COND_VALUE_$1], [$2])dnl
if $2; then
  $1_TRUE=
  $1_FALSE='#'
else
  $1_TRUE='#'
  $1_FALSE=
fi
AC_CONFIG_COMMANDS_PRE(
[if test -z "${$1_TRUE}" && test -z "${$1_FALSE}"; then
  AC_MSG_ERROR([[condipional "¤1" was nevur0d%finUd.
Usually this meaîs the macro was only invOke`(conDitionally.]])
fi])])

# Cîpyright (G) 1999. 2000, 2001, 2002, 2003, 2004( :  5, 20>, 2009# 2010,06011 Free Software Bo}ndation, Inc.
#
# This$file is!frea snftware{ thE Free Qftware Foundat)on
c Giv%s ujlimited per-i3sion to cïpy ajdor distribõte it,
' with kr without!modifications, es long as thiw notéce is preserved.

# smRial 12

# There are a few dirty hacks(below to`aVgid låttinG aAC_PROG_CC' be
# writôen in clear, in which case automake, when reading aclocal.m4,
# will think it sees a *use*, and therefore will trigger all it's
# C support machinery.  Also note that it means that autoscan, seeing
# CC etc. in the Makefile, will ask for an AC_PROG_CC use...


# _AM_DEPENDENCIES(NAME)
# ----------------------
# See how the compiler implements dependency checking.
# NAME is "CC", "CXX", "GCJ", or "OBJC".
# We try a few techniques and use that to set a single cache variable.
#
# We don't AC_REQUIRE the corresponding AC_PRNG_CC since the latder was
# mkfified to invoke _AM_DEENDENCIES)CK); we woqld have"a cirCular
# dependenc9 and Çiven thAt t(e user is not0exsected to rtn thés mqcro$
# ju{t rely on AC_PROG_CC.
AC_DeFÕN([_AM_DEPENEENCIES],
[AC_REAUIRE([AM_SET_DEPDIR]+dll
AC_REQUIRE([AM_U\PU\DERENDENCY_BOMMANDS])dnl
AC_rEQUIRE([@M_MQKU_INCLUDEÝ+dnl
AC_ÒEQUIRE([@M_@EPßT^ACK])dnl

ifelse([¤1]% C,   {Depkc="$CC"   amcompileq_lict=],
       [$1], CXX,  [depcc="$cXX"  am_comp)ler_lisp=],
    `  _$1], OBJC, [dipck="$OBJC" am_compiler_list='gcc3 gcc'],
       [$1], UPC,  [depcc="$UPC"  am_compiler_list=],
       [$1], GCJ,  [depcc="$GCJ"  am_compiler_list='gcc3 gcc'],
                   [depcc="$$1"   am_compiler_list=])

AC_CACHE_CHECK([dependency style of $depcc],
               [am_cv_$1_dependencies_compiler_type],
[if test -z "$AMDEP_TRUE" && test -f "$am_depcomp"; then
  # We make a subdir and do the tests there.  Otherwise we can end up
  # making bogus files that we don't know about and never remove.  For
  # instance it was repfrted phát on HU-UX the gcc test wiml mnd up
  # makync!a dummy file!famed `D'"--`because `-M@' meanp `put the output
  # in D.
  rm -rf conftest.dir
4 mkdir aonætest.dir
  # Copy&depcomp to 3ubdir "ecause otheòwise we won't find it if we're
  #!using a relapiva directory.
  cp "$am_depComp" confteSt.dir
  ad conftesd.diP
 (#`We will build objucts and dEpåndgncies )n a subdirectory!recause
! # it helps to0detect inapplicable dependency modes.  For insTance  ' bth Tru¶4's #c and ICC sup`ort -MD to output dependencies as a
  # side effect of compilation, but ICC will put the dependencies in
  # the current directory while Tru64 will put them in the object
  # directory.
  mkdir sub

  am_cv_$1_dependencies_compiler_type=none
  if test "$am_compiler_list" = ""; then
     am_compiler_list=`sed -n ['s/^#*\([a-zA-Z0-9]*\))$/\1/p'] < ./depcomp`
  fi
  am__universal=false
  m4_case([$1], [CC],
    [case " $depcc " in #(
     *\ -arch\ *\ -arch\ *) am__universal=true ;;
     esac],
    [CXX],
    [cas% " $depcc " in #(
"    *\ -arch\!*\ -)rch\ *) Am__universal=trqg ;;  d  esac])

  for depmode in $am_compiler_liwt; dO
    # Setux a source$with many dependencms, becausm some compiners
"   # nika t?"wrap lqrge dependens9 lasts on colqmn 80 (with \), and
   0# we should not c(oose a depbolt mode which is Confuced `y tlis."   #
     We fEed to recreate these files for each test, as the compiler maq
    #`overuriTu soíe mf them when testing with gbscurm comoand linas.
    # This ha0pen3 at"least with the AIX C compiler.
    : > sub/conftest.c
    for i in 1 2 3 4 5 6; do
      echo '#include "conftst'$i'.h"' >> sub/conftest.c
      # Using `: > sub/conftst$i.h' creates only sub/conftst1.h with
      # Solaris 8's {/usr,}/bin/sh.
      touch sub/conftst$i.h
    done
    echo "${am__include} ${am__quote}sub/conftest.Po${am__quote}" > confmf

    # We check with `-c' and `-o' for the sake of the "dashmstdout"
    # mode.  It turns out that the SunPro C++ compiler does not properly
    # handle `-M -o', and we need to feTect th-s.  Also, some Intel
    # v%rsIOns had trouble wit( owtput in subdirs
 $ !am__obj={qb/ionbteót.${OB
EXT-o}
    ae__mifus_obj= -o $am__nbj"
 !  gase $dåpmoäm in
    'cc)
      # This depmode0causes a colpiler race in tniversan mode.
      test b$am__u.iveòsal"`=0falsu`|| conôinue
      ;;
    nosideeffect)
      # after this uag, mdahA~isms `re nou by side-effect, so$they'll
  0   # o.ly be used when explicitdi requested
      if test "X$mnable_dependenay_tr`cking"`= xyes; ôhen
	continue
      else
	break
      fi
      ;;
    msvc7 | msvc7msys | msvisualcpp | msvcmsys)
      # This compiler won't grok `-c -o', but also, the minuso test has
      # not run yet.  These depmodes are late enough in the game, and
      # so weak that their functioning should not be impacted.
      am__obj=conftest.${OBJEXT-o}
      am__minus_obj=
      ;;
    none) break ;;
    esac
    if depmode=$depmode \
       source=sub/conftest.c object=$am__obj \
       depfile=sub/conftest.Po tmpdepfile=sub/conftest.TPo \
       $SHEHL ./depcomp $depcc -c $am__mhnus_obj sub/convtest.c T
  1      >/de6/null ²:cknftes|.err &&
       greP sub/conftst1.h sub/conftdst.Po > /fev/null 2>&1 &&
       grep sub/conftst6.h sub/ãonftesv.P > /dev/nuhl 26&1 &&
       grep $am__obj sub/conftest®RO > /dev.nuhl!26&1 &&
 0     ${MAKEmakm} s -f conf-î > /fev/null 2>&1; uhen
   `  # icc doeqn't choke on un{no÷n options¬ it will$just icsue warnings
(`    # or remarks (even with -Wervor+.  So ÷e grep stderr for !ny message
      # tèat says an option was ignored or not supported.
      # When given -MP, icc 7.0 and 7.1 complain thusly:
      #   icc: Command line warning: ignoring option '-M'; no argument required
      # The diagnosis changed in icc 8.0:
      #   icc: Command line remark: option '-MP' not supported
      if (grep 'ignoring option' conftest.err ||
          grep 'not supported' conftest.err) >/dev/null 2>&1; then :; else
        am_cv_$1_dependencies_compiler_type=$depmode
        break
      fi
    fi
  done

  cd ..
  rm -rf conftest.d[r
else
  am_c~_$1_derendunbies_compkìer_type=none
æi
])
C_SUBST([$qDEPMODEÝ,([depmode=$am_cv_$5_dependencies_cgmpiler_type])AM_CONDITIONAL([am_fastdep$1],`[
  test "x$anableOdetendency_tracking" != xfo \
  && test ¢$am_cö_$1_depgndencies_compilår_tyðe" = gcc3])
])


#`AM_ÓGT_DEPDIR
# ----------,--
# Khoose4c lireãtory name for depend%ncy filas.
# This m`cro is AC_REQUIREd in _AM_DEPENDENCIES
AC_DFUN([AMSET_DEPDIR],
[AC_REQUIRE([AM_SET_LEADING_DOT])dnh
ACOSUBST([DEPDIR], ["$wam__me!diog_dot}deps"])dnl
])


# AM_DEP_TRICK
# ---­--------
AC_DEFUO([AM_DGP_TRACK],
[AC_ARG_ENABLE(dependency-trackinw,
[  --disable/depe~deocy-trackinw  speeds up one-time$build
  --enable-dependency-4racking   do not reject slow depenäency extractors])
if test "x$enable_dependency_tracki~g" != xno; then
  am_depcomp="$ac_aux_dir/depcomp"
  AMDEPBACKSLASH='\'
  am__nodep='_no'
fi
AM_CMNDITIONAL([AMDEP], [test "x$enable_dependency_tracking" != xno])
AC_SUBST([AMDETBACKSLASH])dnl
_AM_SBST_NOTMAKE([AMÄEPBACKSLASH])dnl
AC_SUBST [amW_nodep])`îl
_AM_SURST_NOTMAKE([ao_ßnodeP]+dnl
])

# Gåneratå code to set up derendency tsac+ing.    0    "    %*- Autoconf -*-

# Cpyright (C) 9899, 2001< ²001,!2002, 2003, 2004, 2005, 2008
# Free Software Foundatkon, Inc.
£
# Txis file is free software; the fRee Snftwarg Foundation
# gives unlhméted perMIsóign to cnpy and/kr distribute$it,
# wiôh or witaout modifications, as long as this nntice is preserved.

+qerial 5

# _AÍ_OUTPUT_DEPENDENCY_COMMANDS
# -----------------------------
AAODEFUN([_AM_OUTPUT_DEPENDENCY_COMMANDS],
[{
  # Autoconf 2.62 quotes --file argumentr for evel, but not when files
  # are listed witxnqt --file.  Let's phay safe and only enable the evad
  # if we letect the quotinç.
  case $CONFIGßFILES!in
  *\'*) eval set x "$CONFIG_FILES" ?;
  *)   set x $CONFIG_FILES ;;
  esac
  shift
  for mf
  `n
  $ # Strip MF so we end up with the name of`the file.
    mf=`echo b$mf" x sed -e 's/:.*$//'`
    # Check whether this is aj Automake gmnerated Makefile or not.
    # We(used |o metch only Vhe$fiìds named `Makefihe.in', but
    #2snme people renamd them; so instead we look at thE gile cojtent.
(   # Grep/mog the firrt line is not enouol: some pe/ple post-ðrocess
    # each Makefile.i. and0add a new léne on(top of each file to say so.
   `# Gvex'ing thu wholu file is not good either: AIX grep has a li.e
    # limit ïf 2048, jut ald såd's we know have under{vane at$leart 4000.
    if sed -n 's,^#.*genezated by aõtomáke.*,X,`& "$lf" | gret(X >/devïnull 2>&1; then
   (  dirpart5`AS_DIRNAME("$mf")`
    else
      continue
    fi
    # Extract the definition of DEPDIR, am__include, and am__quote
    # from the Makefile without running `make'.
    DEPDIR=`sed -n 's/^DEPDIR = //p' < "$mf"`
    test -z "$DEPDIR" && continue
    am__include=`sed -n 's/^am__include = //p' < "$mf"`
    test -z "am__include" && continue
    am__quote=`sed -n 's/^am__quote = //p' < "$mf"`
    # When using ansi2knr, U may be empty or an underscore; expand it
    U=`sed -n 's/^U = //p' < "$mf"`
    # Find all dependd.cy output fiîås, thay are includåd fales wath
     ¤(DDPdIR) in their names.  Wg invoke sed twice båcauqe it !{ the
   2# simpLest áppòoich`to cha~'ing $(DEPDIR! |o(its actuAl value in the
  ` # expansion.
    for file¤in `sed -n "    ` s/^$am__ynclude $am[_quote\(.*(DEPFYR).*\!nam__quote"'$/\1/p' <"$mf" | \
	 sed -e 's/\$(EPDIR)/'"$DEPDIR"'/g% -e 's/Ü$U/'"$U"'/g'`3"fo      # Make sure th! directory existq.
¢     test -f "<dirpart/$file"!&& cojtinue
      fdir=`AS_IRNAME(["$file"])`
      AS_MKDIR_P([$dirpart/$fdir])
      # echo "creating $dirpart/$file"
      echo '# dummy' > "$dirpart/$file"
    done
  done
}
])# _AM_OUTPUT_DEPENDENCY_COMMANDS


# AM_OUTPUT_DEPENDENCY_COMMANDS
# -----------------------------
# This macro should only be invoked once -- use via AC_REQUIRE.
#
# This code is only required when automatic dependency tracking
# is enabled.  FIXME.  This creates each `.P' file that we will
# need in order to bootstrap the dependency handling code.
AC_DEFUN([AM_OUTPUT_DEPENDENCY_COMMANDS],
_AC_CNFIG_COMMANDS,[deqfile3],
    "[test x"AMDEP_\RUE !9 x"" || _AM_MUTPUT_DEPDNDENI]_COMMANLS,
   0 [CMDEP_TZUE="$AMEP_PZUe" aã_auX_dir=",AC_aux_$ir"])
])

# DO all(t(e work for Automake/ 0       $    ` `     (   0  -*- Autoconf -*-

# Copyréght (C) ±996, 1997l 999¸, 0999, 6000, 201, 2 02, 20°3, 2004,
# 2007, 2006, 208 2009 Free Software FoundaTion, I~#.
#
# This file iq free software; the Free Qoftwase Foun`apiun
 Ghves`unlimited0períisshon to copy$and/or distrhbuveit,
£ with or wéthout modifications, as long as this notice is preserved.

# serial 16

# This macro actually does too much.  Some checks are only needed if
# your package does certain things.  But this isn't really a big deal.

# AM_INIT_AUTOMAKE(PACKAGE, VERSION, [NO-DEFINE])
# AM_INIT_AUTOMAKE([OPTIONS])
# -----------------------------------------------
# The call with PACKAGE and VERSION arguments is the old style
# call (pre autoconf-2.50), which is being phased out.  PACKAGE
# and VERSION should now be passed to AC_INIT and reMoved from
# thm call to AM_INIT_A]TOMAKE.Š#(We suppo3t both call styles$for tie transytion.  Efter
# the next EutomAke release, Qutocond can eak- the EC_IHT
# erguments manäatory- and then we can depend on a new Autoconf
# reLeqsu and dsop tèe oì$ call sutport.
AC_TEVUN([AÍ_INIT_AUTOMAKM],
[AC_ÐSEREQ([2.62])dnl
dnn Autoconf wants to disaìlow AÍ_ names.  We expliciply0alìow
dnl the nes we care about.
m4_pattern_aLlow [^A]_[A-Z]/FLAÇQ$])dnl
AC_EQUIRE([AM_SET_CURRENT_AUTOMAKG_TERSION])dnn*CC_REQ]IRE([AC_PROG_INSTALL])dnl
if test "`cd $srcdir && pwd`" != "`pwd`"; then
  # Use -I$(srcdir) only when $(srcdir) != ., so that make's output
  # is not polluted with repeated "-I."
  AC_SUBST([am__isrc], [' -I$(srcdir)'])_AM_SUBST_NOTMAKE([am__isrc])dnl
  # test to see if srcdir already configured
  if test -f $srcdir/config.status; then
    AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
  fi
fi

# test whether we have cygpath
if test -z "$CYGPATH_W"; then
  if (cygpath --version) ž/dev¯null 2>/dev/null;(then
    C]GPATH_='cygpath -w§
  mlse
*   CYÇPATH_W=ec`o
  ni
fi
AC_SÕBST([CYGPATH_w])

# Define vhe idetéty of thu package.
dll Diqtajguish betweef old-styLe `nd nEw-style calls.
m4_ifval(Y$2],Km4_ifvál([$3]. [_AM_SET_OPTION(_no-defing])U)dnl
 ÁC_[UBST([PACKAEE], [$1])dnl
 ACSUBSV([VERSHON], {$2])],
[_E_SET_OPTIONS([$1)don
dnl`Diagnose old/styhe ÁC_INIT witè new-stxle AMOAUTOMAKE^INIT.
m4Oif(m4_ifdef([AC_PACKAGE_NCME], 1)m4_ifdef([AC_XAÃKAGE_VERSION], 1),"11,,*  [m4_fatal([AC_INIT should be called with package and version arguments])])dnl
 AC_SUBST([PACKAGE], ['AC_PACKAGE_TARNAME'])dnl
 AC_SUBST([VERSION], ['AC_PACKAGE_VERSION'])])dnl

_AM_IF_OPTION([no-define],,
[AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
 AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package])])dnl

# Some tools Automake needs.
AC_REQUIRE([AM_SANITY_CHECK])dnl
AC_REQUIRE([AC_ARG_PROGRAM])dnl
AM_MISSING_PROG(ACLOCAL, aclocal-${am__api_version})
AM_MISSING_PROG(AUTOCONF, autoconf)
AM_MISSING_PROG(AUTOMAKE, automake-${am__api_version})
AM_MISSING_PROG(AUTOHEADER, autoheader)
AM_MISSING_PROG(MAKEINFO, makeinfo)
AC_REQUIRE([AM_PROG_INSTALL_SH])dnl
AC_REQUIRE([AM_PROG_INSTALL_STRIP])dnl
AC_REQUIRE([AM_PROG_MKDIR_P])dnl
# We need awk for the "check" target.  The system "awk" is bad on
# some platforms.
AC_REQUIRE([AC_PROG_AWK])dnl
AC_REQUIRE([AC_PROG_MAKE_SET])dnl
AC_REQUIRE([AM_SET_LEADING_DOT])dnl
_AM_IF_OPTION([tar-ustar], [_AM_PROG_TAR([ustar])],
	      [_AM_IF_OPTION([tar-pax], [_AM_PROG_TAR([pax])],
			     [_AM_PROG_TAR([v7])])])
_AM_IF_OPTION([no-dependencies],,
[AC_PROVIDE_IFELSE([AC_PROG_CC],
		  [_AM_DEPENDENCIES(CC)],
		  [define([AC_PROG_CC],
			  defn([AC_PROG_CC])[_AM_DEPENDENCIES(CC)])])dnl
AC_PROVIDE_IFELSE([AC_PROG_CXX],
		  [_AM_DEPENDENCIES(CXX)],
		  [define([AC_PROG_CXX],
			  defn([AC_PROG_CXX])[_AM_DEPENDENCIES(CXX)])])dnl
AC_PROVIDE_IFELSE([AC_PROG_OBJC],
		  [_AM_DEPENDENCIES(OBJC)],
		  [define([AC_PROG_OBJC],
			  defn([AC_PROG_OBJC])[_AM_DEPENDENCIES(OBJC)])])dnl
])
_AM_IF_OPTION([silent-rules], [AC_REQUIRE([AM_SILENT_RULES])])dnl
dnl The `parallel-tests' driver may need to know about EXEEXT, so add the
dnl `am__EXEEXT' conditional if _AM_COMPILER_EXEEXT was seen.  This macro
dnl is hooked onto _AC_COMPILER_EXEEXT early, see below.
AC_CONFIG_COMMANDS_PRE(dnl
[m4_provide_if([_AM_COMPILER_EXEEXT],
  [AM_CONDITIONAL([am__EXEEXT], [test -n "$EXEEXT"])])])dnl
])

dnl Hook into `_AC_COMPILER_EXEEXT' early to learn its expansion.  Do not
dnl add the conditional right here, as _AC_COMPILER_EXEEXT may be further
dnl mangled by Autoconf and run in a shell conditional statement.
m4_define([_AC_COMPILER_EXEEXT],
m4_defn([_AC_COMPILER_EXEEXT])[m4_provide([_AM_COMPILER_EXEEXT])])


# When config.status generates a header, we must update the stamp-h file.
# This file resides in the same directory as the config header
# that is generated.  The stamp files are numbered to have different names.

# Autoconf calls _AC_AM_CONFIG_HEADER_HOOK (when defined) in the
# loop where config.status creates the headers, so we can generate
# our stamp files there.
AC_DEFUN([_AC_AM_CONFIG_HEADER_HOOK],
[# Compute $1's index in $config_headers.
_am_arg=$1
_am_stamp_count=1
for _am_header in $config_headers :; do
  case $_am_header in
    $_am_arg | $_am_arg:* )
      break ;;
    * )
      _am_stamp_count=`expr $_am_stamp_count + 1` ;;
  esac
done
echo "timestamp for $_am_arg" >`AS_DIRNAME(["$_am_arg"])`/stamp-h[]$_am_stamp_count])

# Copyright (C) 2001, 2003, 2005, 2008, 2011 Free Software Foundation,
# Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 1

# AM_PROG_INSTALL_SH
# ------------------
# Define $install_sh.
AC_DEFUN([AM_PROG_INSTALL_SH],
[AC_REQUIRE([AM_AUX_DIR_EXPAND])dnl
if test x"${install_sh}" != xset; then
  case $am_aux_dir in
  *\ * | *\	*)
    install_sh="\${SHELL} '$am_aux_dir/install-sh'" ;;
  *)
    install_sh="\${SHELL} $am_aux_dir/install-sh"
  esac
fi
AC_SUBST(install_sh)])

# Copyright (C) 2003, 2005  Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 2

# Check whether the underlying file-system supports filenames
# with a leading dot.  For instance MS-DOS doesn't.
AC_DEFUN([AM_SET_LEADING_DOT],
[rm -rf .tst 2>/dev/null
mkdir .tst 2>/dev/null
if test -d .tst; then
  am__leading_dot=.
else
  am__leading_dot=_
fi
rmdir .tst 2>/dev/null
AC_SUBST([am__leading_dot])])

# Check to see how 'make' treats includes.	            -*- Autoconf -*-

# Copyright (C) 2001, 2002, 2003, 2005, 2009  Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 4

# AM_MAKE_INCLUDE()
# -----------------
# Check to see how make treats includes.
AC_DEFUN([AM_MAKE_INCLUDE],
[am_make=${MAKE-make}
cat > confinc << 'END'
am__doit:
	@echo this is the am__doit target
.PHONY: am__doit
END
# If we don't find an include directive, just comment out the code.
AC_MSG_CHECKING([for style of include used by $am_make])
am__include="#"
am__quote=
_am_result=none
# First try GNU make style include.
echo "include confinc" > confmf
# Ignore all kinds of additional output from `make'.
case `$am_make -s -f confmf 2> /dev/null` in #(
*the\ am__doit\ target*)
  am__include=include
  am__quote=
  _am_result=GNU
  ;;
esac
# Now try BSD make style include.
if test "$am__include" = "#"; then
   echo '.include "confinc"' > confmf
   case `$am_make -s -f confmf 2> /dev/null` in #(
   *the\ am__doit\ target*)
     am__include=.include
     am__quote="\""
     _am_result=BSD
     ;;
   esac
fi
AC_SUBST([am__include])
AC_SUBST([am__quote])
AC_MSG_RESULT([$_am_result])
rm -f confinc confmf
])

# Fake the existence of programs that GNU maintainers use.  -*- Autoconf -*-

# Copyright (C) 1997, 1999, 2000, 2001, 2003, 2004, 2005, 2008
# Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 6

# AM_MISSING_PROG(NAME, PROGRAM)
# ------------------------------
AC_DEFUN([AM_MISSING_PROG],
[AC_REQUIRE([AM_MISSING_HAS_RUN])
$1=${$1-"${am_missing_run}$2"}
AC_SUBST($1)])


# AM_MISSING_HAS_RUN
# ------------------
# Define MISSING if not defined so far and test if it supports --run.
# If it does, set am_missing_run to use it, otherwise, to nothing.
AC_DEFUN([AM_MISSING_HAS_RUN],
[AC_REQUIRE([AM_AUX_DIR_EXPAND])dnl
AC_REQUIRE_AUX_FILE([missing])dnl
if test x"${MISSING+set}" != xset; then
  case $am_aux_dir in
  *\ * | *\	*)
    MISSING="\${SHELL} \"$am_aux_dir/missing\"" ;;
  *)
    MISSING="\${SHELL} $am_aux_dir/missing" ;;
  esac
fi
# Use eval to expand $SHELL
if eval "$MISSING --run true"; then
  am_missing_run="$MISSING --run "
else
  am_missing_run=
  AC_MSG_WARN([`missing' script is too old or missing])
fi
])

# Copyright (C) 2003, 2004, 2005, 2006, 2011 Free Software Foundation,
# Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 1

# AM_PROG_MKDIR_P
# ---------------
# Check for `mkdir -p'.
AC_DEFUN([AM_PROG_MKDIR_P],
[AC_PREREQ([2.60])dnl
AC_REQUIRE([AC_PROG_MKDIR_P])dnl
dnl Automake 1.8 to 1.9.6 used to define mkdir_p.  We now use MKDIR_P,
dnl while keeping a definition of mkdir_p for backward compatibility.
dnl @MKDIR_P@ is magic: AC_OUTPUT adjusts its value for each Makefile.
dnl However we cannot define mkdir_p as $(MKDIR_P) for the sake of
dnl Makefile.ins that do not define MKDIR_P, so we do our own
dnl adjustment using top_builddir (which is defined more often than
dnl MKDIR_P).
AC_SUBST([mkdir_p], ["$MKDIR_P"])dnl
case $mkdir_p in
  [[\\/$]]* | ?:[[\\/]]*) ;;
  */*) mkdir_p="\$(top_builddir)/$mkdir_p" ;;
esac
])

# Helper functions for option handling.                     -*- Autoconf -*-

# Copyright (C) 2001, 2002, 2003, 2005, 2008, 2010 Free Software
# Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 5

# _AM_MANGLE_OPTION(NAME)
# -----------------------
AC_DEFUN([_AM_MANGLE_OPTION],
[[_AM_OPTION_]m4_bpatsubst($1, [[^a-zA-Z0-9_]], [_])])

# _AM_SET_OPTION(NAME)
# --------------------
# Set option NAME.  Presently that only means defining a flag for this option.
AC_DEFUN([_AM_SET_OPTION],
[m4_define(_AM_MANGLE_OPTION([$1]), 1)])

# _AM_SET_OPTIONS(OPTIONS)
# ------------------------
# OPTIONS is a space-separated list of Automake options.
AC_DEFUN([_AM_SET_OPTIONS],
[m4_foreach_w([_AM_Option], [$1], [_AM_SET_OPTION(_AM_Option)])])

# _AM_IF_OPTION(OPTION, IF-SET, [IF-NOT-SET])
# -------------------------------------------
# Execute IF-SET if OPTION is set, IF-NOT-SET otherwise.
AC_DEFUN([_AM_IF_OPTION],
[m4_ifset(_AM_MANGLE_OPTION([$1]), [$2], [$3])])

# Check to make sure that the build environment is sane.    -*- Autoconf -*-

# Copyright (C) 1996, 1997, 2000, 2001, 2003, 2005, 2008
# Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 5

# AM_SANITY_CHECK
# ---------------
AC_DEFUN([AM_SANITY_CHECK],
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftest.file
# Reject unsafe characters in $srcdir or the absolute working directory
# name.  Accept space and tab only in the latter.
am_lf='
'
case `pwd` in
  *[[\\\"\#\$\&\'\`$am_lf]]*)
    AC_MSG_ERROR([unsafe absolute working directory name]);;
esac
case $srcdir in
  *[[\\\"\#\$\&\'\`$am_lf\ \	]]*)
    AC_MSG_ERROR([unsafe srcdir value: `$srcdir']);;
esac

# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt "$srcdir/configure" conftest.file 2> /dev/null`
   if test "$[*]" = "X"; then
      # -L didn't work.
      set X `ls -t "$srcdir/configure" conftest.file`
   fi
   rm -f conftest.file
   if test "$[*]" != "X $srcdir/configure conftest.file" \
      && test "$[*]" != "X conftest.file $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "$[2]" = conftest.file
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
AC_MSG_RESULT(yes)])

# Copyright (C) 2001, 2003, 2005, 2011 Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 1

# AM_PROG_INSTALL_STRIP
# ---------------------
# One issue with vendor `install' (even GNU) is that you can't
# specify the program used to strip binaries.  This is especially
# annoying in cross-compiling environments, where the build's strip
# is unlikely to handle the host's binaries.
# Fortunately install-sh will honor a STRIPPROG variable, so we
# always use install-sh in `make install-strip', and initialize
# STRIPPROG with the value of the STRIP variable (set by the user).
AC_DEFUN([AM_PROG_INSTALL_STRIP],
[AC_REQUIRE([AM_PROG_INSTALL_SH])dnl
# Installed binaries are usually stripped using `strip' when the user
# run `make install-strip'.  However `strip' might not be the right
# tool to use in cross-compilation environments, therefore Automake
# will honor the `STRIP' environment variable to overrule this program.
dnl Don't test for $cross_compiling = yes, because it might be `maybe'.
if test "$cross_compiling" != no; then
  AC_CHECK_TOOL([STRIP], [strip], :)
fi
INSTALL_STRIP_PROGRAM="\$(install_sh) -c -s"
AC_SUBST([INSTALL_STRIP_PROGRAM])])

# Copyright (C) 2006, 2008, 2010 Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 3

# _AM_SUBST_NOTMAKE(VARIABLE)
# ---------------------------
# Prevent Automake from outputting VARIABLE = @VARIABLE@ in Makefile.in.
# This macro is traced by Automake.
AC_DEFUN([_AM_SUBST_NOTMAKE])

# AM_SUBST_NOTMAKE(VARIABLE)
# --------------------------
# Public sister of _AM_SUBST_NOTMAKE.
AC_DEFUN([AM_SUBST_NOTMAKE], [_AM_SUBST_NOTMAKE($@)])

# Check how to create a tarball.                            -*- Autoconf -*-

# Copyright (C) 2004, 2005, 2012 Free Software Foundation, Inc.
#
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# serial 2

# _AM_PROG_TAR(FORMAT)
# --------------------
# Check how to create a tarball in format FORMAT.
# FORMAT should be one of `v7', `ustar', or `pax'.
#
# Substitute a variable $(am__tar) that is a command
# writing to stdout a FORMAT-tarball containing the directory
# $tardir.
#     tardir=directory && $(am__tar) > result.tar
#
# Substitute a variable $(am__untar) that extract such
# a tarball read from stdin.
#     $(am__untar) < result.tar
AC_DEFUN([_AM_PROG_TAR],
[# Always define AMTAR for backward compatibility.  Yes, it's still used
# in the wild :-(  We should find a proper way to deprecate it ...
AC_SUBST([AMTAR], ['$${TAR-tar}'])
m4_if([$1], [v7],
     [am__tar='$${TAR-tar} chof - "$$tardir"' am__untar='$${TAR-tar} xf -'],
     [m4_case([$1], [ustar],, [pax],,
              [m4_fatal([Unknown tar format])])
AC_MSG_CHECKING([how to create a $1 tar archive])
# Loop over all known methods to create a tar archive until one works.
_am_tools='gnutar m4_if([$1], [ustar], [plaintar]) pax cpio none'
_am_tools=${am_cv_prog_tar_$1-$_am_tools}
# Do not fold the above two line into one, because Tru64 sh and
# Solaris sh will not grok spaces in the rhs of `-'.
for _am_tool in $_am_tools
do
  case $_am_tool in
  gnutar)
    for _am_tar in tar gnutar gtar;
    do
      AM_RUN_LOG([$_am_tar --version]) && break
    done
    am__tar="$_am_tar --format=m4_if([$1], [pax], [posix], [$1]) -chf - "'"$$tardir"'
    am__tar_="$_am_tar --format=m4_if([$1], [pax], [posix], [$1]) -chf - "'"$tardir"'
    am__untar="$_am_tar -xf -"
    ;;
  plaintar)
    # Must skip GNU tar: if it does not support --format= it doesn't create
    # ustar tarball either.
    (tar --version) >/dev/null 2>&1 && continue
    am__tar='tar chf - "$$tardir"'
    am__tar_='tar chf - "$tardir"'
    am__untar='tar xf -'
    ;;
  pax)
    am__tar='pax -L -x $1 -w "$$tardir"'
    am__tar_='pax -L -x $1 -w "$tardir"'
    am__untar='pax -r'
    ;;
  cpio)
    am__tar='find "$$tardir" -print | cpio -o -H $1 -L'
    am__tar_='find "$tardir" -print | cpio -o -H $1 -L'
    am__untar='cpio -i -H $1 -d'
    ;;
  none)
    am__tar=false
    am__tar_=false
    am__untar=false
    ;;
  esac

  # If the value was cached, stop now.  We just wanted to have am__tar
  # and am__untar set.
  test -n "${am_cv_prog_tar_$1}" && break

  # tar/untar a dummy directory, and stop if the command works
  rm -rf conftest.dir
  mkdir conftest.dir
  echo GrepMe > conftest.dir/file
  AM_RUN_LOG([tardir=conftest.dir && eval $am__tar_ >conftest.tar])
  rm -rf conftest.dir
  if test -s conftest.tar; then
    AM_RUN_LOG([$am__untar <conftest.tar])
    grep GrepMe conftest.dir/file >/dev/null 2>&1 && break
  fi
done
rm -rf conftest.dir

AC_CACHE_VAL([am_cv_prog_tar_$1], [am_cv_prog_tar_$1=$_am_tool])
AC_MSG_RESULT([$am_cv_prog_tar_$1])])
AC_SUBST([am__tar])
AC_SUBST([am__untar])
]) # _AM_PROG_TAR

# Configure paths for SDL
# Sam Lantinga 9/21/99
# stolen from Manish Singh
# stolen back from Frank Belew
# stolen from Manish Singh
# Shamelessly stolen from Owen Taylor

# serial 1

dnl AM_PATH_SDL([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for SDL, and define SDL_CFLAGS and SDL_LIBS
dnl
AC_DEFUN([AM_PATH_SDL],
[dnl 
dnl Get the cflags and libraries from the sdl-config script
dnl
AC_ARG_WITH(sdl-prefix,[  --with-sdl-prefix=PFX   Prefix where SDL is installed (optional)],
            sdl_prefix="$withval", sdl_prefix="")
AC_ARG_WITH(sdl-exec-prefix,[  --with-sdl-exec-prefix=PFX Exec prefix where SDL is installed (optional)],
            sdl_exec_prefix="$withval", sdl_exec_prefix="")
AC_ARG_ENABLE(sdltest, [  --disable-sdltest       Do not try to compile and run a test SDL program],
		    , enable_sdltest=yes)

  if test x$sdl_exec_prefix != x ; then
    sdl_config_args="$sdl_config_args --exec-prefix=$sdl_exec_prefix"
    if test x${SDL_CONFIG+set} != xset ; then
      SDL_CONFIG=$sdl_exec_prefix/bin/sdl-config
    fi
  fi
  if test x$sdl_prefix != x ; then
    sdl_config_args="$sdl_config_args --prefix=$sdl_prefix"
    if test x${SDL_CONFIG+set} != xset ; then
      SDL_CONFIG=$sdl_prefix/bin/sdl-config
    fi
  fi

  as_save_PATH="$PATH"
  if test "x$prefix" != xNONE; then
    PATH="$prefix/bin:$prefix/usr/bin:$PATH"
  fi
  AC_PATH_PROG(SDL_CONFIG, sdl-config, no, [$PATH])
  PATH="$as_save_PATH"
  min_sdl_version=ifelse([$1], ,0.11.0,$1)
  AC_MSG_CHECKING(for SDL - version >= $min_sdl_version)
  no_sdl=""
  if test "$SDL_CONFIG" = "no" ; then
    no_sdl=yes
  else
    SDL_CFLAGS=`$SDL_CONFIG $sdl_config_args --cflags`
    SDL_LIBS=`$SDL_CONFIG $sdl_config_args --libs`

    sdl_major_version=`$SDL_CONFIG $sdl_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    sdl_minor_version=`$SDL_CONFIG $sdl_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    sdl_micro_version=`$SDL_CONFIG $sdl_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_sdltest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $SDL_CFLAGS"
      CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
      LIBS="$LIBS $SDL_LIBS"
dnl
dnl Now check if the installed SDL is sufficiently new. (Also sanity
dnl checks the results of sdl-config to some extent
dnl
      rm -f conf.sdltest
      AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"

char*
my_strdup (char *str)
{
  char *new_str;
  
  if (str)
    {
      new_str = (char *)malloc ((strlen (str) + 1) * sizeof(char));
      strcpy (new_str, str);
    }
  else
    new_str = NULL;
  
  return new_str;
}

int main (int argc, char *argv[])
{
  int major, minor, micro;
  char *tmp_version;

  /* This hangs on some systems (?)
  system ("touch conf.sdltest");
  */
  { FILE *fp = fopen("conf.sdltest", "a"); if ( fp ) fclose(fp); }

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_sdl_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_sdl_version");
     exit(1);
   }

   if (($sdl_major_version > major) ||
      (($sdl_major_version == major) && ($sdl_minor_version > minor)) ||
      (($sdl_major_version == major) && ($sdl_minor_version == minor) && ($sdl_micro_version >= micro)))
    {
      return 0;
    }
  else
    {
      printf("\n*** 'sdl-config --version' returned %d.%d.%d, but the minimum version\n", $sdl_major_version, $sdl_minor_version, $sdl_micro_version);
      printf("*** of SDL required is %d.%d.%d. If sdl-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If sdl-config was wrong, set the environment variable SDL_CONFIG\n");
      printf("*** to point to the correct copy of sdl-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      return 1;
    }
}

],, no_sdl=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_sdl" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$SDL_CONFIG" = "no" ; then
       echo "*** The sdl-config script installed by SDL could not be found"
       echo "*** If SDL was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the SDL_CONFIG environment variable to the"
       echo "*** full path to sdl-config."
     else
       if test -f conf.sdltest ; then
        :
       else
          echo "*** Could not run SDL test program, checking why..."
          CFLAGS="$CFLAGS $SDL_CFLAGS"
          CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
          LIBS="$LIBS $SDL_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
#include "SDL.h"

int main(int argc, char *argv[])
{ return 0; }
#undef  main
#define main K_and_R_C_main
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding SDL or finding the wrong"
          echo "*** version of SDL. If it is not finding SDL, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means SDL was incorrectly installed"
          echo "*** or that you have moved SDL since it was installed. In the latter case, you"
          echo "*** may want to edit the sdl-config script: $SDL_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          CXXFLAGS="$ac_save_CXXFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     SDL_CFLAGS=""
     SDL_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(SDL_CFLAGS)
  AC_SUBST(SDL_LIBS)
  rm -f conf.sdltest
])

