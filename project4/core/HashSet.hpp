// HashSet.hpp
//
// ICS 46 Spring 2020
// Project #4: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"
#include<iostream>


template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    ~HashSet() noexcept override;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8, in which case
    // the new capacity should be determined by this formula:
    //
    //     capacity * 2 + 1
    //
    // In the case where the array is resized, this function runs in linear
    // time (with respect to the number of elements, assuming a good hash
    // function); otherwise, it runs in constant time (again, assuming a good
    // hash function).  The amortized running time is also constant.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns 0.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;

    struct Node
    {
        ElementType element;
        Node* next = nullptr;
    };

    Node** hash;
    void deletehash(Node* head) noexcept;
    unsigned int hashsize;
    unsigned int hashcapacity;
    unsigned int numelement;
};



namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}


template <typename ElementType> //pass
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    hashcapacity = DEFAULT_CAPACITY;
    hashsize = 0;
    hash = new Node* [hashcapacity];
    for(int i = 0; i < hashcapacity; ++i)
        hash[i] = new Node{};
    numelement=0;

}




template <typename ElementType>
void HashSet<ElementType>::deletehash(Node* head) noexcept

{

    Node* current = head;
    while (current != nullptr)
    {
        Node* temp = current;
        current = current-> next;
        delete temp;
        temp=nullptr;

    }
}

template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    for (int i=0; i<hashsize ; ++i)
    {
        deletehash(hash[i]);

    }

    hash = nullptr;
    delete[] hash;



}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{

    hashsize = s.hashsize;
    hashcapacity = s.hashcapacity;
    numelement = s.numelement;

    hash = new Node* [hashcapacity];
    for(int i = 0; i < s.hashcapacity; i++)
        hash[i] = s.hash[i];
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
        hashsize = s.hashsize;
        hashcapacity = s.hashcapacity;
        numelement = s.numelement;
        hash = new Node*[hashcapacity];
        std::swap(hash,s.hash);
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    if (this  != &s)
    {
        for (int i=0; i< hashcapacity ; ++i)
        {
            deletehash(hash[i]);
        }
        hashsize=0;
        hashcapacity=s.hashcapacity;

        for ( int i =0; i<hashcapacity; ++i)
        {
            hash[i] =s.hash[i];
        }

        hashcapacity=s.hashcapacity;
        hashFunction=s.hashFunction;
    }
    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    hashsize = s.hashsize;
    hashcapacity = s.hashcapacity;
    numelement = s.numelement;
    hash = new Node*[hashcapacity];
    std::swap(hash,s.hash);
    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{

    int elementindex;
    if ((hashsize/hashcapacity) >0.8)
    {
        //resize it 
        int oldcapacity = hashcapacity;

        hashcapacity = hashcapacity *2 + 1;
        Node **oldhash = hash;
        
        for (int i=0; i<hashcapacity;i++)
        {
            deletehash(hash[i]);
        }
        hash=nullptr;

        hash = new Node* [hashcapacity];
        for ( int i=0; i<hashcapacity; i++)
        {
            hash[i]= new Node{};
        }

        //reload data
        for (int i =0 ; i< oldcapacity;i++)
        {
            Node* eachhead = oldhash[i]; 
            while (eachhead !=nullptr) //load each list in old hash table
            {
                ElementType elementdata = eachhead->element;
                elementindex = hashFunction(elementdata) % hashcapacity;
                if (hash[elementindex] == nullptr)
                {
                    hash[elementindex] = new Node{elementdata};
                    numelement++;
                    hashsize++;

                }
                else
                {
                    Node *pend = hash[elementindex];
                    while (pend->next != nullptr)
                    {
                        pend=pend->next;
                    }
                    pend->next = new Node{elementdata};
                    numelement++;
                }

                eachhead = eachhead->next; //next data.                
            }

            eachhead=nullptr;
            delete eachhead;


        }
    }

    // adding
    elementindex = hashFunction(element) % hashcapacity;
    if (hash[elementindex]==nullptr) //if empty cell
    {
        hash[elementindex] = new Node{element};
 

        hashsize++;
        numelement++;
       
    }
    else // if not
    {
        if ( ! isElementAtIndex(element,elementindex)) // find duplicated element?
        {
            Node *pend  = hash[elementindex];
            while (pend->next !=nullptr)
            {
                pend = pend->next;

            } //get to the end;

            pend->next = new Node{element};
            numelement++;
            pend =nullptr;
            delete pend;
            
        }
    }




        



}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    unsigned int index = hashFunction(element) % hashcapacity;
    return isElementAtIndex(element,index);
}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    return numelement;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    int countelement=0;
    Node* phead = hash[index];


    if (phead->element and phead->next == nullptr)
    {
        return 1;

    }
    else
    {

        while (phead->next !=nullptr)
        {
            countelement++;
            phead =phead->next;

        }
        
    }
    phead= nullptr;
    delete phead;


    return countelement;

}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{
    if (hash[index])
    {
        Node* phead = hash[index];
        
        
        while (phead !=nullptr)
        {

            if (phead->element == element)
                
                return true;

            
            phead =phead->next;

        }

        phead = nullptr;
        delete phead ; 
        return false;

    }

    return false;

}



#endif // HASHSET_HPP

