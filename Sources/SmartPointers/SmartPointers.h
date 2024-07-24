// Custom smart pointers implementation

#pragma once
#include <iostream>
#include <cassert>

namespace SmartPointers
{
struct ControlStruct
{
	int SharedCounter;
	int WeakCounter;

	ControlStruct() : SharedCounter(1), WeakCounter(1) {}
};

template<typename T>
class WeakPointer;

template<typename T>
class SharedPointer
{
public:
	explicit SharedPointer(T* InPointer = nullptr)
		: Pointer(InPointer)
		, ControlBlock(InPointer != nullptr ? new ControlStruct() : nullptr)
	{}

	SharedPointer(const SharedPointer<T>& other)
		: Pointer(other.Pointer)
		, ControlBlock(other.ControlBlock)
	{
		if (ControlBlock != nullptr)
		{
			ControlBlock->SharedCounter++;
		}
	}

	SharedPointer(SharedPointer<T>&& other) noexcept
		: Pointer(other.Pointer)
		, ControlBlock(other.ControlBlock)
	{
		other.Pointer = nullptr;
		other.ControlBlock = nullptr;
	}

	SharedPointer(const WeakPointer<T> other)
		: Pointer(other.Pointer)
		, ControlBlock(other.ControlBlock)
	{
		if (ControlBlock != nullptr)
		{
			ControlBlock->SharedCounter++;
		}
	}

	~SharedPointer()
	{
		Release();
	}

	SharedPointer<T>& operator=(const SharedPointer<T>& other)
	{
		if (this != &other)
		{
			Release();

			Pointer = other.Pointer;
			ControlBlock = other.ControlBlock;
			if (ControlBlock != nullptr)
			{
				ControlBlock->SharedCounter++;
			}
		}
		return *this;
	}

	SharedPointer<T>& operator=(SharedPointer<T>&& other) noexcept
	{
		if (this != &other)
		{
			Release();

			Pointer = other.Pointer;
			ControlBlock = other.ControlBlock;

			other.Pointer = nullptr;
			other.ControlBlock = nullptr;
		}
		return *this;
	}

	T* operator->() const
	{
		return Pointer;
	}

	T& operator*() const
	{
		return *Pointer;
	}

	T* Get() const { return Pointer; }

	int UseCount() const { return ControlBlock != nullptr ? ControlBlock->SharedCounter : 0; }



private:
	void Release()
	{
		if (ControlBlock != nullptr)
		{
			if (--ControlBlock->SharedCounter == 0)
			{
				delete Pointer;
				Pointer = nullptr;
				if (ControlBlock->WeakCounter == 0)
				{
					delete ControlBlock;
					ControlBlock = nullptr;
				}
			}
		}
	}

private:
	T* Pointer;
	ControlStruct* ControlBlock;

	friend class WeakPointer<T>;
};

template<typename T>
class WeakPointer
{
public:
	WeakPointer()
		: Pointer(nullptr)
		, ControlBlock(nullptr)
	{}

	WeakPointer(const SharedPointer<T>& InSharedPointer)
		: Pointer(InSharedPointer.Pointer)
		, ControlBlock(InSharedPointer.ControlBlock)
	{
		if (ControlBlock != nullptr)
		{
			ControlBlock->WeakCounter++;
		}
	}

	WeakPointer(const WeakPointer<T>& other)
		: Pointer(other.Pointer)
		, ControlBlock(other.ControlBlock)
	{
		if (ControlBlock != nullptr)
		{
			ControlBlock->WeakCounter++;
		}
	}

	WeakPointer(WeakPointer<T>&& other) noexcept
		: Pointer(other.Pointer)
		, ControlBlock(other.ControlBlock)
	{
		other.Pointer = nullptr;
		other.ControlBlock = nullptr;
	}

	~WeakPointer()
	{
		Release();
	}

	WeakPointer<T>& operator=(const WeakPointer<T>& other)
	{
		if (this != &other)
		{
			Release();

			Pointer = other.Pointer;
			ControlBlock = other.ControlBlock;
			if (ControlBlock != nullptr)
			{
				ControlBlock->WeakCounter++;
			}
		}
		return *this;
	}

