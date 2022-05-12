#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class Forward_list
{
public:
    class Node
    {
    public:
        // A node will hold data of type T
        T data{};
        // next will point to the next node in the list
        // we initialise next to nullptr
        Node* next = nullptr;

        // Because we have already intialised the variables
        // the default constructor doesn't need to do anything
        Node(){}

        // To make life easier we also provide a constructor
        // that takes the T data to be copied into the data member variable 
        // There is an optional second argument which is
        // used to update the next pointer.  This defaults to nullptr 
        // if the constructor is called with just one argument.
        Node(T input_data, Node* next_node= nullptr)
        {
            data = input_data;
            next = next_node;
        }

        // Destructor
        ~Node(){}
    };

private:
    // private member variables for Forward_list
    // the trailing underscore is a stylistic choice to 
    // distinguish these as private member variables
    unsigned size_ = 0;
    Node* head_ = nullptr;

public:
    // public member functions of the Forward_list class
    // We have generally used the same names as for the
    // corresponding functions of std::forward_list

    // Default constructor does not need to do anything 
    // and is provided for you.
    Forward_list();
   
    // The destructor is implemented for you
    ~Forward_list();

    // Copy constructor
    //*** For you to implement
    Forward_list(const Forward_list<T>& other);

    // Constructor from initializer list
    //*** For you to implement
    Forward_list(std::initializer_list<T> input);

    // Constructor from vector
    Forward_list(std::vector<T> input);

    // Add an element to the front of the list
    //*** For you to implement
    void push_front(const T& data);

    // Remove the first element of the list
    //*** For you to implement
    void pop_front();

    // Return the data held in the first item of the list
    // This function should not change the list, which is 
    // why it is declared const
    //*** For you to implement
    T front() const;

    // Print out all the data in the list in sequence
    //*** For you to implement
    void display() const;

    // Outputs if the list is empty or not
    // Implemented for you
    bool empty() const;

    // outputs the size of the list
    // Implemented for you, but your code should properly 
    // update the size_ member variable as needed
    unsigned size() const;

    // ---------------------------------------------
    // methods related to sorting     

    // merge two sorted lists, *this and other
    //*** For you to implement
    void merge(Forward_list& other);

    // split *this into its first half, which becomes the new *this,
    // and its second half which is returned
    //*** For you to implement
    Forward_list split();

    // The sort function uses the helper functions 
    // merge and split that you write
    // You do not need to modify sort itself
    void sort();

private:

    // sort is implemented via a recursive merge sort
    // You do not need to modify this function
    void merge_sort(Forward_list&);

    void swap_pointers(Node &a, Node &b);

    void displayNode(Node* n);

};

// Default Constructor
// You do not need to change this
template <typename T>
Forward_list<T>::Forward_list()
{
    size_ = 0;
    head_ = nullptr;
}

// Destructor
// The destructor is implemented for you
template <typename T>
Forward_list<T>::~Forward_list()
{
    while(head_ != nullptr)
    {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
    }
}

// Copy constructor
// ***For you to implement

// The copy constructor takes as argument a const reference to a 
// another Forward_list "other" 
// The const means that the function should not modify other
// The function should make a "deep copy" of the other list,
// that is create a new node for every node in other and copy 
// the data of other into these new nodes.  
template <typename T>
Forward_list<T>::Forward_list(const Forward_list& other)
{
    if (other.head_ == nullptr)
        return;
    
    // Create the first node with the head data of other
    Node* n_this = new Node(other.head_->data, nullptr);
    // Set this node as the head of self
    this->head_ = n_this;
    this->size_++;
    // Create a node for traversing other
    Node* n_oth = other.head_;

    // Once the next node is blank, stop creating new nodes
    while(n_oth->next != nullptr)
    {
        // Advance other node
        n_oth = n_oth->next;
        // Create a new node that copies the data from the other node
        Node* new_node = new Node();
        new_node->data = n_oth->data;
        // Mark new node as the next of our list
        n_this->next = new_node;
        // Advance our node
        n_this = n_this->next;
        this->size_++;
    }

}

