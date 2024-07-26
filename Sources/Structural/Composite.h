// Problem:
// You are tasked with creating a file system that supports both files and directories.
// A directory can contain multiple files and subdirectories, and both files and directories should support common operations such as
// displaying their names and sizes.You want to be able to treat files and directories uniformly.
//
// Requirements :
// - Create an abstract FileSystemComponent class that declares methods for displaying the name and size of a file system component.
// - Implement concrete File and Directory classes.
// - The Directory class should be able to contain multiple FileSystemComponent objects(both files and subdirectories).
// - Demonstrate the usage of the FileSystemComponent to display the structure and size of a directory.

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Composite
{

class FileSystemComponent
{
public:
	virtual ~FileSystemComponent() = default;

	virtual void DisplayInfo(int indent = 0) const = 0;
	virtual size_t GetSize() const = 0;
};

class File : public FileSystemComponent
{
public:
	File(const std::string& InName, size_t InSize)
		: Name(InName)
		, Size(InSize)
	{}

	void DisplayInfo(int indent = 0) const override
	{
		std::cout << std::string(indent, ' ') << "File : " << Name << " | Size : " << Size << " Kb" << std::endl;
	}

	size_t GetSize() const override
	{
		return Size;
	}

private:
	std::string Name;
	size_t Size;
};

class Directory : public FileSystemComponent
{
public:
	Directory(const std::string& InName) : Name(InName) {}

	void AddComponent(std::shared_ptr<FileSystemComponent> ComponentToAdd)
	{
		if (ComponentToAdd != nullptr)
		{
			Components.emplace_back(ComponentToAdd);
		}
	}

	void DisplayInfo(int indent = 0) const override
	{
		std::cout << std::string(indent, ' ') << "Directory : " << Name << " | Size : " << GetSize() << " Kb" << std::endl;

		for (const auto& Component : Components)
		{
			Component->DisplayInfo(indent + 2);
		}
	}

	size_t GetSize() const override
	{
		size_t Total = 0;

		for (const auto& Component : Components)
		{
			Total += Component->GetSize();
		}

		return Total;
	}

private:
	std::string Name;
	std::vector<std::shared_ptr<FileSystemComponent>> Components;
};


void TestCompositePattern()
{
	auto rootDirectory = std::make_shared<Directory>("root");

	auto file1 = std::make_shared<File>("file1.txt", 10);
	auto file2 = std::make_shared<File>("file2.jpg", 20);

	auto subDirectory1 = std::make_shared<Directory>("subdir1");
	auto file3 = std::make_shared<File>("file3.doc", 30);
	auto file4 = std::make_shared<File>("file4.pdf", 40);
	subDirectory1->AddComponent(file3);
	subDirectory1->AddComponent(file4);

	auto subDirectory2 = std::make_shared<Directory>("subdir2");
	auto file5 = std::make_shared<File>("file5.mp3", 50);

	auto subDirectory3 = std::make_shared<Directory>("subdir3");
	auto file6 = std::make_shared<File>("file6.mp3", 60);

	subDirectory3->AddComponent(file6);

	subDirectory2->AddComponent(file5);
	subDirectory2->AddComponent(subDirectory3);

	rootDirectory->AddComponent(file1);
	rootDirectory->AddComponent(file2);
	rootDirectory->AddComponent(subDirectory1);
	rootDirectory->AddComponent(subDirectory2);

	rootDirectory->DisplayInfo();
	std::cout << "Total Size: " << rootDirectory->GetSize() << " KB" << std::endl;
}

} // namespace Composite