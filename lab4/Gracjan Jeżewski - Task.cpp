#include <iostream>
#include <map>

/*
Task
For text "Baba bada baobaby. Baba dba o oba baobaby." count the occurences of each word.
Use std::map for storing the results.
Hint: One of the possible solutions has 15 lines of code. Do NOT overengineer yours.

Output:
baba	  2
bada	  1
baobaby	2
dba	    1
o	      1
oba	    1
*/

////////////////////////////////////////////////////////////////////////////////
// do not touch
int main()
{
  const char input[] = "Baba bada baobaby. Baba dba o oba baobaby.";
  std::map<std::string, unsigned int> output;
////////////////////////////////////////////////////////////////////////////////

  // Write your solution here
  // ...
    std::string word;
    int counter = 0;
    while (input[counter] != '\0') {
        if (input[counter] != ' ' && input[counter] != '.') {
            word+=input[counter];
        }
        else if (word != ""){
            if (output.find(word) != output.end()) {
                output.find(word)->second+=1;
            }
            else output.insert({word, 1});
            word = "";
        }
        counter++;
    }

////////////////////////////////////////////////////////////////////////////////
// do not touch
  for (auto & pair : output)
    std::cout << pair.first << '\t' << pair.second << '\n';

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
