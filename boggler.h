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
//* Boggler                                                                 *//
//*                                                                         *//
//* Class Description : This class provides a data structure to encapsulate *//
//*                     the functionality required to store/manipulate      *//
//*                     a given the boggle puzzles.                         *//
//*                                                                         *//
//* Exceptions Thrown : {None Thrown}                                       *//
//*                                                                         *//
//* File          : boggler.h                                               *//
//* Author        : Clifford Thompson                                       *//
//* Creation Date : July 15, 2004                                           *//
//*                                                                         *//
//***************************************************************************//

#ifndef BOGGLER_H
#define BOGGLER_H

#define PUZZLE_SIZE  16

#include <string.h> /* C string manipulation */

#include "list.h"
 
class Boggler{

  /*                                                             */
  /* BoggleWord is only used by Boggler, so we'll define it here */
  /*                                                             */

  struct BoggleWord{
    BoggleWord(){memset(word,0,sizeof(word)); found = false;};
    char word[17];
    bool found;
  };

public:

  Boggler();

  void setPuzzle(char* newPuzzle);
  void setDictionary(char* fileName);
  void solvePuzzle();

private:

  void solvePuzzle(list<BoggleWord*> openWordList, const short x, const short y);

  char gridPieces[4][4];
  bool closedLetterList[4][4];
  char currentSequence[17];

  unsigned long nodesChecked;

  list<BoggleWord> dictionary;
  list<BoggleWord*> foundList;
  

};

#endif /* BOGGLER_H */
