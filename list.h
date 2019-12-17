//***************************************************************************//
//*                                                                         *//
//*  Copyright (c) 2004-2019 Clifford Thompson                              *//
//*                                                                         *//
//*  This program is free software: you can redistribute it and/or modify   *//
//*  it under the terms of the GNU General Public License as published by   *//
//*  the Free Software Foundation, either version 3 of the License, or      *//
//* (at your option) any later version.                                     *//
//*                                                                         *//
//*  This program is distributed in the hope that it will be useful,        *//
//*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *//
//*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *//
//*  GNU General Public License for more details.                           *//
//*                                                                         *//
//*  You should have received a copy of the GNU General Public License      *//
//*  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *//
//*                                                                         *//
//***************************************************************************//

//***************************************************************************//
//*                                                                         *//
//* list<Type>                                                              *//
//*                                                                         *//
//* Class Description : This class provides the interface for a doubly      *//
//*                     linked list ADT. The number of operations provided  *//
//*                     is minimal. You can check the size of the list,     *//
//*                     check if the list is empty, push and element onto   *//
//*                     the back of the list, and get an interator to the   *//
//*                     start of the list.                                  *//
//*                                                                         *//
//*                     NOTE: The class definition is also included in this *//
//*                           file because it is required for templated     *//
//*                           classes.                                      *//
//*                                                                         *//
//* Exceptions Thrown : {None Thrown}                                       *//
//*                                                                         *//
//* File          : list.h                                                  *//
//* Author        : Clifford Thompson                                       *//
//* Creation Date : July 15, 2004                                           *//
//*                                                                         *//
//***************************************************************************//

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#include "list_node.h"
#include "list_iterator.h"

template<class Type>
class list {

public:

   list<Type>():list_size(0),head_node(NULL),tail_node(NULL){};
   list<Type>(const list&);
  ~list<Type>();

   unsigned int size() const {return list_size;};
           bool empty() const {return list_size == 0 ? true : false;};
           void push_back(const Type&);
 
   list_iterator<Type> begin()const {return list_iterator<Type>(head_node);};

private:

   void erase (list_iterator<Type>&);

   list_node<Type>* head_node;
   list_node<Type>* tail_node;
      unsigned long list_size;

};

//***************************************************************************//
//*                                                                         *//
//* list<Type>::list(const list& rhs)                                       *//
//*                                                                         *//
//* Function Description: This is the copy constructor for the "list<Type>" *//
//*                       class. In this functions, we copy the data from   *//
//*                       the "rhs" to the new list. This is done to prevent*//
//*                       to prevent dangling pointers if "rhs" were to go  *//
//*                       out of scope and delete it's dynamic data.        *// 
//*                                                                         *//
//* Input Domain     : rhs -> {a valid list<Type>}                          *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

template<class Type>
list<Type>::list(const list& rhs):list_size(0),head_node(NULL),tail_node(NULL){

   list_iterator<Type> copyIter;

   copyIter = rhs.begin();

   for(unsigned long i = 0; i < rhs.size();i++){
      this->push_back(copyIter.this_node());
      copyIter++;
  }

}

//***************************************************************************//
//*                                                                         *//
//* list<Type>::~list(const list& rhs)                                      *//
//*                                                                         *//
//* Function Description: The destructor de-allocates al the dynamic data   *//
//*                       nodes created during its lifetime.                *//
//*                                                                         *//
//* Input Domain     : No variables passed                                  *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

template<class Type>
list<Type>::~list(){

   list_iterator<Type> helper;

   helper.current_node = head_node;

   while(empty() == false){
      erase(helper);
   }
}

//***************************************************************************//
//*                                                                         *//
//* list<Type>::push_back(const Type& newData)                              *//
//*                                                                         *//
//* Function Description: This functions pushes a new data node onto the    *//
//*                       end of the linked list.                           *//
//*                                                                         *//
//* Input Domain     : newData -> {a non-NULL data node of type Type}       *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

template<class Type>
void
list<Type>::push_back(const Type& newData){

   if(head_node == NULL){
      head_node = new list_node<Type>(newData);
      tail_node = head_node;
   }
   else{
      list_node<Type>* temp = new list_node<Type>(newData);
      temp->previous = tail_node;
      tail_node->next = temp;
      tail_node = temp;
   }

   list_size ++;

}

//***************************************************************************//
//*                                                                         *//
//* list<Type>::erase(list_iterator<Type>& location)                        *//
//*                                                                         *//
//* Function Description: This function removes the data in the list        *//
//*                       pointed to by "location". The iterator is set     *//
//*                       to point to the node after the deleted node.      *//
//*                       The head nodes and tail nodes are updated         *//
//*                       accordingly.                                      *// 
//*                                                                         *//
//* Input Domain     : location -> {an iterator pointing to an element in   *//
//*                                 this linked list}                       *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

template<class Type>
void
list<Type>::erase(list_iterator<Type>& location){

   list_node<Type>* temp;

   if(location.current_node != NULL){

      if(location.current_node->next != NULL){
         location.current_node->next->previous = location.current_node->previous;
         temp = location.current_node->next;
      }
      else {
         tail_node = tail_node->previous;
         temp = NULL;
      }


      if(location.current_node->previous != NULL){
         location.current_node->previous->next = location.current_node->next;

      }
      else {
         head_node = head_node->next;
         temp = head_node;
      }

      delete  location.current_node;
      location.current_node = temp;

      list_size --;
   }
   else
      exit(1);

}

#endif /* LIST_H */
