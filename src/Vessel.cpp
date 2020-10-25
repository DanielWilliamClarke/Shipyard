#include "Vessel.h"

BaseVessel::BaseVessel(std::istream& inStream)
{
	std::cout << "Enter Name: " << std::endl;
	std::cout << ">";
	inStream >> name;	
	std::cout << "Enter Speed (Knots): " << std::endl;
	std::cout << ">";
	inStream >> speed;
	std::cout << "Enter Length (Metres): " << std::endl;
	std::cout << ">";
	inStream >> length;
	std::cout << "Enter Range (Nautical Miles): " << std::endl;
	std::cout << ">";
	inStream >> maxRange;
	std::cout << "Enter Displacement (Tons): " << std::endl;
	std::cout << ">";
	inStream >> displacement;
	std::cout << "Enter Crew Size: " << std::endl;
	std::cout << ">";
	inStream >> crewCompliment;
}

BaseVessel::BaseVessel(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment)
	: name(name),
	speed(speed), 
	length(length),
	maxRange(maxRange),
	displacement(displacement),
	crewCompliment(crewCompliment)
{
}

void BaseVessel::Display(std::ostream& outStream) const
{
	outStream << std::endl
		<< "-Vessel Data-" << std::endl
		<< std::endl;

	outStream << "Vessel Name: " << name << std::endl
		<< std::endl
		<< "Max Speed: " << speed << std::endl
		<< "Lenght: " << length << std::endl
		<< "Max Range: " << maxRange << std::endl
		<< "Displacement: " << displacement << std::endl
		<< "Crew Size: " << crewCompliment << std::endl
		<< std::endl;
}

const std::string BaseVessel::GetName() const
{
	return name;
}

SurfaceVessel::SurfaceVessel(std::istream& inStream) 
	: BaseVessel(inStream)
{
	std::cout << "Enter No. Helicopters: " << std::endl;
	std::cout << ">";
	inStream >> numHelicopter;
}

SurfaceVessel::SurfaceVessel(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int numHelicopter) 
	: BaseVessel{ name, speed, length, maxRange, displacement, crewCompliment },
		numHelicopter(numHelicopter)
{
}

void SurfaceVessel::Display(std::ostream& outStream) const
{
	BaseVessel::Display(outStream);

	outStream << "No. Helicopters: " << numHelicopter << std::endl;
}

AircraftCarrier::AircraftCarrier(std::istream& inStream)
	: SurfaceVessel(inStream)
{
	std::cout << "Enter No. Aircraft: " << std::endl;
	std::cout << ">";
	inStream >> numAircraft;
}

AircraftCarrier::AircraftCarrier(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int numHelicopter,
	unsigned int numAircraft)
	: SurfaceVessel{ name, speed, length, maxRange, displacement, crewCompliment, numHelicopter },
		numAircraft(numAircraft)
{
}

void AircraftCarrier::Display(std::ostream& outStream) const
{
	SurfaceVessel::Display(outStream);

	outStream << "No. Aircraft: " << numAircraft << std::endl;
}

Destroyer::Destroyer(std::istream& inStream)
	: SurfaceVessel(inStream)
{
	std::cout << "Enter Weapon System: " << std::endl;
	std::cout << ">";
	inStream >> wepSystem;
}

Destroyer::Destroyer(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int numHelicopter,
	std::string wepSystem)
	: SurfaceVessel{ name, speed, length, maxRange, displacement, crewCompliment, numHelicopter },
	wepSystem(wepSystem)
{
}

void Destroyer::Display(std::ostream& outStream) const
{
	SurfaceVessel::Display(outStream);

	outStream << "Weapon System: " << wepSystem << std::endl;
}

FleetAuxiliary::FleetAuxiliary(std::istream& inStream)
	: SurfaceVessel(inStream)
{
	std::cout << "Enter Deck Space (Metres): " << std::endl;
	std::cout << ">";
	inStream >> deckSpace;
}

FleetAuxiliary::FleetAuxiliary(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int numHelicopter,
	unsigned int deckSpace) 
	: SurfaceVessel{ name, speed, length, maxRange, displacement, crewCompliment, numHelicopter },
	deckSpace(deckSpace)
{
}

void FleetAuxiliary::Display(std::ostream& outStream) const
{
	SurfaceVessel::Display(outStream);

	outStream << "Deck Space (Metres): " << deckSpace << std::endl;
}

