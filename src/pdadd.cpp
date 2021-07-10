#include "diary.hpp"
#include <sstream>

int main() {
    auto book = DiaryBook(DataFile);
    std::string line;
    while (std::getline(std::cin, line, '\n')){
        Diary diary;
        std::istringstream iss(line);
        if (!(iss >> diary)) { break; } // error
        book.add(std::move(diary));
    }
    return 0;
}