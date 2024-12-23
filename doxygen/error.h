#pragma once

#include <stdexcept>
#include <string>

using namespace std;

/**
 * @class RuntimeError
 * @brief Класс для обработки ошибок времени выполнения.
 *
 * Этот класс используется для создания исключений, связанных с ошибками времени выполнения.
 */
class RuntimeError : public runtime_error
{
public:
    /**
     * @brief Конструктор класса RuntimeError.
     * 
     * @param message Сообщение об ошибке.
     * @param func Имя функции, в которой произошла ошибка.
     * @throws runtime_error Всегда выбрасывает исключение с сообщением об ошибке и именем функции.
     */
    RuntimeError(const string &message, const string &func);
};
