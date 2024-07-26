// Task:
// You are tasked with designing a graphical editor that can draw a large number of shapes.
// Each shape has some common properties such as color, and position, but they can differ in size and other attributes.
// Use the Flyweight pattern to minimize memory usage by sharing common properties among the shapes.

// Requirements :
// - Implement a Shape class hierarchy with concrete shapes like Circle, Rectangle, etc.
// - Use a ShapeFactory class to manage and share flyweight objects(shapes with common properties).
// - Implement a method to draw shapes with their specific properties.

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace Flyweight
{
class Shape
{
public:
	virtual ~Shape() = default;
	virtual void Draw(int PosX, int PosY, int Size) const = 0;
};

class Circle : public Shape
{
public:
	Circle(const std::string& InColor)
		: Color(InColor)
	{}

	void Draw(int PosX, int PosY, int Size) const override
	{
		std::cout << "Drawing Circle [Color: " << Color << ", x: " << PosX << ", y: " << PosY << ", size: " << Size << "]\n";
	}

private:
	std::string Color;
};

class Rectangle : public Shape
{
public:
	Rectangle(const std::string& InColor)
		: Color(InColor)
	{}

	void Draw(int PosX, int PosY, int Size) const override
	{
		std::cout << "Drawing Rectangle [Color: " << Color << ", x: " << PosX << ", y: " << PosY << ", size: " << Size << "]\n";
	}

private:
	std::string Color;
};

class Triangle : public Shape
{
public:
	Triangle(const std::string& InColor)
		: Color(InColor)
	{}

	void Draw(int PosX, int PosY, int Size) const override
	{
		std::cout << "Drawing Triangle [Color: " << Color << ", x: " << PosX << ", y: " << PosY << ", size: " << Size << "]\n";
	}

private:
	std::string Color;
};

class ShapeFactory
{
public:
	std::shared_ptr<Shape> GetCircle(const std::string& Color)
	{
		return GetShape<Circle>(Color, Circles);
	}

	std::shared_ptr<Shape> GetRectangle(const std::string& Color)
	{
		return GetShape<Rectangle>(Color, Rectangles);
	}

	std::shared_ptr<Shape> GetTriangle(const std::string& Color)
	{
		return GetShape<Triangle>(Color, Triangles);
	}

	size_t GetAllocatedShapesNum() const
	{
		return Circles.size() + Rectangles.size() + Triangles.size();
	}

private:
	template<typename T>
	std::shared_ptr<Shape> GetShape(const std::string& Color, std::unordered_map<std::string, std::shared_ptr<Shape>>& Shapes)
	{
		auto it = Shapes.find(Color);
		if (it != Shapes.end())
		{
			return it->second;
		}

		auto NewShape = std::make_shared<T>(Color);
		Shapes[Color] = NewShape;
		return NewShape;
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Shape>> Circles;
	std::unordered_map<std::string, std::shared_ptr<Shape>> Rectangles;
	std::unordered_map<std::string, std::shared_ptr<Shape>> Triangles;
};


void TestFlyweightPattern()
{
	ShapeFactory ShapeFactory;

	std::vector<std::shared_ptr<Shape>> Shapes;


	for (int i = 0; i < 3000; ++i)
	{
		Shapes.push_back(ShapeFactory.GetCircle("Red"));
		Shapes.push_back(ShapeFactory.GetCircle("Green"));
		Shapes.push_back(ShapeFactory.GetCircle("Blue"));

		Shapes.push_back(ShapeFactory.GetRectangle("Red"));
		Shapes.push_back(ShapeFactory.GetRectangle("Green"));
		Shapes.push_back(ShapeFactory.GetRectangle("Blue"));

		Shapes.push_back(ShapeFactory.GetTriangle("Red"));
		Shapes.push_back(ShapeFactory.GetTriangle("Green"));
		Shapes.push_back(ShapeFactory.GetTriangle("Blue"));
	}

	//int i = 0;
	//for (const auto& CurrentShape : Shapes)
	//{
	//	CurrentShape->Draw(i, 2 * i, 3 * i);
	//	i++;
	//}

	std::cout << "Shapes number : " << Shapes.size() << std::endl;
	std::cout << "Allocated Shapes number : " << ShapeFactory.GetAllocatedShapesNum() << std::endl;
}

} // namespace Flyweight