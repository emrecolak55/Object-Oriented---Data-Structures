#include <iostream>
#define MAX_COURIERS 10

using namespace std;

class Person {
	protected:
	string name,surname;
	public:
	Person(){}
	Person(string,string);
	string getname(){
		return name;
	}
	string getsurname(){
		return surname;
	}
	~Person();
};

class Owner : public Person {
	float ownership;
	public:
	void print();
	void editownership(int);
	operator bool();
	Owner(string, string);
	Owner(){}
	~Owner();
};

class Courier : public Person {
	
	string vehicle;	
	public:
		string getname(){
		return name;
	}
	string getsurname(){
		return surname;
	}
	string returnvehicle(){
		return vehicle;
	}
	Courier(){}
	Courier(string, string, string);
	~Courier();
	operator bool();
};


class Business {
	string name, address;
	int ownernum; // gereksizse sil
	int couriernum;
	Owner* owners;
	Courier* head;

public:
	void hire_courier(Courier&);
	void fire_courier(Courier&);
	void list_couriers();
	void list_owners();
	int calculate_shipment_capacity();
	
	void operator()();
	const Courier& operator[](int); // check check check check
	Business(){
	}
	Business(string, string, Owner* givenowner, int);
	~Business() {
		delete[] head;
	}
};
// FUNCTIONS -----------------------------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Business::hire_courier(Courier& courier) {

	for (int i = 0;i <MAX_COURIERS;i++) {
		if (!head[i]) {
			head[i] = courier;
			couriernum++;
			break;
		}
	}

}


void Business::list_owners(){
	int i = 0;
	for (i ; i<ownernum ; i++){
		owners[i].print();
	}
}

void Business::fire_courier(Courier& courier) {
	for (int i = 0; i < MAX_COURIERS; i++) {
		if (head[i].getname() == courier.getname() && head[i].getsurname() == courier.getsurname()) {
			for (int j = i; j <MAX_COURIERS-1; j++) {
				
				head[j] = head[j + 1];
			}
			couriernum--;
			break; 
		}
	}
}



int Business::calculate_shipment_capacity() {
	int i = 0;
	int capacity = 0;
	while (head[i]) {
		
		if(head[i].returnvehicle() == "car"){
			capacity+=200;
		}
		else if(head[i].returnvehicle() == "bicycle"){
			capacity+=10;
		}
		else if( head[i].returnvehicle() == "motorcycle") {
			capacity += 35;
		}
		else {
			cout << "invalid vehicle type";
		}
		i++;
	}
	return capacity;
}

void Business::list_couriers(){

	for(int i=0;i<couriernum;i++){
		if(!head[i]){continue;}
		cout << head[i].getname() << " ";
		cout << head[i].getsurname() << " ";
		cout << head[i].returnvehicle() << endl;
	}
}

	const Courier& Business::operator[](int i) {
	
		return head[i];

	}
	void Business::operator()() {
		cout << name << " " <<  address<<endl;
		list_owners();
		list_couriers();
	}

                                                                      // CONSTRUCTORS //                                                

	Person::Person(string givenname,string givensurname){
		name= givenname;
			surname = givensurname;
	}
	
	Courier::Courier(string givenname, string givensurname, string givenvehicle){
		name = givenname;
		surname = givensurname;
		vehicle = givenvehicle;
	}
	
	Business::Business(string givenname, string givenaddress, Owner* givenowner, int numofowner) {
		head = new Courier[MAX_COURIERS];
		couriernum=0;
		owners = givenowner;
		ownernum=numofowner;
		name = givenname;
		address = givenaddress;
			for(int i=0; i<numofowner;i++){
				owners[i].editownership(numofowner);
			}
	}
	
	Owner::Owner(string givenname, string givensurname){
		name = givenname;
		surname = givensurname;
		ownership=100;
	}
	
	void Owner::print(){
	cout << name<< " ";
		cout << surname<< " ";
		cout << ownership<<endl;
	}
	
	void Owner::editownership(int x){
		ownership = 100.0/ x;
	}
	
	Person::~Person(){
	}
	Owner::~Owner(){
	}
	Courier::~Courier(){
	}
	
	Owner::operator bool(){
		if(ownership<=100 && ownership>=0){ // 100 as percentage
			return 1;
		}
		else {
			cout << ownership;
			return 0;
		}
	}
	Courier::operator bool() {
		
		if(vehicle=="car" || vehicle=="motorcycle" || vehicle == "bicycle"){
			return 1;
		}
		else {
			return 0;
		}
	}
