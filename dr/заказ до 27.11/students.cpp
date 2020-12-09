#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

constexpr unsigned int AMOUNT_DIS = 4;

#define FILE_READ "data.txt"
#define FILE_WRITE "result.txt"
#define FILE_BIN "bin"

typedef struct {
    char title[100];
    unsigned int grade;
} discipline;

typedef struct {
    char surname[100];
    char name[100];
    char patronymic[100];
    discipline session[AMOUNT_DIS];
} student;

void show_students(const std::vector<student> &students) {
    for (const student &s : students) {
        std::cout << "Surname: " << s.surname << '\n'
                  << "Name: " << s.name << '\n'
                  << "Patronymic: " << s.patronymic << '\n';

        std::cout << "Результаты сессии\n";
        for (int i = 0; i < AMOUNT_DIS; ++i) {
            std::cout << s.session[i].title << ": " << s.session[i].grade << '\n';
        }
        std::cout << '\n';
    }
}

std::ifstream &operator>>(std::ifstream &ifs, std::vector<student> &students) {
    students.clear();

    while (!ifs.eof()) {
        student s;
        ifs >> s.surname;
        ifs >> s.name;
        ifs >> s.patronymic;
        for (int i = 0; i < AMOUNT_DIS; ++i) {
            ifs >> s.session[i].title;
            ifs >> s.session[i].grade;
        }
        ifs.get();
        students.push_back(s);
    }

    return ifs;
}

std::ofstream &operator<<(std::ofstream &ofs, std::vector<student> &students) {

    for (const student &s : students) {
        ofs << s.surname << '\n';
        ofs << s.name << '\n';
        ofs << s.patronymic << '\n';
        for (int i = 0; i < AMOUNT_DIS; ++i) {
            ofs << s.session[i].title << ' ';
            ofs << s.session[i].grade << '\n';
        }
        ofs << '\n';
    }

    return ofs;
}

int predicate(const student &s) {
    for (int i = 0; i < AMOUNT_DIS; ++i) {
        if (s.session[i].grade != 5) {
            return 0;
        }
    }

    return 1;
}

int get_str(std::ifstream &ifb, char *str) {
    if (str == nullptr) {
        return 0;
    }

    int i = 0;
    do{
        ifb.read(&str[i], sizeof(char));
        ++i;
    } while (str[i - 1] != '\0');

    return 1;
}

int wr_str(std::ofstream &ofb, const char *str) {
    if (str == nullptr) {
        return 0;
    }

    int i = 0;
    while (str[i] != '\0') {
        ofb.write(&str[i++], sizeof(char));
    }
    ofb.write(&str[i], sizeof(char));
    return 1;
}

int binary_write(std::ofstream &ofb, std::vector<student> &students) {
    for (const student &s: students) {
        wr_str(ofb, s.surname);
        wr_str(ofb, s.name);
        wr_str(ofb, s.patronymic);
        for (int i = 0; i < AMOUNT_DIS; ++i) {
            wr_str(ofb, s.session[i].title);
            ofb.write((char*)&s.session[i].grade, sizeof(unsigned));
        }
    }

    return 1;
}

int binary_read(std::ifstream &ifb, std::vector<student> &students) {
    students.clear();

    while (!ifb.eof()) {
        student s;
        get_str(ifb, s.surname);
        get_str(ifb, s.name);
        get_str(ifb, s.patronymic);
        for (int i = 0; i < AMOUNT_DIS; ++i) {
            get_str(ifb, s.session[i].title);
            ifb.read((char*)&s.session[i].grade, sizeof(unsigned int));
        }
        students.push_back(s);
    }

    return 1;
}

int main() {
    std::ifstream text_read(FILE_READ);
    std::ofstream text_write(FILE_WRITE);
    std::ofstream text_obin(FILE_BIN, std::ios::binary);
    std::ifstream text_ibin(FILE_BIN, std::ios::binary);
    if (!text_read.is_open() ||
        !text_write.is_open() ||
        !text_obin.is_open() ||
        !text_ibin.is_open()) {
        std::cerr << "File not opened\n";
        return 0;
    }


    std::vector<student> students;
    text_read >> students;
    show_students(students);
    std::sort(students.begin(),
              students.end(),
              [](const student &s1, const student &s2) {return s1.surname < s2.surname;});

    int excellent_students = std::count_if(students.begin(), students.end(), predicate);

    text_write << students;

    std::cout << "============================================\n\n";
    show_students(students);
    std::cout << "Amount of excellent students: " << excellent_students << '\n';

    binary_write(text_obin, students);
    text_obin.close();
    binary_read(text_ibin, students);

    text_read.close();
    text_write.close();
    text_ibin.close();
    return 1;
}
