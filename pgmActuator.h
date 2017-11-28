#ifndef _PgmActuator_
#define	_PgmActuator_

/*
* Bsys::PgmActuator i.e. Pneumatic Gel Muscle Actuator, a low powered
* Authod::Chetan Thakur
*/


#include <OpenSim\OpenSim.h>
#include <fstream>
#include <iostream>
#include <OpenSim/Common/PiecewiseConstantFunction.h>
#include <ctime>

namespace OpenSim {

	class PgmActuator : public PathActuator {
		OpenSim_DECLARE_CONCRETE_OBJECT(PgmActuator, PathActuator);

		// Data needed for actuator to work. 
		/*
		Inputs: Air Pressure and Applied Load
		Air Pressure : From Control input or excitation editor
		Applied Load : From attached body or opensim force dynamics during simulation
		Muscle Length : length of muscle at rest typical configuration is 15, 21, 30, 45 (all units are centimeters here)
		*/
		OpenSim_DECLARE_PROPERTY(pgm_rest_length, double, "Length of muscle at rest with no supplied air pressure and load");
		OpenSim_DECLARE_PROPERTY(pgmSlackLength, double,
			"Maximum possible elongation of the PGM. The moment of the connectedobject should be restricted beyond this length");
	public:

		PgmActuator();

		PgmActuator(const std::string& name, double pgm_rest_length, double pgm_SlackLength);

		void setPgmRestLength(double pgm_rest_length){
			set_pgm_rest_length(pgm_rest_length);
		}


		double getPgmRestLength() const{
			return get_pgm_rest_length();
		}


		double computeActuation(const SimTK::State& s) const override;

	private:
		void constructProperties();

		// Force interface

		void computeForce(const SimTK::State& state,
			SimTK::Vector_<SimTK::SpatialVec>& bodyForces,
			SimTK::Vector& mobilityForces) const override;



		// Implement model component interface
		void ConnectToModel(Model& aModel);

	};


}

#endif // !_PgmActuator_
