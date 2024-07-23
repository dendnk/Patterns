// You are tasked with creating a system that processes different types of shapes(e.g., Circle, Rectangle, Triangle)
// and applies different operations on them(e.g., calculating area, printing details).

// Requirements:
// - Create an abstract Shape class and concrete shape classes(Circle, Rectangle, Triangle).
// - Implement a ShapeVisitor interface with visit methods for each shape type.
// - Create concrete visitor classes(AreaCalculator, DetailPrinter) that implement the ShapeVisitor interface and provide specific operations.
// - Implement a method to demonstrate the visitor pattern with different operations.

#pragma once
#include <iostream>

#define M_PI       3.14159265358979323846   // pi

namespace Visitor
{

class Circle;
class Rectangle;
class Triangle;

class ShapeVisitor
{
public:
	virtual ~ShapeVisitor() = default;
	virtual void VisitCircle(const Circle& InCircle) = 0;
	virtual void VisitRectangle(const Rectangle& InRectangle) = 0;
	virtual void VisitTriangle(const Triangle& InTriangle) = 0;
};

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void Accept(ShapeVisitor& visitor) const = 0;
};

class Circle : public Shape
{
public:
	Circle(double InRadius) : Radius(InRadius) {}

	double GetRadius() const { return Radius; }
	void Accept(ShapeVisitor& InVisitor) const override
	{
		InVisitor.VisitCircle(*this);
	}

private:
	double Radius;
};

class Rectangle : public Shape
{
public:
	Rectangle(double InWidth, double InHeight)
		: Width(InWidth)
		, Height(InHeight)
	{}

	double GetWidth() const { return Width; }
	double GetHeight() const { return Height; }

	void Accept(ShapeVisitor& InVisitor) const override
	{
		InVisitor.VisitRectangle(*this);
	}

private:
	double Width;
	double Height;
};

class Triangle : public Shape
{
public:
	Triangle(double InBase, double InHeight)
		: Base(InBase)
		, Height(InHeight)
	{}

	double GetBase() const { return Base; }
	double GetHeight() const { return Height; }

	void Accept(ShapeVisitor& InVisitor) const override
	{
		InVisitor.VisitTriangle(*this);
	}

private:
	double Base;
	double Height;
};

class AreaCalculator : public ShapeVisitor
{
public:
	void VisitCircle(const Circle& InCircle) override
	{
		double area = M_PI * InCircle.GetRadius() * InCircle.GetRadius();
		std::cout << "Circle area : " << area << std::endl;
	}

	void VisitRectangle(const Rectangle& InRectangle) override
	{
		double area = InRectangle.GetHeight() * InRectangle.GetWidth();
		std::cout << "Rectangle area : " << area << std::endl;
	}

	void VisitTriangle(const Triangle& InTriangle) override
	{
		double area = 0.5 * InTriangle.GetBase() * InTriangle.GetHeight();
		std::cout << "Triangle area : " << area << std::endl;
	}
};

class DetailPrinter : public ShapeVisitor
{
public:
	void VisitCircle(const Circle& InCircle) override
	{
		std::cout << "Circle radius : " << InCircle.GetRadius() << std::endl;
	}

	void VisitRectangle(const Rectangle& InRectangle) override
	{
		std::cout << "Rectangle width : " << InRectangle.GetWidth() << std::endl;
		std::cout << "Rectangle height : " << InRectangle.GetHeight() << std::endl;
	}

	void VisitTriangle(const Triangle& InTriangle) override
	{
		std::cout << "Triangle base : " << InTriangle.GetBase() << std::endl;
		std::cout << "Triangle height : " << InTriangle.GetHeight() << std::endl;
	}
};

void TestVisitorPattern()
{
	std::vector<std::shared_ptr<Shape>> Shapes =
	{
		std::make_shared<Circle>(10.0),
		std::make_shared<Rectangle>(4.0, 5.0),
		std::make_shared<Triangle>(6.0, 7.0)
	};

	AreaCalculator AreaProcessor;
	DetailPrinter DetailsLogger;

	std::cout << "Calculating areas : " << std::endl;
	for (const auto& CurrentShape : Shapes)
	{
		CurrentShape->Accept(AreaProcessor);
	}

	std::cout << "Printing details: " << std::endl;
	for (const auto& CurrentShape : Shapes)
	{
		CurrentShape->Accept(DetailsLogger);
	}
}

} // namespace Visitor
