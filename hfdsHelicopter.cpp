/*******************************************************************
*
*  DESCRIPTION: Atomic Model Helicopter
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

/** include files **/
#include <math.h>
#include "hfdsHelicopter.h" // base header
#include "message.h"         // InternalMessage ....
#include "mainsimu.h"        // class MainSimulator


/*******************************************************************
* Function Name: Helicopter
* Description: constructor
********************************************************************/
Helicopter::Helicopter( const string &name )
: Atomic( name )
, inHelicopter( addInputPort( "inHelicopter" ) )
, inDeckAvailability( addInputPort( "inDeckAvailability" ) )
, inLandingClearance( addInputPort( "inLandingClearance" ) )
, inTakeOffClearance( addInputPort( "inTakeOffClearance" ) )
, outLandingRequest( addOutputPort( "outLandingRequest" ) )
, outDeckAvailabilityCheck( addOutputPort( "outDeckAvailabilityCheck" ) )
, outHelicopter( addOutputPort( "outHelicopter" ) )
, durationOfApproach( 0, 0, 0, 0 )
, durationOfFinalApproach( 0, 2, 0, 0 )
, durationOfHover( 0, 0, 30, 0 )
, durationOfTakeOff( 0, 1, 0, 0 )
{	
	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfApproach"))
	{
		string approachTime(MainSimulator::Instance().getParameter(
			description(), "durationOfApproach"));

		if (approachTime != "")
		{
			durationOfApproach = approachTime ;
		}		
	}

	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfFinalApproach"))
	{
		string finalApproachTime(MainSimulator::Instance().getParameter(
			description(), "durationOfFinalApproach"));

		if (finalApproachTime != "")
		{
			durationOfFinalApproach = finalApproachTime ;
		}		
	}

	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfHover"))
	{
		string hoverTime(MainSimulator::Instance().getParameter(
			description(), "durationOfHover"));

		if (hoverTime != "")
		{
			durationOfHover = hoverTime ;
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
Model &Helicopter::initFunction()
{
	flightPhaseCurrent = Mission;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Helicopter::externalFunction( const ExternalMessage &msg )
{	
	if (msg.port() == inHelicopter)
	{
		if (msg.value() == 1)
		{
			if (state() == passive)
			{
				if (flightPhaseCurrent == Mission)
				{
					flightPhaseCurrent = Approach;
					holdIn(active, durationOfApproach);
				}
			}
		}
	}
	else if (msg.port() == inDeckAvailability)
	{
		// No need to check state; flight phase changes
		// after first inDeckAvailability
		if (flightPhaseCurrent == Approach)
		{
			if (msg.value() == 0)
			{
				flightPhaseCurrent = TakeOff;
				holdIn(active, durationOfTakeOff);
			}
			else
			{
				flightPhaseCurrent = FinalApproach;
				holdIn(active, durationOfFinalApproach);
			}
		}
	}
	else if (msg.port() == inLandingClearance)
	{
		if (flightPhaseCurrent == Hover)
		{			
			if (msg.value() == 0)
			{
				flightPhaseCurrent = TakeOff;
				holdIn(active, durationOfTakeOff);
			}
			else
			{
				if (state() == active)
				{
					// If repeated clearance, subtract time already used
					holdIn(active, nextChange());
				}
				else
				{
					holdIn(active, durationOfHover);
				}
			}
		}
	}
	else if (msg.port() == inTakeOffClearance)
	{
		if (flightPhaseCurrent == Landing)
		{			
			flightPhaseCurrent = TakeOff;
			if (state() == active)
			{
				// If repeated clearance, subtract time already used
				holdIn(active, nextChange());
			}
			else
			{
				holdIn(active, durationOfTakeOff);
			}
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Helicopter::internalFunction( const InternalMessage & )
{
	if ( (flightPhaseCurrent == Mission) ||
		(flightPhaseCurrent == Landing) )
	{
		cerr << "Helicopter Error: Invalid flight phase.\n";
	}
	else if (flightPhaseCurrent == Approach)
	{
	}
	else if (flightPhaseCurrent == FinalApproach)
	{
		flightPhaseCurrent = Hover;
	}
	else if (flightPhaseCurrent == Hover)
	{
		flightPhaseCurrent = Landing;		
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
Model &Helicopter::outputFunction( const InternalMessage &msg )
{
	if ( (flightPhaseCurrent == Mission) ||
		(flightPhaseCurrent == Landing) )
	{
		cerr << "Helicopter Error: Invalid flight phase.\n";
	}
	else if (flightPhaseCurrent == Approach)
	{
		sendOutput(msg.time(), outDeckAvailabilityCheck, 1);
	}
	else if (flightPhaseCurrent == FinalApproach)
	{
		sendOutput(msg.time(), outLandingRequest, 1);
	}
	else if (flightPhaseCurrent == Hover)
	{
	}
	else if (flightPhaseCurrent == TakeOff)
	{
		sendOutput(msg.time(), outHelicopter, 1);
	}
	return *this;
}
