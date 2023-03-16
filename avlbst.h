#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getBalance () const;
    void setBalance (int balance); //int8_t
    void updateBalance(int diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		virtual void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* c);
		virtual void rotateRight(AVLNode<Key,Value>* node);
		virtual void rotateLeft(AVLNode<Key,Value>* node);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
		if (BinarySearchTree<Key, Value>::root_ == NULL) //if empty tree...
		{
			//set n as root, b(n) = 0, done!
			BinarySearchTree<Key, Value>::root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
			return;
		}
		
		//now, let's search for the insertion position
		AVLNode<Key, Value>* new_node = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
		AVLNode<Key, Value>* cur = static_cast<AVLNode<Key, Value>*> (this->getRoot());
		while (cur)
		{
			if (new_item.first < cur->getKey())
			{
				if (cur->getLeft()  == NULL) //there is an open leaf position
				{
					cur->setLeft(new_node);
					new_node->setParent(cur);
					cur->updateBalance(-1);

					if (cur->getBalance() == -1) { insertFix(cur, new_node); }
					return;
				}
				else cur = cur->getLeft(); //compare with node in place
			}
			else if (new_item.first > cur->getKey())
			{
				if (cur->getRight() == NULL) //there is an open leaf position
				{
					cur->setRight(new_node);
					new_node->setParent(cur);
					cur->updateBalance(1);
					if (cur->getBalance() == 1) { insertFix(cur, new_node); }
					return;
				}
				else cur = cur->getRight(); //compare with node in place
			}
			else //duplicate key found -- replace with updated value
			{ 
				cur->setValue( new_item.second );
				return;
			}
		}

}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* c)
{
	if (p == NULL || p->getParent() == NULL) return;
	AVLNode<Key, Value>* gp = p->getParent();
	if (p == gp->getLeft()) //parent is left child of grandparent
	{
		gp->updateBalance(-1);
		if (gp->getBalance() == 0) return;
		else if (gp->getBalance() == -1) insertFix(gp, p);
		else if (gp->getBalance() == -2)
		{
			//Zig-zig pattern
			if ((p == gp->getLeft() && c == p->getLeft()) || (p == gp->getRight() && c == p->getRight()))
			{
				rotateRight(gp);
				gp->setBalance(0);
				p->setBalance(0);
				return;
			}
			else //Zig-zag pattern
			{
				rotateLeft(p); rotateRight(gp);
				if (c->getBalance() == -1)
				{
					p->setBalance(0); gp->setBalance(1); c->setBalance(0);
				}
				else if (c->getBalance() == 0)
				{
					p->setBalance(0); gp->setBalance(0); c->setBalance(0);
				}
				else if (c->getBalance() == 1)
				{
					p->setBalance(-1); gp->setBalance(0); c->setBalance(0);
				}
				else std::cout << "Should never reach here (zigzag) " << std::endl;
				return;
			}
		}
		else { std::cout << "Should never reach this case (Left)" << std::endl; }

	}
	else //parent is right child of gradparent
	{
		gp->updateBalance(1);
		if (gp->getBalance() == 0) return;
		else if (gp->getBalance() == 1) { insertFix(gp, p); }
		else if (gp->getBalance() == 2)
		{
			//Zig-zig pattern
			if ((p == gp->getLeft() && c == p->getLeft()) || (p == gp->getRight() && c == p->getRight()))
			{
				rotateLeft(gp);
				gp->setBalance(0);
				p->setBalance(0);
				return;
			}
			else //Zig-zag pattern
			{
				rotateRight(p); rotateLeft(gp); //we ahve an issue with rotate right
				this->printTree();
				if (c->getBalance() == -1)
				{
					p->setBalance(1); gp->setBalance(0); c->setBalance(0);
				}
				else if (c->getBalance() == 0)
				{
					p->setBalance(0); gp->setBalance(0); c->setBalance(0);
				}
				else if (c->getBalance() == 1)
				{
					p->setBalance(0); gp->setBalance(-1); c->setBalance(0);
				}
				else { std::cout << "Should never reach this case (zigzag2)" << std::endl; }
				return;
			}
		}
		else { std::cout << "Should never reach this case (Right)" << std::endl; }

	}
	return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
	if (node == NULL) return;

	if (node->getLeft() == NULL) 
	{
		std::cout << "special issue, left node null" << std::endl;
		return;
	}

	bool node_left = false;

	AVLNode<Key, Value>* y = node;
	AVLNode<Key, Value>* p = y->getParent();
	AVLNode<Key, Value>* x = y->getLeft(); //hopefully not null
	AVLNode<Key, Value>* b = x->getRight(); //possibly null

	if (p && node == node->getParent()->getLeft()) node_left = true;

	y->setLeft(b); 
	if (b) b->setParent(y);
	y->setParent(x); x->setRight(y);
	x->setParent(p);
	if (p)
	{
		if (node_left) p->setLeft(x);
		else p->setRight(x);
	}
	else
	{
		this->setRoot(x);
	}


}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node)
{
	if (node == NULL) return;

	if (node->getRight() == NULL) 
	{
		std::cout << "special issue, right node null" << std::endl;
		return;
	}

	bool node_left = false;

	AVLNode<Key, Value>* x = node;
	AVLNode<Key, Value>* p = x->getParent();
	AVLNode<Key, Value>* y = x->getRight(); //hopefully not null
	AVLNode<Key, Value>* b = y->getLeft(); //possibly null

	if (p && node == node->getParent()->getLeft()) node_left = true;

	x->setRight(b); 
	if (b) b->setParent(x);
	y->setLeft(x); x->setParent(y);
	y->setParent(p);
	if (p)
	{
		if (node_left) p->setLeft(y);
		else p->setRight(y);
	}
	else
	{
		this->setRoot(y);
	}



}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
