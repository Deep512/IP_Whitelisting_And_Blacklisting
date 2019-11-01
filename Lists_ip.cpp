#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class List
{
private:
	
	vector<string> arr;
	
	string padWithZeroes_helper(char*);
	string IPFormat_helper(string);
	
	string nextIP_helper(string);
	
public:
	
	List();
	
	int search(string);
	bool searchRangeAll(string, string);
	bool searchRangeAny(string, string);
	
	void insert(string);
	void remove(string);
	
	int byteSize();
};

List::List()
{
	arr.clear();
}

string List::padWithZeroes_helper(char* arr)
{
	string str(arr);
	
	if (str.size() == 1)
	{
		str = "00" + str;
	}
	
	if (str.size() == 2)
	{
		str = "0" + str;
	}
	
	return str;
}

string List::IPFormat_helper(string str)
{
	string temp = "";
	char* tempC = strtok((char*) str.c_str(), ".");
	while (tempC)
	{
		temp += padWithZeroes_helper(tempC);
		tempC = strtok(NULL, ".");
	}
	
	return temp;
}

string List::nextIP_helper(string str)
{
	string temp[4] = {str.substr(0, 3), str.substr(3, 3), str.substr(6, 3), str.substr(9, 3)};
	
	for (int a = 3; a > -1; a--)
	{
		temp[a] = padWithZeroes_helper((char*) to_string((stoi(temp[a]) + 1) % 256).c_str());
		if (temp[a] != "000")
		{
			break;
		}
	}
	
	return (temp[0] + temp[1] + temp[2] + temp[3]);
}

int List::search(string str)
{
	str = IPFormat_helper(str);
	
	for (int a = 0; a < arr.size(); a++)
	{
		if (str == arr[a])
		{
			return a+1;
		}
	}
	
	return 0;
}

bool List::searchRangeAll(string A, string B)
{
	string temp1 = IPFormat_helper(A);
	string temp2 = IPFormat_helper(B);
	
	string begin = min(temp1, temp2);
	string end = max(temp1, temp2);
	
	if (!search(begin))
	{
		return false;
	}
	
	string str = begin;
	while (str != end)
	{
		str = nextIP_helper(str);
		if (!search(str))
		{
			return false;
		}
	}
	
	return true;
}

bool List::searchRangeAny(string A, string B)
{
	string temp1 = IPFormat_helper(A);
	string temp2 = IPFormat_helper(B);
	
	string begin = min(temp1, temp2);
	string end = max(temp1, temp2);
	
	if (search(begin))
	{
		return true;
	}
	
	string str = begin;
	while (str != end)
	{
		str = nextIP_helper(str);
		if (search(str))
		{
			return true;
		}
	}
	
	return false;
}

void List::insert(string str)
{
	str = IPFormat_helper(str);
	
	if (search(str))
	{
		return;
	}
	
	arr.push_back(str);
}

void List::remove(string str)
{
	str = IPFormat_helper(str);
	
	int a = search(str);
	
	if (a)
	{
		arr.erase(arr.begin() + a - 1);
	}
}

int List::byteSize()
{
	return (sizeof(arr) + sizeof(string) * arr.capacity());
}

int main()
{
	List l;
	l.insert("192.168.1.0");
	cout << l.search("192.168.1.000") << endl << l.search("192.168.1.0") << endl;
	l.insert("1.1.1.1");
	cout << l.byteSize() << endl;
	
	l.remove("192.168.1.0");
	cout << l.search("192.168.1.000") << endl << l.search("192.168.1.0") << endl;
}