#pragma once
#include <include.h>
#include <unordered_set>
#include <fstream>

class c_checker {
public:
	std::unordered_set<std::string> generatedUsernames;  // To keep track of generated usernames
	void checkRandom(int length); //will generate random usernames and check them 
	bool checkUsername(std::string username); //check username
	std::string randomString(int length); //will generate random strings

	void saveUsername(std::string username, std::string path); 
};

inline c_checker checker;