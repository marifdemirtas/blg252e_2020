/*
Student Name: Mehmet Arif Demirtaş
Student ID : 150180001
*/

#include <iostream> // for cout, cin
#include <cstdlib>  // for NULL declaration
#include <string> // for string ops

using namespace std;

void lowerCase(string& input) //function to turn strings lowercase
{
   for(unsigned int i=0; i<input.length(); i++){
      input[i] = tolower(input[i]);
   }
}

//CLASS DEFINITIONS

class Pizza
{
    string name;
    string size;
    string *ingredients;
    string crust_type;

    Pizza* next; //for linked list structure

public:
    void print() const;
    Pizza* getNext() const{
        return this->next;
    };
    void setNext(Pizza* next){
        this->next = next;
    };
    string getType() const{
        return size;
    };

    Pizza();
    Pizza(string size, string crust_type, int pizza_type);
    Pizza(Pizza& pizza);
    ~Pizza();
};

class stringNode {
    string data;
    int count;
    stringNode *next;
  public:
    string getData() const{
        return data;
    };
    void setData(string data){
        this->data = data;
    };
    int getCount() const{
        return count;
    };
    void addCount(){
        count++;
    };
    stringNode* getNext() const{
        return next;
    };
    void setNext(stringNode* next){
        this->next = next;
    };

    stringNode(string);

};

class Order;
class stringList {
    friend Order;

    stringNode *head;

  public:
    void add(string);
    void print() const;
    void clear();
    
    stringList();
};

class Order
{
    string customer;
    Pizza* pizza;
    stringList drink;

    Order* next;

public:
    double getPrice() const;
    void printOrder() const;

    Order* getNext() const{
        return this->next;
    };
    void setNext(Order* next){
        this->next = next;
    };
    string getName() const{
        return customer;
    };

    Order(string, Pizza*, stringList);
    Order(string, Pizza*);
    ~Order();  
};

class OrderList {
    Order *head;
    int n;

  public:
    void takeOrder();
    void listOrders() const;
    void deliverOrders();

    OrderList();
    ~OrderList();
};

//END OF CLASS DECLARATIONS

//PIZZA CLASS METHODS

Pizza::Pizza()
{
    size = "medium";
    crust_type = "normal";
    ingredients = new string[1];
    ingredients[0] = "mozzarella";

}

Pizza::Pizza(string size, string crust_type, int pizza_type)
{
    this->size = size;
    this->crust_type = crust_type;
    ingredients = new string[6];

    if (pizza_type == 1) {
        name = "Chicken";
        ingredients[0] = "mozzarella";
        ingredients[1] = "chicken";
        ingredients[2] = "mushroom";
        ingredients[3] = "corn";
        ingredients[4] = "onion";
        ingredients[5] = "tomato";
    } else if (pizza_type == 2) {
        name = "Broccoli";
        ingredients[0] = "mozzarella";
        ingredients[1] = "broccoli";
        ingredients[2] = "pepperoni";
        ingredients[3] = "olive";
        ingredients[4] = "corn";
        ingredients[5] = "onion";
    } else if (pizza_type == 3) {
        name = "Sausage";
        ingredients[0] = "mozzarella";
        ingredients[1] = "sausage";
        ingredients[2] = "tomato";
        ingredients[3] = "olive";
        ingredients[4] = "mushroom";
        ingredients[5] = "corn";
    }
}

Pizza::Pizza(Pizza& pizza)
{
    name = pizza.name;
    size = pizza.size;
    crust_type = pizza.crust_type;
    next = NULL;

    cout << "Please enter the number of the ingredient you want to remove from your pizza." << endl;
    for(int i = 0; i < 6; i++){
        cout << i+1 << ". " << pizza.ingredients[i] << endl;
    }
    cout << "Press 0 to save." << endl;
    char num = 1;
    ingredients = new string[6];
    for(int i = 0; i < 6; i++){
        ingredients[i] = pizza.ingredients[i]; 
    }
    while(true){
        cin >> num;
        num = num - '0';
        num = int(num);
        if(num == 0){
            break;
        }
        if (num > 6 || num < 0)
        {
        	cout << "Invalid number for ingredient" << endl;
        	continue;
        }

        ingredients[num - 1] = "";
    }
}

Pizza::~Pizza()
{
    delete[] ingredients;
}

void Pizza::print() const
{
    cout << name << " Pizza(";
    for(int i = 0; i < 6; i++){
        if (ingredients[i] != "")
        {
            cout << ingredients[i] << ", ";
        }
    }
    cout << ")" << endl << "size: " << size << ", crust: " << crust_type << endl << endl;
}

//END OF PIZZA CLASS METHODS

//STRINGNODE + STRINGLIST CLASS METHODS

stringNode::stringNode(string data = "")
{
    this->data = data;
    next = NULL;
    count = 1;
}

stringList::stringList()
{
    head = NULL;
}

