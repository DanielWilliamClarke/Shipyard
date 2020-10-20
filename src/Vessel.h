#pragma once

#include <string>
#include <iostream>

//base class
//3 levels of inheritence
class BaseVessel
{
protected:
	std::string name;
	unsigned int speed; //knots
	unsigned int length; //metres
	unsigned int maxRange; //nautical miles
	unsigned int displacement; //tons
	unsigned int crewCompliment; //a number
public:
	BaseVessel(std::istream& inStream);
	virtual void Display(std::ostream& outStream) const;
};

//derived classes
	//surface vessels
class SurfaceVessel : public BaseVessel
{
protected:
	unsigned int numHelicopter;
public:
	SurfaceVessel(std::istream& inStream);
	virtual void Display(std::ostream& outStream) const override;
};

class AircraftCarrier : public SurfaceVessel
{
protected:
	unsigned int numAircraft;
public:
	AircraftCarrier(std::istream& inStream);
	virtual void Display(std::ostream& outStream) const override;
};

class Destroyer : public SurfaceVessel
{
protected:
	std::string wepSystem;
public:
	Destroyer(std::istream& inStream);
	virtual void Display(std::ostream& outStream) const override;
};

class FleetAuxiliary : public SurfaceVessel
{
protected: 
	unsigned int deckSpace; //metres
public:
	FleetAuxiliary(std::istream & inStream);
	virtual void Display(std::ostream & outStream) const override;
};

class Tanker : public FleetAuxiliary
{
protected: 
	unsigned int capacity; //litres
public:
	Tanker(std::istream & inStream);
	virtual void Display(std::ostream & outStream) const override;
};

class LandingPlat : public FleetAuxiliary
{
protected: 
	unsigned int capacity; //cubic metres
public:
	LandingPlat(std::istream& inStream);
	virtual void Display(std::ostream & outStream) const override;
};

//Submarines
class Submarine : public BaseVessel
{
protected:
	unsigned int maxDiveDepth; //metres
	unsigned int maxSubSpeed; //knots
	unsigned int subDisplacement; //tons
public:
	Submarine(std::istream & inStream);
	virtual void Display(std::ostream & outStream) const override;
};

class BallisticSub : public Submarine
{
protected:
	unsigned int numSLBM; 
public:
	BallisticSub(std::istream & inStream);
	virtual void Display(std::ostream & outStream) const override;
};

class AttackSub : public Submarine
{
protected:
	unsigned int numTorpedos;
public:
	AttackSub(std::istream & inStream);
	virtual void Display(std::ostream & outStream) const override;
};


