#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport) const char* get_name() { 
    return "ln"; 
}

extern "C" __declspec(dllexport) double evaluate(double arg) {
    if (arg <= 0.0) {
        throw std::domain_error("ERROR_DLL, ln of non-positive value");
    }
    return std::log(arg);
}