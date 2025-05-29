#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Personality {
protected:
    string name;
    string activityYear;
    string description;
    static int count; // Статический счетчик объектов
public:
    Personality() {
        name = "Unknown";
        activityYear = "Unknown";
        description = "No description";
        count++;
    }

    Personality(string n, string y, string d) {
        name = n;
        activityYear = y;
        description = d;
        count++;
    }

    virtual ~Personality() {
        count--;
    }

    virtual void print() = 0;

    static int getCount() {
        return count;
    }
};

int Personality::count = 0;

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

class Encyclopedia {
    string title;
    string publishYear;
    vector<Personality*> personalities;
    static int count; // Статический счетчик в энциклопедии
public:
    Encyclopedia(string t, string y) : title(t), publishYear(y) {}

    void addPersonality(Personality* p) {
        personalities.push_back(p);
        count++;
    }

    void showAll() {
        cout << "Encyclopedia: " << title << " (" << publishYear << ")\n";
        cout << "Contains " << personalities.size() << " personalities:\n\n";

        for (auto p : personalities) {
            p->print();
        }
    }

    static int getPersonalityCount() {
        return count;
    }
};

int Encyclopedia::count = 0;

int main() {
    cout << "Personalities count before creation: " << Personality::getCount() << endl;
    cout << "In encyclopedia before creation: " << Encyclopedia::getPersonalityCount() << endl;

    Encyclopedia enc("Great Figures", "2023");

    Painter* p1 = new Painter("Van Gogh", "1853-1890",
        "Post-Impressionist painter", "Post-Impressionism");
    Painter* p2 = new Painter("Picasso", "1881-1973",
        "Modern artist", "Cubism");

    cout << "\nAfter creating 2 personalities: " << Personality::getCount() << endl;
    cout << "In encyclopedia after creation: " << Encyclopedia::getPersonalityCount() << endl;

    enc.addPersonality(p1);
    enc.addPersonality(p2);

    cout << "\nAfter adding to encyclopedia: " << Personality::getCount() << endl;
    cout << "In encyclopedia after adding: " << Encyclopedia::getPersonalityCount() << endl;

    enc.showAll();

    delete p1;
    delete p2;

    cout << "\nAfter deletion: " << Personality::getCount() << endl;
    cout << "In encyclopedia after deletion: " << Encyclopedia::getPersonalityCount() << endl;

    return 0;
}