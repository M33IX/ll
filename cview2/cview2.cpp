#include <iostream>
#include <string>
#include "XML.cpp"

int main()
{
    setlocale(LC_ALL, "Russian");
    /*
    Visual v;
    Hardware h;

    DWORD userial = 0;;
    DWORD fsf = 0;
    std::string mbs = "";
    std::string cps = "";

    std::string letter = v.GetDriveLetter();

    h.GetSystemData(letter, userial, fsf, cps, mbs);

    std::cout << "Usb serial: " << userial << "\n";
    std::cout << "File System Flags: " << fsf << "\n";
    std::cout << "CPU serial: " << cps << "\n";
    std::cout << "MotherBoard serial: " << mbs << "\n";
    */

    std::string path = "config.xml";

    XMLParser xml = XMLParser(path);

    std::string username = "churka";
    std::string password = "churka";
    std::string group = "churka";
    std::string status = "churka";

    xml.GetUserData(username, password, group, status);

    return 0;
 }