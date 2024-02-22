// Keegan Scott
// 424 HW 1

#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <utility>
#include <string>
#include <cstdlib>
#include <ctime>

class Plane;  // Forward declaration of the Plane class

// Question 6-----------------------------------------------------------------------------------------------------------
// Represents a pilot controlling a plane
class Pilot { 
private:
    std::string name;

public:
    Plane *myPlane;  // Pointer to the Plane class
    
    // Constructor
    Pilot(const std::string& pilotName);

    // Destructor
    ~Pilot();

    // Getter function for the variable "name"
    std::string getName() const;
   
    // assignPlane function to set the myPlane pointer
    void assignPlane(Plane* plane);

    // Friend declaration to grant access to the Plane class
    friend class Plane;
};

// Implementation of the function to set the myPlane pointer
void Pilot::assignPlane(Plane* plane) {
    myPlane = plane;
}

// Question 3-----------------------------------------------------------------------------------------------------------
// Represents an aircraft's characteristics and behavior
class Plane {
private:
    double pos, vel, distance;
    bool at_SCE;
    std::string origin, destination;
    std::map<std::pair<std::string, std::string>, int> flightDistances;

public:
    // Constructor
    Plane(const std::string& from, const std::string& to);

    // Destructor
    ~Plane();

    // Member function to perform operations
    void operate(double dt);

    // Getter functions
    double getPos() const;
    double getVel() const;
    double getDistance() const;
    bool getAtSCE() const;
    std::string getOrigin() const;
    std::string getDestination() const;

    // Setter function for velocity
    void setVel(double newVel);
};

// Question 4-----------------------------------------------------------------------------------------------------------
// Constructor implementation
Plane::Plane(const std::string& from, const std::string& to) :
    pos(0.0), vel(0.0), distance(0.0), at_SCE(true), origin(from), destination(to) {
    // Question 2-----------------------------------------------------------------------------------------------------------
    // Initialize flight distances
    flightDistances[std::make_pair("SCE", "PHL")] = 160;
    flightDistances[std::make_pair("SCE", "ORD")] = 640;
    flightDistances[std::make_pair("SCE", "EWR")] = 220;
    flightDistances[std::make_pair("PHL", "SCE")] = 160;
    flightDistances[std::make_pair("ORD", "SCE")] = 640;
    flightDistances[std::make_pair("EWR", "SCE")] = 220;

    // Calculate distance between origin and destination airports
    auto it = flightDistances.find(std::make_pair(origin, destination));
    if (it != flightDistances.end()) {
        distance = it->second;
    }
    else {
        distance = 0.0; // Set to a default value if airports not found in the container
    }

    std::cout << "Plane Created with a Tail number " << this << std::endl;
}

// Destructor implementation
Plane::~Plane() {
    std::cout << "Plane Destroyed" << std::endl;
}

// Member function to perform operations
void Plane::operate(double dt) {
    if (pos < distance) {
        pos += vel * (dt/3600);
        at_SCE = false;
    }
    else if (destination == "SCE") {
        at_SCE = true;
        std::swap(origin, destination);
        pos = 0.0;
    }
    else {
        std::swap(origin, destination);
        pos = 0.0;
    }
}

// Getter functions
double Plane::getPos() const {
    return pos;
}
double Plane::getVel() const {
    return vel;
}
double Plane::getDistance() const {
    return distance;
}
bool Plane::getAtSCE() const {
    return at_SCE;
}
std::string Plane::getOrigin() const {
    return origin;
}
std::string Plane::getDestination() const {
    return destination;
}

// Setter function for velocity
void Plane::setVel(double newVel) {
    vel = newVel;
}

// Implementation of the Pilot class
Pilot::Pilot(const std::string& pilotName) : name(pilotName), myPlane(nullptr) {
    std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane." << std::endl;
}

Pilot::~Pilot() {
    std::cout << "Pilot " << name << " is out of the plane." << std::endl;
}

std::string Pilot::getName() const {
    return name;
}

