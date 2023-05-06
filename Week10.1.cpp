#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Ticket{
    private:
    double price;
    string nameOfEvent;
    public:
    Ticket(){
        this->price =0;
        this->nameOfEvent = "-";
    };
    Ticket(const double priceVal, const string nameVal){
        this->price = priceVal;
        this->nameOfEvent = nameVal;
    }
    Ticket(const Ticket &t){
        this->price = t.price;
        this->nameOfEvent = t.nameOfEvent;
    }
    Ticket &operator=(const Ticket &t){
        if(this != &t){
            this->price = t.price;
            this->nameOfEvent = t.nameOfEvent;
        }
        return *this;
    }
    double getPrice()const{
        return this->price;
    }
    virtual void print()const{
        cout << "Price: " << this->price << " | Name of event: " << this->nameOfEvent;
        return;
    };
};

class PriviligedTicket : public Ticket {
    private:
    string guestName;
    public:
    string getGuestName()const{
        return this->guestName;
    }
    PriviligedTicket(){
        this->guestName = "-";
    }
    PriviligedTicket(const double priceVal, const string nameVal,const string guestNameVal):Ticket(priceVal/2, nameVal),guestName(guestNameVal){};
    PriviligedTicket(const PriviligedTicket &pt):Ticket(pt),guestName(pt.guestName){};
    PriviligedTicket &operator=(const PriviligedTicket &pt){
        if(this != &pt){
            this -> Ticket::operator=(pt);
            this->guestName = pt.guestName;
        }
        return *this;
    };
    void print()const{
        this -> Ticket::print();
        cout << " | Name of guest: " << this->guestName;
        return;
    };
};

class GroupTicket : public Ticket {
    private:
    int numberPeople;
    public: 
    GroupTicket(){
        this->numberPeople = 0;
    }
    GroupTicket(const double priceVal, const string nameVal,const int numberPeopleVal):Ticket((priceVal-2)*numberPeopleVal, nameVal),numberPeople(numberPeopleVal){};
    GroupTicket(const GroupTicket &gt):Ticket(gt),numberPeople(gt.numberPeople){};
    GroupTicket &operator=(const GroupTicket &gt){
        if(this != &gt){
            this -> Ticket::operator=(gt);
            this->numberPeople = gt.numberPeople;
        }
        return *this;
    };
    void print()const{
        this -> Ticket::print();
        cout << " | Number of guests: " << this->numberPeople;
        return;
    };
};

void reference(const double pVal, const string eventVal,const Ticket* tickets,const int numberOfTickets){
    int guestCount =0;
    double sumPrice =0;
    for(int i=0;numberOfTickets > i;i++){
        if(tickets[i].getPrice() == pVal || tickets[i].getPrice() == pVal/2){
            guestCount++;
            sumPrice=sumPrice + tickets[i].getPrice();
        }
        else{
            guestCount= guestCount + tickets[i].getPrice()/(pVal-2);
            sumPrice=sumPrice + tickets[i].getPrice();
        }
    }
    cout << "Event: "<< eventVal << " | Total guests: " << guestCount << " | Revenue: " << sumPrice << endl;
    return;
}

int main(){
    //only tests in main()
    Ticket a(100, "Borovec");
    Ticket b(100, "Borovec");
    PriviligedTicket pv(100, "Borovec","Stukata");
    GroupTicket c(100, "Borovec", 10);
    Ticket p1[4] = {a,b,pv,c};
    pv.print();
    //reference(100, "Borovec", p1,4);
    return 0;
}