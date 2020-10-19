#pragma once

#include <string>

//base class
//3 levels of inheritence
class BaseVessel
{
protected:
	std::string _vesselType;
	unsigned int _speed; //knots
	unsigned int _length; //metres
	unsigned int _maxRange; //nautical miles
	unsigned int _displacement; //tons
	unsigned int _crewCompliment; //a number
public:
	BaseVessel();
	BaseVessel(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew);
	virtual unsigned int getSpeed(void);
	virtual unsigned int getLength(void);
	virtual unsigned int getRange(void);
	virtual unsigned int getDisp(void);
	virtual unsigned int getCrew(void);
	virtual std::string getVesselType(void);
};

//derived classes
	//surface vessels
class SurfaceVessel : public BaseVessel
{
protected:
	unsigned int _numHelicopter;
public:
	SurfaceVessel();
	SurfaceVessel(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew ,unsigned int newHeli);
	unsigned int getHeli(void);
};

class AircraftCarrier : public SurfaceVessel
{
protected:
	unsigned int _numAircraft;
public:
	AircraftCarrier();
	AircraftCarrier(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newAircraft);
	unsigned int getCraft(void);
};

class Destroyer : public SurfaceVessel
{
protected:
	std::string _wepSystem;
public:
	Destroyer(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, std::string newWep);
	std::string getWep(void);
};

class FleetAuxiliary : public SurfaceVessel
{
protected: 
	unsigned int _deckSpace; //metres
public:
	FleetAuxiliary(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newDeck);
	unsigned int getDeck(void);
};

class Tanker : public FleetAuxiliary
{
protected: 
	unsigned int _capacity; //litres
public:
	Tanker(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newDeck, unsigned int newCap);	
	unsigned int getCapL(void);
};

class LandingPlat : public FleetAuxiliary
{
protected: 
	unsigned int _capacity; //cubic metres
public:
	LandingPlat(std::string vesselType, unsigned int newSpeed,unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int newHeli, unsigned int newDeck, unsigned int newCap);
	unsigned int getCapM3(void);
};

//Submarines
class Submarine : public BaseVessel
{
protected:
	unsigned int _maxDiveDepth; //metres
	unsigned int _maxSubSpeed; //knots
	unsigned int _subDisplacement; //tons
public:
	Submarine(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int maxDepth, unsigned int maxSpeed, unsigned int newSubsubSDisp);
	unsigned int getDiveDepth(void);
	unsigned int getSubSpeed(void);
	unsigned int getSubDisp(void); 
};

class BallisticSub : public Submarine
{
protected:
	unsigned int _numSLBM; 
public:
	BallisticSub(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int maxDepth, unsigned int maxSpeed, unsigned int newSubDisp, unsigned int newSLBM);
	unsigned int getSLBM(void);
};

class AttackSub : public Submarine
{
protected:
	unsigned int _numTorpedos;
public:
	AttackSub(std::string vesselType, unsigned int newSpeed, unsigned int newLength, unsigned int newRange, unsigned int newDisp, unsigned int newCrew, unsigned int maxDepth, unsigned int maxSpeed, unsigned int newSubDisp, unsigned int newTorpedo);
	unsigned int getTorpedos(void);
};


