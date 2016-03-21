#include <OpenSim/OpenSim.h>
#include <ctime>    // for clock()
#include "CustomSo.h"

using namespace OpenSim;
using namespace SimTK;
using namespace std;

void customSo::runFixedOptimizatio(){
	string motionData = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\subject01_walk_IK.mot";
	string modelData = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\subject01.osim";
	string resultDir = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\soAutomation";
	string settingsFile = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\AutomationSo.xml";
	string bkpsettingFile = "D:\\Backup-Models\\WorkingWithStaticOptimization\\WorkingWithStaticOptimization\\Settings_ByChetan\\So_StrongActuator_Filter_Automation.xml";
	string grforce = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\subject01_walk_grf.xml";
	try{ 
		// Open Model file
		Model osimModel(modelData, true);
		osimModel.initSystem();
		// Load motion data to be used for optimization
		Storage motSo(motionData);
		// Create Static OPtimization Object
		StaticOptimization staticOpt;
		
		//State s; 
		// Create object of analyise class
		AnalyzeTool ana;
		ana.setName("ChetanTrial");
		ana.setInitialTime(motSo.getFirstTime());
		ana.setFinalTime(motSo.getLastTime());
		ana.setOutputPrecision(8);
		ana.setModel(osimModel);
		ana.setModelFilename(modelData);
		ana.setCoordinatesFileName(motionData);
		ana.setExternalLoadsFileName(grforce);
		ana.setLowpassCutoffFrequency(6);
		ana.setSolveForEquilibrium(false);
		ana.setResultsDir(resultDir);
		staticOpt.setName("ChetanSO");
		staticOpt.setStartTime(motSo.getFirstTime());
		staticOpt.setEndTime(motSo.getLastTime());
		staticOpt.setUseMusclePhysiology(true);
		
		AnalysisSet & anaSet = ana.getAnalysisSet();
	
		anaSet.setName("chetan_staticOptimization");
		anaSet.insert(0, staticOpt);
		
				
		ana.print(settingsFile);

		AnalyzeTool anaTool(bkpsettingFile);
		//ana = anaTool;
		anaTool.run();
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void customSo::muscleForceAnalysis(){
	/*
	In this I am reading force generation storage file and I want to plot graph 
	for selected muscle provided in parameter to the method.
	*/
	string muscleForceFromSo = "D:\\Backup-Models\\WorkingWithStaticOptimization\\WorkingWithStaticOptimization\\ResultsSO_StrongActuators_Filter\\Scaled_Model_StaticOptimization_force.sto";
	Storage genForces(muscleForceFromSo);
	double forceData ;
	for (size_t i = 0; i < genForces.getColumnLabels().getCapacity(); i++)
	{
		cout << genForces.getColumnLabels()[i] << " , ";
	} 
}

void customSo::viewModel(){
	/*
	This method should visualize the mode provided in the parameter to it. 
	At the same time it shuold update the changes in the model and visualize them. 
	*/
	string modelFile = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\subject01.osim";
	string updated_modelFile = "D:\\Backup-Models\\WorkingWithStaticOptimizationAutomation\\WorkingWithStaticOptimization\\subject01_updated.osim";
	Model osimModel(modelFile);
	
	osimModel.print(updated_modelFile);
	osimModel.setUseVisualizer(true);
	osimModel.updDisplayHints().setShowFrames(true);
	SimTK::State& si = osimModel.initSystem();
	osimModel.equilibrateMuscles(si);
	// TBD: Need to know what is highestRuntime is in stage of the state.
	osimModel.getMultibodySystem().realize(si, Stage::HighestRuntime);
	osimModel.getVisualizer().show(si);
}
