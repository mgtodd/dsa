#ifndef BST_ASSIGNMENT_HPP
#define BST_ASSIGNMENT_HPP

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class BST
{
public:
    // We have a Node class with more features now
    // In addition to pointers to the left and right child,
    // there is also a pointer to the parent of Node.  
    // The parent of the root should always be nullptr
    // We also hava a height field to store the height of 
    // a node in the tree.
    class Node 
    {
    public:
        T key;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        // default constructor
        Node(){}
        // constructor that takes one or optionally 2 arguments
        // if only one argument is passed in the second argument 
        // defaults to nullptr
        Node(T k, Node* input_node = nullptr)
        {
            key = k;
            parent = input_node;
        }
    };

private:
    // The BST has two private variables, a pointer to the root
    // and an unsigned integer to hold its size
    // We make the style choice of indicating these are private 
    // data variables by having a trailing underscore in their names.
    Node* root_ = nullptr;
    unsigned int size_ = 0;


public:
    // Default constructor.  No action required on this one.
    BST(); 

    // Destructor.  We implement this for you.
    ~BST();

    //*** Methods for you to implement
    // insert
    // insert the key k into the BST while maintaining the BST property
    // Like std::set, if k is already in the tree then no action is taken
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void insert(T k);

    // successor
    // Return a pointer to the node containing the smallest key larger 
    // than k
    // Return nullptr if k is the largest key in the tree
    // Also return nullptr if k is not in the tree
    //*** For you to implement
    Node* successor(T k);

    // delete the minimum
    // Erase the minimum key in the tree
    // Take no action if tree is empty
    //*** For you to implement
    void delete_min();

    // erase
    // Locate the key k in the tree and remove it
    // If k is not in the tree you do not have to do anything
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void erase(T k);

    // Implement a right rotation about the node pointed to by 
    // node, as described in Lecture 8.6.  This will only be 
    // called when node has a left child.  
    // If left_child points to the left child of *node, 
    // then *left_child becomes the parent of *node, and the 
    // right subtree of *left_child becomes the left subtree of *node.  
    // Node heights should be properly updated after this operation.
    //*** For you to implement
    void rotate_right(Node* node);

    //*** End of methods for you to implement

    // Returns the number of keys in the tree
    // we implement this for you, but it is up to you to correctly
    // update the size_ variable
    unsigned size();

    // Prints out the keys in the tree via an in-order traversal
    // we implement this for you
    void print();

    // Returns a pointer to the node containing the key k
    // We implement this for you
    Node* find(T k);

    // Creates a vector holding the keys in the tree by
    // doing an in-order traversal
    // We implement this for you, it is used in our testing.
    std::vector<T> make_vec();

    // The next two functions are to check your height values 
    // Please do not modify
    std::vector<int> your_postorder_heights();

    std::vector<int> real_postorder_heights();

    // get_root_value returns the value stored at the root
    // It used for testing purposes
    // No action needed on your part
    T get_root_value();

    // Return a pointer to the node containing the minimum key in the tree
    // We implement this for you
    Node* min();

private: 
    // We found it useful to have a "fix_height" function.
    // This assumes that the subtrees rooted at node's children have 
    // correct heights and then walks up the tree from node to the root 
    // correcting the heights.
    // You can imlement this, or correct the heights another way
    void fix_height(Node* n);

    // The rest of these functions are already implemented

    // helper function for the destructor
    void delete_subtree(Node* node);

    // returns pointer to minimum node in subtree rooted by node
    // Assumes node is not nullptr
    Node* min(Node* node);

    // helper function for print
    void print(Node* node);

    // helper function for make_vec
    void make_vec(Node* node, std::vector<T>& vec);

    void your_postorder_heights(Node* node, std::vector<int>& vec);

    int real_postorder_heights(Node* node, std::vector<int>& vec);

};

// Default constructor
// You do not need to change this
template <typename T>
BST<T>::BST()
{
}

// Destructor
// We implement this for you
template <typename T>
BST<T>::~BST()
{
    delete_subtree(root_);
}

// helper function for destructor
template <typename T>
void BST<T>::delete_subtree(Node* node)
{
    if(node==nullptr)
    {
        return;
    }
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}

