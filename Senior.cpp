/*
 * Implementation of Class Senior in SeniorHELPSystem header
 */

#include "SeniorHELPSystem.h"

// constructor
Senior::Senior(): User('S') {address="unknown";}
Senior::Senior(string address): User('S') {this->address = address;}

// accessor functions
string Senior::getAddress() const {return address;}

// mutator functions
void Senior::setAddress(string address) {this->address = address;}

/**A pure virtual method of class User to display User-specific menu*/
void Senior::mainMenu() {
    int active, pending, completed, reviewed;
    active = pending = completed = reviewed = 0;

    // find total number of request with a certain status
    for (int i = 0; i < getNumOfRequest(); i++) {
        if (getRequestList()[i]->getStatus() == "ACTIVE") {
            active++;
        }
        if (getRequestList()[i]->getStatus() == "PENDING") {
            pending++;
        }
        if (getRequestList()[i]->getStatus() == "COMPLETED") {
            completed++;
        }
        if (getRequestList()[i]->getStatus() == "REVIEWED") {
            reviewed++;
        }
    }

    cout << "-------------------------------------\n";
    cout << "              Main Menu\n";
    cout << "-------------------------------------\n\n";
    cout << "1. Request Service\n";
    cout << "2. View Requested Service\n";
    cout << "3. Manage Request\n";
    cout << "4. Complete Request\n";
    cout << "5. Give Review\n\n";
    cout << "0. Logout\n\n";
    cout << "-------------------------------------\n";
    cout << getFullName() << endl;
    cout << "-------------------------------------\n";
    cout << "Active Service    : " <<active<<"\n";
    cout << "Pending Request   : " <<pending<<"\n";
    cout << "Completed Service : " <<completed<<"\n";
    cout << "Reviewed Service  : " <<reviewed<<"\n";
    cout << "-------------------------------------\n\n";
}

// SERVICEREQUEST-RELATED METHODS

/**A method to display the chosen service type and request ID
 * of every ServiceRequest that is requested by Senior*/
 void Senior::requestedService() {
     for (int i = 0; i < getNumOfRequest(); i++) {
         cout<<i+1<<". "
         <<getRequestList()[i]->getType()->getServiceDesc()
         <<" (Request ID <"<<getRequestList()[i]->getRequestID()
         <<">)"<<endl;
     }
 }

/**A method to display every ServiceRequest that is requested by Senior*/
void Senior::showRequest() {
    for (int i = 0; i < getNumOfRequest(); i++) {
        ServiceRequest* request = getRequestList()[i];
        cout<<i+1<<".\t"<<"Request ID    : "<<request->getRequestID()
        <<endl;
        cout<<"\t"<<"Status        : "<<request->getStatus()<<endl;
        if (request->getStatus() == "ACTIVE"){
            cout<<"\t"<<"Provider      : "
                <<request->getProvider()->getFullName()<<endl;
        }
        cout<<"\t"<<"Type          : "<<request->getType()
        ->getServiceDesc()<<endl;
        cout<<"\t"<<"Required Date : "<<request->getDate()<<endl;
        cout<<"\t"<<"Notes"<<endl;
        cout<<"\t"<<"------------------------------"<<endl;
        cout<<request->getNotes()<<endl;
        cout<<endl;
    }
}

/**A method to display every ServiceRequest with
 * a specific status in vector*/
void Senior::showRequest(string status) {
    int num = 1;
    for (int i = 0; i < getNumOfRequest(); i++) {
        ServiceRequest* request = getRequestList()[i];
        if (request->getStatus() == status){
            cout<<num<<".\t"<<"Request ID    : "<<request->getRequestID()
            <<endl;
            if (status != "PENDING"){
                cout<<"\t"<<"Provider      : "
                    <<request->getProvider()->getFullName()<<endl;
            }
            cout<<"\t"<<"Type          : "<<request->getType()
            ->getServiceDesc()<<endl;
            cout<<"\t"<<"Required Date : "<<request->getDate()<<endl;
            cout<<"\t"<<"Notes"<<endl;
            cout<<"\t"<<"------------------------------"<<endl;
            cout<<request->getNotes()<<endl;
            cout<<endl; num++;
        }
    }
}

/**A method to remove ServiceRequest from vector*/
void Senior::removeRequest(ServiceType* type, int reqID) {
    for (int i = 0; i < getNumOfRequest(); i++) {
        ServiceRequest* request = getRequestList()[i];
        if (request->getRequestID() == reqID) {
            // if request is already accepted by provider,
            // need to remove it from provider as well
            if (request->getStatus() != "PENDING") {
                getRequestList()[i]->getProvider()->deleteRequest(reqID);
            }
            deleteRequest(reqID);
            type->deleteRequest(reqID);
            break;
        }
    }
}

// REVIEW-RELATED METHODS

/**A method to create, add, and return newly-created Review*/
Review* Senior::createReview(ServiceRequest* request) {
    // initialize Review* object
    Review* newReview;
    newReview = new Review();
    // senior as the reviewer
    newReview->setReviewer(this);
    // add review to the senior's vector
    addReview(newReview);
    // sent review to provider (reviewedUser)
    request->getProvider()->receiveReview(newReview);
    // change request status to "reviewed"
    request->setStatus('R');
    return newReview;
}

// destructor
Senior::~Senior() {};

/**Overloading operator<< to display Senior details*/
ostream& operator<<(ostream& strm, const Senior& s) {
    return strm
            <<"Username ["<<s.getUsername()<<"]"<<endl
            <<"Full Name : "<<s.getFullName()<<endl
            <<"Mobile No : "<<s.getMobileNo()<<endl
            <<"Address   : "<<s.getAddress()<<endl;
}