void stringList::add(string data)
{
    stringNode *newnode = new stringNode(data);
    stringNode *traverse = head;

    while(traverse != NULL){
        if(traverse->getData() == data){
            traverse->addCount();
            delete newnode;
            return;
        }
        traverse = traverse->getNext();
    }

    traverse = head;
    if(head == NULL){
        head = newnode;
    } else {
        while(traverse->getNext() != NULL){
            traverse = traverse->getNext();
        }
        traverse->setNext(newnode); 
    }
}

void stringList::print() const{
   stringNode *traverse = head;
   while (traverse != NULL) { 
      cout << traverse->getCount() << " " << traverse->getData() << ", ";
      traverse = traverse->getNext();
   }
   cout << endl;
}

void stringList::clear(){
  stringNode *traverse;
  while(head != NULL){
    traverse=head->getNext();
    delete head;
    head = traverse;
  }
  head = NULL;
}

//END OF STRINGNODE + STRINGLIST CLASS METHODS

//ORDER CLASS METHODS 

Order::Order(string customer, Pizza* pizza, stringList drink)
{
    this->customer = customer;
    this->pizza = pizza;
    this->drink = drink;
    this->next = next;
}

Order::Order(string customer, Pizza* pizza)
{
    this->customer = customer;
    this->pizza = pizza;
    this->drink = stringList();
    this->next = next;
}

Order::~Order()
{
    Pizza* traverse;
    while(pizza != NULL){
        traverse = pizza;
        pizza = pizza->getNext();
        delete traverse;
    }
    drink.clear();
}

void Order::printOrder() const 
{
    cout << "--------------------" << endl;
    cout << "Customer: " << customer << endl << endl;;
    Pizza* traverse = pizza;
    while(traverse != NULL){
        traverse->print();
        traverse = traverse->getNext();
    }
    cout << endl;
    drink.print();
    cout << endl;
}

double Order::getPrice() const
{
    double price = 0;
    int pizza_price = 0;
    Pizza* traverse = pizza;
    string pizza_type = traverse->getType();
    if(pizza_type == "small"){
        pizza_price = 15;
    }else if(pizza_type == "medium"){
        pizza_price = 20;
    }else if(pizza_type == "big"){
        pizza_price = 25;
    }
    while(traverse != NULL){
        price += pizza_price;
        traverse = traverse->getNext();
    }

    stringNode* traverse_drink = drink.head;
    while(traverse_drink != NULL){
        string drink_type = traverse_drink->getData();
        int drink_price = 0;
        if(drink_type == "cola"){
            drink_price = 4;
        }else if (drink_type == "soda")
        {
            drink_price = 2;
        }else if (drink_type == "ice tea")
        {
            drink_price = 3;
        }else if (drink_type == "fruit juice")
        {
            drink_price = 3.5;
        }
        price += drink_price * traverse_drink->getCount();
        traverse_drink = traverse_drink->getNext();
    }

    return price;
}

//END OF ORDER CLASS DEFINITIONS

//ORDERLIST CLASS METHODS

OrderList::OrderList()
{
    head = NULL;
    n = 0;
}

void OrderList::takeOrder()
{
    int pizza_type, amount;
    string size, crust_type;
    cout << "Pizza Menu" << endl;
    cout << "1. Chicken Pizza (mozzarella, chicken, mushroom, corn, onion, tomato)" << endl
        << "2. Broccoli Pizza (mozzarella, broccoli, pepperoni, olive, corn, onion)" << endl
        << "3. Sausage Pizza (mozzarella, sausage, tomato, olive, mushroom, corn)" << endl
        << "0. Back to main menu" << endl;
    cin >> pizza_type;
    while(pizza_type != 0 && pizza_type != 1 && pizza_type != 2 && pizza_type != 3){
        cerr << "Please enter a valid choice" << endl;
        cin >> pizza_type;      
    }
    if(pizza_type == 0){
        cout << "Returning to main menu..." << endl;
        return;
    }
    cout << "Select size: small (15 TL), medium (20 TL), big (25 TL)" << endl;
    cin >> size;
    lowerCase(size);
    if(!(size == "small" || size == "medium" || size == "big")){
        cout << "Invalid choice, setting size to medium..." << endl;
        size = "medium";
    }

    cout << "Select crust type: thin, normal, thick" << endl;
    cin >> crust_type;
    lowerCase(crust_type);
    if(!(crust_type == "thin" || crust_type == "normal" || crust_type == "thick")){
        cout << "Invalid choice, setting crust type to normal..." << endl;
        crust_type = "normal";
    }

    Pizza* new_pizza = new Pizza(size, crust_type, pizza_type);

    cout << "Enter the amount:";
    cin >> amount;
    if (!(amount > 0))
    {
        cout << "Invalid input for amount, producing 1 pizza..." << endl;
        amount = 1;
    }

    Pizza* traverse_pizza = new_pizza;
    for (int i = 0; i < amount - 1; ++i)
    {
        traverse_pizza->setNext(new Pizza(*new_pizza));
        traverse_pizza = traverse_pizza->getNext();

    }
    cout << "Please choose a drink:" << endl
        << "0. no drink" << endl
        << "1. cola 4 TL" << endl
        << "2. soda 2 TL" << endl
        << "3. ice tea 3 TL" << endl
        << "4. fruit juice 3.5 TL" << endl
        << "Press -1 for save your order" << endl;
    stringList drinks;
    int drink_choice;
    bool exit = false;
    while(!exit){
        cin >> drink_choice;
        string drink = "";
        switch(drink_choice){
            case 0:
                drinks.clear();
            case -1:
                exit = true;
                break;
            case 1:
                drink = "cola";
                break;
            case 2:
                drink = "soda";
                break;
            case 3:
                drink = "ice tea";
                break;
            case 4:
                drink = "fruit juice";
                break;
            default:
                cout << "invalid choice" << endl;
                break;
        }
        if (drink != ""){
            drinks.add(drink);
        };
    }

    string customer;
    cout << "Please enter your name:" << endl;
    cin >> customer;
    lowerCase(customer);

    Order* new_order = new Order(customer, new_pizza, drinks);

    cout << "Your order is saved, it will be delivered when it is ready..." << endl;
    new_order->printOrder();

    Order *traverse = head;
    if(head == NULL){
        head = new_order;
    } else {
        while(traverse->getNext() != NULL){
            traverse = traverse->getNext();
        }
        traverse->setNext(new_order);
    }
    n++;
}

