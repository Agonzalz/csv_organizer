/* 

NOTES TO SELF: Worth looking into randomization and number generators

Draft Requirements: 
-User input and interface.
- keep title bar even in filtered lists. 
- formatting so that content remains in line with title bar. 
- output only desired info. (can use split line for this)
 -user input for the file when ruunning the program (lets try the command line for now)
    -eventually just try getting it possibly from the url 
 -user input for the type of randomization based off of the filters specified
    - randomization is done. Now need to combine it with filtered list. 
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>


//checks if vector contains a string. Not useful yet 
// bool in_vector(const std::vector<std::string> &vector, const std::string &str) {
//     return std::find(vector.begin(),vector.end(),str) != vector.end();
// }

std::string booltostring (bool value) {
    if (value == true) {
        return "True";
    }
    else {
        return "False";
    }
}

//splits a string or line from file into a vector of strings for each word in the line
std::vector<std::string> split_line(const std::string &line, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(line);
    while(std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

//used for filtering for checknboxes and True or False categories
std::vector<std::string> bool_checker( std::vector<std::string> lines, bool value){
    std::vector<std::string> filteredline;
    for(std::string line:lines) {
        if (line.find(booltostring(value)) != std::string::npos) {
            filteredline.push_back(line);
        }
    }
    return filteredline;
}


void printlines(std::vector<std::string> contents) {
    std::cout << "================================================================================" << std::endl;
    for (const std::string &field: contents) {
            std::cout << field << std::endl;
    }
    std::cout << "================================================================================" << std::endl;
}


std::string random_select(std::vector<std::string> &list) {
    std::random_device seed;    //creates a random seed from random source
    std::mt19937 gen(seed());   //generates an instance of Mersenne Twister 19937 pseudorandom number generator with the seed
    std::uniform_int_distribution<> dis(1, list.size()-1);  //generates a rand int between specified range in dis() aka distance. This line specifies the range. Initilization
    int randomIndex = dis(gen);     //generates random int from distribution in dis and the generator gen; This combo only produces a random number from specified range
    return list[randomIndex];
}


int main(int argc, char* argv[]) {
    
    std::cout << "reading from csv file: " << argv[1] << std::endl; 

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file" << std::endl; 
        return 1;
    }

    std::vector<std::string> list;
    std::string line;
    while(std::getline(file, line)) {
        //std::vector<std::string> fields = split_line(line, ',');
        list.push_back(line);
    }
    file.close();
    int user_choice;
    while(user_choice != 4) {
        std::cout << "\n What do you want to do with your file? \n" 
                  << "1. list the whole file\n"
                  << "2. Random Item \n"
                  << "3. Filter \n"
                  << "4. exit \n\n"
                  << ">> ";
        std::cin >> user_choice;
        std::cout << "\n";

        if (user_choice == 1) {
            printlines(list);
        }
        else if (user_choice == 2) {
            std::cout << "===========================================================================\n"
                      << random_select(list)
                      <<"\n============================================================================"
                      << std::endl;
        }
        else if (user_choice == 3) {
            std::vector<std::string> filtered_list = bool_checker(list, false);
            printlines(filtered_list);
        }
        else{
            std::cout << "not a valid option" << std::endl;
        }
        
    }

    return 0;
}