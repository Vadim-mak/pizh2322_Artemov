#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Correspondence {
protected:
    string date;
    string topic;
    string sender;

public:
    Correspondence(const string& d, const string& t, const string& s)
        : date(d), topic(t), sender(s) {}

    virtual void print() const = 0;
    virtual void saveToFile(ofstream& out) const = 0;
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

    void saveToFile(ofstream& out) const override {
        out << "Email|" << date << "|" << topic << "|" << sender << "|"
            << emailAddress << "|" << (hasAttachment ? "1" : "0") << endl;
    }
};

int main() {
    vector<Correspondence*> correspondenceList;
    correspondenceList.push_back(new Email("2023-01-15", "Meeting", "John Doe", "john@example.com", true));
    correspondenceList.push_back(new Email("2023-01-10", "Report", "Alice Smith", "alice@example.com", false));

    // Сохранение в файл
    ofstream outFile("correspondence.txt");
    if (outFile.is_open()) {
        for (const auto& item : correspondenceList) {
            item->saveToFile(outFile);
        }
        outFile.close();
    }

    // Чтение из файла
    ifstream inFile("correspondence.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << "Read from file: " << line << endl;
        }
        inFile.close();
    }

    // Освобождение памяти
    for (const auto& item : correspondenceList) {
        delete item;
    }

    return 0;
}