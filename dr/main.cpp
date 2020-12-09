#include <regex>
#include <map>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

// Параметры для инициализации графа
struct InitParams {
    enum GraphType {
        Directed,
        Undirected,
    };

    enum TraversalWay {
        Breadth,
        Depth,
    };

    // Тип графа (ориентированный, неориентированный)
    GraphType Type;
    // Способ обхода (в ширину, в глубину)
    TraversalWay Way;
    // Узел, с которого начинаем обход
    std::string TraverBegin;
};

// Функиця добавляет в массив neighbors элемент v так, чтобы массив оставался
// отсортированным и не было повторяющихся эементов
void SortedPush(std::vector<std::string>& neighbors, const std::string& v) {
    if (std::find(neighbors.begin(), neighbors.end(), v) == neighbors.end()) {
        neighbors.insert(std::lower_bound(neighbors.begin(), neighbors.end(), v), v);
    }
}

class Graph {
private:
    // Множество вершин и их соответсвующих соседей
    std::unordered_map<std::string, std::vector<std::string>> _vertexes;
    // Параметры инициализации
    InitParams _params;

public:
    // Переновим параметры инициализации
    explicit Graph(InitParams params)
      : _params(std::move(params))
    {}

    // Добавляем новое ребро i-j в граф (если нет вершины i или j,
    // то добавляет их во множество вершин)
    void AddEdge(const std::string& i, const std::string& j) {
        auto iIter = _vertexes.find(i);
        if (iIter == _vertexes.end()) {
            _vertexes.insert(std::make_pair(i, std::vector<std::string>{}));
            iIter = _vertexes.find(i);
        }

        auto jIter = _vertexes.find(j);
        if (jIter == _vertexes.end()) {
            _vertexes.insert(std::make_pair(j, std::vector<std::string>{}));
            jIter = _vertexes.find(j);
        }

        // Добавляем к соседям вершины i вершину j
        SortedPush(iIter->second, j);
        // Если граф неориентрованный, то добавляем и обратное ребро
        if (_params.Type == InitParams::Undirected) {
            SortedPush(jIter->second, i);
        }
    }

    // Фунцкия обхожа графа
    std::vector<std::string> Traversal() const {
        switch (_params.Way) {
            case InitParams::Breadth:
                // Вызываем обходв ширину
                return _Breadth();
            case InitParams::Depth:
                // Создаем массив для вершин, которые обошли и
                // вызываем обход в глубину
                std::unordered_set<std::string> visited;
                std::vector<std::string> traversal;
                _Depth(_params.TraverBegin, visited, traversal);
                return traversal;
        }
        throw std::runtime_error{
            "unexpected traversal way"
        };
    }

private:
    // Алгоритм обхода в ширину
    std::vector<std::string> _Breadth() const {
        // Вершины которые обошли
        std::vector<std::string> traversal;
        std::unordered_set<std::string> visited;

        // Создаем очередь, в которую сохранияем детей
        std::queue<std::string> q;
        // Записываем начальную вершину в очередь
        q.push(_params.TraverBegin);
        visited.insert(_params.TraverBegin);
        // Пока очередь не пуста, то снимаем с верха очереди вершину
        // Если мы ее еще не обощли, то записываем в очередь всех детей вершины
        while (!q.empty()) {
            // Вытаскиваем из очереди выршину и добавляем в обход
            auto popped = q.front();
            q.pop();
            traversal.push_back(popped);

            // Проходимся по непосещенным соседям
            for (const auto& neighbor : _vertexes.find(popped)->second) {
                if (visited.find(neighbor) == visited.end()) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }

        return traversal;
    }

    // Алгоритм обхода в глубину
    void _Depth(const std::string& v, std::unordered_set<std::string>& visited,
                std::vector<std::string>& traversal) const {
        // Записываем вершину, как обойденную
        visited.insert(v);
        traversal.push_back(v);
        // Обходим всех детей по очереди
        for (const auto& neighbor : _vertexes.find(v)->second) {
            // Если мы уже были в этой вершине, то пропускаем ее
            if (visited.find(neighbor) == visited.end()) {
                _Depth(neighbor, visited, traversal);
            }
        }
    }
};


// Создаем структуру для инициализации графа с помощью регулярных выражений
InitParams ParseInit(const std::string& command) {
    static std::regex regex("[d|u] \\S+ [d|b]");
    if (std::regex_match(command, regex)) {
        InitParams params;

        switch (command[0]) {
            case 'd':
                params.Type = InitParams::Directed;
                break;
            case 'u':
                params.Type = InitParams::Undirected;
                break;
        }

        switch (command[command.size() - 1]) {
            case 'b':
                params.Way = InitParams::Breadth;
                break;
            case 'd':
                params.Way = InitParams::Depth;
                break;
        }

        params.TraverBegin = std::string{command.begin() + 2, command.end() - 2};

        return params;
    }

    throw std::invalid_argument{
        "error"
    };
}

// Читаем ребро с помощью регулярных выражений
std::pair<std::string, std::string> ParseEdge(const std::string& command) {
    static std::regex regex("\\S+ \\S+");
    if (std::regex_match(command, regex)) {
        size_t spaceIndex = command.find(' ');
        return std::make_pair(
                std::string(command.begin(), command.begin() + spaceIndex),
                std::string(command.begin() + spaceIndex + 1, command.end())
        );
    }

    throw std::invalid_argument{
        "error"
    };
}

int main() {
    InitParams params;

    // Инициализируем params
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        try {
            params = ParseInit(line);
            break;
        } catch (...) {
            std::cout << "error" << std::endl;
        }
    }

    // Читаем и добавляем ребра
    Graph G(params);
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == "EOF") {
            break;
        }
        try {
            auto edge = ParseEdge(line);
            G.AddEdge(edge.first, edge.second);
        } catch (...) {
            std::cout << "error" << std::endl;
        }
    }

    // Обходим граф и выводим обход
    auto traversal = G.Traversal();
    for (const auto& vertex : traversal) {
        std::cout << vertex << std::endl;
    }
    
    return 0;
}
