#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Correspondence {
protected:
    string date;
    string topic;
    string sender;

public:
    Correspondence() : date(""), topic(""), sender("") {}
    Correspondence(const string& d, const string& t, const string& s)
        : date(d), topic(t), sender(s) {}

    virtual ~Correspondence() {}

    string getDate() const { return date; }
    string getTopic() const { return topic; }
    string getSender() const { return sender; }

    void setDate(const string& d) { date = d; }
    void setTopic(const string& t) { topic = t; }
    void setSender(const string& s) { sender = s; }

    virtual void print() const = 0;
};

class Email : public Correspondence {
private:
    string emailAddress;
    bool hasAttachment;

public:
    Email() : Correspondence(), emailAddress(""), hasAttachment(false) {}
    Email(const string& d, const string& t, const string& s,
        const string& addr, bool attachment)
        : Correspondence(d, t, s), emailAddress(addr), hasAttachment(attachment) {}

    bool operator==(const Email& other) const {
        return date == other.date && topic == other.topic &&
            sender == other.sender && emailAddress == other.emailAddress;
    }

    void print() const override {
        cout << "Email === Date: " << date << ", Topic: " << topic
            << ", Sender: " << sender << ", Address: " << emailAddress
            << ", Attachment: " << (hasAttachment ? "Yes" : "No") << endl;
    }
};

class RegistrationJournal {
private:
    string number;
    string name;
    vector<Correspondence*> correspondenceList;

public:
    RegistrationJournal() : number(""), name("") {}
    RegistrationJournal(const string& num, const string& n) : number(num), name(n) {}

    void setNumber(const string& num) { number = num; }
    void setName(const string& n) { name = n; }

    // Оператор + для добавления корреспонденции
    RegistrationJournal& operator+(Correspondence* corr) {
        correspondenceList.push_back(corr);
        return *this;
    }

    // Префиксный ++
    RegistrationJournal& operator++() {
        correspondenceList.push_back(new Email());
        return *this;
    }

    // Постфиксный ++
    RegistrationJournal operator++(int) {
        RegistrationJournal temp = *this;
        correspondenceList.push_back(new Email());
        return temp;
    }

    // Оператор [] для доступа к элементам
    Correspondence* operator[](size_t index) {
        if (index < correspondenceList.size()) {
            return correspondenceList[index];
        }
        return nullptr;
    }

    friend ostream& operator<<(ostream& os, const RegistrationJournal& journal);

    void printAll() const {
        cout << "=== Journal Information ===" << endl;
        cout << "Number: " << number << endl;
        cout << "Name: " << name << endl;
        cout << "=== Correspondence List ===" << endl;

        for (size_t i = 0; i < correspondenceList.size(); ++i) {
            correspondenceList[i]->print();
        }
    }

    ~RegistrationJournal() {
        for (auto corr : correspondenceList) {
            delete corr;
        }
    }
};

// Глобальный оператор <<
ostream& operator<<(ostream& os, const RegistrationJournal& journal) {
    os << "Journal [" << journal.number << "] " << journal.name << " with "
        << journal.correspondenceList.size() << " items";
    return os;
}

int main() {
    Email* email1 = new Email("2023-01-15", "Meeting", "John Doe", "john@example.com", true);
    Email* email2 = new Email("2023-01-16", "Report", "Alice Smith", "alice@example.com", false);

    RegistrationJournal journal;
    journal.setNumber("J-2023-001");
    journal.setName("Main Journal");

    // Использование оператора +
    journal + email1 + email2;

    // Использование оператора ++
    ++journal;
    journal++;

    cout << "=== Using operator<< ===" << endl;
    cout << journal << endl;

    cout << "\n=== Using operator[] ===" << endl;
    if (journal[1] != nullptr) {
        journal[1]->print();
    }

    cout << "\n=== Print all ===" << endl;
    journal.printAll();

    cout << "\n=== End of program ===" << endl;
    return 0;
}