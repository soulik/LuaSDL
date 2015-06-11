find_path(PULSE_INCLUDE_DIR NAMES pulse/pulseaudio.h
          DOC "The Pulse Audio include directory"
)

find_library(PULSE_LIBRARY NAMES pulse-simple
          DOC "The Pulse Audio library"
)
