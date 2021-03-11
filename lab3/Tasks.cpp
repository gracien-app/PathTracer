#include <iostream>

//MARK: TASK 1

// Task 1 should teach how to use the template functions.
/*
Write the template function returning:
- result of multiplication of two arguments              ->that function should be able to handle variables of two different types
- result of division of two arguments ( first/second )   ->that function should be able to handle variables of one type
- result of sum of squares                               ->that function should be able to handle variables of two different types,
                                                           and additionally write a specialized template for int and double type ( first argument int and the second double )
*/

// Here you should declare your template functions

// Take note that the return type used while declaring function matters !!
// HINT  If you name your functions by the name they are called by in main you will save some time ;)

//Declare the function template here
template <typename tA, typename tB>
tA multiplication (tA x, tB y)
{
    //I believe auto and decltype should be used instead of return type Ta, but I did it according to the presentation where such functionality was not mentioned.
    return x*y;
};

//Declare the function template here
template <typename T>
T division (T x, T y)
{
    return x/y;
};

//Declare the function template here
template <typename tA, typename tB>
tB sum_of_squares (tA x, tB y)
{
    return (x*x) + (y * y);
};

//Declare the function template here
template <>
double sum_of_squares(int x, double y)
{
    std::cout << "The specialized template has been used!! result: ";
    return (x*x) + (y * y);
    // While passing the int and double arguments the line from above should be printed
};


//MARK: TASK 2

// Task2
// 1. Write class template with three different data types as arguments. Then in main generate and add the class code. You can check with cout if your class arguments are appropriately filled. Try it for 3 different sets of data.
template <typename tA, typename tB, typename tC> //here you must fill in class identifier
class Personal_info
{
public:
    tA _name;
    tB _age;
    tC _height;
    //Here you can create the three arguments.

    Personal_info(tA name, tB age, tC height) : _name(name), _age(age), _height(height) //Fill a constructor which will take arguments for name age and height.
    {
        std::cout << "Constructed" << std::endl;
    }
};

int main(){
    
    //MARK: TASK 1
    
    // If you like, you can change the names of functions
    std::cout << " Result of multiplication of two arguments: " << multiplication(7.4, 2)  << "\n";
    std::cout << " Result of division of two arguments ( first/second ): " << division(18, 6)  << "\n";
    std::cout << " Result of sum of squares: " << sum_of_squares('a', 'b')  << "\n";  //  <- The normal numbers may be normal numbers as well
    std::cout << " Result of sum of squares: " << sum_of_squares(7, 2.5)  << "\n";

    //MARK: TASK 2
    
    //Here call the constructor so it will generate a class code. Test it 3 times, with different order or data type.
    Personal_info<const char*, int, float> person1 ("Gracjan", 21, 177);
    
    Personal_info<float, const char*, int> person2 (184, "John", 18 );
    
    Personal_info<char,double, unsigned> person3 ('A', 167.76, 74);
    
    std::cout << person1._name << std::endl;
    std::cout << person2._name << std::endl;
    std::cout << person3._name << std::endl;
    

   return 0;
}

