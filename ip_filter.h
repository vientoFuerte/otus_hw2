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

//int32_t ipStrToInt(const std::string& ipStr);

std::string intToIPStr(uint32_t ip);

bool compareIP(const IPAddress& a, const IPAddress& b);

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

// Распарсить строку с IP-адресом.
IPAddress parseIPAddress(const std::string& ipStr);
