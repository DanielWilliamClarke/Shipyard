// File: Vessel.cpp
// Version: V1.1 
// Date: 04/04/2012
// Name: Daniel Clarke - Computer Science 
// ID: n0271538
// This program contains the parameterised constructors for the bass class BaseVessel and all of it derived classes, as well as the getter functions for each classes private data memebers
// Modification history: 
// V1.1 4/4/2012

#include "Vessel.h"
BaseVessel::BaseVessel(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew)
{
	_vesselType = vesselType;
	_speed = newSpeed;
	_length = newLength;
	_maxRange = newRange;
	_displacement = newDisp;
	_crewCompliment = newCrew;
}
SurfaceVessel::SurfaceVessel(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli) : BaseVessel(vesselType, newSpeed, newLength, newRange, newDisp, newCrew)
{
	_numHelicopter = newHeli;
}
AircraftCarrier::AircraftCarrier(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newAircraft) : SurfaceVessel(vesselType, newSpeed, newLength, newRange, newDisp, newCrew, newHeli)
{
	_numAircraft = newAircraft;
}
Destroyer::Destroyer(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, std::string newWep) : SurfaceVessel(vesselType, newSpeed, newLength, newRange, newDisp, newCrew, newHeli)
{
	_wepSystem = newWep;
}
FleetAuxiliary::FleetAuxiliary(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newDeck) : SurfaceVessel(vesselType, newSpeed, newLength, newRange, newDisp, newCrew, newHeli)
{
	_deckSpace = newDeck;
}
Tanker::Tanker(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newDeck, unsigned int newCap) : FleetAuxiliary(vesselType, newSpeed, newLength, newRange, newDisp, newCrew, newHeli, newDeck)
{
	_capacity = newCap;
}
LandingPlat::LandingPlat(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newDeck, unsigned int newCap) :  FleetAuxiliary(vesselType, newSpeed, newLength, newRange, newDisp, newCrew, newHeli, newDeck)
{
	_capacity = newCap;
}
Submarine::Submarine(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int maxDepth, unsigned int maxSpeed, unsigned int newSubDisp) : BaseVessel(vesselType, newSpeed, newLength, newRange, newDisp, newCrew)
{
	_maxDiveDepth = maxDepth;
	_maxSubSpeed = maxSpeed;
	_subDisplacement = newSubDisp;
}
BallisticSub::BallisticSub(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int maxDepth, unsigned int maxSpeed, unsigned int newSubDisp, unsigned int newSLBM) : Submarine(vesselType, newSpeed, newLength, newRange, newDisp, newCrew, maxDepth, maxSpeed, newSubDisp)
{
	_numSLBM = newSLBM;
}
AttackSub::AttackSub(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int maxDepth, unsigned int maxSpeed, unsigned int newSubDisp, unsigned int newTorpedo) : Submarine(vesselType, newSpeed, newLength, newRange, newDisp, newCrew, maxDepth, maxSpeed, newSubDisp)
{
	_numTorpedos = newTorpedo;
}
std::string BaseVessel::getVesselType()
{
	return _vesselType;
}
unsigned int BaseVessel::getSpeed()
{
	return _speed;
}
unsigned int BaseVessel::getLength()
{
	return _length;
}
unsigned int BaseVessel::getRange()
{
	return _maxRange;
}
unsigned int BaseVessel::getDisp()
{
	return _displacement;
}
unsigned int BaseVessel::getCrew()
{
	return _crewCompliment;
}
unsigned int SurfaceVessel::getHeli()
{
	return _numHelicopter;
}
unsigned int AircraftCarrier::getCraft()
{
	return _numAircraft;
}
std::string Destroyer::getWep()
{
	return _wepSystem;
}
unsigned int FleetAuxiliary::getDeck()
{
	return _deckSpace;
}
unsigned int Tanker::getCapL()
{
	return _capacity;
}
unsigned int LandingPlat::getCapM3()
{
	return _capacity;
}
unsigned int Submarine::getDiveDepth()
{
	return _maxDiveDepth;
}
unsigned int Submarine::getSubSpeed()
{
	return _maxSubSpeed;
}
unsigned int Submarine::getSubDisp()
{
	return _subDisplacement;
}
unsigned int BallisticSub::getSLBM()
{
	return _numSLBM;
}
unsigned int AttackSub::getTorpedos()
{
	return _numTorpedos;
}