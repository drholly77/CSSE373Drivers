//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "SortingMachine\SortingMachine1.hpp"
#include "SortingMachine\SortingMachine2.hpp"

static Boolean areOrdered (
		Integer& lhs,
		Integer& rhs
	)
{
	return (lhs <= rhs);
	}  // areOrdered


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef SortingMachine2<Integer, areOrdered> SMachine;
#else
// Compiling in Debug configuration
#include "SortingMachine\SortingMachineChecking.hpp"

typedef SortingMachineChecking1 <Integer, SortingMachine1<Integer, areOrdered>> SMachine;
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
	wcout << "        e - add" << endl;
	wcout << "        d - remove first" << endl;
	wcout << "        m - change to extraction mode" << endl;
	wcout << "        ? - is in insertion mode?" << endl;
	wcout << "        z - size" << endl;
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
		wcout << "which Sorting Machine? 1 or 2:";
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

void getInteger (Integer& x)
{
	wcout << "Enter integer:";
	wcin >> x;
}	// getInteger

//-------------------------------------------------------------------

void doAdd (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Boolean inInsertionPhase;
	Integer i;
	Integer x;

	wcout << "Add to ";
	i = getIndex();
	if (i == 1) {
		inInsertionPhase = sm1.isInInsertionMode();
		if (inInsertionPhase) {
			getInteger(x);
			sm1.add(x);
		} // end if
	} else {
		inInsertionPhase = sm2.isInInsertionMode();
		if (inInsertionPhase) {
			getInteger(x);
			sm2.add(x);
		} // end if
	}	// end if
	if (inInsertionPhase) {
		wcout << endl << "sm" << i << ".add(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << endl << "Error: sm" << i << ".inserting = false - ";
		wcout << "cannot Insert into a machine in extraction mode." << endl;
	} // end if
}	// doAdd

//-------------------------------------------------------------------

void doRemove (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Boolean inInsertionPhase;
	Integer i, size;
	Integer x;

	wcout << "Remove from ";
	i = getIndex();
	if (i == 1) {
		inInsertionPhase = sm1.isInInsertionMode();
		size = sm1.size();
		if (!inInsertionPhase &&(size > 0)) {
			sm1.removeFirst(x);
		} // end if
	} else {
		inInsertionPhase = sm2.isInInsertionMode();
		size = sm2.size();
		if (!inInsertionPhase && (size > 0)) {
			sm2.removeFirst(x);
		} // end if
	}	// end if
	if (!inInsertionPhase && (size > 0)) {
		wcout << endl << "sm" << i << ".removeFirst(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else if (inInsertionPhase) {
		wcout << endl << "Error: sm" << i << ".inserting = true - ";
		wcout << "cannot remove from a machine in insertion mode." << endl;
	} else {
		// size = 0
		wcout << endl << "Error: |sm" << i << ".contents| = 0 - ";
		wcout << "cannot remove from an empty sorting machine." << endl;
	} // end if
}	// doRemove

//-------------------------------------------------------------------

void doChangeToExtractionMode (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Boolean inInsertionPhase;
	Integer i;

	wcout << "Change to extraction mode for ";
	i = getIndex();
	if (i == 1) {
		inInsertionPhase = sm1.isInInsertionMode();
		if (inInsertionPhase) {
			sm1.changeToExtractionMode();
		} // end if
	} else {
		inInsertionPhase = sm2.isInInsertionMode();
		if (inInsertionPhase) {
			sm2.changeToExtractionMode();
		} // end if
	}	// end if
	if (inInsertionPhase) {
		wcout << endl << "sm" << i << ".changeToExtractionMode(); executed." << endl;
	} else {
		wcout << endl << "Error: sm" << i << ".inserting = false - ";
		wcout << "machine already in extraction mode." << endl;
	} // end if
}	// doChangeToExtractionMode

//-------------------------------------------------------------------

void doSize (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Integer i, z;
	Integer x;

	wcout << "Size of ";
	i = getIndex();
	if (i == 1) {
		z = sm1.size();
	} else {
		z = sm2.size();
	}	// end if
	wcout << "|sm" << i << ".contents| = " << z << endl;
}	// doSize

//-------------------------------------------------------------------

void doIsInInsertionMode (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Boolean b;
	Integer i;

	wcout << "Test for insertion mode for ";
	i = getIndex();
	if (i == 1) {
		b = sm1.isInInsertionMode();
	} else {
		b = sm2.isInInsertionMode();
	}	// end if
	wcout << "sm" << i << " is ";
	if (!b) {
		wcout << "not ";
	}   // end if
	wcout << "in insertion mode." << endl;
}	// doIsInInsertionMode

