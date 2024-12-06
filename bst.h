#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{   

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clearHelper(Node<Key, Value>* root);
    int depth(Node<Key, Value>*node) const;
    bool balancehelper(Node<Key,Value>* root) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    //If the user gives us somewhere specific to point we set
    //the current iterator pointer to that specific location
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    //If an iterator is declared without initialization
    //set to point nowhere NULL
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //If the pointers are the same then they are
    //pointing to the same thing thus will return true. Otherwise 
    //will return false
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //If the pointers are not the same then they are
    //pointing to different things thus will return true. Otherwise
    //will return false
    return current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    //Call the clear function to 
    //Make the tree back to its empty state
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //Check to see if the node already in the tree
    //If so just update the value of the node
    Node<Key, Value>* found = internalFind(keyValuePair.first);
    if(found != nullptr)
    {
        found->setValue(keyValuePair.second); //update value if already in tree
        return;
    }
    //This holds the dynamic node to get updated as we find where
    //it needs to be inserted
    Node<Key, Value>* newNode = new Node<Key,Value> (keyValuePair.first, keyValuePair.second, nullptr);
    if(root_ == nullptr)
    {
        root_ = newNode;
        return;
    }

    //This will hold a copy of the root so we can traverse
    Node<Key, Value>* current = root_;

    //This will be the node where we find to insert the new item 
    Node<Key, Value>* node = current;

    //While we can traverse
    while(current != nullptr)
    {
        //This will make sure we find the node before we 
        //get to the nullptr
        node = current;

        //If already in the tree
        if(keyValuePair.first == current->getKey())
        {
            found->setValue(keyValuePair.second); //update value if already in tree
            return;
        }
        //If the key is less that the current key go left
        else if(keyValuePair.first < current->getKey())
        {
            current = current->getLeft();
        }
        //If the key is greater than the current key go right
        else if(keyValuePair.first > current->getKey())
        {
            current = current->getRight();
        }
    }
    //If the key is less than the node go left
    if(keyValuePair.first < node->getKey())
    {
        node->setLeft(newNode);
    }
    //If the key is greater than the node go right
    else if (keyValuePair.first > node->getKey())
    {
        node->setRight(newNode);
    }

    //Make sure to update the parent
    newNode->setParent(node);
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    //variable to hold the node we found (if found)
    Node<Key,Value>* current = internalFind(key);

    //If the item is not in the tree yet 
    if(current == nullptr)
    {
        return;
    }

    //Case where the value has 0 children
    if(current->getRight() == nullptr && current->getLeft() == nullptr)
    {
        //If the item is the root
        if(current == root_ && current != nullptr)
        {
            delete current;
            root_ = nullptr;
            return;
        }
        else if(current->getParent()->getLeft() == current) //Left child
        {
            //If it is the left child, then set the parent's left child
            //to null and delete the node 
            current->getParent()->setLeft(nullptr);
            delete current;
            return;
        }
        else if(current->getParent()->getRight() == current) //right child
        {
            //If it is the right chiild, then set the parent's right child
            //to null and delete the node 
            current->getParent()->setRight(nullptr);
            delete current;
            return;
        } 
    }
    //If the node has one child and that child is the left node
    else if(current->getRight() == nullptr && current->getLeft() != nullptr)
    {
        //If current is the root
        if(current == root_ && current != nullptr)
        {
            //Promote the left child
            root_ = root_->getLeft();

            //Update the parent
            root_->setParent(nullptr);

            //Delete the node and return
            delete current;
            return;
        }
        else if(current->getParent()->getLeft() == current) //right child
        {
            //Make the left child of the current node the right child of the
            //current node's parent
            nodeSwap(current, current->getRight());

            //Delete the node and return
            delete current;
            return;
        }
    }
    //If the current node has one child and that child is the right node
    else if(current->getRight() != nullptr && current->getLeft() == nullptr)
    {
        if(current == root_ && current != nullptr)
        {
            //Promote the child
            root_ = root_->getRight();

            //Update the parent
            root_->setParent(nullptr);

            //Delete the current node and return
            delete current;
            return;
        }
        else if(current->getParent()->getRight() == current) //right child
        {
            //Make the right child of the current node the the child
            //of the current parent 
            nodeSwap(current, current->getLeft());
            //Delete the node and return
            delete current;
            return;
        }
        
    }
    //If the node has two children 
    else if(current->getRight() != nullptr && current->getLeft() != nullptr)
    {
        //Get the predecessor of the node we want and then we swap it 
        Node<Key, Value>* predecessorNode = predecessor(current);
        nodeSwap(current, predecessorNode);

        //If the left child of the current node is valid
        if (current->getLeft() != nullptr)
        {
            //If this is the right child then update pointers
            if (current->getParent()->getRight() == current)
            {
                current->getParent()->setRight(current->getLeft());
                current->getLeft()->setParent(current->getParent());

                //Delete the node and return
                delete current;
                return;
            }
            //If this is the left child then update pointers
            else if(current->getParent()->getLeft() == current)
            {
                current->getParent()->setLeft(current->getLeft());
                current->getLeft()->setParent(current->getParent());

                //Delete the node and return
                delete current;
                return;
            }
        }
        //If the right child of the current node is valid
        else if (current->getRight() != nullptr)
        {
            //If this is the right child then update the pointers
            if (current->getParent()->getRight() == current)
            {
                current->getParent()->setRight(current->getRight());
                current->getRight()->setParent(current->getParent());

                //Delete the node and return
                delete current;
                return;
            }
            //If this is the left child then update the pointers
            else if(current->getParent()->getLeft() == current)
            {
                current->getParent()->setLeft(current->getRight());
                current->getRight()->setParent(current->getParent());

                //Delete the node and return
                delete current;
                return;
            }
        }
        //If both children are invalid 
        else if(current->getRight() == nullptr && current->getLeft() == nullptr)
        {
            if (current->getParent()->getRight() == current)
            {
                current->getParent()->setRight(nullptr);
            }
            if (current->getParent()->getLeft() == current)
            {
                current->getParent()->setLeft(nullptr);
            }

            //Delete the node and return
            delete current;
            return;
        }
    }
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    //Node to hold a copy of the current node
    Node<Key, Value>* node = current;

    //If the node is invalid return null
    if(node == nullptr)
    {
        return nullptr;
    }
    //If the left child exists
    if(node->getLeft() != nullptr)
    {
        //Move to the left child
        node = node->getLeft();

        //While we can traverse right keep 
        //going right
        while(node->getRight() != NULL)
        {
            node = node->getRight();
        }
    }
    //If the left node is invalid then we need
    //to go up the ancestry tree
    else if(node->getLeft() == nullptr)
    {
        //While we can traverse
        while( node != nullptr )
        {
            //Get the parrent and check
            //to see if the parent is invalid
            node = node->getParent();
            if(node == nullptr)
            {
                return nullptr;
            }
            //once we find the first node that is the right child of
            //the parent aabove us that is who we need
            else if(node->getParent()->getRight() == node)
            {
                node = node->getParent();
            }
        }
    }
    
    //get the node where it is the predecessor
    return node;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    //Node to hold a copy of the current node
    Node<Key, Value>* node = current;

    //If the node is invalid return null
    if(node == nullptr)
    {
        return nullptr;
    }
    //If the right child exists
    if(node->getRight() != nullptr)
    {
        //Move to the right child
        node = node->getRight();

        //While we can traverse left keep 
        //going left
        while(node->getLeft() != NULL)
        {
            node = node->getLeft();
        }
    }
    //If the right node is invalid then we need
    //to go up the ancestry tree
    else if(node->getRight() == nullptr)
    {
        //While we can traverse
        while( node != nullptr )
        {
            //Get the parrent and check
            //to see if the parent is invalid
            node = node->getParent();
            if(node == nullptr)
            {
                return nullptr;
            }
            //once we find the first node that is the left child of
            //the parent aabove us that is who we need
            else if(node->getLeft() == node)
            {
                node = node->getParent();
            }
        }
    }
    
    //get the node where it is the predecessor
    return node;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    //Calling a helper function 
    if(root_ == nullptr)
    {
        return;
    }
    clearHelper(root_);
    root_ = nullptr;
}

