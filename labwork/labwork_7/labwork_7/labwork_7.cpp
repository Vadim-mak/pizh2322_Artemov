#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Шаблонный класс для работы с массивом
template<class T>
class MyArray {
private:
    T* arr;
    int size;
    int count;

public:
    MyArray(int n) : size(n), count(0) {
        arr = new T[size];
    }

    ~MyArray() {
        delete[] arr;
    }

    void addItem(const T& item) {
        if (count < size) {
            arr[count++] = item;
        }
    }

    T getItem(int index) const {
        if (index >= 0 && index < count) {
            return arr[index];
        }
        return T();
    }

    T min() const {
        if (count == 0) return T();

        T minVal = arr[0];
        for (int i = 1; i < count; ++i) {
            if (arr[i] < minVal) {
                minVal = arr[i];
            }
        }
        return minVal;
    }

    T max() const {
        if (count == 0) return T();

        T maxVal = arr[0];
        for (int i = 1; i < count; ++i) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }
        return maxVal;
    }
};

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

    bool operator<(const Correspondence& other) const {
        return date < other.date;
    }

    bool operator>(const Correspondence& other) const {
        return date > other.date;
    }

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

    void print() const override {
        cout << "Email === Date: " << date << ", Topic: " << topic
            << ", Sender: " << sender << ", Address: " << emailAddress
            << ", Attachment: " << (hasAttachment ? "Yes" : "No") << endl;
    }
};

int main() {
    // Использование шаблона для int
    MyArray<int> intArray(5);
    intArray.addItem(10);
    intArray.addItem(5);
    intArray.addItem(20);

    cout << "Int array - Min: " << intArray.min()
        << ", Max: " << intArray.max() << endl;

    // Использование шаблона для char
    MyArray<char> charArray(3);
    charArray.addItem('A');
    charArray.addItem('C');
    charArray.addItem('B');

    cout << "Char array - Min: " << charArray.min()
        << ", Max: " << charArray.max() << endl;

    // Использование шаблона для пользовательского класса (Email)
    MyArray<Email*> emailArray(3);
    emailArray.addItem(new Email("2023-01-15", "Meeting", "John Doe", "john@example.com", true));
    emailArray.addItem(new Email("2023-01-10", "Report", "Alice Smith", "alice@example.com", false));
    emailArray.addItem(new Email("2023-01-20", "Invoice", "Bob Brown", "bob@example.com", true));

    cout << "\n=== Email array ===" << endl;
    for (int i = 0; i < 3; ++i) {
        emailArray.getItem(i)->print();
    }

    // Освобождение памяти
    for (int i = 0; i < 3; ++i) {
        delete emailArray.getItem(i);
    }

    return 0;
}