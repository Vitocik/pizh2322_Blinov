#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class PersonalityException : public runtime_error {
public:
    PersonalityException(const string& msg) : runtime_error(msg) {}
};

class EmptyNameException : public PersonalityException {
public:
    EmptyNameException() : PersonalityException("Name cannot be empty") {}
};

class Personality {
protected:
    string name;
    string activityYear;
    string description;
public:
    Personality(string n, string y, string d) {
        if (n.empty()) throw EmptyNameException();
        name = n;
        activityYear = y;
        description = d;
    }

    virtual void print() const = 0;
};

class Painter : public Personality {
    string style;
public:
    Painter(string n, string y, string d, string s) : Personality(n, y, d), style(s) {}

    void print() const override {
        cout << "PAINTER\nName: " << name << "\nYears: " << activityYear
            << "\nStyle: " << style << "\nDescription: " << description << "\n\n";
    }
};

class Encyclopedia {
    vector<Personality*> personalities;
public:
    ~Encyclopedia() {
        for (auto p : personalities) delete p;
    }

    void addPersonality(Personality* p) {
        personalities.push_back(p);
    }

    void printAll() const {
        for (auto p : personalities) p->print();
    }
};

int main() {
    Encyclopedia enc;

    try {
        enc.addPersonality(new Painter("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism"));
        enc.addPersonality(new Painter("", "1881-1973", "Modern artist", "Cubism")); // Это вызовет исключение
    }
    catch (const EmptyNameException& e) {
        cerr << "Error adding personality: " << e.what() << endl;
    }
    catch (const PersonalityException& e) {
        cerr << "Personality error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "General error: " << e.what() << endl;
    }

    cout << "\nEncyclopedia contents:\n";
    enc.printAll();

    return 0;
}