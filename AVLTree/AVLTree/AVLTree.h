#ifndef __AVLTREE__
#define __AVLTREE__
#include <iostream>
#include <deque>
#include <windows.h>

void gotoxy(int x, int y);
COORD getxy();



template<typename T>
class AVLTree
{

public:
	struct NODE
	{
		T data;
		NODE* left;
		NODE* right;
		int lH;
		int rH;
		NODE() : data(), left(NULL), right(NULL), lH(0), rH(0) {};
		NODE(T x, NODE* l, NODE* r, int lh, int rh) : data(x), left(l), right(r), lH(0), rH(0) {};
	};

private:
	NODE* root;
	bool insert(T x, NODE*& node);
	void AVLCheck(NODE** node);
	bool remove(T x, NODE** node);
	T removeMax(NODE** node);
	void LLRotate(NODE** node);
	void RRRotate(NODE** node);
	void printInOrder(NODE* node);
	void printpretty(NODE* node, COORD coor, int absY);

public:
	AVLTree() : root(NULL) {};
	bool insert(T x);
	bool remove(T x);
	void print();
	void printTree();

	T* find(T x);
};

template<typename T>
bool AVLTree<T>::insert(T x)
{
	return insert(x, root);
}

template<typename T>
bool AVLTree<T>::remove(T x)
{
	return remove(x, &root);
}

template<typename T>
bool AVLTree<T>::remove(T x, NODE** node)
{
	NODE* temp;
	T tData;
	if (*node == NULL)
		return false;
	else if (x < (*node)->data)
		remove(x, &(*node)->left);
	else if (x > (*node)->data)
		remove(x, &(*node)->right);
	else
	{
		if ((*node)->right == NULL || (*node)->left == NULL)
		{
			if ((*node)->right != NULL)
			{
				temp = (*node)->right;
				delete *node;
				*node = temp;
			}
			else if ((*node)->left != NULL)
			{
				temp = (*node)->left;
				delete *node;
				*node = temp;
			}
			else
			{
				delete* node;
				*node = NULL;
				return true;
			}
		}
		else
		{
			(*node)->data = removeMax(&(*node)->left);
		}
	}

	if ((*node)->right != NULL)
		(*node)->rH = (*node)->right->lH > (*node)->right->rH ? (*node)->right->lH + 1 : (*node)->right->rH + 1;
	else
		(*node)->rH = 0;

	if ((*node)->left != NULL)
		(*node)->lH = (*node)->left->lH > (*node)->left->rH ? (*node)->left->lH + 1 : (*node)->left->rH + 1;
	else
		(*node)->lH = 0;

	AVLCheck(node);

	return true;
}

template<typename T>
T AVLTree<T>::removeMax(NODE** node)
{
	NODE* temp;
	T res;
	if ((*node)->right == NULL)
	{
		res = (*node)->data;
		temp = (*node)->left;
		delete *node;
		*node = temp;
		return res;
	}
	else
		res = removeMax(&(*node)->right);

	if ((*node)->right != NULL)
		(*node)->rH = (*node)->right->lH > (*node)->right->rH ? (*node)->right->lH + 1 : (*node)->right->rH + 1;
	else
		(*node)->rH = 0;

	if ((*node)->left != NULL)
		(*node)->lH = (*node)->left->lH > (*node)->left->rH ? (*node)->left->lH + 1 : (*node)->left->rH + 1;
	else
		(*node)->lH = 0;

	AVLCheck(node);

	return res;
}

template<typename T>
T* AVLTree<T>::find(T x)
{
	NODE* temp = root;
	while (temp != NULL)
	{
		if (x < temp->data)
			temp = temp->left;
		else if (x > temp->data)
			temp = temp->right;
		else
			break;
	}
	
	if (temp != NULL)
		return &temp->data;
	return NULL;
}


