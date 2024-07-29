// Task
// Create a logging system where only one instance of the Logger class exists.
// This Logger class should provide methods to log messages to the console.
// The class should ensure that all parts of the application use the same instance of the Logger.

#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <string>

namespace Singleton
{

class Logger
{
public:
	static Logger& GetInstance()
	{
		std::call_once(InitInstanceFlag, []()
			{
				LoggerInstance.reset(new Logger());
			});

		return *LoggerInstance;
	}

	void Log(const std::string& MessageToLog)
	{
		std::lock_guard<std::mutex> lock(Mtx);
		std::cout << "Logger :" << MessageToLog << std::endl;
	}

private:
	Logger() = default;

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

private:
    static std::unique_ptr<Logger> LoggerInstance;
    static std::once_flag InitInstanceFlag;

	std::mutex Mtx;
};

std::unique_ptr<Logger> Logger::LoggerInstance;
std::once_flag Logger::InitInstanceFlag;

void TestSingletonPattern()
{
	Logger& logger = Logger::GetInstance();
	logger.Log("Singleton Pattern Logger - First message");

	Logger& logger2 = Logger::GetInstance();
	logger2.Log("Singleton Pattern Logger - Second message");

	// Verify that both loggers are the same instance
	if (&logger == &logger2)
	{
		logger.Log("Both logger instances are the same.");
	}
}

} // namespace Singleton
