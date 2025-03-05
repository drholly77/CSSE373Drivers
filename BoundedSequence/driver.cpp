//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "BoundedSequence/BoundedSequence1.hpp"

#ifdef NDEBUG
typedef BoundedSequence1 <Text, 6> TextSequence;
#else
#include "BoundedSequence/BoundedSequenceChecking.hpp"
typedef BoundedSequenceChecking1<Text, 6, BoundedSequence1 <Text, 6>> TextSequence;
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
	wcout << "        e - add" << endl;
	wcout << "        d - remove" << endl;
	wcout << "        r - replace entry" << endl;
	wcout << "        f - access entry" << endl;
	wcout << "        x - transfer from" << endl;
	wcout << "        a - append" << endl;
	wcout << "        s - split" << endl;
	wcout << "        z - length" << endl;
	wcout << "        n - remaining capacity" << endl;
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
		wcout << "which Sequence? 1 or 2:";
		wcin >> index;
	} while ((index < 1) || (index > 2));
	wcout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

Integer getPosition(Integer maxAllowable)
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

void getText(Text& s)
{
	wcout << "Enter text string:";
	wcin >> s;
}	// getText

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	TextSequence s1, s2;
	Character command;
	Integer i, p, size;
	Text x;

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
			wcout << "Add to ";
			i = getIndex();
			if (i == 1) {
				p = getPosition(s1.length());
				getText(x);
				s1.add(p, x);
			}
			else {
				p = getPosition(s2.length());
				getText(x);
				s2.add(p, x);
			} // end if
			wcout << endl << "s" << i << ".add(" << p << ", x); executed." << endl;
			wcout << "x = " << x << endl;;
			break;
		case 'd':
			wcout << "Remove from ";
			i = getIndex();
			if (i == 1) {
				p = getPosition(s1.length() - 1);
				s1.remove(p, x);

			}
			else {
				p = getPosition(s2.length() - 1);
				s2.remove(p, x);
			} // end if
			wcout << endl << "s" << i << ".remove(" << p << ", x); executed." << endl;
			wcout << "x = " << x << endl;
			break;
		case 'r':
			wcout << "Replace entry from ";
			i = getIndex();
			if (i == 1) {
				p = getPosition(s1.length() - 1);
				getText(x);
				s1.replaceEntry(p, x);
			}
			else {
				p = getPosition(s2.length() - 1);
				getText(x);
				s2.replaceEntry(p, x);
			} // end if
			wcout << endl << "s" << i << ".replaceEntry(" << p << ", x); executed." << endl;
			wcout << "x = " << x << endl;
			break;
		case 'a':
			wcout << "Append ";
			i = getIndex();
			if (i == 1) {
				s2.append(s1);
				wcout << "s2.append(s1); executed." << endl;
			}
			else {
				s1.append(s2);
				wcout << "s1.append(s2); executed." << endl;
			} // end if
			break;
		case 's':
			wcout << "Split ";
			i = getIndex();
			if (i == 1) {
				p = getPosition(s1.length());
				s1.split(p, s2);
				wcout << "s1.split(" << p << ", s2); executed." << endl;
			}
			else {
				p = getPosition(s2.length());
				s2.split(p, s1);
				wcout << "s2.split(" << p << ", s1); executed." << endl;
			} // end if
			break;
		case 'f':
			wcout << "Access entry in ";
			i = getIndex();
			if (i == 1) {
				p = getPosition(s1.length() - 1);
				wcout << "s1.entry(" << p << ") = " << s1.entry(p) << endl;
			}
			else {
				p = getPosition(s2.length() - 1);
				wcout << "s2.entry(" << p << ") = " << s2.entry(p) << endl;
			} // end if
			break;
		case 'z':
			wcout << "Length of ";
			i = getIndex();
			if (i == 1) {
				size = s1.length();
			}
			else {
				size = s2.length();
			} // end if
			wcout << "|s" << i << "| = " << size << endl;
			break;
		case 'n':
			wcout << "Remaining capacity of ";
			i = getIndex();
			if (i == 1) {
				size = s1.remainingCapacity();
			}
			else {
				size = s2.remainingCapacity();
			}	// end if
			wcout << "s" << i << " remaining capacity = " << size << endl;
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
		case 'c':
			wcout << "Clear ";
			i = getIndex();
			if (i == 1) {
				s1.clear();
			}
			else {
				s2.clear();
			} // end if
			wcout << "s" << i << ".clear(); executed." << endl;
			break;
		case 'l':
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
			}
			else {
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
				}
				else {
					s2.transferFrom(s);
				} // end if
			}	// end if
		}
		break;
		case 'o':
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
			}
			else {
				wcout << "Output from ";
				index = getIndex();
				if (index == 1) {
					s.transferFrom(s1);
				}
				else {
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
				}
				else {
					s2.transferFrom(s);
				} // end if
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
			} // end if
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
	} while (command != 'q' && command != 'Q');
	wcout << "end program" << endl;
	return 0;
}	// end main
