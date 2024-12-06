#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int depth(Node* node, int& value);


bool equalPaths(Node * root)
{
    //Copy of the root
    //used for traversal
    Node* current = root;

    //If the tree is empty
    if(current == NULL)
    {
        return true;
    }

    //Value to hold 0
    int zero = 0;

    //Getting the ints for both sides of the tree
    int lheight = depth(current->left, zero);
    int rheight = depth(current->right, zero);

    //Checking to make sure they are balanced
    //If not then the tree is not balanced and will return false
    if(abs(lheight- rheight) == 0)
    {
        if(equalPaths(current->left) == true && equalPaths(current->right) == true)
        {
            return true;
        }
    }

    //Not balanced so return false
    return false;
}

int depth(Node* node, int& value)
{
    //Value to hold the return count
    value++;

    //Base case for recursion
    if (node == NULL)
    {
        return 0;
    }
    
    //If the left side of the tree is 
    //heavier than the right side
    if(depth(node->left, value) > depth(node->right, value) )
    {
        value = depth(node->left, value);
        return value + 1;
    }
    //If the right side of the tree is 
    //heavier than the left side
    else if(depth(node->left, value) < depth(node->right, value))
    {
        value = depth(node->right, value);
        return value + 1;
    }

    //If they are equal then this return value will happen
    return 0;
}

