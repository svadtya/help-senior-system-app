/*
 * Implementation of Class User in SeniorHELPSystem header
 */

#include "SeniorHELPSystem.h"

// constructor
User::User(char type) : userType(type) {
    username = "?unknown?";
    password = "#pass#";
    fullName = "unknown";
    mobileNo = "-";
    numOfRequest = numOfReview = 0;
}

// accessor functions
char User::getUserType() const {return userType;}
string User::getUsername() const {return username;}
string User::getPassword() const {return password;}
string User::getFullName() const {return fullName;}
string User::getMobileNo() const {return mobileNo;}
vector<ServiceRequest*>& User::getRequestList() {return requestList;};
int User::getNumOfRequest() const {return numOfRequest;}
vector<Review*>& User::getReviewList() {return reviewList;}
int User::getNumOfReview() const {return numOfReview;}

// mutator functions
void User::setUsername(string username) {this->username = username;}
void User::setPassword(string password) {this->password = password;}
void User::setFullName(string fullName) {this->fullName = fullName;}
void User::setMobileNo(string mobileNo) {this->mobileNo = mobileNo;}
void User::setNumOfRequest(int num) {numOfRequest = num;}
void User::setNumOfReview(int num) {numOfReview = num;}

// SERVICEREQUEST-RELATED METHODS

/**A method to add ServiceRequestptr object to vector*/
void User::addRequest(ServiceRequest* newRequest) {
    requestList.push_back(newRequest);
    setNumOfRequest(requestList.size());
}

/**A method to check whether a ServiceRequest with given
 * given requestID exists in vector*/
bool User::findRequest(int requestID) const {
    for (int i = 0; i < numOfRequest; i++){
        if (requestList[i]->getRequestID() == requestID)
            return true;
    }
    return false;
}

/**A method to search and return Requestptr object from vector*/
ServiceRequest* User::getRequest(int requestID) {
    for (int i = 0; i < numOfRequest; i++){
        if (requestList[i]->getRequestID() == requestID)
            return requestList[i];
    }
}

/**A method to check the availabity of ServiceRequest with
 * given status in vector*/
bool User::checkRequestList(string status) {
    for (int i = 0; i < numOfRequest; i++) {
        if (requestList[i]->getStatus() == status)
            return true;
    }

    return false;
}

/**A method to remove ServiceRequest from vector*/
void User::deleteRequest(int reqID) {
    for (int i = 0; i < numOfRequest; i++) {
        if (requestList[i]->getRequestID() == reqID) {
            requestList.erase(requestList.begin() + i);
        }
    }

    setNumOfRequest(requestList.size());
}

// REVIEW-RELATED METHODS

/**A method to add Review to vector in class User*/
void User::addReview(Review *newReview) {
    reviewList.push_back(newReview);
    setNumOfReview(reviewList.size());
}

// destructor
User::~User() {
    for (int i = 0; i < numOfReview; i++) {delete reviewList[i];}
    reviewList.clear();
}

/**Overloading operator<< to display User details*/
ostream& operator<<(ostream& strm, const User& u) {
    return strm<<"Username  ["<<u.getUsername()<<"]"<<endl;
}

