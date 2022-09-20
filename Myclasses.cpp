#include <fstream>
#include <ctime>
#include "Myclasses.h"

using namespace std;
ifstream myfile;

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// CONSTRUCTORS //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

Student::Student(){}
Teacher::Teacher(){}

void Class::setC(int C){
    this->Cnow=0;
    this->C=C;
    this->isFull=false;
    this->students=new Student[C];
}
void Class::setTeacher(Teacher& teacher){this->teacher=teacher;}

void Corridor::setC(int C){
    this->Cnow=0;
    this->C=C;
    this->isFull=false;
    this->students=new Student[C];
}

void Floor::setC(int Cclass,int Ccorridor){
    int i;
    this->Cnow=0;
    this->students=new Student[6*Cclass]; //O orofos exei megistei xwrhtikothta 6*Cclass
    corridor.setC(Ccorridor);
    for(i=0;i<6;i++) classes[i].setC(Cclass);
}

void Staircase::setC(int C){
    this->Cnow=0;
    this->C=C;
    this->isFull=false;
    this->students=new Student[C];
}


void Schoolyard::setC(int C){
    this->Cnow=0;
    this->C=C;
    this->isFull=false;
    this->students=new Student[C];
}

School::School(int Cclass,int Cyard,int Cstairs,int Ccorr){
    cout << "A school to be created!\n" << endl;
    int i,fl,cl;
    char temp[10];
    string name;

    Maxnumofstudents=18*Cclass; //To megisto plh8os ma8htwn einai iso me plh8os ta3ewn(18)*Xwrhtikothta ta3hs
    Realnumofstudents=0; //Edw krataw to plh8os twn ma8htwn pou dw8hkan
    students=new Student[Maxnumofstudents];
    myfile.open("Students.txt"); //Arxikopoiw ma8htes me th xrhsh tou arxeiou Students.txt
    i=0;
    while(true){
        if(!(myfile >> name)) break;
        myfile >> temp;
        fl=atoi(temp);
        myfile >> temp;
        cl=atoi(temp);
        students[i++].setData(name,fl,cl);
        Realnumofstudents++;
    }
    myfile.close();

    teachers=new Teacher[18]; //Arxikopoiw ka8hghtes me th xrhsh tou arxeiou Teachers.txt
    myfile.open("Teachers.txt");
    for(i=0;i<18;i++) teachers[i].setData();
    myfile.close();

    yard.setC(Cyard); //Arxikopoiw tous xwrous tou sxoleiou
    stairs.setC(Cstairs);
    for(i=0;i<3;i++) floors[i].setC(Cclass,Ccorr);
    for(i=0;i<18;i++) floors[i/6].getClass(i%6)->setTeacher(teachers[i]);
}

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DESTRUCTORS ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

Student::~Student(){cout << "A student to be destroyed!" << endl;}
Teacher::~Teacher(){cout << "A teacher to be destroyed!" << endl;}
Class::~Class(){delete[] students;}
Corridor::~Corridor(){delete[] students;}
Floor::~Floor(){delete[] students;}
Staircase::~Staircase(){delete[] students;}
Schoolyard::~Schoolyard(){delete[] students;}

School::~School(){
    cout << "A School to be destroyed!\n";
    delete[] students;
    delete[] teachers;
}


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// ACCESSORS /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void Teacher::print(){cout << name << endl;}

void Student::print(){cout << name << endl;}
bool Student::getIsOutside(){return isOutside;}
bool Student::getIsInClass(){return isInClass;}
string Student::getName(){return name;}
int Student::getCfloor(){return numoffloor;}
int Student::getCclass(){return numofclass;}

bool Class::getIsFull(){return isFull;}
int Class::getCnow(){return Cnow;}

bool Corridor::getIsFull(){return isFull;}
int Corridor::getCnow(){return Cnow;}
int Corridor::getC(){return C;}
Student* Corridor::getStudent(){return &(students[Cnow-1]);}

int Floor::getCnow(){return Cnow;}
Student* Floor::getStudent(){return &(students[Cnow-1]);}
Corridor* Floor::getCorridor(){return &corridor;}
Class* Floor::getClass(int i){return &(classes[i]);}

bool Staircase::getIsFull(){return isFull;}
int Staircase::getCnow(){return Cnow;}
int Staircase::getC(){return C;}
Student* Staircase::getStudent(){return &(students[Cnow-1]);}

bool Schoolyard::getIsFull(){return isFull;}
int Schoolyard::getCnow(){return Cnow;}
int Schoolyard::getC(){return C;}
Student* Schoolyard::getStudent(){return &(students[Cnow-1]);}

void Class::print(int i){
    cout << "\nPeople in class " << i+1 << " are:" << endl;
    for(int j=0;j<Cnow;j++) students[j].print();
    cout << "Teacher is " << teacher.getName() << endl;
}

void Corridor::print(){
    cout << "People in corridor are:" << endl;
    for(int i=0;i<Cnow;i++) students[i].print();
}

