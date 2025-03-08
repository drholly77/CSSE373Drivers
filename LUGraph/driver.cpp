#include "Wrapper.h"
#include "LUGraphInst.h"


//-------------------------------------------------------------------

void displayMenu(void)
//! ensures: a menu of commands to all user to manipulate a queue is displayed to the user
{
	std::wcout << endl;
	wcout << "---------------------------------------------" << endl;
	wcout << endl;
	wcout << "     Command -  Result" << endl;
	wcout << "        g - toggle display menu" << endl;
	wcout << "        S - setNumberVertices" << endl;
	wcout << "        e - addEdge" << endl;
	wcout << "        d - removeEdge" << endl;
	wcout << "        i - doRemoveAnyIncidentEdge" << endl;
	wcout << "        1 - doRemoveAnyEdge" << endl;
	wcout << "        z - numberOfEdges" << endl;
	wcout << "        v - doNumberOfVertices" << endl;
	wcout << "        ? - doIsEdge" << endl;
	wcout << "        x - transferFrom" << endl;
	wcout << "        = - copy" << endl;
	wcout << "        o - degree" << endl;
	wcout << "        p - display" << endl;
	wcout << "        c - clear" << endl;
	wcout << "        q - quit program" << endl;
	wcout << endl;
	wcout << "---------------------------------------------" << endl;
	wcout << endl << "        command:";
}	// showMenu


//-------------------------------------------------------------------

void getCommand(Character& command)
//! replaces command
//! ensures: getCommand = a keyboard character entered by the user
{
	wcin >> command;
	wcout << endl;
}	// getCommand

	//-------------------------------------------------------------------

Integer getIndex(void)
//! ensures: getIndex = 1 or getIndex = 2 
{
	Integer index;

	do {
		wcout << "which Graph? 1 or 2:";
		wcin >> index;
	} while ((index < 1) || (index > 2));
	wcout << endl;
	return index;
}	// getIndex

	//-------------------------------------------------------------------

void getNumberOfVertices(Integer& vertexCount)
{
	do {
		wcout << "Enter a vertex count:";
		wcin >> vertexCount;
	} while (vertexCount < 1);
	wcout << endl;
}	// getNumberOfVertices

	//-------------------------------------------------------------------

void getVertexNumber(Integer& vertexNumber, Integer edgeMax)
{
	do {
		wcout << "Enter a vertex #:";
		wcin >> vertexNumber;
	} while ((vertexNumber < 1) || (vertexNumber > edgeMax));
}	// getVertexNumber

	//-------------------------------------------------------------------

void doSetNumberVertices(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index, nv;

	wcout << "setNumberOfVertices for ";
	index = getIndex();
	getNumberOfVertices(nv);
	if (index == 1) {
		g1.setNumberOfVertices(nv);
	}
	else {
		g2.setNumberOfVertices(nv);
	}	// end if
	wcout << endl << "g" << index << ".setNumberOfVertices(nv); executed." << endl;
	wcout << "nv = " << nv << endl;
}	// doSetNumberVertices


//-------------------------------------------------------------------

void doAddEdge(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index, v1, v2;

	wcout << "addEdge to ";
	index = getIndex();

	if (index == 1) {
		getVertexNumber(v1, g1.numberOfVertices());
		getVertexNumber(v2, g1.numberOfVertices());
		if (v1 > v2) {
			Integer temp = v1;
			v1 = v2;
			v2 = temp;
		}
		g1.addEdge(v1, v2);
	}
	else {
		getVertexNumber(v1, g2.numberOfVertices());
		getVertexNumber(v2, g2.numberOfVertices());
		if (v1 > v2) {
			Integer temp = v1;
			v1 = v2;
			v2 = temp;
		}
		g2.addEdge(v1, v2);
	}	// end if
	wcout << endl << "g" << index << ".addEdge(v1, v2); executed." << endl;
	wcout << "v1 = " << v1 << endl;
	wcout << "v2 = " << v2 << endl;
}	// doAddEdge

//-------------------------------------------------------------------

