// Task
// Implement an Image Viewer using the Proxy Pattern
// Objective : Create an Image interface with a Display method.
// Implement a RealImage class that loads an image from the disk and displays it.
// Use a ProxyImage class to control access to the RealImage, loading it only when necessary.

// Requirements :
// - Image Interface : Defines a method Display.
// - RealImage Class : Implements the Image interface and represents the actual image. Loads the image from the disk.
// - ProxyImage Class : Implements the Image interface and controls access to the RealImage.
//						It should load the RealImage only when Display is called for the first time.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Proxy
{

class Image
{
public:
	virtual ~Image() = default;
	virtual void Display() const = 0;
};

class RealImage : public Image
{
public:
	RealImage(const std::string& InName)
		: Name(InName)
	{
		LoadFromDisk(InName);
	}

	void Display() const override
	{
		std::cout << "Displaying " << Name << std::endl;
	}

private:
	void LoadFromDisk(const std::string& InName)
	{
		std::cout << "Loading image " << InName << " from disk...\n";
	}

private:
	std::string Name;
};

class ProxyImage : public Image
{
public:
	ProxyImage(const std::string& InName)
		: Name(InName)
	{}

	void Display() const override
	{
		if (CachedImage == nullptr)
		{
			CachedImage = std::make_shared<RealImage>(Name);
		}
		CachedImage->Display();
	}

private:
	std::string Name;
	mutable std::shared_ptr<RealImage> CachedImage;
};

void TestProxyPattern()
{
	std::shared_ptr<Image> image = std::make_shared<ProxyImage>("test_image.jpg");

	image->Display();

	image->Display();
}

} // namespace Proxy