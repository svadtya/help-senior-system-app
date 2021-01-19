/*
 * Implementation of Class SeniorHelp in SeniorHELPSystem header
 */

#include "SeniorHELPSystem.h"

// constructor
SeniorHelp::SeniorHelp() {numOfUser=numOfService=0;}

// accessor functions
int SeniorHelp::getNumOfUser() const {return numOfUser;}
int SeniorHelp::getNumOfService() const {return numOfService;}

// mutator functions
void SeniorHelp::setNumOfUser(int num) {numOfUser=num;}
void SeniorHelp::setNumOfService(int num) {numOfService=num;}

// CLASS USER RELATED METHODS

/**A method to add User to SeniorHelp*/
User* SeniorHelp::createUser(string username, string password,
        char userType) {
    User *newUser;
    if (userType == 'S')
        newUser = new Senior(); // add Senior User
    else
        newUser = new Provider(); // add Provider User
    seniorUser.push_back(newUser);
    newUser->setUsername(username);
    newUser->setPassword(password);
    setNumOfUser(seniorUser.size());
    return newUser;
}

/**A method to display every User of SeniorHelp*/
void SeniorHelp::allUser() const {
    for (int i = 0; i < numOfUser; i++)
        cout<<seniorUser[i];
}

/**A method to delete User from vector in SeniorHelp*/
void SeniorHelp::deleteUser(string username) {
    for (int i = 0; i < numOfUser; i++) {
        if (seniorUser[i]->getUsername() == username){
            delete seniorUser[i];
            seniorUser.erase(seniorUser.begin() + i);
            setNumOfUser(seniorUser.size());
        }
    }
}

/**A method to check whether User with given
 * username has been added to SeniorHelp*/
bool SeniorHelp::findUser(string username) const {
    for (int i = 0; i < numOfUser; i++)
        if (seniorUser[i]->getUsername() == username)
            return true;

    return false;
}

/**A method to validate User login with given username & password*/
bool SeniorHelp::validLoginUser(string username, string password) const {
    for (int i = 0; i < numOfUser; i++)
        if (seniorUser[i]->getUsername() == username &&
        seniorUser[i]->getPassword() == password)
            return true;

    return false;
}

/**A method to search and return Userptr objects from vector*/
User* SeniorHelp::returnUser(string username) {
    for (int i = 0; i < numOfUser; i++)
        if (seniorUser[i]->getUsername() == username)
            return seniorUser[i];

    return NULL;
}

// CLASS SERVICETYPE RELATED METHODS

/**A method to add ServiceType to SeniorHelp*/
int SeniorHelp::addService(string desc) {
    for (int i = 0; i < numOfService; i++) {
        if (serviceList[i]->getServiceDesc() == desc)
            return 0;
    }
    ServiceType* newService;
    newService =  new ServiceType(desc);
    serviceList.push_back(newService);
    setNumOfService(serviceList.size());
    return newService->getServiceCode();
}

/**A method to display all ServiceType of SeniorHelp*/
void SeniorHelp::allService() const {
    for (int i = 0; i < numOfService; i++) {
        ServiceType *serviceType = serviceList[i];
        cout << i + 1 << ". " <<serviceType->getServiceDesc()
        <<" (Service Code <"<<serviceType->getServiceCode()<<">)"<<endl;
    }
    cout<<endl;
}

/**A method to remove ServiceTypeptr object from vector*/
void SeniorHelp::removeService(int serviceCode) {
    for (int i = 0; i < numOfService; i++) {
        if (serviceList[i]->getServiceCode() == serviceCode) {
            delete serviceList[i];
            serviceList.erase(serviceList.begin() + i);
            setNumOfService(serviceList.size());
            break;
        }
    }
}

/**A method to check whether ServiceType with
 * the passed serviceDesc exist in own vector*/
 bool SeniorHelp::checkServiceType(string desc) const {
    for (int i = 0; i < numOfService; i++)
        if (serviceList[i]->getServiceDesc() == desc)
            return true;

    return false;
 }

/**A method to check whether ServiceType with given
 * serviceCode exists in vector*/
bool SeniorHelp::findService(int serviceCode) const {
    for (int i = 0; i < numOfService; i++)
        if (serviceList[i]->getServiceCode() == serviceCode)
            return true;

    return false;
}

/**A method to search and return ServiceTypeptr object from vector*/
ServiceType* SeniorHelp::returnService(int serviceCode) {
    for (int i = 0; i < numOfService; i++)
        if (serviceList[i]->getServiceCode() == serviceCode)
            return serviceList[i];
}

// destructor
SeniorHelp::~SeniorHelp() {
    for (int i = 0; i < numOfUser; i++) {delete seniorUser[i];}
    seniorUser.clear();
    for (int i = 0; i < numOfService; i++) {delete serviceList[i];}
    serviceList.clear();
}

/**Overloading operator<< to display SeniorHelp details*/
ostream& operator<<(ostream& strm, const SeniorHelp& senHelp) {
    return strm
            <<"***********************************************"<<endl
            <<"Number of User         : "<<senHelp.getNumOfUser()<<endl
            <<"Number of Service Type : "<<senHelp.getNumOfService()<<endl
            <<"***********************************************"<<endl;
}