void doRemoveEdge(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Boolean edgePresent;
	Integer index, v1, v2, numEdges;

	wcout << "removeEdge from ";
	index = getIndex();
	if (index == 1) {
		numEdges = g1.numberOfEdges();
	}
	else {
		numEdges = g2.numberOfVertices();
	} // end if

	if (numEdges > 0) {
		getVertexNumber(v1, g1.numberOfVertices());
		getVertexNumber(v2, g1.numberOfVertices());

		if (index == 1) {
			edgePresent = g1.isEdge(v1, v2);
			if (edgePresent) {
				g1.removeEdge(v1, v2);
			} // end if
		}
		else {
			edgePresent = g2.isEdge(v1, v2);
			if (edgePresent) {
				g2.removeEdge(v1, v2);
			} // end if
		}	// end if
		if (edgePresent) {
			wcout << endl << "g" << index << ".removeEdge(v1, v2); executed." << endl;
			wcout << "v1 = " << v1 << endl;
			wcout << "v2 = " << v2 << endl;
		}
		else {
			wcout << "Error: {" << v1 << "," << v2 << "} not in g" << index << endl;
		} // end if
	}
	else {
		wcout << "Error: |g" << index << ".edges| = 0" << endl;
	}
}	// doRemoveEdge

//-------------------------------------------------------------------

void doRemoveAnyIncidentEdge(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index, v1, v2, degree, numEdges;

	wcout << "removeAnyIncidentEdge from ";
	index = getIndex();
	if (index == 1) {
		numEdges = g1.numberOfEdges();
	}
	else {
		numEdges = g2.numberOfVertices();
	} // end if


	if (numEdges > 0) {
		if (index == 1) {
			getVertexNumber(v1, g1.numberOfVertices());
			degree = g1.degree(v1);
			if (degree > 0) {
				g1.removeAnyIncidentEdge(v1, v2);
			} // end if
		}
		else {
			getVertexNumber(v1, g2.numberOfVertices());
			degree = g2.degree(v1);
			if (degree > 0) {
				g2.removeAnyIncidentEdge(v1, v2);
			} // end if
		}	// end if
		if (degree > 0) {
			wcout << endl << "g" << index << ".removeAnyIncidentEdge(v1, v2); executed." << endl;
			wcout << "v1 = " << v1 << endl;
			wcout << "v2 = " << v2 << endl;
		}
		else {
			wcout << "Error: vertex " << v1 << "'s degree = " << degree << endl;
		} // end if
	}
	else {
		wcout << "Error: |g" << index << ".edges| = 0" << endl;
	} // end if
}	// doRemoveAnyIncidentEdge

//-------------------------------------------------------------------

void doRemoveAnyEdge(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index, v1, v2, edgeCount;

	wcout << "removeAnyEdge from ";
	index = getIndex();

	if (index == 1) {
		edgeCount = g1.numberOfEdges();
		if (edgeCount > 0) {
			g1.removeAnyEdge(v1, v2);
		} // end if
	}
	else {
		edgeCount = g2.numberOfEdges();
		if (edgeCount > 0) {
			g2.removeAnyEdge(v1, v2);
		} // end if
	}	// end if
	if (edgeCount > 0) {
		wcout << endl << "g" << index << ".removeAnyEdge(v1, v2); executed." << endl;
		wcout << "v1 = " << v1 << endl;
		wcout << "v2 = " << v2 << endl;
	}
	else {
		wcout << "Error: |g" << index << ".edges| = 0" << endl;
	} // end if
}	// doRemoveAnyEdge

//-------------------------------------------------------------------

void doNumberOfEdges(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index, z;

	wcout << "Number of edges in ";
	index = getIndex();
	if (index == 1) {
		z = g1.numberOfEdges();
	}
	else {
		z = g2.numberOfEdges();
	}	// end if
	wcout << "|g" << index << ".edges| = " << z << endl;
}	// doNumberOfEdges

//-------------------------------------------------------------------

void doNumberOfVertices(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index, z;

	wcout << "Number of vertices in ";
	index = getIndex();
	if (index == 1) {
		z = g1.numberOfVertices();
	}
	else {
		z = g2.numberOfVertices();
	}	// end if
	wcout << "|g" << index << ".vertices| = " << z << endl;
}	// doNumberOfVertices

//-------------------------------------------------------------------

