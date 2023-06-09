/*******************************************************************
*
*  DESCRIPTION: Atomic Model Mission Planning
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

/** include files **/
#include <math.>
#include "hfdsMissionPlanning.h" // base header
#include "message.h"         // InternalMessage ....
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"         // str2float( ... )


/*******************************************************************
* Function Name: MissionPlanning
* Description: constructor
********************************************************************/
MissionPlanning::MissionPlanning( const string &name )
: Atomic( name )
, inCompletedLanding( addInputPort( "inCompletedLanding" ) )
, outNewMission( addOutputPort( "outNewMission" ) )
, shapeFactor( 7 )
, minimumDuration( 30 )
{
	try
	{
		pDist = Distribution::create(MainSimulator::Instance().getParameter( 
			description(), "distribution"));

		MASSERT(pDist);

		register int i;
		for (i = 0 ; i < pDist->varCount() ; i++)
		{
			string parameter(MainSimulator::Instance().getParameter(
				description(), pDist->getVar(i)));
			pDist->setVar(i, str2float(parameter)) ;
		}		
	}
	catch (InvalidDistribution &e)
	{
		e.addText("The model " + description() + " has distribution problems!");
		e.print(cerr);
		MTHROW(e) ;
	}
	catch (MException &e)
	{
		MTHROW(e) ;
	}
	
	if (MainSimulator::Instance().existsParameter(description(), 
		"shapeFactor"))
	{
		string factor(MainSimulator::Instance().getParameter(
			description(), "shapeFactor"));

		if (factor != "")
		{
			shapeFactor = str2float(factor);
		}		
	}

	if (MainSimulator::Instance().existsParameter(description(), 
		"minimumDuration"))
	{
		string time(MainSimulator::Instance().getParameter(
			description(), "minimumDuration"));

		if (time != "")
		{
			minimumDuration = str2float(time);
		}		
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &MissionPlanning::initFunction()
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &MissionPlanning::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == inCompletedLanding)
	{
		// If a new aircraft has landed, restart planning
		// Get time from distribution in minutes
		float durationInMinutes = 
			fabs(distribution().get() * shapeFactor + minimumDuration);
		float durationInMs = durationInMinutes * 60.0 * 1000.0;
		Time t(0, 0, 0, durationInMs);
		holdIn(active, t);
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &MissionPlanning::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &MissionPlanning::outputFunction( const InternalMessage &msg )
{
	sendOutput(msg.time(), outNewMission, 1);
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: destructor
********************************************************************/
MissionPlanning::~MissionPlanning()
{
	delete pDist;
}
