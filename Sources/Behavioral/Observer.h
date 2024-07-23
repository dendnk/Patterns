// Create a stock price monitoring application.
// This application should notify multiple observers whenever the stock price changes.
// Each observer can then react accordingly, such as logging the new price or making a decision based on the price change.

// Requirements
// Subject(Observable) Class: This class will manage and notify observers about changes in stock prices.
// Observer Interface : This interface will define the Update method, which observers must implement to react to changes.
// ConcreteObserver Classes : Implement at least two different types of observers that react to stock price changes.
// ConcreteSubject Class : This class will extend the Subject class and will store the stock price.

#pragma once

namespace Observer
{

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Update(float newPrice) = 0;
};

class Subject
{
public:
	virtual ~Subject() = default;

	void Attach(std::shared_ptr<Observer> observer)
	{
		Observers_.emplace_back(observer);
	}

	void Detach(std::shared_ptr<Observer> observer)
	{
		Observers_.remove(observer);
	}

	void SetPrice(float newPrice)
	{
		CurrentPrice_ = newPrice;
		Notify();
	}

	void Notify()
	{
		for (const auto& CurrentObserver : Observers_)
		{
			CurrentObserver->Update(CurrentPrice_);
		}
	}

private:
	float CurrentPrice_;

	std::list<std::shared_ptr<Observer>> Observers_;
};

class Stock : public Subject
{
public:
	void SetStockPrice(float price)
	{
		SetPrice(price);
	}
};

class Logger : public Observer
{
public:
	void Update(float newPrice)
	{
		std::cout << "Logging new stock price : " << newPrice << std::endl;
	}
};

class Investor : public Observer
{
	void Update(float newPrice) override
	{
		if (newPrice > 100.0f)
		{
			std::cout << "Investor: Price is above 100. Consider selling." << std::endl;
		}
		else
		{
			std::cout << "Investor: Price is below 100. Consider buying." << std::endl;
		}
	}
};


void TestObserverPattern()
{
	auto stock = std::make_shared<Stock>();

	auto logger = std::make_shared<Logger>();
	auto investor = std::make_shared<Investor>();

	stock->Attach(logger);
	stock->Attach(investor);

	stock->SetStockPrice(95.0f);
	stock->SetStockPrice(105.0f);

	stock->Detach(investor);
	stock->SetStockPrice(69.0f);
}

} // namespace Observer
