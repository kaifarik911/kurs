#include "client.h"

// Конструктор
Client::Client(const string &address, uint16_t port)
    : address_(address), port_(port), socket_(-1) {}

// Метод для установки соединения
void Client::connectToServer()
{
    this->socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket_ < 0)
    {
        throw RuntimeError("Failed to create socket", __func__);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port_);

    if (inet_pton(AF_INET, this->address_.c_str(), &server_addr.sin_addr) <= 0)
    {
        throw RuntimeError("Invalid address/ Address not supported", __func__);
    }

    if (connect(this->socket_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        throw RuntimeError("Connection failed", __func__);
    }
}

// Метод для аутентификации
void Client::authenticate(const string &username, const string &password)
{
    // Отправка логина серверу
    if (send(this->socket_, username.c_str(), username.size(), 0) < 0)
    {
        throw RuntimeError("Failed to send login", __func__);
    }

    // Получение соли от сервера
    char salt[17]; // Соль должна быть 16 символов
    int salt_length = recv(this->socket_, salt, sizeof(salt) - 1, 0);
    if (salt_length < 0)
    {
        throw RuntimeError("Failed to receive salt", __func__);
    }
    salt[salt_length] = '\0';

    // Вычисление хеша с использованием CryptoPP
    Weak::MD5 hash_func; // создаем объект хеш-функции
    string hash_hex;

    // формирование хэша и преобразование в шестнадцатеричную строку
    StringSource(
        string(salt) + password,
        true,
        new HashFilter(
            hash_func,
            new HexEncoder(
                new StringSink(hash_hex),
                true // Заглавные буквы
                )));

    // Отправка хеша серверу
    if (send(this->socket_, hash_hex.c_str(), hash_hex.size(), 0) < 0)
    {
        throw RuntimeError("Failed to send hash", __func__);
    }

    // Получение ответа от сервера
    char response[1024];
    int response_length = recv(this->socket_, response, sizeof(response) - 1, 0);
    if (response_length < 0)
    {
        throw RuntimeError("Failed to receive auth response", __func__);
    }

    response[response_length] = '\0';
    if (string(response) != "OK")
    {
        throw RuntimeError("Authentication failed", __func__);
    }
}

vector<double> Client::calculate(const vector<vector<double>> &data)
{
    // Передача количества векторов
    uint32_t num_vectors = data.size();
    if (send(this->socket_, &num_vectors, sizeof(num_vectors), 0) < 0)
    {
        throw RuntimeError("Failed to send number of vectors", __func__);
    }

    // Передача каждого вектора
    for (const auto &vec : data)
    {
        uint32_t vec_size = vec.size();
        if (send(this->socket_, &vec_size, sizeof(vec_size), 0) < 0)
        {
            throw RuntimeError("Failed to send vector size", __func__);
        }
        if (send(this->socket_, vec.data(), vec_size * sizeof(double), 0) < 0)
        {
            throw RuntimeError("Failed to send vector data", __func__);
        }
    }

    // Получение результатов
    vector<double> results(num_vectors);
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        if (recv(this->socket_, &results[i], sizeof(double), 0) < 0)
        {
            throw RuntimeError("Failed to receive result", __func__);
        }
    }

    // Логирование результата
    cout << "Log: \"Client.calculate()\"\n";
    cout << "Results: {";
    for (const auto &val : results)
    {
        cout << val << ", ";
    }
    if (!results.empty())
    {
        cout << "\b\b"; // Удалить последнюю запятую и пробел
    }
    cout << "}\n";

    return results;
}

// Метод для закрытия соединения
void Client::closeConnection()
{
    if (this->socket_ >= 0)
    {
        ::close(this->socket_);
        this->socket_ = -1;
    }
}

// Методы для получения значений атрибутов
const string &Client::getAddress() const
{
    return address_;
}

uint16_t Client::getPort() const
{
    return port_;
}
