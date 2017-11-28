#include "pendulum.h"


pendulum::pendulum()
{
	// Define the system.
	MultibodySystem system;
	SimbodyMatterSubsystem matter(system);
	GeneralForceSubsystem forces(system);
	SimTK::Force::Gravity gravity(forces, matter, -YAxis, 9.8);

	// Describe mass and visualization properties for a generic body.
	
	SimTK::Body::Rigid bodyInfo(MassProperties(1.0, Vec3(0), UnitInertia(1)));
	bodyInfo.addDecoration(Transform(), DecorativeSphere(0.1));

	// Create the moving (mobilized) bodies of the pendulum.
	MobilizedBody::Pin pendulum1(matter.Ground(), Transform(Vec3(0)),
		bodyInfo, Transform(Vec3(0, 1, 0)));
	MobilizedBody::Pin pendulum2(pendulum1, Transform(Vec3(0)),
		bodyInfo, Transform(Vec3(0, 1, 0)));

	// Set up visualization.
	Visualizer viz(system);
	system.addEventReporter(new Visualizer::Reporter(viz, 0.01));

	// Initialize the system and state.
	State state = system.realizeTopology();
	pendulum2.setRate(state, 5.0);

	// Simulate for 20 seconds.
	RungeKuttaMersonIntegrator integ(system);
	TimeStepper ts(system, integ);
	ts.initialize(state);
	ts.stepTo(20.0);

}