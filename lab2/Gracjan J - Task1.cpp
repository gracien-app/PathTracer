#include <iostream>
#include <exception>


class FormulaDriver : public std::exception
{
    int speed;

    public:

        const char* what()
        {
            return "You are going to crash, but you have done this task\n";
        }

        void setSpeed(int speed)
        {
            this->speed = speed;
        }
};

class Bolid
{
    int speed;

    public:
        Bolid()
        {
            speed = 0;
        }

        void accelerate()
        {
            for (int n = 4; n < 100; n++)
            {
                speed = speed + 5 * n;
                std::cout << "Your current speed is: " << speed << "\n";
                if (speed >= 300)
                {
                    FormulaDriver exc;
                    exc.setSpeed(speed); // Also use a setSpeed() function to transfer speed from this class to another
                    
                    throw exc; // Here you must throw an exception
                }
            }
        }

};

int main()
{
    // In main function you must use try and catch blocks to handle the exception
    // In catch block you should call out what() function
    
    try {
        Bolid Williams;
        Williams.accelerate();
    }
    catch (FormulaDriver Senna) {
        std::cerr << Senna.what() << std::endl;
    }

    return 0;
}

