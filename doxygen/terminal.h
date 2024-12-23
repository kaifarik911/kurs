#pragma once

#include "error.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @class Terminal
 * @brief Класс для работы с параметрами командной строки и конфигурацией.
 *
 * Этот класс предоставляет методы для разбора аргументов командной строки,
 * получения параметров конфигурации и отображения справки.
 */
class Terminal
{
public:
    /**
     * @brief Конструктор класса Terminal.
     * 
     * Устанавливает значения по умолчанию для адреса сервера, порта и пути к файлу конфигурации.
     */
    Terminal();

    /**
     * @brief Возвращает адрес сервера.
     * 
     * @return Адрес сервера.
     */
    string getAddress() const;

    /**
     * @brief Возвращает порт сервера.
     * 
     * @return Порт сервера.
     */
    int getPort() const;

    /**
     * @brief Возвращает путь к входному файлу.
     * 
     * @return Путь к входному файлу.
     */
    string getInputPath() const;

    /**
     * @brief Возвращает путь к выходному файлу.
     * 
     * @return Путь к выходному файлу.
     */
    string getOutputPath() const;

    /**
     * @brief Возвращает путь к файлу конфигурации.
     * 
     * @return Путь к файлу конфигурации.
     */
    string getConfigPath() const;

    /**
     * @brief Разбирает аргументы командной строки и устанавливает соответствующие параметры.
     * 
     * @param argc Количество аргументов командной строки.
     * @param argv Массив аргументов командной строки.
     * @throws RuntimeError Если отсутствует значение для параметра или обнаружен неизвестный параметр.
     */
    void parseArgs(int argc, char *argv[]);

    /**
     * @brief Показывает справочную информацию.
     * 
     * Выводит справочное сообщение о доступных параметрах командной строки.
     */
    void showHelp() const;

private:
    string address_;     ///< Адрес сервера.
    uint16_t port_;      ///< Порт сервера.
    string input_path_;  ///< Путь к входному файлу.
    string output_path_; ///< Путь к выходному файлу.
    string config_path_; ///< Путь к файлу конфигурации.
};
