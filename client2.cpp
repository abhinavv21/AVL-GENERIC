#include "avl.cpp"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;
void disp(int i) 
{  // function:
  cout << ' ' << i;
}

int main()
{
	int  item;
	vector<int> b={1,2,3,4,5,6,7,8,9,10,10};
	avl<int,less<int>> a(b.begin(),b.end());
	/*a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(-1);
	a.insert(0);
	a.insert(4);*/
	a.display();
	cout<<endl;
	for_each(a.begin(), a.end(), disp);
	cout<<endl;
	cout<<7<<" "<<5<<" "<<a.common_ancestor(7,5)->key<<endl;
	cout<<1<<" "<<9<<" "<<a.common_ancestor(1,9)->key<<endl;
	cout<<9<<" "<<10<<" "<<a.common_ancestor(9,10)->key<<endl;
	cout<<10<<" "<<10<<" "<<a.common_ancestor(10,10)->key<<endl;
}
