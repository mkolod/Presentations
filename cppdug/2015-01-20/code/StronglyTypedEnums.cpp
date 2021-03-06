/*
This example aims to demonstrate the benefit of strongly-typed enums and the pitfalls of the classic C-style enums.
*/
#include <iostream>
#include <bitset>
#include <cstdint>

class Object
{
public:
	enum class Options : uint64_t {None = 11, One = 22, All = 33};//note the custom underlying type!
	enum Fruits {Apples, Oranges, Bananas};
	//enum BagContents {Bananas, Bread, Cheese};//oups, we get a collision

	static void Test()
	{
		std::cout << Oranges << std::endl;//besides polluting the namespace, it implicitly converts to int
		//std::cout << Options::All << std::endl;//enum class members don't provide direct conversions
		
		auto all = static_cast<std::underlying_type<Options>::type>(Options::All);
		std::cout << all << std::endl;
	}

	static void TestSwitchStatementWithEnum(Options input)
	{
		switch (input)
		{
		case Options::One:
			std::cout << "One" << std::endl;
			break;
		case Options::All:
			std::cout << "All" << std::endl;
			break;
		//case None://class enum members will not pollute the namespace!
		default:
			std::cout << "None" << std::endl;
		}
	}
};

static void Foo(int input)
{
	std::cout << input << std::endl;
}

int main()
{
	Object::Test();

	//no namespace pollution
	Object::TestSwitchStatementWithEnum(Object::Options::One);

	//undesired implicit conversion to int
	Foo(Object::Bananas);

	return 0;
}