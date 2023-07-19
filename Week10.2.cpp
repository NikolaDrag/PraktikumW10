#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::string;

class Worker{
    private:
    string name;
    int age;
    int months;
    double salary;
    public:
    //constructors
    Worker(){
        this->name = "-";
        this->age = 0;
        this->months = 0;
        this->salary=0;
    }
    Worker(const string &nameVal, const int ageVal, const int monthsVal, const double salaryVal):name(nameVal), age(ageVal), months(monthsVal), salary(salaryVal){};
    Worker(const Worker &w){
        this->name = w.name;
        this->age = w.age;
        this->months = w.months;
        this->salary= w.salary;
    }
    //operators
    Worker &operator=(const Worker &w){
        if(this != &w){
            this->name = w.name;
            this->age = w.age;
            this->months = w.months;
            this->salary= w.salary;
        }
        return *this;
    }
    bool operator==(const Worker &w){
        if(this->name == w.name && this->age == w.age && this->months == w.months && this->salary == w.salary){
        return true; 
        }
        return false;
    }
    //other methods
    //getters
    string getName()const{
        return this->name;
    }
    int getAge()const{
        return this->age;
    }
    int getMonths()const{
        return this->months;
    }
    double getSalary()const{
        return this->salary;
    }
    //destructor
    virtual ~Worker(){};
};

class Manager : public Worker{
    private:
    Worker* workersOfManager;
    int workersAmount;
    string department;
    public:
    //constructors
    Manager(){
        this->workersAmount = 0;
        this->workersOfManager = new Worker [this->workersAmount];
        this->department = "-";
    }
    Manager(const string nameVal, const int ageVal, const int monthsVal, const double salaryVal, const Worker* workersVal, const int amountVal, const string depVal):
    Worker(nameVal,ageVal, monthsVal,salaryVal),workersOfManager(new Worker[amountVal]),workersAmount(amountVal),department(depVal){
        for(int i=0;i<amountVal;i++){
            workersOfManager[i] = workersVal[i];
        }
    }
    Manager(const Manager &m):Worker(m),workersOfManager(new Worker[m.workersAmount]),workersAmount(m.workersAmount),department(m.department){
        for(int i=0;i<m.workersAmount;i++){
            workersOfManager[i] = m.workersOfManager[i];
        }
    }
    //operators
    Manager &operator=(const Manager &m){
        if(this != &m){
            this ->Worker::operator=(m);
            delete [] this->workersOfManager;
            this->workersAmount = m.workersAmount;
            this->workersOfManager = new Worker[m.workersAmount];
            department = m.department;
            for(int i=0;i<workersAmount;i++){
            workersOfManager[i] = m.workersOfManager[i];
            }
        }
        return *this;
    }
    //getters
    Worker * getWorkers()const{
        return this->workersOfManager;
    }
    int getWorkersAmount() const{
        return this->workersAmount;
    }
    string getDepartment() const{
        return this->department;
    }
    //other methods
     /*Worker &operator[](int index)const{
        return this->workersOfManager[index];
    }*/
    //destructor
    ~Manager(){
        delete[] this->workersOfManager;
    }
};

class Boss : public Worker{
    private:
    Manager* managersOfBoss;
    int managersAmount;
    string companyName;
    public:
    //constructors
    Boss(){
        managersAmount = 0;
        managersOfBoss = new Manager[managersAmount];
        companyName = "-";
    }
    Boss(const string nameVal, const int ageVal, const int monthsVal, const double salaryVal, const Manager * managersVal, const int mAVal, const string cNameVal)
    :Worker(nameVal,ageVal,monthsVal, salaryVal), managersOfBoss(new Manager[mAVal]), managersAmount(mAVal), companyName(cNameVal){
        for(int i=0;i < mAVal;i++){
            managersOfBoss[i] = managersVal[i];
        }
    }
    Boss(const Boss &b):Worker(b),managersOfBoss(new Manager[b.managersAmount]), managersAmount(b.managersAmount), companyName(b.companyName){
        for(int i=0;i < b.managersAmount;i++){
            managersOfBoss[i] = b.managersOfBoss[i];
        }
    }
    //operators
    Boss &operator=(const Boss &b){
        if(this != &b){
            this->Worker::operator=(b);
            delete [] this->managersOfBoss;
            managersAmount = b.managersAmount;
            managersOfBoss = new Manager[managersAmount];
            for(int i=0;i < managersAmount;i++){
            managersOfBoss[i] = b.managersOfBoss[i];
            }
            companyName = b.companyName;
        }
        return *this;
    }
    
