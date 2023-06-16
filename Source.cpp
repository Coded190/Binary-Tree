//Program builds a Binary Tree using Preorder string

#include <iostream>
#include <string>
using namespace std;

struct BinaryTree
{
	char key;
	BinaryTree* left;
	BinaryTree* right;
};
typedef BinaryTree* BTptr;
BTptr root;



//Function Prototypes
string validInput(string);
BTptr buildTree(string);
void insertBSTNode(BTptr&, char);
void insertBTNode(BTptr&, char);
void preorder(BTptr);
void inorder(BTptr);
void postorder(BTptr);
void levelorder(BTptr);
void currentLevel(BTptr, int);
bool isBST(BTptr);
int node_count(BTptr);
int height(BTptr);
bool isFullBT(BTptr);
bool isFull(BTptr);
bool isCompleteBT(BTptr, int, int);
int max(int, int);
void insertPreorder(BTptr&, string, int&);

int main()
{
	//string str = "AB.C.DE.F....";	//Invalid input -> "AB.C.DE.F..." needs 1 extra dot than chars!!!
	string str;
	cout << "Please Enter Preorder String: ";
	cin >> str;
	str = validInput(str);
	root = buildTree(str);
	int index = 0;
	int nodeCount = node_count(root);

	if (isBST(root))
		cout << "isBST true.\n";
	else
		cout << "isBST false.\n";

	cout << "Node Count: " << node_count(root) << endl;
	cout << "Height: " << height(root) << endl;
	
	if (isFullBT(root))
		cout << "isFullBT true.\n";
	else
		cout << "isFullBT false.\n";

	if (isCompleteBT(root, index, nodeCount))
		cout << "isCompleteBT true.\n";
	else
		cout << "isCompleteBT false.\n";

	cout << "Preorder: ";
	preorder(root);
	cout << endl;

	cout << "Inorder: ";
	inorder(root);
	cout << endl;

	cout << "Postorder: ";
	postorder(root);
	cout << endl;

	cout << "Level-order: ";
	levelorder(root);
	cout << endl;


	return 0;
}

void insertPreorder(BTptr& T, string str, int& i)
{
	if (str[i] == '.')
	{
		i++;
		return;
	}
	else if (T == nullptr)
	{
		T = new BinaryTree;
		T->key = str[i];
		T->left = T->right = nullptr;
		i++;
	}
	insertPreorder(T->left, str, i);
	insertPreorder(T->right, str, i);
}


//-------------------------------------------------------------
// Inserts a node into BT
// 
// @param - BTptr&, char
// @return - void
//-------------------------------------------------------------

void insertBTNode(BTptr& temp, char ch)	
{
	if (temp == nullptr)
	{
		temp = new BinaryTree;
		temp->key = ch;
		temp->left = temp->right = nullptr;
	}
	else
	{
		if (temp->left == nullptr)
		{
			insertBTNode(temp->left, ch);

		}
		else if (temp->right == nullptr)
		{
			insertBTNode(temp->right, ch);

		}
		else
			if (node_count(temp->left) <= node_count(temp->right))
				insertBTNode(temp->left, ch);
			else
				insertBTNode(temp->right, ch);
	}
}


//-------------------------------------------------------------
// Builds a Binary Tree from the given preorder string
// 
// @param - string
// @return - BTptr
//-------------------------------------------------------------

BTptr buildTree(string str)
{
	int i = 0;
	insertPreorder(root, str, i);
	return root;
}


//-------------------------------------------------------------
// Checks for a Full BT
// 
// @param - BTptr
// @return - bool
//-------------------------------------------------------------

bool isFullBT(BTptr T)	
{
	if (T == nullptr)
		return true;
	else
		return (isFull(T->left) && isFull(T->right) && (height(T->left) == height(T->right)));
}


//-------------------------------------------------------------
// Checks for a Full BT
// 
// @param - BTptr
// @return - bool
//-------------------------------------------------------------

bool isFull(BTptr T)
{
	if (T == nullptr)
		return true;
	else if (T->left == nullptr && T->right == nullptr)
		return true;
	else if (T->left != nullptr && T->right != nullptr)
	{
		if (height(T->left) == height(T->right))
			return true;
	}
	else
		return false;
}


//-------------------------------------------------------------
// Determines if a BST
// 
// @param - BTptr
// @return - bool
//-------------------------------------------------------------