	WeakPointer<T>& operator=(WeakPointer<T>&& other) noexcept
	{
		if (this != &other)
		{
			Release();

			Pointer = other.Pointer;
			ControlBlock = other.ControlBlock;

			other.Pointer = nullptr;
			other.ControlBlock = nullptr;
		}
		return *this;
	}

	SharedPointer<T> Lock() const
	{
		if (IsExpired())
		{
			return SharedPointer<T>();
		}

		return SharedPointer<T>(*this);
	}

	bool IsExpired() const
	{
		return ControlBlock == nullptr || ControlBlock->SharedCounter == 0;
	}

private:
	void Release()
	{
		if (ControlBlock != nullptr)
		{
			if (--ControlBlock->WeakCounter == 0)
			{
				if (ControlBlock->SharedCounter == 0)
				{
					delete ControlBlock;
					ControlBlock = nullptr;
				}
			}
		}
	}


	WeakPointer(T* InPointer, ControlStruct* InControlBlock)
		: Pointer(InPointer)
		, ControlBlock(InControlBlock)
	{}

private:
	T* Pointer;
	ControlStruct* ControlBlock;

	friend class SharedPointer<T>;
};

template<typename T>
class UniquePointer
{
public:
	UniquePointer(T* InPointer = nullptr)
		: Pointer(InPointer)
	{}

	~UniquePointer()
	{
		delete Pointer;
	}

	UniquePointer(UniquePointer<T>&& Other) noexcept
	{
		Pointer = Other.Pointer;

		Other.Pointer = nullptr;
	}

	UniquePointer<T>& operator=(UniquePointer<T>&& Other) noexcept
	{
		if (this != &Other)
		{
			delete Pointer;

			Pointer = Other.Pointer;

			Other.Pointer = nullptr;
		}

		return *this;
	}

	UniquePointer(const UniquePointer<T>& other) = delete;
	UniquePointer<T> operator=(const UniquePointer<T>& other) = delete;

	T* operator->() const
	{
		return Pointer;
	}

	T& operator*() const
	{
		return *Pointer;
	}

	T* Release()
	{
		T* OldPointer = Pointer;
		Pointer = nullptr;
		return OldPointer;
	}

	void Reset(T* NewPointer = nullptr)
	{
		delete Pointer;
		Pointer = NewPointer;
	}

