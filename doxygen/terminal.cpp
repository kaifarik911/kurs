#include "terminal.h"
#include <iostream>
#include <cstring>

// Конструктор
Terminal::Terminal()
    : address_("127.0.0.1"), port_(33333),
      config_path_("./config/vclient.conf") {}

string Terminal::getConfigPath() const
{
    return this->config_path_;
}

string Terminal::getAddress() const
{
    return this->address_;
}

int Terminal::getPort() const
{
    return this->port_;
}

string Terminal::getInputPath() const
{
    return this->input_path_;
}

string Terminal::getOutputPath() const
{
    return this->output_path_;
}

// Метод для разбора аргументов
void Terminal::parseArgs(int argc, char *argv[])
{
    if (argc == 1)
    {
        showHelp();
        exit(0);
    }
    
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            showHelp();
            exit(0);
        }
        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0)
        {
            if (i + 1 < argc)
                this->address_ = argv[++i];
            else
                throw RuntimeError("Missing value for address parameter", __func__);
        }
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0)
        {
            if (i + 1 < argc)
                this->port_ = stoi(argv[++i]);
            else
                throw RuntimeError("Missing value for port parameter", __func__);
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0)
        {
            if (i + 1 < argc)
                this->input_path_ = argv[++i];
            else
                throw RuntimeError("Missing value for input parameter", __func__);
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            if (i + 1 < argc)
                this->output_path_ = argv[++i];
            else
                throw RuntimeError("Missing value for output parameter", __func__);
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0)
        {
            if (i + 1 < argc)
                this->config_path_ = argv[++i];
            else
                throw RuntimeError("Missing value for config parameter", __func__);
        }
        else
        {
            throw RuntimeError("Unknown parameter: " + string(argv[i]), __func__);
        }
    }

    // Проверка, заданы ли все необходимые параметры
    if (this->input_path_.empty() || this->output_path_.empty())
    {
        throw RuntimeError("Missing mandatory input or output file path", __func__);
    }
}

// Метод для показа справки
void Terminal::showHelp() const
{
    cout << "Usage: vclient [options]\n"
         << "Options:\n"
         << "  -h, --help            Show this help message and exit\n"
         << "  -a, --address ADDRESS Server address (default: 127.0.0.1)\n"
         << "  -p, --port PORT       Server port (default: 33333)\n"
         << "  -i, --input PATH      Path to input data file\n"
         << "  -o, --output PATH     Path to output data file\n"
         << "  -c, --config PATH     Path to config file (default: ./config/vclient.conf)\n";
}
