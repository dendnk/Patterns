// Problem Statement
// You need to create a system for managing different types of documents(e.g., Reports, Resumes, Letters).
// Each type of document has a default template. Users should be able to create new documents by cloning
// these templates and then customizing them as needed.
//
// Prototype Pattern Solution
// The Prototype pattern involves creating new objects by copying existing ones.
// This can be useful for creating objects that are similar but not identical.
//
// Components
// - Prototype : An interface that declares a cloning method.
// - Concrete Prototypes : Classes that implement the Prototype interface.
// - Client Code : Uses the prototype instances to clone new objects.

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace Prototype
{

class Document
{
public:
    Document(const std::string& InContent)
        : Content(InContent)
    {}
    virtual ~Document() = default;

    virtual std::shared_ptr<Document> Clone() const = 0;

    virtual void ShowContent() const = 0;
    virtual void SetContent(const std::string& InContent)
    {
        Content = InContent;
    }

protected:
    std::string Content;
};

class Report : public Document
{
public:
    Report() : Document("Default Report Content") {}
    Report(const Report& Other) : Document(Other.Content) {}

    std::shared_ptr<Document> Clone() const override
    {
        return std::make_shared<Report>(*this);
    }

    void ShowContent() const override
    {
        std::cout << "Report Content: " << Content << std::endl;
    }
};

class Resume : public Document
{
public:
    Resume() : Document("Default Resume Content") {}
    Resume(const Resume& Other) : Document(Other.Content) {}

    std::shared_ptr<Document> Clone() const override
    {
        return std::make_shared<Resume>(*this);
    }

    void ShowContent() const override
    {
        std::cout << "Resume Content: " << Content << std::endl;
    }
};

class Letter : public Document
{
public:
    Letter() : Document("Default Letter Content") {}
    Letter(const Letter& Other) : Document(Other.Content) {}

    std::shared_ptr<Document> Clone() const override
    {
        return std::make_shared<Letter>(*this);
    }

    void ShowContent() const override
    {
        std::cout << "Letter Content: " << Content << std::endl;
    }
};

class DocumentManager
{
public:
    void AddPrototype(const std::string& InKey, std::shared_ptr<Document> InPrototype)
    {
        Prototypes[InKey] = InPrototype;
    }

    std::shared_ptr<Document> CreateDocument(const std::string& InKey)
    {
        if (Prototypes.find(InKey) != Prototypes.end())
        {
            return Prototypes[InKey]->Clone();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Document>> Prototypes;
};

void TestPrototypePattern()
{
    DocumentManager manager;

    manager.AddPrototype("Report", std::make_shared<Report>());
    manager.AddPrototype("Resume", std::make_shared<Resume>());
    manager.AddPrototype("Letter", std::make_shared<Letter>());

    auto report = manager.CreateDocument("Report");
    report->ShowContent();
    report->SetContent("Custom Report Content");
    report->ShowContent();

    auto resume = manager.CreateDocument("Resume");
    resume->ShowContent();
    resume->SetContent("Custom Resume Content");
    resume->ShowContent();

    auto letter = manager.CreateDocument("Letter");
    letter->ShowContent();
    letter->SetContent("Custom Letter Content");
    letter->ShowContent();
}

} // namespace Prototype