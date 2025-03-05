//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "Sequence\Sequence1.hpp"

#ifdef NDEBUG
typedef Sequence1 <Text> TextSequence;
#else
#include "Sequence\SequenceChecking.hpp"
typedef SequenceChecking1<Sequence1, Text> TextSequence;
#endif


//-------------------------------------------------------------------
// program operations
//-------------------------------------------------------------------

void displayMenu(void)
{
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;
	cout << "     Command -  Result" << endl;
	cout << "        g - toggle display menu" << endl;
	cout << "        e - add" << endl;
	cout << "        d - remove" << endl;
	cout << "        r - replace entry" << endl;
	cout << "        f - access entry" << endl;
	cout << "        x - transfer from" << endl;
	cout << "        a - append" << endl;
	cout << "        s - split" << endl;
	cout << "        z - length" << endl;
	cout << "        = - copy" << endl;
	cout << "        l - load from file" << endl;
	cout << "        o - output to file" << endl;
	cout << "        p - display" << endl;
	cout << "        c - clear" << endl;
	cout << "        q - quit program" << endl;
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl << "        command:";
}	// showMenu

//-------------------------------------------------------------------

void getCommand(Character& command)
{
	cin >> command;
	cout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex(void)
{
	Integer index;

	do {
		cout << "which Sequence? 1 or 2:";
		cin >> index;
	} while ((index < 1) || (index > 2));
	cout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

Integer getPosition(Integer maxAllowable)
{
	Integer position;

	do {
		cout << "which position? 0 .. " << maxAllowable << ":";

		cin >> position;
		cout << endl;
	} while ((position < 0) || (position > maxAllowable));
	return (position);
}	// getPosition

//-------------------------------------------------------------------

void getText(Text& s)
{
	cout << "Enter text string:";
	cin >> s;
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
			cout << "Add to ";
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
			cout << endl << "s" << i << ".add(" << p << ", x); executed." << endl;
			cout << "x = " << x << endl;;
			break;
		case 'd':
			cout << "Remove from ";
			i = getIndex();
			if (i == 1) {
				size = s1.length();
				if (size > 0) {
					p = getPosition(size - 1);
					s1.remove(p, x);
				} // end if
			}
			else {
				size = s2.length();
				if (size > 0) {
					p = getPosition(size - 1);
					s2.remove(p, x);
				} // end if
			} // end if

			if (size > 0) {
				cout << endl << "s" << i << ".remove(" << p << ", x); executed." << endl;
				cout << "x = " << x << endl;
			}
			else {
				cout << "Error: |s" << i << "| = 0 - cannot Remove from an empty sequence." << endl;
			} // end if
			break;
		case 'r':
			cout << "Replace entry from ";
			i = getIndex();
			if (i == 1) {
				size = s1.length();
				if (size > 0) {
					p = getPosition(size - 1);
					getText(x);
					s1.replaceEntry(p, x);
				} // end if
			}
			else {
				size = s2.length();
				if (size > 0) {
					p = getPosition(size - 1);
					getText(x);
					s2.replaceEntry(p, x);
				} // end if
			} // end if

			if (size > 0) {
				cout << endl << "s" << i << ".replaceEntry(" << p << ", x); executed." << endl;
				cout << "x = " << x << endl;
			}
			else {
				cout << "Error: |s" << i << "| = 0 - cannot replace an entry in an empty sequence." << endl;
			} // end if
			break;
		case 'a':
			cout << "Append ";
			i = getIndex();
			if (i == 1) {
				s2.append(s1);
				cout << "s2.append(s1); executed." << endl;
			}
			else {
				s1.append(s2);
				cout << "s1.append(s2); executed." << endl;
			} // end if
			break;
		case 's':
			cout << "Split ";
			i = getIndex();
			if (i == 1) {
				p = getPosition(s1.length());
				s1.split(p, s2);
				cout << "s1.split(" << p << ", s2); executed." << endl;
			}
			else {
				p = getPosition(s2.length());
				s2.split(p, s1);
				cout << "s2.split(" << p << ", s1); executed." << endl;
			} // end if
			break;
		case 'f':
			cout << "Access entry in ";
			i = getIndex();
			if (i == 1) {
				size = s1.length();
				if (size > 0) {
					p = getPosition(size - 1);
					cout << "s1.entry(" << p << ") = " << s1.entry(p) << endl;
				} // end if
			}
			else {
				size = s2.length();
				if (size > 0) {
					p = getPosition(size - 1);
					cout << "s2.entry(" << p << ") = " << s2.entry(p) << endl;
				} // end if
			} // end if
			if (size == 0) {
				cout << "Error: |s" << i << "| = 0 - cannot access an empty sequence." << endl;
			} // end if
			break;
		case 'z':
			cout << "Length of ";
			i = getIndex();
			if (i == 1) {
				size = s1.length();
			}
			else {
				size = s2.length();
			} // end if
			cout << "|s" << i << "| = " << size << endl;
			break;
		case 'x':
			cout << "Transfer from ";
			i = getIndex();
			if (i == 1) {
				s2.transferFrom(s1);
				cout << endl << "s2.transferFrom(s1); executed." << endl;
			}
			else {
				s1.transferFrom(s2);
				cout << endl << "s1.transferFrom(s2); executed." << endl;
			} // end if
			break;
		case '=':
			cout << "Copy ";
			i = getIndex();
			if (i == 1) {
				s2 = s1;
				cout << "s2 = s1; executed." << endl;
			}
			else {
				s1 = s2;
				cout << "s1 = s2; executed." << endl;
			}	// end if
			break;
		case 'c':
			cout << "Clear ";
			i = getIndex();
			if (i == 1) {
				s1.clear();
			}
			else {
				s2.clear();
			} // end if
			cout << "s" << i << ".clear(); executed." << endl;
			break;
		case 'l':
		{
			Boolean successful;
			Integer i, size, index;
			Text filename, x;
			File input;
			TextSequence s;

			cout << "Enter data file name: ";
			cin >> filename;
			cout << endl;

			input.openFile(filename, File::openForRead, successful);

			if (!successful) {
				cout << "Could not successfully open file: " << filename << endl;
			}
			else {
				input.read(size, successful);
				for (i = 0; i < size; i++) {
					input.read(x, successful);
					s.add(0, x);
				}	// end for
				input.closeFile(successful);

				cout << "Load file into ";
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

			cout << "Enter data file name: ";
			cin >> filename;
			cout << endl;

			output.openFile(filename, File::openForWrite, successful);

			if (!successful) {
				cout << "Could not successfully open file" << endl;
			}
			else {
				cout << "Output from ";
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
			cout << "Display ";
			i = getIndex();
			cout << "s" << i << " = ";
			if (i == 1) {
				cout << s1 << endl;
			}
			else {
				cout << s2 << endl;
			} // end if
			break;
		case 'q':
			cout << "Quit Command Interpreter" << endl;
			break;
		case '@':
			cout << "Authored by Dr. Holly" << endl;
			break;
		default:
			cout << "Unknown command: " << command << endl;
			cout << "Please reenter your command" << endl;
			break;
		}	// end switch
	} while (command != 'q' && command != 'Q');
	cout << "end program" << endl;
	return 0;
}	// end main
