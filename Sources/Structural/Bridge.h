// Problem:
// You are tasked with creating a remote control system for various types of devices(e.g., TVs and Radios).
// Each device can have different brands(e.g., Sony, Samsung).
// You want to be able to control any brand of any device without creating a class for every combination of device and brand.
//
// Requirements :
// - Create an abstract Device interface with methods to turn on, turn off, and set the volume.
// - Implement concrete Device classes for different brands(e.g., SonyTV, SamsungRadio).
// - Create an abstract RemoteControl class that can operate a Device.
// - Implement concrete RemoteControl classes(e.g., BasicRemote, AdvancedRemote).
// - Demonstrate the usage of the RemoteControl to operate various Device implementations.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Bridge
{

class Device
{
public:
	virtual ~Device() = default;

	virtual void SetEnabled(bool IsEnabled) = 0;
	virtual void SetVolume(float NewVolume) = 0;
};

class SonyTV : public Device
{
	void SetEnabled(bool IsEnabled) override
	{
		auto NewState = IsEnabled ? "true" : "false";
		std::cout << "Set SonyTV Enabled to " << NewState << std::endl;
	}

	void SetVolume(float NewVolume) override
	{
		std::cout << "Set SonyTV Volume to " << NewVolume << std::endl;
	}
};

class SamsungRadio : public Device
{
	void SetEnabled(bool IsEnabled) override
	{
		auto NewState = IsEnabled ? "true" : "false";
		std::cout << "Set SamsungRadio Enabled to " << NewState << std::endl;
	}

	void SetVolume(float NewVolume) override
	{
		std::cout << "Set SamsungRadio Volume to " << NewVolume << std::endl;
	}
};

class RemoteControl
{
public:
	RemoteControl(std::shared_ptr<Device> InDevice)
		: UsedDevice(InDevice)
	{}

	~RemoteControl() = default;

	virtual void SetEnabled(bool IsEnabled)
	{
		if (UsedDevice != nullptr)
		{
			UsedDevice->SetEnabled(IsEnabled);
		}
	}

	virtual void SetVolume(float NewVolume)
	{
		if (UsedDevice != nullptr)
		{
			UsedDevice->SetVolume(NewVolume);
		}
	}

private:
	std::shared_ptr<Device> UsedDevice;
};

class BasicRemote : public RemoteControl
{
	using Parent = RemoteControl;

public:
	BasicRemote(std::shared_ptr<Device> InDevice)
		: RemoteControl(InDevice)
	{}

	void SetEnabled(bool IsEnabled) override
	{
		std::cout << "Basic Remote : ";
		Parent::SetEnabled(IsEnabled);
	}

	void SetVolume(float NewVolume) override
	{
		std::cout << "Basic Remote : ";
		Parent::SetVolume(NewVolume);
	}
};

class AdvancedRemote : public RemoteControl
{
	using Parent = RemoteControl;

public:
	AdvancedRemote(std::shared_ptr<Device> InDevice)
		: RemoteControl(InDevice)
	{}

	void Mute()
	{
		std::cout << "Advanced Remote : Mute : ";
		SetVolume(0);
	}
};

void TestBridgePattern()
{
	std::shared_ptr<Device> sonyTV = std::make_shared<SonyTV>();
	std::shared_ptr<RemoteControl> basicRemote = std::make_shared<BasicRemote>(sonyTV);

	basicRemote->SetEnabled(true);
	basicRemote->SetVolume(10);
	basicRemote->SetEnabled(false);

	std::shared_ptr<Device> samsungRadio = std::make_shared<SamsungRadio>();
	std::shared_ptr<RemoteControl> advancedRemote = std::make_shared<AdvancedRemote>(samsungRadio);

	advancedRemote->SetEnabled(true);
	advancedRemote->SetVolume(5);
	std::static_pointer_cast<AdvancedRemote>(advancedRemote)->Mute();
	advancedRemote->SetEnabled(false);
}

} // namespace Bridge