void OrderList::listOrders() const {
   Order *traverse = head;
   if (traverse == NULL)
   {
       cout << "empty list, no orders found" << endl;
       cout << "Returning to main menu" << endl;
   }
   while (traverse != NULL) { 
      traverse->printOrder();
      traverse = traverse->getNext();
   }
   cout << "--------------------" << endl;
}

void OrderList::deliverOrders() {
    this->listOrders();

    if(head == NULL){
        cerr << "No orders found, cannot deliver" << endl;
        return;
    }
    cout << "Please write the customer name in order to deliver his/her order: ";
    string customer;
    cin >> customer;
    lowerCase(customer);

    string promo;
    string code = "I am a student";

    Order* traverse = head;
    if(traverse->getName() == customer){
        head = traverse->getNext();
        cout << "Following order is delivering..." << endl;
        traverse->printOrder();
        cout << "Total price: " << traverse->getPrice() << endl;
        char promo_choice = 'n';
        while(true){
            cout << "Do you have a promotion code? (y/n)";
            cin >> promo_choice;
            if(promo_choice == 'n')
                break;
            cout << "Please enter your code: ";
            cin.ignore();
            getline(cin, promo);
            if(promo == code){
                cout << "Discounted price: " << traverse->getPrice()*0.9 << endl;
                break;
            }else {
                cout << "Promotion code is not accepted." << endl;
            }     
        }
        cout << "The order is delivered successfully!" << endl << endl;
        delete traverse;
        return;
    } 

    while(traverse->getNext() != NULL){
        if(traverse->getNext()->getName() == customer){
            Order* todelete = traverse->getNext();
            traverse->setNext(traverse->getNext()->getNext());
            cout << "Following order is delivering..." << endl;
            todelete->printOrder();
            cout << "Total price: " << todelete->getPrice() << endl;
            char promo_choice = 'n';
            while(true){
                cout << "Do you have a promotion code? (y/n)";
                cin >> promo_choice;
                if(promo_choice == 'n')
                    break;
                cout << "Please enter your code: ";
                cin.ignore();
                getline(cin, promo);
                if(promo == code){
                    cout << "Discounted price: " << traverse->getPrice()*0.9 << endl;
                }else {
                    cout << "Promotion code is not accepted." << endl;
                }     
            }
            cout << "The order is delivered successfully!" << endl << endl;
            delete todelete;
            return;
        }
        traverse = traverse->getNext();
    }
    cerr << "Wrong name, order not found in the list" << endl;
    cerr << "Returning to main menu..." << endl;
}

OrderList::~OrderList(){
  Order* traverse;
  while(head != NULL){
    traverse = head->getNext();
    delete head;
    head = traverse;
  }
  head = NULL;
}

//END OF ORDERLIST CLASS METHODS

int take_choice()
{
    cin.clear();
    cout << "Welcome to Pizzaria!" << endl <<
    "1. Add an order" << endl <<
    "2. List orders" << endl <<
    "3. Deliver order" << endl <<
    "4. Exit" << endl <<
    "Choose what to do:";
    int choice;
    cin >> choice;
    if(choice == 1 || choice == 2 || choice == 3 || choice == 4)
        return choice;
    cout << "Invalid input, try again" << endl;
    return 0;
}

int main(int argc, char* argv[])
{
    OrderList rainbow_pizzeria;
    bool exit = false;
    string customer = "hi";
    while(!exit){
        switch(take_choice()){
            case 1: //Add an order
                rainbow_pizzeria.takeOrder();
                break;
            case 2: //List orders
                rainbow_pizzeria.listOrders();
                break;
            case 3: //Deliver orders
                rainbow_pizzeria.deliverOrders();
                break;
            case 4: //Exit
                cout << "Goodbye..." << endl;
                exit = true;
                break;
            default: //Invalid input
                break;
        }
    }
    return 0;
}