template <typename T>
void BST<T>::fix_height(Node* n)
{
    // This function assumes that the subtrees of n have correct heights already
    Node* current_node = n;
    while (current_node != nullptr)
    {
        int l_height = -1;
        int r_height = -1;
        if (current_node->left != nullptr)
            l_height = current_node->left->height;

        if (current_node->right != nullptr)
            r_height = current_node->right->height;

        // This nodes height is the greater of the l&r subtree heights +1
        current_node->height = std::max(l_height, r_height) + 1;
        // Continue advancing up the tree and correcting their heights also
        current_node = current_node->parent;
    }
}


//*** For you to implement
template <typename T>
void BST<T>::insert(T k)
{
    // You can mostly follow your solution from Week 9 lab here
    // Add functionality to set the parent pointer of the new node created
    // ++size_;
    // Also remember to correct the heights on the path from the newly
    // inserted node to the root.
    // fix_height(start_fix);

    // node will iterate down through the tree starting from the root
    // Node* node = root_;
    // prev_node will hold node's parent
    Node* node = root_;
    Node* prev_node = node;
    bool went_right;
    int node_height = 0;

    if(node == nullptr)
    {
        root_ = new Node(k);
        ++size_;
        return;
    }
    while(node != nullptr)
    {
        prev_node = node;
        node_height++;
        if(k < node->key)
        {
            node = node->left;
            went_right = false;
        }
        else if (k > node->key)
        {
            node = node->right;
            went_right = true;
        }
        // item already in set
        else
        {
            return;
        }
    }
    // new node is either left or right child of prev_node
    if(went_right)
    {
        prev_node->right= new Node(k, prev_node);
        node = prev_node->right;
    }
    else
    {
        prev_node->left= new Node(k, prev_node);
        node = prev_node->left;
    }
    fix_height(node);
    ++size_;
    
}

//*** For you to implement
template <typename T>
typename BST<T>::Node* BST<T>::successor(T k)
{
    // Begin by locating the node that holds key k
    Node* current_node = find(k);
    if (current_node == nullptr) 
        return nullptr; // Node not found

    // Case 1: current_node has a right child
    //         locate the minimum node in the right subtree of current_node
    if (current_node->right != nullptr)
    {
        return min(current_node->right);
    }
    else
    // Case 2: current_node has no right child.
    //         traverse upwards until we find a key larger than k
    {
        while(current_node != nullptr)
        {
            if (current_node->key > k)
                return current_node; // found a key greater than k
            else
                current_node = current_node->parent; // keep searching
        }
    }
    // If we get here then we never found a key larger than k
    return nullptr;

}

//*** For you to implement
template <typename T>
void BST<T>::delete_min()
{
    // if tree is empty just return.
    Node* min_node = min();
    if (min_node == nullptr)
        return;
    Node* parent = min_node->parent;
    Node* child = min_node->right;

    // If the parent of min_node is null then this is the root_
    if (parent == nullptr)
    {
        // If min_node has a valid right child, make this root
        if (child != nullptr)
        {
            child->parent = nullptr;
        }
        this->root_ = child;
        fix_height(root_);
    }
    else
    // Move the right subtree of min_node beneath min_node's parent
    {
        parent->left = child;
        if (child != nullptr)
            child->parent = parent;
        fix_height(parent);
    }
    // Delete min, update size
    delete min_node;
    --size_;
}

//*** For you to implement
template <typename T>
void BST<T>::erase(T k)
{
    // locate node holding key k
    Node* n = find(k);
    if (n == nullptr)
        return;
    
    Node* r = n->right;
    Node* l = n->left;
    Node* replacement = nullptr; // default case is n has no children
    Node* parent = n->parent;
    // Case 1: n has only left child
    if (r == nullptr && l != nullptr)
    {
        replacement = l;
    }
    // Case 2: n has only left child
    else if (r != nullptr && l == nullptr)
    {
        replacement = r;
    }
    // Case 3: n has left and right children
    else if (r != nullptr && l != nullptr)
    {
        // In this case, we don't actually delete this node,
        // instead we update it with the key of its successor and 
        // delete the successor node
        replacement = successor(k);
        int new_key = replacement->key;
        erase(new_key);
        n->key = new_key;
        fix_height(n);
        return;
    }

    // Decide what to update
    if (replacement == nullptr)
    {
        // If n is a leaf node, replacement is null
        // update parent appropriately
        if (parent->key > n->key)
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }
    else
    {
        // n is not a leaf node
        // Update the parent node and also the replacement node pointers
        if (parent == nullptr)
        {
            // n is actually the root node
            root_ = replacement;
            replacement->parent = nullptr;
        }
        else
        {
            if (parent->key > k)
            {
                // put replacement on the left side
                parent->left = replacement;
                replacement->parent = parent;
            }
            else
            {
                // put replacement on the right side
                parent->right = replacement;
                replacement->parent = parent;
            }
        }
    }
    // Delete the node, update size and height
    delete n;
    size_--;
    fix_height(parent);
}