//Helper function to recursively delete all the nodes and
//return the tree back to the empty state
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* node)
{
    //If the node is equal to NULL then we have deleted all the nodes
    //including the root so just return
    if(node == NULL)
    {
        return;
    }
    //Recurse into all the left children 
    clearHelper(node->getLeft());

    //Recurse into all the right children
    clearHelper(node->getRight());

    //Remove current node we are in from the tree
    delete node;

}
/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    //NOTE::The smallest node will ALWAYS be the left most
    //Node of the tree

    //Make a copy of the root to use as the pointer
    //to the current node we are on
    Node<Key, Value>* current = root_;

    //While we can iterate to the left traverse downward
    //until we hit the nullptr indicating we are at the 
    //smallest node of the tree
    while(current->getLeft() != nullptr)
    {
        //Traverse downward to the left
        current = current->getLeft();
    }

    //Return the smallest node in the given tree
    return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO

    //A copy to hold the root of the tree
    Node<Key, Value>* current = root_;
    while(current != nullptr)
    {
        //If the key is less than the parent key
        //Go to the left child
        if(key < current->getKey())
        {
            current = current->getLeft();
        }
        //If the key is greater than the parent key
        //GO to the right child
        else if(key > current->getKey())
        {
            current = current->getRight();
        }
        //If the key is equal to the parent key
        //We have found the node so just return it 
        else if(key == current->getKey())
        {
            return current;
        }
    }

    //If no NODE was found from the given key, the node does
    //not exist so just return NULL
    return nullptr;
}

/**
 * Return true if the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return balancehelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balancehelper(Node<Key,Value>* root ) const
{
    //If the tree is empty then it is balanced
    if(root == NULL)
    {
        return true;
    }

    //Get the inter heights of the right and 
    //left sides of all trees 
    int leftH = depth(root->getLeft());
    int rightH = depth(root->getRight());

    //If the height is 1 or 0 then the tree is balanced
    if(abs(leftH- rightH) == 1 || leftH - rightH == 0)
    {
        //Balanced so return true
        if(balancehelper(root->getLeft()) == true && balancehelper(root->getRight()) == true)
        {
            return true;
        }
    }

    //Not balanced so return false
    return false;
}
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::depth(Node<Key,Value>* node) const
{
    //Value to tell the heigh to of
    //the trees
    int value = 0;

    //Base case to break the recursion 
    if (node == NULL)
    {
        return 0;
    }
    //If the left tree is greater than right tree
    if(depth(node->getLeft()) >  depth(node->getRight()))
    {
        value = depth(node->getLeft());
    }
    //If the right tree is greater than the left tree
    else if(depth(node->getLeft()) < depth(node->getRight()))
    {
        value = depth(node->getRight());
    }

    //Increment the value of the tree we are
    //checking and return it to the recursive call
    value++;
    return value;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
