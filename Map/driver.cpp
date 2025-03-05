//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "Map\Map1.hpp"
#include "Map\Map2.hpp"
#include "Map\Map5.hpp"

static Boolean areEqual(Integer& lhs, Integer& rhs)
{
	return (lhs == rhs);
};

static Integer hashCode(Integer& key)
	{return (key);};

static Boolean areOrdered(Integer& lhs, Integer& rhs)
	{return (lhs <= rhs);};


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
//typedef Map1 <Integer, Text, areEqual> ITMap;
//typedef Map2 <Integer, Text, areEqual, hashCode> ITMap;
typedef Map5 <Integer, Text, areEqual, areOrdered> ITMap;
#else
// Compiling in Debug configuration
#include "Map\MapChecking.hpp"
typedef MapChecking1 <Integer, Text, Map5 <Integer, Text, areEqual, areOrdered>> ITMap;
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
	wcout << "        d - add" << endl;
	wcout << "        u - remove" << endl;
	wcout << "        1 - removeAny" << endl;
	wcout << "        v - value" << endl;
	wcout << "        ? - hasKey" << endl;
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
		wcout << "which Map? 1 or 2:";
		wcin >> index;
	} while ((index < 1) || (index > 2));
	wcout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

void getInteger (Integer& x)
{
	wcout << "Enter a key value (integer):";
	wcin >> x;
}	// getInteger

//-------------------------------------------------------------------

void getText (Text& s)
{
	wcout << "Enter text string:";
	wcin >> s;
}	// getText

//-------------------------------------------------------------------

void doAdd (
		ITMap& m1,
		ITMap& m2
	)
{
	Boolean defined;
	Integer i, key;
	Text value;

	wcout << "Add to ";
	i = getIndex ();
	getInteger (key);
	getText (value);
	if (i == 1) {
		defined = m1.hasKey (key);
		if (!defined) {
			m1.add (key, value);
		} // end if
	} else {
		defined = m2.hasKey (key);
		if (!defined) {
			m2.add (key, value);
		} // end if
	}	// end if
	if (!defined) {
		wcout << endl << "m" << i << ".add(key, value); executed." << endl;
		wcout << "key = " << key <<"   value = " << value << endl;
	} else {
		wcout << endl << "Error: " << key << " is already in m." << i << endl;
	} // end if
}	// doAdd

//-------------------------------------------------------------------

void doRemove (
		ITMap& m1,
		ITMap& m2
	)
{
	Boolean defined;
	Integer i, key, keyFromMap;
	Text value;

	wcout << "Remove from ";
	i = getIndex ();
	getInteger (key);
	if (i == 1) {
		defined = m1.hasKey (key);
		if (defined) {
			m1.remove (key, keyFromMap, value);
		} // end if
	} else {
		defined = m2.hasKey (key);
		if (defined) {
			m2.remove (key, keyFromMap, value);
		} // end if
	}	// end if
	if (defined) {
		wcout << endl << "m" << i << ".remove(key, keyFromMap, value); executed." << endl;
		wcout << "key = " << key << endl;
		wcout << "keyFromMap = " << keyFromMap << endl;
		wcout << "value = " << value << endl;
	} else {
		wcout << endl << "Error: " << key << " is not in m." << i << endl;
	} // end if
}	// doRemove

//-------------------------------------------------------------------

