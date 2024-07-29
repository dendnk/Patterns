// Problem Statement
// You need to design a cross - platform GUI application that can create various UI components like buttons and checkboxes.
// The application should support multiple operating systems(e.g., Windows and MacOS).
// The design should allow easy addition of new operating systems without modifying existing code.
//
// Abstract Factory Pattern Solution
// The Abstract Factory pattern provides an interface for creating families of related or dependent objects without
// specifying their concrete classes.Here's how we can implement this for our GUI toolkit.
//
// Components
// - Abstract Product Interfaces : Define the interfaces for each type of product.
// - Concrete Products : Implementations of the abstract product interfaces for different operating systems.
// - Abstract Factory Interface : Declares a set of methods for creating each type of product.
// - Concrete Factories : Implement the abstract factory interface to create concrete products for each operating system.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace AbstractFactory
{

class Button
{
public:
    virtual ~Button() = default;
    virtual void Paint() const = 0;
};

class Checkbox
{
public:
    virtual ~Checkbox() = default;
    virtual void Paint() const = 0;
};

class WindowsButton : public Button
{
public:
    void Paint() const override
    {
        std::cout << "Rendering a button in Windows style.\n";
    }
};

class WindowsCheckbox : public Checkbox
{
public:
    void Paint() const override
    {
        std::cout << "Rendering a checkbox in Windows style.\n";
    }
};

class MacOSButton : public Button
{
public:
    void Paint() const override
    {
        std::cout << "Rendering a button in MacOS style.\n";
    }
};

class MacOSCheckbox : public Checkbox
{
public:
    void Paint() const override
    {
        std::cout << "Rendering a checkbox in MacOS style.\n";
    }
};

class GUIFactory
{
public:
    virtual ~GUIFactory() = default;
    virtual std::shared_ptr<Button> CreateButton() const = 0;
    virtual std::shared_ptr<Checkbox> CreateCheckbox() const = 0;
};

class WindowsFactory : public GUIFactory
{
public:
    std::shared_ptr<Button> CreateButton() const override
    {
        return std::make_shared<WindowsButton>();
    }

    std::shared_ptr<Checkbox> CreateCheckbox() const override
    {
        return std::make_shared<WindowsCheckbox>();
    }
};

class MacOSFactory : public GUIFactory
{
public:
    std::shared_ptr<Button> CreateButton() const override
    {
        return std::make_shared<MacOSButton>();
    }

    std::shared_ptr<Checkbox> CreateCheckbox() const override
    {
        return std::make_shared<MacOSCheckbox>();
    }
};

void RenderUI(const GUIFactory& factory)
{
    auto button = factory.CreateButton();
    auto checkbox = factory.CreateCheckbox();

    button->Paint();
    checkbox->Paint();
}


void TestAbstractFactory()
{
    std::cout << "Windows factory type:\n";
    WindowsFactory windowsFactory;
    RenderUI(windowsFactory);

    std::cout << "\nMacOS factory type:\n";
    MacOSFactory macFactory;
    RenderUI(macFactory);
}

} // namespace AbstractFactory