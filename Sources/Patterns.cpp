// Patterns.cpp : Defines the entry point for the application.

#include "Patterns.h"

#include <iostream>
#include "ChainOfResponsibility.h"

int main()
{
	std::cout << "Project Version: " << PATTERNS_VERSION_MAJOR << "." 
									 << PATTERNS_VERSION_MINOR << "."
									 << PATTERNS_VERSION_PATCH << std::endl;
	
	std::cout << "Current changelist info:\n";
	std::cout << "Hash: " << GIT_COMMIT_HASH <<
				 " Commit message: " << GIT_COMMIT_MESSAGE <<
				 " Author: " << GIT_COMMIT_AUTHOR << 
				 " Time : " << GIT_COMMIT_TIME << std::endl << std::endl;
	
	ChainOfResponsibility::TestChainOfResponsibility();

	return 0;
}