int main() {
    // Question 1-----------------------------------------------------------------------------------------------------------
    // Variables to store input values
    const double GROSS_WEIGHT_LIMIT = 2950.0;
    const double MIN_CG = 82.1;
    const double MAX_CG = 84.7;
    double emptyWeight, fuelWeightPerGallon, baggageWeight;
    int numFrontSeatOccupants, numRearSeatOccupants, numGallonsOfFuel;
    double emptyWeightMoment, frontSeatMomentArm, rearSeatMomentArm, fuelTankMomentArm, baggageMomentArm;

    // Read input values from the user
    std::cout << "Enter airplane empty weight (pounds): ";
    std::cin >> emptyWeight;
    std::cout << "Enter airplane empty-weight moment (pounds-inches): ";
    std::cin >> emptyWeightMoment;
    std::cout << "Enter the number of front seat occupants: ";
    std::cin >> numFrontSeatOccupants;

    std::vector<double> weightFrontSeatOccupant(numFrontSeatOccupants);
    for (int i = 0; i < numFrontSeatOccupants; ++i) {
        std::cout << "Enter weight of front seat occupant " << i + 1 << " (pounds): ";
        std::cin >> weightFrontSeatOccupant[i];
    }

    std::cout << "Enter the front seat moment arm (inches): ";
    std::cin >> frontSeatMomentArm;
    std::cout << "Enter the number of rear seat occupants: ";
    std::cin >> numRearSeatOccupants;

    std::vector<double> weightRearSeatOccupant(numRearSeatOccupants);
    for (int i = 0; i < numRearSeatOccupants; ++i) {
        std::cout << "Enter weight of front seat occupant " << i + 1 << " (pounds): ";
        std::cin >> weightRearSeatOccupant[i];
    }

    std::cout << "Enter the rear seat moment arm (inches): ";
    std::cin >> rearSeatMomentArm;
    std::cout << "Enter the number of gallons of usable fuel (gallons): ";
    std::cin >> numGallonsOfFuel;
    std::cout << "Enter the usable fuel weights per gallon (pounds): ";
    std::cin >> fuelWeightPerGallon;
    std::cout << "Enter the fuel tank moment arm (inches): ";
    std::cin >> fuelTankMomentArm;
    std::cout << "Enter the baggage weight (pounds): ";
    std::cin >> baggageWeight;
    std::cout << "Enter the baggage moment arm (inches): ";
    std::cin >> baggageMomentArm;

    // Calculate total weight and total moment
    double totalWeight = emptyWeight;
    double totalMoment = emptyWeightMoment;

    // Calculate front seat weight and moment
    for (int i = 0; i < numFrontSeatOccupants; ++i) {
        totalWeight += weightFrontSeatOccupant[i];
        totalMoment += weightFrontSeatOccupant[i] * frontSeatMomentArm;
    }

    // Calculate rear seat weight and moment
    for (int i = 0; i < numRearSeatOccupants; ++i) {
        totalWeight += weightRearSeatOccupant[i];
        totalMoment += weightRearSeatOccupant[i] * rearSeatMomentArm;
    }

    // Calculate fuel weight and moment
    totalWeight += numGallonsOfFuel * fuelWeightPerGallon;
    totalMoment += numGallonsOfFuel * fuelWeightPerGallon * fuelTankMomentArm;

    // Calculate baggage weight and moment
    totalWeight += baggageWeight;
    totalMoment += baggageWeight * baggageMomentArm;

    // Calculate based on all the inputs how the aircraft needs to be adjusted
    double newCG = 0.0;
    double gallonWeight = numGallonsOfFuel * fuelWeightPerGallon;
    double requiredFuel = gallonWeight / fuelWeightPerGallon;
    std::cout << "Weight above(+)/below(-) gross weight limit: " << totalWeight - GROSS_WEIGHT_LIMIT << " pounds" << std::endl;

    while (totalWeight > GROSS_WEIGHT_LIMIT || newCG < MIN_CG || newCG > MAX_CG) {
        if (totalWeight > GROSS_WEIGHT_LIMIT || newCG < MIN_CG) {
            gallonWeight -= 0.01;
            totalWeight -= 0.01;
        }
        else if (newCG > MAX_CG) {
            gallonWeight += 0.01;
            totalWeight += 0.01;
        }
        requiredFuel = gallonWeight / fuelWeightPerGallon;
        newCG = totalMoment / totalWeight;
    }

    // Output new locations and values of the aircraft
    std::cout << "Required fuel to be added(+)/drained(-) to meet the gross weight limit: " << std::fixed << std::setprecision(2) << requiredFuel - numGallonsOfFuel << " gallons" << std::endl;
    std::cout << "New gross weight: " << totalWeight << " lbs." << std::endl;
    std::cout << "New C.G. location: " << newCG << " inches \n" << std::endl;

    // Question 5-----------------------------------------------------------------------------------------------------------
    // Seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // User input for origin and destination
    std::string origin, destination;
    std::cout << "Enter the origin airport code: ";
    std::cin >> origin;
    std::cout << "Enter the destination airport code: ";
    std::cin >> destination;

    // Create a Plane object with user input
    Plane airplane(origin, destination);

    // Choose a speed between [400, 500]
    double speed = 400 + (std::rand() % 101);
    airplane.setVel(speed);

    // Choose a timestep between [10, 100]
    double timestep = 10 + (std::rand() % 91);

    // Choose the maximum number of iterations between [1000, 2000]
    int maxIterations = 1000 + (std::rand() % 1001);

    double flighttime = 0;
    // Iterate and print the airplane position at each timestep until the maximum number of iterations is reached
    for (int i = 0; i < maxIterations; ++i) {
        airplane.operate(timestep);
        std::cout << "Time: " << flighttime << " seconds, Position: " << airplane.getPos() << " miles" << std::endl;
        flighttime += timestep;
    }
    std::cout << "\n" << std::endl;

    // Question 7-----------------------------------------------------------------------------------------------------------
    // Modern CPP
    // Create Pilot objects
    Pilot pilot1("Alpha");
    pilot1.myPlane = &airplane;
    Pilot pilot2("Bravo");
    pilot2.myPlane = nullptr;

    std::cout << "Plane Created with a Tail number " << pilot1.myPlane << std::endl;
    std::cout << "Pilot " << pilot1.getName() << " with certificate number " << &pilot1 << " is in control of a plane: " << pilot1.myPlane << std::endl;
    std::cout << "Pilot " << pilot2.getName() << " with certificate number " << &pilot2 << " is in control of a plane: " << pilot2.myPlane << std::endl; 
    // Iterate and simulate the scenario
    for (int i = 0; i < maxIterations; ++i) {
        airplane.operate(timestep);
        if (airplane.getAtSCE() == 1) {
            std::cout << "\nThe plane " << &airplane << " is at SCE." << std::endl;
            std::swap(pilot1.myPlane, pilot2.myPlane);
            std::cout << "Pilot " << pilot1.getName() << " with certificate number " << &pilot1 << " is in control of a plane: " << pilot1.myPlane << std::endl;
            std::cout << "Pilot " << pilot2.getName() << " with certificate number " << &pilot2 << " is in control of a plane: " << pilot2.myPlane << std::endl;
        }
    }
    
    //// Question 8-----------------------------------------------------------------------------------------------------------
    //// Old CPP - Commented out to not interfere with Question 7 above
    //// Create Pilot objects
    //Pilot* pilot1 = new Pilot("Alpha");
    //pilot1->assignPlane(&airplane);

    //Pilot* pilot2 = new Pilot("Bravo");
    //pilot2->assignPlane(nullptr);

    //std::cout << "Plane Created with a Tail number " << pilot1->myPlane << std::endl;
    //std::cout << "Pilot " << pilot1->getName() << " with certificate number " << pilot1 << " is in control of a plane: " << pilot1->myPlane << std::endl;
    //std::cout << "Pilot " << pilot2->getName() << " with certificate number " << pilot2 << " is in control of a plane: " << pilot2->myPlane << std::endl;

    //// Iterate and simulate the scenario
    //for (int i = 0; i < maxIterations; ++i) {
    //    airplane.operate(timestep);
    //    if (airplane.getAtSCE() == 1) {
    //        std::cout << "\nThe plane " << &airplane << " is at SCE." << std::endl;

    //        // Swap raw pointers
    //        Plane* tempPlane = pilot1->myPlane;
    //        pilot1->myPlane = pilot2->myPlane;
    //        pilot2->myPlane = tempPlane;

    //        std::cout << "Pilot " << pilot1->getName() << " with certificate number " << pilot1 << " is in control of a plane: " << pilot1->myPlane << std::endl;
    //        std::cout << "Pilot " << pilot2->getName() << " with certificate number " << pilot2 << " is in control of a plane: " << pilot2->myPlane << std::endl;
    //    }
    //}

    //// Release memory
    //delete pilot1;
    //delete pilot2;

    return 0;
}