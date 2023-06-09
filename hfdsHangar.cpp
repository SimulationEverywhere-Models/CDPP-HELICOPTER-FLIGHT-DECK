/*******************************************************************
*
*  DESCRIPTION: Atomic Model Hangar
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

/** include files **/
#include "hfdsHangar.h"      // base header
#include "message.h"         // InternalMessage ....
#include "mainsimu.h"        // class MainSimulator


/*******************************************************************
* Function Name: Hangar
* Description: constructor
********************************************************************/
Hangar::Hangar( const string &name )
: Atomic( name )
, inCompletedLanding( addInputPort( "inCompletedLanding" ) )
, inTakeOff( addInputPort( "inTakeOff" ) )
, outHangarAvailability( addOutputPort( "outHangarAvailability" ) )
, durationOfPreparation(0, 0, 30, 0)
{
	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfPreparation"))
	{
		string time( MainSimulator::Instance().getParameter(
			description(), "durationOfPreparation"));

		if (time != "")
		{
			durationOfPreparation = time ;
		}		
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Hangar::initFunction()
{
	isFull = false;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Hangar::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == inCompletedLanding)
	{
		if (isFull)
		{
			// Error: Hangar already full
			cerr << "Hangar Error: Hangar already full.\n";
		}
		else
		{
			isFull = true;
		}		
		holdIn(active, 0);
	}
	else if (msg.port() == inTakeOff)
	{
		if (isFull)
		{
			isFull = false;
		}
		else
		{
			// Error: Hangar is empty
			cerr << "Hangar Error: Hangar is empty.\n";
		}
		
		if (state() == active)
		{
			holdIn(active, nextChange());
		}
		else
		{
			holdIn(active, durationOfPreparation);
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Hangar::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Hangar::outputFunction( const InternalMessage &msg )
{
	if (isFull)
	{
		sendOutput(msg.time(), outHangarAvailability, 0);
	}
	else
	{
		sendOutput(msg.time(), outHangarAvailability, 1);
	}
	return *this;
}