void Floor::print(int i){
    cout << "\nPeople in floor " << i+1 << " are:" << endl;
    corridor.print();
    for(int j=0;j<6;j++) classes[j].print(j);
}

void Staircase::print(){
    cout << "\nPeople in stairs are:" << endl;
    for(int i=0;i<Cnow;i++) students[i].print();
}

void Schoolyard::print(){
    cout << "People in yard are:" << endl;
    for(int i=0;i<Cnow;i++) students[i].print();
}

void School::print(){
    int i;
    cout << "\nSchool life consists of :" << endl;
    yard.print();
    stairs.print();
    for(i=0;i<3;i++) floors[i].print(i);
    cout << endl;
}
bool School::CheckTeachers(Teacher* teachers){
    int i;
    for(i=0;i<18;i++){
        cout << teachers[i].getIsinclass() << endl;
        if(teachers[i].getIsinclass() == false ) return false;
    }
    cout << "\nAll teachers are in class\n";
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MUTATORS //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

Student Student::copyStudent(Student& s){
    this->numoffloor=s.getCfloor();
    this->numofclass=s.getCclass();
    this->name=s.getName();
    return *this;
}
void Student::setData(string name,int fl,int cl){
    cout << "A student to be created!\n";
    this->name=name;
    this->numoffloor=fl;
    this->numofclass=cl;
    isOutside=true;
    isInClass=false;
}
void Student::changeIsOutside(){isOutside=false;}
void Student::changeIsInClass(){isInClass=true;}

void Teacher::setData(){
    cout << "A teacher to be created!\n";
    char line[100];
    myfile >> name;
    myfile >> line;
    numoffloor=atoi(line);
    myfile >> line;
    numofclass=atoi(line);
    IsInClass=false;
}
Teacher* Teacher::place(){
    IsInClass=true;
    return this;
}
string Teacher::getName(){return name;}
int Teacher::getNumoffloor(){return numoffloor;}
int Teacher::getNumofclass(){return numofclass;}
bool Teacher::getIsinclass(){return IsInClass;}

void School::StartSimulation(){
    cout << "\nStarting simulation...\n" << endl;
    if(Realnumofstudents == 0) {
        cout << "No students given." << endl;
        return;
    }
    srand((unsigned)time(0)); //Xrhsimopoiw thn time gia na exw ka8e fora diaforetikh timh
    bool flag=false;
    int i,j,m;
    Student* student;
    Teacher* teacher;
    Corridor* corridor;
    Class* cl;

    while(!flag){ //Epanalhptika metakinw ma8htes pros thn ta3h tous mexri na mpoun oloi sautes h na mpoun oloi oi ka8hghtes sautes
        while(yard.getIsFull() == false){ //Arxika bazw tuxaious ma8htes sto sxoleio kai kateu8eian meta sto proaulio mexri to proaulio na gemisei
            for(i=0;i<Realnumofstudents;i++){ //Elegxw an uparxei ma8hths e3w apto sxoleio
                if(students[i].getIsOutside() == true) break;
            }
            if(i == Realnumofstudents) break; //An oloi oi ma8htes einai ston xwro tou sxoleiou hdh proxwraw
            i=rand()%Realnumofstudents;
            if(students[i].getIsOutside() == true){ //Ama brisketai hdh sto kthrio den ton bazw mesa
                students[i].changeIsOutside();
                this->enter(students[i]);
                yard.enter(students[i]);
            }
        }
        
        while(stairs.getIsFull() == false && yard.getCnow() > 0){ //Meta pairnw autous pou einai sto proaulio kai tous bazw stis skales mexri na gemisoun oi skales h na adeiasei to proaulio
            student=yard.getStudent(); //H getStudent() mou epistrefei ton ma8hth sth 8esh Cnow tou pinaka ma8htwn ths yard
            yard.exit(*student);
            stairs.enter(*student);
        }
        
        i=rand()%18; //Topo8etw enan tuxaio ka8hghth sthn ta3h tou
        teacher=&(teachers[i]);
        teacher=teacher->place();
        floors[teachers[i].getNumoffloor()-1].getClass(teachers[i].getNumofclass()-1)->changeIsFull(); //Pleon oi ma8htes den mporoun na mpoun sthn ta3h auth
        for(i=0;i<18;i++){
            if(teachers[i].getIsinclass() == false) break;
        }
        if(i == 18){
            cout << "\nAll teachers are in class!\n";
            break;
        }

        while(stairs.getCnow() > 0){ //Meta metaferw enan enan tous ma8htes aptis skales stous orofous tous mexri na adeiasoun oi skales
            student=stairs.getStudent(); //H getStudent() mou epistrefei ton ma8hth sth 8esh Cnow tou pinaka ma8htwn twn skalwn
            stairs.exit(*student);
            floors[student->getCfloor()-1].enter(*student);
        }
        
        for(i=0;i<3;i++){ //Telos gia ka8e orofo metakinw tous ma8htes ston diadromo kai tis ta3eis

            corridor=floors[i].getCorridor();
            while(floors[i].getCnow() > 0 && corridor->getIsFull() == false){ //Arxika bazw ma8htes ston diadromo tou orofou i mexri na gemisei o diadromos h na adeiasei o orofos
                student=floors[i].getStudent();
                floors[i].exit();
                corridor->enter(*student);
            }

            m=corridor->getCnow();
            for(j=0;j<m;j++){ //Telos tous pairnw enan enan apto diadromo kai tous bazw stis ta3eis tous an xwrane
                cl=floors[i].getClass( student->getCclass()-1 );
                if(cl->getIsFull() == false && student->getIsInClass() == false){
                    corridor->exit(*student);
                    cl->enter(*student);
                    student->changeIsInClass();
                }
                student=corridor->getStudent();
            }
        }
        
        i=rand()%18; //Topo8etw enan tuxaio ka8hghth sthn ta3h tou
        teacher=&(teachers[i]);
        teacher=teacher->place();
        floors[teachers[i].getNumoffloor()-1].getClass(teachers[i].getNumofclass()-1)->changeIsFull(); //Pleon oi ma8htes den mporoun na mpoun sthn ta3h auth
        for(i=0;i<18;i++){
            if(teachers[i].getIsinclass() == false) break;
        }
        if(i == 18){
            cout << "\nAll teachers are in class!\n";
            break;
        }

        for(i=0;i<3;i++){ //Elegxw an oles oi ta3eis einai gemates
            for(j=0;j<6;j++){
                if(floors[i].getClass(j)->getIsFull() == false) break;//An bre mia mh gemath ta3h stamataw
            }
            if(j < 6) break; //Ama to j einai mikrotero apo 6 shmainei pws h epanalhpsh espase
        }
        if(i == 3){ //An to i einai 3 h epanalhpsh den espase pote kai sunepws einai gemates oles oi ta3eis
            cout << "\nAll classes are full!\n";
            flag=true;
        }
    }
    cout << "\nThe simulation has ended.The results are :\n\n";
}

void School::enter(Student student){
    cout << student.getName() << " enter school!" << endl;
}

void Schoolyard::enter(Student student){
    cout << student.getName() << " enters schoolyard!" << endl;
    Cnow++; //Au3anw to plh8os twn ma8htwn pou briskontai sto proaulio kata 1
    students[Cnow-1]=students[Cnow-1].copyStudent(student); //Antigrafw ton ma8hth ston pinaka ma8htwn tou proauliou
    if(Cnow == C) isFull=true; //An ftasw sthn megisth xwrhtikothta kanw to isFull true
}

void Schoolyard::exit(Student student){
    cout << student.getName() << " exits schoolyard!" << endl;
    isFull=false; //Pleon den einai gemath h aulh
    Cnow--; //Meiwnw to plh8os twn ma8htwn pou briskontai sthn aulh
}

void Staircase::enter(Student student){
    cout << student.getName() << " enters stairs!" << endl;
    Cnow++; //Au3anw to plh8os twn ma8htwn pou briskontai stis skales kata 1
    students[Cnow-1]=students[Cnow-1].copyStudent(student); //Antigrafw ton ma8hth ston pinaka ma8htwn twn skalwn
    if(Cnow == C) isFull=true; //An ftasw sthn megisth xwrhtikothta kanw to isFull true
}

void Staircase::exit(Student student){
    cout << student.getName() << " exits stairs!" << endl;
    isFull=false; //Pleon den einai gemates oi skales
    Cnow--; //Meiwnw to plh8os ma8htwn pou briskontai stis skales
}

void Floor::enter(Student student){
    cout << student.getName() << " enters floor " << student.getCfloor() << "!" << endl;
    Cnow++; //Au3anw to plh8os twn ma8htwn pou briskontai ston orofo
    students[Cnow-1]=students[Cnow-1].copyStudent(student); //Antigrafw ton ma8hth ston pinaka ma8htwn tou orofou
}

void Floor::exit(){Cnow--;} //Ka8e fora pou kapoios ma8hths mpainei ston diadromo meiwnw to Cnow tou orofou

void Corridor::enter(Student student){
    cout << student.getName() << " enters corridor!" << endl;
    Cnow++; //Au3anw to plh8os twn ma8htwn pou briskontai ston diadromo
    students[Cnow-1]=students[Cnow-1].copyStudent(student); //Antigrafw ton ma8hth ston pinaka ma8htwn tou diadromou
    if(Cnow == C) isFull=true; //An ftasw sthn megisth xwrhtikothta kanw to isFull true
}

void Corridor::exit(Student student){
    cout << student.getName() << " exits corridor!" << endl;
    isFull=false; //Pleon den einai gemates oi skales
    Cnow--; //Meiwnw to plh8os ma8htwn pou briskontai stis skales
}

void Class::enter(Student student){
    cout << student.getName() << " enters class!" << endl;
    Cnow++; //Au3anw to plh8os twn ma8htwn pou briskontai sthn ta3h
    students[Cnow-1]=students[Cnow-1].copyStudent(student); //Antigrafw ton ma8hth ston pinaka ma8htwn tou diadromou
    if(Cnow == C) isFull=true;
}
void Class::changeIsFull(){isFull=true;}