// AVLSet.hpp
//
// ICS 46 Spring 2020
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include "Set.hpp"




template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    ~AVLSet() noexcept override;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const noexcept;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.


    struct Node
    {
        ElementType element;
        Node* left;
        Node* right;
    };

    Node* root;
    int treesize;
    bool balance;
    void deleteAll(Node* a) noexcept;
    void copyAll(Node* leftt, Node* rightt);
    void dobalance (Node *r);

    void AVLing(Node *&r, const ElementType& element);
    void NAVLing(Node* &r, const ElementType& element);
    
    bool isfind(Node* r, const ElementType& value) const;
    int findheight(Node* r) const;

    void preorderbase(Node* r, VisitFunction visit) const;
    void postorderbase(Node* r, VisitFunction visit)const;
    void inorderbase(Node* r, VisitFunction visit)const;
    void LL(Node* &r);
    void RR(Node* &r);
    void LR(Node* &r);
    void RL(Node* &r);
};


template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
    root =nullptr;
    treesize=0;
    balance=shouldBalance;


}


template <typename ElementType>
void ::AVLSet<ElementType>::deleteAll(Node *r) noexcept
{
    
    Node* current = r;
    if (current !=nullptr and current->left !=nullptr)
        deleteAll(current->left);
    if (current !=nullptr and current->right !=nullptr)
        deleteAll(current->right);
        
    if (current!=nullptr)
    {
        delete current;
        current =nullptr;

    }
    

}

template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    deleteAll(root);
    treesize=0;

}


// }

template <typename ElementType>
void AVLSet<ElementType>::copyAll(Node* n, Node* s){
    if(s != nullptr){
        n = new Node{s->element};
        if(s->left != nullptr){
            n->left = new Node{s->element};
            copyAll(n->left, s->left);
        }
        if(s->right != nullptr){
            n->right = new Node{s->element};
            copyAll(n->right, s->right);
        }
    }
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
    root = nullptr;
    copyAll(root, s.root);

    
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
    root =nullptr;
    
    std::swap(root, s.root);

}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    if (this != &s)
    {
        deleteAll(root);
        copyAll(root,s.root);
    }
    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    std::swap(root,s.root);
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& value)
{
    if (balance)
    {
      AVLing(root,value);
      
    }
    else
    {
        NAVLing(root,value);
    }

}



template <typename ElementType>
void AVLSet<ElementType>::AVLing(Node*& r, const ElementType& value)
{
     if(r == nullptr){
        r = new Node{value};
        treesize++;
        return;
    }

    else if (value > r->element)
    {
        AVLing(r->right, value);
        if (findheight(r->right) - findheight(r->left) == 2){
            if (value > r->right->element)
                RR(r);
            else
                RL(r);
        }
    }
    else if (value < r->element){
        AVLing(r->left, value);
        if (findheight(r->left) - findheight(r->right) == 2){
            if (value < r->left->element)
                LL(r);
            else
                LR(r);
        }
    }
    else if(value == r->element)
        return;

 
}


template <typename ElementType>
void AVLSet<ElementType>::NAVLing(Node*& r, const ElementType& value)
{
    if(root == nullptr){
        root = new Node{value};
        treesize++;
        return;
    }


    Node* currentNode = root;

    while(true){
        if(value > currentNode->element){
            if(currentNode->right == nullptr){
                currentNode->right = new Node{value};
                treesize++;
      

                break;
            }
            else
                currentNode = currentNode->right;
        }
        else if(value < currentNode->element){
            if(currentNode->left == nullptr){
                currentNode->left = new Node{value};
                treesize++;


                break;
            }
            else
                currentNode = currentNode->left;
        }
        else
            break;
    }


    currentNode = nullptr;
    delete currentNode;

    return;

}

template<typename ElementType>
void AVLSet<ElementType>::LL(Node* &node){
    Node* temp;
    temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node = temp;
}

template<typename ElementType>
void AVLSet<ElementType>::RR(Node* &node){
    Node* temp;
    temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node = temp;
}

template<typename ElementType>
void AVLSet<ElementType>::LR(Node* &node){
    RR(node->left);
    LL(node);
}

template<typename ElementType>
void AVLSet<ElementType>::RL(Node* &node){
    LL(node->right);
    RR(node);
}

template <typename ElementType>
bool AVLSet<ElementType>::isfind(Node* r, const ElementType& value) const{
    bool result = false;
    if(r == nullptr)
        return false;
    else if(r != nullptr and r->element == value)
        return true;
    else if(r != nullptr and r->element == value)
        result = isfind(r->right, value);
    else if(r != nullptr and r->element == value)
        result = isfind(r->left, value);
    return result;
}

template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& value) const
{

    if(root == nullptr)
        return false;
    Node* current = root;
   
    while(current != nullptr){
        if(current->element == value)
            return true;
        else if (value > current->element)
            current = current->right;
        else if (value < current->element)
            current = current->left;
    }
    return false;
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return treesize;

}

template <typename ElementType>
int AVLSet<ElementType>::findheight(Node* r) const{
    if(r != nullptr)
    {
        int heightL = findheight(r->left);
        int heightR = findheight(r->right);

        if(heightL >= heightR)
            return heightL + 1;
        return heightR +1 ;
    }
    return -1;
}



template <typename ElementType>
int AVLSet<ElementType>::height() const noexcept
{
    return findheight(root);
}





//==================finished 
template <typename ElementType>
void AVLSet<ElementType>::preorderbase(Node* r, VisitFunction visit)const{
    if(r != nullptr){
        visit(r->element);
        preorderbase(r->left, visit);
        preorderbase(r->right, visit);
    }
}
template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    preorderbase(root,visit);

}
template <typename ElementType>
void AVLSet<ElementType>::inorderbase(Node* r, VisitFunction visit)const{
    if(r != nullptr){
        inorderbase(r->left,visit);
        visit(r->element);
        inorderbase(r->right, visit);
    }
}

template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    inorderbase(root,visit);
}

template <typename ElementType>
void AVLSet<ElementType>::postorderbase(Node* r, VisitFunction visit)const{
    if(r != nullptr){
        postorderbase(r->left, visit);
        postorderbase(r->right, visit);
        visit(r->element);
    }
    
}
template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    postorderbase(root,visit);

}



#endif // AVLSET_HPP

