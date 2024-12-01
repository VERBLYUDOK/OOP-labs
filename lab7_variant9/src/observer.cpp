#include "observer.h"

void ConsoleObserver::onEvent(const std::string& event) {
    std::lock_guard<std::mutex> lock(console_mutex);
    std::cout << event << std::endl;
}

FileObserver::FileObserver(const std::string& filename) {
    ofs.open(filename, std::ios::app);
}

FileObserver::~FileObserver() {
    if (ofs.is_open()) {
        ofs.close();
    }
}

void FileObserver::onEvent(const std::string& event) {
    if (ofs.is_open()) {
        ofs << event << std::endl;
    }
}
