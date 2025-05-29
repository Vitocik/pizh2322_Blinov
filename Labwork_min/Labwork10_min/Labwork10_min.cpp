#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

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
    map<string, vector<unique_ptr<Personality>>> byStyle;
    vector<unique_ptr<Personality>> allPersonalities;
public:
    void addPersonality(unique_ptr<Personality> p) {
        if (auto painter = dynamic_cast<Painter*>(p.get())) {
            byStyle[painter->getStyle()].push_back(move(p));
        }
        else {
            allPersonalities.push_back(move(p));
        }
    }

    void printAll() const {
        cout << "All personalities:\n";
        for (const auto& p : allPersonalities) {
            p->print();
        }

        for (const auto& pair : byStyle) {
            cout << "Style: " << pair.first << "\n";
            for (const auto& p : pair.second) {
                p->print();
            }
        }
    }

    void printByStyle(const string& style) const {
        auto it = byStyle.find(style);
        if (it != byStyle.end()) {
            cout << "Painters of style " << style << ":\n";
            for (const auto& p : it->second) {
                p->print();
            }
        }
        else {
            cout << "No painters found for style " << style << "\n";
        }
    }
};

int main() {
    Encyclopedia enc;

    enc.addPersonality(make_unique<Painter>("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism"));
    enc.addPersonality(make_unique<Painter>("Picasso", "1881-1973", "Modern artist", "Cubism"));
    enc.addPersonality(make_unique<Painter>("Monet", "1840-1926", "Impressionist painter", "Impressionism"));
    enc.addPersonality(make_unique<Painter>("Braque", "1882-1963", "Modern artist", "Cubism"));

    cout << "--- All personalities ---\n";
    enc.printAll();

    cout << "\n--- Cubism painters ---\n";
    enc.printByStyle("Cubism");

    return 0;
}