#pragma once

#include <iostream>
#include <memory>
#include <string>

// Chain of Responsibility (CoR) is a behavioral design pattern that lets you pass requests along a chain of handlers.
// Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain.

//	Consider the task of creating a system for processing requests for access to resources in a corporate network.
//  This network has several access levels, each of which must process requests differently:
//	User: Can access basic resources.
//	Manager : Can approve requests for access to more important resources.
//	Administrator : Can approve access to critical resources and perform administrative tasks.

//	Each level must be able to pass a request to the next level if it cannot handle it.

namespace ChainOfResponsibility
{

using namespace std;

string StringBasicResource			= "BasicResource";
string StringImportantResource		= "ImportantResource";
string StringCriticalResource		= "CriticalResource";
string StringAdministrativeTask		= "AdministrativeTask";
string StringTestRequest			= "TestRequest";
string StringRequestWasNotHandled	= "RequestWasNotHandled";

class Handler
{
public:
	virtual ~Handler() = default;
	virtual shared_ptr<Handler> SetNext(shared_ptr<Handler> handler)
	{
		Next = handler;
		return handler; // allow to connect handlerslike this : handlerA->SetNext(handlerB)->SetNext(handlerC)
	}

	virtual std::string Handle(const std::string& request)
	{
		if (Next != nullptr)
		{
			Next->Handle(request);
		}

		return StringRequestWasNotHandled;
	}

private:
	shared_ptr<Handler> Next;
};

class CUserHandler : public Handler
{
public:
	std::string Handle(const std::string& request) override
	{
		string result = __FUNCSIG__;

		if (request == StringBasicResource)
		{
			result.append(" : Handling request for " + request + "\n");
		}
		else
		{
			result.append(" : Passing request to next handler\n");
			result.append(Handler::Handle(request));
		}

		cout << result;
		return result;
	}
};

class CManagerHandler : public Handler
{
public:
	std::string Handle(const std::string& request) override
	{
		string result = __FUNCSIG__;

		if (request == StringImportantResource)
		{
			result.append(" : Handling request for " + request + "\n");
		}
		else
		{
			result.append(" : Passing request to next handler\n");
			result.append(Handler::Handle(request));
		}

		cout << result;
		return result;
	}
};

class CAdministratorHandler : public Handler
{
public:
	std::string Handle(const std::string& request) override
	{
		string result = __FUNCSIG__;

		if (request == StringCriticalResource || request == StringAdministrativeTask)
		{
			result.append(" : Handling request for " + request + "\n");
		}
		else
		{
			result.append(" : Passing request to next handler\n");
			result.append(Handler::Handle(request));
		}

		cout << result;
		return result;
	}
};

void TestChainOfResponsibility()
{
	cout << __FUNCSIG__ << endl;

	auto UserHandler = make_shared<CUserHandler>();
	auto ManagerHandler = make_shared<CManagerHandler>();
	auto AdminHandler = make_shared<CAdministratorHandler>();

	UserHandler->SetNext(ManagerHandler)->SetNext(AdminHandler);

	string requests[] = { StringBasicResource, StringImportantResource, StringCriticalResource, StringAdministrativeTask, StringTestRequest };

	for (const auto& request : requests)
	{
		cout << "Sending request for " << request << endl;
		UserHandler->Handle(request);
		cout << "\n";
	}
}

}; // namespace ChainOfResponsibility
