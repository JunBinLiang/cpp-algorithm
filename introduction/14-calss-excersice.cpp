#include<iostream> 
#include<vector> 
using namespace std;


class Person {
    public : 
        int age;
        string name;
        Person(int aage, string nname) {
            age = aage;
            name = nname;
        }
        
        string getName() {
            return name;
        }
    
};


vector<string> get(vector<Person>& a, int minimumAge) {
    //find all people's name whose age >= minimumAge
    return {};
}


int main() {
    Person a(1, "a");
    Person b(2, "b");
    Person c(3, "c");
    Person d(4, "d");
    Person e(5, "e");
   
    vector<Person> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    v.push_back(e);
    
    
    vector<string> allNames = get(v, 3);
    for(int i = 0; i < allNames.size(); i++) {
        cout << allNames[i] << endl; 
    }


    return 0;
}
