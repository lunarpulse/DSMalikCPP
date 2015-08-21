#include <cinttypes>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <functional>
#include <unordered_set>

using namespace std;

class unorderedSetObject;
namespace std
{
	template <>
	class hash<unorderedSetObject>
	{
	public:
		template <typename... Args>
		size_t operator()(Args&&... unorderedSetObject) const
		{
			return hash<string>()((forward<Args...>(unorderedSetObject...)).GetName());
		}
	};
}
class unorderedSetObject
{
private:
	string m_Name;
	size_t m_Hash{};
public:
	unorderedSetObject(const string& name) 
	{
		m_Name=name;
		m_Hash = hash<unorderedSetObject>()(*this);
	}
	const string& GetName() const
	{
		return m_Name;
	}
	const size_t& GetHash() const
	{
		return m_Hash;
	}
	bool operator==(const unorderedSetObject& other) const
	{
		return m_Hash == other.m_Hash;
	}
};

class SetObject
{
private:
	string m_Name{};
	int32_t m_Key{};
public:
	SetObject(int32_t key, const string& name)
		
	{
		m_Name = name;
		m_Key = key;
	}
	SetObject(int32_t key)
		: SetObject(key, "")
	{
	}
	const string& GetName() const
	{
		return m_Name;
	}
	int32_t GetKey() const
	{
		return m_Key;
	}
	bool operator<(const SetObject& other) const
	{
		return m_Key < other.m_Key;
	}
	bool operator>(const SetObject& other) const
	{
		return m_Key > other.m_Key;
	}
};

class MapObject
{
private:
	string m_Name;

public:
	MapObject(const string& name) 
	{
		m_Name = name;
	}

	const string& GetName() const
	{
		return m_Name;
	}
};

int main(int argv, char* argc[])
{
	set<SetObject> mySet
	{
		{ 6, "Six" },
		{ 3, "Three" },
		{ 4, "Four" },
		{ 1, "One" },
		{ 2, "Two" }
	};

	for (auto&& number : mySet)
	{
		cout << number.GetName() << endl;
	}
	cout << endl;
	mySet.emplace(SetObject(5, "Five"));

	for (auto&& number : mySet)
	{
		cout << number.GetName() << endl;
	}
	auto iter = mySet.find(3);
	if (iter != mySet.end())
	{
		cout << "Found: " << iter->GetName() << endl;
	}
	cout << endl;

	set<SetObject, greater<SetObject>> mySet1
	{
		{ 6, "Six" },
		{ 3, "Three" },
		{ 4, "Four" },
		{ 1, "One" },
		{ 2, "Two" }
	};
	for (auto&& number : mySet1)
	{
		cout << number.GetName() << endl;
	}
	auto iter0 = mySet1.find(4);
	if (iter0 != mySet1.end())
	{
		cout << "Found: " << iter0->GetName() << endl;
	}

	map<int32_t, MapObject, greater<int32_t>> myMap
	{
		pair<int32_t, MapObject>(6, MapObject("Six")),
		pair<int32_t, MapObject>(2, MapObject("Two")),
		pair<int32_t, MapObject>(1, MapObject("Il")),
		pair<int32_t, MapObject>(3, MapObject("Sam")),
		pair<int32_t, MapObject>(4, MapObject("Sa"))
	};

	for (auto&& number : myMap)
	{
		cout << number.second.GetName() << endl;
	}
	cout << endl;

	myMap.emplace(pair<int32_t, MapObject>(5, MapObject("O")));
	for (auto&& number : myMap)
	{
		cout << number.second.GetName() << endl;
	}
	cout << endl;

	unordered_set<unorderedSetObject> myUnorderedSet;
	myUnorderedSet.emplace("Five");
	myUnorderedSet.emplace("fivE");
	myUnorderedSet.emplace("fiVe");

	myUnorderedSet.emplace("fIve");

	myUnorderedSet.emplace("One");
	myUnorderedSet.emplace("Two");
	myUnorderedSet.emplace("Three");
	myUnorderedSet.emplace("Four");

	cout << showbase << hex;

	for (auto && number : myUnorderedSet)
	{
		cout << number.GetName() << "	-	" << number.GetHash() << endl;
	}
	auto iter2 = myUnorderedSet.find({ "One" });
	if (iter2 != myUnorderedSet.end())
	{
		cout << "Found: " << iter2->GetName() << " with hash: " << iter2->GetHash() << endl;
	}
	return 0;
}