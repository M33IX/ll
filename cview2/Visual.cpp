#include <iostream>
#include <vector>
#include <string>
#include "Hardware.cpp"

class Visual {
public:
	std::string GetDriveLetter() {
		int userInput = -1;
		drives = Hardware::GetDrivesList();
		std::cout << "�������� ���������� �������� ��� �������: " << "\n";
		for (int i = 0; i < drives.size(); i++)
			std::cout << i+1 << ". " << drives[i] << "\n";
		if (!(std::cin >> userInput)) {
			std::cout << "������ ����� ";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		if (userInput > 0 && userInput <= drives.size()) return drives[userInput - 1];
	}
private:
	std::vector<std::string> drives;
};