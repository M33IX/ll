#include <string>
#include <fstream>
#include <iostream>
#include <cryptopp/files.h> 
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

using namespace CryptoPP;

class Crypto {
private:
	std::string key = "";
	std::string iv = "";
public:
	Crypto() {};
	~Crypto() {}
	void SetKey(std::string& key) {
		this->key = key;
	}
	void SetIV(std::string& iv) {
		this->iv = iv;
	}
	void Crypt() {}
	void Decrypt() {}
	std::string MakeHash() {}
};