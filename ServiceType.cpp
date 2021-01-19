/*
 * Implementation of Class ServiceType in SeniorHELPSystem header
 */

#include "SeniorHELPSystem.h"

// static variable to auto-generate service code
int ServiceType::nextServiceCode = 1;

// constructor
ServiceType::ServiceType() {
    serviceCode = nextServiceCode++;
    serviceDescription = "unknown";
    numOfProvider = numOfRequest = 0;
}
ServiceType::ServiceType(string desc) {
    serviceCode = nextServiceCode++;
    serviceDescription = desc;
    numOfProvider = numOfRequest = 0;
}

// accessor functions
int ServiceType::getServiceCode() const {return serviceCode;}
string ServiceType::getServiceDesc() const {return serviceDescription;}
int ServiceType::getNumOfProvider() const {return numOfProvider;}
int ServiceType::getNumOfRequest() const {return numOfRequest;}
vector<ServiceRequest*>& ServiceType::getAllRequest() {return serviceRequest;}

// mutator functions
void ServiceType::setServiceDesc(string desc) {serviceDescription = desc;}
void ServiceType::setNumOfProvider(int num) {numOfProvider = num;}
void ServiceType::setNumOfRequest(int num) {numOfRequest = num;}

// PROVIDER-RELATED METHODS

/**A method to add Provider to own vector*/
bool ServiceType::addProvider(Provider* newProvider) {
    for (int i = 0; i < numOfProvider; i++)
        if (providerList[i]->getUsername() == newProvider->getUsername())
            return false;

    providerList.push_back(newProvider);
    setNumOfProvider(providerList.size());
    return true;
}

/**A method to display every Provider that is stored in vector*/
void ServiceType::showProvider() const {
    for (int i = 0; i < numOfProvider; i++) {
        cout<<i+1<<". "<<providerList[i]->getFullName()<<endl;
    }
}

/**A method to return Providerptr object from vector using index*/
Provider* ServiceType::getProvider(int index) {
    return providerList[index];
}

/**A method to remove Provider from vector*/
void ServiceType::removeProvider(string username) {
    for (int i = 0; i < numOfProvider; i++) {
        if (providerList[i]->getUsername() == username) {
            providerList.erase(providerList.begin() + i);
            setNumOfProvider(providerList.size());
            break;
        }
    }
}

// SERVICEREQUEST-RELATED METHODS

/**A method to create ServiceRequest and store it in own vector*/
int ServiceType::createRequest(Senior *senior) {
    // initialize servicerequestptr object
    // call constructor and pass this servicetype as pointer
    ServiceRequest* newRequest;
    newRequest =  new ServiceRequest(this);
    // seniorptr passed in the argument as the request sender
    newRequest->setSender(senior);
    // set request status to "pending"
    newRequest->setStatus('P');
    serviceRequest.push_back(newRequest);
    setNumOfRequest(serviceRequest.size());
    return newRequest->getRequestID();
}

/**A method to fill in ServiceRequest details using
 * value passed in parameter*/
void ServiceType::addRequestDetail(int id, string date, string notes) {
    for (int i = 0; i < numOfRequest; i++){
        if (serviceRequest[i]->getRequestID() == id) {
            serviceRequest[i]->setDate(date);
            serviceRequest[i]->setNotes("\t - "+notes);
            return;
        }
    }
}

/**A method to display every ServiceRequest of this type*/
void ServiceType::showAllRequest() const {
    for (int i = 0; i < numOfRequest; i++) {
        cout<<i+1<<*serviceRequest[i]<<endl;
    }
}

/**A method to display every ServiceRequest that has a certain status*/
void ServiceType::showAllRequest(string status) const {
    int num = 1;
    for (int i = 0; i < numOfRequest; i++) {
        if (serviceRequest[i]->getStatus() == status) {
            cout<<"-\t"<<"Type => "<<serviceDescription
            <<" ("<<"Code <"<<serviceCode<<">)"<<endl;
            ServiceRequest* request = serviceRequest[i];
            cout<<" \t"<<"Request ID     : "<<request->getRequestID()
            << endl;
            cout<<" \t"<<"Request Sender : "
            <<request->getRequestSender()->getFullName()<<endl;
            cout<<" \t"<<"Required Date  : "<<request->getDate()<<endl;
            cout<<" \t"<<"Notes"<<endl;
            cout<<" \t"<<"------------------------------"<<endl;
            cout<<" "<<request->getNotes()<<endl;
            cout<<endl; num++;
        }
    }
}

/**A method to check whether a ServiceRequest with the
 * given requestID exists in vector*/
bool ServiceType::findRequest(int id) const {
    for (int i = 0; i < numOfRequest; ++i) {
        if (serviceRequest[i]->getRequestID() == id)
            return true;
    }

    return false;
}

/**A method to search and return ServiceRequestptr object from vector*/
ServiceRequest* ServiceType::returnRequest(int id) {
    for (int i = 0; i < numOfRequest; ++i) {
        if (serviceRequest[i]->getRequestID() == id)
            return serviceRequest[i];
    }
}
/**A method to return ServiceRequestptr object from vector using index*/
ServiceRequest* ServiceType::returnRequestByIndex(int index) {
    return serviceRequest[index];
}

/**A method to check whether this ServiceType has any ServiceRequest
 * with "pending" status*/
bool ServiceType::checkReqAvailability() {
    for (int i = 0; i < numOfRequest; i++) {
        if (serviceRequest[i]->getStatus() == "PENDING")
            return true;
    }

    return false;
}

/**A method to check whether this ServiceType has any ServiceRequest
 * with given status*/
bool ServiceType::checkRequestStatus(string status) {
    for (int i = 0; i < numOfRequest; i++) {
        if (serviceRequest[i]->getStatus() == status)
            return true;
    }

    return false;
}

/**A method to delete ServiceRequestptr object from vector*/
void ServiceType::deleteRequest(int reqID) {
    for (int i = 0; i < numOfRequest; i++) {
        if (serviceRequest[i]->getRequestID() == reqID) {
            delete serviceRequest[i];
            serviceRequest.erase(serviceRequest.begin() + i);
            setNumOfRequest(serviceRequest.size());
            break;
        }
    }
}

// destructor
ServiceType::~ServiceType() {
    for (int i = 0; i < numOfRequest; i++) {delete serviceRequest[i];}
    serviceRequest.clear();
}

/**Overloading operator<< to display ServiceType details*/
ostream& operator<<(ostream& strm, const ServiceType& s) {
    return strm
            <<"Service Code <"<<s.getServiceCode()<<">"<<endl
            <<"Service Description : "<<s.getServiceDesc()<<endl
            <<"Number of Provider  : "<<s.getNumOfProvider()<<endl
            <<"Number of Request   : "<<s.getNumOfRequest()<<endl;
}

