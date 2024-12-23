#include "data.h"
#include "error.h"
#include <sstream>
#include <fstream>

// Конструктор
DataHandler::DataHandler(const string &config_path, const string &input_path, const string &output_path)
    : config_path(config_path),
      input_path(input_path),
      output_path(output_path) {}

// Метод для чтения конфигурационных данных
array<string, 2> DataHandler::loadConfig() const
{
    ifstream conf_file(this->config_path);
    if (!conf_file.is_open())
    {
        throw RuntimeError("Failed to open configuration file \"" + this->config_path + "\"", __func__);
    }

    array<string, 2> credentials;
    string line;
    getline(conf_file, line);
    conf_file.close();

    istringstream iss(line);
    getline(iss, credentials[0], ':');
    getline(iss, credentials[1]);

    if (credentials[0].empty() || credentials[1].empty())
    {
        throw RuntimeError("Missing login or password", __func__);
    }

    return credentials;
}

// Метод для чтения данных
vector<vector<double>> DataHandler::readData() const
{
    ifstream input_file(this->input_path, ios::binary);
    if (!input_file.is_open())
    {
        throw RuntimeError("Failed to open input file for reading.", __func__);
    }

    uint32_t num_vectors;
    input_file.read(reinterpret_cast<char *>(&num_vectors), sizeof(num_vectors));

    vector<vector<double>> data(num_vectors);
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        uint32_t vector_size;
        input_file.read(reinterpret_cast<char *>(&vector_size), sizeof(vector_size));

        vector<double> vec(vector_size);
        for (uint32_t j = 0; j < vector_size; ++j)
        {
            input_file.read(reinterpret_cast<char *>(&vec[j]), sizeof(double));
        }

        data[i] = vec;
    }

    input_file.close();
    return data;
}

// Метод для записи данных
void DataHandler::writeData(const vector<double> &data) const
{
    ofstream output_file(this->output_path, ios::binary);
    if (!output_file.is_open())
    {
        throw RuntimeError("Failed to open output file \"" + this->output_path + "\"", __func__);
    }

    uint32_t count = data.size();
    output_file.write(reinterpret_cast<const char *>(&count), sizeof(count));

    for (const auto &num : data)
    {
        output_file.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }

    output_file.close();
}

// Методы для получения значений атрибутов
const string &DataHandler::getConfigPath() const
{
    return config_path;
}

const string &DataHandler::getInputPath() const
{
    return input_path;
}

const string &DataHandler::getOutputPath() const
{
    return output_path;
}

// Функции для вывода
void PrintVector(const vector<double> &data)
{
    cout << "[ ";
    for (const auto &val : data)
    {
        cout << fixed << setprecision(2) << val << " ";
    }
    cout << "]";
    cout << endl;
}

void PrintVectors(const vector<vector<double>> &data)
{
    cout << "[\n";
    for (const auto &vec : data)
    {
        cout << "  [ ";
        for (const auto &val : vec)
        {
            cout << fixed << setprecision(2) << val << " ";
        }
        cout << "]\n";
    }
    cout << "]";
    cout << endl;
}
