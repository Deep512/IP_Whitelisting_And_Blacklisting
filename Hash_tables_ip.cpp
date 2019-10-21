#include<bits/stdc++.h>
#include<iostream>
#define ll long long int
using namespace std;
struct Hash_table
{
	string ip;
	Hash_table* next;
};
ll size_of_hash;
struct Hash_table* chain[65536];

struct Hash_table* newNode(string s){
	struct Hash_table *temp=(struct Hash_table*)malloc(sizeof(struct Hash_table));
	temp->ip=s;
	temp->next=NULL;
	return temp;
}

ll network_id(string s){
	string s1="";
	ll i=0;
	ll value=0;
	ll count=0;
	while(i<s.length() && count<2){
		if(s[i]!='.'){
			s1=s1+s[i];
		}
		else{
			value=value*256 + stoi(s1);
			count++;
			s1="";
		}
		i++;
	}
	return value;
}

ll hash_func(string s1,string s2){
	ll x1=stoi(s1);
	ll x2=stoi(s2);
	ll pos=x2*256 + x1;
	return pos;
}
ll helper(string s){
	string s1="";
	string s2="";	
	ll i=s.length()-1;
	ll count=0;
	while(i>=0 && count<2){
		if(s[i]!='.' && count==0)
		{
			s1=s[i]+s1;
		}
		if(s[i]=='.'){
			count++;
		}
		if(s[i]!='.' && count==1){
			s2=s[i]+s2;
		}
		i--;
	}
	ll pos=hash_func(s1,s2);
	return pos;
}

ll insert(string s)
{	
	ll pos=helper(s);
	struct Hash_table* node=newNode(s);
	node->next=chain[pos];
	chain[pos]=node;
	size_of_hash+=sizeof(struct Hash_table);
	return pos;
}

bool search(string s)
{
	ll pos=helper(s);
	if(chain[pos]==NULL){
		return false;
	}
	struct Hash_table* temp=chain[pos];
	while(temp){
		if(temp->ip==s){
			return true;
		}
		temp=temp->next;
	}
	return false;
}

void remove_node(string s){
	ll pos=helper(s);
	if(chain[pos]==NULL){
		return;
	}
	struct Hash_table* temp=chain[pos];
	if(chain[pos]->ip==s){
		temp=chain[pos];
		chain[pos]=chain[pos]->next;
		free(temp);
		size_of_hash-=sizeof(struct Hash_table);
		return;
	}
	while(temp->next){
		if(temp->next->ip==s){
			struct Hash_table* node=temp->next;
			temp->next=temp->next->next;
			free(node);
			size_of_hash-=sizeof(struct Hash_table);
			return;
		}
		temp=temp->next;
	}

}

bool searchRangeAll(string s1,string s2){
	ll value1=network_id(s1);
	ll value2=network_id(s2);
	ll pos1=helper(s1);
	ll pos2=helper(s2);
	bool flag;
	struct Hash_table* temp=NULL;
	while(value1<value2){
	    flag=false;
	    temp=chain[pos1];
		while(temp){
			if(network_id(temp->ip)==value1){
				flag=true;
				break;
			}
			temp=temp->next;
		}
		if(flag){
			pos1++;
			if(pos1==65536){
				value1++;
				pos1=0;
			}
		}
		else{
			return false;
		}
	}
	while(pos1<=pos2){
		temp=chain[pos1];
		flag=false;
		while(temp){
			if(network_id(temp->ip)==value1){
				flag=true;
				break;
			}
			temp=temp->next;
		}
		if(flag){
			pos1++;
		}
		else{
			return false;
		}	
	}	
	return true;
}	

bool searchRangeAny(string s1,string s2)
{
	ll value1=network_id(s1);
	ll value2=network_id(s2);
	ll pos1=helper(s1);
	ll pos2=helper(s2);
	struct Hash_table* temp=NULL;
	while(value1<value2){
	    temp=chain[pos1];
		while(temp){
			if(network_id(temp->ip)==value1){
				return true;
			}
			temp=temp->next;
		}
		pos1++;
	}
	while(pos1<=pos2){
		temp=chain[pos1];
		while(temp){
			if(network_id(temp->ip)==value1){
				return true;
			}
			temp=temp->next;
		}
		pos1++;
	}	
	return false;
}    


void byteSize(){
    cout<<65536*1+size_of_hash/8<<" bytes"<<endl;
}

int main(){
	for(ll i=0;i<65536;i++){
		chain[i]=(struct Hash_table*)malloc(sizeof(struct Hash_table));
	    chain[i]=NULL;
	}
    insert("192.168.3.1");
    byteSize();
    insert("192.168.3.2");
    insert("192.168.3.3");
    insert("192.168.3.4");
    byteSize();
    insert("192.168.3.5");
    insert("192.168.3.6");
    insert("192.168.3.7");
    insert("192.168.3.8");
    insert("192.168.3.9");
    insert("192.168.3.10");
    insert("192.168.255.253");
    insert("192.168.255.254");
    insert("192.168.255.255");
    insert("192.169.0.0");
    insert("192.169.0.1");
    insert("192.169.0.2");
    insert("192.169.0.3");
    byteSize();
}
