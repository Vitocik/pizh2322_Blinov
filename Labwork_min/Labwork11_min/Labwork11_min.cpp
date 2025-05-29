#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Personality {
protected:
    string name;
    string activityYear;
    string description;
public:
    Personality(string n, string y, string d) : name(n), activityYear(y), description(d) {}
    virtual ~Personality() {}

    virtual void print() const = 0;
    const string& getName() const { return name; }
    const string& getYears() const { return activityYear; }

    bool operator<(const Personality& other) const { return name < other.name; }
};

class Painter : public Personality {
    string style;
public:
    Painter(string n, string y, string d, string s) : Personality(n, y, d), style(s) {}

    void print() const override {
        cout << "PAINTER\nName: " << name << "\nYears: " << activityYear
            << "\nStyle: " << style << "\nDescription: " << description << "\n\n";
    }

    const string& getStyle() const { return style; }
};

class Encyclopedia {
    vector<unique_ptr<Personality>> personalities;
public:
    void addPersonality(unique_ptr<Personality> p) {
        personalities.push_back(move(p));
    }

    void sortByName() {
        sort(personalities.begin(), personalities.end(),
            [](const unique_ptr<Personality>& a, const unique_ptr<Personality>& b) {
                return *a < *b;
            });
    }

    void sortByYear() {
        sort(personalities.begin(), personalities.end(),
            [](const unique_ptr<Personality>& a, const unique_ptr<Personality>& b) {
                return a->getYears() < b->getYears();
            });
    }

    set<string> getAllStyles() const {
        set<string> styles;
        for (const auto& p : personalities) {
            if (auto painter = dynamic_cast<const Painter*>(p.get())) {
                styles.insert(painter->getStyle());
            }
        }
        return styles;
    }

    vector<const Personality*> findByStyle(const string& style) const {
        vector<const Personality*> result;
        for (const auto& p : personalities) {
            if (auto painter = dynamic_cast<const Painter*>(p.get())) {
                if (painter->getStyle() == style) {
                    result.push_back(p.get());
                }
            }
        }
        return result;
    }

    void printAll() const {
        for (const auto& p : personalities) {
            p->print();
        }
    }
};

int main() {
    Encyclopedia enc;

    enc.addPersonality(make_unique<Painter>("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism"));
    enc.addPersonality(make_unique<Painter>("Picasso", "1881-1973", "Modern artist", "Cubism"));
    enc.addPersonality(make_unique<Painter>("Monet", "1840-1926", "Impressionist painter", "Impressionism"));
    enc.addPersonality(make_unique<Painter>("Braque", "1882-1963", "Modern artist", "Cubism"));

    cout << "--- Unsorted ---\n";
    enc.printAll();

    cout << "\n--- Sorted by name ---\n";
    enc.sortByName();
    enc.printAll();

    cout << "\n--- Sorted by year ---\n";
    enc.sortByYear();
    enc.printAll();

    cout << "\n--- All styles ---\n";
    auto styles = enc.getAllStyles();
    for (const auto& style : styles) {
        cout << style << "\n";
    }

    cout << "\n--- Cubism painters ---\n";
    auto cubists = enc.findByStyle("Cubism");
    for (const auto p : cubists) {
        p->print();
    }

    return 0;
}