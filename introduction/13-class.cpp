#include<iostream> 
#include<vector>
using namespace std;


class Person {
    private:
        int age;
        string name;
        
    //constructor
    
    public:
    Person(int aage, string nname) {
        age = aage;
        name = nname ;
    }
    
    int getAge() {
        return age;
    }
    
    string getName() {
        return name;
    }
    
    void setAge(int aage) {
        age = aage;
    }
    
    
};


int main() {
    /*Person a;
    a.age = 10;
    a.name = "a";
    
    
    Person b;
    b.age = 20;
    b.name = "b";
    
    cout << a.age << " " << a.name <<" " << b.age << " " << b.name << endl;*/
    
    
    Person c(15, "c");
    cout << c.getAge() << " " << c.getName() << endl;
    c.setAge(20);
    cout << c.getAge() << " " << c.getName() << endl;
    
    
    return 0;
}
