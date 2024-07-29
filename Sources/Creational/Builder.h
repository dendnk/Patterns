// Problem Statement
// You need to design a flexible system for constructing different types of computers(e.g., Gaming PC, Office PC)
// with various configurations(e.g., CPU, GPU, RAM, Storage).
// The design should allow easy modification and extension of computer configurations without changing the client code.
//
// Builder Pattern Solution
// The Builder pattern separates the construction of a complex object from its representation,
// allowing the same construction process to create different representations.
//
// Components
// - Product : The complex object being built.
// - Builder Interface : Declares the steps to build the product.
// - Concrete Builders : Implement the steps defined in the Builder interface to construct and assemble parts of the product.
// - Director : Constructs the object using the Builder interface.
// - Client Code : Uses the Director to get the desired product.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Builder
{

class PC
{
public:
	void SetCPU(const std::string& InCPU) { CPU = InCPU; }
	void SetGPU(const std::string& InGPU) { GPU = InGPU; }
	void SetRAM(int InRAM) { RAM = InRAM; }
	void SetStorage(int InStorage) { Storage = InStorage; }

	void ShowSpecifications()
	{
		std::cout << "PC Specifications:\n";
		std::cout << "CPU: " << CPU << "\n";
		std::cout << "GPU: " << GPU << "\n";
		std::cout << "RAM: " << RAM << " GB\n";
		std::cout << "Storage: " << Storage << " GB\n";
	}

private:
	std::string CPU;
	std::string GPU;
	int RAM;
	int Storage;
};

class PCBuilder
{
public:
	virtual ~PCBuilder() = default;
	virtual void BuildCPU() = 0;
	virtual void BuildGPU() = 0;
	virtual void BuildRAM() = 0;
	virtual void BuildStorage() = 0;
	virtual std::shared_ptr<PC> GetPC() = 0;
};

class GamingPCBuilder : public PCBuilder
{
public:
	GamingPCBuilder() { Computer = std::make_shared<PC>(); }

	void BuildCPU() override { Computer->SetCPU("Intel Core i9"); }
	void BuildGPU() override { Computer->SetGPU("NVIDIA GeForce RTX 4090"); }
	void BuildRAM() override { Computer->SetRAM(128); }
	void BuildStorage() override { Computer->SetStorage(5000); }
	std::shared_ptr<PC> GetPC() override { return Computer; }

private:
	std::shared_ptr<PC> Computer;
};

class OfficePCBuilder : public PCBuilder
{
public:
	OfficePCBuilder() { Computer = std::make_shared<PC>(); }

	void BuildCPU() override { Computer->SetCPU("Intel Core i5"); }
	void BuildGPU() override { Computer->SetGPU("Integrated video card"); }
	void BuildRAM() override { Computer->SetRAM(16); }
	void BuildStorage() override { Computer->SetStorage(1000); }
	std::shared_ptr<PC> GetPC() override { return Computer; }

private:
	std::shared_ptr<PC> Computer;
};

class Director
{
public:
	void SetBuilder(std::shared_ptr<PCBuilder> InBuilder) { this->Builder = InBuilder; }

	std::shared_ptr<PC> BuildComputer()
	{
		if (Builder)
		{
			Builder->BuildCPU();
			Builder->BuildGPU();
			Builder->BuildRAM();
			Builder->BuildStorage();
			return Builder->GetPC();
		}
		return nullptr;
	}

private:
	std::shared_ptr<PCBuilder> Builder;
};


void TestBuilderPattern()
{
	Director director;

	std::shared_ptr<PCBuilder> gamingPCBuilder = std::make_shared<GamingPCBuilder>();
	director.SetBuilder(gamingPCBuilder);
	std::shared_ptr<PC> gamingPC = director.BuildComputer();
	gamingPC->ShowSpecifications();

	std::shared_ptr<PCBuilder> officePCBuilder = std::make_shared<OfficePCBuilder>();
	director.SetBuilder(officePCBuilder);
	std::shared_ptr<PC> officePC = director.BuildComputer();
	officePC->ShowSpecifications();
}

} // namespace Builder