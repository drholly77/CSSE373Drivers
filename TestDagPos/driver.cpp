#include "Wrapper.h"
#include "DAGPosition\DAGPosition1.hpp"

int main (int argc, char* argv[])
{

	typedef DagPosition1 <Integer, 2> TwoWayDagOfInteger;

	TwoWayDagOfInteger d1, d2, d3, d4;
	Integer x = 11;

	d1.labelNew(x);
	x = 22;
	d2.labelNew(x);
	x = 33;
	d3.labelNew(x);
	d2.swapWithTarget(0, d1);
	d2.swapWithTarget(1, d3);
	x = 44;
	d4.labelNew(x);
	d4.swapWithTarget(0, d2);

	cout << d4 << endl;

	char c;
	cin >> c;


	cout << "end program" << endl;
	return 0;
}	// end main