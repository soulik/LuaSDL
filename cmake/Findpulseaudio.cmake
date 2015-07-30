find_path(pulseaudio_INCLUDE_DIR NAMES pulse/pulseaudio.h
          DOC "The Pulse Audio include directory"
)

find_library(pulseaudio_LIBRARY NAMES pulse-simple
          DOC "The Pulse Audio library"
)
