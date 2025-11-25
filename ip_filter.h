#pragma once

#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
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

template <typename T>
void addBytes(std::vector<uint8_t>& vec, T byte) {
    vec.push_back(static_cast<uint8_t>(byte));
}

template <typename T, typename... Args>
void addBytes(std::vector<uint8_t>& vec, T first, Args... rest) {
    vec.push_back(static_cast<uint8_t>(first));
    addBytes(vec, rest...);
}

template <typename... Args>
std::vector<uint8_t> addBytesToVector(Args... bytes) {
    std::vector<uint8_t> result;
    addBytes(result, bytes...);
    return result;
}

// Рекурсивная функция фильтрации с variadic templates
// Для шаблонных функций реализация в заголовке!
template <typename T, typename... Args>
std::vector<IPAddress> FilterIpPool(const std::vector<IPAddress>& ipPool, T firstByte, Args... otherBytes) {
    std::vector<IPAddress> result;
    // Сложили в вектор входные байты для проверки на соответствие
    std::vector<uint8_t> filterBytes = addBytesToVector(firstByte, otherBytes...);
    
    // Фильтруем IP-адреса
    for (const auto& ipAddr : ipPool) {
        bool matches = true;
        
        // Проверяем соответствие каждому байту фильтра
        for (size_t i = 0; i < filterBytes.size(); ++i) {
            if (getByteFromIP(ipAddr.ip, i) != filterBytes[i]) {
                matches = false;
                break;
            }
        }
        
        if (matches) {
            result.push_back(ipAddr);
        }
    }
    
    return result;
}

// Вывести на печать все адреса из списка
void printIPAddresses(const std::vector<IPAddress>& ipObjects);