    //getters
    string getcName()const{
        return this->companyName;
    }
    int getManagersAmount()const{
        return this->managersAmount;
    }
    Manager* getManagersOfBoss()const{
        return this->managersOfBoss;
    }
    //other methods
    /*Manager&operator[](int index)const{
        return this->managersOfBoss[index];
    }*/
    //destructor
    ~Boss(){
        delete [] managersOfBoss;
    }
};

void writeCompany(Boss &b, const char * fileName){
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << fileName << " for writing\n";
        return;
    }
    file << b.getcName() << endl;
    for(int i=0;i<b.getManagersAmount();i++){
        file << "Name of Manager: " << b.getManagersOfBoss()[i].getName() << " | Age of Manager: " << b.getManagersOfBoss()[i].getAge() << 
        " | Months of work: " << b.getManagersOfBoss()[i].getMonths() <<
        " | Salary of Manager: " << b.getManagersOfBoss()[i].getSalary() << ": Name of department: " << b.getManagersOfBoss()[i].getDepartment() << endl;
        for(int j=0;j<b.getManagersOfBoss()[i].getWorkersAmount();j++){
            file << "Name of Worker: " << b.getManagersOfBoss()[i].getWorkers()[j].getName() << " | Age of Worker: " << b.getManagersOfBoss()[i].getWorkers()[j].getAge() <<
            " | Months of work: " << b.getManagersOfBoss()[i].getWorkers()[j].getMonths() << " | Salary of Worker: " << b.getManagersOfBoss()[i].getWorkers()[j].getSalary() << endl;
        }
    }
    file.close();
    return;
}

double workersMonths(Boss &b){
    double averageMonths =0;
    int workerCounter =0;
    for(int i=0;i<b.getManagersAmount();i++){
        for(int j=0;j<b.getManagersOfBoss()[i].getWorkersAmount();j++){
            averageMonths = averageMonths + b.getManagersOfBoss()[i].getWorkers()[j].getMonths();
            workerCounter++;
        }
    }
    averageMonths = averageMonths/workerCounter;
    return averageMonths;
}

double averageMonths(Boss &b){
    double averageMonthsAll =0;
    int allCounter =1;
    for(int i=0;i<b.getManagersAmount();i++){
         averageMonthsAll = averageMonthsAll + b.getManagersOfBoss()[i].getMonths();
         allCounter++;
        for(int j=0;j<b.getManagersOfBoss()[i].getWorkersAmount();j++){
            averageMonthsAll = averageMonthsAll + b.getManagersOfBoss()[i].getWorkers()[j].getMonths();
            allCounter++;
        }
    }
      averageMonthsAll = (averageMonthsAll + b.getMonths())/allCounter;
      return averageMonthsAll;
}

bool isDepartment(Manager &m, Worker &w){
    for(int i=0;i < m.getWorkersAmount();i++){
        if(m.getWorkers()[i] == w){
            return true;
        }
    }
    return false;
}

int main(){
    Worker w1("Ivan",20,11,60);
    Worker w2("Antony", 30,12,40);
    Worker w3("Pavel", 16,24,90.5);
    Worker w4("Kuzu", 22, 6, 25);
    Worker* workers1 = new Worker[2];
    workers1[0] = w1;
    workers1[1] = w2;
    Worker* workers2 = new Worker[2];
    workers2[0] = w3;
    workers2[1] = w4;
    Manager m1("Martin", 30, 18,200,workers1,2,"Mladost");
    Manager m2("Ronaldo", 37, 36,150,workers2,2,"Lulin");
    //cout << m1.getWorkers()[0].getName() << endl;
    Manager* managers = new Manager[2];
    managers[0] = m1;
    managers[1] = m2;
    //cout << m1.getWorkersAmount();
    Boss b1("Dragnev", 22, 48,9999,managers,2,"DragnevIndustries");
    //cout << b1.getManagersOfBoss()[0].getDepartment() << endl << b1.getManagersOfBoss()[0].getWorkers()[0].getName(); //
    //cout << b1.getManagersOfBoss()[0].getWorkersAmount();
    writeCompany(b1,"FileName11");
    cout << workersMonths(b1) << endl;
    cout << averageMonths(b1) << endl;
    cout << isDepartment(m1,w2); //ako ima 2 absolutno ednakvi v razlichni otdeli?
    delete[] workers1;
    delete[] workers2;
    delete[] managers;
    return 0;
    //tryabvat li ni operator[]? Zashto da/ne?
    //bonus?
}
