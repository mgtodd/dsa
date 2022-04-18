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

    Node* tmp = other.head_;
    std::vector<T> other_values;
    while (tmp != nullptr)
    {
        other_values.push_back(tmp->data);
        tmp = tmp->next;
    }
    // Insert values backwards so that the two lists have
    // the same order
    for(int i=other.size()-1; i >= 0; i--)
    {
        this->push_front(other_values.at(i));
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
    this->display();
    // Prepare an empty forward list named other
    Forward_list<T> empty_list = Forward_list();
    // Minimum length for splitting must be 2
    if (this->size_ < 2)
        return empty_list;

    // Traverse up until the halfway point
    Node* tmp = this->head_;
    int idx = 0;
    cout << "Length is " << this->size_;
    cout << "\nMid idx is " << (this->size_ + 1) / 2 << endl;

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
    // other.push_front
    Node* tmp_other = tmp;
    // Create a vector of the new values required for other
    std::vector<T> other_values;
    while (tmp_other->next != nullptr)
    {
        tmp_other = tmp_other->next;
        other_values.push_back(tmp_other->data); // todo: somehow we are meant to not use push_back
                                                 // ie, only rearrange some pointers. 
    }
    // Update this list end value and size
    tmp->next = nullptr;
    this->size_ = (this->size_ + 1)/2;

    this->display();

    // Create the other list using the vector and return it
    Forward_list<T> other = Forward_list(other_values);
    other.display();
    return other;

}   

template <typename T>
void Forward_list<T>::swap_pointers(Node &a, Node &b)
{
    Node c = a;
    a = b;
    b = c;
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
    // todo: merge is pretty broken atm
    Node* it_this = this->head_;
    Node* it_other = other.head_;

    Node* tmp;

    cout << "this: ";    this->display();
    cout << "other: ";other.display();

    vector<T> merged_values;
    while(true)
    {
        // this list finished, copy other values
        if (it_this == nullptr && it_other != nullptr)
        {
            it_this->next = it_other;
            break;
            merged_values.push_back(it_other->data);
            // it_other = it_other->next;
        }
        // other list finished, copy this values
        else if (it_this != nullptr && it_other == nullptr)
        {
            break;
            merged_values.push_back(it_this->data);
            // it_this = it_this->next;
        }
        // neither list finished
        // grab the lowest value and increment appropriately
        else if (it_this != nullptr && it_other != nullptr)
        {
            // cout << "this: " << it_this->data << " other: " << it_other->data << ", ";
            if (it_this->data < it_other->data)
            {
                // cout << "this < other" << endl;
                // merged_values.push_back(it_this->data);
                tmp = it_this;
                it_this = it_this->next;1
                tmp->next = it_other;
            }
            else
            {
                // cout << "this > other" << endl;
                // merged_values.push_back(it_other->data);

                tmp = it_this->next;
                it_this->next = it_other;
                it_this = tmp;

            }
            // this->display();
        }
        else
            break;
        // // this list finished, copy other values
        // if (it_this == nullptr && it_other != nullptr)
        // {
        //     merged_values.push_back(it_other->data);
        //     it_other = it_other->next;
        // }
        // // other list finished, copy this values
        // else if (it_this != nullptr && it_other == nullptr)
        // {
        //     merged_values.push_back(it_this->data);
        //     it_this = it_this->next;
        // }
        // // neither list finished
        // // grab the lowest value and increment appropriately
        // else if (it_this != nullptr && it_other != nullptr)
        // {
        //     if (it_this->data < it_other->data)
        //     {
        //         merged_values.push_back(it_this->data);
        //         it_this = it_this->next;
        //     }
        //     else
        //     {
        //         merged_values.push_back(it_other->data);
        //         it_other = it_other->next;
        //     }
        // }
        // else
        //     break;
    }
    cout << "merged values : ";
    for (auto v : merged_values)
        cout << v << " ";
    cout << endl;
    this->display();
    // // Create the new list from the vector of values
    // if (merged_values.size() > 0)
    // {
    //     Forward_list<T>* merged_list = Forward_list(merged_values);
    //     cout << "created merged_list success" << endl;
    //     this->head_ = merged_list->head_;
    //     this->size_ = merged_list->size_;

    // }   
    // cout << "displaying merged list";
    // this->display();
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