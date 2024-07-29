# Design Patterns Showcase

## Overview
This project showcases various design patterns categorized into three main groups: Creational, Structural, and Behavioral. Each category contains practical examples and implementations of common design patterns used in software development.

### Creational Patterns
Creational patterns deal with object creation mechanisms, trying to create objects in a manner suitable to the situation. This category includes:
 - **Factory Method**: Defines an interface for creating an object, but lets subclasses alter the type of objects that will be created.
 - **Abstract Factory**: Provides an interface for creating families of related or dependent objects without specifying their concrete classes.
 - **Builder**: Constructs a complex object step by step. It separates the construction of a complex object from its representation.
 - **Prototype**: Creates new objects by copying an existing object, known as the prototype.
 - **Singleton**: Ensures a class has only one instance and provides a global point of access to it.

### Structural Patterns
Structural patterns focus on composing classes or objects to form larger structures while keeping them flexible and efficient. This category includes:
- **Adapter**: Allows objects with incompatible interfaces to work together by wrapping an existing class with a new interface.
- **Bridge**: Separates abstraction from implementation, allowing them to vary independently.
- **Composite**: Composes objects into tree structures to represent part-whole hierarchies. It allows clients to treat individual objects and compositions of objects uniformly.
- **Decorator**: Adds responsibilities to objects dynamically without altering their structure. Useful for extending functionalities in a flexible manner.
- **Facade**: Provides a simplified interface to a complex subsystem, making it easier to use and understand.
- **Flyweight**: Sharing common parts of state between multiple objects instead of keeping all of the data in each object.
- **Proxy**: Allowing you to perform something either before or after the request gets through to the original object.
 
### Behavioral Patterns
Behavioral patterns deal with object collaboration and the delegation of responsibilities. This category includes:
- **Chain of Responsibility**: Passes a request along a chain of handlers. Each handler processes the request or passes it to the next handler in the chain.
- **Command**: Encapsulates a request as an object, thereby allowing parameterization of clients with queues, requests, and operations.
- **Iterator**: Provides a way to access elements of an aggregate object sequentially without exposing its underlying representation.
- **Mediator**: Defines an object that encapsulates how a set of objects interact, promoting loose coupling.
- **Memento**: Captures and externalizes an object's internal state without violating encapsulation so that the object can be restored to that state later.
- **Observer**: Defines a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.
- **State**: Allows an object to alter its behavior when its internal state changes. The object will appear to change its class.
- **Strategy**: Defines a family of algorithms, encapsulates each one, and makes them interchangeable. The strategy lets the algorithm vary independently from clients that use it.
- **Template Method**: Defines the skeleton of an algorithm in a base class but lets subclasses override specific steps of the algorithm without changing its structure.
- **Visitor**: Defines a new operation to a class without change. It allows adding new operations to existing object structures.

## Usage
To explore each design pattern, navigate to the respective files in the `/Source` directory. 



## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes or enhancements.
