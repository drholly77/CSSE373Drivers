//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "List/List1.hpp"


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef List1<Text> TextList;
#else
// Compiling in Debug configuration
#include "List\ListChecking.hpp"
typedef ListChecking1<Text, List1<Text>> TextList;
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

void holdScreen(void)
{
	Text x;

	wcout << "Type Return to continue." << endl;
	wcin >> x;
}	// holdScreen

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
		wcout << "which List? 1 or 2:";
		wcin >> index;
	} while ((index < 1) || (index > 2));
	wcout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	TextList s1, s2;

	Integer i, z;
	Text x;
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);

		switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			wcout << "Add right to ";
			i = getIndex();
			wcout << "Enter text string:";
			wcin >> x;
			if (i == 1) {
				s1.addRightFront(x);
			}
			else {
				s2.addRightFront(x);
			}	// end if
			wcout << endl << "s" << i << ".addRightFront(x); executed." << endl;
			wcout << "x = " << x << endl;
			break;
		case 'd':
			wcout << "Remove right from ";
			i = getIndex();
			if (i == 1) {
				z = s1.rightLength();
				if (z > 0) {
					s1.removeRightFront(x);
				} // end if				
			}
			else {
				z = s2.rightLength();
				if (z > 0) {
					s2.removeRightFront(x);
				} // end if	
			}	// end if

			if (z > 0) {
				wcout << endl << "s" << i << ".removeRightFront(x); executed." << endl;
				wcout << "x = " << x << endl;
			}
			else {
				wcout << "Error: |s" << i << ".right| = 0 - cannot remove from an empty s" << i << ".right." << endl;
			} // end if
			break;
		case 'r':
			wcout << "Replace right front of ";
			i = getIndex();

			if (i == 1) {
				z = s1.rightLength();
				if (z > 0) {
					wcout << "Enter text string:";
					wcin >> x;
					s1.replaceRightFront(x);
				} // end if
			}
			else {
				z = s2.rightLength();
				if (z > 0) {
					wcout << "Enter text string:";
					wcin >> x;
					s2.replaceRightFront(x);
				}
			}	// end if
			if (z > 0) {
				wcout << endl << "s" << i << ".replaceRightFront(x); executed." << endl;
				wcout << "x = " << x << endl;
			}
			else {
				wcout << "Error: |s" << i << ".right| = 0 - cannot replace the front of an empty s" << i << ".right." << endl;
			} // end if
			break;
			break;
		case 'f':
			wcout << "Access right front ";
			if (getIndex() == 1) {
				z = s1.rightLength();
				if (z > 0) {
					wcout << "s1.rightFront() = " << s1.rightFront() << endl;
				} else {
					wcout << "Error: |s1.right| = 0 - cannot access the front of an empty s1.right." << endl;
				}
			}
			else {
				z = s2.rightLength();
				if (z > 0) {
					wcout << "s2.rightFront() = " << s2.rightFront() << endl;
				} else {
					wcout << "Error: |s2.right| = 0 - cannot access the front of an empty s2.right." << endl;
				}
			}	// end if
			break;
		case 'a':
			wcout << "Advance ";
			i = getIndex();
			if (i == 1) {
				z = s1.rightLength();
				if (z > 0) {
					s1.advance();
				} // end if
			}
			else {
				z = s2.rightLength();
				if (z > 0) {
					s2.advance();
				}
			}	// end if
			
			if (z > 0) {
				wcout << "s" << i << ".advance(); executed." << endl;
			}
			else {
				wcout << "Error: |s" << i << ".right| = 0 - cannot advance on an empty s" << i << ".right." << endl;
			} // end if
			break;
		case '<':
			wcout << "Move to start ";
			i = getIndex();
			if (i == 1) {
				s1.moveToStart();
			}
			else {
				s2.moveToStart();
			}	// end if
			wcout << "s" << i << ".moveToStart(); executed." << endl;
			break;
		case '>':
			wcout << "Move to finish ";
			i = getIndex();
			if (i == 1) {
				s1.moveToFinish();
			}
			else {
				s2.moveToFinish();
			}	// end if
			wcout << "s" << i << ".moveToFinish(); executed." << endl;
			break;
		case 's':
			s1.swapRights(s2);
			wcout << endl << "s1.swapRights(s2); executed." << endl;
			break;
		case '(':
			wcout << "Left length of ";
			i = getIndex();
			if (i == 1) {
				z = s1.leftLength();
			}
			else {
				z = s2.leftLength();
			}	// end if
			wcout << "|s" << i << ".left| = " << z << endl;
			break;
		case ')':
			wcout << "Right length of ";
			i = getIndex();
			if (i == 1) {
				z = s1.rightLength();
			}
			else {
				z = s2.rightLength();
			}	// end if
			wcout << "|s" << i << ".right| = " << z << endl;
			break;
		case 'x':
			wcout << "Transfer from ";
			i = getIndex();
			if (i == 1) {
				s2.transferFrom(s1);
				wcout << endl << "s2.transferFrom(s1); executed." << endl;
			}
			else {
				s1.transferFrom(s2);
				wcout << endl << "s1.transferFrom(s2); executed." << endl;
			} // end if
			break;
		case '=':
			wcout << "Copy ";
			i = getIndex();
			if (i == 1) {
				s2 = s1;
				wcout << "s2 = s1; executed." << endl;
			}
			else {
				s1 = s2;
				wcout << "s1 = s2; executed." << endl;
			}	// end if
			break;
		case 'l':
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
			}
			else {
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
				}
				else {
					s2.transferFrom(s);
				}	// end if
			}	// end if
		}
		break;
		case 'o':
		{
			Boolean successful;
			Integer lz, z, index;
			Text filename;
			File output;
			TextList s;

			wcout << "Enter data file name: ";
			wcin >> filename;
			wcout << endl;
			output.openFile(filename, File::openForWrite, successful);

			if (!successful) {
				wcout << "Could not successfully open file" << endl;
			}
			else {
				wcout << "Output from ";
				index = getIndex();

				if (index == 1) {
					s.transferFrom(s1);
				}
				else {
					s.transferFrom(s2);
				}	// end if

				lz = s.leftLength();
				s.moveToStart();
				z = s.rightLength();
				output.write(z, successful);
				for (int i = 0; i < z; i++) {
					output.write(s.rightFront(), successful);
					s.advance();
				}	// end for
				output.closeFile(successful);

				s.moveToStart();
				for (int i = 0; i < lz; i++) {
					s.advance();
				}	// end for

				if (index == 1) {
					s1.transferFrom(s);
				}
				else {
					s2.transferFrom(s);
				}	// end if
			}  // end if
		}
		break;
		case 'p':
			wcout << "Display ";
			i = getIndex();
			wcout << "s" << i << " = ";
			if (i == 1) {
				wcout << s1 << endl;
			}
			else {
				wcout << s2 << endl;
			}	// end if
			wcout << endl;
			break;
		case 'c':
			wcout << "Clear ";
			i = getIndex();
			if (i == 1) {
				s1.clear();
			}
			else {
				s2.clear();
			}	// end if
			wcout << endl << "s" << i << ".clear(); executed." << endl;
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
	} while (command != 'q' && command != 'Q');
	wcout << "end program" << endl;
	return 0;
}	// end main
