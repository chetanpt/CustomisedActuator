#include "CustomSo.h"
#include "graph.h"
#include "pgmActuator.h"


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
	//osimModel.getMultibodySystem().realize(si, Stage::);
	
	//osimModel.updMatterSubsystem().setShowDefaultGeometry(true);
	const ModelVisualizer& modelViz = osimModel.getVisualizer();
	const Visualizer& viz = modelViz.getSimbodyVisualizer();

	viz.drawFrameNow(si);
	//viz.setWindowTitle("PathSpring Endpoint Identification");

	getchar();
}

void customSo::addMuscle(){
	string model = "D:\\Work\\SampleData\\subject01_RRA_Adjusted.osim";
	string modelPathspring = "D:\\Work\\SampleData\\subject01_RRA_Adjusted_clutchedpathspring.osim";
	Model* osimModel = new Model(model);
	osimModel->setName("modelClutchedPathSpringController");
	//osimModel->initSystem();

	/* Define pathspring with properties */
	double restlength = 0.3, stiffness = 108, dissipation = .44, strechLength = 0.5;
	ClutchedPathSpring* leftSpring = new ClutchedPathSpring("leftleg", stiffness, dissipation, 0.01, 0.5);

	/* Define body parts for the endpoints of the spring. */
	OpenSim::Body body, body2;
	int index = osimModel->getBodySet().getIndex("femur_l");
	body = osimModel->getBodySet()[index];
	cout << index << " and " << body << "\n";

	int index2 = osimModel->getBodySet().getIndex("tibia_l");
	body2 = osimModel->getBodySet()[index2];
	cout << index2 << " and " << body2 << "\n";
	
	/* Update geometry path in the pathspring*/
	leftSpring->updGeometryPath().appendNewPathPoint("femur_l_start", body, Vec3(0.113487, 0.0279152, -0.0287838));
	leftSpring->updGeometryPath().appendNewPathPoint("tibia_l_end", body2, Vec3(0.117681, -0.104413, -0.0260623));
	
	cout << "Test Update Geometry\n";

	/* Write updated model with added pathspring to new file */
	osimModel->addForce(leftSpring);

	cout << "Test Add Force\n";
	/*
	Code segment below is taken from reference from
	https :// github.com/opensim-org/opensim-core/blob/4ccecb05096e1faa970acc5fb78e6cca33e95c26/OpenSim/Actuators
	/Test/testActuators.cpp
	to control the pathspring muscle used in this simultaion.
	This use is for learning purpose. Not used commercially.
	*/
	cout << "Test Prescribed controller \n";

	PrescribedController* controller = new PrescribedController();
	controller->addActuator(*leftSpring);
	controller->setName("artificialMuscle");
	cout << "Test Prescribed controller \n";

	// Control greater than 1 or less than 0 should be treated as 1 and 0 respectively.
	double     timePts[4] = { 0.1, 0.76, 1.3, 1.9 };
	double clutchOnPts[4] = { -0.5, 1, -1.0, 1 };

	PiecewiseConstantFunction* controlfunc =
	new PiecewiseConstantFunction(4, timePts, clutchOnPts);

	controller->prescribeControlForActuator("leftleg", controlfunc);
	osimModel->addController(controller);

	/*
	Until Here
	*/
	

	//osimModel.initSystem();
	osimModel->print(modelPathspring);


}

void customSo::muscleForceAnalysis(){
	/*
	In this I am reading force generation storage file and I want to plot graph
	for selected muscle provided in parameter to the method.
	*/
	//string muscleForceFromSo = "D:\\Backup-Models\\WorkingWithStaticOptimization\\WorkingWithStaticOptimization\\ResultsSO_StrongActuators_Filter\\Scaled_Model_StaticOptimization_force.sto";
	string muscleForceFromSo = "D:\\Lab Research Documents\\Models\\Gait2392_Simbody\\modified_external_pathspring\\3DGaitModel2392-External Muscle_StaticOptimization_force.sto";
	Storage genForces(muscleForceFromSo);
	string muscleName = "rect_fem_r";
	Array<double> forceTime;
	Array<double> muscleForce;
	//cout << genForces.getColumnLabels() << "\n";
	genForces.getTimeColumnWithStartTime(forceTime, genForces.getFirstTime());
	genForces.getDataColumn(muscleName, muscleForce);
	cout << genForces.getFirstTime() << "\n";
	cout << genForces.getLastTime() << "\n";
	
	//cout << muscleForce.getLast() << "\n";
	//cout << muscleForce.getCapacity() << "\n";
	//cout << muscleForce.getSize() << "\n";
	//cout << "OUT: max force for " << muscleName << "  " << getMax(muscleForce, muscleName) << "\n";
	cout << customSo::getMaxFromList(muscleForce, muscleName) << "\n";
	graph grp;
	grp.drawDataGraph(forceTime, muscleForce, genForces.getLastTime(), customSo::getMaxFromList(muscleForce, muscleName));

}

