//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "StaticArray\StaticArray1.hpp"
#include "List\List0.hpp"
#include "List\List1.hpp"
#include "List\List2.hpp"


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef List2 <Text> TextList;
enum {lowerBound = 1, upperBound = 7};
typedef StaticArray1<TextList, lowerBound, upperBound> ListArray;
#else
// Compiling in Debug configuration
#include "List\ListChecking.hpp"
#include "StaticArray\StaticArrayChecking.hpp"
typedef ListChecking1 <Text, List1 <Text>> TextList;
enum {lowerBound = 1, upperBound = 7};
typedef StaticArrayChecking1<TextList, lowerBound, upperBound, StaticArray1<TextList, lowerBound, upperBound>> ListArray;
#endif

//-------------------------------------------------------------------
// program constants
//-------------------------------------------------------------------

void displayMenu (void)
{
	wcout << endl;
	wcout << "---------------------------------------------" << endl;
	wcout << endl;
	wcout << "     Command -  Result" << endl;
	wcout << "        g - toggle display menu" << endl;
	wcout << "        e - addRightFront" << endl;
	wcout << "        d - removeRightFront" << endl;
	wcout << "        r - replaceRightFront" << endl;
	wcout << "        f - rightFront" << endl;
	wcout << "        a - advance" << endl;
	wcout << "        < - moveToStart" << endl;
	wcout << "        > - moveToFinish" << endl;
	wcout << "        s - swapRights" << endl;
	wcout << "        ( - leftLength" << endl;
	wcout << "        ) - rightLength" << endl;
	wcout << "        x - transferFrom" << endl;
	wcout << "        = - copy" << endl;
	wcout << "        l - load from file" << endl;
	wcout << "        o - output to file" << endl;
	wcout << "        p - display" << endl;
	wcout << "        c - clear" << endl;
	wcout << "        q - quit program" << endl;
	wcout << endl;
	wcout << "---------------------------------------------" << endl;
	wcout << endl << "        command:";
}	// showMenu

//-------------------------------------------------------------------

void holdScreen (void)
{
	Text x;

	wcout << "Type Return to continue." << endl;
	wcin >> x;
}	// holdScreen

//-------------------------------------------------------------------

