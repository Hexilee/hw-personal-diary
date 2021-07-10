#include "diary.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>

Date::Date(): Date(0, 0, 0) {}

Date::Date(uint year, uint month, uint day): year(year), month(month), day(day) {}

const bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

const bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

const bool Date::operator>(const Date& other) const {
    if (year > other.year) {
        return true;
    }

    if (year == other.year && month > other.month) {
        return true;
    }

    if (year == other.year && month == other.month && day > other.day) {
        return true;
    }

    return false;
}

const bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

const bool Date::operator<(const Date& other) const {
    if (year < other.year) {
        return true;
    }

    if (year == other.year && month < other.month) {
        return true;
    }

    if (year == other.year && month == other.month && day < other.day) {
        return true;
    }

    return false;
}

const bool Date::operator<=(const Date& other) const {
    return !(*this > other);
}

const std::string Date::to_string() const {
    std::ostringstream buffer;
    buffer << year << '-' << month << '-' << day;
    return buffer.str();
}

std::istream& operator>>(std::istream& is, Date& date) {
    uint year, month, day;
    char seperator1, seperator2;

    is >> year >> seperator1 >> month >> seperator2 >> day;
    if (seperator1 != '-' || seperator2 != '-') {
        std::ostringstream buffer;
        buffer << "invalid seperator: " << seperator1 << " or " << seperator2 << std::endl;
        std::iostream::failure(buffer.str());
    }

    date = Date(year, month, day);
    return is;
}

std::ostream& operator<<(std::ostream& os, Date& date) {
    os << date.to_string();
    return os;
}

Diary::Diary(): date(Date()), content("") {}
Diary::Diary(Date date, std::string&& content): date(date), content(std::move(content)) {}

const bool Diary::operator==(const Diary& other) const {
    return date == other.date;
}

const bool Diary::operator!=(const Diary& other) const {
    return date != other.date;
}

const bool Diary::operator>(const Diary& other) const {
    return date > other.date;
}

const bool Diary::operator>=(const Diary& other) const {
    return date >= other.date;
}

const bool Diary::operator<(const Diary& other) const {
    return date < other.date;
}

const bool Diary::operator<=(const Diary& other) const {
    return date <= other.date;
}

std::istream& operator>>(std::istream& is, Diary& diary) {
    is >> diary.date;
    is.ignore();
    std::getline(is, diary.content);
    return is;
}

std::ostream& operator<<(std::ostream& os, Diary& diary) {
    os << diary.date << " " << diary.content;
    return os;
}

DiaryBook::DiaryBook(std::string path): path(path), diaries(std::vector<Diary>()) {
    auto file = std::ifstream(path);
    std::string line;
    Diary diary;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        if (!(iss >> diary)) { break; } // error
        diaries.push_back(diary);
    }
}

DiaryBook::~DiaryBook() {
    auto file = std::ofstream(path);
    for (auto diary: diaries) {
        file << diary << std::endl;
    }
}


void DiaryBook::add(Diary&& diary) {
    auto target = std::find(diaries.begin(), diaries.end(), diary);
    if (target != diaries.end()) {
        *target = diary;
    } else {
        diaries.push_back(diary);
        std::sort(diaries.begin(), diaries.end());
    }
}

std::string DiaryBook::show(Date date) {
    auto target = std::find(diaries.begin(), diaries.end(), Diary(date, ""));
    if (target != diaries.end()) {
        return target->content;
    } else {
        return "Diary Not Found";
    }
}

void DiaryBook::list(Date start, Date end) {
    for (auto diary: diaries) {
        if (diary.date > end) {
            break;
        }

        if (diary.date >= start) {
            std::cout << diary << std::endl;
        }
    }
}

// return true if removed; return false if not found
bool DiaryBook::remove(Date date) {
    auto pos = std::remove(diaries.begin(), diaries.end(), Diary(date, ""));
    if (pos == diaries.end()) {
        return false;
    }
    diaries.erase(pos, diaries.end());
    return true;
}
