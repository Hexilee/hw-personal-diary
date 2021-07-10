#include "diary.hpp"
#include <sstream>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Please specify the date in command arguments!" << std::endl;
        return -1;
    } 

    auto book = DiaryBook(DataFile);
    Date date;
    std::istringstream(argv[1]) >> date;
    std::cout << book.show(date) << std::endl;
    return 0;
}
