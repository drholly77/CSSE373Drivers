//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "PartitionableArray\PartitionableArray1.hpp"



static Boolean isInteresting (Integer& x)
{
	Boolean odd;

	odd = ((x % 2) == 1);
	return (odd);
}


#ifdef NDEBUG
typedef PartitionableArray1 <Integer, isInteresting> IntegerArray;
#else
#include "PartitionableArray\PartitionableArrayChecking.hpp"
typedef PartitionableArrayChecking1 <Integer, PartitionableArray1 <Integer, isInteresting>> IntegerArray;
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
	wcout << "        t - test for empty partition" << endl;
	wcout << "        i - index of odd value in partition" << endl;
	wcout << "        S - setBounds" << endl;
	wcout << "        G - getBounds" << endl;
	wcout << "        c - clear" << endl;
	wcout << "        x - transferFrom" << endl;
	wcout << "        = - copy" << endl;
	wcout << "        p - display" << endl;
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
	Integer index, l, u;

	a.getBounds(l, u);

	do {
		wcout << "which Location? " << l << ".." << u << ":";
		wcin >> index;
	} while ((index < l) || (index > u));
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

void getBoundsFromUser (Integer& l, Integer& u)
{
	l.clear();
	u.clear();
	do {
		wcout << "Enter the array's new lower bound:";
		wcin >> l;
		wcout << "Enter the array's new upper bound:";
		wcin >> u;
		if (u < l) {
			wcout << "upper bound must be >= lower bound." << endl;
		} // end if
	} while (u < l);
}	// getBoundsFromUser


//-------------------------------------------------------------------

void doSetBounds (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which, l, u;

	wcout << "Set bounds for ";
	which = getWhich();
	getBoundsFromUser(l, u);
	if (which == 1) {
		a1.setBounds(l, u);
	} else {
		a2.setBounds(l, u);
	}	// end if
	wcout << endl << "a" << which << ".setBounds(";
	wcout << l << ", " << u << "); executed." << endl;
}	// doSetBounds

//-------------------------------------------------------------------

void doGetBounds (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which, l, u;

	wcout << "Get bounds for ";
	which = getWhich();
	if (which == 1) {
		a1.getBounds(l, u);
	} else {
		a2.getBounds(l, u);
	}	// end if
	wcout << endl << "a" << which << ".getBounds(l, u); executed." << endl;
	wcout << "[l, u] = [" << l << ", " << u << "]" << endl;
}	// doGetBounds

//-------------------------------------------------------------------

void doAccess (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which, index;

	wcout << "Access ";
	which = getWhich();
	if (which == 1) {
		index = getIndex(a1);
		wcout << "a1[" << index << "] = " << a1[index] << endl;
	} else {
		index = getIndex(a2);
		wcout << "a2[" << index << "] = " << a2[index] << endl;
	}	// end if
}	// doAccess

//-------------------------------------------------------------------

void doEmptyPartition (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which;

	wcout << "Test Partition for ";
	which = getWhich();
	if (which == 1) {
		if (a1.numberOfInterestingEntries() > 0) {
			wcout << "a1's partition is non empty." << endl;
		} else {
			wcout << "a1's partition is empty." << endl;
		} // end if
	} else {
		if (a2.numberOfInterestingEntries() > 0) {
			wcout << "a2's partition is non empty." << endl;
		} else {
			wcout << "a2's partition is empty." << endl;
		} // end if
	}	// end if
}	// doEmptyPartition

//-------------------------------------------------------------------

void doGetPartitionIndex (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which, index;

	wcout << "Get Partition Index for ";
	which = getWhich();
	if (which == 1) {
		if (a1.numberOfInterestingEntries() > 0) {
			a1.giveIndexOfInterestingEntry(index);
			wcout << "a1[" << index << "] = " << a1[index] << endl;
		} else {
			wcout << "Error: a1's partition is empty - ";
			wcout << "cannot get partition index for empty partition." << endl;
		} // end if
	} else {
		if (a2.numberOfInterestingEntries() > 0) {
			a2.giveIndexOfInterestingEntry(index);
			wcout << "a2[" << index << "] = " << a2[index] << endl;
		} else {
			wcout << "Error: a2's partition is empty - ";
			wcout << "cannot get partition index for empty partition." << endl;
		} // end if
	}	// end if
}	// doGetPartitionIndex

//-------------------------------------------------------------------

void doAssignValue (
		IntegerArray& a1,
		IntegerArray& a2
	)
{
	Integer which, index, x;

	wcout << "Assign a Value to ";
	which = getWhich();
	if (which == 1) {
		index = getIndex(a1);
		getInteger(x);
		a1[index] = x;
		wcout << "a1[" << index << "] = " << x << "; executed." << endl;
	} else {
		index = getIndex(a2);
		getInteger(x);
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

	wcout << "Copy ";
	i = getWhich();
	if (i == 1) {
		a2 = a1;
		wcout << "a2 = a1; executed." << endl;
	} else {
		a1 = a2;
		wcout << "a1 = a2; executed." << endl;
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
	i = getWhich();
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
	which = getWhich();
	if (which == 1) {
		a1.clear();
	} else {
		a2.clear();
	}	// end if
	wcout << endl << "a" << which << ".clear()  executed." << endl;
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
		case 'S':
			doSetBounds(a1, a2);
			break;
		case 'G':
			doGetBounds(a1, a2);
			break;
		case 't':
			doEmptyPartition(a1, a2);
			break;
		case 'i':
			doGetPartitionIndex(a1, a2);
			break;
		case '[':
			doAccess(a1, a2);
			break;
		case ':':
			doAssignValue(a1, a2);
			break;
		case 'x':
			doTransferFrom(a1, a2);
			break;
		case '=':
			doCopy(a1, a2);
			break;
		case 'p':
			doDisplay(a1, a2);
			break;
		case 'c':	
			doClear(a1, a2);
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
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, a1, a2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	IntegerArray a1, a2;

	commandController(a1, a2, showMenu);
	wcout << "end program" << endl;
	return 0;
}	// end main
