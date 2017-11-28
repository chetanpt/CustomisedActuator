#include "Simbody.h"
#include <OpenSim\OpenSim.h>
#include "CustomSo.h"
#include "Trial.h"
#include "graph.h"
#include <fstream>


using namespace OpenSim;
using namespace SimTK;
using namespace std;

int main(int argc, int *argv[]){
	//customSo cSo;
	//cSo.runFixedOptimizatio();
	try
	{
		/*
		Command Line option OR Use Setting File
		1 - Model File 
		2 - Motion Data
		3 - Ground Force setting file
		4 - Results Directory
		5 - Result Prefix
		*/
		
		
		
		/*
		Current features in this solution
		1. Run static optimization on the model 
		2. Visualize the current model as is 

		TBD

		1. Organize the code
		2. take out all the parameters outside of the code. 
		3. make visualize a method 
		3. update header file 
		4. add code for adding pathspring muscle to the model as described in the earlier research 
		5. Move visualie to a class/method and implement it with some context of model scaling and 
		   editing i.e using current model of action 
		6. Logger for this application (may be, at this time not sure how to)
		7. Add copts for invalid commands
		*/

		
		//trial test;
		//test.trialMethod();
		

		/*
		Temp commented. Uncomment when needed. - Chetan
		*/
		
		customSo cSO;
		//cSO.runFixedOptimizatio();
		//cSO.viewModel();
		//cSO.addMuscle();
		//cSO.muscleForceAnalysis(); // display static optimization result; muscle force output
		cSO.testPGM();

		// Following two lines are depricated now. 
		//graph img;
		//img.drawGraph();
		
		// Define the system.

		getchar();
		
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
	/*catch (...)
	{
		std::cout << "UNRECOGNIZED EXCEPTION" << std::endl;
		return 1;
	}*/

	return 0;
}