Tanker::Tanker(std::istream& inStream)
	: FleetAuxiliary(inStream)
{
	std::cout << "Enter Capacity (Litres): " << std::endl;
	std::cout << ">";
	inStream >> capacity;
}

Tanker::Tanker(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int numHelicopter,
	unsigned int deckSpace,
	unsigned int capacity)
	: FleetAuxiliary{ name, speed, length, maxRange, displacement, crewCompliment, numHelicopter, deckSpace },
	capacity(capacity)
{
}

void Tanker::Display(std::ostream& outStream) const
{
	FleetAuxiliary::Display(outStream);

	outStream << "Capacity (Litres): " << capacity << std::endl;
}

LandingPlat::LandingPlat(std::istream& inStream)
	: FleetAuxiliary(inStream)
{
	std::cout << "Enter Capacity (Cubic Metres): " << std::endl;
	std::cout << ">";
	inStream >> capacity;
}

LandingPlat::LandingPlat(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int numHelicopter,
	unsigned int deckSpace,
	unsigned int capacity)
	: FleetAuxiliary{ name, speed, length, maxRange, displacement, crewCompliment, numHelicopter, deckSpace },
	capacity(capacity)
{
}

void LandingPlat::Display(std::ostream& outStream) const
{
	FleetAuxiliary::Display(outStream);

	outStream << "Capacity (Cubic Metres): " << capacity << std::endl;
}

Submarine::Submarine(std::istream& inStream) 
	: BaseVessel(inStream)
{
	std::cout << "Enter Max Dive Depth (Metres): " << std::endl;
	std::cout << ">";
	inStream >> maxDiveDepth;
	std::cout << "Enter Max Speed (Knots): " << std::endl;
	std::cout << ">";
	inStream >> maxSubSpeed;
	std::cout << "Enter Displacement (Tons): " << std::endl;
	std::cout << ">";
	inStream >> subDisplacement;
}

Submarine::Submarine(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int maxDiveDepth,
	unsigned int maxSubSpeed,
	unsigned int subDisplacement)
	: BaseVessel{ name, speed, length, maxRange, displacement, crewCompliment },
	maxDiveDepth(maxDiveDepth), maxSubSpeed(maxSubSpeed), subDisplacement(subDisplacement)
{
}

void Submarine::Display(std::ostream& outStream) const
{
	BaseVessel::Display(outStream);

	outStream << "Max Dive Depth (Metres): " << maxDiveDepth << std::endl
		<< "Max Speed (Knots): " << maxSubSpeed << std::endl
		<< "Displacement (Tons): " << subDisplacement << std::endl;
}

BallisticSub::BallisticSub(std::istream& inStream)
	: Submarine(inStream)
{
	std::cout << "Enter No. Missles: " << std::endl;
	std::cout << ">";
	inStream >> numSLBM;
}

BallisticSub::BallisticSub(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int maxDiveDepth,
	unsigned int maxSubSpeed,
	unsigned int subDisplacement,
	unsigned int numSLBM)
	: Submarine{ name, speed, length, maxRange, displacement, crewCompliment, maxDiveDepth, maxSubSpeed, subDisplacement },
	numSLBM(numSLBM)
{
}

void BallisticSub::Display(std::ostream& outStream) const
{
	Submarine::Display(outStream);

	outStream << " No. Missles:  " << numSLBM << std::endl;
}

AttackSub::AttackSub(std::istream& inStream)
	: Submarine(inStream)
{
	std::cout << "Enter No. Torpedos: " << std::endl;
	std::cout << ">";
	inStream >> numTorpedos;
}

AttackSub::AttackSub(
	std::string name,
	unsigned int speed,
	unsigned int length,
	unsigned int maxRange,
	unsigned int displacement,
	unsigned int crewCompliment,
	unsigned int maxDiveDepth,
	unsigned int maxSubSpeed,
	unsigned int subDisplacement,
	unsigned int numTorpedos)
	: Submarine{ name, speed, length, maxRange, displacement, crewCompliment, maxDiveDepth, maxSubSpeed, subDisplacement },
	numTorpedos(numTorpedos)
{
}

void AttackSub::Display(std::ostream& outStream) const
{
	Submarine::Display(outStream);

	outStream << " No. Torpedos:  " << numTorpedos << std::endl;
}