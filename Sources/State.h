// Traffic Light System
// Need to implement a traffic light system using the State design pattern.
// The traffic light system has three states : Red, Green, and Yellow.
// Each state should have its own behavior and should transition to the next state after a certain period.

// Requirements:
// Implement a TrafficLight class that manages the state of the traffic light.
// Create abstract TrafficLightState class and concrete state classes RedState, GreenState, and YellowState.
// Each state should have a method to handle the traffic light behavior and transition to the next state.
// Implement a method to simulate the traffic light system for a given number of cycles.

#pragma once
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

namespace State
{

class TrafficLight;

class TrafficLightState
{
public:
	virtual ~TrafficLightState() = default;

	virtual void HandleState(TrafficLight& InTrafficLight) = 0;
};

class TrafficLight
{
public:
	TrafficLight(std::shared_ptr<TrafficLightState> InitialState) : CurrentState(InitialState) {}

	std::shared_ptr<TrafficLightState> GetState() const { return CurrentState; }
	std::shared_ptr<TrafficLightState> GetPreviousState() const { return PreviosState; }

	void SetState(std::shared_ptr<TrafficLightState> NextState)
	{
		if (NextState != nullptr)
		{
			PreviosState = CurrentState;
			CurrentState = NextState;
		}
	}

	void RequestSwitch()
	{
		CurrentState->HandleState(*this);
	}

private:
	std::shared_ptr<TrafficLightState> CurrentState;
	std::shared_ptr<TrafficLightState> PreviosState;
};

class RedState : public TrafficLightState
{
	void HandleState(TrafficLight& InTrafficLight) override;
};

class YellowState : public TrafficLightState
{
	void HandleState(TrafficLight& InTrafficLight) override;
};

class GreenState : public TrafficLightState
{
	void HandleState(TrafficLight& InTrafficLight) override;
};

void RedState::HandleState(TrafficLight& InTrafficLight)
{
	std::cout << "Red Light - Stop" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	InTrafficLight.SetState(std::make_shared<YellowState>());
}

void YellowState::HandleState(TrafficLight& InTrafficLight)
{
	std::cout << "Yellow Light - Warning" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));


	if (dynamic_cast<RedState*>(InTrafficLight.GetPreviousState().get()))
	{
		InTrafficLight.SetState(std::make_shared<GreenState>());
	}
	else
	{
		InTrafficLight.SetState(std::make_shared<RedState>());
	}
}

void GreenState::HandleState(TrafficLight& InTrafficLight)
{
	std::cout << "Green Light - Go Go Go" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	InTrafficLight.SetState(std::make_shared<YellowState>());
}

void SimulateTrafficLight(uint8_t cyclesNum)
{
	auto InitialState = std::make_shared<RedState>();
	TrafficLight TrafficLightOne(InitialState);

	for (int i = 0; i < cyclesNum; ++i)
	{
		TrafficLightOne.RequestSwitch();
	}
}

void TestStatePattern()
{
	uint8_t cyclesNum = 10;
	SimulateTrafficLight(cyclesNum);
}

} // namespace State
