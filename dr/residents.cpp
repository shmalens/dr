#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string_view>

#define TEXT_FILE_READ "text_file_read.txt"
#define TEXT_FILE_WRITE "text_file_write.txt"
#define BINARY_FILE_READ "binary_file.txt"
#define BINARY_FILE_WRITE "binary_file.txt"

constexpr unsigned int MALE = 1;
constexpr unsigned int FEMALE = 0;

// Необходимые структуры
typedef struct {
    unsigned sur_len;
    unsigned name_len;
    unsigned patron_len;
    unsigned street_len;
} t_meta;

typedef struct {
    std::string street;
    unsigned house_num;
    unsigned apart_num;
} t_address;

typedef struct {
    t_meta metadata;
    std::string surname;
    std::string name;
    std::string patronymic;
    t_address address;
    unsigned gender;
    unsigned age;
} t_citizen;

// эту функцию можно удалить
void show_residents_info(const std::vector<t_citizen> &residents) {
    for (const t_citizen &citizen: residents) {
        std::cout << "Surname: " << citizen.surname << " \n" <<
                  "Name: " << citizen.name << " \n" <<
                  "Patryon: " << citizen.patronymic << " \n" <<
                  "Street: " << citizen.address.street << " \n" <<
                  "House number: " << citizen.address.house_num << " \n" <<
                  "Apartment number: " << citizen.address.apart_num << " \n" <<
                  "Gender: " << (citizen.gender == (unsigned)1 ? "male " : "female ") << citizen.gender << " \n" <<
                  "Age: " << citizen.age << " \n\n";
    }
}

void show_resident_info(const t_citizen &citizen) {
    std::cout << "Surname: " << citizen.surname << " \n" <<
                 "Name: " << citizen.name << " \n" <<
                 "Patryon: " << citizen.patronymic << " \n" <<
                 "Street: " << citizen.address.street << " \n" <<
                 "House number: " << citizen.address.house_num << " \n" <<
                 "Apartment number: " << citizen.address.apart_num << " \n" <<
                 "Gender: " << (citizen.gender == (unsigned)1 ? "male " : "female ") << citizen.gender << " \n" <<
                 "Age: " << citizen.age << " \n\n";
}

// Перегрузка для ввода в тесковом режиме
std::ifstream& operator>> (std::ifstream &file_db, std::vector<t_citizen> &getting_db) {
    std::string line;
    t_citizen tmp;
    while (!file_db.eof()) {
        std::getline(file_db, tmp.surname);
        std::getline(file_db, tmp.name);
        std::getline(file_db, tmp.patronymic);
        std::getline(file_db, tmp.address.street);
        file_db >> tmp.address.house_num;
        file_db >> tmp.address.apart_num;
        file_db >> tmp.gender;
        file_db >> tmp.age;

        tmp.metadata.sur_len = tmp.surname.length();
        tmp.metadata.name_len = tmp.name.length();
        tmp.metadata.patron_len = tmp.patronymic.length();
        tmp.metadata.street_len = tmp.address.street.length();

        getting_db.push_back(tmp);
        file_db.get();
        file_db.get();
    }

    getting_db.pop_back();
    return file_db;
}

// Перегрузка для вывода в текстовом режиме
std::ofstream& operator<< (std::ofstream &file_db, std::vector<t_citizen> &residents) {
    for (const t_citizen &citizen: residents) {
        file_db << citizen.surname << " \n" <<
                   citizen.name << " \n" <<
                   citizen.patronymic << " \n" <<
                   citizen.address.street << " \n" <<
                   citizen.address.house_num << " \n" <<
                   citizen.address.apart_num << " \n" <<
                   citizen.gender << " \n" <<
                   citizen.age << " \n\n";
    }
    return file_db;
}

// считает кол-во женщин и мужчин в определенном доме
std::vector<t_citizen> res_in_house(const std::vector<t_citizen> &residents, const t_address &cur_addr) {
    std::vector<t_citizen> tmp;
    unsigned int female_amount = 0;
    unsigned int male_amount = 0;
    for (const t_citizen &resident : residents) {
        if (resident.address.street != cur_addr.street ||
            resident.address.house_num != cur_addr.house_num) {
            continue;
        }

        (resident.gender == MALE ? ++male_amount: ++female_amount);
        tmp.push_back(resident);
    }

    std::cout << "Количесвто мужчин: " << male_amount << '\n';
    std::cout << "Количесвто женщин: " << female_amount << "\n\n";
    return tmp;
}

