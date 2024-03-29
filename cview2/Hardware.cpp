#include <Windows.h>
#include <array>
#include <vector>
#include <string>

class Hardware{
public:
	Hardware() {
		
	}
	~Hardware() {
		
	}
	void GetSystemData(std::string& driveletter, DWORD& serial, DWORD& filesystemflags, std::string& cpuSerial, std::string& motherboardserial) {
		GetDriveData(driveletter);
		GetHardwaredata();
		cpuSerial = cserial;
		motherboardserial = mbserial;
		serial = usbserial;
		filesystemflags = fsflags;
	}
	static std::vector<std::string> GetDrivesList() {
		DWORD drives = GetLogicalDrives();
		std::vector<std::string> result;
		for (char i = 'A'; i <= 'Z'; ++i) {
			if ((drives & 1) != 0) {
				result.push_back(std::string{i} + ":\\");
			}
			drives >>= 1;
		}
		return result;
	}
private:
	DWORD usbserial = 0;
	DWORD fsflags = 0;
	std::string cserial;
	std::string mbserial;
	std::string dletter;
	char moboSerialBuf[1024]{};
	std::string moboSerialCommand;
	int i = 0;

	void GetDriveData(std::string letter) {
		dletter = "";
		dletter = letter;
			if (!GetVolumeInformationA(dletter.c_str(), nullptr, 0, &usbserial, nullptr, &fsflags, nullptr, 0)) {
				throw "Can't get drive info";
			}
	}
	void GetHardwaredata() {
		cserial = "";
		mbserial = "";
		moboSerialCommand = "wmic baseboard get serialnumber | find /v \"SerialNumber\"";

		FILE* moboSerialStream = _popen(moboSerialCommand.c_str(), "r");
		if (moboSerialStream) {
			if (fgets(moboSerialBuf, sizeof(moboSerialBuf), moboSerialStream) != nullptr) {
				i = 0;
				while ((moboSerialBuf[i] != 32) && (moboSerialBuf[i] != '\0') && (moboSerialBuf[i] != 13) && (moboSerialBuf[i] != 10) && (moboSerialBuf[i] != 0) && (i <= 64)) {

					mbserial += moboSerialBuf[i];
					i++;
				}
			}
			_pclose(moboSerialStream);
		}
		

		moboSerialCommand = "wmic cpu get processorId | find /v \"ProcessorId\"";

		moboSerialStream = _popen(moboSerialCommand.c_str(), "r");
		if (moboSerialStream) {
			if (fgets(moboSerialBuf, sizeof(moboSerialBuf), moboSerialStream) != nullptr) {
				i = 0;
				while ((moboSerialBuf[i] != 32) && (moboSerialBuf[i] != '\0') && (moboSerialBuf[i] != 13) && (moboSerialBuf[i] != 10) && (moboSerialBuf[i] != 0) && (i <= 64)) {

					cserial += moboSerialBuf[i];
					i++;
				}
			}
			_pclose(moboSerialStream);
		}
	}
};