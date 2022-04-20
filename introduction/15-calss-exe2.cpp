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


int get(vector<Person>& a, string name) {
    //find how many person whose age <
    return 9;
}


int main() {
    Person a(1, "a");
    Person b(2, "b");
    Person c(3, "c");
    Person d(4, "d");
    Person e(5, "e");
    
    
    Person aa(6, "aa");
    Person bb(7, "bb");
    Person cc(8, "cc");
    Person dd(9, "dd");
    Person ee(10, "ee");
   
    vector<Person> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    v.push_back(e);
    
    v.push_back(aa);
    v.push_back(bb);
    v.push_back(cc);
    v.push_back(dd);
    v.push_back(ee);
    
    
    
    int count1 = get(v, "cc");
    int count2 = get(v, "d");
    int count3 = get(v, "aa");

    return 0;
}
