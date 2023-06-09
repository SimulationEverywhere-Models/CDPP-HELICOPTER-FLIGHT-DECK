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

#ifndef __HFDSHELICOPTER_H
#define __HFDSHELICOPTER_H

#include "atomic.h"     // class Atomic

#include "hfdsPrerequisites.h"

class Helicopter : public Atomic
{
public:
	Helicopter( const string &name = "Helicopter" );
	virtual string className() const ;
	
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inHelicopter;
	const Port &inDeckAvailability;
	const Port &inLandingClearance;
	const Port &inTakeOffClearance;
	Port &outLandingRequest;
	Port &outDeckAvailabilityCheck;
	Port &outHelicopter;
	
	FlightPhase flightPhaseCurrent;
	Time durationOfApproach;
	Time durationOfFinalApproach;
	Time durationOfHover;
	Time durationOfTakeOff;

};	// class Helicopter

// ** inline ** // 
inline string Helicopter::className() const
{
	return "Helicopter" ;
}

#endif   //__HFDSHELICOPTER_H