bool isBST(BTptr T)	
{
	if (T == nullptr)
		return true;
	else if (T->left != nullptr && T->right != nullptr)
	{
		if ((T->left->key < T->key) && (T->right->key > T->key))
			return (isBST(T->left) && isBST(T->right));
		else
			return false;
	}
	else if (T->left != nullptr)
	{
		if (T->left->key < T->key)
			return isBST(T->left);
		else
			return false;
	}
	else if (T->right != nullptr)
	{
		if (T->right->key > T->key)
			return isBST(T->right);
		else
			return false;
	}
	else
		return true;
}


//-------------------------------------------------------------
// Checks for a complete BT
// 
// @param - BTptr, int, int
// @return - bool
//-------------------------------------------------------------

bool isCompleteBT(BTptr T, int index, int nodeCount)	
{
	if (T == nullptr)
		return true;
	if (index >= nodeCount)	//If i send in 1, I have to change this to > only
		return false;

	return (isCompleteBT(T->left, 2 * index + 1, nodeCount) && isCompleteBT(T->right, 2 * index + 2, nodeCount)); //change to index and index + 1
}


//-------------------------------------------------------------
// Returns the node count in a BT
// 
// @param - BTptr
// @return - int
//-------------------------------------------------------------

int node_count(BTptr T)	
{
	if (T == nullptr)
		return 0;
	else
		return (1 + node_count(T->left) + node_count(T->right));
}


//-------------------------------------------------------------
// Validates the preorder BT string given
// 
// @param - string
// @return - string
//-------------------------------------------------------------

string validInput(string str)	
{
	string tStr = str;
	for (int i = 0; i < str.length(); i++) 
	{
		if (str[i] == ' ')
		{
			continue;
		}
		else
		{
			tStr += str[i];
		}
	}

	str = tStr;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[0] == '.' && str.length() > 1)	
		{
			cout << "Please enter a valid Preorder representation of a Binary Tree: ";
			cin >> str;
			return validInput(str);
		}

		if (!isalnum(str[i]) && str[i] != '.')
		{
			cout << "Please enter a valid Preorder representation of a Binary Tree: ";
			cin >> str;
			return validInput(str);
		}
	}
	return str;
}


//-------------------------------------------------------------
// Returns the height of a BT
// 
// @param - BTptr
// @return - int
//-------------------------------------------------------------

int height(BTptr T)	
{
	if (T == nullptr)
		return 0;
	else
		return (max(height(T->left), height(T->right)) + 1);
}


//-------------------------------------------------------------
// Prints the preorder of a BT
// 
// @param - BTptr
// @return - void
//-------------------------------------------------------------

void preorder(BTptr T)
{
	if (T == nullptr)
		return;
	else
	{
		cout << T->key;
		preorder(T->left);
		preorder(T->right);
	}
}


//-------------------------------------------------------------
// Prints the inorder of a BT
// 
// @param - BTptr
// @return - void
//-------------------------------------------------------------

void inorder(BTptr T)
{
	if (T == nullptr)
		return;
	else
	{
		inorder(T->left);
		cout << T->key;
		inorder(T->right);
	}
}


//-------------------------------------------------------------
// Prints the postorder of a BT
// 
// @param - BTptr
// @return - void
//-------------------------------------------------------------

void postorder(BTptr T)
{
	if (T == nullptr)
		return;
	else
	{
		postorder(T->left);
		postorder(T->right);
		cout << T->key;
	}
}


//-------------------------------------------------------------
// Prints the levelorder of a BT
// 
// @param - BTptr
// @return - void
//-------------------------------------------------------------

void levelorder(BTptr T)
{
	int h = height(T);
	for (int i = 0; i <= h; i++)
		currentLevel(T, i);
}


//-------------------------------------------------------------
// Traverses the BT in level order to output values
// 
// @param - BTptr, int
// @return - void
//-------------------------------------------------------------

void currentLevel(BTptr T, int level)
{
	if (T == nullptr)
		return;
	if (level == 1)
		cout << T->key << " ";
	else if (level > 1)
	{
		currentLevel(T->left, level - 1);
		currentLevel(T->right, level - 1);
	}
}


//-------------------------------------------------------------
// Determines the max of 2 given integers
// 
// @param - int, int
// @return - int
//-------------------------------------------------------------

int max(int i, int j)
{
	return (i >= j ? i : j);
}


void insertBSTNode(BTptr& temp, char ch)	//didn't have to build:)
{
	if (temp == nullptr)
	{
		temp = new BinaryTree;
		temp->key = ch;
		temp->left = temp->right = nullptr;
	}
	else
	{
		if (temp->key > ch)
			insertBSTNode(temp->left, ch);
		if (temp->key < ch)
			insertBSTNode(temp->right, ch);
	}
}