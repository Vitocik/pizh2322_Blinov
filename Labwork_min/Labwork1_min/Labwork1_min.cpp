#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Personality {
    string name;
    string activityYear;
    string description;
public:
    string getName() { return name; }
    void setName(string n) { name = n; }

    string getActivityYear() { return activityYear; }
    void setActivityYear(string y) { activityYear = y; }

    string getDescription() { return description; }
    void setDescription(string d) { description = d; }

    void setProperties() {
        string temp;
        cout << "Enter name: ";
        getline(cin, temp);
        setName(temp);

        cout << "Enter activity year: ";
        getline(cin, temp);
        setActivityYear(temp);

        cout << "Enter description: ";
        getline(cin, temp);
        setDescription(temp);
    }

    void setProperties(string n, string y, string d) {
        setName(n);
        setActivityYear(y);
        setDescription(d);
    }
};

class Encyclopedia {
    string title;
    string publishYear;
    vector<Personality> personalities;
public:
    string getTitle() { return title; }
    void setTitle(string t) { title = t; }

    string getPublishYear() { return publishYear; }
    void setPublishYear(string y) { publishYear = y; }

    void addPersonality(Personality p) {
        personalities.push_back(p);
    }

    Personality getPersonality(int index) {
        return personalities[index];
    }

    int getPersonalityCount() {
        return personalities.size();
    }
};

int main() {
    Encyclopedia enc;
    string temp;

    cout << "Enter encyclopedia title: ";
    getline(cin, temp);
    enc.setTitle(temp);

    cout << "Enter publish year: ";
    getline(cin, temp);
    enc.setPublishYear(temp);

    for (int i = 0; i < 3; i++) {
        cout << "\nEnter data for personality #" << i + 1 << ":\n";
        Personality p;
        if (i % 2 == 0) {
            p.setProperties();
        }
        else {
            string n, y, d;
            cout << "Enter name: ";
            getline(cin, n);
            cout << "Enter activity year: ";
            getline(cin, y);
            cout << "Enter description: ";
            getline(cin, d);
            p.setProperties(n, y, d);
        }
        enc.addPersonality(p);
    }

    cout << "\nEncyclopedia: " << enc.getTitle() << " (" << enc.getPublishYear() << ")\n";
    cout << "Personalities:\n";
    for (int i = 0; i < enc.getPersonalityCount(); i++) {
        Personality p = enc.getPersonality(i);
        cout << i + 1 << ". " << p.getName() << " (" << p.getActivityYear() << ")\n";
        cout << "   " << p.getDescription() << "\n";
    }

    return 0;
}