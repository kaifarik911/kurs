#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#pragma once

#include "error.h"
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cryptopp/hex.h>
#include <cryptopp/md5.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;
using namespace CryptoPP::Weak1;

/**
 * @class Client
 * @brief Класс для работы с сервером.
 *
 * Этот класс предоставляет методы для установки соединения с сервером,
 * аутентификации пользователя, выполнения вычислений и закрытия соединения.
 */
class Client
{
public:
    /**
     * @brief Конструктор класса Client.
     * 
     * @param address Адрес сервера.
     * @param port Порт сервера.
     */
    Client(const string &address, uint16_t port);

    /**
     * @brief Устанавливает соединение с сервером.
     * 
     * @throws RuntimeError Если не удалось создать сокет или подключиться к серверу.
     */
    void connectToServer();

    /**
     * @brief Аутентифицирует пользователя на сервере.
     * 
     * @param username Имя пользователя.
     * @param password Пароль пользователя.
     * @throws RuntimeError Если аутентификация не удалась.
     */
    void authenticate(const string &username, const string &password);

    /**
     * @brief Выполняет вычисления на сервере.
     * 
     * @param data Данные для вычислений в виде вектора векторов.
     * @return Результаты вычислений в виде вектора.
     * @throws RuntimeError Если не удалось передать данные или получить результат.
     */
    vector<double> calculate(const vector<vector<double>> &data);

    /**
     * @brief Закрывает соединение с сервером.
     */
    void closeConnection();

    /**
     * @brief Возвращает адрес сервера.
     * 
     * @return Адрес сервера.
     */
    const string &getAddress() const;

    /**
     * @brief Возвращает порт сервера.
     * 
     * @return Порт сервера.
     */
    uint16_t getPort() const;

private:
    string address_; ///< Адрес сервера.
    uint16_t port_;  ///< Порт сервера.
    int socket_;     ///< Сокет подключения.
};