// Constructor from initializer list
// ***For you to implement

// This implements the functionality you see with, for example, 
// std::forward_list<int> my_list = {1,2,3}
// which creates a new linked list where the first node holds 1, second 2, and 
// third 3.
// The {1,2,3} here is of type std::initializer_list<int> and you 
// see this is the argument to this constructor (with data of type T
// rather than just int). 

// You can access the elements of a std::initializer_list via an iterator
// for example you can cycle through all the elements with
// for(auto it = input.begin(); it!= input.end(); ++it){Do something with *it} 
template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> input)
{
    // Add the values in backwards so that the front node has the first
    // value from the initializer list
    // todo : use iterators
    for (int i = input.size()-1; i >= 0; i--)
    {
        this->push_front(input.begin()[i]);
    }
}

template<typename T>
Forward_list<T>::Forward_list(std::vector<T> input)
{
    for (int i = input.size()-1; i>=0; i--)
    {
        this->push_front(input.at(i));
    }
}


// Add element to front of list
// ***For you to implement
template <typename T>
void Forward_list<T>::push_front(const T& data)
{
    // Create a new node that links with the front
    Node* new_node = new Node(data,this->head_);
    // Update the front node and size
    this->head_ = new_node;
    this->size_++;
}

// Remove the front element of the list 
// If the list is empty don't do anything
// ***For you to implement
template <typename T>
void Forward_list<T>::pop_front()
{
    if (this->head_ != nullptr)
    {
        // Hold onto the head so that we can delete it
        Node* tmp = this->head_;
        // Update the head
        this->head_ = this->head_->next;
        // displayNode(tmp);
        delete tmp;
        this->size_--;
    }
}

// Return the data in the front element of the list
// If the list is empty the behaviour is undefined:
// you can return an arbitrary value, but don't segfault 
// ***For you to implement
template <typename T>
T Forward_list<T>::front() const
{
    // Return the front value unless the list is empty
    if (this->head_ != nullptr)
    {
        return this->head_->data;
    }
    // Use templated constructor to return an empty value
    return T();
}