double customSo::getMaxFromList(Array<double> dataList, string indentifier){
	double temp = 0.0;
	for (size_t i = 0; i < dataList.getSize(); i++)
	{
		if (dataList[i] > temp){
			temp = dataList[i];
		}
	}
	cout << "IN - max force for " << indentifier << " " << temp << endl;
	return temp;
}

void customSo::pendulum(){
	
}

int customSo::testPGM(){
	try {
		// Step 1: Create an OpenSim model and set its name

		Model osimModel;
		osimModel.setName("lowerlimbmodel");
		osimModel.setAuthors("Chetan Thakur");

		/* Step2: Set Gravitiy, Set Ground and Set display geometry*/
		Vec3 gravity = osimModel.getGravity();
		OpenSim::Body& ground = osimModel.getGroundBody();
		ground.addDisplayGeometry("checkered_floor.vtp");
		/*
		Create bodies and connect them in the following sections
		*/

		// Experiment 1: Create a rod start from 0 to 50 i.e. 50 cm length in negative y direction 
		// mass of the rod is 500 gram

		double mass = 5, linkLength = 0.5, linkDiameter = 0.05;
		Vec3 linkDimension(linkDiameter, linkLength, linkDiameter);
		Vec3 linkMassCenter(0, linkLength / 2, 0);
		Inertia linkInertia = Inertia::cylinderAlongY(linkDiameter / 2.0, linkLength / 2.0);
		// Create the body now
		OpenSim::Body* link1 = new OpenSim::Body("link1", mass, linkMassCenter, mass*linkInertia);

		// assign display geometry to link1

		link1->addDisplayGeometry("cylinder.vtp");
		// scale the geometry to match the size of link
		GeometrySet& geometry = link1->updDisplayer()->updGeometrySet();
		std::cout << geometry << std::endl;
		DisplayGeometry& thinCylinder = geometry[0];
		thinCylinder.setScaleFactors(linkDimension);
		thinCylinder.setTransform(Transform(Vec3(0.0, linkLength / 2, 0.0)));


		// Body for experiment 2: Ogawa experiment. 
		// i.e. one end is fixed and other end is free connected with block of certain mass
		// acting as load.
		// We create a block as load connected to the free end.
		double blockmass = 1, blockSideLength = 0.1;
		Vec3 blockMassCenter(0);
		Inertia blockInertia = blockmass* Inertia::brick(blockSideLength, blockSideLength, blockSideLength);
		OpenSim::Body *block = new OpenSim::Body("block", blockmass, blockMassCenter, blockInertia);
		block->addDisplayGeometry("block.vtp");
		// scaling the apperance of the block geometry
		block->updDisplayer()->updGeometrySet()[0].setScaleFactors(Vec3(0.5));


		// Add bodies to model. Just adding the body does not work. All the bodies must be
		// conntected i.e. there should be joint 
		osimModel.addBody(link1);
		//osimModel.addBody(block);

		// Create a block of mass 1Kg
		// create 1DOF joint between ground and link1
		/*
		(0.0,0.5,0.0) connects ground with rod at end of the rod and
		due to no change in orientation of the rod the rod goes straignt down in negative Y-axis
		*/

		Vec3 orientationInGround(0), locationInGround(0), locationInParent(0.0, linkLength, 0.0),
			orientationInChild(0), locationInChild(0.0, 0.5, 0.0);

		//WeldJoint *muscleLoad = new WeldJoint("muscleLoad", ground, Vec3(1, 0, 0), orientationInGround, 
		//*block, Vec3(0), Vec3(0));
		// PinJoint 
		PinJoint *hip = new PinJoint("hip", ground, locationInGround, orientationInGround, *link1,
			locationInChild, orientationInChild);

		// Now assign the range of motion in radians. 
		// Note while programming opensim support setting coordianates range as radians only. 


		double range[2] = { 0.0, SimTK::Pi / 2 };
		CoordinateSet& hipCoordinateSet = hip->upd_CoordinateSet();
		hipCoordinateSet[0].setName("q1");
		hipCoordinateSet[0].setRange(range);

		/*
		* Create a PGM and set muscle length to 30 cm and print the value
		*/


		PgmActuator *pgm = new PgmActuator("PGM", 0.3, 0.5);
		pgm->addNewPathPoint("ground_1", ground, Vec3(0.30, 0, 0));
		pgm->addNewPathPoint("link_1", *link1, Vec3(0, 0, 0));
		//pgm->addNewPathPoint("block", *block, Vec3(0.05, 0.05, 0.05));

		std::cout << "PGM rest Length" << pgm->getPgmRestLength() << std::endl;

		/*
		Now we connect the actuator from (10,0,0) on X-axis and (0,-50,0 ) on Y axis
		We will use clutched path spring to swing the rod upon actuation of the spring
		reference for use of clutched path spring @
		*/

		/*
		double restlength = 0.3, stiffness = 440, dissipation = 2.7, strechLength = 0.5;
		ClutchedPathSpring* pgmAssist = new ClutchedPathSpring("PGM", stiffness, dissipation, 0.01,.5);
		pgmAssist->addNewPathPoint("ground_1_Start", ground, Vec3(0.1, 0, 0.0));
		pgmAssist->addNewPathPoint("link1_1_end", *link1, Vec3(0.0, 0.0, 0.0));


		*/
		/*
		Add the muscle to the model now. Use addForce method
		*/

		//osimModel.addForce(pgmAssist);
		osimModel.addForce(pgm);

		/*
		Now add controller for the force to make swing motion of the rod
		*/

		PrescribedController* controller = new PrescribedController();
		/*
		controller->addActuator(*pgmAssist);
		controller->setName("pgmController");
		*/
		controller->setActuators(osimModel.updActuators());
		controller->addActuator(*pgm);

		// below is simulation time and control values. For this actuator the control values can be 0 or 1
		// negative is trated as sero and positive is treated as 1

		//double     timePts[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Time series for simulation and changes in supply air pressure 
		//double clutchOnPts[12] = { 0, 0, 0.05, 0.05, 0.1, 0.1, 0.05, 0.05, 0, 0.2, 0, 0 }; // Test case for 50 Kpa
		//double clutchOnPts[12] = { 0.2, 0.1, 0.1 , 0.3, 0, 0.1, 0.1, 0, 0, 0.2, 0, 0}; // Test Case for randomness
		//double clutchOnPts[12] = { 0, 0, 0, 0, 0.1, 0.1, 0, 0, 0, 0, 0, 0 }; // Test case for 100 Kpa

		//For Test purpose we will use smaller simulation and one combination of pressure and load 
		double     timePts[12] = { 0, 1, 2, 3, 4, 5, 6 };
		//double clutchOnPts[12] = { 0, 0, 0, 0, 0, 0, 0 };
		double clutchOnPts[12] = { 0, 0, 0.05, 0.05, 0.05, 0, 0 };
		//double clutchOnPts[12] = { 0, 0, 0.1, 0.1, 0.1, 0, 0 };
		//double clutchOnPts[12] = { 0, 0, 0.15, 0.15, 0.15, 0, 0 };
		//double clutchOnPts[12] = { 0, 0, 0.2, 0.2, 0.2, 0, 0 };
		//double clutchOnPts[12] = { 0, 0, 0.25, 0.25, 0.25, 0, 0 };
		//double clutchOnPts[12] = { 0, 0, 0.3, 0.3, 0.3, 0, 0 };

		PiecewiseConstantFunction* controlFunction = new PiecewiseConstantFunction(7, timePts, clutchOnPts);
		controller->prescribeControlForActuator("", controlFunction);
		//controller->prescribeControlForActuator("", new PiecewiseLinearFunction(12))
		osimModel.addController(controller);

		// acceleration due to gravity
		osimModel.setGravity(Vec3(0.0, -9.81, 0.0));

		/*Enable visualization of created model and simulation*/
		osimModel.setUseVisualizer(true);

		/*
		Get the model ready for simulation and visualizat
		1. Initializa the system
		2. Integrate system (i.e. multibody system using SimTK::RungeKuttaMersonIntegrator
		3. Create Manager
		4. Integrate manager with states created in step 1
		5.
		*/

		SimTK::State& si = osimModel.initSystem(); //1
		SimTK::RungeKuttaMersonIntegrator integrator(osimModel.getMultibodySystem()); //2
		integrator.setAccuracy(1.0e-3);

		// this is needed to record th force generated by actuator during simulation
		ForceReporter *forces = new ForceReporter(&osimModel);
		osimModel.updAnalysisSet().adoptAndAppend(forces);

		Manager manager(osimModel, integrator); //3

		//Examine the model
		osimModel.printDetailedInfo(si, std::cout);
		//save the model
		osimModel.print("twolinkonejoint.osim");

		// Print initial position and velocity
		si.getQ().dump("Initial q's");
		si.getU().dump("Initial u's");
		std::cout << "Initial time:" << si.getTime() << std::endl;


		// for visualizing simulation the start and end time of simulation must be visible
		double t0 = 0.0, tf = 8;
		//tf is 6 seconds for experiment purpose. else it can be based on the experiment requirements e.g. tf = 12;
		manager.setInitialTime(t0); manager.setFinalTime(tf);

		manager.integrate(si);
		osimModel.printControlStorage("pgmActuated_Controls.sto");
		Storage statesDegree(manager.getStateStorage());
		osimModel.updSimbodyEngine().convertRadiansToDegrees(statesDegree);
		// this model motion i.e. motion file for replaying for postprocessing
		statesDegree.print("pgmActuated_degrees.mot");

		forces->getForceStorage().print("pgm_forces.mot");


		// saving the results

		//getchar(); // This waits for user input and keeps the visualization window open 

	}
	catch (OpenSim::Exception ex)
	{
		std::cout << ex.getMessage() << std::endl;
		return 1;
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cout << "UNRECOGNIZED EXCEPTION" << std::endl;
		return 1;
	}

	std::cout << "OpenSim example completed successfully.\n";
	//std::cin.get();
}