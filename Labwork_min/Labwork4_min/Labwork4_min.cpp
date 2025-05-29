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
    }

    Personality(string n, string y, string d) {
        name = n;
        activityYear = y;
        description = d;
    }

    virtual ~Personality() {}

    virtual void print() = 0; // Чисто виртуальная функция
};

class Painter : public Personality {
    string style;
public:
    Painter(string n, string y, string d, string s) : Personality(n, y, d) {
        style = s;
    }

    void print() override {
        cout << "PAINTER\n";
        cout << "Name: " << name << "\n";
        cout << "Years: " << activityYear << "\n";
        cout << "Style: " << style << "\n";
        cout << "Description: " << description << "\n\n";
    }
};

class Writer : public Personality {
    string genre;
public:
    Writer(string n, string y, string d, string g) : Personality(n, y, d) {
        genre = g;
    }

    void print() override {
        cout << "WRITER\n";
        cout << "Name: " << name << "\n";
        cout << "Years: " << activityYear << "\n";
        cout << "Genre: " << genre << "\n";
        cout << "Description: " << description << "\n\n";
    }
};

class Encyclopedia {
    string title;
    string publishYear;
    vector<Personality*> personalities;
public:
    Encyclopedia(string t, string y) : title(t), publishYear(y) {}

    void addPersonality(Personality* p) {
        personalities.push_back(p);
    }

    void showAll() {
        cout << "Encyclopedia: " << title << " (" << publishYear << ")\n";
        cout << "Contains " << personalities.size() << " personalities:\n\n";

        for (auto p : personalities) {
            p->print();
        }
    }
};

int main() {
    Encyclopedia enc("Great Figures", "2023");

    Painter* p1 = new Painter("Van Gogh", "1853-1890",
        "Post-Impressionist painter", "Post-Impressionism");
    Writer* p2 = new Writer("Shakespeare", "1564-1616",
        "Playwright and poet", "Drama");
    Painter* p3 = new Painter("Picasso", "1881-1973",
        "Modern artist", "Cubism");

    enc.addPersonality(p1);
    enc.addPersonality(p2);
    enc.addPersonality(p3);

    enc.showAll();

    delete p1;
    delete p2;
    delete p3;

    return 0;
}