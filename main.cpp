
// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <cassert>
#include "ip_filter.h"


int main()
{

    // Вектор для хранения IP-адресов в числовом представлении
    std::vector<IPAddress> ip_pool;

    std::ifstream inputFile;

    try
    {
        // Читаем IP-адреса из файла
        std::string line;

        for (std::string line; std::getline(std::cin, line);)
        {
            ip_pool.push_back(parseIPAddress(line));
        }


        // Сортируем IP-адреса в числовом представлении
        std::sort(ip_pool.begin(), ip_pool.end(), compareIP);

        // Выводим отсортированный список IP-адресов в числовом представлении
        for (const auto& addr : ip_pool) {
            std::cout << intToIPStr(addr.ip) << std::endl;
        }

        // Фильтрация IP адресов по первому байту
        std::vector<IPAddress> filteredIPs;
        for (const auto& ipObj : ip_pool) {
            if (getByteFromIP(ipObj.ip, 0) == 1) {
                filteredIPs.push_back(ipObj);
            }
        }

        // Вывод результатов
        printIPAddresses(filteredIPs);

        // Очистка вектора filteredIPs
        filteredIPs.clear();

        // Фильтрация IP адресов по первому и второму байтам
        for (const auto& ipObj : ip_pool) 
        {
            if ((getByteFromIP(ipObj.ip, 0) == 46) && 
                (getByteFromIP(ipObj.ip, 1) == 70)) 
            {
                filteredIPs.push_back(ipObj);
            }
        }

        // Вывод результатов
        printIPAddresses(filteredIPs);

        // Очистка вектора filteredIPs
        filteredIPs.clear();

        // Фильтрация IP адресов по любому байту
        for (const auto& ipObj : ip_pool) {
            if (getByteFromIP(ipObj.ip, 0) == 46 ||
                (getByteFromIP(ipObj.ip, 1) == 46) ||
                (getByteFromIP(ipObj.ip, 2) == 46) ||
                (getByteFromIP(ipObj.ip, 3) == 46))
            {
                filteredIPs.push_back(ipObj);
            }
        }

        // Вывод результатов
        printIPAddresses(filteredIPs);

    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}



