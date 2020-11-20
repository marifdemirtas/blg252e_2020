/*
Student Name: Mehmet Arif Demirtaş
Student ID : 150180001
*/
#ifndef _MYCLASSES
#define _MYCLASSES

#include <string>

using namespace std;

class Person
{
private:
    string name;
    string surname;

public:
    Person(string, string);
    Person(Person const&);
    ~Person();
    string getName() const{
        return name;
    };
    string getSurname() const{
        return surname;
    };
    void setName(string name){
        this->name = name;
    };
    void setSurname(string surname){
        this->surname = surname;
    };
};

class Owner: public Person
{
    int percentage;

public:
    Owner(string name = "John", string surname = "Doe");
    ~Owner();
    double getPercentage() const{
        return percentage;
    };
    void setPercentage(int percentage){
        if(percentage >= 0 && percentage <= 100){
            this->percentage = percentage;
        } else if (percentage > 100){
            cerr << "INVALID PERCENTAGE, SET TO 100." << endl;
            this->percentage = 100;
        } else {
            cerr << "INVALID PERCENTAGE, SET TO 0." << endl;            
            this->percentage = 0;
        }
    };
};

class Courier: public Person
{
    string vehicle_type;
    int capacity;

    Courier* next;
public:
    Courier(string, string, string);
    Courier(Courier const& to_copy);
    ~Courier();
    string getVehicle() const{
        return vehicle_type;
    };
    void setVehicle(string vehicle_type){
        if(vehicle_type == "car" || vehicle_type == "motorcycle" || vehicle_type == "bicycle"){
            this->vehicle_type = vehicle_type;
        } else {
            cerr << "INVALID VEHICLE, SET TO BICYCLE" << endl;
            this->vehicle_type = "bicycle";
        }
    };
    int getCapacity() const;
    Courier* getNext() const{
        return next;
    }
    void setNext(Courier* next){
        this->next = next;
    }
    bool operator==(Courier &);
};

class Business
{
    string name;
    string address;
    Owner* owners;
    Courier* courier_head;
    int number_of_owners;

public:
    Business(string name, string address, Owner* owner_array, int number_of_owners);
    ~Business();
    string getName() const{
        return name;
    };
    string getAddress() const{
        return address;
    };
    void hire_courier(Courier &);
    void fire_courier(Courier &);
    void list_couriers();
    void list_owners();
    int calculate_shipment_capacity();
    void operator()();
    const Courier& operator[](int) const;
};

#endif