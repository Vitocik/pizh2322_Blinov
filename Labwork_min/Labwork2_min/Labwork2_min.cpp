#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Personality {
    string name;
    string activityYear;
    string description;
public:
    // Конструкторы
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

    Personality(const Personality& p) {
        name = p.name;
        activityYear = p.activityYear;
        description = p.description;
        cout << "Personality: Copy constructor called\n";
    }

    // Деструктор
    ~Personality() {
        cout << "Personality: Destructor called for " << name << "\n";
    }

    // Методы доступа
    string getName() { return name; }
    void setName(string n) { name = n; }

    string getActivityYear() { return activityYear; }
    void setActivityYear(string y) { activityYear = y; }

    string getDescription() { return description; }
    void setDescription(string d) { description = d; }
};

class Encyclopedia {
    string title;
    string publishYear;
    vector<Personality> personalities;
public:
    // Конструкторы
    Encyclopedia() {
        title = "Untitled";
        publishYear = "Unknown";
        cout << "Encyclopedia: Default constructor called\n";
    }

    Encyclopedia(string t, string y) {
        title = t;
        publishYear = y;
        cout << "Encyclopedia: Parameterized constructor called\n";
    }

    Encyclopedia(const Encyclopedia& e) {
        title = e.title;
        publishYear = e.publishYear;
        personalities = e.personalities;
        cout << "Encyclopedia: Copy constructor called\n";
    }

    // Деструктор
    ~Encyclopedia() {
        cout << "Encyclopedia: Destructor called for " << title << "\n";
    }

    // Методы
    string getTitle() { return title; }
    void setTitle(string t) { title = t; }

    string getPublishYear() { return publishYear; }
    void setPublishYear(string y) { publishYear = y; }

    void addPersonality(Personality p) {
        personalities.push_back(p);
    }

    void addNewPersonality(string n, string y, string d) {
        Personality p(n, y, d);
        personalities.push_back(p);
    }

    void addCopyPersonality(Personality& p, int count) {
        for (int i = 0; i < count && i < 10; i++) {
            Personality newP(p);
            personalities.push_back(newP);
        }
    }

    Personality getPersonality(int index) {
        return personalities[index];
    }

    int getPersonalityCount() {
        return personalities.size();
    }
};

int main() {
    cout << "=== Step 1: Create encyclopedia objects ===\n";
    Encyclopedia enc1;
    Encyclopedia enc2("Great History", "2020");
    Encyclopedia enc3(enc2);

    cout << "\n=== Step 2: Create personality objects ===\n";
    Personality p1;
    Personality p2("Napoleon", "1769-1821", "French military leader");
    Personality p3(p2);

    cout << "\n=== Step 3: Add personalities to encyclopedia ===\n";
    enc1.addNewPersonality("Einstein", "1879-1955", "Physicist");
    enc2.addCopyPersonality(p2, 2);

    cout << "\n=== Step 4: Show contents ===\n";
    cout << "Encyclopedia 1: " << enc1.getTitle() << " (" << enc1.getPublishYear() << ")\n";
    cout << "Contains " << enc1.getPersonalityCount() << " personalities\n";

    cout << "\nEncyclopedia 2: " << enc2.getTitle() << " (" << enc2.getPublishYear() << ")\n";
    cout << "Contains " << enc2.getPersonalityCount() << " personalities\n";

    cout << "\n=== End of program ===\n";
    return 0;
}