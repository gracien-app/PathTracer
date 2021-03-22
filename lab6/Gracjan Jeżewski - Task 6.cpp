#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Car
{
public:
	Car() : type("Sedan") {}
	Car(string t) : type(t) {}

	void displayType()
	{
		cout << "Type of the car: " << type << endl;
	}

private:
	string type;
};

struct Motorcycle {
	Motorcycle(string n) : name(n) {}
	void displayName()
	{
		cout << "Name of the motorcycle: " << name << endl;
	}
	string name;
};

vector<shared_ptr<Car>> cars;

void uniquePointer()
{
	//Create unique pointer to Car class use make_unique and name the car however you like
    auto ptr1 = make_unique<Car>("Hatchback");
	//Display type of the Ccr
    ptr1->displayType();
	//Create second unique pointer to class Car, transfer control from the first pointer
    auto ptr2 = move(ptr1);
	//Display type of the car using second pointer
    ptr2->displayType();
	//What if you would try to display car type from first pointer? Check. Why?
    if (ptr1) ptr1->displayType(); // Pointer is empty, program breaks at this point when executed without any checks.
}

//Design a function printing number of references of given pointer
//Function should take any shared pointer
//Ensure, that this function will not interfere in reference count
template<typename T>
void displayReferencesCount(std::shared_ptr<T> &ptr)
{
    const auto count = ptr.use_count();
	//Print number of references from passed pointer
    std::cout << "References count: " << count << " for object of type: " << typeid(T).name() << std::endl;
}

//Function should take shared pointer without interfering into reference count
void sharedPointer(std::shared_ptr<Car> &ptr)
{
	cout << endl;
	//Display reference count to check if everything works fine
    displayReferencesCount(ptr);
	{
		//Copy passed pointer to the new one
        shared_ptr<Car> get_Ptr = ptr;
		//Display references count of the original pointer
        displayReferencesCount(ptr);
		//Insert copy into cars vector
        cars.push_back(get_Ptr);
		//What is the count of the references now?
        displayReferencesCount(ptr);
		//Display type of car
        ptr->displayType();
	}
	//What is the difference in count? Check
    displayReferencesCount(ptr);
    displayReferencesCount(cars[cars.size()-1]);
	cout << endl;
}

//Pass shared pointer of type Car
void resetPointer(std::shared_ptr<Car> ptr)
{
	cout << endl;
	//Display reference count of pointer
    displayReferencesCount(ptr);
	//Reset pased pointer so it holds another one, car should have different name
    ptr.reset(new Car("Definitely not used name"));
	//Display car type
    ptr->displayType();
	//Display reference count of pointer
    displayReferencesCount(ptr);
	cout << endl;
}

void getRaw()
{
	//Create shared pointer to Motorcycle class with whatever name
    auto moto_Shared = make_shared<Motorcycle>("Caferacer");
	//Create raw pointer to the same member as shared pointer
    Motorcycle* moto_Raw = moto_Shared.get();
	//Display motorcycle's name from shared and raw pointers
    moto_Shared->displayName();
    moto_Raw->displayName();
	//Check reference count of shared pointer, is it incremented or not, why?
    displayReferencesCount(moto_Shared); //It's not because of get() method, we extracted raw pointer.
	//What would happen, when the raw pointer gets deleted? Check. Why?
//    delete moto_Raw; // Unsuccessful deletion of pointer
}

void weakPointer()
{
	cout << endl;
	//Create a shared pointer
    auto ptr = make_shared<Car>("Audi");
	//Print its use count
    displayReferencesCount(ptr);
	//Create a weak pointer that observes it
    std::weak_ptr<Car> weak_ptr = ptr;
	//Display reference count. What are the values?
    displayReferencesCount(ptr);
    std::cout << "Ref count of weak ptr: " << weak_ptr.use_count() << std::endl;
	//Assign a weak pointer to a shared pointer
    auto assign_ptr = weak_ptr.lock();
	//Check that the weak pointer is not empty
    if (weak_ptr.expired()) cout << "Weak is empty at this moment.\n";
    else cout << "Weak is not empty.\n";
	//Assign a weak pointer to another weak pointer
    std::weak_ptr<Car> new_weak;
    weak_ptr = new_weak.lock();
	//Display reference count of a weak pointer
    std::cout << "Ref count of weak ptr: " << weak_ptr.use_count() << std::endl;
	//Assign a weak pointer to another shared pointer
    std::shared_ptr<Car> new_shared = weak_ptr.lock();
	//Display reference count of a weak pointer
    std::cout << "Ref count of weak ptr: " << weak_ptr.use_count() << std::endl;
	cout << endl;
}


//Check for additional instructions
int main()
{
	uniquePointer();
	//Create shared pointer of type Car("name_of_your_Car")
    std::shared_ptr<Car> car1 = make_shared<Car>("My_new_car");
	//Pass it to the function below
	sharedPointer(car1);
	//Pass it to the function below
	resetPointer(car1);
	cout << endl;
	//Display type of Car from vector Cars
	cars.at(0)->displayType();
	//Display its reference count
	displayReferencesCount(cars.at(0));
	cout << endl;
	getRaw();
	weakPointer();
}
