#include <string>
#include <fstream>
#include <iostream>

#include <cryptopp/files.h> 
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

constexpr auto LENGTH = CryptoPP::AES::BLOCKSIZE;

using namespace CryptoPP;

class Crypto {
private:
    byte key[AES::DEFAULT_KEYLENGTH] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };
    byte iv[AES::BLOCKSIZE] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };
    std::string inputFile;
    std::string output = "bin";

public: 
    Crypto(std::string filename) {
        this->inputFile = filename;
    }
    void encryptFile() {
    std::ifstream ifs(inputFile, std::ios::binary);
    std::ofstream ofs(output, std::ios::binary);

    AES::Encryption aesEncryption(key, AES::DEFAULT_KEYLENGTH);
    CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

    FileSource fileSource(ifs, true,
        new StreamTransformationFilter(cbcEncryption,
            new FileSink(ofs)
        )
    );
    ifs.close();
    ofs.close();
    std::remove(inputFile.c_str());
    }

    void decryptFile() {
        std::ifstream ifs(inputFile, std::ios::binary);
        std::ofstream ofs(output, std::ios::binary);

        AES::Decryption aesDecryption(key, AES::DEFAULT_KEYLENGTH);
        CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

        FileSource fileSource(ifs, true,
            new StreamTransformationFilter(cbcDecryption,
            new FileSink(ofs)
            )
        );
        ifs.close();
        ofs.close();
        std::remove(output.c_str());
      }

      void SetKey(std::string& key) {
          if (strnlen_s(key.c_str(), 64) != AES::DEFAULT_KEYLENGTH) throw std::string("Wrong key size");
          for (int i = 0; i < LENGTH; i++) {
              this->key[i] = key[i];
          }
      }
      void SetIV(std::string& iv) {
          if (strnlen_s(iv.c_str(), 64) != AES::BLOCKSIZE) throw std::string("Wrong key size");
          for (int i = 0; i < LENGTH; i++) {
              this->iv[i] = iv[i];
          }
      }

};