template<typename T>
bool AVLTree<T>::insert(T x, NODE*& node)
{
	NODE ** line = NULL;
	int* h = NULL;
	if (root == NULL)
	{
		root = new NODE(x, NULL, NULL, 0, 0);
		return true;
	}
	if (x > node->data)
	{
		line = &node->right;
		h = &node->rH;
	}
	else if (x < node->data)
	{
		line = &node->left;
		h = &node->lH;
	}
	else
		return false;
	
	if (*line == NULL)
	{
		*line = new NODE(x, NULL, NULL, 0, 0);
		*h = 1;
	}
	else
	{
		insert(x, *line);
		*h = (*line)->lH > (*line)->rH ? (*line)->lH + 1 : (*line)->rH + 1;
		AVLCheck(&node);
	}

	return true;
}

template<typename T>
void AVLTree<T>::AVLCheck(NODE** node)
{
	if ((*node)->rH - (*node)->lH > 1)
	{
		if ((*node)->right->rH > (*node)->right->lH)
			RRRotate(node);
		else
		{
			LLRotate(&(*node)->right);
			RRRotate(node);
		}
	}
	else if ((*node)->rH - (*node)->lH < -1)
	{
		if ((*node)->left->rH > (*node)->left->lH)
		{
			RRRotate(&(*node)->left);
			LLRotate(node);
		}
		else
			LLRotate(node);
	}
}

template<typename T>
void AVLTree<T>::LLRotate(NODE** node)
{
	NODE* L = (*node)->left;
	NODE* temp;
	(*node)->left = (*node)->left->right;
	if ((*node)->left != NULL)
		(*node)->lH = (*node)->left->lH > (*node)->left->rH ? (*node)->left->lH + 1 : (*node)->left->rH + 1;
	else
		(*node)->lH = 0;
	temp = *node;
	*node = L;
	(*node)->right = temp;
	if ((*node)->right != NULL)
		(*node)->rH = (*node)->right->lH > (*node)->right->rH ? (*node)->right->lH + 1 : (*node)->right->rH + 1;
	else
		(*node)->rH = 0;
}

template<typename T>
void AVLTree<T>::RRRotate(NODE** node)
{
	NODE* R = (*node)->right;
	NODE* temp;
	(*node)->right = (*node)->right->left;
	if ((*node)->right != NULL)
		(*node)->rH = (*node)->right->lH > (*node)->right->rH ? (*node)->right->lH + 1 : (*node)->right->rH + 1;
	else
		(*node)->rH = 0;
	temp = *node;
	*node = R;
	(*node)->left = temp;
	if((*node)->left != NULL)
		(*node)->lH = (*node)->left->lH > (*node)->left->rH ? (*node)->left->lH + 1 : (*node)->left->rH + 1;
	else
		(*node)->lH = 0;
}


template<typename T>
void AVLTree<T>::print()
{
	printInOrder(root);
}

template<typename T>
void AVLTree<T>::printInOrder(NODE* node)
{
	if (node == NULL)
		return;
	printInOrder(node->left);
	std::cout << node->data << ' ';
	printInOrder(node->right);
}

template<typename T>
void AVLTree<T>::printTree()
{
	int width = 1;
	int height = root->rH > root->lH ? root->rH : root->lH;
	COORD coord = getxy();

	NODE* temp = root;
	while (temp != NULL)
	{
		temp = temp->left;
		width++;
	}

	temp = root;
	while (temp != NULL)
	{
		temp = temp->right;
		width++;
	}

	coord.X = (width / 2 + 1) * 5;
	coord.Y = coord.Y + 1;
	printpretty(root, coord, coord.Y);
}

template<typename T>
void AVLTree<T>::printpretty(NODE* node, COORD coord, int absY)
{
	if (node == NULL)
		return;
	int span =  absY - coord.Y;
	gotoxy(coord.X, coord.Y);
	std::cout << node->data;


	COORD newCoord1 = { coord.X - (10 + span), coord.Y + 2 };
	COORD newCoord2 = { coord.X + (10 + span), coord.Y + 2 };

	printpretty(node->left, newCoord1, absY);
	printpretty(node->right, newCoord2, absY);
}

#endif