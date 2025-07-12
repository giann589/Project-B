#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Person {
public:
    Person();                         // Default Constructor
    Person(string name);              // Constructor with given name

    void befriend(Person* p);         // Add friend (by pointer)
    void unfriend(Person* p);         // Remove friend (by pointer)

    string get_friend_names() const;  // Return all friend names as a string
    string get_name() const;          // Return name of person

private:
    string name;
    vector<Person*> friends;          
};


Person::Person() : name("") {}

Person::Person(string name) : name(name) {}

string Person::get_name() const {
    return name;
}

void Person::befriend(Person* p) {
    if (p == this) {
        cout << "Cannot befriend yourself." << endl;
        return;
    }

    // Avoid duplicate friends
    for (Person* f : friends) {
        if (f == p) {
            cout << name << " is already friends with " << p->get_name() << "." << endl;
            return;
        }
    }

    friends.push_back(p);
}

void Person::unfriend(Person* p) {
    auto it = find(friends.begin(), friends.end(), p);
    if (it != friends.end()) {
        friends.erase(it);
    }
    else {
        cout << name << " doesn't have " << p->get_name() << " as a friend." << endl;
    }
}

string Person::get_friend_names() const {
    if (friends.empty()) {
        cout << name << " does not have any friends listed." << endl;
        return "";
    }

    string result = "";
    for (Person* p : friends) {
        result += p->get_name() + " ";
    }
    return result;
}


int main() {
    cout << "Adding first person..." << endl;
    Person p1("Rachel");
    cout << p1.get_name() << " has been added." << endl;

    cout << "Adding second person..." << endl;
    Person p2("George");
    cout << p2.get_name() << " has been added." << endl;

    cout << "Adding third person..." << endl;
    Person p3("Richard");
    cout << p3.get_name() << " has been added." << endl;

    cout << "Check error handling if Person does not have a friend..." << endl;
    cout << p1.get_friend_names() << endl;

    cout << "Befriending person2 to person1..." << endl;
    p1.befriend(&p2);
    cout << p1.get_name() << " is now friends with " << p1.get_friend_names() << endl;

    cout << "Check error handling if Person does not have this specific friend to unfriend..." << endl;
    p1.unfriend(&p3);

    cout << "Befriending person3 to person1..." << endl;
    p1.befriend(&p3);
    cout << p1.get_name() << " is now friends with " << p1.get_friend_names() << endl;

    cout << "Unfriending person3 from person1..." << endl;
    p1.unfriend(&p3);
    cout << p1.get_name() << " friends is " << p1.get_friend_names() << endl;

    return 0;
}
