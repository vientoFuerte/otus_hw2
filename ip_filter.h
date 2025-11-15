
#include <stdint.h>
#include <string>


struct IPAddress {
     uint32_t ip;
};




int32_t ipStrToInt(const std::string& ipStr);
std::string intToIPStr(uint32_t ip);
bool compareIP(const IPAddress& a, const IPAddress& b);
uint8_t getFirstByte(uint32_t ip);

// Функция для получения первого байта IP адреса
uint8_t getFirstByte(uint32_t ip);

// Функция для получения второго байта IP адреса
uint8_t getSecondByte(uint32_t ip);

// Функция для получения третьего байта IP адреса
uint8_t getThirdByte(uint32_t ip);


// Функция для получения четвертого байта IP адреса
uint8_t getFourthByte(uint32_t ip);

// Функция сравнения для сортировки по первому байту
bool compareByFirstByte(const IPAddress& a, const IPAddress& b);
