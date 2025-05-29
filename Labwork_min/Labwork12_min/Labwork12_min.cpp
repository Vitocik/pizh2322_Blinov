#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>  // Добавлен этот заголовочный файл
#include <memory>      // Для std::unique_ptr

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
    vector<unique_ptr<Personality>> personalities;
public:
    void addPersonality(unique_ptr<Personality> p) {
        personalities.push_back(move(p));
    }

    void processPersonalities(const function<void(const Personality&)>& processor) const {
        for (const auto& p : personalities) {
            processor(*p);
        }
    }

    void filterAndPrint(const function<bool(const Personality&)>& filter) const {
        cout << "Filtered personalities:\n";
        for (const auto& p : personalities) {
            if (filter(*p)) {
                p->print();
            }
        }
    }
};

int main() {
    Encyclopedia enc;

    enc.addPersonality(make_unique<Painter>("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism"));
    enc.addPersonality(make_unique<Painter>("Picasso", "1881-1973", "Modern artist", "Cubism"));
    enc.addPersonality(make_unique<Painter>("Monet", "1840-1926", "Impressionist painter", "Impressionism"));
    enc.addPersonality(make_unique<Painter>("Braque", "1882-1963", "Modern artist", "Cubism"));

    // Лямбда для вывода всех личностей
    cout << "--- All personalities ---\n";
    enc.processPersonalities([](const Personality& p) {
        p.print();
        });

    // Лямбда для фильтрации по стилю
    string searchStyle = "Cubism";
    cout << "\n--- " << searchStyle << " painters ---\n";
    enc.filterAndPrint([&searchStyle](const Personality& p) {
        if (auto painter = dynamic_cast<const Painter*>(&p)) {
            return painter->getStyle() == searchStyle;
        }
        return false;
        });

    // Лямбда для поиска по году
    string startYear = "1850";
    string endYear = "1900";
    cout << "\n--- Painters active between " << startYear << " and " << endYear << " ---\n";
    enc.filterAndPrint([&startYear, &endYear](const Personality& p) {
        return p.getYears() >= startYear && p.getYears() <= endYear;
        });

    return 0;
}