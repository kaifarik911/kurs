#pragma once

#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "error.h"

using namespace std;

/**
 * @class DataHandler
 * @brief Класс для работы с данными.
 *
 * Этот класс предоставляет методы для загрузки конфигурации, чтения и записи данных.
 */
class DataHandler
{
public:
    /**
     * @brief Конструктор класса DataHandler.
     * 
     * @param config_path Путь к файлу конфигурации.
     * @param input_path Путь к входному файлу.
     * @param output_path Путь к выходному файлу.
     */
    DataHandler(const string &config_path, const string &input_path, const string &output_path);

    /**
     * @brief Загружает конфигурационные данные из файла.
     * 
     * @return Массив строк, содержащий логин и пароль.
     * @throws RuntimeError Если не удалось открыть файл конфигурации или отсутствует логин или пароль.
     */
    array<string, 2> loadConfig() const;

    /**
     * @brief Читает данные из входного файла.
     * 
     * @return Вектор векторов данных.
     * @throws RuntimeError Если не удалось открыть входной файл или произошла ошибка чтения данных.
     */
    vector<vector<double>> readData() const;

    /**
     * @brief Записывает данные в выходной файл.
     * 
     * @param data Вектор данных для записи.
     * @throws RuntimeError Если не удалось открыть выходной файл или произошла ошибка записи данных.
     */
    void writeData(const vector<double> &data) const;

    /**
     * @brief Возвращает путь к файлу конфигурации.
     * 
     * @return Путь к файлу конфигурации.
     */
    const string &getConfigPath() const;

    /**
     * @brief Возвращает путь к входному файлу.
     * 
     * @return Путь к входному файлу.
     */
    const string &getInputPath() const;

    /**
     * @brief Возвращает путь к выходному файлу.
     * 
     * @return Путь к выходному файлу.
     */
    const string &getOutputPath() const;

private:
    string config_path; ///< Путь к файлу конфигурации.
    string input_path;  ///< Путь к входному файлу.
    string output_path; ///< Путь к выходному файлу.
};

/**
 * @brief Функция для красивого вывода вектора данных.
 * 
 * @param data Вектор данных для вывода.
 */
void PrintVector(const vector<double> &data);

/**
 * @brief Функция для красивого вывода векторов данных.
 * 
 * @param data Вектор векторов данных для вывода.
 */
void PrintVectors(const vector<vector<double>> &data);
