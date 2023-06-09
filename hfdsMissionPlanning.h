/*******************************************************************
*
*  DESCRIPTION: Atomic Model Mission Planning
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

#ifndef __HFDSMISSIONPLANNING_H
#define __HFDSMISSIONPLANNING_H

#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution;

class MissionPlanning : public Atomic
{
public:
	MissionPlanning( const string &name = "MissionPlanning" );
	~MissionPlanning();
	virtual string className() const ;
	
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inCompletedLanding;
	Port &outNewMission;
	double shapeFactor;
	double minimumDuration;
	Distribution *pDist ;

	Distribution &distribution();

};	// class MissionPlanning

// ** inline ** // 
inline string MissionPlanning::className() const
{
	return "MissionPlanning" ;
}

inline Distribution &MissionPlanning::distribution()
{
	return *pDist;
}

#endif   //__HFDSMISSIONPLANNING_H
