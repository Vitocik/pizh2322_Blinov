#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Базовый класс Personality из предыдущих работ
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
    virtual bool operator<(const Personality& other) const { return name < other.name; }
    virtual bool operator==(const Personality& other) const { return name == other.name; }
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

template<typename T>
class EncyclopediaContainer {
    vector<T*> items;
public:
    ~EncyclopediaContainer() {
        for (auto item : items) delete item;
    }

    void addItem(T* item) { items.push_back(item); }

    T* getItem(size_t index) const {
        if (index >= items.size()) throw out_of_range("Index out of range");
        return items[index];
    }

    size_t size() const { return items.size(); }

    T* findMin() const {
        if (items.empty()) return nullptr;
        return *min_element(items.begin(), items.end(),
            [](const T* a, const T* b) { return *a < *b; });
    }

    T* findMax() const {
        if (items.empty()) return nullptr;
        return *max_element(items.begin(), items.end(),
            [](const T* a, const T* b) { return *a < *b; });
    }

    void printAll() const {
        for (auto item : items) item->print();
    }
};

int main() {
    EncyclopediaContainer<Personality> enc;

    enc.addItem(new Painter("Van Gogh", "1853-1890", "Post-Impressionist painter", "Post-Impressionism"));
    enc.addItem(new Painter("Picasso", "1881-1973", "Modern artist", "Cubism"));
    enc.addItem(new Painter("Da Vinci", "1452-1519", "Renaissance genius", "Renaissance"));

    cout << "All personalities:\n";
    enc.printAll();

    auto minPerson = enc.findMin();
    auto maxPerson = enc.findMax();

    cout << "\nFirst by name:\n";
    if (minPerson) minPerson->print();

    cout << "\nLast by name:\n";
    if (maxPerson) maxPerson->print();

    return 0;
}