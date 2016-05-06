// $Id: listmap.tcc,v 1.7 2015-04-28 19:22:02-07 - - $

#include "listmap.h"
#include "trace.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (node* next, node* prev,
                                     const value_type& value):
            link (next, prev), value (value) {
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap() {
   TRACE ('l', (void*) this);
}


//
// iterator listmap::insert (const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::insert (const value_type& pair) {
   TRACE ('l', &pair << "->" << pair);
   //First we check if it's currently empty
   //If it is empty, then we can just insert it.
   if(this->begin() == this->end()){
      //Since it's empty, our key doesnt not exist so we make a new node
      //The first node will just have anchor as its next and prev
      node* newNode = new node(anchor(), anchor(), pair);

      //Since it's the only node, anchor's next and prev point to it
      anchor()->next = newNode;
      anchor()->prev = newNode;
      return newNode;  
   }
   //If it is not empty, then we have to check if it exists already
   //If it does not exist, then we need to insert it in the right place
   iterator findIter = this->find(pair.first);
   if(findIter == iterator()){
      //If this is true, that means the key does not exist
      
      //This is a place holder node that we will compare to see where the new node goes.
      node* currentNode = anchor()->next;
      
      //Since it is ordered by key, we compare that
      //Also, don't compare if you reach anchor because anchor has no data
      while(less(currentNode->value.first, pair.first) && currentNode != anchor()){
         currentNode = currentNode->next;
      }

      //Once we figure ouut where it goes, make a new node and insert it there
      node* newNode = new node(currentNode, currentNode->prev, pair);
      newNode->prev->next = newNode;
      currentNode->prev = newNode;
      return newNode;
   }else{
      //If the key does exist, then all we need to do is update the value
      findIter->second = pair.second;
      return findIter;
   }
   return iterator();
}

//
// listmap::find(const key_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) {
   TRACE ('l', that);
   //Just cycles through the listmap checking if the key already exists
   //if it does not exist, it just returns iterator()
   for(node* currentNode = anchor()->next; currentNode != anchor(); currentNode = currentNode->next){
      if(currentNode->value.first == that) return currentNode;      
   }
   return iterator();
}

//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::erase (iterator position) {
   TRACE ('l', &*position);
   return iterator();
}


//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type&
listmap<Key,Value,Less>::iterator::operator*() {
   TRACE ('l', where);
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type*
listmap<Key,Value,Less>::iterator::operator->() {
   TRACE ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++() {
   TRACE ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator--() {
   TRACE ('l', where);
   where = where->prev;
   return *this;
}


//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}

