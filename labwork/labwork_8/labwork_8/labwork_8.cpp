#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Пользовательские классы исключений
class InvalidDateException : public invalid_argument {
public:
    InvalidDateException(const string& msg) : invalid_argument(msg) {}
};

class EmptyTopicException : public runtime_error {
public:
    EmptyTopicException(const string& msg) : runtime_error(msg) {}
};

class Correspondence {
protected:
    string date;
    string topic;
    string sender;

public:
    Correspondence(const string& d, const string& t, const string& s) {
        if (d.empty()) {
            throw InvalidDateException("Date cannot be empty!");
        }
        if (t.empty()) {
            throw EmptyTopicException("Topic cannot be empty!");
        }
        date = d;
        topic = t;
        sender = s;
    }

    virtual void print() const = 0;
};

class Email : public Correspondence {
private:
    string emailAddress;
    bool hasAttachment;

public:
    Email(const string& d, const string& t, const string& s,
        const string& addr, bool attachment)
        : Correspondence(d, t, s), emailAddress(addr), hasAttachment(attachment) {}

    void print() const override {
        cout << "Email === Date: " << date << ", Topic: " << topic
            << ", Sender: " << sender << ", Address: " << emailAddress
            << ", Attachment: " << (hasAttachment ? "Yes" : "No") << endl;
    }
};

int main() {
    try {
        // Попытка создать объект с неверными данными
        Email* email1 = new Email("", "Meeting", "John Doe", "john@example.com", true);
    }
    catch (const InvalidDateException& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const EmptyTopicException& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error occurred!" << endl;
    }

    // Работа с корректными данными
    try {
        Email* email2 = new Email("2023-01-15", "Report", "Alice Smith", "alice@example.com", false);
        email2->print();
        delete email2;
    }
    catch (...) {
        cerr << "Failed to create email!" << endl;
    }

    return 0;
}