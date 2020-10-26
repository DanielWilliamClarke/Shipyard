#pragma once

#include <string>
#include <iostream>

//base class
//3 levels of inheritence
class BaseVessel
{
public:
	BaseVessel(unsigned int signature, std::istream& inStream);
	BaseVessel(
		unsigned int signature,
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment);

	virtual void Display(std::ostream& outStream) const;
	const std::string GetName() const;
	const unsigned int GetSignature() const;
protected:
	unsigned int signature;
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
	SurfaceVessel(unsigned int signature, std::istream& inStream);
	SurfaceVessel(
		unsigned int signature,
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
	AircraftCarrier(unsigned int signature, std::istream& inStream);
	AircraftCarrier(
		unsigned int signature,
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
	Destroyer(unsigned int signature, std::istream& inStream);
	Destroyer(
		unsigned int signature,
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
	FleetAuxiliary(unsigned int signature, std::istream& inStream);
	FleetAuxiliary(
		unsigned int signature,
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
	Tanker(unsigned int signature, std::istream& inStream);
	Tanker(
		unsigned int signature,
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
	LandingPlat(unsigned int signature, std::istream& inStream);
	LandingPlat(
		unsigned int signature,
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
public:
	Submarine(unsigned int signature, std::istream& inStream);
	Submarine(
		unsigned int signature,
		std::string name,
		unsigned int speed,
		unsigned int length,
		unsigned int maxRange,
		unsigned int displacement,
		unsigned int crewCompliment,
		unsigned int maxDiveDepth,
		unsigned int maxSubSpeed,
		unsigned int subDisplacement);
	virtual void Display(std::ostream& outStream) const override;
protected:
	unsigned int maxDiveDepth; //metres
	unsigned int maxSubSpeed; //knots
	unsigned int subDisplacement; //tons
};

class BallisticSub : public Submarine
{
public:
	BallisticSub(unsigned int signature, std::istream& inStream);
	BallisticSub(
		unsigned int signature,
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
	AttackSub(unsigned int signature, std::istream& inStream);
	AttackSub(
		unsigned int signature,
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


