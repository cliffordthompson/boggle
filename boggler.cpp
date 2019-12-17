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
//*                     the functionality required to store, manipulate     *//
//*                     and solve a give Boggle puzzle.                     *//
//*                                                                         *//
//* Exceptions Thrown : {None Thrown}                                       *//
//*                                                                         *//
//* File          : boggler.cpp                                             *//
//* Author        : Clifford Thompson                                       *//
//* Creation Date : July 15, 2004                                           *//
//*                                                                         *//
//***************************************************************************//

#include "boggler.h"

#include <string.h> /* C string manipulation */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//***************************************************************************//
//*                                                                         *//
//* Boggler::Boggler()                                                      *//
//*                                                                         *//
//* Function Description: In this constructor, all the members variables    *//
//*                       are initialized to ensure consistancy. The puzzle *//
//*                       is set to be all 'a's                             *//
//*                                                                         *//
//* Input Domain     : No variable passed                                   *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

Boggler::Boggler():nodesChecked(0){

  memset(gridPieces,'a',sizeof(gridPieces));
  memset(closedLetterList,false,sizeof(closedLetterList));
  memset(currentSequence,0,sizeof(currentSequence));

}


//***************************************************************************//
//*                                                                         *//
//* Boggler::setPuzzle(char* newPuzzle)                                     *//
//*                                                                         *//
//* Function Description: This function is used to set the current boggle   *//
//*                       puzzle configuration. Checking is performed for   *//
//*                       the length of the puzzle. A check is also done    *//
//*                       to make sure the puzzle only contains alphabet    *//
//*                       characters. The program will exit if these two    *//
//*                       conditions are not met.                           *//
//*                                                                         *//
//* Input Domain     : newPuzzle -> {any character array pointer}           *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

void
Boggler::setPuzzle(char* newPuzzle){


  if(strlen(newPuzzle) != PUZZLE_SIZE){
    printf("\nboggler: puzzle must contain 16 alphabet characters\n\n");
    exit(1);
  }
   
  for(int i = 0; i < PUZZLE_SIZE; i++){
    if(isalpha(newPuzzle[i]) == false){
      printf("\nboggler: puzzle must only contain alphabet characters\n\n");
      exit(1);
    }
  }
  

  for(int y = 0 ; y < 4; y++){
    for(int x = 0; x < 4; x++)
      gridPieces[y][x] = newPuzzle[y*4 + x];  
  }

 
}

//***************************************************************************//
//*                                                                         *//
//* Boggler::setDictionary(char* fileName)                                  *//
//*                                                                         *//
//* Function Description: This function loads the words contained in the    *//
//*                       file "fileName" into the "dictionary" list. The   *//
//*                       file checked to see if it exists. As well, if a   *//
//*                       word is longer than 16 characters, it is not      *//
//*                       added to the dictionary. A tally of the excessive *//
//*                       length words is kept and printed after the        *//
//*                       dictionary is read in.                            *//
//*                                                                         *//
//* Input Domain     : fileName -> {any character array pointer}            *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

void
Boggler::setDictionary(char* fileName){

  FILE* filePtr  = NULL;
  char* fileWord = new char[64];
  BoggleWord newWord;
  unsigned long tooLongCount = 0;

  memset(fileWord,0,sizeof(char[64]));

  filePtr = fopen(fileName,"r");

  if(filePtr == NULL){
    printf("\nboggler: cannot open \"%s\"\n\n",fileName); /* file doesn't exist */
    exit(1);
  }

  printf("\n|----- Reading Dictionary from \"%s\" -----|\n\n",fileName);

  while((fileWord = fgets(fileWord,64,filePtr)) != NULL){

    fileWord[strlen(fileWord)-1] = '\0'; /* remove '\n' character */

    if(fileWord[strlen(fileWord)-1] == '\r')
      fileWord[strlen(fileWord)-1] = '\0'; /* remove '\r' character on UNIX/Linux */
 
    if(strlen(fileWord) < PUZZLE_SIZE+1){
      strcpy(newWord.word,fileWord);
      dictionary.push_back(newWord);
    }
    else{
      tooLongCount++ ;
    }

    memset(fileWord,0,sizeof(char[64]));
    memset(&newWord,0,sizeof(BoggleWord));
  }

  printf(" %lu word(s) had length greater than 16.\n\n",tooLongCount);
  
  
  fclose(filePtr);
  delete[] fileWord;

}

//***************************************************************************//
//*                                                                         *//
//* Boggler::solvePuzzle()                                                  *//
//*                                                                         *//
//* Function Description: This function is used to solve the current puzzle *//
//*                       with the current dictionary. If the dictionary    *//
//*                       contains no words, we exit immediately, otherwise *//
//*                       we call the recursive version of "solvePuzzle".   *//
//*                       If solutions are found, they are printed to the   *//
//*                       standard output. The number of nodes examined in  *//
//*                       the search tree is also printed.                  *//
//*                                                                         *//
//* Input Domain     : No variable passed                                   *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

