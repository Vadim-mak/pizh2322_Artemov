#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Correspondence {
    string date;
    string topic;
    string sender;

public:
    Correspondence(const string& d, const string& t, const string& s)
        : date(d), topic(t), sender(s) {}

    string getTopic() const { return topic; }
    string getSender() const { return sender; }

    void print() const {
        cout << "Дата: " << date << ", Тема: " << topic << ", Отправитель: " << sender << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    cout << "=== Алгоритмы STL ===" << endl;

    vector<Correspondence> correspondenceList = {
        Correspondence("2023-01-10", "Отчет", "Иван Иванов"),
        Correspondence("2023-01-15", "Встреча", "Петр Петров"),
        Correspondence("2023-01-20", "Договор", "Сергей Сергеев")
    };

    // 1. Поиск по теме "Встреча"
    auto it = find_if(correspondenceList.begin(), correspondenceList.end(),
        [](const Correspondence& c) { return c.getTopic() == "Встреча"; });

    if (it != correspondenceList.end()) {
        cout << "\nНайдено:" << endl;
        it->print();  // Используем it->, так как it — итератор
    }

    // 2. Копирование всех записей от "Петр Петров" в новый вектор
    vector<Correspondence> filteredList;
    copy_if(correspondenceList.begin(), correspondenceList.end(), back_inserter(filteredList),
        [](const Correspondence& c) { return c.getSender() == "Петр Петров"; });

    cout << "\nФильтр по отправителю:" << endl;
    for (const auto& item : filteredList) {
        item.print();  // Используем item., так как item — объект, а не указатель
    }

    return 0;
}