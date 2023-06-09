/*******************************************************************
*
*  DESCRIPTION: Atomic Model Weather
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

/** include files **/
#include "hfdsWeather.h"     // base header
#include "message.h"         // InternalMessage ....
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"         // str2float( ... )


/*******************************************************************
* Function Name: Weather
* Description: constructor
********************************************************************/
Weather::Weather( const string &name )
: Atomic( name )
, inWeatherCheck( addInputPort( "inWeatherCheck" ) )
, outWeatherAcceptability( addOutputPort( "outWeatherAcceptability" ) )
, probabilityAcceptableWeather( 0.84 )
, durationOfPreparation( 0, 5, 0, 0 )
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
		"acceptability"))
	{
		probabilityAcceptableWeather = str2float(
			MainSimulator::Instance().getParameter(
			description(), "acceptability"));
	}

	if (MainSimulator::Instance().existsParameter(description(), 
		"durationOfPreparation"))
	{
		string time( MainSimulator::Instance().getParameter(
			description(), "durationOfPreparation"));

		if (time != "")
		{
			durationOfPreparation = time;
		}		
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Weather::initFunction()
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Weather::externalFunction( const ExternalMessage &msg )
{	
	if (msg.port() == inWeatherCheck)
	{
		if (state() == passive)
		{
			holdIn(active, durationOfPreparation);
		}
		else if (state() == active)
		{
			holdIn(active, nextChange());
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Weather::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Weather::outputFunction( const InternalMessage &msg )
{
	double randomNumber = distribution().get();

	if (randomNumber < probabilityAcceptableWeather)
	{
		sendOutput(msg.time(), outWeatherAcceptability, 1);
	}
	else
	{
		sendOutput(msg.time(), outWeatherAcceptability, 0);
	}
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: destructor
********************************************************************/
Weather::~Weather()
{
	delete pDist;
}
