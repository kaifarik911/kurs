#include "error.h"
#include "data.h"
#include "client.h"
#include "terminal.h"
#include <array>
#include <iostream>

using namespace std;

/**
 * @brief Главная функция программы.
 * 
 * Выполняет следующие шаги:
 * - Инициализирует терминал.
 * - Разбирает аргументы командной строки.
 * - Подключается к серверу.
 * - Загружает конфигурацию.
 * - Аутентифицирует пользователя.
 * - Читает данные из входного файла.
 * - Выполняет вычисления.
 * - Записывает результаты в выходной файл.
 * 
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return int Код возврата программы.
 */
int main(int argc, char *argv[])
{
    try
    {
        // Логируем инициализацию терминала
        cout << "[LOG] Initializing Terminal..." << endl;
        Terminal terminal;
        terminal.parseArgs(argc, argv);

        // Логируем пути и параметры конфигурации
        cout << "[LOG] Config Path: " << terminal.getConfigPath() << endl;
        cout << "[LOG] Input Path: " << terminal.getInputPath() << endl;
        cout << "[LOG] Output Path: " << terminal.getOutputPath() << endl;
        cout << "[LOG] Server Address: " << terminal.getAddress() << endl;
        cout << "[LOG] Server Port: " << terminal.getPort() << endl;

        // Подключаемся к серверу
        cout << "[LOG] Connecting to server at " << terminal.getAddress() << ":" << terminal.getPort() << "..." << endl;
        Client client(terminal.getAddress(), terminal.getPort());
        client.connectToServer();

        // Загружаем конфигурацию
        cout << "[LOG] Loading configuration from " << terminal.getConfigPath() << "..." << endl;
        DataHandler data(terminal.getConfigPath(), terminal.getInputPath(), terminal.getOutputPath());

        // Получаем логин и пароль из конфигурационного файла
        array<string, 2> userpass = data.loadConfig();
        cout << "[LOG] Username: " << userpass[0] << endl;

        // Аутентифицируем пользователя на сервере
        cout << "[LOG] Authenticating user " << userpass[0] << "..." << endl;
        client.authenticate(userpass[0], userpass[1]);

        // Читаем данные из входного файла
        cout << "[LOG] Reading data from " << terminal.getInputPath() << "..." << endl;
        vector<vector<double>> vectors = data.readData();
        cout << "[LOG] Read data: " << endl;
        PrintVectors(vectors);

        // Выполняем вычисления
        cout << "[LOG] Calculating results..." << endl;
        vector<double> result = client.calculate(vectors);
        cout << "[LOG] Calculated results: " << endl;
        PrintVector(result);

        // Записываем результаты в выходной файл
        cout << "[LOG] Writing results to " << terminal.getOutputPath() << "..." << endl;
        data.writeData(result);

        cout << "[LOG] Operation completed successfully!" << endl;
    }
    catch (const RuntimeError &e)
    {
        // Логируем ошибки времени выполнения
        cerr << "[ERR] Runtime error: " << e.what() << endl;
        return 1;
    }
    catch (const exception &e)
    {
        // Логируем общие ошибки
        cerr << "[ERR] Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
