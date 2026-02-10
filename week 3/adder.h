#ifndef MATHSLIB_ADDER_H
#define MATHSLIB_ADDER_H

#if defined(_WIN32) || defined(WIN32)
    #ifdef maths_STATIC
        // don't add any keywords if building a static library
        #define MATHSLIB_API
    #else
        #ifdef maths_EXPORTS
            #define MATHSLIB_API __declspec(dllexport)
        #else
            #define MATHSLIB_API __declspec(dllimport)
        #endif
    #endif
#else
    // On macOS/Linux, we can either leave this blank or use visibility attribute
    #ifdef maths_EXPORTS
        #define MATHSLIB_API __attribute__((visibility("default")))
    #else
        #define MATHSLIB_API
    #endif
#endif

// Function prototype
MATHSLIB_API int add(int a, int b);

#endif
