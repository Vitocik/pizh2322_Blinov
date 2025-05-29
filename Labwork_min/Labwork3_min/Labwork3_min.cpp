#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Personality {
protected:
    string name;
    string activityYear;
    string description;
public:
    Personality() {
        name = "Unknown";
        activityYear = "Unknown";
        description = "No description";
        cout << "Personality: Default constructor called\n";
    }

    Personality(string n, string y, string d) {
        name = n;
        activityYear = y;
        description = d;
        cout << "Personality: Parameterized constructor called\n";
    }

    ~Personality() {
        cout << "Personality: Destructor called for " << name << "\n";
    }

    virtual void print() {
        cout << "Name: " << name << "\n";
        cout << "Years: " << activityYear << "\n";
        cout << "Description: " << description << "\n";
    }
};

class Painter : public Personality {
    string style;
public:
    Painter() : Personality() {
        style = "Unknown";
        cout << "Painter: Default constructor called\n";
    }

    Painter(string n, string y, string d, string s) : Personality(n, y, d) {
        style = s;
        cout << "Painter: Parameterized constructor called\n";
    }

    ~Painter() {
        cout << "Painter: Destructor called for " << name << "\n";
    }

    void print() override {
        Personality::print();
        cout << "Style: " << style << "\n";
    }
};

class Writer : public Personality {
    string genre;
public:
    Writer() : Personality() {
        genre = "Unknown";
        cout << "Writer: Default constructor called\n";
    }

    Writer(string n, string y, string d, string g) : Personality(n, y, d) {
        genre = g;
        cout << "Writer: Parameterized constructor called\n";
    }

    ~Writer() {
        cout << "Writer: Destructor called for " << name << "\n";
    }

    void print() override {
        Personality::print();
        cout << "Genre: " << genre << "\n";
    }
};

int main() {
    cout << "=== Step 1: Create base and derived objects ===\n";
    Personality p1("Leonardo da Vinci", "1452-1519", "Polymath");
    Painter p2("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism");
    Writer p3("Shakespeare", "1564-1616", "Playwright and poet", "Drama");

    cout << "\n=== Step 2: Array of base class ===\n";
    Personality* arr[3];
    arr[0] = &p1;
    arr[1] = &p2;
    arr[2] = &p3;

    for (int i = 0; i < 3; i++) {
        cout << "\nPersonality #" << i + 1 << ":\n";
        arr[i]->print();
    }

    cout << "\n=== Step 3: Array of derived class ===\n";
    Painter painters[2] = {
        Painter("Picasso", "1881-1973", "Modern artist", "Cubism"),
        Painter("Monet", "1840-1926", "Impressionist painter", "Impressionism")
    };

    for (int i = 0; i < 2; i++) {
        cout << "\nPainter #" << i + 1 << ":\n";
        painters[i].print();
    }

    cout << "\n=== End of program ===\n";
    return 0;
}