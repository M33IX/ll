#include <iostream>
#include <string>
#include "Hardware.cpp"

int main()
{
    std::string a = "";
    Hardware::GetHardwareData(a);
    std::cout << a << std::endl;
    return 0;

}