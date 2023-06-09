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

#ifndef __HFDSHANGAR_H
#define __HFDSHANGAR_H

#include "atomic.h"     // class Atomic

class Hangar : public Atomic
{
public:
	Hangar( const string &name = "Hangar" );
	virtual string className() const ;
	
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inCompletedLanding;
	const Port &inTakeOff;
	Port &outHangarAvailability;

	bool isFull;
	Time durationOfPreparation;

};	// class Hangar

// ** inline ** // 
inline string Hangar::className() const
{
	return "Hangar" ;
}

#endif   //__HFDSHANGAR_H
