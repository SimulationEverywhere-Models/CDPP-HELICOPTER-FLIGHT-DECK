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

#ifndef __HFDSWEATHER_H
#define __HFDSWEATHER_H

#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution;

class Weather : public Atomic
{
public:
	Weather( const string &name = "Weather" );
	~Weather();
	virtual string className() const ;
	
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inWeatherCheck;
	Port &outWeatherAcceptability;
	
	Time durationOfPreparation;
	double probabilityAcceptableWeather;
	Distribution *pDist ;

	Distribution &distribution();

};	// class Weather

// ** inline ** // 
inline string Weather::className() const
{
	return "Weather" ;
}

inline Distribution &Weather::distribution()
{
	return *pDist;
}

#endif   //__HFDSWEATHER_H
