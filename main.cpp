
// ip_filter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

// Source - https://stackoverflow.com/a
// Posted by templatetypedef, modified by community. See post 'Timeline' for change history
// Retrieved 2025-11-15, License - CC BY-SA 4.0

#include <stdint.h>



struct IPAddress {
     uint32_t ip;
};


// Из строки выделить 4 фграмента IP адреса и склеить в одно число.
uint32_t ipStrToInt(const std::string& ipStr) {
    uint32_t result = 0;
    std::istringstream issIP(ipStr);
    std::string segmentPart;
    std::vector<int> ipParts;
    while (std::getline(issIP, segmentPart, '.'))
    {
        ipParts.push_back(std::stoi(segmentPart));
    }

    if (ipParts.size() != 4)
    {
        throw std::invalid_argument("Invalid IP address format");
    }
    result = (ipParts[0] << 24) |
        (ipParts[1] << 16) |
        (ipParts[2] << 8) |
        ipParts[3];

    return result;
}


// Преобразование целого числа обратно в IP-адрес
std::string intToIPStr(uint32_t ip) {
    std::stringstream ss;
    for (int i = 3; i >= 0; --i) {
        if (i < 3) ss << ".";
        ss << ((ip >> (i * 8)) & 0xFF);
    }
    return ss.str();
}

bool compareIP(const IPAddress& a, const IPAddress& b) {
    return a.ip > b.ip;
}

// Функция для получения первого байта IP адреса
uint8_t getFirstByte(uint32_t ip) {
    return (ip >> 24) & 0xFF;
}

// Функция для получения второго байта IP адреса
uint8_t getSecondByte(uint32_t ip) {
    return (ip >> 16) & 0xFF;
}
// Функция для получения третьего байта IP адреса
uint8_t getThirdByte(uint32_t ip) {
    return (ip >> 8) & 0xFF;
}

// Функция для получения четвертого байта IP адреса
uint8_t getFourthByte(uint32_t ip) {
    return ip & 0xFF;
}

// Функция сравнения для сортировки по первому байту
bool compareByFirstByte(const IPAddress& a, const IPAddress& b) {
    return getFirstByte(a.ip) < getFirstByte(b.ip);
}


// Распарсить строку с IP-адресом.
IPAddress parseIPAddress(const std::string& ipStr) {
    IPAddress addr {};
    addr.ip = ipStrToInt(ipStr);
    return addr;
}



int main()
{

    // Вектор для хранения IP-адресов в числовом представлении
    std::vector<IPAddress> ip_pool;

    std::ifstream inputFile;

#if 0
    std::string filename = "ip_filter.tsv";

    // Открываем файл для чтения
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) 
    {
        std::cerr << "File open error: " << filename << std::endl;
        std::cerr << "Error code: " << inputFile.rdstate() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "file opened" << std::endl;
    }

#endif
    try
    {
        // Читаем IP-адреса из файла
        std::string line;

        for (std::string line; std::getline(std::cin, line);)
        {
            ip_pool.push_back(parseIPAddress(line));
        }
        /*
        while (std::getline(inputFile, line)) 
        {
            ip_pool.push_back(parseIPAddress(line));
        }*/

        // Сортируем IP-адреса в числовом представлении
        std::sort(ip_pool.begin(), ip_pool.end(), compareIP);

        // Выводим отсортированный список IP-адресов в числовом представлении
        for (const auto& addr : ip_pool) {
            std::cout << intToIPStr(addr.ip) << std::endl;
        }

        // Фильтрация IP адресов по первому байту
        std::vector<IPAddress> filteredIPs;
        for (const auto& ipObj : ip_pool) {
            if (getFirstByte(ipObj.ip) == 1) {
                filteredIPs.push_back(ipObj);
            }
        }

        // Вывод результатов
        for (const auto& ipObj : filteredIPs) {
            std::cout << intToIPStr(ipObj.ip) << std::endl;
        }

        // Очистка вектора filteredIPs
        filteredIPs.clear();

        // Фильтрация IP адресов по первому и второму байтам
        for (const auto& ipObj : ip_pool) {
            if (getFirstByte(ipObj.ip) == 46 && getSecondByte(ipObj.ip) == 70) {
                filteredIPs.push_back(ipObj);
            }
        }

        // Вывод результатов
        for (const auto& ipObj : filteredIPs) {
            std::cout << intToIPStr(ipObj.ip) << std::endl;
        }

        // Очистка вектора filteredIPs
        filteredIPs.clear();

        // Фильтрация IP адресов по любому байту
        for (const auto& ipObj : ip_pool) {
            if (getFirstByte(ipObj.ip) == 46 || 
                (getSecondByte(ipObj.ip) == 46) ||
                (getThirdByte(ipObj.ip) == 46) ||
                (getFourthByte(ipObj.ip) == 46)) 
            {
                filteredIPs.push_back(ipObj);
            }
        }

        // Вывод результатов
        for (const auto& ipObj : filteredIPs) {
            std::cout << intToIPStr(ipObj.ip) << std::endl;
        }


        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Закрываем файл
    inputFile.close();

    return 0;
}


