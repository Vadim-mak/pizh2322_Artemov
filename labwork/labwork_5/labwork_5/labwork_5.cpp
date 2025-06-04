#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Correspondence {
protected:
    string date;
    string topic;
    string sender;
    static int count; // Статический счетчик объектов

public:
    Correspondence() : date(""), topic(""), sender("") {
        count++;
        cout << "Correspondence created. Total: " << count << endl;
    }

    Correspondence(const string& d, const string& t, const string& s)
        : date(d), topic(t), sender(s) {
        count++;
        cout << "Correspondence created. Total: " << count << endl;
    }

    Correspondence(const Correspondence& other)
        : date(other.date), topic(other.topic), sender(other.sender) {
        count++;
        cout << "Correspondence created. Total: " << count << endl;
    }

    virtual ~Correspondence() {
        count--;
        cout << "Correspondence destroyed. Remaining: " << count << endl;
    }

    static int getCount() { return count; }

    virtual void print() const = 0;
};

int Correspondence::count = 0;

class Email : public Correspondence {
private:
    string emailAddress;
    bool hasAttachment;

public:
    Email() : Correspondence(), emailAddress(""), hasAttachment(false) {}
    Email(const string& d, const string& t, const string& s,
        const string& addr, bool attachment)
        : Correspondence(d, t, s), emailAddress(addr), hasAttachment(attachment) {}

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
    static int itemsInJournal; // Статический счетчик элементов в журнале

public:
    RegistrationJournal() : number(""), name("") {}
    RegistrationJournal(const string& num, const string& n) : number(num), name(n) {}

    void setNumber(const string& num) { number = num; }
    void setName(const string& n) { name = n; }

    void addCorrespondence(Correspondence* corr) {
        correspondenceList.push_back(corr);
        itemsInJournal++;
    }

    static int getItemsCount() { return itemsInJournal; }

    void printAll() const {
        cout << "=== Journal Information ===" << endl;
        cout << "Number: " << number << endl;
        cout << "Name: " << name << endl;
        cout << "Items in journal: " << itemsInJournal << endl;
        cout << "Total correspondences: " << Correspondence::getCount() << endl;
        cout << "=== Correspondence List ===" << endl;

        for (size_t i = 0; i < correspondenceList.size(); ++i) {
            correspondenceList[i]->print();
        }
    }

    ~RegistrationJournal() {
        for (auto corr : correspondenceList) {
            delete corr;
            itemsInJournal--;
        }
    }
};

int RegistrationJournal::itemsInJournal = 0;

int main() {
    cout << "=== Initial counts ===" << endl;
    cout << "Total correspondences: " << Correspondence::getCount() << endl;
    cout << "Items in journals: " << RegistrationJournal::getItemsCount() << endl;

    cout << "\n=== Step 1: Create objects ===" << endl;
    Email* email1 = new Email("2023-01-15", "Meeting", "John Doe", "john@example.com", true);
    Email* email2 = new Email("2023-01-16", "Report", "Alice Smith", "alice@example.com", false);

    cout << "\n=== Step 2: Create journal and add items ===" << endl;
    RegistrationJournal journal;
    journal.setNumber("J-2023-001");
    journal.setName("Main Journal");

    journal.addCorrespondence(email1);
    journal.addCorrespondence(email2);

    cout << "\n=== Current counts ===" << endl;
    cout << "Total correspondences: " << Correspondence::getCount() << endl;
    cout << "Items in journals: " << RegistrationJournal::getItemsCount() << endl;

    cout << "\n=== Step 3: Print journal ===" << endl;
    journal.printAll();

    cout << "\n=== End of program ===" << endl;
    return 0;
}