// Print out the list
// ***For you to implement
template <typename T>
void Forward_list<T>::display() const
{
    // Traverse the list and print along the way
    Node* tmp = this->head_;
    while (tmp != nullptr)
    {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << endl;
}


// Outputs if the list is empty or not
// Implemented for you
template <typename T>
bool Forward_list<T>::empty() const
{
    return (head_ == nullptr);
}

// Returns the size of the list
// It is implemented for you but you need to correctly 
// update the size_ variable in your code as needed

// Note that std::forward_list actually does not have a size function
template <typename T>
unsigned Forward_list<T>::size() const
{
    return size_;
}


// the split function splits *this into its first half, which becomes 
// the new *this, and its second half which is returned
// if the the size of *this is n, then after split the size of *this 
// should be ceiling(n/2), and the size of the returned list should be
// floor(n/2)

// As an example, if *this is of the form
// head_ -> a -> b -> c -> d -> nullptr
// then after split *this should be
// head_ -> a -> b -> nullptr
// and you should a return a Forward_list other where
// other.head_ = c -> d -> nullptr

// Don't forget to update the size_ variable of this and other
// You do not need to create any new nodes for this function,
// just change pointers.
// ***For you to implement
template <typename T>
Forward_list<T> Forward_list<T>::split()
{
    // Minimum length for splitting must be 2
    if (this->size_ < 2)
        return Forward_list();

    // Traverse up until the halfway point
    Node* tmp = this->head_;
    // cout << "Length is " << this->size_;
    // cout << "\nMid idx is " << (this->size_ + 1) / 2 << endl;

    int mid = 0;
    if (this->size_ % 2 == 0)
        mid = this->size_ / 2 - 1;
    else
        mid = this->size_ / 2;

    for(int i = 0; i < mid; i++)
    {
        tmp = tmp->next;
    }
    // At this point, tmp holds the final node of this
    // tmp->next will be the first node of other

    Forward_list<T> other = Forward_list();
    other.head_ = tmp->next;
    other.size_ = this->size_ / 2;

    // Update this list end value and size
    tmp->next = nullptr;
    this->size_ = (this->size_ + 1)/2;

    return other;
}   

template <typename T>
void Forward_list<T>::swap_pointers(Node &a, Node &b)
{
    Node c = a;
    a = b;
    b = c;
}

// // Make the order a -> b -> c
// function set_node_order(Node* &a, Node* &b, Node* &c)
// {
//     // 
//     a->next = b;
//     b->next = c;
// }
template <typename T>
void Forward_list<T>::displayNode(Node* n)
{
    cout << "data: " << n->data << " adress: " << n << " n->next: " << n->next << endl;
}

// Merging two sorted lists
// For this function it is assumed that both *this and the 
// input Forward_list other are already sorted
// The function merges the two lists into sorted order, and the merger becomes 
// the new *this

// You do not need to create any new nodes in this function,
// just update pointers.  
// Set other to be an empty list at the end of the function
//***For you to implement
template <typename T>
void Forward_list<T>::merge(Forward_list& other)
{

    cout << "this  list pre merge: ";
    this->display();
    cout << "other list pre merge: ";
    other.display();

    Node* n_other = other.head_;
    Node* n_this = this->head_;
    Node* n_merged = nullptr;

    // robust against nullptr
    if (n_this == nullptr)
    {
        this->head_ = other.head_;
        this->size_ = other.size_;    
        other.head_ = nullptr;
        other.size_ = 0;
        return;
    }
    if (n_other == nullptr)
        return;

    // Header select
    if (n_this->data > n_other->data)
    {
        n_merged = n_other; 
        n_other = n_other->next;
        this->size_++;
    }
    else
    {
        n_merged = n_this;
        n_this = n_this->next;
    }
    
    this->head_ = n_merged;

    // Now traverse
    while(1)
    // for (int i=0; i<50; i++)
    {
        // cout<< "n_this   -- "; displayNode(n_this);
        // cout<< "n_other  -- "; displayNode(n_other);
        // cout<< "n_merged -- "; displayNode(n_merged);
        // cout << endl;
        // If this list is depleted
        if (n_this == nullptr && n_other != nullptr)
        {
            n_merged->next = n_other;
            // Advance n_other
            n_other = n_other->next;
            this->size_++;
        }
        // If other list is depleted
        else if (n_this != nullptr && n_other == nullptr)
        {
            n_merged->next = n_this;
            // Advance n_this
            n_this = n_this->next;
        }
        // If neither is depleted, compare and choose the next value
        else if (n_this != nullptr && n_other != nullptr)
        {
            if (n_other->data < n_this->data)
            {
                n_merged->next = n_other;
                // Now advance other list
                n_other = n_other->next;
                this->size_++;
            }
            else // n_other->data > n_this->data
            {
                n_merged->next = n_this;
                // Now advance this list
                n_this = n_this->next;
            }
            
        }
        else // both lists are finished
            break;
        
        // Always advance n_merged
        n_merged = n_merged->next;
    }

    // Kill the other list
    other.head_ = nullptr;
    other.size_ = 0;

}   

// recursive implementation of merge_sort
// you do not need to change this function
template <typename T>
void Forward_list<T>::merge_sort(Forward_list& my_list)
{
    if(my_list.size() == 0 || my_list.size() == 1)
    {
        return;
    }
    Forward_list<T> second = my_list.split();
    merge_sort(my_list);
    merge_sort(second);
    my_list.merge(second);
}

// sorts the list by calling merge_sort
// once your merge and split functions are working
// sort should automatically work
// you do not need to change this function
template <typename T>
void Forward_list<T>::sort()
{
    merge_sort(*this);
}


#endif