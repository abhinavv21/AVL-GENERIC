#include "avl.cpp"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	int choice, item;
    avl<int,less<char>> a;
    
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        cout<<"3.Inorder traversal"<<endl;
		cout<<"4.Delete Element"<<endl;
		cout<<"5.Internal Find Element"<<endl;
		cout<<"6.Generic Find Element"<<endl;
        cout<<"7.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;

            a.insert(item);
            break;

        case 2:
            
            cout<<"Balanced AVL Tree:"<<endl;
            a.display();
            break;
        case 3:
            cout<<"Inorder Traversal:"<<endl;
            a.inorder();
            cout<<endl;
            break;

        case 4:
			cout<<"Enter value to be deleted: ";
			cin>>item;
			a.deleteNode(item);
			break;
        case 5:
		{
			cout<<"Enter value to search: ";
			cin>>item;
			Node<int>* iter=a.find(item);
			if(iter!=nullptr)
			{
				cout<<iter->key<<" found!"<<endl;
			}
			else
			{
				cout<<"key not found"<<endl;
			}
		}
			break;
		case 6:
		{
			cout<<"Enter value to search: ";
			cin>>item;
			auto iter=find(a.begin(), a.end(),item);
			if(iter!=nullptr)
			{
				cout<<*iter<<" found!"<<endl;
			}
			else
			{
				cout<<"key not found"<<endl;
			}
		}
		break;
        case 7:
            exit(1);
            break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;

}
