//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "Sequence\Sequence1.hpp"
#include "Sequence\Sequence2.hpp"
#include "Sequence\Sequence3.hpp"
#include "Sequence\Sequence4.hpp"

#ifdef NDEBUG
typedef Sequence4 <Text> TextSequence;
#else
#include "Sequence\SequenceChecking.hpp"
typedef SequenceChecking1<Text, Sequence1 <Text>> TextSequence;
#endif


//-------------------------------------------------------------------
// program operations
//-------------------------------------------------------------------

void displayMenu (void)
{
	wcout << endl;
	wcout << "---------------------------------------------" << endl;
	wcout << endl;
	wcout << "     Command -  Result" << endl;
	wcout << "        g - toggle display menu" << endl;
	wcout << "        e - add" << endl;
	wcout << "        d - remove" << endl;
	wcout << "        r - replace entry" << endl;
	wcout << "        f - access entry" << endl;
	wcout << "        x - transfer from" << endl;
	wcout << "        a - append" << endl;
	wcout << "        s - split" << endl;
	wcout << "        z - length" << endl;
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

void getCommand (Character& command)
{
	wcin >> command;
	wcout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex (void)
{
	Integer index;

	do {
		wcout << "which Sequence? 1 or 2:";
		wcin >> index;
	} while ((index < 1) || (index > 2));
	wcout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

Integer getPosition (Integer maxAllowable)
{
	Integer position;

	do {
		wcout << "which position? 0 .. " << maxAllowable << ":";

		wcin >> position;
		wcout << endl;
	} while ((position < 0) || (position > maxAllowable));
	return (position);
}	// getPosition

//-------------------------------------------------------------------

void getText (Text& s)
{
	wcout << "Enter text string:";
	wcin >> s;
}	// getText

//-------------------------------------------------------------------

void doAdd (TextSequence& s1, TextSequence& s2)
{
	Integer i, p;
	Text x;

	wcout << "Add to ";
	i = getIndex();
	if (i == 1) {
		p = getPosition(s1.length());
		getText(x);
		s1.add(p, x);
	} else {
		p = getPosition(s2.length());
		getText(x);
		s2.add(p, x);
	} // end if
	wcout << endl << "s" << i << ".add(" << p << ", x); executed." << endl;
	wcout << "x = " << x << endl;
}	// doAdd

//-------------------------------------------------------------------

void doRemove (TextSequence& s1, TextSequence& s2)
{
	Integer i, p, size;
	Text x;

	wcout << "Remove from ";
	i = getIndex();
	if (i == 1) {
		size = s1.length();
		if (size > 0) {
			p = getPosition(size - 1);
			s1.remove(p, x);
		} // end if
	} else {
		size = s2.length();
		if (size > 0) {
			p = getPosition(size - 1);
			s2.remove(p, x);
		} // end if
	} // end if

	if (size > 0) {
		wcout << endl << "s" << i << ".remove(" << p << ", x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << "| = 0 - cannot remove from an empty sequence." << endl;
	} // end if
}	// doRemove

//-------------------------------------------------------------------

void doReplaceEntry (TextSequence& s1, TextSequence& s2)
{
	Integer i, p, size;
	Text x;

	wcout << "Replace entry from ";
	i = getIndex();
	if (i == 1) {
		size = s1.length();
		if (size > 0) {
			p = getPosition(size - 1);
			getText(x);
			s1.replaceEntry(p, x);
		} // end if
	} else {
		size = s2.length();
		if (size > 0) {
			p = getPosition(size - 1);
			getText(x);
			s2.replaceEntry(p, x);
		} // end if
	} // end if

	if (size > 0) {
		wcout << endl << "s" << i << ".replaceEntry(" << p << ", x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |s" << i << "| = 0 - cannot replace an entry in an empty sequence." << endl;
	} // end if
}	// doReplaceEntry

//-------------------------------------------------------------------

void doAppend (TextSequence& s1, TextSequence& s2)
{
	Integer i;

	wcout << "Append ";
	i = getIndex();
	if (i == 1) {
		s2.append(s1);
		wcout << "s2.append(s1); executed." << endl;
	} else {
		s1.append(s2);
		wcout << "s1.append(s2); executed." << endl;
	} // end if
}	// doAppend

//-------------------------------------------------------------------

void doSplit (TextSequence& s1, TextSequence& s2)
{
	Integer i, p;
	Text x;

	wcout << "Split ";
	i = getIndex();
	if (i == 1) {
		p = getPosition(s1.length());
		s1.split(p, s2);
		wcout << "s1.split(" << p << ", s2); executed." << endl;
	} else {
		p = getPosition(s2.length());
		s2.split(p, s1);
		wcout << "s2.split(" << p << ", s1); executed." << endl;
	} // end if
}	// doSplit

//-------------------------------------------------------------------

void doEntry (TextSequence& s1, TextSequence& s2)
{
	Integer i, p, size;

	wcout << "Access entry in ";
	i = getIndex();
	if (i == 1) {
		size = s1.length();
		if (size > 0) {
			p = getPosition(size - 1);
			wcout << "s1.entry(" << p << ") = " << s1.entry(p) << endl;
		} // end if
	} else {
		size = s2.length();
		if (size > 0) {
			p = getPosition(size - 1);
			wcout << "s2.entry(" << p << ") = " << s2.entry(p) << endl;
		} // end if
	} // end if
	if (size == 0) {
		wcout << "Error: |s" << i << "| = 0 - cannot access an empty sequence." << endl;
	} // end if
}	// doEntry

//-------------------------------------------------------------------

void doLength (TextSequence& s1, TextSequence& s2)
{
	Integer i, z;

	wcout << "Length of ";
	i = getIndex();
	if (i == 1) {
		z = s1.length();
	} else {
		z = s2.length();
	} // end if
	wcout << "|s" << i << "| = " << z << endl;
}	// doLength

//-------------------------------------------------------------------

void doClear (TextSequence& s1, TextSequence& s2)
{
	Integer i;

	wcout << "Clear ";
	i = getIndex();
	if (i == 1) {
		s1.clear();
	} else {
		s2.clear();
	} // end if
	wcout << "s" << i << ".clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void doTransferFrom (TextSequence& s1, TextSequence& s2)
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

void doCopy (TextSequence& s1, TextSequence& s2)
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

void display (TextSequence& s)
{
	wcout << "<";
	for (int p = 0, z = s.length(), lastItem = (z - 1); p < z; p++) {
		wcout << s.entry(p);
		if (p < lastItem) {
			wcout << ",";
		} // end if
	}	// end for
	wcout << ">" << endl;
}	// display

//-------------------------------------------------------------------

void doDisplay (TextSequence& s1, TextSequence& s2)
{
	Integer i;

	wcout << "Display ";
	i = getIndex();
	wcout << "s" << i << " = ";
	if (i == 1) {
		wcout << s1 << endl;
	} else {
		wcout << s2 << endl;
	} // end if
}	// doDisplay

//-------------------------------------------------------------------

void doInputFromFile (TextSequence& s1, TextSequence& s2)
{
	Boolean successful;
	Integer i, size, index;
	Text filename, x;
	File input;
	TextSequence s;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file: " << filename << endl;
	} else {
		input.read(size, successful);
		for (i = 0; i < size; i++) {
			input.read(x, successful);
			s.add(0, x);
		}	// end for
		input.closeFile(successful);

		wcout << "Load file into ";
		index = getIndex();
		if (index == 1) {
			s1.transferFrom(s);
		} else {
			s2.transferFrom(s);
		} // end if
	}	// end if
}	// doInputFromFile

//-------------------------------------------------------------------

void doOutputToFile (TextSequence& s1, TextSequence& s2)
{
	Boolean successful;
	Integer p, z, index;
	Text filename;
	File output;
	TextSequence s;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;

	output.openFile(filename, File::openForWrite, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		wcout << "Output from ";
		index = getIndex();
		if (index == 1) {
			s.transferFrom(s1);
		} else {
			s.transferFrom(s2);
		} // end if
		z = s.length();
		output.write(z, successful);
		for (p = 0; p < z; p++) {
			output.write(s.entry(p), successful);
		}	// end for
		output.closeFile(successful);
		if (index == 1) {
			s1.transferFrom(s);
		} else {
			s2.transferFrom(s);
		} // end if
	}  // end if
}	// doOutputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		Character command,
		Boolean& showMenu,
		TextSequence& s1, 
		TextSequence& s2
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doAdd(s1, s2);
			break;
		case 'd':
			doRemove(s1, s2);
			break;
		case 'r':
			doReplaceEntry(s1, s2);
			break;
		case 'a':
			doAppend(s1, s2);
			break;
		case 's':
			doSplit(s1, s2);
			break;
		case 'f':
			doEntry(s1, s2);
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
			doInputFromFile(s1, s2);
			break;
		case 'o':
			doOutputToFile(s1, s2);
			break;
		case 'p':
			doDisplay(s1, s2);
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

void commandController (
		TextSequence& s1, 
		TextSequence& s2,
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
	TextSequence s1, s2;

	commandController(s1, s2, showMenu);
	wcout << "end program" << endl;
	return 0;
}	// end main