//-------------------------------------------------------------------

void doTransferFrom(
		SMachine& s1,
		SMachine& s2
	)
{
	Integer index;

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
		SMachine& sm1,
		SMachine& sm2
	)
{
	Integer i;

	wcout << "Copy ";
	i = getIndex();
	if (i == 1) {
		sm2 = sm1;
		wcout << "sm2 = sm1; executed." << endl;
	} else {
		sm1 = sm2;
		wcout << "sm1 = sm2; executed." << endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void doDisplay (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Integer i;

	wcout << "Display ";
	i = getIndex();
	wcout << "sm" << i << " = ";
	if (i == 1) {
		wcout << sm1 << endl;
	} else {
		wcout << sm2 << endl;
	}	// end if
}	// doDisplay

//-------------------------------------------------------------------

void doClear (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Integer i;

	wcout << "Clear ";
	i = getIndex();
	if (i == 1) {
		sm1.clear();
	} else {
		sm2.clear();
	}	// end if
	wcout << endl << "sm" << i << ".clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Boolean successful;
	Integer i, size, index;
	Text filename;
	Integer x;
	File input;
	SMachine sm;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		input.read(size, successful);
		for (i = 0; i < size; i++) {
			input.read(x, successful);
			sm.add(x);
		}	// end for
		input.closeFile(successful);

		wcout << "Load file into ";
		index = getIndex();
		if (index == 1) {
			sm1.transferFrom(sm);
		} else {
			sm2.transferFrom(sm);
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile (
		SMachine& sm1,
		SMachine& sm2
	)
{
	Boolean successful, inInsertionPhase;
	Integer i, z, index;
	Text filename;
	Integer x;
	File output;
	SMachine sm, temp;

	// get file name from user
	// open file for writing
	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	output.openFile(filename, File::openForWrite, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		// find out from which Queue to output contents.
		wcout << "Output from ";
		index = getIndex();

		// swap contents of chosen Queue into local sm.
		// note:   
		// &=   is an infix operator that swaps the values
		//      of two different Queue objects.
		if (index == 1) {
			sm.transferFrom(sm1);
		} else {
			sm.transferFrom(sm2);
		}	// end if

		inInsertionPhase = sm.isInInsertionMode();
		if (inInsertionPhase) {
			sm.changeToExtractionMode();
		}   // end if

		// write to file:
		// 1) write an Integer telling how many items are in sm
		// 2) write each item found in sm
		// note: 
		// after loop has finished, sm must contain
		// the same values as before, in same order.
		z = sm.size();
		output.write(z, successful);
		for (i = 0; i < z; i++) {
			sm.removeFirst(x);
			output.write(x, successful);
			temp.add(x);
		}	// end for
		output.closeFile(successful);

		sm.transferFrom(temp);
		if (!inInsertionPhase) {
			sm.changeToExtractionMode();
		}   // end if

		// swap the contents of local sm back into original
		if (index == 1) {
			sm1.transferFrom(sm);
		} else {
			sm2.transferFrom(sm);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		Character command,
		Boolean& showMenu,
		SMachine& sm1,
		SMachine& sm2
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doAdd(sm1, sm2);
			break;
		case 'd':
			doRemove(sm1, sm2);
			break;
		case 'm':
			doChangeToExtractionMode(sm1, sm2);
			break;
		case '?':
			doIsInInsertionMode(sm1, sm2);
			break;
		case 'z':
			doSize(sm1, sm2);
			break;
		case 'x':
			doTransferFrom(sm1, sm2);
			break;
		case '=':
			doCopy(sm1, sm2);
			break;
		case 'l':
			inputFromFile(sm1, sm2);
			break;
		case 'o':
			outputToFile(sm1, sm2);
			break;
		case 'p':
			doDisplay(sm1, sm2);
			break;
		case 'c':	
			doClear(sm1, sm2);
			break;
		case '@':
			wcout << "Authored by Dr. Holly" << endl;
			{
				sm2.clear();
				for (int k = 0, z = 20; k < z; k++) {
					Integer j = rand() % 1000;
					sm2.add(j);
				} // end for
			}
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
		SMachine& sm1,
		SMachine& sm2,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, sm1, sm2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	SMachine sm1, sm2;

	commandController(sm1, sm2, showMenu);

	wcout << "end program" << endl;
	return 0;
}	// end main
