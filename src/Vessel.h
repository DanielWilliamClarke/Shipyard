#pragma once

#include <string>
#include <iostream>

//base class
//3 levels of inheritence
class BaseVessel
{
public:
	BaseVessel(std::istream& inStream);
	BaseVessel(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment);

	virtual void Display(std::ostream& outStream) const;
	const std::string GetName() const;
protected:
	std::string name;
	unsigned int speed; //knots
	unsigned int length; //metres
	unsigned int maxRange; //nautical miles
	unsigned int displacement; //tons
	unsigned int crewCompliment; //a number
};

//derived classes
	//surface vessels
class SurfaceVessel : public BaseVessel
{
public:
	SurfaceVessel(std::istream& inStream);
	SurfaceVessel(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int numHelicopter);
	virtual void Display(std::ostream& outStream) const override;
protected:
	unsigned int numHelicopter;
};

class AircraftCarrier : public SurfaceVessel
{
public:
	AircraftCarrier(std::istream& inStream);
	AircraftCarrier(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int numHelicopter,
		unsigned int numAircraft);
	virtual void Display(std::ostream& outStream) const override;
protected:
	unsigned int numAircraft;
};

class Destroyer : public SurfaceVessel
{
public:
	Destroyer(std::istream& inStream);
	Destroyer(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int numHelicopter,
		std::string wepSystem);
	virtual void Display(std::ostream& outStream) const override;
protected:
	std::string wepSystem;
};

class FleetAuxiliary : public SurfaceVessel
{
public:
	FleetAuxiliary(std::istream& inStream);
	FleetAuxiliary(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int numHelicopter,
		unsigned int deckSpace);
	virtual void Display(std::ostream& outStream) const override;
protected: 
	unsigned int deckSpace; //metres
};

class Tanker : public FleetAuxiliary
{
public:
	Tanker(std::istream& inStream);
	Tanker(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int numHelicopter,
		unsigned int deckSpace,
		unsigned int capacity);
	virtual void Display(std::ostream& outStream) const override;
protected: 
	unsigned int capacity; //litres
};

class LandingPlat : public FleetAuxiliary
{
public:
	LandingPlat(std::istream& inStream);
	LandingPlat(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int numHelicopter,
		unsigned int deckSpace,
		unsigned int capacity);
	virtual void Display(std::ostream& outStream) const override;
protected: 
	unsigned int capacity; //cubic metres
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
	Submarine(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int maxDiveDepth,
		unsigned int maxSubSpeed,
		unsigned int subDisplacement);
	virtual void Display(std::ostream & outStream) const override;
};

class BallisticSub : public Submarine
{
public:
	BallisticSub(std::istream& inStream);
	BallisticSub(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int maxDiveDepth,
		unsigned int maxSubSpeed,
		unsigned int subDisplacement,
		unsigned int numSLBM);
	virtual void Display(std::ostream& outStream) const override;
protected:
	unsigned int numSLBM; 
};

class AttackSub : public Submarine
{
public:
	AttackSub(std::istream& inStream);
	AttackSub(
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int maxDiveDepth,
		unsigned int maxSubSpeed,
		unsigned int subDisplacement,
		unsigned int numTorpedos);
	virtual void Display(std::ostream& outStream) const override;
protected:
	unsigned int numTorpedos;
};


