//
// Created by abhilekh on 5/10/24.
//

#ifndef STAB_LIB_H
#define STAB_LIB_H

// check if being compiled on MSVC compiler
#if defined(_MSC_VER)
// export as dll if MSVC Compiler
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC
#endif

#include <string>

namespace STAB{
    namespace Lib{
        extern "C++" DECLSPEC void println(char* str, ...);
        extern "C++" DECLSPEC void print(char* str, ...);
    }
}

#endif //STAB_LIB_H
