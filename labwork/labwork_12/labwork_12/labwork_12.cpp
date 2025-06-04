#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Correspondence {
    string date;
    string topic;

public:
    Correspondence(const string& d, const string& t) : date(d), topic(t) {}

    string getDate() const { return date; }
    string getTopic() const { return topic; }

    void print() const {
        cout << "Дата: " << date << " | Тема: " << topic << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    cout << "=== Лямбда-функции ===" << endl;

    vector<Correspondence> correspondenceList = {
        Correspondence("2023-01-10", "Отчет"),
        Correspondence("2023-01-15", "Встреча"),
        Correspondence("2023-01-05", "План")
    };

    // Сортировка по дате с лямбдой
    sort(correspondenceList.begin(), correspondenceList.end(),
        [](const Correspondence& a, const Correspondence& b) {
            return a.getDate() < b.getDate();
        });

    cout << "\nПосле сортировки:" << endl;
    for (const auto& item : correspondenceList) {
        item.print();
    }

    // Поиск темы, содержащей "ет"
    auto result = find_if(correspondenceList.begin(), correspondenceList.end(),
        [](const Correspondence& c) {
            return c.getTopic().find("ет") != string::npos;
        });

    if (result != correspondenceList.end()) {
        cout << "\nНайдено совпадение:" << endl;
        result->print();
    }

    return 0;
}