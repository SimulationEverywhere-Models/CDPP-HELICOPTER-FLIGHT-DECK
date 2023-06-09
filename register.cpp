/*******************************************************************
*
*  DESCRIPTION: Register New Atomics
*
*  AUTHOR: Kin Wing Tsui
*
*  EMAIL: kwtsui@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "hfdsControlTower.h"
#include "hfdsDeckOfficer.h"
#include "hfdsHangar.h"
#include "hfdsHelicopter.h"
#include "hfdsMissionPlanning.h"
#include "hfdsRast.h"
#include "hfdsWeather.h"

void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<ControlTower>() , "ControlTower" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<DeckOfficer>() , "DeckOfficer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Hangar>() , "Hangar" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Helicopter>() , "Helicopter" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<MissionPlanning>() , "MissionPlanning" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Rast>() , "Rast" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Weather>() , "Weather" ) ;
}
