#ifndef LOGGER_H
#define LOGGER_G

#include <mutex>
#include <string>
#include <iostream>

class Logger {
public:
    // Синхронизированный вывод строки
    static void log(const std::string& message);

    // Шаблонный метод для синхронизированного вывода любых данных
    template<typename T>
    static void log(const T& data) {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << data << std::endl;
    }

    // Шаблонный метод для синхронизированного вывода с произвольным количеством аргументов
    template<typename... Args>
    static void log(const Args&... args) {
        std::lock_guard<std::mutex> lock(console_mutex);
        (std::cout << ... << args) << std::endl;
    }

    // Метод для синхронизированного вывода блока кода
    template<typename Func>
    static void logBlock(Func func) {
        std::lock_guard<std::mutex> lock(console_mutex);
        func();
    }

private:
    static std::mutex console_mutex;
};

#endif