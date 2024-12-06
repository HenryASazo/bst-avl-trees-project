#ifndef RBBST_H
#define RBBST_H

#include "bst.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError {};

/**
 * A special kind of node for an AVL tree, which adds the balance as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance() const;
    void setBalance(char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    signed char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
        : Node<Key, Value>(key, value, parent), balance_(0) {}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode() {}

/**
 * A getter for the balance of a AVLNode.
 */
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const {
    return balance_;
}

/**
 * A setter for the balance of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance) {
    balance_ = balance;
}

/**
 * Adds diff to the balance of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff) {
    balance_ += diff;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
    virtual void insert(const std::pair<const Key, Value>& new_item);  // TODO
    virtual void remove(const Key& key);                               // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here
    void insert_fix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void remove_fix(AVLNode<Key, Value>* n, char diff);
    void rotateRight(AVLNode<Key, Value>* pivot);
    void rotateLeft(AVLNode<Key, Value>* pivot);
};

/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item) {
    // TODO
    // Check to see if the node already in the tree
    // If so just update the value of the node
    Node<Key, Value>* found = this->internalFind(new_item.first);
    if (found != nullptr) {
        found->setValue(new_item.second);  // update value if already in tree
        return;
    }
    // This holds the dynamic node to get updated as we find where
    // it needs to be inserted
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    if (this->root_ == nullptr) {
        this->root_ = newNode;
        return;
    }

    // This will hold a copy of the root so we can traverse
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);

    // This will be the node where we find to insert the new item
    AVLNode<Key, Value>* node = current;

    // While we can traverse
    while (current != nullptr) {
        // This will make sure we find the node before we
        // get to the nullptr
        node = current;

        // If the key is less that the current key go left
        if (new_item.first < current->getKey()) {
            current = current->getLeft();
        }
        // If the key is greater than the current key go right
        else if (new_item.first > current->getKey()) {
            current = current->getRight();
        }
    }
    // If the key is less than the node go left
    if (new_item.first < node->getKey()) {
        // insert into the left child of the parent
        node->setLeft(newNode);

        // Make sure to update the parent
        newNode->setParent(node);

        // Checking the balance of the parent
        if (node->getBalance() == -1) {
            node->setBalance(0);
            return;
        }

        if (node->getBalance() == 1) {
            node->setBalance(0);
            return;
        }

        if (node->getBalance() == 0) {
            node->updateBalance((signed char)-1);
            return this->insert_fix(node, newNode);
        }
    }
    // If the key is greater than the node go right
    else if (new_item.first > node->getKey()) {
        // Insert into the right child of the parent
        node->setRight(newNode);

        // Make sure to update the parent
        newNode->setParent(node);

        // Checking the balance of the parent
        if (node->getBalance() == -1) {
            node->setBalance(0);
            return;
        }

        if (node->getBalance() == 1) {
            node->setBalance(0);
            return;
        }

        if (node->getBalance() == 0) {
            node->updateBalance(1);
            return this->insert_fix(node, newNode);
        }
    }
}

// Function for inserting
template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) {
    // If the current node or the current node is null just terminate the
    // function
    if (p == nullptr || p->getParent() == nullptr) {
        return;
    }

    // Value to hold the g (grandparent) of n (inserted node)
    AVLNode<Key, Value>* g = p->getParent();

    // Checking if p is the left child of g
    if (p == g->getLeft()) {
        // Update the balance of grandparent
        g->updateBalance(-1);

        // Case 1
        if (g->getBalance() == 0) {
            return;
        }

        // Case 2
        if (g->getBalance() == -1) {
            insert_fix(g, p);
            return;
        }

        // Case 3
        if (g->getBalance() == -2) {
            // zig zig
            if (n == p->getLeft()) {
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            } else
            // zig zag
            {
                rotateLeft(p);
                rotateRight(g);
                if (n->getBalance() == -1) {
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                } else if (n->getBalance() == 0) {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                } else if (n->getBalance() == 1) {
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }

    }
    // Checking if p is the right child of g
    else if (p == g->getRight()) {
        // Update the balance of grandparent
        g->updateBalance(1);

        // Case 1
        if (g->getBalance() == 0) {
            return;
        }

        // Case 2
        if (g->getBalance() == 1) {
            insert_fix(g, p);
            return;
        }

        // Case 3
        if (g->getBalance() == 2) {
            // zig zig
            if (n == p->getRight()) {
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            // zig zag
            else {
                rotateRight(p);
                rotateLeft(g);
                if (n->getBalance() == 1) {
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                } else if (n->getBalance() == 0) {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                } else if (n->getBalance() == -1) {
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key, Value>* n, char diff) {
    // If the node is empty return
    signed char ndiff = 0;
    if (n == nullptr) {
        return;
    }

    AVLNode<Key, Value>* parent = n->getParent();

    if (parent != nullptr) {
        if (this->isLeft(parent, n)) {
            ndiff = 1;
        } else {
            ndiff = -1;
        }
    }
    if (diff == -1) {
        if (n->getBalance() + diff == -2) {
            AVLNode<Key, Value>* c = n->getLeft();
            if (c->getBalance() == -1) {
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                return this->remove_fix(parent, ndiff);
            } else if (c->getBalance() == 0) {
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
                return;
            } else if (c->getBalance() == 1) {
                AVLNode<Key, Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if (g->getBalance() == 1) {
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                } else if (g->getBalance() == 0) {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                } else if (g->getBalance() == -1) {
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                return remove_fix(parent, ndiff);
            }
        } else if (n->getBalance() + diff == -1) {
            n->setBalance(-1);
            return;
        } else if (n->getBalance() + diff == 0) {
            n->setBalance(0);
            return remove_fix(parent, ndiff);
        }
    } else if (diff == 1) {
        if (n->getBalance() + diff == 2) {
            AVLNode<Key, Value>* c = n->getRight();
            if (c->getBalance() == 1) {
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                return remove_fix(parent, ndiff);
            } else if (c->getBalance() == 0) {
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
                return;
            } else if (c->getBalance() == -1) {
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                if (g->getBalance() == -1) {
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                } else if (g->getBalance() == 0) {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                } else if (g->getBalance() == -1) {
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                return remove_fix(parent, ndiff);
            }
        } else if (n->getBalance() + diff == 1) {
            n->setBalance(1);
            return;
        } else if (n->getBalance() + diff == 0) {
            n->setBalance(0);
            return remove_fix(parent, ndiff);
        }
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* p) {
    // variable to hold the left child of parent
    AVLNode<Key, Value>* leftChild = p->getLeft();

    // Update the left child
    Node<Key, Value>* p_parent = p->getParent();
    leftChild->setParent(p_parent);

    // Update the parent
    Node<Key, Value>* l_right = leftChild->getRight();
    p->setLeft(l_right);

    // If the left child of the parent is invalid
    Node<Key, Value>* l_parent = p->getLeft();
    if (l_parent != nullptr) {
        l_parent->setParent(p);
    }

    // Update the right child of the left child
    leftChild->setRight(p);
    p->setParent(leftChild);

    // Update the parent of the new parent node
    if (leftChild->getParent() == nullptr) {
        this->root_ = leftChild;
    } else if (leftChild->getParent() != nullptr && leftChild->getParent()->getLeft() == p) {
        leftChild->getParent()->setLeft(leftChild);
    } else if (leftChild->getParent() != nullptr && leftChild->getParent()->getRight() == p) {
        leftChild->getParent()->setRight(leftChild);
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* p) {
    // Variable to hold the right child of the parent
    AVLNode<Key, Value>* rightChild = p->getRight();

    // Update the right child
    Node<Key, Value>* p_parent = p->getParent();
    rightChild->setParent(p_parent);

    // Update the parent
    Node<Key, Value>* r_left = rightChild->getLeft();
    p->setRight(r_left);

    // If the right child is invalid
    Node<Key, Value>* r_parent = p->getRight();
    if (r_parent != nullptr) {
        r_parent->setParent(p);
    }

    // Update the left child of the right child
    rightChild->setLeft(p);
    p->setParent(rightChild);

    // Update the parent of the new parent node
    if (rightChild->getParent() != nullptr && rightChild->getParent()->getLeft() == p) {
        rightChild->getParent()->setLeft(rightChild);
    } else if (rightChild->getParent() != nullptr && rightChild->getParent()->getRight() == p) {
        rightChild->getParent()->setRight(rightChild);
    } else if (rightChild->getParent() == nullptr) {
        this->root_ = rightChild;
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key) {
    // TODO
    // variable to hold the node we found (if found)
    Node<Key, Value>* found = BinarySearchTree<Key, Value>::internalFind(key);

    // Making it into avl
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(found);

    // Varaible to hold the parent of the current node
    AVLNode<Key, Value>* p = current->getParent();

    // Char to hold the diff
    char diff = 0;

    // If the item is not in the tree yet
    if (current == nullptr || this->root_ == nullptr) {
        return;
    }

    // Case where the value has 0 children
    if (current->getRight() == nullptr && current->getLeft() == nullptr) {
        // If the item is the root
        if (current == this->root_ && current != nullptr) {
            this->root_ = nullptr;
        } else if (current->getParent()->getLeft() == current)  // Left child
        {
            // If it is the left child, then set the parent's left child
            // to null
            current->getParent()->setLeft(nullptr);
        } else if (current->getParent()->getRight() == current)  // right child
        {
            // If it is the right chiild, then set the parent's right child
            // to null
            current->getParent()->setRight(nullptr);
        }

        // Checking for the balance of the parent
        if (p != nullptr) {
            // If left child
            if (current->getParent()->getLeft() == current) {
                diff = 1;
            } else if (current->getParent()->getRight() == current) {
                diff = (signed char)-1;
            }
        }

        delete current;
        return;
    }
    // If the node has one child and that child is the left node
    else if (current->getRight() == nullptr && current->getLeft() != nullptr) {
        // If current is the root
        if (current == this->root_) {
            // Promote the left child
            this->root_ = this->root_->getLeft();

            // Update the parent
            this->root_->setParent(nullptr);
        } else if (current->getParent()->getRight() == current)  // right child
        {
            // Make the left child of the current node the right child of the
            // current node's parent
            current->getParent()->setRight(current->getLeft());
            current->getLeft()->setParent(current->getParent());
        } else if (current->getParent()->getLeft() == current)  // left child
        {
            // Make the left child of the current node the left child of the
            // current node's parent
            current->getParent()->setLeft(current->getLeft());
            current->getLeft()->setParent(current->getParent());
        }

        // Checking for the balance of the parent
        if (p != nullptr) {
            // If left child
            if (current->getParent()->getLeft() == current) {
                diff = 1;
            } else if (current->getParent()->getRight() == current) {
                diff = (signed char)-1;
            }
        }

        // Delete the node and return
        delete current;
        return;
    }
    // If the current node has one child and that child is the right node
    else if (current->getRight() != nullptr && current->getLeft() == nullptr) {
        if (current == this->root_) {
            // Promote the child
            this->root_ = this->root_->getRight();

            // Update the parent
            this->root_->setParent(nullptr);
        } else if (current->getParent()->getRight() == current)  // right child
        {
            // Make the right child of the current node the the child
            // of the current parent
            current->getParent()->setRight(current->getRight());
            current->getRight()->setParent(current->getParent());
        } else if (current->getParent()->getLeft() == current)  // left child
        {
            // Make the left child of the current node the child
            // pf the current's parent
            current->getParent()->setLeft(current->getRight());
            current->getRight()->setParent(current->getParent());
        }

        // Checking for the balance of the parent
        if (p != nullptr) {
            // If left child
            if (current->getParent()->getLeft() == current) {
                diff = 1;
            } else if (current->getParent()->getRight() == current) {
                diff = (signed char)-1;
            }
        }

        // Delete the node and return
        delete current;
        return;
    }
    // If the node has two children
    else if (current->getRight() != nullptr && current->getLeft() != nullptr) {
        Node<Key, Value>* finder = BinarySearchTree<Key, Value>::predecessor(current);
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(finder);
        nodeSwap(current, pred);
        if (current->getLeft() != nullptr || current->getRight() != nullptr) {
            if (current->getRight() != nullptr) {
                if (current->getParent()->getRight() == current) {
                    current->getParent()->setRight(current->getRight());
                    current->getRight()->setParent(current->getParent());
                } else {
                    current->getParent()->setLeft(current->getRight());
                    current->getRight()->setParent(current->getParent());
                }
            } else if (current->getLeft() != nullptr) {
                if (current->getParent()->getRight() == current) {
                    current->getParent()->setRight(current->getLeft());
                    current->getLeft()->setParent(current->getParent());
                } else {
                    current->getParent()->setLeft(current->getLeft());
                    current->getLeft()->setParent(current->getParent());
                }
            }

            // Checking for the balance of the parent
            if (p != nullptr) {
                // If left child
                if (current->getParent()->getLeft() == current) {
                    diff = 1;
                } else if (current->getParent()->getRight() == current) {
                    diff = (signed char)-1;
                }
            }
            delete current;
            return;
        }

        if (current->getParent()->getRight() == current) {
            current->getParent()->setRight(nullptr);
        }
        if (current->getParent()->getLeft() == current) {
            current->getParent()->setLeft(nullptr);
        }

        // Checking for the balance of the parent
        if (p != nullptr) {
            // If left child
            if (current->getParent()->getLeft() == current) {
                diff = 1;
            } else if (current->getParent()->getRight() == current) {
                diff = (signed char)-1;
            }
        }
        delete current;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2) {
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

#endif
