//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "PreemptableQueue\PreemptableQueue1.hpp"


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef PreemptableQueue1<Text> PQOfText;
#else
// Compiling in Debug configuration
#include "PreemptableQueue\PreemptableQueueChecking.hpp"
typedef PreemptableQueueChecking1 <Text, PreemptableQueue1<Text>> PQOfText;
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
	wcout << "        e - enqueue" << endl;
	wcout << "        d - dequeue" << endl;
	wcout << "        i - inject" << endl;
	wcout << "        r - replaceFront" << endl;
	wcout << "        f - front" << endl;
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
		wcout << "which Preemptable Queue? 1 or 2:";
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

void doEnqueue(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index;
	Text x;

	wcout << "Enqueue onto ";
	index = getIndex();
	getText(x);
	if (index == 1) {
		q1.enqueue(x);
	} else {
		q2.enqueue(x);
	}	// end if
	wcout << endl << "q" << index << ".enqueue(x); executed." << endl;
	wcout << "x = " << x << endl;
}	// doEnqueue

//-------------------------------------------------------------------

void doDequeue(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index, z;
	Text x;

	wcout << "Dequeue from ";
	index = getIndex();
	if (index == 1) {
		z = q1.length();
		if (z > 0) {
			q1.dequeue(x);
		} // end if
	} else {
		z = q2.length();
		if (z > 0) {
			q2.dequeue(x);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "q" << index << ".dequeue(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |q" << index << "| = 0 - cannot dequeue from an empty queue." << endl;
	} // end if
}	// doDequeue

//-------------------------------------------------------------------

void doInject(
	PQOfText& q1,
	PQOfText& q2
	)
{
	Integer index;
	Text x;

	wcout << "Inject onto ";
	index = getIndex();
	getText(x);
	if (index == 1) {
		q1.inject(x);
	}
	else {
		q2.inject(x);
	}	// end if
	wcout << endl << "q" << index << ".inject(x); executed." << endl;
	wcout << "x = " << x << endl;
}	// doInject

//-------------------------------------------------------------------

void doReplaceFront(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index, z;
	Text x;

	wcout << "Replace front of ";
	index = getIndex();
	if (index == 1) {
		z = q1.length();
		if (z > 0) {
			getText(x);
			q1.replaceFront(x);
		} // end if
	} else {
		z = q2.length();
		if (z > 0) {
			getText(x);
			q2.replaceFront(x);
		} // end if
	}	// end if
	if (z > 0) {
		wcout << endl << "q" << index << ".replaceFront(x); executed." << endl;
		wcout << "x = " << x << endl;
	} else {
		wcout << "Error: |q" << index << "| = 0 - cannot replace front on an empty queue." << endl;
	} // end if
}	// doReplaceFront

//-------------------------------------------------------------------

void doFront(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index;

	wcout << "Access front of ";
	index = getIndex();
	if (index == 1) {
		if (q1.length() > 0) {
			wcout << "q1.front() = " << q1.front() << endl;
		} else {
			wcout << "Error: |q1| = 0 - cannot access front of an empty queue." << endl;
		} // end if
	} else {
		if (q2.length() > 0) {
			wcout << "q2.front() = " << q2.front() << endl;
		} else {
			wcout << "Error: |q2| = 0 - cannot access front of an empty queue." << endl;
		} // end if
	}	// end if
}	// doFront

//-------------------------------------------------------------------

void doLength(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index, z;

	wcout << "Length of ";
	index = getIndex();
	if (index == 1) {
		z = q1.length();
	} else {
		z = q2.length();
	}	// end if
	wcout << "|q" << index << "| = " << z << endl;
}	// doLength

//-------------------------------------------------------------------

void doTransferFrom(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index;

	wcout << "Transfer from ";
	index = getIndex();
	if (index == 1) {
		q2.transferFrom(q1);
		wcout << endl << "q2.transferFrom(q1); executed." << endl;
	} else {
		q1.transferFrom(q2);
		wcout << endl << "q1.transferFrom(q2); executed." << endl;
	} // end if
}	// doTransferFrom

//-------------------------------------------------------------------

void doCopy(
		PQOfText& q1,
		PQOfText& q2
	)
{
	wcout << "Copy ";
	if (getIndex() == 1) {
		q2 = q1;
		wcout << "q2 = q1; executed." << endl;
	} else {
		q1 = q2;
		wcout << "q1 = q2; executed." << endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void display(
		PQOfText& q
	)
{
	Integer i, z;
	Text x;

	wcout << "< ";
	z = q.length();
	for(i = 0; i < z; i++) {
		q.dequeue(x);
		wcout << x << " ";
		q.enqueue(x);
	}	// end for
	wcout << ">" << endl;
}	// display

//-------------------------------------------------------------------

void doDisplay(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index;

	wcout << "Display ";
	index = getIndex();
	wcout << "q" << index << " = ";
	if (index == 1) {
		wcout << q1 << endl;
	} else {
		wcout << q2 << endl;
	}	// end if
}	// doDisplay

//-------------------------------------------------------------------

void doClear(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Integer index;

	wcout << "Clear ";
	index = getIndex();
	if (index == 1) {
		q1.clear();
	} else {
		q2.clear();
	}	// end if
	wcout << endl << "q" << index << ".clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Boolean successful;
	Integer size, index;
	Text filename, x;
	File input;
	PQOfText q;

	wcout << "Enter data file name: ";
	wcin >> filename;
	wcout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		wcout << "Could not successfully open file" << endl;
	} else {
		input.read(size, successful);
		for(int i = 0; i < size; i++) {
			input.read(x, successful);
			q.enqueue(x);
		}	// end for
		input.closeFile(successful);

		wcout << "Load file into ";
		index = getIndex();
		if (index == 1) {
			q1.transferFrom(q);
		} else {
			q2.transferFrom(q);
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile(
		PQOfText& q1,
		PQOfText& q2
	)
{
	Boolean successful;
	Integer z, index;
	Text filename, x;
	File output;
	PQOfText q;

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

		// transfer contents of chosen Queue into local q.
		if (index == 1) {
			q.transferFrom(q1);
		} else {
			q.transferFrom(q2);
		}	// end if

		// write to file:
		// 1) write an Integer telling how many items are in q
		// 2) write each item found in q
		// note: 
		// after loop has finished, q must contain
		// the same values as before, in same order.
		z = q.length();
		output.write(z, successful);
		for(int i = 0; i < z; i++) {
			q.dequeue(x);
			output.write(x, successful);
			q.enqueue(x);
		}	// end for
		output.closeFile(successful);

		// transfer the contents of local q back into original
		if (index == 1) {
			q1.transferFrom(q);
		} else {
			q2.transferFrom(q);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand(
		Character command,
		Boolean& showMenu,
		PQOfText& q1,
		PQOfText& q2
	)
{
	switch(command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doEnqueue(q1, q2);
			break;
		case 'd':
			doDequeue(q1, q2);
			break;
		case 'i':
			doInject(q1, q2);
			break;
		case 'r':
			doReplaceFront(q1, q2);
			break;
		case 'f':
			doFront(q1, q2);
			break;
		case 'z':
			doLength(q1, q2);
			break;
		case 'x':
			doTransferFrom(q1, q2);
			break;
		case '=':
			doCopy(q1, q2);
			break;
		case 'l':
			inputFromFile(q1, q2);
			break;
		case 'o':
			outputToFile(q1, q2);
			break;
		case 'p':
			doDisplay(q1, q2);
			break;
		case 'c':	
			doClear(q1, q2);
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
		PQOfText& q1,
		PQOfText& q2,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, q1, q2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	PQOfText q1, q2;

	commandController(q1, q2, showMenu);
	wcout << "end program" << endl;
	return 0;
}	// end main
