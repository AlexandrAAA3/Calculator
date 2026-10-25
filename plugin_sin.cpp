#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport) const char* get_name() { 
    return "sin"; 
}

extern "C" __declspec(dllexport) double evaluate(double arg) {
    return std::sin(arg * std::numbers::pi / 180.0);
}