//
// Created by Siva Aditya on 15/04/2020.
//

#ifndef BIT205_ASSIGNMENT_SENIORHELPSYSTEM_H
#define BIT205_ASSIGNMENT_SENIORHELPSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdio>
#include <limits>
using namespace std;

class SeniorHelp;
class User;
class Senior;
class Provider;
class ServiceType;
class ServiceRequest;
class Review;

/*
 * Class SeniorHelp serves as a container class for class User derived
 * objects and class ServiceType objects
 */
class SeniorHelp {
public:
    // constructor
    SeniorHelp();
    // accessor functions
    int getNumOfUser() const;
    int getNumOfService() const;
    // mutator functions
    void setNumOfUser(int);
    void setNumOfService(int);
    // class User related methods
    User* createUser(string, string, const char);
    void allUser() const;
    void deleteUser(string);
    bool findUser(string) const;
    bool validLoginUser(string, string) const;
    User* returnUser(string);
    // class ServiceType related methods
    int addService(string);
    void allService() const;
    void removeService(int);
    bool checkServiceType(string) const;
    bool findService(int) const;
    ServiceType* returnService(int);
    // destructor
    ~SeniorHelp();

private:
    vector<User*> seniorUser;
    vector<ServiceType*> serviceList;
    int numOfUser;
    int numOfService;
};

ostream& operator<<(ostream& strm, const SeniorHelp& senHelp);

/*
 * Class User is an abstract base class for class Senior and class Provider
 */
class User {
public:
    // constructor
    User(char);
    // accessor functions
    char getUserType() const;
    string getUsername() const;
    string getPassword() const;
    string getFullName() const;
    string getMobileNo() const;
    vector<ServiceRequest*>& getRequestList();
    int getNumOfRequest() const;
    vector<Review*>& getReviewList();
    int getNumOfReview() const;
    // mutator functions
    void setUsername(string);
    void setPassword(string);
    void setFullName(string);
    void setMobileNo(string);
    void setNumOfRequest(int);
    void setNumOfReview(int);
    // pure virtual methods to display menu
    virtual void mainMenu() = 0;
    // ServiceRequest-related methods
    virtual void addRequest(ServiceRequest*);
    bool findRequest(int) const;
    virtual void showRequest() = 0;
    virtual void showRequest(string) = 0;
    ServiceRequest* getRequest(int);
    bool checkRequestList(string);
    void deleteRequest(int);
    // Review-related methods
    void addReview(Review*);
    // destructor
    ~User();

private:
    const char userType; // define whether User is a Senior or Provider
    string username;
    string password;
    string fullName;
    string mobileNo;
    vector<ServiceRequest*> requestList;
    int numOfRequest;
    vector<Review*> reviewList;
    int numOfReview;

};

ostream& operator<<(ostream& strm, const User& u);


/*
 * Class Senior inherits from class User, creates Senior object
 */
class Senior: public User {
public:
    // constructor
    Senior();
    Senior(string);
    // accessor function
    string getAddress() const;
    // mutator function
    void setAddress(string address);
    void mainMenu();
    // ServiceRequest-related methods
    void requestedService();
    void showRequest();
    void showRequest(string);
    void removeRequest(ServiceType*,int);
    // Review-related methods
    Review* createReview(ServiceRequest*);
    // destructor
    ~Senior();

private:
    string address;

};

ostream& operator<<(ostream& strm, const Senior& s);

/*
 * Class Provider inherits from class User, creates Provider object
 */
class Provider: public User{
public:
    // constructor
    Provider();
    // accessor function
    int getNumOfServices() const;
    // mutator function
    void setNumOfServices(int);
    void mainMenu();
    // ServiceRequest-related methods
    void addRequest(ServiceRequest*);
    void showRequest();
    void showRequest(string);
    void showRequestPool();
    bool requestAvailable();
    bool checkStatusReqOnType(int,string);
    // ServiceType-related methods
    void addServiceType(ServiceType*);
    void allServiceType() const;
    bool findServiceType(int);
    ServiceType* getServiceType(int);
    void stopService(int);
    // Review-related methods
    void receiveReview(Review*);
    void portofolioReview();
    // destructor
    ~Provider();

private:
    vector<ServiceType*> services;
    int numOfServices;
};

ostream& operator<<(ostream& strm, const Provider& p);

/*
 * Class ServiceType represents the services which will be offered
 * by Provider and requested by Senior
 */
class ServiceType {
public:
    // constructor
    ServiceType();
    ServiceType(string);
    // accessor functions
    int getServiceCode() const;
    string getServiceDesc() const;
    int getNumOfProvider() const;
    int getNumOfRequest() const;
    vector<ServiceRequest*>& getAllRequest();
    // mutator functions
    void setServiceDesc(string);
    void setNumOfProvider(int);
    void setNumOfRequest(int);
    // Provider-related methods
    bool addProvider(Provider*);
    void showProvider() const;
    Provider* getProvider(int);
    void removeProvider(string);
    // ServiceRequest-related methods
    int createRequest(Senior*);
    void addRequestDetail(int,string,string);
    void showAllRequest() const;
    void showAllRequest(string) const;
    bool findRequest(int) const;
    ServiceRequest* returnRequest(int);
    ServiceRequest* returnRequestByIndex(int);
    bool checkReqAvailability();
    bool checkRequestStatus(string);
    void deleteRequest(int);
    // destructor
    ~ServiceType();

private:
    int serviceCode;
    static int nextServiceCode;
    string serviceDescription;
    vector<Provider*> providerList;
    int numOfProvider;
    vector<ServiceRequest*> serviceRequest;
    int numOfRequest;

};

ostream& operator<<(ostream& strm, const ServiceType& s);

/*
 * Class ServiceRequest represents the request of service that is sent
 * by Senior to provider
 */
class ServiceRequest {
public:
    // destructor
    ServiceRequest(ServiceType*);
    // accessor functions
    int getRequestID() const;
    string getDate() const;
    string getNotes() const;
    string getStatus() const;
    ServiceType* getType() const;
    Senior* getRequestSender() const;
    Provider* getProvider() const;
    // mutator functions
    void setDate(string date);
    void setNotes(string notes);
    void setStatus(char ind);
    void setSender(Senior*);
    void setProvider(Provider*);
    // destructor
    ~ServiceRequest();

private:
    int requestID;
    static int nextRequestID;
    ServiceType* type;
    Senior* requestSender;
    Provider* provider;
    string requiredDate;
    string notes;
    string status;
};

ostream& operator<<(ostream& strm, const ServiceRequest& s);

/*
 * Class Review represents the review of provider based on their service
 * given to Senior
 */
class Review {
public:
    // constructor
    Review();
    Review(string,double,string);
    // accessor functions
    string getDate() const;
    double getRatings() const;
    string getComments() const;
    User* getReviewer() const;
    User* getReviewedUser() const;
    // mutator functions;
    void setDate(string);
    void setRatings(double);
    void setComments(string);
    void setReviewer(User*);
    void setReviewedUser(User*);
    // destructor
    ~Review();

private:
    User* reviewer;
    User* reviewedUser;
    string date;
    double ratings;
    string comments;
};

ostream& operator<<(ostream& strm, const Review& r);

#endif //BIT205_ASSIGNMENT_SENIORHELPSYSTEM_H
