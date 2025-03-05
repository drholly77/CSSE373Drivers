//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "StaticArray\StaticArray1.hpp"

#define LOWERBOUND 0
#define UPPERBOUND 9

#ifdef NDEBUG
typedef StaticArray1 <Integer, LOWERBOUND, UPPERBOUND> IntegerArray;
#else
#include "StaticArray\StaticArrayChecking.hpp"
typedef StaticArrayChecking1 <Integer, LOWERBOUND, UPPERBOUND, StaticArray1 <Integer, LOWERBOUND, UPPERBOUND>> IntegerArray;
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
	wcout << "        [ - access" << endl;
	wcout << "        : - assign value" << endl;
	wcout << "        c - clear" << endl;
	wcout << "        x - transferFrom" << endl;
	wcout << "        = - copy" << std::endl;
	wcout << "        p - display" << endl;
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

Integer getWhich (void)
{
	Integer which;

	do {
		wcout << "which Array? 1 or 2:";
		wcin >> which;
	} while ((which < 1) || (which > 2));
	wcout << endl;
	return (which);
}	// getWhich

//-------------------------------------------------------------------

Integer getIndex (IntegerArray& a)
{
	Integer index, lb, ub;
	a.getBounds(lb, ub);

	do {
		wcout << "which Location? " << lb << ".." << ub << ":";
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

void getInteger (Integer& x)
{
	wcout << "Enter an integer:";
	wcin >> x;
}	// getInteger

//-------------------------------------------------------------------

void doAccess (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which, index;

	wcout << "Access ";
	which = getWhich ();
	if (which == 1) {
		index = getIndex (a1);
		wcout << "a1[" << index << "] = " << a1[index] << endl;
	} else {
		index = getIndex (a2);
		wcout << "a2[" << index << "] = " << a2[index] << endl;
	}	// end if
}	// doAccess

//-------------------------------------------------------------------

void doAssignValue (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which, index, x;

	wcout << "Assign a value to ";
	which = getWhich ();
	if (which == 1) {
		index = getIndex (a1);
		getInteger (x);
		a1[index] = x;
		wcout << "a1[" << index << "] = " << x << "; executed." << endl;
	} else {
		index = getIndex (a2);
		getInteger (x);
		a2[index] = x;
		wcout << "a2[" << index << "] = " << x << "; executed." << endl;
	}	// end if
}	// doAssignValue

//-------------------------------------------------------------------

void doTransferFrom(
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer index;

	wcout << "Transfer from ";
	index = getWhich();
	if (index == 1) {
		a2.transferFrom(a1);
		wcout << endl << "a2.transferFrom(a1); executed." << endl;
	} else {
		a1.transferFrom(a2);
		wcout << endl << "a1.transferFrom(a2); executed." << endl;
	} // end if
}	// doTransferFrom

//-------------------------------------------------------------------

void doCopy (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer i;

	std::wcout << "Copy ";
	i = getWhich ();
	if (i == 1) {
		a2 = a1;
		std::wcout << "a2 = a1; executed." << std::endl;
	} else {
		a1 = a2;
		std::wcout << "a1 = a2; executed." << std::endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void doDisplay (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer i;

	wcout << "Display ";
	i = getWhich ();
	wcout << "a" << i << " = ";
	if (i == 1) {
		wcout << a1 << endl;
	} else {
		wcout << a2 << endl;
	}	// end if
}	// doDisplay

//-------------------------------------------------------------------

void doClear (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which;

	wcout << "Clear ";
	which = getWhich ();
	if (which == 1) {
		a1.clear ();
	} else {
		a2.clear ();
	}	// end if
	wcout << endl << "a" << which << ".clear (); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void dispatchCommand (
		Character command,
		Boolean& showMenu,
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case '[':
			doAccess (a1, a2);
			break;
		case ':':
			doAssignValue (a1, a2);
			break;
		case 'x':
			doTransferFrom (a1, a2);
			break;
		case '=':
			doCopy (a1, a2);
			break;
		case 'p':
			doDisplay (a1, a2);
			break;
		case 'c':	
			doClear (a1, a2);
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
		IntegerArray& a1,
		IntegerArray& a2,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu ();
		}	// end if
		getCommand (command);
		dispatchCommand (command, showMenu, a1, a2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	IntegerArray a1, a2;

	commandController (a1, a2, showMenu);
	wcout << "end program" << endl;
}	// end main
