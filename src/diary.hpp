#include <string>
#include <vector>
#include <iostream>

constexpr auto DataFile = "data.txt";

class Date {
    uint year, month, day;
    friend std::istream& operator>>(std::istream& is, Date& date);
public:
    Date();
    Date(uint year, uint month, uint day);
    const bool operator==(const Date& other) const;
    const bool operator!=(const Date& other) const;
    const bool operator>(const Date& other) const;
    const bool operator>=(const Date& other) const;
    const bool operator<(const Date& other) const;
    const bool operator<=(const Date& other) const;
    const std::string to_string() const;
};

class Diary {
    friend std::ostream& operator<<(std::ostream& os, Diary& diary);
    friend std::istream& operator>>(std::istream& is, Diary& diary);
public:
    Date date;
    std::string content;
    Diary();
    Diary(Date date, std::string&& content);
    const bool operator==(const Diary& other) const;
    const bool operator!=(const Diary& other) const;
    const bool operator>(const Diary& other) const;
    const bool operator>=(const Diary& other) const;
    const bool operator<(const Diary& other) const;
    const bool operator<=(const Diary& other) const;
};

class DiaryBook {
    std::string path;
    std::vector<Diary> diaries;
public:
    DiaryBook(std::string path);
    ~DiaryBook();
    void add(Diary&& diary);
    std::string show(Date date);
    void list(Date start, Date end);
    bool remove(Date date);
};

std::istream& operator>>(std::istream& is, Date& date);
std::ostream& operator<<(std::ostream& os, Date& date);

std::istream& operator>>(std::istream& is, Diary& diary);