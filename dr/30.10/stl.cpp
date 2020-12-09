#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>
#include <set>

int main() {
    std::unordered_multimap<int, std::string> my_multimap = {
        {1, "value1"},
        {-1, "value2"},
        {2, "value3"},
        {3, "value4"},
        {3, "value5"},
        {5, "value6"},
        {6, "value7"}
    };

    std::cout << "Контейнер unordered_multimap содержит:\n";
    std::for_each(my_multimap.begin(),
                  my_multimap.end(),
                  [](const auto &pair){std::cout << "ключ = " << pair.first << ", значение = " << pair.second << '\n';});
    std::cout << '\n';

    my_multimap.erase(3);
    my_multimap.erase(5);
    std::cout << "Контейнер unordered_multimap, после удаления "
                 "ключей 3 и 5, содержит:\n";
    std::for_each(my_multimap.begin(),
                  my_multimap.end(),
                  [](const auto &pair){std::cout << "ключ = " << pair.first << ", значение = " << pair.second << '\n';});
    std::cout << '\n';

    my_multimap.insert({4, "inserted value1"});
    my_multimap.insert({4, "inserted value2"});
    my_multimap.insert({4, "inserted value3"});
    std::cout << "Контейнер unordered_multimap, после добавления "
                 "3 ключей 4, содержит:\n";
    std::for_each(my_multimap.begin(),
                  my_multimap.end(),
                  [](const auto &pair){std::cout << "ключ = " << pair.first << ", значение = " << pair.second << '\n';});
    std::cout << '\n';

    std::map<int, std::string> my_map;
    std::for_each(my_multimap.begin(), my_multimap.end(), [&my_map](const auto &pair){my_map.insert(pair);});

    std::cout << "Полученная map из unordered_multimap\n";
    std::for_each(my_map.begin(),
                  my_map.end(),
                  [](const auto &pair){std::cout << "ключ = " << pair.first << ", значение = " << pair.second << '\n';});
    std::cout << '\n';

    int val = std::count_if(my_map.begin(), my_map.end(), [](auto const& pair){return pair.first > 0;});
    std::cout << "Количесвто элементов с положтельными ключами " << val << "\n\n";

    std::vector<int> keys(my_map.size());
    std::transform(my_map.begin(), my_map.end(), keys.begin(), [](auto const& pair){return pair.first;});
    std::cout << "Выделенный вектор ключей\n";
    std::for_each(keys.begin(), keys.end(), [](const int &key){std::cout << "ключ = " << key << '\n';});
    std::cout << '\n';

    auto it = std::find(keys.begin(), keys.end(), 2);
    if (it != keys.end()) {
        std::cout << "Элемент 2 найден в массиве\n\n";
    } else {
        std::cout << "Элемент 2 не найден в массиве\n\n";
    }

    std::sort(keys.begin(), keys.end(), [](int &i, int &j){return i - j > 0;});
    std::cout << "Сортированный по убыванию вектор ключей\n";
    std::for_each(keys.begin(), keys.end(), [](const int &key){std::cout << "ключ = " << key << '\n';});
    std::cout << '\n';

    std::replace_if(keys.begin(), keys.end(), [](int &i){return i < 0;}, 1);
    std::cout << "Вектор ключей без отрицательных значений\n";
    std::for_each(keys.begin(), keys.end(), [](const int &key){std::cout << "ключ = " << key << '\n';});
    std::cout << '\n';

    std::set<int> my_set(keys.begin(), keys.end());
    std::cout << "Множествно неповторяющихся ключей, полученное из вектора\n";
    std::for_each(my_set.begin(), my_set.end(), [](const int &key){std::cout << "ключ = " << key << '\n';});
}

