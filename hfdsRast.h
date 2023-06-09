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

#ifndef __HFDSRAST_H
#define __HFDSRAST_H

#include "atomic.h"     // class Atomic

#include "hfdsPrerequisites.h"

class Rast : public Atomic
{
public:
	Rast( const string &name = "Rast" );
	virtual string className() const ;
	
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inLandingClearance;
	const Port &inNewMission;
	Port &outCompletedLanding;
	Port &outTakeOff;
	
	FlightPhase flightPhaseCurrent;
	Time durationOfLanding;
	Time durationOfTakeOff;

};	// class Rast

// ** inline ** // 
inline string Rast::className() const
{
	return "Rast" ;
}

#endif   //__HFDSRAST_H
