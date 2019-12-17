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
//* list_interator<Type>                                                    *//
//*                                                                         *//
//* Class Description : This class provides a very basic structure for      *//
//*                     iterating accross nodes of type "list_node<Type>".  *//
//*                     The "list<Type>" class has access to this class     *//
//*                     through friendship.                                 *//
//*                                                                         *//
//*                     NOTE: The class definition is also included in this *//
//*                           file because it is required for templated     *//
//*                           classes.                                      *//
//*                                                                         *//
//* Exceptions Thrown : {None Thrown}                                       *//
//*                                                                         *//
//* File          : list_iterator.h                                         *//
//* Author        : Clifford Thompson                                       *//
//* Creation Date : July 15, 2004                                           *//
//*                                                                         *//
//***************************************************************************//

#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include <stdio.h>

#include "list_node.h"

template<class Type>
class list_iterator{

public:

   list_iterator<Type>():current_node(NULL){};

   Type& this_node(){return current_node->data;};     /* return data at current node */

   bool isNull(){return (current_node == NULL);};

   list_iterator<Type>& operator ++();
   list_iterator<Type>& operator ++(int);
   list_iterator<Type>& operator --();
   list_iterator<Type>& operator --(int);


private:

   list_iterator<Type>(list_node<Type>* newNode):current_node(newNode){};

   list_node<Type>* current_node;

   friend class list<Type>; 

};

//***************************************************************************//
//*                                                                         *//
//* list_iterator& list_iterator::operator ++()                             *//
//*                                                                         *//
//* Function Description: This function makes the list iterator point to    *// 
//*                       the next node in the list. If the iterator is     *//
//*                       currently NULL, the program exits.                *//
//*                                                                         *//
//*                       NOTE: this is the pre-increment version of ++     *//
//*                                                                         *//
//* Input Domain     : No variable passed                                   *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

template<class Type>
list_iterator<Type>&
list_iterator<Type>::operator ++(){

   if(current_node != NULL)
      current_node = current_node->next;
   else
      exit(1);

   return *this;

}

//***************************************************************************//
//*                                                                         *//
//* list_iterator& list_iterator::operator ++(int dummy)                    *//
//*                                                                         *//
//* Function Description: This function makes the list iterator point to    *// 
//*                       the next node in the list. If the iterator is     *//
//*                       currently NULL, the program exits.                *//
//*                                                                         *//
//*                       NOTE: this is the post-increment version of ++    *//
//*                                                                         *//
//* Input Domain     : dummy -> {value not used}                            *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

template<class Type>
list_iterator<Type>&
list_iterator<Type>::operator ++(int dummy){

   if(current_node != NULL)
      current_node = current_node->next;
   else
      exit(1);

   return *this;

}

//***************************************************************************//
//*                                                                         *//
//* list_iterator& list_iterator::operator --()                             *//
//*                                                                         *//
//* Function Description: This function makes the list iterator point to    *// 
//*                       the previous node in the list. If the iterator is *//
//*                       currently NULL, the program exits.                *//
//*                                                                         *//
//*                       NOTE: this is the pre-decrement version of --     *//
//*                                                                         *//
//* Input Domain     : No variable passed                                   *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//


template<class Type>
list_iterator<Type>&
list_iterator<Type>::operator --(){

   if(current_node != NULL)
      current_node = current_node->previous;
   else
      exit(1);

   return *this;
}

//***************************************************************************//
//*                                                                         *//
//* list_iterator& list_iterator::operator --(int dummy)                    *//
//*                                                                         *//
//* Function Description: This function makes the list iterator point to    *// 
//*                       the previous node in the list. If the iterator is *//
//*                       currently NULL, the program exits.                *//
//*                                                                         *//
//*                       NOTE: this is the post-decrement version of --    *//
//*                                                                         *//
//* Input Domain     : dummy -> {value not used}                            *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//


template<class Type>
list_iterator<Type>&
list_iterator<Type>::operator --(int dummy){

   if(current_node != NULL)
      current_node = current_node->previous;
   else
      int x =0;
      /*exit(1); */

   return *this;
}


#endif /* LIST_ITERATOR_H*/
