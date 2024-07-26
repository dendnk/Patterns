// Task Description
// You are tasked with creating a notification system that can send notifications through various channels
// (e.g., Email, SMS, and Push Notifications). The notification system should allow for adding multiple notification
// channels dynamically to enhance the basic notification functionality. Use the Decorator design pattern to achieve this.
//
// Requirements
// - Implement a base Notification class with a method send() for sending a basic notification.
// - Create concrete classes EmailNotification, SMSNotification, and PushNotification that extend the base Notification class.
// - Implement a NotificationDecorator abstract class that also extends the base Notification class.
// - Create concrete decorator classes EmailDecorator, SMSDecorator, and PushDecorator that extend the NotificationDecorator class and add additional notification channels to the base notification.
// - Demonstrate the usage of the notification system by sending a notification through multiple channels.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Decorator
{

class Notification : public std::enable_shared_from_this<Notification>
{
public:
	virtual ~Notification() = default;
	virtual void Send(const std::string& Message) const = 0;

	virtual std::shared_ptr<Notification> RemoveDecorator(const std::type_info& Type, int Indent = 0)
	{
		std::cout << std::string(Indent, ' ') << "RemoveDecorator [Notification] : shared_from_this()" << std::endl;
		return shared_from_this();
	}
};

class BasicNotification : public Notification
{
public:
	void Send(const std::string& Message) const override
	{
		std::cout << "Basic Notification : " << Message << std::endl;
	}
};

class NotificationDecorator : public Notification
{
public:
	NotificationDecorator(std::shared_ptr<Notification> InNotification)
		: WrappedNotification(InNotification)
	{}

	virtual ~NotificationDecorator() = default;

	void Send(const std::string& Message) const override
	{
		if (WrappedNotification != nullptr)
		{
			WrappedNotification->Send(Message);
		}
	}

	std::shared_ptr<Notification> RemoveDecorator(const std::type_info& Type, int Indent = 0) override
	{
		std::cout << std::string(Indent,' ') << "RemoveDecorator [" << typeid(*this).name() << "] ... " << std::endl;

		if (typeid(*this) == Type)
		{
			std::cout << std::string(Indent, ' ') << "[" << typeid(*this).name() << "] ... return WrappedNotification" << std::endl;
			return WrappedNotification;
		}

		if (WrappedNotification != nullptr)
		{
			WrappedNotification = WrappedNotification->RemoveDecorator(Type, Indent + 2);
		}

		std::cout << std::string(Indent, ' ') << "[" << typeid(*this).name() << "] ...  shared_from_this()" << std::endl;
		return shared_from_this();
	}

protected:
	std::shared_ptr<Notification> WrappedNotification;
};

class EmailDecorator : public NotificationDecorator
{
public:
	EmailDecorator(std::shared_ptr<Notification> notification) : NotificationDecorator(notification) {}

	void Send(const std::string& message) const override
	{
		if (WrappedNotification != nullptr)
		{
			WrappedNotification->Send(message);
		}

		SendEmail(message);
	}

private:
	void SendEmail(const std::string& message) const
	{
		std::cout << "Sending Email : " << message << std::endl;
	}
};

class SMSDecorator : public NotificationDecorator
{
public:
	SMSDecorator(std::shared_ptr<Notification> notification) : NotificationDecorator(notification) {}

	void Send(const std::string& message) const override
	{
		if (WrappedNotification != nullptr)
		{
			WrappedNotification->Send(message);
		}
		SendSMS(message);
	}

private:
	void SendSMS(const std::string& message) const
	{
		std::cout << "Sending SMS : " << message << std::endl;
	}
};


class PushDecorator : public NotificationDecorator
{
public:
	PushDecorator(std::shared_ptr<Notification> notification) : NotificationDecorator(notification) {}

	void Send(const std::string& message) const override
	{
		if (WrappedNotification != nullptr)
		{
			WrappedNotification->Send(message);
		}
		SendPush(message);
	}

private:
	void SendPush(const std::string& message) const
	{
		std::cout << "Sending Push : " << message << std::endl;
	}
};

std::shared_ptr<Notification> RemoveDecorator(std::shared_ptr<Notification> InNotification, const std::type_info& Type)
{
	if (InNotification != nullptr)
	{
		return InNotification->RemoveDecorator(Type);
	}
	return nullptr;
}

void TestDecoratorPattern()
{
	std::shared_ptr<Notification> notification = std::make_shared<BasicNotification>();

	notification = std::make_shared<EmailDecorator>(notification);
	notification = std::make_shared<SMSDecorator>(notification);
	notification = std::make_shared<PushDecorator>(notification);

	notification->Send("Hello, this is a test notification!");

	std::cout << "\nRemove Email notifications:" << std::endl;
	notification = RemoveDecorator(notification, typeid(EmailDecorator));

	std::cout << "\nSending notification after removing:" << std::endl;
	notification->Send("Hello, this is a second test notification without Email!");
}

} // namespace Composite