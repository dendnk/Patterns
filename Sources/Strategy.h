// You are tasked with developing a simple payment processing system for an e-commerce application.
// The system should support multiple payment methods(e.g., credit card, PayPal, and Bitcoin).
// Each payment method should have its own implementation of the payment process.

// Requirements :
// - Create an abstract class PaymentStrategy that defines the interface for payment processing.
// - Implement concrete strategies for different payment methods(CreditCardPayment, PayPalPayment, BitcoinPayment).
// - Create a PaymentContext class that uses a PaymentStrategy to process payments.
// - Implement a method to simulate processing a payment with a chosen payment strategy.

#pragma once
#include <iostream>
#include <iostream>

namespace Strategy
{

class PaymentStrategy
{
public:
	virtual ~PaymentStrategy() = default;
	virtual void Pay(float amount) = 0;
};

class CreditCardPayment : public PaymentStrategy
{
	void Pay(float amount) override
	{
		std::cout << "Credit card payment [" << std::fixed << std::setprecision(2) << amount << "] is processing " << std::endl;
	}
};

class PayPalPayment : public PaymentStrategy
{
	void Pay(float amount) override
	{
		std::cout << "PayPal payment [" << std::fixed << std::setprecision(2) << amount << "] is processing " << std::endl;
	}
};

class BitcoinPayment : public PaymentStrategy
{
	void Pay(float amount) override
	{
		std::cout << "Bitcoin payment [" << std::fixed << std::setprecision(2) << amount << "] is processing " << std::endl;
	}
};

class PaymentContext
{
public:
	void SetStrategy(std::shared_ptr<PaymentStrategy> InStrategy)
	{
		CurrentPaymentStrategy = InStrategy;
	}

	void ProcessPayment(float amount)
	{
		if (CurrentPaymentStrategy != nullptr)
		{
			CurrentPaymentStrategy->Pay(amount);
		}
		else
		{
			std::cerr << "Payment strategy not set!" << std::endl;
		}
	}

private:
	std::shared_ptr<PaymentStrategy> CurrentPaymentStrategy;
};

void TestStrategyPattern()
{
	PaymentContext context;

	context.ProcessPayment(100.f);

	context.SetStrategy(std::make_shared<CreditCardPayment>());
	context.ProcessPayment(159.f);

	context.SetStrategy(std::make_shared<BitcoinPayment>());
	context.ProcessPayment(753.f);

	context.SetStrategy(std::make_shared<PayPalPayment>());
	context.ProcessPayment(654.f);
}

} // namespace Strategy
