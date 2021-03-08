#include <iostream>

class User
{
private:
    int age;

public:
    User(int w)
    {

    // This is supposed to be a registration aplication
    // Correct range for users to register into this aplication is 18-100 years old
    // The program should print 4 types of messages:
    // - when your age is lower than 0
    // - when your age is higher than 0 but lower than 18
    // - when your age is correct (range 18-100)
    // - when your age is higher than 100
    // To obtain such a solution use throw blocks here for 3 incorrect scenarios
    // Remember to throw different types of data for each of the scenario!
        if (w>=18 && w<=100) {
            std::cout << "Application registration successful" << std::endl;
            age = w;
        }
        else {
            if (w<0) throw -1; //Throws int
            if (w>=0 && w<18) throw "User too young to register"; //throws const char*
            if (w>100) throw 'E'; //Throws char
        }
    }
};

int main()
{
    // The program needs to write different, appropiate message for each of the errors
    // Here you must use try and catch blocks
    // Call the user whatever name you want
    // When you are done, check if ur solution works for any age
    try {
//        User User1(101);
//        User User1(-23);
//        User User1(18);
        User User1(2);
    }
    catch (int err) {
        std::cerr << "Error: Age can't be smaller than 0: ErrorID(" << err << ")\n";
    }
    catch (const char* err) {
        std::cerr << "Error: " << err << std::endl;
    }
    catch (char err) {
        std::cerr << "Error: Thrown with identifier: 0x" << err << std::endl;
    }
    

    
    return 0;
}
