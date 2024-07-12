// You are tasked with creating a chat room application where multiple users can communicate with each other.
// Implement a ChatRoom class that acts as the mediator, coordinating the communication between users.

// Requirements
// - Create a User class with attributes for the user's name.
// - Implement a ChatRoom class that facilitates communication between users.
// - Users should be able to send messages to the chat room, and the chat room should be responsible for delivering the messages to all users except the sender.

#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Mediator
{

class ChatRoom;

class User
{
public:
	explicit User(const std::string& userName) : UserName_(userName), ChatRoom_(nullptr) {}

	inline std::string GetUserName() const { return UserName_; }

	bool JoinChatRoom(ChatRoom* NewChatRoom);
	void LeaveChatRoom();

	void SendMessage(const std::string& message) const;
	void ReceiveMessage(const std::string& sender, const std::string& message) const;

private:
	std::string UserName_;
	ChatRoom* ChatRoom_;
};

class ChatRoom
{
public:
	void AddUser(std::shared_ptr<User> UserToAdd)
	{
		Users_.emplace_back(UserToAdd);
		UserToAdd->JoinChatRoom(this);
	}

	void RemoveUser(User* UserToRemove)
	{
		if (UserToRemove == nullptr)
		{
			return;
		}

		Users_.erase(std::remove_if(Users_.begin(), Users_.end(), [&](const std::shared_ptr<User>& user)
			{
				return user->GetUserName() == UserToRemove->GetUserName();
			}),Users_.end());

		BroadcastMessage(UserToRemove->GetUserName(), "left the chat room");
	}

	void BroadcastMessage(const std::string& sender, const std::string& message) const
	{
		for (auto& CurrentUser : Users_)
		{
			if (CurrentUser->GetUserName() != sender)
			{
				CurrentUser->ReceiveMessage(sender, message);
			}
		}
	}

private:
	std::vector<std::shared_ptr<User>> Users_;
};


bool User::JoinChatRoom(ChatRoom* NewChatRoom)
{
	if (NewChatRoom == nullptr)
	{
		return false;
	}

	ChatRoom_ = NewChatRoom;

	std::cout << GetUserName() << " joined the chat room" << std::endl;

	return true;
}

void User::LeaveChatRoom()
{
	if (ChatRoom_ != nullptr)
	{
		std::cout << GetUserName() << " left the chat room" << std::endl;

		ChatRoom_->RemoveUser(this);
		ChatRoom_ = nullptr;
	}
}

void User::SendMessage(const std::string& message) const
{
	if (ChatRoom_ != nullptr)
	{
		std::cout << GetUserName() << " sent message : " << message << " to chat room" << std::endl;

		ChatRoom_->BroadcastMessage(GetUserName(), message);
	}
}

void User::ReceiveMessage(const std::string& sender, const std::string& message) const
{
	std::cout << GetUserName() << " received message : [" << sender << "] : " << message << std::endl;
}


void TestMediatorPattern()
{
	auto chatRoom = std::make_shared<ChatRoom>();

	auto user1 = std::make_shared<User>("Alice");
	auto user2 = std::make_shared<User>("Bob");
	auto user3 = std::make_shared<User>("Charlie");

	chatRoom->AddUser(user1);
	chatRoom->AddUser(user2);
	chatRoom->AddUser(user3);

	user1->SendMessage("Hi everyone!");
	user2->SendMessage("Hello Alice!");
	user3->SendMessage("Hey guys, what's up?");

	user1->LeaveChatRoom();
}

} // namespace Mediator