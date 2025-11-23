#pragma once

#include <stdint.h>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

struct IPAddress {
    uint32_t ip;
};

//Строку с IP преобразовать в целое беззнаковое число.
uint32_t ipStrToInt(const std::string& ipStr);

//Целое беззнаковое число преобразовать в строку с IP.
std::string intToIPStr(uint32_t ip);

//Сравнить IP-адреса
bool compareIP(const IPAddress& a, const IPAddress& b);

// Получение байта IP-адреса (байты в диапазоне от 0 до 3)
uint8_t getByteFromIP(uint32_t ip, uint8_t byteIndex);

// Распарсить строку с IP-адресом.
IPAddress parseIPAddress(const std::string& ipStr);

// Фильтрация IP адресов по любому байту
std::vector<IPAddress> filterByAnyByte(const std::vector<IPAddress>& ipPool, uint8_t byte);

// Вывести на печать все адреса из списка
void printIPAddresses(const std::vector<IPAddress>& ipObjects);
