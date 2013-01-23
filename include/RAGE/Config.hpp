////////////////////////////////////////////////////////////
//
// GGE - Generic Game Engine
// Copyright (C) 2011-2012 Adrián Guerra (adrigm@razonartificial.com)
//
////////////////////////////////////////////////////////////

#ifndef RAGE_CONFIG_HPP
#define RAGE_CONFIG_HPP

////////////////////////////////////////////////////////////
// Define the SFML version
////////////////////////////////////////////////////////////
#define RAGE_VERSION_MAJOR 0
#define RAGE_VERSION_MINOR 1


////////////////////////////////////////////////////////////
// Identify the operating system
////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(__WIN32__)

    // Windows
    #define RAGE_SYSTEM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

#elif defined(linux) || defined(__linux)

    // Linux
    #define RAGE_SYSTEM_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    // MacOS
    #define RAGE_SYSTEM_MACOS

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

    // FreeBSD
    #define RAGE_SYSTEM_FREEBSD

#else

    // Unsupported system
    #error This operating system is not supported by SFML library

#endif


////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

    #define RAGE_DEBUG

#endif


////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if defined(RAGE_DYNAMIC)

    #if defined(RAGE_SYSTEM_WINDOWS)

        // Windows compilers need specific (and different) keywords for export and import
        #define RAGE_API_EXPORT __declspec(dllexport)
        #define RAGE_API_IMPORT __declspec(dllimport)

        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
        #ifdef _MSC_VER

            #pragma warning(disable : 4251)

        #endif

    #else // Linux, FreeBSD, Mac OS X

        #if __GNUC__ >= 4

            // GCC 4 has special keywords for showing/hidding symbols,
            // the same keyword is used for both importing and exporting
            #define RAGE_API_EXPORT __attribute__ ((__visibility__ ("default")))
            #define RAGE_API_IMPORT __attribute__ ((__visibility__ ("default")))

        #else

            // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
            #define RAGE_API_EXPORT
            #define RAGE_API_IMPORT

        #endif

    #endif

#else

    // Static build doesn't need import/export macros
    #define RAGE_API_EXPORT
    #define RAGE_API_IMPORT

#endif


////////////////////////////////////////////////////////////
// Define portable fixed-size types
////////////////////////////////////////////////////////////
namespace ra
{
    // All "common" platforms use the same size for char, short and int
    // (basically there are 3 types for 3 sizes, so no other match is possible),
    // we can use them without doing any kind of check

    // 8 bits integer types
    typedef signed   char Int8;
    typedef unsigned char Uint8;

    // 16 bits integer types
    typedef signed   short Int16;
    typedef unsigned short Uint16;

    // 32 bits integer types
    typedef signed   int Int32;
    typedef unsigned int Uint32;

    // 64 bits integer types
#if defined(_MSC_VER)
	typedef signed   __int64 Int64;
	typedef unsigned __int64 Uint64;
#else
	typedef long long Int64;
	typedef unsigned long long Uint64;
#endif

} // namespace GGE


#endif // RAGE_CONFIG_HPP