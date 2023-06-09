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

#ifndef __HFDSCONTROLTOWER_H
#define __HFDSCONTROLTOWER_H

#include "atomic.h"     // class Atomic

#include "hfdsPrerequisites.h"

/** forward declarations **/
class Distribution;

class ControlTower : public Atomic
{
public:
	ControlTower( const string &name = "ControlTower" );
	virtual string className() const ;
	
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inLandingRequest;
	const Port &inWeatherAcceptability;
	const Port &inTakeOff;
	Port &outWeatherCheck;
	Port &outLandingClearance;
	Port &outTakeOffClearance;
	
	FlightPhase flightPhaseCurrent;
	Time durationOfApproach;
	Time durationOfHover;
	Time durationOfLanding;
	Distribution *pDist;
	
	Distribution &distribution();

};	// class ControlTower

// ** inline ** // 
inline string ControlTower::className() const
{
	return "ControlTower" ;
}

inline Distribution &ControlTower::distribution()
{
	return *pDist;
}

#endif   //__HFDSCONTROLTOWER_H