//*** For you to implement
template <typename T>
void BST<T>::rotate_right(Node* node)
{
    // Assumptions: node is not nullptr and must have a left child

    // Node* move_up_node = node->left;  
    
    // There are 3 pairs (parent and child) of pointers to change
    // 1) node's left child becomes move_up_node's right child
    // 2) node's original parent becomes move_up_node's parent
    // 3) move_up_node's right child becomes node

    Node* move_up_node = node->left;
    Node* parent = node->parent;

    // Binary tree right rotate
    node->left = move_up_node->right;
    move_up_node->right = node;

    // Update the parent of node 
    node->parent = move_up_node;
    move_up_node->parent = parent;

    // handle node's original parent linkages
    if (parent == nullptr)
        root_ = move_up_node;
    else if (parent->key > move_up_node->key)
        parent->left = move_up_node;
    else
        parent->right = move_up_node;
    
    fix_height(node);


}

// The rest of the functions below are already implemented

// returns a pointer to the minimum node
template <typename T>
typename BST<T>::Node* BST<T>::min()
{
    if(root_ == nullptr)
    {
        return root_;
    }
    else
    {
        return min(root_);
    }
}

// returns pointer to minimum node in the subtree rooted by node
// Assumes node is not nullptr
template <typename T>
typename BST<T>::Node* BST<T>::min(Node* node)
{
    while(node->left != nullptr)
    {
        node = node->left;
    } 
    return node;
}

// returns a pointer to node with key k
template <typename T>
typename BST<T>::Node* BST<T>::find(T k)
{
    Node* node = root_;  
    while(node != nullptr && node->key != k)
    {
        node = k < node->key ?  node->left : node->right;
    }
    return node;  
}

template <typename T>
unsigned BST<T>::size()
{
    return size_;
}

// prints out the keys in the tree using in-order traversal
template <typename T>
void BST<T>::print()
{
    print(root_);
}

// you can modify what is printed out to suit your needs
template <typename T>
void BST<T>::print(Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    print(node->left);
    std::cout << node->key << " height " << node->height << '\n';
    print(node->right);
}

// This is used in our testing, please do not modify
template <typename T>
typename std::vector<T> BST<T>::make_vec()
{
    std::vector<T> vec;
    vec.reserve(size_);
    make_vec(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::make_vec(Node* node, std::vector<T>& vec)
{
    if(node == nullptr)
    {
        return;
    }
    make_vec(node->left, vec);
    vec.push_back(node->key);
    make_vec(node->right, vec);
    
}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::your_postorder_heights(Node* node, std::vector<int>& vec)
{
    if(node == nullptr)
    {
        return;
    }
    your_postorder_heights(node->left, vec);
    your_postorder_heights(node->right, vec);
    vec.push_back(node->height);
}

// This is used for our testing, please do not modify
template <typename T>
int BST<T>::real_postorder_heights(Node* node, std::vector<int>& vec)
{
    if(node == nullptr)
    {
        return -1;
    }
    int left_height = real_postorder_heights(node->left, vec);
    int right_height = real_postorder_heights(node->right, vec);
    int node_height = 1 + std::max(left_height, right_height);
    vec.push_back(node_height);
    return node_height;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::your_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    your_postorder_heights(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::real_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    real_postorder_heights(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
T BST<T>::get_root_value()
{
    if(root_ == nullptr)
    {
        //std::cout << "Calling get_root_value on empty tree\n";
        T dummy {};
        return dummy;
    }
    else
    {
        return root_->key;
    }
}

#endif