	T* Get() const
	{
		return Pointer;
	}

private:
	T* Pointer;
};

void TestSharedPointer()
{
	// Test constructor
	SharedPointer<int> sp1(new int(10));
	assert(*sp1 == 10);
	assert(sp1.UseCount() == 1);

	// Test copy constructor
	SharedPointer<int> sp2(sp1);
	assert(sp1.UseCount() == 2);
	assert(sp2.UseCount() == 2);
	assert(*sp2 == 10);

	// Test move constructor
	SharedPointer<int> sp3(std::move(sp2));
	assert(sp1.UseCount() == 2);
	assert(sp2.UseCount() == 0);
	assert(sp3.UseCount() == 2);
	assert(*sp3 == 10);
	assert(sp2.Get() == nullptr);

	// Test copy assignment operator
	SharedPointer<int> sp4;
	sp4 = sp1;
	assert(sp1.UseCount() == 3);
	assert(sp4.UseCount() == 3);
	assert(*sp4 == 10);

	// Test move assignment operator
	SharedPointer<int> sp5;
	sp5 = std::move(sp3);
	assert(sp1.UseCount() == 3);
	assert(sp3.UseCount() == 0);
	assert(sp5.UseCount() == 3);
	assert(*sp5 == 10);
	assert(sp3.Get() == nullptr);

	// Test dereference and member access operators
	{
		struct TestStruct1
		{
			int data = 172;

			void foo()
			{
				std::cout << "foo called" << std::endl;
			}
		};

		SharedPointer<TestStruct1> sp6(new TestStruct1());
		assert((*sp6).data == 172);
		assert(sp6->data == 172);
	}

	// Test destructor
	{
		SharedPointer<int> sp7(new int(30));
		assert(sp7.UseCount() == 1);
	} // sp7 goes out of scope here and should properly release resources

	// Edge case: Empty SharedPointer
	SharedPointer<int> sp8;
	assert(sp8.Get() == nullptr);
	assert(sp8.UseCount() == 0);

	std::cout << __FUNCTION__ << " : All tests passed!" << std::endl;
}

void TestWeakPointer()
{
	// Default constructor
	WeakPointer<int> wp1;
	assert(wp1.IsExpired());

	// Constructor with SharedPointer
	SharedPointer<int> sp1(new int(20));
	WeakPointer<int> wp2(sp1);
	assert(!wp2.IsExpired());

	// Copy constructor
	WeakPointer<int> wp3 = wp2;
	assert(!wp3.IsExpired());

	// Move constructor
	WeakPointer<int> wp4 = std::move(wp3);
	assert(!wp4.IsExpired());
	assert(wp3.IsExpired());

	// Copy assignment operator
	WeakPointer<int> wp5;
	wp5 = wp2;
	assert(!wp5.IsExpired());

	// Move assignment operator
	WeakPointer<int> wp6;
	wp6 = std::move(wp5);
	assert(!wp6.IsExpired());
	assert(wp5.IsExpired());

	// Lock to get SharedPointer
	SharedPointer<int> sp2 = wp2.Lock();
	assert(sp2.UseCount() == 2);
	assert(*sp2 == 20);

	// Expire the WeakPointer
	sp2.~SharedPointer();
	assert(!wp2.IsExpired());
	sp1.~SharedPointer();
	assert(wp2.IsExpired());

	std::cout << __FUNCTION__ << " : All tests passed!" << std::endl;
}

void TestCycleReferencing()
{
	struct Node {
		//SharedPointer<Node> next; // Circular references
		WeakPointer<Node> next;
		Node() = default;
		Node(const SharedPointer<Node>& nextNode) : next(nextNode) {}
	};

	// Create nodes and form a cycle
	SharedPointer<Node> node1(new Node());
	SharedPointer<Node> node2(new Node());
	SharedPointer<Node> node3(new Node());

	// Create a cycle: node1 -> node2 -> node3 -> node1
	node1->next = node2;
	node2->next = node3;
	node3->next = node1;

	// Check use counts in the cycle
	//std::cout << __FUNCTION__ << " node1.UseCount() " << node1.UseCount() << std::endl;
	//std::cout << __FUNCTION__ << " node2.UseCount() " << node2.UseCount() << std::endl;
	//std::cout << __FUNCTION__ << " node3.UseCount() " << node3.UseCount() << std::endl;

	assert(node1.UseCount() == 1);
	assert(node2.UseCount() == 1);
	assert(node3.UseCount() == 1);

	std::cout << __FUNCTION__ << " : Cycle test passed!" << std::endl;
}

void TestUniquePointer()
{
	// Test constructor and operator*
	UniquePointer<int> up1(new int(10));
	assert(*up1 == 10);

	// Test move constructor
	UniquePointer<int> up2(std::move(up1));
	assert(up1.Get() == nullptr);
	assert(*up2 == 10);

	// Test move assignment operator
	UniquePointer<int> up3;
	up3 = std::move(up2);
	assert(up2.Get() == nullptr);
	assert(*up3 == 10);

	//UniquePointer<int> up4(up3); // will not compile
	//UniquePointer<int> up5;
	//up5 = up1;

	// Test Release
	UniquePointer<int> up4(new int(20));
	int* rawPtr = up4.Release();
	assert(rawPtr != nullptr);
	delete rawPtr; // Since we released ownership, we need to delete the raw pointer ourselves.
	assert(up4.Get() == nullptr);

	// Test Reset
	UniquePointer<int> up5(new int(30));
	up5.Reset(new int(40));
	assert(*up5 == 40);

	std::cout << __FUNCTION__ << " : All tests passed!" << std::endl;
}

void TestSmartPointers()
{
	TestSharedPointer();
	TestWeakPointer();
	TestCycleReferencing();
	TestUniquePointer();
}

} // namespace SmartPointers
