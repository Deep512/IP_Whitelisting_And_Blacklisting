#include <iostream>
using namespace std;

struct Node
{
	int value;
	Node* keys[10];
};

Node* newNode()
{
	Node* temp = new Node;
	temp->value = 0;
	
	for (int a = 0; a < 10; a++)
	{
		temp->keys[a] = NULL;
	}
	
	return temp;
}

class Trie
{
private:
	
	Node* root;
	
	int size;
	void byteSize_helper(Node*);
	
public:

	Trie();

	bool search(string);
	bool searchRange(string, string); //TO DO
	
	void insert(string);
	void remove(string);
	
	int byteSize();
};

Trie::Trie()
{
	root = newNode();
	size = 0;
}

bool Trie::search(string str)
{
	Node* temp = root;
	
	for (int a = 0; a < str.size(); a++)
	{
		if (str[a] < '0' || str[a] > '9')
		{
			continue;
		}
		
		if (temp->keys[str[a] - '0'])
		{
			temp = temp->keys[str[a] - '0'];
		}
		
		else
		{
			return false;
		}
	}
	
	if (temp->value)
	{
		return true;
	}
	
	return false;
}

void Trie::insert(string str)
{
	Node* temp = root;
	
	for (int a = 0; a < str.size(); a++)
	{
		if (str[a] < '0' || str[a] > '9')
		{
			continue;
		}
		
		if (temp->keys[str[a] - '0'])
		{
			temp = temp->keys[str[a] - '0'];
		}
		
		else
		{
			temp->keys[str[a] - '0'] = newNode();
			temp = temp->keys[str[a] - '0'];
		}
	}
	
	temp->value = 1;
}

void Trie::byteSize_helper(Node* node)
{
	if (!node)
	{
		return;
	}
	
	size += sizeof(Node);
	
	for (int a = 0; a < 10; a++)
	{
		byteSize_helper(node->keys[a]);
	}
}

int Trie::byteSize()
{
	size = 0;
	byteSize_helper(root);
	size += sizeof(Trie);
	
	return size;
}

int main()
{
	Trie t;
	t.insert("192");
	cout << t.byteSize();
}
