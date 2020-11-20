/*
Student Name: Mehmet Arif Demirtaş
Student ID : 150180001

COMPILE COMMAND: g++ 150180001.cpp

Since #include is used to add main file to this file, main.cpp must be in
the same directory as this .cpp and .h file.
#include "main.cpp" can be commented out to link two cpp files in compile phase, using 'g++ -o result main.cpp 150180001.cpp', which will create a executable called 'result'. 
*/
#include <string>
#include <iostream>
#include "150180001.h"

#include "main.cpp"

using namespace std;

Person::Person(string name = "John", string surname = "Doe"){
    this->name = name; 
    this->surname = surname;
}

Person::Person(Person const& to_copy){
    this->name = to_copy.name; 
    this->surname = to_copy.surname;
}

Person::~Person(){
//    cout << "Person at address " << this << " destructed" << endl; 
}

Owner::Owner(string name, string surname):Person(name, surname){
    setPercentage(0);
}

Owner::~Owner(){
//    cout << "Owner at address " << this << " destructed" << endl;
}

Courier::Courier(string name, string surname, string vehicle_type):Person(name, surname){
    if(vehicle_type == "car" || vehicle_type == "motorcycle" || vehicle_type == "bicycle"){
        this->vehicle_type = vehicle_type;
    } else {
        cerr << "INVALID VEHICLE, SET TO BICYCLE" << endl;
        this->vehicle_type = "bicycle";
    }
    next = NULL;
}

Courier::Courier(Courier const& to_copy): Person(to_copy){
    this->vehicle_type = to_copy.vehicle_type;
    this->next = to_copy.next;
}

Courier::~Courier(){
//    cout << "Courier at address " << this << " destructed" << endl;
}

bool Courier::operator==(Courier & compare_courier){
    return ((this->getName() == compare_courier.getName()) && (this->getSurname() == compare_courier.getSurname()) && (this->vehicle_type == compare_courier.getVehicle()));
}

int Courier::getCapacity() const{
    if(vehicle_type == "car"){
        return 200;
    }
    if(vehicle_type == "motorcycle"){
        return 35;
    }
    if(vehicle_type == "bicycle"){
        return 10;
    }
}

Business::Business(string name, string address, Owner* owner_array, int number_of_owners){
    this->name = name;
    this->address = address;
    double percent = 100.0 / number_of_owners;
    if(owner_array != NULL){
        owners = owner_array;
        for(int i = 0; i < number_of_owners; i++){
            owners[i].setPercentage(percent);
        }
        this->number_of_owners = number_of_owners;
    } else {
        cerr << "NO OWNERS ADDED" << endl;
        this->number_of_owners = 0;
    }
    courier_head = NULL;
}

Business::~Business(){
//    delete[] owners;    //UNCOMMENT THIS LINE IF ONLY DYNAMIC ARRAYS ARE SENT TO CONSTRUCTOR
    //cout << "Business at address " << this << " destructed" << endl;
}

void Business::hire_courier(Courier & new_courier)
{
    Courier* traverse = courier_head;
    if(traverse == NULL){
        courier_head = &new_courier;
    } else {
        while(traverse->getNext() != NULL){
            traverse = traverse->getNext();
        }
        new_courier.setNext(traverse->getNext());
        traverse->setNext(&new_courier);
    }
}

void Business::fire_courier(Courier & to_fire)
{
    if(to_fire == (*courier_head)){
        courier_head = courier_head->getNext();
        return;
    }
    Courier* traverse = courier_head;
    Courier* previous = traverse;
    while(traverse != NULL){
        if(to_fire == (*traverse)){
            previous->setNext(traverse->getNext());
            return;            
        }
        previous = traverse;
        traverse = traverse->getNext();
    }
    cerr << "COURIER NOT FOUND" << endl;
}


void Business::list_couriers()
{
    Courier* traverse = courier_head;
    if(traverse == NULL){
        cout << "NO COURIER ENTRY" << endl;
    } else {
        while(traverse != NULL){
            cout << traverse->getName() << " " << traverse->getSurname() << " " << traverse->getVehicle() << endl;
            traverse = traverse->getNext();
        }
    }
}

void Business::list_owners(){
    if(number_of_owners == 0){
        cout << "NO OWNER ENTRY" << endl;
    } else {
        for(int i = 0; i < number_of_owners; i++){
            cout << owners[i].getName() << " " << owners[i].getSurname() << " " << owners[i].getPercentage() << endl;
        }
    }
}

int Business::calculate_shipment_capacity()
{
    Courier* traverse = courier_head;
    int capacity = 0;
    while(traverse != NULL){
        capacity += traverse->getCapacity();
        traverse = traverse->getNext();
    }
    return capacity;
}

void Business::operator()()
{
    cout << getName() << " " << getAddress() << endl;
    list_owners();
    list_couriers();
}

const Courier& Business::operator[](int a) const
{
    if(courier_head == NULL){
        cerr << "NO COURIERS FOUND" << endl;
        exit(1);
    } else { 
        Courier* traverse = courier_head;
        if (a < 0)
        {
            cerr << "INDEX OUT OF BOUNDS, RETURNING FIRST COURIER" << endl;        
        }
        for(int i = 0; i < a; i++){
            if (traverse->getNext() == NULL)
            {
                cerr << "INDEX OUT OF BOUNDS, RETURNING LAST COURIER" << endl;
                break;
            }
            traverse = traverse->getNext();
        }
        return *traverse;
    }
}

