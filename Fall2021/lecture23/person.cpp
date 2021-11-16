// to compile: g++ person.cpp

#include <string>
#include <iostream>

using namespace std;

class Person
{
   protected:
      int id;
      string name;
      string address;
   public:
      Person(int id, string name, string address); // constructor
      virtual ~Person();  // destructor

      virtual void displayProfile();
      // void changeAddress(string newAddress);
};

Person::Person(int id, string name, string address)
{
    cout << "entering Person constructor for " << name << endl;

     this->id = id;  // id = id
     this->name = name;
     this->address = address;
}

Person::~Person() 
{
    cout << "entering Person destructor for " << name << endl;
}

void Person::displayProfile()
{
    cout << "--------------------------" << endl;
    cout << "Name: " << name << ", ID: " << id;
    cout << ", Address: " << address << endl;
    cout << "--------------------------" << endl;
}


class Student : public Person
{
    protected:
      int course;
      int year; // 1 - f, 2- s...
      // vector <int> classTaken;

    public:
      Student(int id, string name, string address, int course, int year);
      ~Student();

      void displayProfile();
      void updateYear(int newyear);
      //void addCourseTaken(int course);
};

Student::Student(int id, string name, string address, int course, int year) : Person(id, name, address)
{
    cout << "entering Student constructor for " << name << endl;

    this->course = course;
    this->year = year;
}


Student::~Student() 
{
    cout << "entering Student destructor for " << name << endl;
}

void Student::displayProfile()
{
    cout << "--------------------------" << endl;
    cout << "Name: " << name << ", ID: " << id;
    cout << ", Address: " << address << endl;
    cout << "Course: " << course << ", year: " << year << endl;
    cout << "--------------------------" << endl;

}

void Student::updateYear(int newyear) 
{
    this->year = newyear;
}



int main()
{
    cout << endl << "inheritance" << endl;

    Person *john = new Person(12345, "John Doe", "123 University Ave."); 
    john->displayProfile();
    delete john;

    cout << endl;

    Student *james = new Student(45678, "James Lee", "32 Lincoln Ave.", 6, 2);
    james->displayProfile();
    delete james;


    cout << endl << "polymorphism" <<endl;

    Person *jim = new Person(12345, "Jim Doe", "123 University Ave."); 
    Person *dan = new Student(45678, "Dan", "99 N. Lincoln", 7, 3);

    john->displayProfile();

    cout << endl;

    dan->displayProfile();

    delete dan;


    cout << endl << "type casting" <<endl;

    Person *steve = new Student(45678, "Steve", "99 N. Lincoln", 7, 3);

    //steve->updateYear(4);  // will not work 

    Student *steve2 = dynamic_cast<Student*>(steve);
    steve2->updateYear(4); 

    delete steve2;
}
    

