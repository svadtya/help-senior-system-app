/*
 * Implementation of Class Provider in SeniorHELPSystem header
 */

#include "SeniorHELPSystem.h"

// constructor
Provider::Provider(): User('P') {numOfServices=0;}

// accessor functions
int Provider::getNumOfServices() const {return numOfServices;}

// mutator functions
void Provider::setNumOfServices(int num) {numOfServices=num;}

/**A pure virtual method of class User to display User-specific menu*/
void Provider::mainMenu() {
    int assigned, completed;
    assigned = completed = 0;

    // find total number of request with a certain status
    for (int i = 0; i < getNumOfRequest(); i++) {
        if (getRequestList()[i]->getStatus() == "ACTIVE") {
            assigned++;
        }

        if (getRequestList()[i]->getStatus() == "COMPLETED" ||
            getRequestList()[i]->getStatus() == "REVIEWED") {
            completed++;
        }
    }

    cout<<"-------------------------------------\n";
    cout<<"              Main Menu\n";
    cout<<"-------------------------------------\n\n";
    cout<<"1. Add Service\n";
    cout<<"2. View Service\n";
    cout<<"3. Stop Service\n";
    cout<<"4. View Service Request\n";
    cout<<"5. Accept Service Request\n";
    cout<<"6. View Assigned Service\n";
    cout<<"7. Cancel Assigned Service\n";
    cout<<"8. See Portfolio Review\n\n";
    cout<<"0. Logout\n\n";
    cout<<"-------------------------------------\n";
    cout<<getFullName()<<endl;
    cout<<"-------------------------------------\n";
    cout<<"Assigned Service  : "<<assigned<<"\n";
    cout<<"Completed Service : "<<completed<<"\n";
    cout<<"-------------------------------------\n\n";
}

// SERVICEREQUEST-RELATED METHODS

/**A method to accept request from Senior and
 * add the request to own vector*/
void Provider::addRequest(ServiceRequest* newRequest) {
    // set self as provider
    newRequest->setProvider(this);
    getRequestList().push_back(newRequest);
    setNumOfRequest(getRequestList().size());
}

/**A method to display every ServiceRequest that has been accepted*/
void Provider::showRequest() {
    for (int i = 0; i < getNumOfRequest(); i++) {
        ServiceRequest* request = getRequestList()[i];
        cout<<i+1<<".\t"<<"Request ID    : "<<request->getRequestID()
        <<endl;
        cout<<"\t"<<"Status        : "<<request->getStatus()<<endl;
        cout<<"\t"<<"Sender        : "<<request->getRequestSender()
        ->getFullName()<<endl;
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
void Provider::showRequest(string status) {
    int num = 1;
    for (int i = 0; i < getNumOfRequest(); i++) {
        ServiceRequest* request = getRequestList()[i];
        if (request->getStatus() == status) {
            cout<<num<<".\t"<<"Request ID    : "<<request->getRequestID()<<endl;
            cout<<"\t"<<"Sender        : "<<request->getRequestSender()->getFullName()<<endl;
            cout<<"\t"<<"Type          : "<<request->getType()->getServiceDesc()<<endl;
            cout<<"\t"<<"Required Date : "<<request->getDate()<<endl;
            cout<<"\t"<<"Notes"<<endl;
            cout<<"\t"<<"------------------------------"<<endl;
            cout<<request->getNotes()<<endl;
            cout<<endl; num++;
        }
    }
}

/**A method to show pending request from every ServiceType
 * that the provider offered*/
void Provider::showRequestPool() {
    for (int i = 0; i < getNumOfServices(); i++) {
        // invoke servicetype method
        services[i]->showAllRequest("PENDING");
    }
}

/**A method to check whether there are pending ServiceRequests in
 * ServiceType that is offered by provider*/
bool Provider::requestAvailable() {
    for (int i = 0; i < numOfServices; i++) {
        // invoke servicetype method
        if (services[i]->checkReqAvailability())
            return true;
    }
    return false;
}

/**A method to check whether there are ServiceRequest with a specific
 * status in a specific ServiceType offered by provider*/
bool Provider::checkStatusReqOnType(int code, string status) {
    for (int i = 0; i < getNumOfRequest(); i++) {
        ServiceRequest* request = getRequestList()[i];
        if (request->getType()->getServiceCode() == code
            && request->getStatus() == status) {
            return true;
        }
    }
    return false;
}

// SERVICETYPE-RELATED METHODS

/**A method to add ServiceType to provider vector*/
void Provider::addServiceType(ServiceType* newService) {
    services.push_back(newService);
    setNumOfServices(services.size());
}

/**A method to display every ServiceType that is offered by this provider*/
void Provider::allServiceType() const {
    for (int i = 0; i < numOfServices; i++){
        int code = services[i]->getServiceCode();
        string desc = services[i]->getServiceDesc();
        cout<<i+1<<". "<<desc<<" ["<<code<<"]"<<endl;
    }
}

/**A method to check whether a ServiceType with given service code is
 * is offered by this provider*/
bool Provider::findServiceType(int code) {
    for (int i = 0; i < getNumOfServices(); i++){
        if (services[i]->getServiceCode() == code)
            return true;
    }
    return false;
}

/**A method to search and return a ServiceType with given
 * service code from the vector*/
ServiceType* Provider::getServiceType(int code) {
    for (int i = 0; i < numOfServices; i++){
        if (services[i]->getServiceCode() == code)
            return services[i];
    }
}

/**A method to remove ServiceType from vector*/
void Provider::stopService(int code) {
    for (int i = 0; numOfServices; i++) {
        if (services[i]->getServiceCode() == code) {
            services[i]->removeProvider(getUsername());
            services.erase(services.begin() + i);
            setNumOfServices(services.size());
            break;
        }
    }
}

// REVIEW-RELATED METHODS

/**A method to add the given Review to own vector*/
void Provider::receiveReview(Review *newReview) {
    // this provider as the review's reviewed user
    newReview->setReviewedUser(this);
    addReview(newReview);
}

/**A method to show all review received from senior in
 * in a portofolio format*/
void Provider::portofolioReview() {
    cout<<"                           PORTOFOLIO REVIEW\n";
    cout<<"-------------------------------------------------------------------------\n\n";
    double totalRatings = 0;
    for (int i = 0; i < getNumOfReview(); i++) {
        Review* review = getReviewList()[i];
        cout<<i+1<<".\t"<<"Review sent by "<<review->getReviewer()->getFullName()<<endl;
        cout<<" \tDate    : "<<review->getDate()<<endl;
        printf(" \tRatings : %.1f\n", review->getRatings());
        cout<<" \tComments"<<endl;
        cout<<" \t---------------------------------------"<<endl;
        cout<<" \t "<<review->getComments()<<"\n";
        cout<<endl;

        totalRatings += review->getRatings();
    }

    cout<<"-------------------------------------------------------------------------\n";
    printf("OVERALL RATINGS : %.1f\n", ((double) totalRatings/getNumOfReview()));
    cout<<"-------------------------------------------------------------------------\n";
    cout<<endl;
}

// destructor
Provider::~Provider() {}

/**Overloading operator<< to display Provider details*/
ostream& operator<<(ostream& strm, const Provider& p) {
    return strm
            <<"Username ["<<p.getUsername()<<"]"<<endl
            <<"Provider Name     : "<<p.getFullName()<<endl
            <<"Mobile No         : "<<p.getMobileNo()<<endl
            <<"Available Service : "<<p.getNumOfServices()<<endl;

}
