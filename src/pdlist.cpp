#include "diary.hpp"
#include <sstream>


/**
 *  ## Example
 *  > pdlist
 *  > pdlist 2021-7-10
 *  > pdlist 2021-7-10 2022-7-10
 */
int main(int argc, char *argv[]) {
    Date start(0, 0, 0); // min date
    Date end(1 << 31, 1 << 31, 1 << 31); // max date

    if (argc > 1) {
        std::istringstream(argv[1]) >> start;
    } 

    if (argc > 2) {
        std::istringstream(argv[2]) >> end;
    } 

    auto book = DiaryBook(DataFile);
    book.list(start, end);
    return 0;
}
