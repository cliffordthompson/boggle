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
//* list_node<Type>                                                         *//
//*                                                                         *//
//* Class Description : This class provides a very basic structure for      *//
//*                     nodes in a doubly linked list. The data cannot be   *//
//*                     accessed unless by the friend classes "list" and    *//
//*                     "list_iterator".                                    *//
//*                                                                         *//
//* Exceptions Thrown : {None Thrown}                                       *//
//*                                                                         *//
//* File          : list_node.h                                             *//
//* Author        : Clifford Thompson                                       *//
//* Creation Date : July 15, 2004                                           *//
//*                                                                         *//
//***************************************************************************//

#ifndef LIST_NODE_H
#define LIST_NODE_H

/*                                                     */
/* some forward declarations of list and list_iterator */
/*                                                     */

template<class Type> class list;
template<class Type> class list_iterator;

template<class Type>
class list_node {

private:

   list_node<Type>(const Type& newData):data(newData),next(NULL),previous(NULL){}; 

   Type data;
   list_node<Type>* next;
   list_node<Type>* previous;

   friend class list<Type>;
   friend class list_iterator<Type>;

};
  
#endif /* LIST_NODE_H */
