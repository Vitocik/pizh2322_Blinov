#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Personality {
protected:
    string name;
    string activityYear;
    string description;
    static int count;
public:
    Personality() : name("Unknown"), activityYear("Unknown"), description("No description") { count++; }
    Personality(string n, string y, string d) : name(n), activityYear(y), description(d) { count++; }
    virtual ~Personality() { count--; }

    virtual void print() const = 0;
    virtual bool operator<(const Personality& other) const { return name < other.name; }
    virtual bool operator==(const Personality& other) const { return name == other.name; }

    static int getCount() { return count; }
};

int Personality::count = 0;

class Painter : public Personality {
    string style;
public:
    Painter(string n, string y, string d, string s) : Personality(n, y, d), style(s) {}

    void print() const override {
        cout << "PAINTER\nName: " << name << "\nYears: " << activityYear
            << "\nStyle: " << style << "\nDescription: " << description << "\n\n";
    }

    bool operator<(const Personality& other) const override {
        const Painter* p = dynamic_cast<const Painter*>(&other);
        if (p) return style < p->style;
        return Personality::operator<(other);
    }
};

class Encyclopedia {
    string title;
    string publishYear;
    vector<Personality*> personalities;
    static int count;
public:
    Encyclopedia(string t, string y) : title(t), publishYear(y) {}
    ~Encyclopedia() {
        for (auto p : personalities) delete p;
    }

    Encyclopedia& operator+=(Personality* p) {
        personalities.push_back(p);
        count++;
        return *this;
    }

    Personality* operator[](size_t index) {
        if (index >= personalities.size()) throw out_of_range("Index out of range");
        return personalities[index];
    }

    void showAll() const {
        cout << "Encyclopedia: " << title << " (" << publishYear << ")\n";
        cout << "Contains " << personalities.size() << " personalities:\n\n";
        for (auto p : personalities) p->print();
    }

    static int getPersonalityCount() { return count; }

    // Добавленные геттеры
    string getTitle() const { return title; }
    string getPublishYear() const { return publishYear; }
};

int Encyclopedia::count = 0;

std::ostream& operator<<(ostream& os, const Encyclopedia& enc) {
    os << "Encyclopedia \"" << enc.getTitle() << "\" (" << enc.getPublishYear() << ")";
    return os;
}

int main() {
    Encyclopedia enc("Great Figures", "2023");

    enc += new Painter("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism");
    enc += new Painter("Picasso", "1881-1973", "Modern artist", "Cubism");

    cout << enc << endl;
    enc.showAll();

    try {
        cout << "First personality: ";
        enc[0]->print();
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}