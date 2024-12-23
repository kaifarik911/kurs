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

class Client
{
public:
    Client(const string &address, uint16_t port);

    void connectToServer();
    void authenticate(const string &username, const string &password);
    vector<double> calculate(const vector<vector<double>> &data);
    void closeConnection();

    const string &getAddress() const;
    uint16_t getPort() const;

private:
    string address_; ///< Адрес сервера.
    uint16_t port_;  ///< Порт сервера.
    int socket_;     ///< Сокет подключения.
};
