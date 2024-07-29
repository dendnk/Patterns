// Task Description :
// You are tasked with creating a vehicle rental system where different types of vehicles can be rented.
// Each type of vehicle has its own characteristics and rental costs.
// Implement a VehicleFactory using the Factory Method design pattern to create different types of vehicles.
//
// Requirements :
// - Create an abstract Vehicle class with methods to get the vehicle type and rental cost.
// - Implement concrete vehicle classes(Car, Bike, and Truck) that inherit from Vehicle.
// - Create an abstract VehicleFactory class with a factory method CreateVehicle.
// - Implement concrete factory classes(CarFactory, BikeFactory, and TruckFactory) that inherit from VehicleFactory and implement the CreateVehicle method.
// - Implement a method to simulate renting different vehicles and displaying their details.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace FactoryMethod
{

class Vehicle
{
public:
	virtual ~Vehicle() = default;
	virtual std::string GetVehicleType() const = 0;
	virtual float GetRentalCost() const = 0;
};

class Car : public Vehicle
{
public:
	std::string GetVehicleType() const override { return "Car"; }
	float GetRentalCost() const override { return 100; }
};

class Bike : public Vehicle
{
public:
	std::string GetVehicleType() const override { return "Bike"; }
	float GetRentalCost() const override { return 50; }
};

class Truck : public Vehicle
{
public:
	std::string GetVehicleType() const override { return "Truck"; }
	float GetRentalCost() const override { return 150; }
};

class VehicleFactory
{
public:
	virtual ~VehicleFactory() = default;
	virtual std::shared_ptr<Vehicle> CreateVehicle() const = 0;
};

// Concrete Factory classes
class CarFactory : public VehicleFactory
{
public:
	std::shared_ptr<Vehicle> CreateVehicle() const override
	{
		return std::make_shared<Car>();
	}
};

class BikeFactory : public VehicleFactory
{
public:
	std::shared_ptr<Vehicle> CreateVehicle() const override
	{
		return std::make_shared<Bike>();
	}
};

class TruckFactory : public VehicleFactory
{
public:
	std::shared_ptr<Vehicle> CreateVehicle() const override
	{
		return std::make_shared<Truck>();
	}
};


void RentVehicle(const VehicleFactory& factory)
{
	auto vehicle = factory.CreateVehicle();
	std::cout << "Rented a " << vehicle->GetVehicleType() << " with a rental cost of $" << vehicle->GetRentalCost() << " per day.\n";
}

void TestFactoryMethod()
{
	CarFactory carFactory;
	BikeFactory bikeFactory;
	TruckFactory truckFactory;

	RentVehicle(carFactory);
	RentVehicle(bikeFactory);
	RentVehicle(truckFactory);
}

} // namespace FactoryMethod