void
Boggler::solvePuzzle(){

  list<BoggleWord*> openWordList;
  list_iterator<BoggleWord> dictIter;
  list_iterator<BoggleWord*> foundIter;

  if(dictionary.size() == 0){
    printf("|----- 0 solutions found, 0 node(s) examined -----|\n\n");
    return;
  }

  dictIter = dictionary.begin();

  for(unsigned long i = 0; i < dictionary.size(); i++){
    openWordList.push_back(&dictIter.this_node());
    dictIter ++;
  }


  for(int y = 0 ; y < 4; y++){
    for(int x = 0; x < 4; x++){
      printf(" Searching %c at (%i,%i)\n", gridPieces[y][x],x,y);
      solvePuzzle(openWordList,x,y);
    }    
  }

  if(foundList.size() != 0){
      
    foundIter = foundList.begin();
    printf("\n|----- The following solutions were found -----|\n\n");

    for(unsigned long i = 0; i < foundList.size(); i++){
      printf(" %s\n",foundIter.this_node()->word);
      foundIter++;
    }
  }

  printf("\n|----- %i solution(s) found, %lu node(s) examined -----|\n\n",foundList.size(),nodesChecked);

}

//***************************************************************************//
//*                                                                         *//
//* Boggler::solvePuzzle(list<BoggleWord*> openWordList, const short x,     *//
//*                                                      const short y      *//
//*                                                                         *//
//*                                                                         *//
//* Function Description: This is the recursive function that is called to  *//
//*                       to solve the current puzzle. Essentially, the     *//
//*                       function performs a pre-order traversal of the    *//
//*                       puzzle to find valid solutions. The algorithm     *//
//*                       optimizes the search by pruning the search tree   *//
//*                       of sequences that cannot create solutions.        *//
//*                       The list of possible candidate words is passed    *//
//*                       during each successive recursive call.            *//
//*                                                                         *//
//* Input Domain     : openWordList -> {valid pointers to "BoggleWord"s     *//
//*                    x,y          -> {any short integer}                  *//
//*                                                                         *//
//* Output Domain    : No variables returned                                *//
//* Exception Domain : No exceptions thrown                                 *//
//*                                                                         *//
//***************************************************************************//

void
Boggler::solvePuzzle(list<BoggleWord*> openWordList, const short x, const short y){

  size_t sequenceSize = 0;
  unsigned long openListSize = 0;
  list_iterator<BoggleWord*> openIter ;
  list<BoggleWord*> childOpenWordList ;

  /*                                 */
  /* Check for valid x,y coordinates */
  /*                                 */

  if(x < 0 || x > 3 || y < 0 || y > 3)
    return;


  /*                                                 */
  /* First determine if letter has already been used */
  /*                                                 */


  if(closedLetterList[y][x] == true) 
    return;                           

  nodesChecked++;

  sequenceSize = strlen(currentSequence);
  openListSize = openWordList.size();

  currentSequence[sequenceSize]   = gridPieces[y][x];
  currentSequence[sequenceSize+1] = '\000';

  sequenceSize++;

  openIter = openWordList.begin();

  /*                                                        */
  /* Remove non-candidate words and place in child openlist */
  /*                                                        */

  for(unsigned long i = 0; i < openListSize;i++){
    if(openIter.this_node()->word[sequenceSize-1] == gridPieces[y][x]){
      childOpenWordList.push_back(openIter.this_node());
    }
    openIter++;
  }
     
  /*                                                     */
  /* Check for completed words by checking the length of */
  /* each word in child list                             */
  /*                                                     */

  openListSize = childOpenWordList.size();
  openIter     = childOpenWordList.begin();

  for(unsigned long i = 0; i < openListSize ; i++){
   if((strlen(openIter.this_node()->word) == sequenceSize) && (openIter.this_node()->found) == false){
      foundList.push_back(openIter.this_node());
      openIter.this_node()->found = true;
   }
   openIter++;
  }

  /*                                                */  
  /* If open list is empty, current sequence is not */
  /* a prefix of any word in the dictionary         */
  /*                                                */


  if(childOpenWordList.empty() == true){
    currentSequence[sequenceSize-1] = '\0'; /* remove letter from current sequence */
    sequenceSize--;
    return;
  }

  /*                                                 */
  /* Check neighbours because candidate words exists */
  /*                                                 */


  closedLetterList[y][x] = true;          /* set letter as being used */
  
  solvePuzzle(childOpenWordList,x-1,y-1); /* NW neighbour */
  solvePuzzle(childOpenWordList,x-1,y);   /* W  neighbour */
  solvePuzzle(childOpenWordList,x-1,y+1); /* SW neighbour */
  solvePuzzle(childOpenWordList,x,y+1);   /* S  neighbour */
  solvePuzzle(childOpenWordList,x+1,y+1); /* SE neighbour */
  solvePuzzle(childOpenWordList,x+1,y);   /* E  neighbour */
  solvePuzzle(childOpenWordList,x+1,y-1); /* NE neighbour */
  solvePuzzle(childOpenWordList,x,y-1);   /* N  neighbour */

  closedLetterList[y][x] = false;        
  currentSequence[sequenceSize-1] = '\0'; /* remove letter from current sequence */ 
  sequenceSize--;
}


/*                                                */
/*************** End of boggler.cpp ***************/
/*                                                */
