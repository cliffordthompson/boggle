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
//* Boggler Program                                                         *//
//*                                                                         *//
//* Program Description : This program accepts two arguments. The first     *//
//*                       is a string of 16 letters which represent the     *//
//*                       letters of the boggle grid. The second argument   *//
//*                       specifies the file containing a list of valid     *//
//*                       words. The 16 puzzle characters specify the       *//
//*                       puzzle configuration start at top row and moving  *//
//*                       left to right. For example:                       *//
//*                                                                         *//
//*                       ahpmltorvsewmcdu                                  *//
//*                                                                         *//
//*                       is equivalent to:                                 *//
//*                                                                         *//
//*                       a h p m                                           *//
//*                       l t o r                                           *//
//*                       v s e w                                           *//
//*                       m c d u                                           *//
//*                                                                         *//
//* Usage  %boggler <puzzle> <file>                                         *//
//*                                                                         *//
//* Exceptions Thrown : {None Thrown}                                       *//
//*                                                                         *//
//* File          : main.cpp                                                *//
//* Author        : Clifford Thompson                                       *//
//* Creation Date : July 15, 2004                                           *//
//*                                                                         *//
//***************************************************************************//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "boggler.h"

#define PUZZLE_ARG    1
#define FILE_ARG      2

int main(int argc, char* argv[]){

  Boggler hamBoggler;

  if(argc != 3){
    printf("Usage: boggler <puzzle> <file>\n");
    exit(1);
  }

 
  hamBoggler.setPuzzle(argv[PUZZLE_ARG]);   /* read in the puzzle          */
  hamBoggler.setDictionary(argv[FILE_ARG]); /* read in the file            */
  hamBoggler.solvePuzzle();                 /* solve puzzle, print results */


  return 0;
}
