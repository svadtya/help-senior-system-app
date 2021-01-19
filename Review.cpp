/*
 * Implementation of Class Review in SeniorHELPSystem header
 */

#include "SeniorHELPSystem.h"

// constructor
Review::Review() {
    date = comments = "-";
    ratings = 0.0;
    reviewer = NULL;
    reviewedUser = NULL;
}
Review::Review(string date, double ratings, string comments) {
    this->date = date;
    this->ratings = ratings;
    this->comments = comments;
    reviewer = NULL;
    reviewedUser = NULL;
}

// accessor functions
string Review::getDate() const {return date;}
double Review::getRatings() const {return ratings;}
string Review::getComments() const {return comments;}
User* Review::getReviewer() const {return reviewer;}
User* Review::getReviewedUser() const {return reviewedUser;}

// mutator functions
void Review::setDate(string date) {this->date = date;}
void Review::setRatings(double ratings) {this->ratings = ratings;}
void Review::setComments(string comments) {this->comments = comments;}
void Review::setReviewer(User* reviewer) {this->reviewer = reviewer;}
void Review::setReviewedUser(User* reviewedUser) {this->reviewedUser =
reviewedUser;}

// destructor
Review::~Review() {}

/**Overloading operator<< to display Review details*/
ostream& operator<<(ostream& strm, const Review& r) {
    return strm
    <<"Reviewer      : "<<r.getReviewer()->getFullName()<<endl
    <<"Reviewed User : "<<r.getReviewedUser()->getFullName()<<endl
    <<"Date          : "<<r.getDate()<<endl
    <<"Ratings       : "<<r.getRatings()<<endl
    <<"Comments"<<endl
    <<"---------------------------------------"<<endl
    <<" "<<r.getComments()<<endl;
}


