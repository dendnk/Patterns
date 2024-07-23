// Create a simple text editor application that supports undo and redo operations.
// The text editor can perform operations like adding text, removing text, and replacing text.
// Each operation should be encapsulated as a command object.

#pragma once

#include <iostream>
#include <memory>
#include <stack>
#include <string>

namespace Command
{

using namespace std;

class Command // Command interface
{
public:
	virtual ~Command() {}

	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

class TextEditor // Receiver
{
public:
	void AddText(const string& inText)
	{
		content += inText;
	}

	void RemoveText(size_t length)
	{
		if (length > content.size())
		{
			content.clear();
		}
		else
		{
			content.erase(content.size() - length);
		}
	}

	void ReplaceText(const string& inText)
	{
		content = inText;
	}

	const string& GetContent() const
	{
		return content;
	}

private:
	string content;
};

class AddTextCommand : public Command // Concrete Commands
{
public:
	AddTextCommand(TextEditor& inEditor, const string& inText)
		: editor(inEditor)
		, text(inText)
	{}

	void Execute() override
	{
		editor.AddText(text);
	}

	void Undo() override
	{
		editor.RemoveText(text.size());
	}

private:
	TextEditor& editor;
	string text;
};

class RemoveTextCommand : public Command // Concrete Commands
{
public:
	RemoveTextCommand(TextEditor& inEditor, size_t length)
		: editor(inEditor)
		, length(length)
	{}

	void Execute() override
	{
		previousText = editor.GetContent().substr(editor.GetContent().size() - length);
		editor.RemoveText(length);
	}

	void Undo() override
	{
		editor.AddText(previousText);
	}

private:
	TextEditor& editor;
	size_t length;
	string previousText;
};

class ReplaceTextCommand : public Command // Concrete Commands
{
public:
	ReplaceTextCommand(TextEditor& inEditor, const string& newText)
		: editor(inEditor), newText(newText) {}

	void Execute() override
	{
		oldText = editor.GetContent();
		editor.ReplaceText(newText);
	}

	void Undo() override
	{
		editor.ReplaceText(oldText);
	}

private:
	TextEditor& editor;
	string newText;
	string oldText;
};

class CommandManager // Invoker
{
public:
	void ExecuteCommand(unique_ptr<Command> command)
	{
		command->Execute();
		undoStack.push(move(command));

		// Clear redo stack when a new command is executed
		while (!redoStack.empty())
		{
			redoStack.pop();
		}
	}

	void Undo() {
		if (!undoStack.empty())
		{
			undoStack.top()->Undo();
			redoStack.push(move(undoStack.top()));
			undoStack.pop();
		}
	}

	void Redo() {
		if (!redoStack.empty())
		{
			redoStack.top()->Execute();
			undoStack.push(move(redoStack.top()));
			redoStack.pop();
		}
	}

private:
	stack<unique_ptr<Command>> undoStack;
	stack<unique_ptr<Command>> redoStack;
};

void TestCommandPattern()
{
	TextEditor textEditor;
	CommandManager commandManager;

	commandManager.ExecuteCommand(make_unique<AddTextCommand>(textEditor, "Hello, "));
	cout << "Content: " << textEditor.GetContent() << endl;

	commandManager.ExecuteCommand(make_unique<AddTextCommand>(textEditor, "world!"));
	cout << "Content: " << textEditor.GetContent() << endl;

	commandManager.Undo();
	cout << "After undo: " << textEditor.GetContent() << endl;

	commandManager.Redo();
	cout << "After redo: " << textEditor.GetContent() << endl;

	commandManager.ExecuteCommand(make_unique<ReplaceTextCommand>(textEditor, "Hi there!"));
	cout << "Content: " << textEditor.GetContent() << endl;

	commandManager.Undo();
	cout << "After undo: " << textEditor.GetContent() << endl;

	commandManager.Redo();
	cout << "After redo: " << textEditor.GetContent() << endl;
}

} // Command
