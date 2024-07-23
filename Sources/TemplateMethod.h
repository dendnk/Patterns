// You are tasked with developing a data processing system for different types of data(e.g., CSV, JSON, XML).
// Each data type requires a specific way to be read, processed, and written to a file.

// Requirements:
// - Create an abstract class DataProcessor that defines the template method for processing data.
// - Implement concrete classes(CSVProcessor, JSONProcessor, XMLProcessor) that provide specific implementations for reading, processing, and writing data.
// - Create a method to demonstrate processing data using the template method.

#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace TemplateMethod
{

class DataProcessor
{
public:
	virtual ~DataProcessor() = default;

	void ProcessData(const std::string& InFile, const std::string& OutFile)
	{
		std::vector<std::string> data = ReadData(InFile);
		std::vector<std::string> processedData = Process(data);
		WriteData(OutFile, processedData);
	}

protected:
	virtual std::vector<std::string> ReadData(const std::string& File) = 0;
	virtual std::vector<std::string> Process(const std::vector<std::string>& Data) = 0;
	virtual void WriteData(const std::string& File, const std::vector<std::string>& Data) = 0;
};

class DummyCSVProcessor : public DataProcessor
{
	std::vector<std::string> ReadData(const std::string& File) override
	{
		std::cout << "Reading CSV data from " << File << std::endl;
		return { "name,age", "John,43", "Jack,55" };
	}

	std::vector<std::string> Process(const std::vector<std::string>& Data) override
	{
		std::cout << "Processing CSV data " << std::endl;
		return Data;
	}

	void WriteData(const std::string& File, const std::vector<std::string>& Data) override
	{
		std::cout << "Writing processed CSV data to " << File << std::endl;
	}
};

class DummyJSONProcessor : public DataProcessor
{
	std::vector<std::string> ReadData(const std::string& File) override
	{
		std::cout << "Reading JSON data from " << File << std::endl;
		return { "{\"name\": \"John\", \"age\": 43}", "{\"name\": \"Jack\", \"age\": 55}" };
	}

	std::vector<std::string> Process(const std::vector<std::string>& Data) override
	{
		std::cout << "Processing JSON data " << std::endl;
		return Data;
	}

	void WriteData(const std::string& File, const std::vector<std::string>& Data) override
	{
		std::cout << "Writing processed JSON data to " << File << std::endl;
	}
};

class DummyXMLProcessor : public DataProcessor
{
	std::vector<std::string> ReadData(const std::string& File) override
	{
		std::cout << "Reading XML data from " << File << std::endl;
		return { "<person><name>John</name><age>43</age></person>", "<person><name>Jack</name><age>55</age></person>" };;
	}

	std::vector<std::string> Process(const std::vector<std::string>& Data) override
	{
		std::cout << "Processing XML data " << std::endl;
		return Data;
	}

	void WriteData(const std::string& File, const std::vector<std::string>& Data) override
	{
		std::cout << "Writing processed XML data to " << File << std::endl;
	}
};

void TestTemplateMethodPattern()
{
	DummyCSVProcessor CSVProcessor;
	CSVProcessor.ProcessData("InFile.csv", "OutFile.csv");

	DummyJSONProcessor JSONProcessor;
	JSONProcessor.ProcessData("InFile.json", "OutFile.json");

	DummyXMLProcessor XMLProcessor;
	JSONProcessor.ProcessData("InFile.xml", "OutFile.xml");
}

} // namespace TemplateMethod
