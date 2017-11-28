#include "PgmActuator.h"
using namespace OpenSim;
using namespace std;

using std::string;
using SimTK::Vec3; using SimTK::Vector_; using SimTK::Vector;
using SimTK::SpatialVec; using SimTK::UnitVec3; using SimTK::State;

// Default Constructor
PgmActuator::PgmActuator(){
	constructProperties();
}

PgmActuator::PgmActuator(const string& name, double restLength, double pgm_SlackLength){
	constructProperties();
	set_pgm_rest_length(restLength);
}

//Construct and initialize properties

void PgmActuator::constructProperties(){
	setAuthors("Chetan Thakur");
	constructProperty_pgm_rest_length(0.3);
	constructProperty_pgmSlackLength(0.5);
}

double PgmActuator::computeActuation(const SimTK::State& s) const {
	if (!_model) return 0;
	std::ofstream writer("force-length.csv", std::ofstream::app);
	//writer << "presure," << "displacement," << "elongation," << "force" << "\n" ;


	// lengthing speed


	//

	double length = getLength(s) - getPgmRestLength();
	double pressure = getControl(s);
	//cout << get_pgmSlackLength() << "\n" ; 

	// calculate force from linear equation based on ogawa et. al. data
	// e.g. following equation

	// this is test, double force = length * pressure;
	// this is incorrect, double force = 5E-06 * pow(length, 3) - 0.0057* pow(length, 2) + 2.1714* length - 274; // 3rd order poly for 100Kpa
	// Equation below is based on displacement of the PGM for 100 Kpa which gives the approximate value of force generated
	double force;
	if (pressure == 0.05){
		force = 0.9223 * exp(length * 27.55); // (I forgot what this number is. But anyway I woould like to keep it.) 3.2453;
	}
	else if (pressure == 0.1){
		force = 3120 * pow(length, 2) - 137.42 * length + 3.2453;
	}
	else if (pressure == 0.15)
	{
		force = 1976.2 * pow(length, 2) + 85.142 * length + 1.273;
	}
	else if (pressure == 0.2)
	{
		force = 380.39 * length - 1.5864;
	}
	else if (pressure = 0.25)
	{
		//cout << "pressure si : " << pressure << "\n";
		force = 434.44 * length - 0.6295;
	}
	else if (pressure == 0.3)
	{
		force = 573.48 * length - 1.3627;
	}
	else{
		// This is the condition where there is no air pressure supply. 
		cout << "pressure si : " << pressure << "\n";
		// force = 4 * pow(10,-06) * exp(length*1.0172); => I do not know why i had this force for no pressure
		force = 0.0092 * exp(length * 58.43);
	}

	//std::cout << length << "," << getLength(s) << "," << force << "\n";
	if (writer.is_open()){
		writer << getControl(s) << "," << pressure << "," << length << "," << getLength(s) << "," << force << ", " << getGeometryPath().getLengtheningSpeed(s) << "\n";
	}
	else{
		std::cout << "Error opening File for writing" << "\n";
	}
	writer.close();

	//std::cout << length << "," << getLength(s) << "," << getForce(s) << "\n" ;
	setForce(s, force);

	// setActuation(s, force); => what does setActuation do ? => answer is it sets force at that respective state. 
	// in opensim 3.3 it is setForce in opensim 4 it is setActuation (online code is setActuation, thats why the confusion

	return(force);
}

// Apply the actuator force to some path or body

/* The computeForce method is the meat of this simple actuator example.  It
** computes the direction and distance between the two application points.  It
** then uses the difference between it's current length and rest length to determine
** the force magnitude, then applies the force at the application points, in the
** direction between them. */

void PgmActuator::computeForce(const SimTK::State& s,
	SimTK::Vector_<SimTK::SpatialVec>& bodyForces,
	SimTK::Vector& generalizedForces) const{

	double actuation = computeActuation(s);

	getGeometryPath().addInEquivalentForces(s, actuation, bodyForces, generalizedForces);
}

void PgmActuator::ConnectToModel(Model& model){
	Super::connectToModel(model);
}