#ifndef RUAPU_HPP
#define RUAPU_HPP
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define RUAPU_IMPLEMENTATION
#include "../ruapu.h"

class ruapu
{
public:
    static void init() { 
      static int initialised = 0;
      if (!initialised) {
        ruapu_init();
        initialised = 1;
      }
    }


    static bool support(const std::string& isa)
    {
        ruapu::init();
        return ruapu_supports(isa.c_str()) == 1;
    }

    static std::vector<std::string> rua()
    {
        ruapu::init();
        std::vector<std::string> supported_isa_vec;

        const char* const* supported = ruapu_rua();
        while (*supported) {
            supported_isa_vec.push_back(*supported);
            supported++;
        }

        return supported_isa_vec;
    }
};