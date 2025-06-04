#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Дополнительный класс - Корреспонденция
class Correspondence {
private:
    string date;
    string topic;
    string sender;

public:
    // Методы доступа
    string getDate() const { return date; }
    string getTopic() const { return topic; }
    string getSender() const { return sender; }

    void setDate(const string& d) { date = d; }
    void setTopic(const string& t) { topic = t; }
    void setSender(const string& s) { sender = s; }

    // Перегруженные методы
    void setProperties() {
        cout << "Enter date: ";
        getline(cin, date);
        cout << "Enter topic: ";
        getline(cin, topic);
        cout << "Enter sender: ";
        getline(cin, sender);
    }

    void setProperties(const string& d, const string& t, const string& s) {
        date = d;
        topic = t;
        sender = s;
    }
};

// Основной класс - Журнал регистрации
class RegistrationJournal {
private:
    string number;
    string name;
    vector<Correspondence> correspondenceList;

public:
    // Методы доступа
    string getNumber() const { return number; }
    string getName() const { return name; }

    void setNumber(const string& num) { number = num; }
    void setName(const string& n) { name = n; }

    // Метод для добавления корреспонденции
    void addCorrespondence(const Correspondence& corr) {
        correspondenceList.push_back(corr);
    }

    // Метод для получения корреспонденции по индексу
    Correspondence getCorrespondence(int index) const {
        if (index >= 0 && index < correspondenceList.size()) {
            return correspondenceList[index];
        }
        return Correspondence();
    }

    // Метод для вывода всех данных
    void printAll() const {
        cout << "Journal Number: " << number << endl;
        cout << "Journal Name: " << name << endl;
        cout << "Correspondence List:" << endl;

        for (size_t i = 0; i < correspondenceList.size(); ++i) {
            cout << "  Entry " << i + 1 << ":" << endl;
            cout << "    Date: " << correspondenceList[i].getDate() << endl;
            cout << "    Topic: " << correspondenceList[i].getTopic() << endl;
            cout << "    Sender: " << correspondenceList[i].getSender() << endl;
        }
    }
};

int main() {
    RegistrationJournal journal;
    string input;

    // Ввод данных основного класса
    cout << "Enter journal number: ";
    getline(cin, input);
    journal.setNumber(input);

    cout << "Enter journal name: ";
    getline(cin, input);
    journal.setName(input);

    // Ввод данных дополнительного класса
    for (int i = 0; i < 3; ++i) {
        Correspondence corr;
        cout << "\nEnter data for correspondence #" << i + 1 << ":" << endl;

        if (i % 2 == 0) {
            // Использование первого метода setProperties
            corr.setProperties();
        }
        else {
            // Использование второго метода setProperties
            string date, topic, sender;
            cout << "Enter date: ";
            getline(cin, date);
            cout << "Enter topic: ";
            getline(cin, topic);
            cout << "Enter sender: ";
            getline(cin, sender);
            corr.setProperties(date, topic, sender);
        }

        journal.addCorrespondence(corr);
    }

    // Вывод всех данных
    cout << "\nJournal Information:" << endl;
    journal.printAll();

    return 0;
}