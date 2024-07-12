// Movie Collection Iterator
// You are tasked with creating a MovieCollection class that stores a list of movies.
// Each movie has a title, a director, and a release year.
// Implement an iterator for the MovieCollection class to traverse through the movies.
// Additionally, create a function that prints out all the movies in the collection using the iterator.

// Create a Movie class with attributes title, director, and year.
// Implement a MovieCollection class to store multiple Movie objects.
// Implement an iterator for the MovieCollection class.
// Implement a function to print out all movies in the collection using the iterator.

#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

namespace Iterator
{

using namespace std;

class Movie
{
public:
	Movie() : Title(""), Director(""), Year(1895) {}

	Movie(const string& inTitle, const string& inDirector, int inYear)
		: Title(inTitle)
		, Director(inDirector)
		, Year(inYear)
	{}

	string GetTitle() const { return Title; }
	string GetDirector() const { return Director; }
	uint16_t GetYear() const { return Year; }

	void PrintInfo() const
	{
		cout << std::left << std::setw(9) << "Title : "
			 << std::left << std::setw(45) << GetTitle()
			 << std::left << std::setw(13) << " Director : "
			 << std::left << std::setw(15) << GetDirector()
			 << std::left << std::setw(8) << " Year :"
			 << std::left << std::setw(4) << GetYear() << endl;
	}

private:
	string Title;
	string Director;
	uint16_t Year;
};

class MovieCollection
{
public:
	void AddMovie(const Movie& movieToAdd)
	{
		Movies[movieToAdd.GetTitle()] = movieToAdd;
	}

	void RemoveMovie(const string& movieTitle)
	{
		Movies.erase(movieTitle);
	}

	Movie* FindMovie(const string& movieTitle)
	{
		auto found = Movies.find(movieTitle);
		if (found != Movies.end())
		{
			std::cout << "\nMovie was found!\n";
			found->second.PrintInfo();
			return &found->second;
		}

		std::cout << "\nMovie not found\n";
		return nullptr;
	}

	class Iterator
	{
		public:
			Iterator(unordered_map<string, Movie>::iterator it) : it(it) {}

			Movie& operator*()
			{
				return it->second;
			}

			Movie* operator->()
			{
				return &it->second;
			}

			Iterator& operator++()
			{
				++it;
				return *this;
			}

			bool operator!=(const Iterator& other)
			{
				return it != other.it;
			}

		private:
			unordered_map<string, Movie>::iterator it;
	};

	Iterator begin()
	{
		return Iterator(Movies.begin());
	}

	Iterator end()
	{
		return Iterator(Movies.end());
	}

private:
	unordered_map<string, Movie> Movies;

};

void PrintMovies(MovieCollection& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		it->PrintInfo();
	}
}

void TestIteratorPattern()
{
	MovieCollection collection;

	collection.AddMovie(Movie("Harry Potter and the Philosopher’s Stone",		"Chris Columbus",	2001));
	collection.AddMovie(Movie("Harry Potter and the Chamber of Secrets",		"Chris Columbus",	2002));
	collection.AddMovie(Movie("Harry Potter and the Prisoner of Azkaban",		"Alfonso Cuaron",	2004));
	collection.AddMovie(Movie("Harry Potter and the Goblet of Fire",			"Michael Newell",	2005));
	collection.AddMovie(Movie("Harry Potter and the Order of the Phoenix",		"David Yates",		2007));
	collection.AddMovie(Movie("Harry Potter and the Half-Blood Prince",			"David Yates",		2009));
	collection.AddMovie(Movie("Harry Potter and the Deathly Hallows: Part I",	"David Yates",		2010));
	collection.AddMovie(Movie("Harry Potter and the Deathly Hallows: Part II",	"David Yates",		2011));

	PrintMovies(collection);

	std::cout << "\nRemoving 'Prisoner of Azkaban'...\n";
	collection.RemoveMovie("Harry Potter and the Prisoner of Azkaban");

	PrintMovies(collection);

	std::cout << "\nFinding 'Deathly Hallows: Part I'...\n";
	Movie* foundMovie = collection.FindMovie("Harry Potter and the Deathly Hallows: Part I");

	std::cout << "\nFinding 'Deathly Hallows: Part II'...\n";
	foundMovie = collection.FindMovie("Deathly Hallows: Part II");

	std::cout << "\nFinding 'Star Wars'...\n";
	foundMovie = collection.FindMovie("Star Wars");
}

} // Iterator
