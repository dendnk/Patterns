// Patterns.cpp : Defines the entry point for the application.

#include "Patterns.h"

#include <iomanip>
#include <iostream>

#include "Behavioral/ChainOfResponsibility.h"
#include "Behavioral/Command.h"
#include "Behavioral/Iterator.h"
#include "Behavioral/Mediator.h"
#include "Behavioral/Memento.h"
#include "Behavioral/Observer.h"
#include "Behavioral/State.h"
#include "Behavioral/Strategy.h"
#include "Behavioral/TemplateMethod.h"
#include "Behavioral/Visitor.h"

int main()
{
	std::cout << "\n";
	std::cout << std::left << std::setw(30) << "Project Version: "
											<< PATTERNS_VERSION_MAJOR << "."
											<< PATTERNS_VERSION_MINOR << "."
											<< PATTERNS_VERSION_PATCH << std::endl;

	std::cout << std::left << std::setw(30) << "Current changelist hash : "
											<< GIT_COMMIT_HASH << std::endl;
	std::cout << std::left << std::setw(30) << "Commit message : " << GIT_COMMIT_MESSAGE << std::endl;
	std::cout << std::left << std::setw(30) << "Author : " << GIT_COMMIT_AUTHOR << std::endl;
	std::cout << std::left << std::setw(30) << "Time : " << GIT_COMMIT_TIME << std::endl;

	//std::cout << "\n=== ChainOfResponsibility Pattern ===\n";
	//ChainOfResponsibility::TestChainOfResponsibilityPattern();

	//std::cout << "\n=== Command Pattern ===\n";
	//Command::TestCommandPattern();

	//std::cout << "\n=== Iterator Pattern ===\n";
	//Iterator::TestIteratorPattern();

	/*std::cout << "\n=== Mediator Pattern ===\n";
	Mediator::TestMediatorPattern();*/

	//std::cout << "\n=== Memento Pattern ===\n";
	//Memento::TestMementoPattern();

	//std::cout << "\n=== Observer Pattern ===\n";
	//Observer::TestObserverPattern();

	/*std::cout << "\n=== State Pattern ===\n";
	State::TestStatePattern();*/

	//std::cout << "\n=== Strategy Pattern ===\n";
	//Strategy::TestStrategyPattern();

	//std::cout << "\n=== TemplateMethod Pattern ===\n";
	//TemplateMethod::TestTemplateMethodPattern();

	std::cout << "\n=== Visitor Pattern ===\n";
	Visitor::TestVisitorPattern();

	return 0;
}