void doRemoveAny (
		ITMap& m1,
		ITMap& m2
	)
{
	Integer i, key, z;
	Text value;

	wcout << "Remove any from ";
	i = getIndex ();
	if (i == 1) {
		z = m1.size ();
		if (z > 0) {
			m1.removeAny (key, value);
		} // end if
	} else {
		z = m2.size ();
		if (z > 0) {
			m2.removeAny (key, value);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "m" << i << ".removeAny(key, value); executed." << endl;
		wcout << "key = " << key <<"   value = " << value << endl;
	} else {
		wcout << endl << "Error: |m" << i << "| = 0 - ";
		wcout << "cannot undefine one from an empty map." << endl;
	} // end if
}	// doRemoveAny

//-------------------------------------------------------------------

void doValue (
		ITMap& m1,
		ITMap& m2
	)
{
	Integer i, key;

	wcout << "Access value in ";
	i = getIndex ();
	getInteger (key);
	if (i == 1) {
		if (m1.hasKey (key)) {
			wcout << "m1.value(" << key << ") = " << m1.value(key) << endl;
		} else {
			wcout << endl << "Error: " << key << " is not in m1." << endl;
		} // end if
	} else {
		if (m2.hasKey (key)) {
			wcout << "m2.value(" << key << ") = " << m2.value(key) << endl;
		} else {
			wcout << endl << "Error: " << key << " is not in m2." << endl;
		} // end if
	}	// end if
}	// doValue

//-------------------------------------------------------------------

void doSize (
		ITMap& m1,
		ITMap& m2
	)
{
	Integer i, z;
	Text x;

	wcout << "Size of ";
	i = getIndex ();
	if (i == 1) {
		z = m1.size ();
	} else {
		z = m2.size ();
	}	// end if
	wcout << "|m" << i << "| = " << z << endl;
}	// doSize

//-------------------------------------------------------------------

void doHasKey (
		ITMap& m1,
		ITMap& m2
	)
{
	Boolean b;
	Integer i, key;

	wcout << "Has key in ";
	i = getIndex ();
	getInteger (key);
	if (i == 1) {
		b = m1.hasKey (key);
	} else {
		b = m2.hasKey (key);
	}	// end if
	wcout << key << " is";
	if (!b) {
		wcout << " not";
	}   // end if
	wcout << " in m" << i << endl;
}	// doHasKey


//-------------------------------------------------------------------

void doTransferFrom(
		ITMap& m1,
		ITMap& m2
	)
{
	Integer index;

	wcout << "Transfer from ";
	index = getIndex();
	if (index == 1) {
		m2.transferFrom(m1);
		wcout << endl << "m2.transferFrom(m1); executed." << endl;
	} else {
		m1.transferFrom(m2);
		wcout << endl << "m1.transferFrom(m2); executed." << endl;
	} // end if
}	// doTransferFrom

//-------------------------------------------------------------------

void doCopy (
		ITMap& m1,
		ITMap& m2
	)
{
	Integer i;

	wcout << "Copy ";
	i = getIndex ();
	if (i == 1) {
		m2 = m1;
		wcout << "m2 = m1; executed." << endl;
	} else {
		m1 = m2;
		wcout << "m1 = m2; executed." << endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void doDisplay (
		ITMap& m1,
		ITMap& m2
	)
{
	Integer i;

	wcout << "Display ";
	i = getIndex ();
	wcout << "m" << i << " = ";
	if (i == 1) {
		wcout << m1 << endl;
	} else {
		wcout << m2 << endl;
	}	// end if
}	// doDisplay

//-------------------------------------------------------------------

void doClear (
		ITMap& m1,
		ITMap& m2
	)
{
	Integer i;

	wcout << "Clear ";
	i = getIndex ();
	if (i == 1) {
		m1.clear ();
	} else {
		m2.clear ();
	}	// end if
	wcout << endl << "m" << i << ".clear()  executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile (
		ITMap& m1,
		ITMap& m2
	)
{
	Boolean successful;
	Integer i, size, index, key;
	Text filename, value;
	File input;
	ITMap m;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile (filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		input.read (size, successful);
		for (i = 0; i < size; i++) {
			input.read (key, successful);
			input.read (value, successful);
			m.add (key, value);
		}	// end for
		input.closeFile (successful);

		wcout << "Load file into ";
		index = getIndex ();
		if (index == 1) {
			m1.transferFrom(m);
		} else {
			m2.transferFrom(m);
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile (
		ITMap& m1,
		ITMap& m2
	)
{
	Boolean successful;
	Integer i, z, index, key;
	Text filename, value;
	File output;
	ITMap m, temp;

	// get file name from user
	// open file for writing
	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	output.openFile (filename, File::openForWrite, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		// find out from which PartialMap to output contents.
		wcout << "Output from ";
		index = getIndex ();

		// swap contents of chosen PartialMap into local m.
		// note:   
		// &=   is an infix operator that swaps the values
		//      of two different PartialMap objects.
		if (index == 1) {
			m.transferFrom(m1);
		} else {
			m.transferFrom(m2);
		}	// end if

		// write to file:
		// 1) write an Integer telling how many items are in m
		// 2) write each item found in m
		// note: 
		// after loop has finished, m must contain
		// the same values as before, in same order.
		z = m.size ();
		output.write (z, successful);
		for (i = 0; i < z; i++) {
			m.removeAny (key, value);
			output.write (key, successful);
			output.write (value, successful);
			temp.add (key, value);
		}	// end for
		output.closeFile (successful);

		// swap the contents of local m back into original
		if (index == 1) {
			m1.transferFrom(temp);
		} else {
			m2.transferFrom(temp);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		Character command,
		Boolean& showMenu,
		ITMap& m1,
		ITMap& m2
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'd':
			doAdd (m1, m2);
			break;
		case 'u':
			doRemove (m1, m2);
			break;
		case '1':
			doRemoveAny (m1, m2);
			break;
		case 'v':
			doValue (m1, m2);
			break;
		case 'z':
			doSize (m1, m2);
			break;
		case '?':
			doHasKey (m1, m2);
			break;
		case 'x':
			doTransferFrom (m1, m2);
			break;
		case '=':
			doCopy (m1, m2);
			break;
		case 'l':
			inputFromFile (m1, m2);
			break;
		case 'o':
			outputToFile (m1, m2);
			break;
		case 'p':
			doDisplay (m1, m2);
			break;
		case 'c':	
			doClear (m1, m2);
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
		ITMap& m1,
		ITMap& m2,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu ();
		}	// end if
		getCommand (command);
		dispatchCommand (command, showMenu, m1, m2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	ITMap m1, m2;

	commandController (m1, m2, showMenu);
	wcout << "end program" << endl;
	return 0;
}	// end main
