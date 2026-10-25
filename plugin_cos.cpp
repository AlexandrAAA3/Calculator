#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport) const char* get_name() { 
    return "cos"; 
}

extern "C" __declspec(dllexport) double evaluate(double arg) {
    return std::cos(arg * std::numbers::pi / 180.0);
}