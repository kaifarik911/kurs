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

class DataHandler
{
public:
    DataHandler(const string &config_path, const string &input_path, const string &output_path);

    array<string, 2> loadConfig() const;
    vector<vector<double>> readData() const;
    void writeData(const vector<double> &data) const;

    const string &getConfigPath() const;
    const string &getInputPath() const;
    const string &getOutputPath() const;

private:
    string config_path; ///< Путь к файлу конфигурации.
    string input_path;  ///< Путь к входному файлу.
    string output_path; ///< Путь к выходному файлу.
};

// Функции для вывода
void PrintVector(const vector<double> &data);
void PrintVectors(const vector<vector<double>> &data);
