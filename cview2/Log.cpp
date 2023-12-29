#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

constexpr auto MAXLINESCOUNT = 4000;

class Log {
private:
public:
	Log(std::string path){
		this->path = path;
	}
	~Log() {
		
	}
	void WriteLog(int& year, int& month, int& day, 
		int& hour, int& minute, int& second, std::string& timezone, 
		std::string& version, std::string& message) {

		std::ifstream file(path);

		if (file.is_open()) {
			if (std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') > MAXLINESCOUNT) {
				file.close();
				if (std::rename(path.c_str(), (path + std::to_string(month) + std::to_string(day)).c_str()) != 0) {
					throw "Переполнение Log файла без возможности создать новый";
				}
			}
		}

		std::ofstream file1(path, std::ios::app);

		file1 << year << "-" << month << "-" << day << "T" << hour << ":" << minute << ":" << second << timezone << "_" << version << "_" << "\"" << message << "\"" << "\n";

		file1.close();
	}

private:

	std::string path = "";

};