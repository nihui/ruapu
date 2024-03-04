#include <iostream>
#include <vector>

#include "ruapu.hpp"

int main()
{
    ruapu my_ruapu;

    std::cout << "Testing support function:\n";
    std::string isa_to_test = "avx2";
    bool is_supported = my_ruapu.support(isa_to_test);
    if (is_supported) {
        std::cout << isa_to_test << " is supported.\n";
    } else {
        std::cout << isa_to_test << " is not supported.\n";
    }

    std::cout << "\nListing supported ISAs:\n";
    std::vector<std::string> supported_isas = my_ruapu.rua();
    for (const auto& isa : supported_isas) {
      std::cout << isa << "\n";
    }
}