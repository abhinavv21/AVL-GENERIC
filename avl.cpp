#include<iostream>
#include <vector>
#include <stack>
using namespace std;
template<typename T>
struct Node
{
	public:
	struct Node<T>* left=NULL;
	struct Node<T>* right=NULL;
	struct Node<T>* parent=NULL;
	T key;
	int height;
	
};
template<typename T, typename compare=less<T>>
class avl
{
	public:
	compare comp;
	Node<T>* root;
	vector<Node<T>*> ref;
	int size;
	template <typename Iterator>
	avl(Iterator first, Iterator last)
	{
		this->root=nullptr;
		this->size=0;
		while (first!=last)
		{
			insert(*first);
			++first;
		  }
	}
	avl()
	{
		this->root=nullptr;
		this->size=0;
		
	}
	//CHECK DTOR-does this delete all the nodes???

	//template<typename T>
	~avl()
	{	
		for_each(ref.begin(),ref.end(),[](auto e){delete e;});
	}

	int max(int a, int b)
	{
		return (a > b)? a : b;
	}

	int height(Node<T>* temp)
	{
		int h = 0;
		if (temp != NULL)
		{
			int l_height = height (temp->left);
			int r_height = height (temp->right);
			int max_height = max (l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}

	//template<typename T>
	int getBalance(Node<T> *N)
	{
		int l_height = height (N->left);
			int r_height = height (N->right);
			int b_factor= l_height - r_height;
			return b_factor;
	}

	//template<typename T>
	void preOrder(Node<T>* node)
	{
		if(node!=NULL)
		{
			cout<<node->key<<"\n";
			preOrder(node->left);
			preOrder(node->right);
		}
	}
	void inorder()
	{
		inorderFn(root);
	}
	void inorderFn(Node<T>* node)
	{
		if (node == NULL)
			return;
		inorderFn (node->left);
		cout<<node->key<<"  ";
		cout<<endl;
		#if 0
		if(node->parent!=NULL)
			cout<<node->parent->key<<"  ";
		
		#endif
		
		inorderFn (node->right);
	}


	Node<T>* leftRotate(Node<T> *x)
	{
		Node<T> *y = x->right;
		Node<T> *T2 = y->left;
		y->left = x;
		if (x!=NULL)
			x->parent=y;
		x->right = T2;
		if (T2!=NULL)
			T2->parent=x;
		x->height = max(height(x->left), height(x->right))+1;
		y->height = max(height(y->left), height(y->right))+1;
		return y;
	}

	Node<T>* rightRotate(Node<T> *y)
	{
		Node<T> *x = y->left;
		Node<T> *T2 = x->right;
		x->right = y;
		if (y!=NULL)
			y->parent=x;
		y->left = T2;
		if (T2!=NULL)
			T2->parent=y;
		y->height = max((height(y->left)), (height(y->right)))+1;
		x->height = max((height(x->left)), (height(x->right)))+1;
		return x;
	}

	Node<T>* balance(Node<T>* temp)
	{

		int bfactor = getBalance(temp);
		Node<T>* temp1=temp;
			if (bfactor > 1)
			{
				if (getBalance(temp->left) > 0)

			{
				temp=rightRotate(temp);
			}

			else{

				temp->left=leftRotate(temp->left);
				temp=rightRotate(temp);
			}
			}
			else if (bfactor < -1)
			{
				if (getBalance(temp->right) > 0)
			{	
				temp->right=rightRotate(temp->right);
				temp=leftRotate(temp);
			}
					else
			{
						temp =leftRotate(temp);
			}    	
		}
			return temp;

	}
	Node<T>* insert(T key)
	{
		this->size++;
		//Node<T>* node=root;
		root=insertFn(root,key);
		root->parent=NULL;
	}
		
	//template<typename T>
	Node<T>* insertFn(Node<T>* node,T key)
	{
		if (node == NULL)
		{	
			node=new Node<T>;	
			node->key=key;
			node->height=1;
			node->left=NULL;
			node->right=NULL;
			ref.push_back(node);

		}
		else if (comp(key,node->key))
			{
				Node<T>* t=insertFn(node->left,key);
				node->left = t;
				if (t!=NULL)
					t->parent=node;
				node->height=1+node->height;
				node = balance(node);
			}
			else
			{
				Node<T>* t=insertFn(node->right,key);
				node->right =t ;
				if (t!=NULL)
					t->parent=node;
				node->height=1+node->height;
				node = balance(node);
			}	

			return node;
	}
	
	void display()
	{
		displayFn(root,1);
	}
	void displayFn(Node<T> *ptr, int level)
	{
		int i;
		if (ptr!=NULL)
		{
			displayFn(ptr->right, level + 1);
			printf("\n");
			if (ptr == root)
			cout<<"Root -> ";
			for (i = 0; i < level && ptr != root; i++)
				cout<<"        ";
			cout<<ptr->key;
			displayFn(ptr->left, level + 1);
		}
	}
	void deleteNode(T key)
	{
		
		 deleteNodefn(root,key);
	}
	Node<T>* deleteNodefn(Node<T>* node,T key)
	{
		if (node == NULL)
			return node;
		else if ( key < node->key )
			node->left = deleteNodefn(node->left, key);

		else if( key > node->key )
			node->right = deleteNodefn(node->right, key);

		else if(key==node->key)
		{
			if( (node->left == NULL) || (node->right == NULL) )
			{
				Node<T>* temp = node->left ? node->left :node->right;
				if (temp == NULL)
				{
					temp = node;
					node = NULL;
				}
				else 
				{

					node->key = temp->key;
					node->right=temp->right;
					node->left=temp->left;
					node->parent=temp->parent;
				}
				delete temp;
			}
			else
			{
				Node<T>* temp = node->right;
				while (temp->left != NULL)
				{
					Node<T>* t=temp->left;
					temp = t;
					if(t!=NULL)
						t->parent=temp;
				}
				node->key = temp->key;
				Node<T>* t=deleteNodefn(node->right, node->key);
				node->right = t;
				if(t!=NULL)
						t->parent=node->right;
			}
		}
		else
		{
			return root;
		}
		if (node == NULL)
			return node;
		node=balance(node);
		return node;
	}
	Node<T>* _find(Node<T>* node,T key)
	{
		if((node==nullptr)||(node->key==key))
		{
			return node;
		}
		else if(key<node->key)
		{
			node=node->left;
			node=_find(node,key);	
		}
		else if(key>=node->key)
		{
			node=node->right;
			node=_find(node,key);
		}
		return node;

	}

	Node<T>* find(T key)
	{
		return _find(root,key);
	}

	
	Node<T>* leftmost()
	{
		Node<T>* node=root;
		if (node!=NULL)
		{
			for(;node;node=node->left)
			{

				if(!node->left)
					break;
			}
			//cout<<node->key;
			return node;
		}
		return NULL;
	}
	 Node<T>* rightmost()
	{
		Node<T>* node=root;
		if (node!=NULL)
		{
			for(;node;node=node->right)
			{

				if(!node->right)
					break;
			}
			//cout<<node->key;
			return node;
		}
		return NULL;
	}
	
	class Iterator : public std::iterator<std::input_iterator_tag,
							T,
							ptrdiff_t,
							T*,
							T&>
	{
	
		
		public:
		
		Node<T>* current;
		Node<T>* begin;
		Node<T>* end;
		stack<Node<T>*> innernodes;
		Iterator(Node<T>* p_it) : current(p_it) 
		{	
			
		}
		Iterator(Node<T>* p_it,Node<T>* begin,Node<T>* end) 
		: current(p_it), begin(begin), end(end)
		{	
			
		}
		T operator*() const
		{
			return current->key;
		}
		bool operator==(const Iterator& rhs) const
		{
			return current == rhs.current;
		}
		bool operator!=(const Iterator& rhs) const
		{
		//	return current != rhs.current;
			return !(*this	== rhs);
		}
		Iterator& operator++() // pre
		{
			if(current==end)
				current=NULL;
			else
			{
				if((current->right)!=NULL)
				{
					innernodes.push(current);
					current=current->right;
					while((current->left)!=NULL)
					{
						current=current->left;
					}
				}
				else
				{
					if(innernodes.empty() )
					{
						current=current->parent;
					}
					else
					{	
						if(innernodes.top()!=current->parent)
						{

							current=current->parent;
						}
						else
						{
							
							Node<T>* p=current->parent;
							while(innernodes.empty()==false && innernodes.top()==p)
							{
								
								p=p->parent;
								innernodes.pop();
								
								
								
							}
							current=p;
						}
					}
				}
			}
			return *this;
		}
		Iterator  operator++(int) // post
		{
			Iterator temp(*this);
			++*this;
			return temp;
		}
	};
	
		
	Iterator begin()
	{
		return Iterator(leftmost(),leftmost(),rightmost());
	}
	Iterator end()
	{
		
		return Iterator(NULL,leftmost(),rightmost());
	}
	Node<T>* common_ancestor(T key1,T key2)
	{	
		if(!comp(key1,key2))
		{
			T temp=key1;
			key1=key2;
			key2=temp;
		}
		
		return common_ancestorfn2(root,key1,key2);
	}
	Node<T>* common_ancestorfn(Node<T>* node,T key1,T key2)
	{
		
		Node<T>* left=nullptr;
		Node<T>* right=nullptr;
		if(node->left != NULL)
		{
			left=_find(node->left,key1);
			
		}
		if(node->right != NULL)
		{
			right=_find(node->right,key2);
			
		}
		if(left!=nullptr && right!=nullptr)
		{
			return node;
		}
		else if(left!=nullptr)
		{
			return common_ancestorfn(node->left,key1,key2);
		}
		else
		{
			return common_ancestorfn(node->right,key1,key2);
		}
	}
	Node<T>* common_ancestorfn2(Node<T>* node,T key1,T key2)
	{
		
		if(node==NULL)
			return NULL;
		if(node->key==key1 || node->key==key2 )
			return node;
		Node<T>* left=common_ancestorfn2(node->left,key1,key2);
		Node<T>* right=common_ancestorfn2(node->right,key1,key2);
		if(left!=NULL && right!=NULL)
		{
			return node;
		}
		else if(left!=NULL)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
};














