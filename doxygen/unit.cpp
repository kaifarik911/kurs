#include <UnitTest++/UnitTest++.h>
#include "data.h"
#include "client.h"
#include "terminal.h"
#include "error.h"

/**
 * @brief Тесты для модуля DataHandler.
 */
SUITE(DataHandlerTests)
{
    /**
     * @brief Тест конструктора класса DataHandler.
     */
    TEST(ConstructorTest)
    {
        DataHandler dataHandler("./config/vclient.conf", "./input.bin", "./output.bin");
        CHECK_EQUAL("./config/vclient.conf", dataHandler.getConfigPath());
        CHECK_EQUAL("./input.bin", dataHandler.getInputPath());
        CHECK_EQUAL("./output.bin", dataHandler.getOutputPath());
    }

    /**
     * @brief Тест загрузки конфигурации.
     */
    TEST(LoadConfigTest)
    {
        DataHandler dataHandler("./config/vclient.conf", "./input.bin", "./output.bin");
        array<string, 2> credentials = dataHandler.loadConfig();
        CHECK_EQUAL("user", credentials[0]);
        CHECK_EQUAL("P@ssW0rd", credentials[1]);
    }

    /**
     * @brief Тест чтения данных.
     */
    TEST(ReadDataTest)
    {
        DataHandler dataHandler("./config/vclient.conf", "./input.bin", "./output.bin");
        vector<vector<double>> data = dataHandler.readData();
        CHECK_EQUAL(3, data.size()); // Предполагается, что файл содержит 3 вектора
        CHECK_EQUAL(3, data[0].size());
        CHECK_CLOSE(14479.95, data[0][0], 0.01);
        CHECK_CLOSE(26581.72, data[0][1], 0.01);
        CHECK_CLOSE(6036.75, data[0][2], 0.01);
    }

    /**
     * @brief Тест записи данных.
     */
    TEST(WriteDataTest)
    {
        DataHandler dataHandler("./config/vclient.conf", "./input.bin", "./output.bin");
        vector<double> result = {1.0, 2.0, 3.0};
        dataHandler.writeData(result);

        // Проверка, что данные были записаны корректно
        ifstream output_file("./output.bin", ios::binary);
        uint32_t size;
        output_file.read(reinterpret_cast<char *>(&size), sizeof(size));
        CHECK_EQUAL(3, size);

        double value;
        output_file.read(reinterpret_cast<char *>(&value), sizeof(value));
        CHECK_EQUAL(1.0, value);
        output_file.read(reinterpret_cast<char *>(&value), sizeof(value));
        CHECK_EQUAL(2.0, value);
        output_file.read(reinterpret_cast<char *>(&value), sizeof(value));
        CHECK_EQUAL(3.0, value);
        output_file.close();
    }

    /**
     * @brief Тест выброса исключения при отсутствии файла конфигурации.
     */
    TEST(CheckThrowFileNotFound)
    {
        DataHandler dataHandler("./config/invalid.conf", "./input.bin", "./output.bin");
        CHECK_THROW(dataHandler.loadConfig(), RuntimeError);
    }
}

/**
 * @brief Тесты для модуля Client.
 */
SUITE(ClientTests)
{
    /**
     * @brief Тест конструктора класса Client.
     */
    TEST(ConstructorTest)
    {
        Client client("127.0.0.1", 33333);
        CHECK_EQUAL("127.0.0.1", client.getAddress());
        CHECK_EQUAL(33333, client.getPort());
    }
}

/**
 * @brief Тесты для модуля Terminal.
 */
SUITE(TerminalTests)
{
    /**
     * @brief Тест конструктора класса Terminal.
     */
    TEST(ConstructorTest)
    {
        Terminal terminal;
        CHECK_EQUAL("127.0.0.1", terminal.getAddress());
        CHECK_EQUAL(33333, terminal.getPort());
        CHECK_EQUAL("./config/vclient.conf", terminal.getConfigPath());
        CHECK_EQUAL("", terminal.getInputPath());
        CHECK_EQUAL("", terminal.getOutputPath());
    }

    /**
     * @brief Тест разбора аргументов командной строки со всеми параметрами.
     */
    TEST(ParseArgs_AllParamsTest)
    {
        Terminal terminal;
        const char *argv[] = {
            "program", "-a", "192.168.0.1", "-p", "8080",
            "-i", "input.bin", "-o", "output.bin",
            "-c", "custom.conf"};
        terminal.parseArgs(11, const_cast<char **>(argv));
        CHECK_EQUAL("192.168.0.1", terminal.getAddress());
        CHECK_EQUAL(8080, terminal.getPort());
        CHECK_EQUAL("input.bin", terminal.getInputPath());
        CHECK_EQUAL("output.bin", terminal.getOutputPath());
        CHECK_EQUAL("custom.conf", terminal.getConfigPath());
    }

    /**
     * @brief Тест выброса исключения при неизвестном параметре командной строки.
     */
    TEST(ParseArgs_UnknownParamTest)
    {
        Terminal terminal;
        const char *argv[] = {"program", "--unknown"};
        CHECK_THROW(terminal.parseArgs(2, const_cast<char **>(argv)), RuntimeError);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для параметра адреса.
     */
    TEST(ParseArgs_MissingAddressValueTest)
    {
        Terminal terminal;
        const char *argv[] = {"program", "-a"};
        CHECK_THROW(terminal.parseArgs(2, const_cast<char **>(argv)), RuntimeError);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для параметра порта.
     */
    TEST(ParseArgs_MissingPortValueTest)
    {
        Terminal terminal;
        const char *argv[] = {"program", "-p"};
        CHECK_THROW(terminal.parseArgs(2, const_cast<char **>(argv)), RuntimeError);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для параметра входного файла.
     */
    TEST(ParseArgs_MissingInputValueTest)
    {
        Terminal terminal;
        const char *argv[] = {"program", "-i"};
        CHECK_THROW(terminal.parseArgs(2, const_cast<char **>(argv)), RuntimeError);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для параметра выходного файла.
     */
    TEST(ParseArgs_MissingOutputValueTest)
    {
        Terminal terminal;
        const char *argv[] = {"program", "-o"};
        CHECK_THROW(terminal.parseArgs(2, const_cast<char **>(argv)), RuntimeError);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для параметра файла конфигурации.
     */
    TEST(ParseArgs_MissingConfigValueTest)
    {
        Terminal terminal;
        const char *argv[] = {"program", "-c"};
        CHECK_THROW(terminal.parseArgs(2, const_cast<char **>(argv)), RuntimeError);
    }

    /**
     * @brief Тест выброса исключения при отсутствии обязательных параметров.
     */
    TEST(CheckThrowMissingMandatoryParameters)
    {
        Terminal terminal;
        const char *argv[] = {"program", "-a", "192.168.0.1"};
        CHECK_THROW(terminal.parseArgs(3, const_cast<char **>(argv)), RuntimeError);
    }
}

/**
 * @brief Главная функция для запуска всех тестов.
 * 
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return int Код возврата программы.
 */
int main(int argc, char *argv[])
{
    return UnitTest::RunAllTests();
}