void doDegree(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index, degree, v, numVertices;

	wcout << "Examine vertex from ";
	index = getIndex();
	if (index == 1) {
		numVertices = g1.numberOfVertices();
	}
	else {
		numVertices = g2.numberOfVertices();
	} // end if

	if (numVertices > 0) {
		if (index == 1) {
			getVertexNumber(v, g1.numberOfVertices());
			degree = g1.degree(v);
		}
		else {
			getVertexNumber(v, g2.numberOfVertices());
			degree = g2.degree(v);
		}	// end if
		wcout << "In g" << index << " vertex " << v << " has degree = " << degree << endl;
	}
	else {
		wcout << "Error: |g" << index << ".vertices| = 0" << endl;
	} // end if
}	// doDegree

//-------------------------------------------------------------------

void doIsEdge(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Boolean edgePresent;
	Integer index, v1, v2, numVertices;

	wcout << "Examine edge from ";
	index = getIndex();
	if (index == 1) {
		numVertices = g1.numberOfVertices();
	}
	else {
		numVertices = g2.numberOfVertices();
	} // end if
	if (numVertices > 0) {
		getVertexNumber(v1, g1.numberOfVertices());
		getVertexNumber(v2, g1.numberOfVertices());

		edgePresent = (index == 1) ? g1.isEdge(v1, v2) : g2.isEdge(v1, v2);

		if (edgePresent) {
			wcout << "{" << v1 << "," << v2 << "} is in g" << index << ".edges" << endl;
		}
		else {
			wcout << "{" << v1 << "," << v2 << "} is not in g" << index << ".edges" << endl;
		} // end if
	}
	else {
		wcout << "Error: |g" << index << ".vertices| = 0" << endl;
	}
}	// doIsEdge

	//-------------------------------------------------------------------

void doClear(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index;

	wcout << "Clear ";
	index = getIndex();
	if (index == 1) {
		g1.clear();
	}
	else {
		g2.clear();
	}	// end if
	wcout << endl << "g" << index << ".clear(); executed." << endl;
}	// doClear

	//-------------------------------------------------------------------

void doTransferFrom(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index;

	wcout << "Transfer from ";
	index = getIndex();
	if (index == 1) {
		g2.transferFrom(g1);
		wcout << endl << "g2.transferFrom(g1); executed." << endl;
	}
	else {
		g1.transferFrom(g2);
		wcout << endl << "g1.transferFrom(g2); executed." << endl;
	} // end if
}	// doTransferFrom

	//-------------------------------------------------------------------

void doCopy(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	wcout << "Copy ";
	if (getIndex() == 1) {
		g2 = g1;
		wcout << "g2 = g1; executed." << endl;
	}
	else {
		g1 = g2;
		wcout << "g1 = g2; executed." << endl;
	}	// end if
}	// doCopy

	//-------------------------------------------------------------------

void doDisplay(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	Integer index;

	wcout << "Display ";
	index = getIndex();
	wcout << "g" << index << " = ";
	if (index == 1)
		wcout << g1;
	else
		wcout << g2;
	wcout << endl;
}	// doDisplay

//-------------------------------------------------------------------

void dispatchCommand(Character command, Boolean& showMenu, UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2)
{
	switch (command) {
	case 'g':	// toggle display Menu
		showMenu = !showMenu;
		break;
	case 'S':
		doSetNumberVertices(g1, g2);
		break;
	case 'e':
		doAddEdge(g1, g2);
		break;
	case 'd':
		doRemoveEdge(g1, g2);
		break;
	case 'i':
		doRemoveAnyIncidentEdge(g1, g2);
		break;
	case '1':
		doRemoveAnyEdge(g1, g2);
		break;
	case '?':
		doIsEdge(g1, g2);
		break;
	case 'x':
		doTransferFrom(g1, g2);
		break;
	case '=':
		doCopy(g1, g2);
		break;
	case 'z':
		doNumberOfEdges(g1, g2);
		break;
	case 'v':
		doNumberOfVertices(g1, g2);
		break;
	case 'o':
		doDegree(g1, g2);
		break;
	case 'p':
		doDisplay(g1, g2);
		break;
	case 'c':
		doClear(g1, g2);
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

void commandController(UnlabeledUndirectedGraph& g1, UnlabeledUndirectedGraph& g2, Boolean& showMenu)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, g1, g2);
	} while (command != 'q' && command != 'Q');
} // commandController

  //-------------------------------------------------------------------
  // main executable body
  //-------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	UnlabeledUndirectedGraph mainG1, mainG2;

	commandController(mainG1, mainG2, showMenu);
	wcout << "end program" << endl;
	return 0;
}	// end main