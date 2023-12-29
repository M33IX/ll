#include "Visual.cpp"
#include "Crypto.cpp"
#include "Log.cpp"

#include <ctime>
/*
#include "XML.cpp"
#include "Checker.cpp"
#include "Generator.cpp"
*/

class MasterController {
private:
	
	Hardware hardware = Hardware();
	Visual visual;
	Crypto crypto = Crypto("config.xml");
	Log logger = Log(std::string("Log.txt"));


	std::string driveLetter = "";
	DWORD driveSerial = 0;
	DWORD fileSystemFlags = 0;
	std::string cpuSerial = "";
	std::string motherBoardSerial = "";
	
	std::string authKey = "";
	std::string iv = "";

	std::string version = "1.0";
	std::string timezone = "+03:00";


	int year = 0; 
	int month = 0;
	int day = 0;
	int hour = 0; 
	int minute = 0;
	int second = 0;

	void MakeAuthKeys(int size, std::string& authKey, std::string& iv) {
		std::string buffer = std::to_string(driveSerial) + std::to_string(fileSystemFlags) + cpuSerial + motherBoardSerial;
		for (int i = 0; i < size; i++) {
			authKey.append(1, buffer[i % strnlen_s(buffer.c_str(), 90)]);
			iv.append(1, buffer[(4 * i + 1) % strnlen_s(buffer.c_str(), 90)]);
		}
	}

	void GetCurrentDateAndTime(int& year, int& month, int& day, int& hour, int& minute, int& second) {
		time_t currentTime;
		struct tm timeInfo;

		time(&currentTime);

		localtime_s(&timeInfo, &currentTime);

		year = timeInfo.tm_year + 1900;  
		month = timeInfo.tm_mon + 1;     
		day = timeInfo.tm_mday;
		hour = timeInfo.tm_hour;
		minute = timeInfo.tm_min;
		second = timeInfo.tm_sec;
	}

	void MakeLogRecord(std::string message) {
		GetCurrentDateAndTime(year, month, day, hour, minute, second);
		logger.WriteLog(year, month, day, hour, minute, second, timezone, version, message);
	}

	int Compare(std::string first, std::string second) {
		int lengthDifference = strnlen_s(first.c_str(), 255) - strnlen_s(second.c_str(), 255);
		switch (lengthDifference) {
		case 0:
			break;
		default:
			throw "Different lengths";
		}
		int difference = 0;
		for (int i = 0; i < strnlen_s(first.c_str(), 255); i++) {
			difference += (int)first[i] - (int)second[i];
		}
		return difference;
	}


public:
	void Initialize() {
		MakeLogRecord(std::string("Запуск приложения. Начало инициализации"));
		driveLetter = visual.GetDriveLetter();
		hardware.GetSystemData(driveLetter, driveSerial, fileSystemFlags, cpuSerial, motherBoardSerial);
		MakeAuthKeys(16, authKey, iv);
		try {
			crypto.SetKey(authKey);
			crypto.SetIV(iv);
		}
		catch (...) {
			MakeLogRecord("Остановка работы: ошибка инициализации");
			throw std::string("Ошибка генерации ключа");
		}

		try {
			crypto.decryptFile(); 
		}
		catch (std::string& errorMessage) {
			MakeLogRecord("Остановка работы: Произведен запуск с недоверенного устройства");
			throw std::string("Запуск с недоверенного устройства");
		}
	}
};