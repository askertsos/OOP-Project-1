#include <iostream>
#include <string>

class School; //Prepei na dhlw8ei edw gia na 3eroun kapoies synarthseis ti shmainei o typos School

class Student{
    std::string name;
    bool isOutside;
    bool isInClass;
    int numoffloor;
    int numofclass;
public:
    Student();
    ~Student();
    
    Student copyStudent(Student& );
    void setData(std::string ,int ,int );
    void changeIsOutside();
    void changeIsInClass();

    void print();
    bool getIsOutside();
    bool getIsInClass();
    std::string getName();
    int getCfloor();
    int getCclass();
};

class Teacher{
    std::string name;
    int numoffloor;
    int numofclass;
    bool IsInClass;
public:
    Teacher();
    ~Teacher();

    void setData();
    Teacher* place();
    
    std::string getName();
    void print();
    int getNumoffloor();
    int getNumofclass();
    bool getIsinclass();
};

class Schoolyard{
    int C; //max number of students in yard at a time
    int Cnow; //current number of students in yard
    bool isFull; //Deixnei an einai gematos h oxi o xwros
    Student* students; //Pinakas ma8htwn pou einai twra sthn aulh
public:
    ~Schoolyard();

    void setC(int );
    void enter(Student );
    void exit(Student );

    void print();
    bool getIsFull();
    int getCnow();
    int getC();
    Student* getStudent();
};

class Staircase{
    int C; //max number of students in yard at a time
    int Cnow; //current number of students in yard
    bool isFull; //Deixnei an einai gematos h oxi o xwros
    Student* students; //Pinakas ma8htwn pou einai twra sthn aulh
public:
    ~Staircase();

    void setC(int );
    void enter(Student );
    void exit(Student );

    void print();
    bool getIsFull();
    int getCnow();
    int getC();
    Student* getStudent();
};

class Corridor{
    int C; //max number of students in yard at a time
    int Cnow; //current number of students in yard
    bool isFull; //Deixnei an einai gematos h oxi o xwros
    Student* students; //Pinakas ma8htwn pou einai twra sthn aulh
public:
    ~Corridor();

    void setC(int );
    void enter(Student );
    void exit(Student );

    void print();
    bool getIsFull();
    int getCnow();
    int getC();
    Student* getStudent();
};

class Class{
    int C; //max number of students in yard at a time
    int Cnow; //current number of students in yard
    bool isFull;
    Student* students; //Pinakas ma8htwn pou einai twra sthn aulh
    Teacher teacher;
public: 
    ~Class();

    void setC(int );
    void setTeacher(Teacher& );
    void changeIsFull();
    void enter(Student );

    void print(int );
    bool getIsFull();
    int getCnow();
};

class Floor{
    Class classes[6];
    Corridor corridor;
    Student* students;
    int Cnow;
public:
    ~Floor();

    void setC(int ,int );
    void enter(Student );
    void exit();

    void print(int );
    Student* getStudent();
    Corridor* getCorridor();
    Class* getClass(int );
    int getCnow();
};

class School{
    int Maxnumofstudents; //O megistos ari8mos ma8htwn pou xwraei to sxoleio
    int Realnumofstudents; //O pragmatikos arimos ma8htwn pou xwraei to sxoleio
    Teacher* teachers;
    Student* students;
    Schoolyard yard;
    Staircase stairs;
    Floor floors[3];
public:
    School(int ,int ,int ,int );
    ~School();

    void StartSimulation();
    void enter(Student );
    bool CheckTeachers(Teacher* );

    void print();
    Schoolyard getYard(); //Synarthseis pou epistrefoun to yard,stairs kai floor[i] antistoixa, wste na exw prosbash sth synarthsh enter pou 8elw ka8e fora
    Staircase getStairs();
    Floor getFloor(int );
};