/*******************************************************************
*
*  DESCRIPTION: Atomic Model RAST
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

/** include files **/
#include "hfdsRast.h"        // base header
#include "message.h"         // InternalMessage ....
#include "mainsimu.h"        // class MainSimulator


/*******************************************************************
* Function Name: Rast
* Description: constructor
********************************************************************/
Rast::Rast( const string &name )
: Atomic( name )
, inLandingClearance( addInputPort( "inLandingClearance" ) )
, inNewMission( addInputPort( "inNewMission" ) )
, outCompletedLanding( addOutputPort( "outCompletedLanding" ) )
, outTakeOff( addOutputPort( "outTakeOff" ) )
, durationOfLanding( 0, 10, 0, 0 )
, durationOfTakeOff( 0, 5, 0, 0 )
{
	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfLanding"))
	{
		string landingTime(MainSimulator::Instance().getParameter(
			description(), "durationOfLanding"));

		if (landingTime != "")
		{
			durationOfLanding = landingTime ;
		}		
	}

	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfTakeOff"))
	{
		string takeOffTime(MainSimulator::Instance().getParameter(
			description(), "durationOfTakeOff"));

		if (takeOffTime != "")
		{
			durationOfTakeOff = takeOffTime ;
		}		
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Rast::initFunction()
{
	flightPhaseCurrent = Mission;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Rast::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == inLandingClearance)
	{
		if (flightPhaseCurrent == Mission)
		{
			if (msg.value() == 1)
			{
				flightPhaseCurrent = Landing;
				holdIn(active, durationOfLanding);
			}
		}
	}
	else if (msg.port() == inNewMission)
	{
		if (flightPhaseCurrent == Landing)
		{
			flightPhaseCurrent = TakeOff;
			holdIn(active, durationOfTakeOff);
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Rast::internalFunction( const InternalMessage & )
{
	if (flightPhaseCurrent == Mission)
	{
		cerr << "RAST Error: Invalid flight phase.\n";
	}
	else if (flightPhaseCurrent == Landing)
	{
		// Do nothing
	}
	else if (flightPhaseCurrent == TakeOff)
	{
		flightPhaseCurrent = Mission;
	}
	
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Rast::outputFunction( const InternalMessage &msg )
{
	if (flightPhaseCurrent == Mission)
	{
		cerr << "RAST Error: Invalid flight phase.\n";
	}
	else if (flightPhaseCurrent == Landing)
	{
		sendOutput(msg.time(), outCompletedLanding, 1);
	}
	else if (flightPhaseCurrent == TakeOff)
	{
		sendOutput(msg.time(), outTakeOff, 1);
	}
	return *this;
}
