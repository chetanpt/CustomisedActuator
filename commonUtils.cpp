#include <OpenSim/OpenSim.h>
#include "commonUtils.h"

using namespace SimTK;
using namespace std;
using namespace OpenSim;


/*
Add getMax method for the Array<double>for max
*/
double commonUtils::getMax(Array<double> dataList, String dataIdentifier){
	double temp = 0.0;
	for (size_t i = 0; i < dataList.getSize(); i++)
	{
		if (dataList[i] > temp){
			temp = dataList[i];
		}
	}
	cout << "IN: max force for " << dataIdentifier << " " << temp << "\n";
	return temp;
}