void getCommand (
		Character& command
	)
{
	wcin >> command;
	wcout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex (ListArray& sa)
{
	Integer index, lb, ub;

	sa.getBounds(lb, ub);

	do {
		wcout << "which List? " << lb << ".." << ub << ":";
		wcin >> index;
	} while ((index < lb) || (index > ub));
	wcout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

void getText (Text& s)
{
	wcout << "Enter text string:";
	wcin >> s;
}	// getText

//-------------------------------------------------------------------

void doAddRightFront (ListArray& sa)
{
	Integer i;
	Text x;

	wcout << "Add right to ";
	i = getIndex(sa);
	getText(x);
	sa[i].addRightFront(x);
	wcout << endl << "s" << i << ".addRightFront(x); executed." << endl;
	wcout << "x = " << x << endl;
}	// doAddRightFront

//-------------------------------------------------------------------

void doRemoveRightFront (ListArray& sa)
{
	Integer i, z;
	Text x;

	wcout << "Remove right from ";
	i = getIndex(sa);
	z = sa[i].rightLength();
	if (z > 0) {
		sa[i].removeRightFront(x);
	} // end if
	if (z > 0) {
		wcout << endl << "s" << i << ".removeRightFront(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot remove right from an empty s" << i << ".right." << endl;
	} // end if
}	// doRemoveRightFront

//-------------------------------------------------------------------

void doReplaceRightFront (ListArray& sa)
{
	Integer i, z;
	Text x;

	wcout << "Replace right front of ";
	i = getIndex(sa);
	getText(x);
	z = sa[i].rightLength();
	if (z > 0) {
		sa[i].replaceRightFront(x);
	} // end if
	if (z > 0) {
		wcout << endl << "s" << i << ".replaceRightFront(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot replace right front from an empty s" << i << ".right." << endl;
	} // end if
}	// doReplaceRightFront


//-------------------------------------------------------------------

void doRightFront (ListArray& sa)
{
	Integer i;

	wcout << "Access right front ";
	i = getIndex(sa);
	if (sa[i].rightLength() > 0) {
		wcout << "s" << i << ".rightFront() = " << sa[i].rightFront() << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - cannot access an empty s" << i << ".right." << endl;
	} // end if
}	// doRightFront

//-------------------------------------------------------------------

void doAdvance (ListArray& sa)
{
	Integer i, z;

	wcout << "Advance ";
	i = getIndex(sa);
	z = sa[i].rightLength();
	if (z > 0) {
		sa[i].advance();
	} // end if
	if (z > 0) {
		wcout << "s" << i << ".advance(); executed." << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot advance on an empty s" << i << ".right." << endl;
	} // end if
}	// doAdvance

//-------------------------------------------------------------------

void doMoveToStart (ListArray& sa)
{
	Integer i;

	wcout << "Move to start ";
	i = getIndex(sa);
	sa[i].moveToStart();
	wcout << "s" << i << ".moveToStart(); executed." << endl;
}	// doMoveToStart

//-------------------------------------------------------------------

void doMoveToFinish (ListArray& sa)
{
	Integer i;

	wcout << "Move to finish ";
	i = getIndex(sa);
	sa[i].moveToFinish();
	wcout << "s" << i << ".moveToFinish(); executed." << endl;
}	// doMoveToFinish

//-------------------------------------------------------------------

void doSwapRights (ListArray& sa)
{
	Integer i1, i2;

	wcout << "Swap rights ";
	i1 = getIndex(sa);
	do {
		wcout << "with ";
		i2 = getIndex(sa);
	} while (i1 == i2);
	sa[i1].swapRights(sa[i2]);
	wcout << endl << "s" << i1 << ".swapRights(s" << i2 << "); executed." << endl;
}	// doSwapRights

//-------------------------------------------------------------------

void doLeftLength (ListArray& sa)
{
	Integer i, lz;

	wcout << "Left length of ";
	i = getIndex(sa);
	lz = sa[i].leftLength();
	wcout << "|s" << i << ".left| = " << lz << endl;
}	// doLeftLength

//-------------------------------------------------------------------

void doRightLength (ListArray& sa)
{
	Integer i, rz;

	wcout << "Right length of ";
	i = getIndex(sa);
	rz = sa[i].rightLength();
	wcout << "|s" << i << ".right| = " << rz << endl;
}	// doRightLength

//-------------------------------------------------------------------

void doTransferFrom(ListArray& sa)
{
	Integer i1, i2;

	wcout << "Transfer from ";
	i1 = getIndex(sa);
	do {
		wcout << "to ";
		i2 = getIndex(sa);
	} while (i1 == i2);
	sa[i2].transferFrom(sa[i1]);
	wcout << endl << "s" << i2 << ".transferFrom(s" << i1 << "); executed." << endl;
}	// doTransferFrom

//-------------------------------------------------------------------

void doCopy (ListArray& sa)
{
	Integer i1, i2;

	wcout << "Copy ";
	i1 = getIndex(sa);
	do {
		wcout << "to ";
		i2 = getIndex(sa);
	} while (i1 == i2);
	sa[i2] = sa[i1];
	wcout << endl << "s" << i2 << " = s" << i1 << "; executed." << endl;
}	// doCopy

//-------------------------------------------------------------------

void doDisplay (ListArray& sa)
{
	Integer i;

	wcout << "Display ";
	i = getIndex(sa);
	wcout << "s" << i << " = ";
	wcout << sa[i] << endl;
	wcout << endl;
}	// doDisplay

//-------------------------------------------------------------------

void doClear (ListArray& sa)
{
	Integer i;

	wcout << "Clear ";
	i = getIndex(sa);
	sa[i].clear();
	wcout << endl << "s" << i << ".clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile (ListArray& sa)
{
	Boolean successful;
	Integer size, index;
	Text filename, x;
	File input;
	TextList s;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		input.read(size, successful);
		for (int i = 0; i < size; i++) {
			input.read(x, successful);
			s.addRightFront(x);
		}	// end for
		input.closeFile(successful);

		wcout << "Load file into ";
		index = getIndex(sa);
		sa[index].transferFrom(s);
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile (ListArray& sa)
{
	Boolean successful;
	Integer lz, z, index;
	Text filename;
	File output;
	TextList s;

	// get file name from user
	// open file for writing
	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	output.openFile(filename, File::openForWrite, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		// find out from which List to output contents.
		wcout << "Output from ";
		index = getIndex(sa);

		// transfer contents of chosen List into local s.
		s.transferFrom(sa[index]);


		// write to file:
		// 1) write an Integer telling how many items are in s
		// 2) write each item found in s
		// note: 
		// after loop has finished, s must contain
		// the same values as before, in same order with fence in same position.
		lz = s.leftLength();
		s.moveToStart();
		z = s.rightLength();
		output.write(z, successful);
		for (int i = 0; i < z; i++) {
			output.write(s.rightFront(), successful);
			s.advance();
		}	// end for
		output.closeFile(successful);

		// move fence back into original position
		s.moveToStart();
		for (int i = 0; i < lz; i++) {
			s.advance();
		}	// end for

		// transfer the contents of local s back into original list
		sa[index].transferFrom(s);
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		Character command,
		Boolean& showMenu,
		ListArray& sa
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doAddRightFront(sa);
			break;
		case 'd':
			doRemoveRightFront(sa);
			break;
		case 'r':
			doReplaceRightFront(sa);
			break;
		case 'f':
			doRightFront(sa);
			break;
		case 'a':
			doAdvance(sa);
			break;
		case '<':
			doMoveToStart(sa);
			break;
		case '>':
			doMoveToFinish(sa);
			break;
		case 's':
			doSwapRights(sa);
			break;
		case '(':
			doLeftLength(sa);
			break;
		case ')':
			doRightLength(sa);
			break;
		case 'x':
			doTransferFrom(sa);
			break;
		case '=':
			doCopy(sa);
			break;
		case 'l':
			inputFromFile(sa);
			break;
		case 'o':
			outputToFile(sa);
			break;
		case 'p':
			doDisplay(sa);
			break;
		case 'c':	
			doClear(sa);
			break;
		case '@':
			wcout << "Authored by Dr. Holly" << endl;
			break;
		case 'q':
			wcout << "Quit Command Interpreter" << endl;
			break;
		default:
			wcout << "Unknown command: " << command << endl;
			wcout << "Please reenter your command" << endl;
			break;
	}	// end switch
}	// dispatchCommand

//-------------------------------------------------------------------

void commandController (
		ListArray& sa,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, sa);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	ListArray sa;

	commandController (sa, showMenu);
	wcout << "end program" << endl;
	return 0;
}	// end main
