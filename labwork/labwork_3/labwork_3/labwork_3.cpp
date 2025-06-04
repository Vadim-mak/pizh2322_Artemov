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

    virtual ~Correspondence() {
        cout << "Correspondence: Destructor called" << endl;
    }

    string getDate() const { return date; }
    string getTopic() const { return topic; }
    string getSender() const { return sender; }

    void setDate(const string& d) { date = d; }
    void setTopic(const string& t) { topic = t; }
    void setSender(const string& s) { sender = s; }

    virtual void print() const {
        cout << "Date: " << date << ", Topic: " << topic
            << ", Sender: " << sender;
    }
};

// Класс-наследник 1: Электронное письмо
class Email : public Correspondence {
private:
    string emailAddress;
    bool hasAttachment;

public:
    Email() : Correspondence(), emailAddress(""), hasAttachment(false) {
        cout << "Email: Default constructor called" << endl;
    }

    Email(const string& d, const string& t, const string& s,
        const string& addr, bool attachment)
        : Correspondence(d, t, s), emailAddress(addr), hasAttachment(attachment) {
        cout << "Email: Constructor with parameters called" << endl;
    }

    ~Email() {
        cout << "Email: Destructor called" << endl;
    }

    string getEmailAddress() const { return emailAddress; }
    bool getHasAttachment() const { return hasAttachment; }

    void setEmailAddress(const string& addr) { emailAddress = addr; }
    void setHasAttachment(bool attachment) { hasAttachment = attachment; }

    void print() const override {
        Correspondence::print();
        cout << ", Email: " << emailAddress
            << ", Attachment: " << (hasAttachment ? "Yes" : "No") << endl;
    }
};

// Класс-наследник 2: Почтовое письмо
class PostalMail : public Correspondence {
private:
    string postalAddress;
    string trackingNumber;

public:
    PostalMail() : Correspondence(), postalAddress(""), trackingNumber("") {
        cout << "PostalMail: Default constructor called" << endl;
    }

    PostalMail(const string& d, const string& t, const string& s,
        const string& addr, const string& tracking)
        : Correspondence(d, t, s), postalAddress(addr), trackingNumber(tracking) {
        cout << "PostalMail: Constructor with parameters called" << endl;
    }

    ~PostalMail() {
        cout << "PostalMail: Destructor called" << endl;
    }

    string getPostalAddress() const { return postalAddress; }
    string getTrackingNumber() const { return trackingNumber; }

    void setPostalAddress(const string& addr) { postalAddress = addr; }
    void setTrackingNumber(const string& tracking) { trackingNumber = tracking; }

    void print() const override {
        Correspondence::print();
        cout << ", Postal Address: " << postalAddress
            << ", Tracking: " << trackingNumber << endl;
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

    void addCorrespondence(Correspondence* corr) {
        correspondenceList.push_back(corr);
    }

    void printAll() const {
        cout << "Journal Number: " << number << endl;
        cout << "Journal Name: " << name << endl;
        cout << "Correspondence List:" << endl;

        for (size_t i = 0; i < correspondenceList.size(); ++i) {
            cout << "  Entry " << i + 1 << ": ";
            correspondenceList[i]->print();
        }
    }

    ~RegistrationJournal() {
        for (auto corr : correspondenceList) {
            delete corr;
        }
    }
};

int main() {
    cout << "=== Step 1: Create base and derived objects ===" << endl;
    Correspondence corr1("2023-01-10", "Report", "Alice Smith");
    Email email1("2023-01-15", "Meeting", "John Doe", "john@example.com", true);
    PostalMail post1("2023-01-20", "Invoice", "Acme Inc", "123 Main St", "TR123456");

    cout << "\n=== Step 2: Create array of base class ===" << endl;
    Correspondence* arr[3];
    arr[0] = new Correspondence(corr1);
    arr[1] = new Email(email1);
    arr[2] = new PostalMail(post1);

    for (int i = 0; i < 3; ++i) {
        arr[i]->print();
    }

    cout << "\n=== Step 3: Create array of derived class ===" << endl;
    Email emailArr[2];
    emailArr[0] = email1;
    emailArr[1] = Email("2023-01-25", "Follow-up", "Jane Doe", "jane@example.com", false);

    for (int i = 0; i < 2; ++i) {
        emailArr[i].print();
    }

    cout << "\n=== Step 4: Use journal with polymorphic objects ===" << endl;
    RegistrationJournal journal;
    journal.setNumber("J-2023-001");
    journal.setName("Main Journal");

    journal.addCorrespondence(new Correspondence(corr1));
    journal.addCorrespondence(new Email(email1));
    journal.addCorrespondence(new PostalMail(post1));

    journal.printAll();

    // Cleanup
    for (int i = 0; i < 3; ++i) {
        delete arr[i];
    }

    cout << "\n=== End of program ===" << endl;
    return 0;
}