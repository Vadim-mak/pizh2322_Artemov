#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Correspondence {
private:
    string date;
    string topic;
    string sender;

public:
    // Конструкторы
    Correspondence() : date(""), topic(""), sender("") {
        cout << "Correspondence: Default constructor called" << endl;
    }

    Correspondence(const string& d, const string& t, const string& s)
        : date(d), topic(t), sender(s) {
        cout << "Correspondence: Constructor with parameters called" << endl;
    }

    Correspondence(const Correspondence& other)
        : date(other.date), topic(other.topic), sender(other.sender) {
        cout << "Correspondence: Copy constructor called" << endl;
    }

    // Деструктор
    ~Correspondence() {
        cout << "Correspondence: Destructor called" << endl;
    }

    // Методы доступа
    string getDate() const { return date; }
    string getTopic() const { return topic; }
    string getSender() const { return sender; }

    void setDate(const string& d) { date = d; }
    void setTopic(const string& t) { topic = t; }
    void setSender(const string& s) { sender = s; }
};

class RegistrationJournal {
private:
    string number;
    string name;
    vector<Correspondence> correspondenceList;

public:
    // Конструкторы
    RegistrationJournal() : number(""), name("") {
        cout << "RegistrationJournal: Default constructor called" << endl;
    }

    RegistrationJournal(const string& num, const string& n)
        : number(num), name(n) {
        cout << "RegistrationJournal: Constructor with parameters called" << endl;
    }

    RegistrationJournal(const RegistrationJournal& other)
        : number(other.number), name(other.name), correspondenceList(other.correspondenceList) {
        cout << "RegistrationJournal: Copy constructor called" << endl;
    }

    // Деструктор
    ~RegistrationJournal() {
        cout << "RegistrationJournal: Destructor called" << endl;
    }

    // Методы доступа
    string getNumber() const { return number; }
    string getName() const { return name; }

    void setNumber(const string& num) { number = num; }
    void setName(const string& n) { name = n; }

    // Метод для добавления корреспонденции
    void addCorrespondence(const Correspondence& corr) {
        correspondenceList.push_back(corr);
    }

    // Новый метод для создания и добавления корреспонденции
    void addNewCorrespondence(const string& date, const string& topic, const string& sender, int index) {
        if (index >= 0 && index < 10) {
            Correspondence corr(date, topic, sender);
            correspondenceList.push_back(corr);
        }
    }

    // Новый метод для создания копий корреспонденции
    void addCopiesOfCorrespondence(const Correspondence& corr, int count) {
        for (int i = 0; i < count && correspondenceList.size() < 10; ++i) {
            Correspondence newCorr(corr); // Используем конструктор копирования
            correspondenceList.push_back(newCorr);
        }
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
    cout << "=== Step 1: Create journal objects ===" << endl;
    RegistrationJournal journal1;
    RegistrationJournal journal2("J-2023-001", "Main Journal");
    RegistrationJournal journal3(journal2);

    cout << "\n=== Step 2: Create correspondence objects ===" << endl;
    Correspondence corr1;
    Correspondence corr2("2023-01-15", "Meeting", "John Doe");

    cout << "\n=== Step 3: Add correspondences ===" << endl;
    journal1.addNewCorrespondence("2023-01-10", "Report", "Alice Smith", 0);
    journal2.addCopiesOfCorrespondence(corr2, 2);

    cout << "\n=== Step 4: Print information ===" << endl;
    cout << "Journal 2:" << endl;
    journal2.printAll();

    cout << "\n=== End of program ===" << endl;
    return 0;
}