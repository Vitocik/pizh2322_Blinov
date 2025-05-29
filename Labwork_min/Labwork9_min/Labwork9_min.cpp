#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

using namespace std;

class Personality {
protected:
    string name;
    string activityYear;
    string description;
public:
    Personality() : name("Unknown"), activityYear("Unknown"), description("No description") {}
    Personality(string n, string y, string d) : name(n), activityYear(y), description(d) {}
    virtual ~Personality() {}

    virtual void print() const = 0;

    friend ostream& operator<<(ostream& os, const Personality& p);
    friend istream& operator>>(istream& is, Personality& p);
};

ostream& operator<<(ostream& os, const Personality& p) {
    os << p.name << "\n" << p.activityYear << "\n" << p.description << "\n";
    return os;
}

istream& operator>>(istream& is, Personality& p) {
    getline(is, p.name);
    getline(is, p.activityYear);
    getline(is, p.description);
    return is;
}

class Painter : public Personality {
    string style;
public:
    Painter() : Personality(), style("Unknown") {}
    Painter(string n, string y, string d, string s) : Personality(n, y, d), style(s) {}

    void print() const override {
        cout << "PAINTER\nName: " << name << "\nYears: " << activityYear
            << "\nStyle: " << style << "\nDescription: " << description << "\n\n";
    }

    friend ostream& operator<<(ostream& os, const Painter& p);
    friend istream& operator>>(istream& is, Painter& p);
};

ostream& operator<<(ostream& os, const Painter& p) {
    os << static_cast<const Personality&>(p) << p.style << "\n";
    return os;
}

istream& operator>>(istream& is, Painter& p) {
    is >> static_cast<Personality&>(p);
    getline(is, p.style);
    return is;
}

class Encyclopedia {
    string title;
    vector<unique_ptr<Personality>> personalities;
public:
    Encyclopedia(string t) : title(t) {}

    void addPersonality(unique_ptr<Personality> p) {
        personalities.push_back(move(p));
    }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) throw runtime_error("Cannot open file for writing");

        out << title << "\n";
        out << personalities.size() << "\n";

        for (const auto& p : personalities) {
            if (auto painter = dynamic_cast<const Painter*>(p.get())) {
                out << *painter;
            }
        }
    }

    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) throw runtime_error("Cannot open file for reading");

        personalities.clear();
        getline(in, title);

        size_t count;
        in >> count;
        in.ignore();

        for (size_t i = 0; i < count; ++i) {
            auto painter = make_unique<Painter>();
            in >> *painter;
            addPersonality(move(painter));
        }
    }

    void printAll() const {
        cout << "Encyclopedia: " << title << "\n\n";
        for (const auto& p : personalities) {
            p->print();
        }
    }
};

int main() {
    Encyclopedia enc("Great Painters");
    enc.addPersonality(make_unique<Painter>("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism"));
    enc.addPersonality(make_unique<Painter>("Picasso", "1881-1973", "Modern artist", "Cubism"));

    const string filename = "encyclopedia.txt";

    try {
        enc.saveToFile(filename);
        cout << "Saved to file successfully\n";

        Encyclopedia loadedEnc("Empty");
        loadedEnc.loadFromFile(filename);
        cout << "\nLoaded from file:\n";
        loadedEnc.printAll();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}