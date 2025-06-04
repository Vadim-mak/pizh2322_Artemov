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

    virtual void print() const = 0; // Чисто виртуальная функция
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

    string getEmailAddress() const { return emailAddress; }
    bool getHasAttachment() const { return hasAttachment; }

    void setEmailAddress(const string& addr) { emailAddress = addr; }
    void setHasAttachment(bool attachment) { hasAttachment = attachment; }

    void print() const override {
        cout << "Email === Date: " << date << ", Topic: " << topic
            << ", Sender: " << sender << ", Address: " << emailAddress
            << ", Attachment: " << (hasAttachment ? "Yes" : "No") << endl;
    }
};

class PostalMail : public Correspondence {
private:
    string postalAddress;
    string trackingNumber;

public:
    PostalMail() : Correspondence(), postalAddress(""), trackingNumber("") {}
    PostalMail(const string& d, const string& t, const string& s,
        const string& addr, const string& tracking)
        : Correspondence(d, t, s), postalAddress(addr), trackingNumber(tracking) {}

    string getPostalAddress() const { return postalAddress; }
    string getTrackingNumber() const { return trackingNumber; }

    void setPostalAddress(const string& addr) { postalAddress = addr; }
    void setTrackingNumber(const string& tracking) { trackingNumber = tracking; }

    void print() const override {
        cout << "PostalMail === Date: " << date << ", Topic: " << topic
            << ", Sender: " << sender << ", Address: " << postalAddress
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

int main() {
    cout << "=== Step 1: Create derived objects ===" << endl;
    Email* email1 = new Email("2023-01-15", "Meeting", "John Doe", "john@example.com", true);
    PostalMail* post1 = new PostalMail("2023-01-20", "Invoice", "Acme Inc", "123 Main St", "TR123456");

    cout << "\n=== Step 2: Create array of base class pointers ===" << endl;
    Correspondence* arr[2];
    arr[0] = email1;
    arr[1] = post1;

    for (int i = 0; i < 2; ++i) {
        arr[i]->print();
    }

    cout << "\n=== Step 3: Use journal with polymorphic objects ===" << endl;
    RegistrationJournal journal;
    journal.setNumber("J-2023-001");
    journal.setName("Main Journal");

    journal.addCorrespondence(new Email(*email1));
    journal.addCorrespondence(new PostalMail(*post1));
    journal.addCorrespondence(new Email("2023-01-25", "Follow-up", "Jane Doe", "jane@example.com", false));

    journal.printAll();

    // Cleanup
    delete email1;
    delete post1;

    cout << "\n=== End of program ===" << endl;
    return 0;
}