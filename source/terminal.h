#pragma once

#include "error.h"
#include <string>
#include <vector>

using namespace std;

class Terminal
{
public:
    Terminal();
    string getAddress() const;
    int getPort() const;
    string getInputPath() const;
    string getOutputPath() const;
    string getConfigPath() const;
    void parseArgs(int argc, char *argv[]);
    void showHelp() const;

private:
    string address_;     ///< Адрес сервера.
    uint16_t port_;      ///< Порт сервера.
    string input_path_;  ///< Путь к входному файлу.
    string output_path_; ///< Путь к выходному файлу.
    string config_path_; ///< Путь к файлу конфигурации.
};
