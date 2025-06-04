#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Базовый класс - Корреспонденция
class Correspondence {
protected:
    string date;
    string topic;
    string sender;

public:
    Correspondence(const string& d, const string& t, const string& s)
        : date(d), topic(t), sender(s) {}

    virtual ~Correspondence() {}

    string getDate() const { return date; }
    string getTopic() const { return topic; }
    string getSender() const { return sender; }

    virtual void print() const {
        cout << "Дата: " << date << ", Тема: " << topic << ", Отправитель: " << sender;
    }

    // Для сортировки по дате
    bool operator<(const Correspondence& other) const {
        return date < other.date;
    }
};

// Производный класс - Электронное письмо
class Email : public Correspondence {
    string email;
    bool hasAttachment;

public:
    Email(const string& d, const string& t, const string& s, const string& e, bool att)
        : Correspondence(d, t, s), email(e), hasAttachment(att) {}

    void print() const override {
        Correspondence::print();
        cout << ", Email: " << email << ", Вложение: " << (hasAttachment ? "Да" : "Нет") << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    cout << "=== Демонстрация контейнеров STL ===" << endl;

    // 1. Вектор
    vector<Correspondence*> correspondenceVec;
    correspondenceVec.push_back(new Email("2023-01-10", "Отчет", "Иван Иванов", "ivan@mail.ru", false));
    correspondenceVec.push_back(new Email("2023-01-15", "Встреча", "Петр Петров", "petr@mail.ru", true));

    cout << "\nСодержимое вектора:" << endl;
    for (const auto& item : correspondenceVec) {
        item->print();
    }

    // 2. Сортировка вектора по дате
    sort(correspondenceVec.begin(), correspondenceVec.end(),
        [](Correspondence* a, Correspondence* b) { return *a < *b; });

    cout << "\nПосле сортировки по дате:" << endl;
    for (const auto& item : correspondenceVec) {
        item->print();
    }

    // Очистка памяти
    for (auto& item : correspondenceVec) {
        delete item;
    }

    return 0;
}