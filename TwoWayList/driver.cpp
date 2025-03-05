//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "TwoWayList\TwoWayList1.hpp"


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef TwoWayList1 <Text> TextList;
#else
// Compiling in Debug configuration
#include "TwoWayList\TwoWayListChecking.hpp"
typedef TwoWayListChecking1 <Text, TwoWayList1 <Text>> TextList;
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
	wcout << "        b - retreat" << endl;
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

Integer getIndex (void)
{
	Integer index;

	do {
		wcout << "which List? 1 or 2:";
		wcin >> index;
	} while ((index < 1) || (index > 2));
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

void doAddRightFront (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;
	Text x;

	wcout << "Add right to ";
	i = getIndex();
	getText(x);
	if (i == 1) {
		s1.addRightFront(x);
	} else {
		s2.addRightFront(x);
	}	// end if
	wcout << endl << "s" << i << ".addRightFront(x); executed." << endl;
	wcout << "x = " << x << endl;
}	// doAddRightFront

//-------------------------------------------------------------------

void doRemoveRightFront (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, z;
	Text x;

	wcout << "Remove right from ";
	i = getIndex();
	if (i == 1) {
		z = s1.rightLength();
		if (z > 0) {
			s1.removeRightFront(x);
		} // end if
	} else {
		z = s2.rightLength();
		if (z > 0) {
			s2.removeRightFront(x);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "s" << i << ".removeRightFront(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot remove right from an empty s" << i << ".right." << endl;
	} // end if
}	// doRemoveRightFront

//-------------------------------------------------------------------

void doReplaceRightFront (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, z;
	Text x;

	wcout << "Replace right front of ";
	i = getIndex();
	getText(x);
	if (i == 1) {
		z = s1.rightLength();
		if (z > 0) {
			s1.replaceRightFront(x);
		} // end if
	} else {
		z = s2.rightLength();
		if (z > 0) {
			s2.replaceRightFront(x);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "s" << i << ".replaceRightFront(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot replace right front from an empty s" << i << ".right." << endl;
	} // end if
}	// doReplaceRightFront


//-------------------------------------------------------------------

void doRightFront (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Access right front ";
	i = getIndex();
	if (i == 1) {
		if (s1.rightLength() > 0) {
			wcout << "s1.rightFront() = " << s1.rightFront() << endl;
		} else {
			wcout << "Error: |s1.right| = 0 - cannot access an empty s1.right." << endl;
		} // end if
	} else {
		if (s2.rightLength() > 0) {
			wcout << "s2.rightFront() = " << s2.rightFront() << endl;
		} else {
			wcout << "Error: |s2.right| = 0 - cannot access an empty s2.right." << endl;
		} // end if
	}	// end if
}	// doRightFront

//-------------------------------------------------------------------

void doAdvance (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, z;

	wcout << "Advance ";
	i = getIndex();
	if (i == 1) {
		z = s1.rightLength();
		if (z > 0) {
			s1.advance();
		} // end if
	} else {
		z = s2.rightLength();
		if (z > 0) {
			s2.advance();
		} // end if
	}	// end if
	if (z > 0) {
		wcout << "s" << i << ".advance(); executed." << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot advance on an empty s" << i << ".right." << endl;
	} // end if
}	// doAdvance

//-------------------------------------------------------------------

void doRetreat (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, z;

	wcout << "Retreat ";
	i = getIndex();
	if (i == 1) {
		z = s1.leftLength();
		if (z > 0) {
			s1.retreat();
		} // end if
	} else {
		z = s2.leftLength();
		if (z > 0) {
			s2.retreat();
		} // end if
	}	// end if
	if (z > 0) {
		wcout << "s" << i << ".retreat(); executed." << endl;
	} else {
		wcout << "Error: |s" << i << ".left| = 0 - ";
		wcout << "cannot retreat on an empty s" << i << ".left." << endl;
	} // end if
}	// doRetreat

//-------------------------------------------------------------------

void doMoveToStart (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Move to start ";
	i = getIndex();
	if (i == 1) {
		s1.moveToStart();
	} else {
		s2.moveToStart();
	}	// end if
	wcout << "s" << i << ".moveToStart(); executed." << endl;
}	// doMoveToStart

//-------------------------------------------------------------------

void doMoveToFinish (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Move to finish ";
	i = getIndex();
	if (i == 1) {
		s1.moveToFinish();
	} else {
		s2.moveToFinish();
	}	// end if
	wcout << "s" << i << ".moveToFinish(); executed." << endl;
}	// doMoveToFinish

//-------------------------------------------------------------------

void doSwapRights (
		TextList& s1,
		TextList& s2
	)
{
	s1.swapRights(s2);
	wcout << endl << "s1.swapRights(s2); executed." << endl;
}	// doSwapRights

//-------------------------------------------------------------------

void doLeftLength (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, lz;

	wcout << "Left length of ";
	i = getIndex();
	if (i == 1) {
		lz = s1.leftLength();
	} else {
		lz = s2.leftLength();
	}	// end if
	wcout << "|s" << i << ".left| = " << lz << endl;
}	// doLeftLength

//-------------------------------------------------------------------

void doRightLength (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, rz;

	wcout << "Right length of ";
	i = getIndex();
	if (i == 1) {
		rz = s1.rightLength();
	} else {
		rz = s2.rightLength();
	}	// end if
	wcout << "|s" << i << ".right| = " << rz << endl;
}	// doRightLength

//-------------------------------------------------------------------

void doTransferFrom(
		TextList& s1,
		TextList& s2
	)
{
	Integer index, z;

	wcout << "Transfer from ";
	index = getIndex();
	if (index == 1) {
		s2.transferFrom(s1);
		wcout << endl << "s2.transferFrom(s1); executed." << endl;
	} else {
		s1.transferFrom(s2);
		wcout << endl << "s1.transferFrom(s2); executed." << endl;
	} // end if
}	// doTransferFrom

//-------------------------------------------------------------------

void doCopy (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Copy ";
	i = getIndex();
	if (i == 1) {
		s2 = s1;
		wcout << "s2 = s1; executed." << endl;
	} else {
		s1 = s2;
		wcout << "s1 = s2; executed." << endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void doDisplay (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Display ";
	i = getIndex();
	wcout << "s" << i << " = ";
	if (i == 1) {
		wcout << s1 << endl;
	} else {
		wcout << s2 << endl;
	}	// end if
	wcout << endl;
}	// doDisplay

//-------------------------------------------------------------------

void doClear (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Clear ";
	i = getIndex();
	if (i == 1) {
		s1.clear();
	} else {
		s2.clear();
	}	// end if
	wcout << endl << "s" << i << ".clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile (
		TextList& s1,
		TextList& s2
	)
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
		index = getIndex();
		if (index == 1) {
			s1.transferFrom(s);
		} else {
			s2.transferFrom(s);
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile (
		TextList& s1,
		TextList& s2
	)
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
		index = getIndex();

		// transfer contents of chosen List into local s.
		if (index == 1) {
			s.transferFrom(s1);
		} else {
			s.transferFrom(s2);
		}	// end if

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
		if (index == 1) {
			s1.transferFrom(s);
		} else {
			s2.transferFrom(s);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		Character command,
		Boolean& showMenu,
		TextList& s1,
		TextList& s2
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doAddRightFront(s1, s2);
			break;
		case 'd':
			doRemoveRightFront(s1, s2);
			break;
		case 'r':
			doReplaceRightFront(s1, s2);
			break;
		case 'f':
			doRightFront(s1, s2);
			break;
		case 'a':
			doAdvance(s1, s2);
			break;		
		case 'b':
			doRetreat(s1, s2);
			break;
		case '<':
			doMoveToStart(s1, s2);
			break;
		case '>':
			doMoveToFinish(s1, s2);
			break;
		case 's':
			doSwapRights(s1, s2);
			break;
		case '(':
			doLeftLength(s1, s2);
			break;
		case ')':
			doRightLength(s1, s2);
			break;
		case 'x':
			doTransferFrom(s1, s2);
			break;
		case '=':
			doCopy(s1, s2);
			break;
		case 'l':
			inputFromFile(s1, s2);
			break;
		case 'o':
			outputToFile(s1, s2);
			break;
		case 'p':
			doDisplay(s1, s2);
			break;
		case 'c':	
			doClear(s1, s2);
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
		TextList& s1,
		TextList& s2,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, s1, s2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	TextList s1, s2;

	commandController (s1, s2, showMenu);
	wcout << "end program" << endl;
	return 0;
}	// end main


/*
//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "TwoWayList\TwoWayList1.hpp"

#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef TwoWayList1 <Text> TextList;
#else
// Compiling in Debug configuration
#include "TwoWayList\TwoWayListChecking.hpp"
typedef TwoWayListChecking1 <TwoWayList1, Text> TextList;
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
	wcout << "        g - Toggle display Menu" << endl;
	wcout << "        e - Add Right" << endl;
	wcout << "        d - Remove Right" << endl;
	wcout << "        [ - Access" << endl;
	wcout << "        a - Advance" << endl;
	wcout << "        r - Retreat" << endl;
	wcout << "        < - Move To Start" << endl;
	wcout << "        > - Move To Finish" << endl;
	wcout << "        s - Swap Rights" << endl;
	wcout << "        ( - Left Size" << endl;
	wcout << "        ) - Right Size" << endl;
	wcout << "        & - Swap" << endl;
	wcout << "        = - Copy" << endl;
	wcout << "        l - Load From File" << endl;
	wcout << "        o - Output To File" << endl;
	wcout << "        p - display" << endl;
	wcout << "        c - Clear" << endl;
	wcout << "        q - Quit Program" << endl;
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

Integer getIndex (void)
{
	Integer index;

	do {
		wcout << "which List? 1 or 2:";
		wcin >> index;
	} while ((index < 1) || (index > 2));
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

void doAddRight (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;
	Text x;

	wcout << "Add Right to ";
	i = getIndex ();
	getText (x);
	if (i == 1) {
		s1.addRight (x);
	} else {
		s2.addRight (x);
	}	// end if
	wcout << endl << "s" << i << ".addRight (x); executed." << endl;
	wcout << "x = " << x << endl;
}	// doAddRight

//-------------------------------------------------------------------

void doRemoveRight (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, z;
	Text x;

	wcout << "Remove Right from ";
	i = getIndex ();
	if (i == 1) {
		z = s1.rightSize ();
		if (z > 0) {
			s1.removeRight (x);
		} // end if
	} else {
		z = s2.rightSize ();
		if (z > 0) {
			s2.removeRight (x);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "s" << i << ".removeRight (x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot remove from an empty s" << i << ".right." << endl;
	} // end if
}	// doRemove

//-------------------------------------------------------------------

void doAccess (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Access ";
	i = getIndex ();
	if (i == 1) {
		if (s1.rightSize () > 0) {
			wcout << "s1[0] = " << s1[0] << endl;
		} else {
			wcout << "Error: |s1.right| = 0 - cannot access an empty s1.right." << endl;
		} // end if
	} else {
		if (s2.rightSize () > 0) {
			wcout << "s2[0] = " << s2[0] << endl;
		} else {
			wcout << "Error: |s2.right| = 0 - cannot access an empty s2.right." << endl;
		} // end if
	}	// end if
}	// doAccess

//-------------------------------------------------------------------

void doAdvance (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, z;

	wcout << "Advance ";
	i = getIndex ();
	if (i == 1) {
		z = s1.rightSize ();
		if (z > 0) {
			s1.advance ();
		} // end if
	} else {
		z = s2.rightSize ();
		if (z > 0) {
			s2.advance ();
		} // end if
	}	// end if
	if (z > 0) {
		wcout << "s" << i << ".advance (); executed." << endl;
	} else {
		wcout << "Error: |s" << i << ".right| = 0 - ";
		wcout << "cannot advance on an empty s" << i << ".right." << endl;
	} // end if
}	// doAdvance

//-------------------------------------------------------------------

void doRetreat (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, z;

	wcout << "Retreat ";
	i = getIndex ();
	if (i == 1) {
		z = s1.leftSize ();
		if (z > 0) {
			s1.retreat ();
		} // end if
	} else {
		z = s2.leftSize ();
		if (z > 0) {
			s2.retreat ();
		} // end if
	}	// end if
	if (z > 0) {
		wcout << "s" << i << ".retreat (); executed." << endl;
	} else {
		wcout << "Error: |s" << i << ".left| = 0 - ";
		wcout << "cannot retreat on an empty s" << i << ".left." << endl;
	} // end if
}	// doRetreat

//-------------------------------------------------------------------

void doMoveToStart (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Move To Start ";
	i = getIndex ();
	if (i == 1) {
		s1.moveToStart ();
	} else {
		s2.moveToStart ();
	}	// end if
	wcout << "s" << i << ".moveToStart (); executed." << endl;
}	// doMoveToStart

//-------------------------------------------------------------------

void doMoveToFinish (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Move To Finish ";
	i = getIndex ();
	if (i == 1) {
		s1.moveToFinish ();
	} else {
		s2.moveToFinish ();
	}	// end if
	wcout << "s" << i << ".moveToFinish (); executed." << endl;
}	// doMoveToFinish

//-------------------------------------------------------------------

void doSwapRights (
		TextList& s1,
		TextList& s2
	)
{
	s1.swapRights (s2);
	wcout << endl << "s1.swapRights (s2); executed." << endl;
}	// doSwapRights

//-------------------------------------------------------------------

void doLeftSize (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, lz;

	wcout << "Left size of ";
	i = getIndex ();
	if (i == 1) {
		lz = s1.leftSize ();
	} else {
		lz = s2.leftSize ();
	}	// end if
	wcout << "|s" << i << ".left|  = " << lz << endl;
}	// doLeftSize

//-------------------------------------------------------------------

void doRightSize (
		TextList& s1,
		TextList& s2
	)
{
	Integer i, rz;

	wcout << "Right size of ";
	i = getIndex ();
	if (i == 1) {
		rz = s1.rightSize ();
	} else {
		rz = s2.rightSize ();
	}	// end if
	wcout << "|s" << i << ".right| = " << rz << endl;
}	// doRightSize

//-------------------------------------------------------------------

void doSwap (
		TextList& s1,
		TextList& s2
	)
{
	s1 &= s2;
	wcout << endl << "s1 &= s2 executed." << endl;
}	// doSwap

//-------------------------------------------------------------------

void doCopy (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Copy ";
	i = getIndex ();
	if (i == 1) {
		s2 = s1;
		wcout << "s2 = s1; executed." << endl;
	} else {
		s1 = s2;
		wcout << "s1 = s2; executed." << endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void display (
		TextList& s
	)
	//! requires s.right = < >
{
	Integer i, z;
	Text x;

	wcout << " < ";
	z = s.rightSize ();
	for (i = 0; i < z; i++) {
		wcout << s[0] << " ";
		s.advance ();
	}	// end for
	wcout << ">";
	s.moveToStart ();
}	// display

//-------------------------------------------------------------------

void displayHelp (
		TextList& s
	)
{
	TextList t;

	s.swapRights (t);
	s.moveToStart ();
	display (s);
	display (t);
	s.moveToFinish ();
	s.swapRights (t);
}	// displayHelp

//-------------------------------------------------------------------

void doDisplay (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "display ";
	i = getIndex ();
	wcout << "s" << i << " = ";
	if (i == 1) {
		displayHelp (s1);
	} else {
		displayHelp (s2);
	}	// end if
	wcout << endl;
}	// doDisplay

//-------------------------------------------------------------------

void doClear (
		TextList& s1,
		TextList& s2
	)
{
	Integer i;

	wcout << "Clear ";
	i = getIndex ();
	if (i == 1) {
		s1.clear ();
	} else {
		s2.clear ();
	}	// end if
	wcout << endl << "s" << i << ".clear (); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile (
		TextList& s1,
		TextList& s2
	)
{
	Boolean successful;
	Integer i, size, index;
	Text filename, x;
	File input;
	TextList s;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile (filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		input.read (size, successful);
		for (i = 0; i < size; i++) {
			input.read (x, successful);
			s.addRight (x);
		}	// end for
		input.closeFile (successful);

		wcout << "Load file into ";
		index = getIndex ();
		if (index == 1) {
			s &= s1;
		} else {
			s &= s2;
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile (
		TextList& s1,
		TextList& s2
	)
{
	Boolean successful;
	Integer i, lz, z, index;
	Text filename;
	File output;
	TextList s;

	// get file name from user
	// open file for writing
	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	output.openFile (filename, File::openForWrite, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		// find out from which List to output contents.
		wcout << "Output from ";
		index = getIndex ();

		// swap contents of chosen Queue into local s.
		// note:   
		// &=   is an infix operator that swaps the values
		//      of two different List objects.
		if (index == 1) {
			s &= s1;
		} else {
			s &= s2;
		}	// end if

		// write to file:
		// 1) write an Integer telling how many items are in s
		// 2) write each item found in s
		// note: 
		// after loop has finished, s must contain
		// the same values as before, in same order with fence in same position.
		lz = s.leftSize ();
		s.moveToStart ();
		z = s.rightSize ();
		output.write (z, successful);
		for (i = 0; i < z; i++) {
			output.write (s[0], successful);
			s.advance ();
		}	// end for
		output.closeFile (successful);

		// move fence back into original position
		s.moveToStart ();
		for (i = 0; i < lz; i++) {
			s.advance ();
		}	// end for

		// swap the contents of local s back into original
		if (index == 1) {
			s &= s1;
		} else {
			s &= s2;
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		Character command,
		Boolean& showMenu,
		TextList& s1,
		TextList& s2
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doAddRight (s1, s2);
			break;
		case 'd':
			doRemoveRight (s1, s2);
			break;
		case '[':
			doAccess (s1, s2);
			break;
		case 'a':
			doAdvance (s1, s2);
			break;
		case 'r':
			doRetreat (s1, s2);
			break;
		case '<':
			doMoveToStart (s1, s2);
			break;
		case '>':
			doMoveToFinish (s1, s2);
			break;
		case 's':
			doSwapRights (s1, s2);
			break;
		case '(':
			doLeftSize (s1, s2);
			break;
		case ')':
			doRightSize (s1, s2);
			break;
		case '&':
			doSwap (s1, s2);
			break;
		case '=':
			doCopy (s1, s2);
			break;
		case 'l':
			inputFromFile (s1, s2);
			break;
		case 'o':
			outputToFile (s1, s2);
			break;
		case 'p':
			doDisplay (s1, s2);
			break;
		case 'c':	
			doClear (s1, s2);
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
		TextList& s1,
		TextList& s2,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu ();
		}	// end if
		getCommand (command);
		dispatchCommand (command, showMenu, s1, s2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = true;
	TextList s1, s2;

	commandController (s1, s2, showMenu);
	wcout << "end program" << endl;
	return 0;

}	// end main

*/