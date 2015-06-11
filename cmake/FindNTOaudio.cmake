find_path(NAS_INCLUDE_DIR NAMES sys/neutrino.h
          DOC "The NASaudio include directory"
)

find_library(NAS_LIBRARY NAMES audio
          DOC "The NASaudio library"
)
