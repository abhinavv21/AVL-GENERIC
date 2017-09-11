#include "avl.cpp"
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
void disp(string i)
{
	cout<<i<<endl;
}
int main()
{
	fstream f("input.txt");
	avl<string,less<string>> a;
	string word;
	while(f>>word)
	{
		for (int i = 0, len = word.size(); i < len; i++)
		{
			if (ispunct(word[i]))
			{
				word.erase(i--, 1);
				len = word.size();
			}
		}
		a.insert(word);
	}
	a.display();
	cout<<endl;
	cout<<"Enter word to find: "<<"\n";
	cin>>word;
	auto e=a.end();	
	auto k=find(a.begin(),e,word);
	if(k!=e){cout<<*k<<" Found"<<endl;}
	else{cout<<"not found"<<endl;}
	
}
