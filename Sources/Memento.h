// Create a simple text editor application that allows users to type text, save the current state,
// and undo changes by restoring the state from previously saved versions.

// Requirements
// - TextEditor Class : This class will have methods to write text, save the current state, and restore to a previous state.
// - Memento Class : This class will store the state of the TextEditor class.
// - Caretaker Class : This class will manage the saving and restoring of the TextEditor states.

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Memento
{

class Memento
{
public:
	explicit Memento(const std::string& state) : State_(state) {}

	std::string GetState() const { return State_; }

private:
	std::string State_;
};

class TextEditor
{
public:
	void Write(const std::string& text)
	{
		Text_ += text;
	}

	void ShowText()
	{
		std::cout << "Current text : " << Text_ << std::endl;
	}

	std::shared_ptr<Memento> Save() const
	{
		return std::make_shared<Memento>(Text_);
	}

	void Restore(const std::shared_ptr<Memento> memento)
	{
		if (memento != nullptr)
		{
			Text_ = memento->GetState();
		}
	}

private:
	std::string Text_;
};

class Caretaker
{
public:
	void Save(const std::shared_ptr<TextEditor>& editor)
	{
		mementos_.emplace_back(editor->Save());
	}

	void Undo(const std::shared_ptr<TextEditor>& editor)
	{
		if (!mementos_.empty())
		{
			editor->Restore(mementos_.back());
			mementos_.pop_back();
		}
	}

private:
	std::vector<std::shared_ptr<Memento>> mementos_;
};



void TestMementoPattern()
{
	auto editor = std::make_shared<TextEditor>();
	Caretaker caretaker;

	editor->Write("Hello, ");
	editor->ShowText();

	caretaker.Save(editor);

	editor->Write("World!");
	editor->ShowText();

	caretaker.Save(editor);

	editor->Write(" This is a test.");
	editor->ShowText();

	caretaker.Undo(editor);
	editor->ShowText();

	caretaker.Undo(editor);
	editor->ShowText();
}

} // namespace Memento
