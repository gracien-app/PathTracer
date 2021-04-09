#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include <map>
#include <fstream>
/*
Your goal in this task is to present the amount of certain characters in a text file.
To make the output look better, change every character into lowercase.
Output should look like this:
dummny1.txt
a 10
b 5
c 7
.
.
.
z 1
dummny2.txt
.
.
.
Total number of letter: 999

*/

// This guy should be used
std::mutex mut;
// Make sure there is no race with this var
unsigned int total_characters = 0;

void count_characters (std::string file_name) {
    
    std::map <char, unsigned int> output;
/*======= Here comes your solution =======*/
    
    std::ifstream fileStream;
    fileStream.open(file_name);
    char character;
    
    if ( fileStream.is_open() ) {
        
        std::map <char, unsigned int>::iterator findIter;
        
        while ( fileStream >> character ) {
            
            findIter = output.find(std::tolower(character));
            
            if (findIter == output.end()) {
               output.insert( std::pair<char, unsigned int>
                            (  std::tolower(character), 1) );
            }
            else findIter->second++;
            
            mut.lock();
            total_characters++;
            mut.unlock();
            
        }
    }


/*======= Make sure this is printed in the right way  =======*/
    mut.lock();
    
	for (auto & pair : output)
    std::cout << pair.first << '\t' << pair.second << '\n';
    
    mut.unlock();
}

int main()
{
	std::string file_names[] = {"dummy1.txt", "dummy2.txt", "dummy3.txt"};
	/*======= Here you have to manage the threads =======*/
	
    std::thread firstFileThread (&count_characters, file_names[0]);
    std::thread secondFileThread (&count_characters, file_names[1]);
    std::thread thirdFileThread (&count_characters, file_names[2]);

    firstFileThread.join();
    secondFileThread.join();
    thirdFileThread.join();
    
	std::cout << "Total number of characters " << total_characters << std::endl;

	return 0;
}
