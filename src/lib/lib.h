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
        extern "C++" DECLSPEC void writeln(std::string str, ...);
        extern "C++" DECLSPEC void write(std::string str, ...);
        extern "C++" DECLSPEC std::string read(std::string *str, ...);
    }
}

#endif //STAB_LIB_H
