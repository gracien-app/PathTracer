#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

//In this task you have been given a vector with a pair of string and int. It represents a student name and their points from exam.
//You will need to perform tasks that are given to you. Write code only below a task, do not change any structures or functions that are 
//not in a taks. Good luck


template <typename T>
void print(T container) {
	for (auto& x : container) {
		std::cout << x.first << " " << x.second << std::endl;
	}
	std::cout << std::endl;
}


//you will need this in one task, try to guess what it does
bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
	return (a.second > b.second);
}

int main()
{
	//Here we have a vector with students and their exam points
	std::vector<std::pair<std::string, int>> students = {
		{"Amanda",25}, {"Juan", 15},{"Luiz", 8},{"Ben",25},{"Pablo",16}, {"Tom",23},{"Rebbeca",10} };

	std::vector<std::pair<std::string, int>> n = { {"Geralt", 24}, {"Judy", 3}, {"Robert",8}, {"Matthew", 1}, {"Angel",19} };

	//////////////////////////
	//-----------1-----------
	//It turns out some students were not on the list, add them in only one line of code at the end of vector called students
	//Tip: You will need to use a specific kind of iterator.
	//write the code below

    std::copy(n.begin(), n.end(), std::back_inserter(students));

	//Outcome:
	std::cout << "All students:" << std::endl;
	print(students);

	//////////////////////////
	//-----------2-----------
	//Find minimum amount of points and the name of student that obtained them.
	//Tip: Use a lambda with a loong parameter field.
	//Write the code below

	int minPoints = -1;
	std::string minName = "";
    auto iter = std::min_element(students.begin(), students.end(), [] (const auto& lhs, const auto &rhs) {
        return !sortbysec(lhs,rhs);
    });
    
    minName = iter->first;
    minPoints = iter->second;
    
	//Outcome:
	std::cout << minName << " got minimal amount of " << minPoints << " and is a big doofus.\n" << std::endl;

	//////////////////////////
	//-----------3-----------
	//Using one line copy the students that had >15 points from students to best.
	//Use of a lambda funtion is preffered in this task.
	//Tip: Remember that our vector has a std::pair and the lambda function will need this information
	//write the code below

	std::vector<std::pair<std::string, int>> best;

    std::copy_if(students.begin(), students.end(), std::back_inserter(best), [](const auto &elem) {
        return elem.second > 15;
    });

	//////////////////////////
	//-----------4-----------
	//Sort the best vector by points in decreasing order
	//Tip: Do it in ine line, use one of the functions declared at the top (or a lambda ;) )
	//write the code below

    std::sort(best.begin(), best.end(), [](const auto &lhs, const auto &rhs) {
        return sortbysec(lhs, rhs);
    });

	//Outcome:
	std::cout << "Best students" << std::endl;
	print(best);

	//////////////////////////
	//-----------5-----------
	//End the decleration so it will have the number of students that passed with t (25) points, try to use a lambda function.
	//Tip: You will have to capture the t variable.
	//Write the code below

	int t = 25;
	int count = 0;
    
    count = std::count_if(best.begin(), best.end(), [&t](const auto &elem) {
        return (elem.second == t);
    });


	//Outcome:
	std::cout << "Number of students with max points:" << count << "\n" << std::endl;

	//////////////////////////
	//-----------6-----------
	//Just to chceck who might've been cheating, find points and names of students that got the same amount of points and print them in pairs. No need to store them.
	//Tip: The algorithm you're supposed to use needs the data to be sorted. This task might even require a whooping 15 lines of code! Make use of iterators and two algorithms.
	//Tip: Look Tip 2 and 4. 
	//Tip: Luiz and Robert sit together, whatch out for them.
	//Write the code below

    std::sort(students.begin(), students.end(), [](const auto &lhs, const auto &rhs) {
        return sortbysec(lhs, rhs);
    });
    
    auto samePoints = students.begin();
    
    while (true) {
        
        samePoints = std::adjacent_find(samePoints, students.end(), [](const auto &lhs, const auto rhs) {
            return lhs.second == rhs.second;
        });
        
        if (samePoints != students.end()) {
            std::cout << samePoints->first << " got same ammount of points as " << (samePoints+1)->first << "\n";
            samePoints++;
        }
        else break;
    }
    
    
	//////////////////////////
	//-----------7-----------
	//Check at which position is Tom, your favourite student.
	//Write the code below

	int position = -1;

    position = std::find_if(students.begin(), students.end(), [](const auto &elem) {
        return (elem.first == "Tom");
    }) - students.begin();


	//Outcome:
	std::cout << "\nTom found at position:" << position << '\n' << std::endl;

	//////////////////////////
	//-----------8-----------
	//Thinking back on it, you feel kind of bad for poor Matthew. Raise his points so that they are equal to the second to last person using a reverse iterator.
	//Hint: The data is already sorted, this should be easy.
	//Write the code below
    
    auto findMatthew = std::find_if(students.begin(), students.end(), [](const auto &elem) {
        return ( elem.first == "Matthew" );
    });
    
    std::reverse_iterator<std::vector<std::pair<std::string, int>>::iterator> revIter = students.rbegin();
    std::advance(revIter, students.size()-2);
    
    findMatthew->second = revIter->second;
    
    std::cout << "Matthew now has " << findMatthew->second << " points.\n";

	return 0;
}

