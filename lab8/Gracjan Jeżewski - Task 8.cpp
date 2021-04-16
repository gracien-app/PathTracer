#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

/// REGEX ///
void task1()
{
    //use std::regex to create regular expressions
    //There are two regular expressions already declared for you - your task is to assign them accordingly to their purpose:
    //rx0 has to find every word that begins with an uppercase letter
    //rx1 has to find every word that contains "or" in it
    string text = "Lorem ipsum dolor sit amet, Consectetur adipiscing elit, Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    string rx0text = text;
    string rx1text = text;
    
    // Begins with upppercase A-Z
    regex rx0 ("\\b([A-Z].*?)\\b"); // <-- assign this
    
    // OR
    regex rx1 ("([\\w]*(or)[\\w]*)"); // <-- assign this

    smatch smatch1;

    // loop to write out the matched words into the console
    while(regex_search(rx0text, smatch1, rx0))
    {
        cout << smatch1.str(1) << endl;
        rx0text = smatch1.suffix().str();
    }
    cout << endl;

    // loop to write out the matched words into the console
    while(regex_search(rx1text, smatch1, rx1))
    {
        cout << smatch1.str(1) << endl;
        rx1text = smatch1.suffix().str();
    }
}

void task2()
{
    //use sregex_iterator
    //Here your task is to find out the number of occurrences of the words "ring" and "hobbit" within the text file
    //Those words can occur in the text in both upper- and lowercase letters
    //Words like "rings" or "hobbits" are allowed, but words like "during" or "ringmaker" aren't
    string txt;
    ifstream file("task2.txt");
    regex rx2 ("\\b(?:[Rr]ing[s]?|[Hh]obbit[s]?)\\b"); // <-- assign this


    int sum_of_occurrences = 0;
    if(file.is_open())
    {
        while(getline(file, txt))
        {
            // create two sregex_iterators here - one containing variables, the other empty
            std::sregex_iterator Iter;
            std::sregex_iterator Iter2 (txt.begin(), txt.end(), rx2);
             
            // then use the std::distance() function, assign it to an integer and pass two iterators to it as variables
            int distBetweenIter = distance(Iter, Iter2);
            
            // lastly, add the result of the line to the overall sum_of_occurrences number
            sum_of_occurrences += distBetweenIter;
            
        }
        file.close();
    }
    cout << "Sum of occurrences: " << sum_of_occurrences << endl;
}

void task3()
{
    //using regex_replace
    //for the first text, you can use any regex you want to change anything in this sentence
    //for the second text, there are multiple digits inserted randomly into it - your task is to use regex to remove them
    string before1 = "To be or not to be, that is the question";
    string after1;
    regex rx3 ("(or)"); // <-- assign this

    after1 = regex_replace(before1, rx3, "and");
    
    cout << after1 << endl;
    cout << "-------------" << endl;

    string before2 = "Far ov8er the m13isty mounta2ins cold \n"
                     "To du3nge45ons dee45p an2d ca3verns 7old \n"
                     "We 2must awa4y, ere br7eak of d89ay";
    string after2;
    regex rx4 ("\\d"); // <-- assign this

    after2 = regex_replace(before2, rx4, "\0");
    cout << after2 << endl;
}

int main()
{
    task1();
    task2();
    task3();
    return 0;
}
