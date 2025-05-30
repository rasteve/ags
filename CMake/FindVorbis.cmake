# find_package uses this "FindVorbis.cmake" in CMAKE_MODULE_PATH of the ags project
# It uses PkgConfig on Linux and it should probably be redone to be simpler

if (TARGET Vorbis::Vorbis)
    return()
endif()

if (WIN32)
    add_library(Vorbis::Vorbis STATIC IMPORTED)
    set_property(TARGET Vorbis::Vorbis PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/Solutions/.lib/libvorbis_static.lib)
    set_property(TARGET Vorbis::Vorbis PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/Windows/include)

    add_library(Vorbis::VorbisFile STATIC IMPORTED)
    set_property(TARGET Vorbis::VorbisFile PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/Solutions/.lib/libvorbisfile_static.lib)
    set_property(TARGET Vorbis::VorbisFile PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/Windows/include)
endif()

if (LINUX)
    pkg_check_modules(VORBIS REQUIRED IMPORTED_TARGET GLOBAL vorbis)
    add_library(Vorbis::Vorbis ALIAS PkgConfig::VORBIS)
    pkg_check_modules(VORBISFILE REQUIRED IMPORTED_TARGET GLOBAL vorbisfile)
    add_library(Vorbis::VorbisFile ALIAS PkgConfig::VORBISFILE)
endif()

if (MACOS)
    add_library(Vorbis::Vorbis STATIC IMPORTED)
    set_property(TARGET Vorbis::Vorbis PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/OSX/lib/libvorbis.a)
    set_property(TARGET Vorbis::Vorbis PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/OSX/include)
    set_property(TARGET Vorbis::Vorbis PROPERTY INTERFACE_LINK_LIBRARIES Ogg::Ogg)

    add_library(Vorbis::VorbisFile STATIC IMPORTED)
    set_property(TARGET Vorbis::VorbisFile PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/OSX/lib/libvorbisfile.a)
    set_property(TARGET Vorbis::VorbisFile PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/OSX/include)
    set_property(TARGET Vorbis::VorbisFile PROPERTY INTERFACE_LINK_LIBRARIES Vorbis::Vorbis Ogg::Ogg)
endif()
