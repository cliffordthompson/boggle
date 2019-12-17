# =========================================================================
#
#  Copyright (c) 2004-2019 Clifford Thompson
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# =========================================================================

.SUFFIXES: .cpp $(SUFFIXES)
CPPFLAGS = -O
DEBUG = -g3 -Q -Wall
PROGRAM = boggler

$(PROGRAM)  : boggler.o main.o 
	g++ $(CPPFLAGS) -o $(PROGRAM) boggler.o main.o 

debug : boggler.o main.o
	g++ $(DEBUG) -o $(PROGRAM) boggler.o main.o

.cpp.o:
	g++ $(CPPFLAGS) -c $<

clean :
	-rm *.o *~ $(PROGRAM)