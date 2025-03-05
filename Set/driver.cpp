//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "Set\Set1.hpp"


static Boolean areEqual(Text& lhs, Text& rhs)
{return (lhs == rhs);};


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef Set1 <Text, areEqual> TextSet;
#else
// Compiling in Debug configuration
#include "Set\SetChecking.hpp"
typedef SetChecking1 <Text, Set1 <Text, areEqual>> TextSet;
#endif



//-------------------------------------------------------------------
// program constants
//-------------------------------------------------------------------

void displayMenu(void)
{
	wcout << endl;
	wcout << "---------------------------------------------" << endl;
	wcout << endl;
	wcout << "     Command -  Result" << endl;
	wcout << "        g - toggle display menu" << endl;
	wcout << "        d - add" << endl;
	wcout << "        u - remove" << endl;
	wcout << "        1 - removeAny" << endl;
	wcout << "        ? - contains" << endl;
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

void getCommand(
		Character& command
	)
{
	wcin >> command;
	wcout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex(void)
{
	Integer index;

	do {
		wcout << "which Set? 1 or 2:";
		wcin >> index;
	} while ((index < 1) ||(index > 2));
	wcout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

void getText(Text& s)
{
	wcout << "Enter text string:";
	wcin >> s;
}	// getText

//-------------------------------------------------------------------

void doAdd(
		TextSet& s1,
		TextSet& s2
	)
{
	Boolean defined;
	Integer i;
	Text r;

	wcout << "Add into ";
	i = getIndex();
	getText(r);
	if (i == 1) {
		defined = s1.contains(r);
		if (!defined) {
			s1.add(r);
		} // end if
	} else {
		defined = s2.contains(r);
		if (!defined) {
			s2.add(r);
		} // end if
	}	// end if
	if (!defined) {
		wcout << endl << "s" << i << ".add(r); executed." << endl;
		wcout << "r = " << r << " after add" << endl;
	} else {
		wcout << "Error: " << r << " already a member of s" << i << endl;
	} // end if
}	// doAdd

//-------------------------------------------------------------------

void doRemove(
		TextSet& s1,
		TextSet& s2
	)
{
	Boolean defined;
	Integer i;
	Text rFromUser, rFromSet;

	wcout << "Remove from ";
	i = getIndex();
	getText(rFromUser);
	if (i == 1) {
		defined = s1.contains(rFromUser);
		if (defined) {
			s1.remove(rFromUser, rFromSet);
		} // end if
	} else {
		defined = s2.contains(rFromUser);
		if (defined) {
			s2.remove(rFromUser, rFromSet);
		} // end if
	}	// end if
	if (defined) {
		wcout << endl << "s" << i << ".remove(rFromUser, rFromSet); executed." << endl;
		wcout << "rFromUser = " << rFromUser << endl;
		wcout << " rFromSet = " << rFromSet << endl;
	} else {
		wcout << "Error: " << rFromUser << " not a member of s" << i << endl;
	} // end if
}	// doRemove

//-------------------------------------------------------------------

void doRemoveAny(
		TextSet& s1,
		TextSet& s2
	)
{
	Integer i, z;
	Text r;

	wcout << "Remove any from ";
	i = getIndex();
	if (i == 1) {
		z = s1.size();
		if (z > 0) {
			s1.removeAny(r);
		} // end if
	} else {
		z = s2.size();
		if (z > 0) {
			s2.removeAny(r);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "s" << i << ".removeAny(r); executed." << endl;
		wcout << "r = " << r << endl;
	} else {
		wcout << "Error: |s" << i << "| = 0 - cannot remove from empty set." << endl;
	} // end if
}	// doRemoveAny

//-------------------------------------------------------------------

void doSize(
		TextSet& s1,
		TextSet& s2
	)
{
	Integer i, z;

	wcout << "Size of ";
	i = getIndex();
	if (i == 1) {
		z = s1.size();
	} else {
		z = s2.size();
	}	// end if
	wcout << "|s" << i << "| = " << z << endl;
}	// doSize

//-------------------------------------------------------------------

void doContains(
		TextSet& s1,
		TextSet& s2
	)
{
	Boolean b;
	Integer i;
	Text r;

	wcout << "Contained in ";
	i = getIndex();
	getText(r);
	if (i == 1) {
		b = s1.contains(r);
	} else {
		b = s2.contains(r);
	}	// end if
	wcout << r << " is";
	if (!b) {
		wcout << " not";
	}   // end if
	wcout << " contained in s" << i << endl;
}	// doContains


//-------------------------------------------------------------------

void doTransferFrom(
		TextSet& s1,
		TextSet& s2
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

void doCopy(
		TextSet& s1,
		TextSet& s2
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

void doDisplay(
		TextSet& s1,
		TextSet& s2
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
}	// doDisplay

//-------------------------------------------------------------------

void doClear(
		TextSet& s1,
		TextSet& s2
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

void inputFromFile(
		TextSet& s1,
		TextSet& s2
	)
{
	Boolean successful;
	Integer i, size, index;
	Text filename, r;
	File input;
	TextSet s;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		input.read(size, successful);
		for(i = 0; i < size; i++) {
			input.read(r, successful);
			s.add(r);
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

void outputToFile(
		TextSet& s1,
		TextSet& s2
	)
{
	Boolean successful;
	Integer i, z, index;
	Text filename, r;
	File output;
	TextSet s, temp;

	// get file name from user
	// open file for writing
	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	output.openFile(filename, File::openForWrite, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		// find out from which Set to output contents.
		wcout << "Output from ";
		index = getIndex();

		// transfer contents of chosen Set into local s.
		if (index == 1) {
			s.transferFrom(s1);
		} else {
			s.transferFrom(s2);
		}	// end if

		// write to file:
		// 1) write an Integer telling how many items are in Set s
		// 2) write each item found in Set s
		// note: 
		// after loop has finished, s must contain
		// the same values as before.
		z = s.size();
		output.write(z, successful);
		for(i = 0; i < z; i++) {
			s.removeAny(r);
			output.write(r, successful);
			temp.add(r);
		}	// end for
		output.closeFile(successful);

		// swap the contents of local Set temp back into original
		if (index == 1) {
			s1.transferFrom(temp);
		} else {
			s2.transferFrom(temp);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand(
		Character command,
		Boolean& showMenu,
		TextSet& s1,
		TextSet& s2
	)
{
	switch(command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'd':
			doAdd(s1, s2);
			break;
		case 'u':
			doRemove(s1, s2);
			break;
		case '1':
			doRemoveAny(s1, s2);
			break;
		case 'z':
			doSize(s1, s2);
			break;
		case '?':
			doContains(s1, s2);
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
		case 'q':
			wcout << "Quit Command Interpreter" << endl;
			break;
		case '@':
			wcout << "Authored by Dr. Holly" << endl;
			break;
		default:
			wcout << "Unknown command: " << command << endl;
			wcout << "Please reenter your command" << endl;
			break;
	}	// end switch
}	// dispatchCommand

//-------------------------------------------------------------------

void commandController(
		TextSet& s1,
		TextSet& s2,
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

int main(int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	TextSet s1, s2;
	commandController(s1, s2, showMenu);

	wcout << "end program" << endl;
	return 0;
}	// end main
