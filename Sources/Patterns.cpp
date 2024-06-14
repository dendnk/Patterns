// Patterns.cpp : Defines the entry point for the application.

#include "Patterns.h"

#include <iostream>
#include "ChainOfResponsibility.h"
#include "Command.h"

int main()
{
	std::cout << "\nProject Version: " << PATTERNS_VERSION_MAJOR << "."
									 << PATTERNS_VERSION_MINOR << "."
									 << PATTERNS_VERSION_PATCH << std::endl;

	std::cout << "Current changelist hash : " << GIT_COMMIT_HASH << std::endl;
	std::cout << "Commit message : " << GIT_COMMIT_MESSAGE << std::endl;
	std::cout << "Author : " << GIT_COMMIT_AUTHOR << std::endl;
	std::cout << "Time : " << GIT_COMMIT_TIME << std::endl;

	std::cout << "\n=== ChainOfResponsibility Pattern ===\n";
	ChainOfResponsibility::TestChainOfResponsibilityPattern();

	std::cout << "\n=== Command Pattern ===\n";
	Command::TestCommandPattern();

	return 0;
}