int binary_write(std::ofstream &db, std::vector<t_citizen> &residents) {
    for (t_citizen &resident : residents) {
        db.write((char*)&resident.metadata, sizeof(t_meta));
        db.write((char*)resident.surname.c_str(), resident.metadata.sur_len);
        db.write((char*)resident.name.c_str(), resident.metadata.name_len);
        db.write((char*)resident.patronymic.c_str(), resident.metadata.patron_len);
        db.write((char*)resident.address.street.c_str(), resident.metadata.street_len);
        db.write((char*)&resident.address.house_num, sizeof(resident.address.house_num));
        db.write((char*)&resident.address.apart_num, sizeof(resident.address.apart_num));
        db.write((char*)&resident.gender, sizeof(resident.gender));
        db.write((char*)&resident.age, sizeof(resident.age));
    }

    return 1;
}

void clean(char *str) {
    for (int i = 0; i < 100; ++i) {
        str[i] = 0;
    }
}

std::vector<t_citizen> binary_read(std::ifstream &db) {
    std::vector<t_citizen> tmp;
    t_citizen res;
    char tmp_line[100];

    while (!db.eof()) {
        db.read((char*)&res.metadata, sizeof(t_meta));
        db.read((char*)tmp_line, res.metadata.sur_len);
        res.surname = tmp_line;
        clean(tmp_line);
        db.read((char*)tmp_line, res.metadata.name_len);
        res.name = tmp_line;
        clean(tmp_line);
        db.read((char*)tmp_line, res.metadata.patron_len);
        res.patronymic = tmp_line;
        clean(tmp_line);
        db.read((char*)tmp_line, res.metadata.street_len);
        res.address.street = tmp_line;
        clean(tmp_line);
        db.read((char*)&res.address.house_num, sizeof(res.address.house_num));
        db.read((char*)&res.address.apart_num, sizeof(res.address.apart_num));
        db.read((char*)&res.gender, sizeof(res.gender));
        db.read((char*)&res.age, sizeof(res.age));
        tmp.push_back(res);
    }
    tmp.pop_back();
    return tmp;
}

int main() {
    std::ifstream text_file_read(TEXT_FILE_READ);
    std::ofstream text_file_write(TEXT_FILE_WRITE);
    std::ifstream binary_file_read(BINARY_FILE_READ, std::ios::binary);
    std::ofstream binary_file_write(BINARY_FILE_WRITE, std::ios::binary);
    if (!text_file_write.is_open() ||
        !text_file_read.is_open() ||
        !binary_file_read.is_open() ||
        !binary_file_write.is_open()) {
        std::cerr << "Ошибка открытия файла\n";
        return -1;
    }

    // Создаем вкетор
    std::vector<t_citizen> residents;
    // запоняем ветор, заодно демонстрируем работу перегрузки >>
    text_file_read >> residents;
    std::cout << "Вектор значений полученный из text_file_read.txt\n";
    show_residents_info(residents);
    std::cout << "==============================================\n";

    std::sort(residents.begin(),
              residents.end(),
              [](const t_citizen &res1, const t_citizen &res2) {return res1.surname < res2.surname;});

    std::cout << "Отсортированный по фамилиям веткор\n";
    show_residents_info(residents);
    std::cout << "==============================================\n";

    // То задание, где надо воодить улицу
    t_address cur_addres;
    std::cout << "Введите улицу: ";
    std::getline(std::cin, cur_addres.street);
    std::cout << "Введите номер дома: ";
    std::cin >> cur_addres.house_num;

    std::vector<t_citizen> mf_residents = res_in_house(residents, cur_addres);
    std::cout << "Отобранные жители:\n";
    show_residents_info(mf_residents);
    std::cout << "==============================================\n";

    // Запись в текстовый файл и в бинарный файл
    text_file_write << mf_residents;
    binary_write(binary_file_write, mf_residents);
    binary_file_write.close();

    // Ну и просто демонстрация работы чтения из бинарного файла
    std::vector<t_citizen> demo = binary_read(binary_file_read);
    std::cout << "Данные, прочитанные из бинарного файла\n";
    show_residents_info(demo);
    binary_file_read.close();

    text_file_read.close();
    text_file_write.close();
}