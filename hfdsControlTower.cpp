/*******************************************************************
*
*  DESCRIPTION: Atomic Model Control Tower
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
#include "hfdsControlTower.h" // base header
#include "message.h"         // InternalMessage ....
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"         // str2float( ... )


/*******************************************************************
* Function Name: ControlTower
* Description: constructor
********************************************************************/
ControlTower::ControlTower( const string &name )
: Atomic( name )
, inLandingRequest( addInputPort( "inLandingRequest" ) )
, inWeatherAcceptability( addInputPort( "inWeatherAcceptability" ) )
, inTakeOff( addInputPort( "inTakeOff" ) )
, outWeatherCheck( addOutputPort( "outWeatherCheck" ) )
, outLandingClearance( addOutputPort( "outLandingClearance" ) )
, outTakeOffClearance( addOutputPort( "outTakeOffClearance" ) )
, durationOfApproach( 0, 0, 30, 0 )
, durationOfHover( 0, 0, 15, 0 )
, durationOfLanding( 0, 0, 15, 0 )
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
		"durationOfApproach"))
	{
		string approachTime( MainSimulator::Instance().getParameter(
			description(), "durationOfApproach"));

		if (approachTime != "")
		{
			durationOfApproach = approachTime ;
		}		
	}

	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfHover"))
	{
		string hoverTime( MainSimulator::Instance().getParameter(
			description(), "durationOfHover"));

		if (hoverTime != "")
		{
			durationOfHover = hoverTime ;
		}		
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &ControlTower::initFunction()
{
	flightPhaseCurrent = Mission;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &ControlTower::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == inLandingRequest)
	{
		if (flightPhaseCurrent == Mission)
		{
			flightPhaseCurrent = Approach;
			holdIn(active, durationOfApproach);
		}
	}
	else if (msg.port() == inWeatherAcceptability)
	{
		if (flightPhaseCurrent == Hover)
		{
			if (msg.value() == 1)
			{
				flightPhaseCurrent = Landing;
				holdIn(active, durationOfLanding);
			}
			else
			{
				if (state() == active)
				{
					holdIn(active, nextChange());
				}
				else
				{
					holdIn(active, durationOfHover);
				}
			}
		}
	}
	else if (msg.port() == inTakeOff)
	{
		if (flightPhaseCurrent == Landing)
		{
			flightPhaseCurrent = TakeOff;
			float timeInMs = fabs(distribution().get());
			Time t(0, 0, 0, timeInMs);
			holdIn(active, t);
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &ControlTower::internalFunction( const InternalMessage & )
{
	if ( (flightPhaseCurrent == Mission) ||
		(flightPhaseCurrent == FinalApproach) )
	{
		cerr << "ControlTower Error: Invalid flight phase.\n";
	}
	else if (flightPhaseCurrent == Approach)
	{
		flightPhaseCurrent = Hover;
	}
	else if (flightPhaseCurrent == Hover)
	{
		flightPhaseCurrent = Mission;
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
Model &ControlTower::outputFunction( const InternalMessage &msg )
{
	if ( (flightPhaseCurrent == Mission) ||
		(flightPhaseCurrent == FinalApproach) )
	{
		cerr << "ControlTower Error: Invalid flight phase.\n";
	}
	else if (flightPhaseCurrent == Approach)
	{
		sendOutput(msg.time(), outWeatherCheck, 1);
	}
	else if (flightPhaseCurrent == Hover)
	{
		sendOutput(msg.time(), outLandingClearance, 0);
	}
	else if (flightPhaseCurrent == Landing)
	{
		sendOutput(msg.time(), outLandingClearance, 1);
	}
	else if (flightPhaseCurrent == TakeOff)
	{
		sendOutput(msg.time(), outTakeOffClearance, 1);
	}
	return *this;
}
