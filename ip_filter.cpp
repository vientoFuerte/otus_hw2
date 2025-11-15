include "ip_filter.h"

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
