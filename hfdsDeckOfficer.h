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

#ifndef __HFDSDECKOFFICER_H
#define __HFDSDECKOFFICER_H

#include "atomic.h"     // class Atomic

#include "hfdsPrerequisites.h"

class DeckOfficer : public Atomic
{
public:
	DeckOfficer( const string &name = "DeckOfficer" );
	virtual string className() const ;
	
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inDeckAvailabilityCheck;
	const Port &inHangarAvailability;
	Port &outDeckAvailability;
	
	bool isCheckingDeck;
	bool isHangarFull;
	Time durationOfPreparation;

};	// class DeckOfficer

// ** inline ** // 
inline string DeckOfficer::className() const
{
	return "DeckOfficer" ;
}

#endif   //__HFDSDECKOFFICER_H
