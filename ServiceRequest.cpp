/*
 * Implementation of Class ServiceRequest in SeniorHELPSystem header
 */

#include "SeniorHELPSystem.h"

// static variable to auto-generate request ID
int ServiceRequest::nextRequestID = 1;

// constructor
ServiceRequest::ServiceRequest(ServiceType* serviceType):
    type(serviceType) {
    requestID = nextRequestID++;
    requiredDate = notes = "-";
    requestSender = NULL;
    provider = NULL;
    status = "UNKNOWN";
}

// accessor functions
string ServiceRequest::getDate() const {return requiredDate;}
int ServiceRequest::getRequestID() const {return requestID;}
string ServiceRequest::getNotes() const {return notes;}
string ServiceRequest::getStatus() const {return status;}
ServiceType* ServiceRequest::getType() const {return type;}
Senior* ServiceRequest::getRequestSender() const {return requestSender;}
Provider* ServiceRequest::getProvider() const {return provider;}

// mutator functions
void ServiceRequest::setDate(string date) {this->requiredDate = date;}
void ServiceRequest::setNotes(string notes) {this->notes = notes;}
void ServiceRequest::setStatus(char ind) {
    switch (toupper(ind)) {
            // just requested by senior but is not accepted yet
        case 'P': status = "PENDING"; break;
            // request is accepted by Provider
        case 'A': status = "ACTIVE"; break;
            // request is completed (set by Senior)
        case 'C': status = "COMPLETED"; break;
            // request is already reviewed by Senior
        case 'R': status = "REVIEWED"; break;
            // unknown status
        default: status = "UNKNOWN"; break;
    }
}
void ServiceRequest::setSender(Senior *senior) {requestSender = senior;}
void ServiceRequest::setProvider(Provider *chosenProvider) {provider = chosenProvider;}

// destructor
ServiceRequest::~ServiceRequest() {}

/**Overloading operator<< to display ServiceRequest details*/
ostream& operator<<(ostream& strm, const ServiceRequest& s) {
    return strm
    <<"\tRequest ID    : "<<s.getRequestID()<<endl
    <<"\tStatus        : "<<s.getStatus()<<endl
    <<"\tRequired Date : "<<s.getDate()<<endl
    <<"\tNotes"<<endl
    <<"\t------------------------------"<<endl
    <<s.getNotes()<<endl;

}

