/*******************************************************************
*
*  DESCRIPTION: Atomic Model Deck Officer
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

/** include files **/
#include "hfdsDeckOfficer.h" // base header
#include "message.h"         // InternalMessage ....
#include "mainsimu.h"        // class MainSimulator


/*******************************************************************
* Function Name: DeckOfficer
* Description: constructor
********************************************************************/
DeckOfficer::DeckOfficer( const string &name )
: Atomic( name )
, inDeckAvailabilityCheck( addInputPort( "inDeckAvailabilityCheck" ) )
, inHangarAvailability( addInputPort( "inHangarAvailability" ) )
, outDeckAvailability( addOutputPort( "outDeckAvailability" ) )
, durationOfPreparation( 0, 0, 10, 0 )
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
Model &DeckOfficer::initFunction()
{
	isCheckingDeck = false;
	isHangarFull = false;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &DeckOfficer::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == inDeckAvailabilityCheck)
	{
		isCheckingDeck = true;

		if (state() == active)
		{
			holdIn(active, nextChange());
		}
		else
		{
			holdIn(active, durationOfPreparation);
		}
	}
	else if (msg.port() == inHangarAvailability)
	{		
		if (msg.value() == 1)
		{
			isHangarFull = false;
		}
		else if (msg.value() == 0)
		{
			isHangarFull = true;
		}
		
		if (state() == active)
		{
			holdIn(active, nextChange());
		}
		else
		{
			isCheckingDeck = false;
			holdIn(active, 0);
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &DeckOfficer::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &DeckOfficer::outputFunction( const InternalMessage &msg )
{
	if (isCheckingDeck)
	{
		if (isHangarFull)
		{
			sendOutput(msg.time(), outDeckAvailability, 0);
		}
		else
		{
			sendOutput(msg.time(), outDeckAvailability, 1);
		}
	}
	
	return *this;
}
