//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "Stack\Stack1.hpp"

#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef Stack1 <Text> TextStack;
#else
// Compiling in Debug configuration
#include "Stack/StackChecking.hpp"
typedef StackChecking1 <Text, Stack1 <Text>> TextStack;
#endif

//-------------------------------------------------------------------
// program operations
//-------------------------------------------------------------------

void displayMenu(void)
{
	wcout << endl;
	wcout << "---------------------------------------------" << endl;
	wcout << endl;
	wcout << "     Command -  Result" << endl;
	wcout << "        g - toggle display menu" << endl;
	wcout << "        e - push" << endl;
	wcout << "        d - pop" << endl;
	wcout << "        r - replaceTop" << endl;
	wcout << "        t - top" << endl;
	wcout << "        z - length" << endl;
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

void getCommand(Character& command)
{
	wcin >> command;
	wcout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex(void)
{
	Integer index;

	do {
		wcout << "which Stack? 1 or 2:";
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

void doPush(
		TextStack& s1,
		TextStack& s2
	)
{
	Integer i;
	Text x;

	wcout << "Push onto ";
	i = getIndex();
	getText(x);
	if (i == 1) {
		s1.push(x);
	} else {
		s2.push(x);
	}	// end if
	wcout << endl << "s" << i << ".push(x); executed." << endl;
	wcout << "x = " << x << endl;
}	// doPush

//-------------------------------------------------------------------

void doPop(
		TextStack& s1,
		TextStack& s2
	)
{
	Integer i, z;
	Text x;

	wcout << "Pop from ";
	i = getIndex();
	if (i == 1) {
		z = s1.length();
		if (z > 0) {
			s1.pop(x);
		} // end if
	} else {
		z = s2.length();
		if (z > 0) {
			s2.pop(x);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "s" << i << ".pop(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << "| = 0 - cannot pop an empty stack." << endl;
	} // end if
}	// doPop

//-------------------------------------------------------------------

void doReplaceTop(
		TextStack& s1,
		TextStack& s2
	)
{
	Integer index, z;
	Text x;

	wcout << "Replace top of ";
	index = getIndex();
	if (index == 1) {
		z = s1.length();
		if (z > 0) {
			getText(x);
			s1.replaceTop(x);
		} // end if
	} else {
		z = s2.length();
		if (z > 0) {
			getText(x);
			s2.replaceTop(x);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "s" << index << ".replaceTop(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << index << "| = 0 - cannot replace top on an empty stack." << endl;
	} // end if
}	// doReplaceTop

//-------------------------------------------------------------------

void doTop(
		TextStack& s1,
		TextStack& s2
	)
{
	Integer i;

	wcout << "Access top of ";
	i = getIndex();

	if (i == 1) {
		if (s1.length() > 0) {
			wcout << "s1.top() = " << s1.top() << endl;
		} else {
			wcout << "Error: |s1| = 0 - cannot access an empty stack." << endl;
		} // end if
	} else {
		if (s2.length() > 0) {
			wcout << "s2.top() = " << s2.top() << endl;
		} else {
			wcout << "Error: |s2| = 0 - cannot access an empty stack." << endl;
		} // end if
	}	// end if
}	// doTop

//-------------------------------------------------------------------

void doLength(
		TextStack& s1,
		TextStack& s2
	)
{
	Integer i, z;

	wcout << "Length of ";
	i = getIndex();
	if (i == 1) {
		z = s1.length();
	} else {
		z = s2.length();
	}	// end if
	wcout << "|s" << i << "| = " << z << endl;
}	// doLength

//-------------------------------------------------------------------

void doClear(
		TextStack& s1,
		TextStack& s2
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
	wcout << "s" << i << ".clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void doTransferFrom(
		TextStack& s1,
		TextStack& s2
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
		TextStack& s1,
		TextStack& s2
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
		TextStack& s1,
		TextStack& s2
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

void inputFromFile(
		TextStack& s1,
		TextStack& s2
	)
{
	Boolean successful;
	Integer length, index;
	Text filename, x;
	File input;
	TextStack temp;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file: " << filename << endl;
	} else {
		input.read(length, successful);
		for(int i = 0; i < length; i++) {
			input.read(x, successful);
			temp.push(x);
		}	// end for
		input.closeFile(successful);

		wcout << "Load file into ";
		index = getIndex();
		if (index == 1) {
			s1.transferFrom(temp);
		} else {
			s2.transferFrom(temp);
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile(
		TextStack& s1,
		TextStack& s2
	)
{
	Boolean successful;
	Integer z, index;
	Text filename, x;
	File output;
	TextStack s, temp;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;

	output.openFile(filename, File::openForWrite, successful);

	wcout << "Output from ";
	index = getIndex();

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		if (index == 1) {
			s.transferFrom(s1);
		} else {
			s.transferFrom(s2);
		}	// end if
		
		z = s.length();
		output.write(z, successful);
		for(int p = 0; p < z; p++) {
			s.pop(x);
			output.write(x, successful);
			temp.push(x);
		}	// end for
		output.closeFile(successful);
		for(int p = 0; p < z; p++) {
			temp.pop(x);
			s.push(x);
		}	// end for

		if (index == 1) {
			s1.transferFrom(s);
		} else {
			s2.transferFrom(s);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand(
		Character command,
		Boolean& showMenu,
		TextStack& s1,
		TextStack& s2
	)
{
	switch(command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doPush(s1, s2);
			break;
		case 'd':
			doPop(s1, s2);
			break;
		case 'r':
			doReplaceTop(s1, s2);
			break;
		case 't':
			doTop(s1, s2);
			break;
		case 'z':
			doLength(s1, s2);
			break;
		case 'x':
			doTransferFrom(s1, s2);
			break;
		case '=':
			doCopy(s1, s2);
			break;
		case 'c':
			doClear(s1, s2);
			break;
		case 'l':
			inputFromFile(s1, s2);
			break;
		case 'o':
			outputToFile(s1, s2);
			break;
		case 'p':	// display
			doDisplay(s1, s2);
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

void commandController(
		TextStack& s1,
		TextStack& s2,
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
	TextStack s1, s2;

	commandController(s1, s2, showMenu);
	return 0;
}	// end main
