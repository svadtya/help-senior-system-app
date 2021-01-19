//
// Created by Siva Aditya on 15/04/2020.
//
// Note :   This code compiled and run correctly on CLion IDE ver. 2020.1
//          using MinGW version 3.20 compiler and C++14 language standard
//

#include "SeniorHELPSystem.h"

void signUpSen();
void signUpProv();
void manageService();
void seniorMenu(Senior*);
void providerMenu(Provider*);
char inChoice();
void errMsg(string);
void nextIs(string);

SeniorHelp senHelp;

int main() {

    // initialize SeniorHelp Object
    senHelp = SeniorHelp();
    char choice;

    do{
        nextIs("go to welcome page");
        cout<<"\n\n";
        cout<<"***********************************************\n";
        cout<<"        Welcome To SeniorHELP Program\n";
        cout<<"***********************************************\n\n";
        cout<<"1. Sign Up\n";
        cout<<"2. Login\n";
        cout<<"3. Manage Services\n\n";
        cout<<"0. Exit\n\n";
        cout<<senHelp<<endl;
        inputmenu:
        choice = inChoice();
        cout<<endl;

        // SIGNUP USER
        if (choice == '1') {
            cout<<"Enter 1 to sign up as Senior\n";
            cout<<"Enter 2 to sign up as Service Provider\n";
            cout<<"Enter 0 to cancel\n\n";
            char signUp = inChoice();

            cout<<endl;

            switch (signUp) {
                case '1': signUpSen(); break;
                case '2': signUpProv(); break;
                default: cout<<"Canceled...\n"; break;
            }

        }
        // LOGIN USER
        else if (choice == '2') {
            if (senHelp.getNumOfUser() > 0) {
                cout<<"---------     LOGIN     ---------\n\n";
                cout<<"Username  :";
                string username; getline(cin>>ws, username);

                // validate username
                while (!senHelp.findUser(username)){
                    errMsg("Username doesn't exist");
                    cout<<"Username  :";
                    getline(cin>>ws, username);
                }

                cout<<"Password  :";
                string password; getline(cin, password);

                // validate password
                while (!senHelp.validLoginUser(username,password)){
                    errMsg("Wrong password");
                    cout<<"Password  :";
                    getline(cin, password);
                }

                cout<<"\nLogin successful!\n";

                // cast User* object and go to menu function
                switch (senHelp.returnUser(username)->getUserType())
                {
                    case 'S':
                        seniorMenu(dynamic_cast<Senior*>
                                   (senHelp.returnUser(username)));
                        break;
                    case 'P':
                        providerMenu(dynamic_cast<Provider*>
                                     (senHelp.returnUser(username)));
                        break;
                    default: break;
                }
            } else {errMsg("You need to sign up before login");}


        }

        else if (choice == '3') {manageService();}
        else if (choice == '0') {cout<<"Program closed...\n";}
        else {errMsg("Invalid choice"); goto inputmenu;}

    } while (choice != '0');

    cout<<"See you again next time~\n";

    return 0;
}

/**A function to manage service type of SeniorHelp*/
void manageService() {

    cout<<"           Manage Services\n";
    cout<<"-------------------------------------\n\n";
    cout<<"1. Add New Service Type\n";
    cout<<"2. Update Service Type Detail\n";
    cout<<"3. View All Service Type\n\n";
    cout<<"0. Exit Menu\n\n";
    inputmenu:
    char choice = inChoice();
    cout<<endl;
    int code;

    // ADD NEW TYPE
    if (choice == '1') {
        char again = 'N';
        do {
            cout<<"Service description :";
            string desc;
            getline(cin>>ws, desc);
            cout<<"------------------\n\n";
            // validate service description and add to SeniorHelp
            int code = senHelp.addService(desc);
            if(code != 0){
                cout<<senHelp.returnService(code)->getServiceDesc()
                    <<" (Service Code <"<<code<<">)\n";
                cout<<"New service type successfully added!\n";
            }
            else
                errMsg("Service type is already added");

            cout<<endl;
            // option to loop
            cout<<"Do you want to add another service type (Y/N)?\n";
            again = inChoice();
            if (again == 'Y') {cout<<endl;}

        } while (again == 'Y');

    }

    // UPDATE TYPE DETAILS
    else if (choice == '2') {
        if (senHelp.getNumOfService() == 0) {
            errMsg("Service type is not added yet");
        }else {
            senHelp.allService();
            cout << "\nWhich service do you want update?\n";
            cout << "Enter Service Code :";
            cin >> code;

            // validate code
            while (!senHelp.findService(code)) {
                errMsg("Invalid service code");
                cout<<"Enter service code :";
                cin>>code;
            }

            cout<<senHelp.returnService(code)->getServiceDesc()
            <<" (Service Code <"<<code<<">)\n\n";
            cout << "New service description :";
            string desc;
            getline(cin >> ws, desc);

            // validate new service description
            while(senHelp.checkServiceType(desc)) {
                errMsg("Service type with that description already"
                       " exists in system");
                cout << "New service description :";
                getline(cin >> ws, desc);
            }

            senHelp.returnService(code)->setServiceDesc(desc);
            cout<<"\nService description successfully updated!\n";
        }
    }

    // VIEW ALL TYPE
    else if (choice == '3') {
        if (senHelp.getNumOfService() == 0) {
            errMsg("Service type is not added yet");

        } else
            senHelp.allService();
    }

    else if (choice == '0') {return;}
    else {errMsg("Invalid choice"); goto inputmenu;}
}

// -------------------------     SENIOR     ---------------------------- //

/**A function for signing up Senior user*/
void signUpSen() {
    cout<<"-------- SIGN UP SENIOR --------\n\n";

    cout<<"Username   :";
    string username; getline(cin>>ws, username);

    // username must be unique
    while (senHelp.findUser(username)){
        errMsg("Username has been taken. Try something else");
        cout<<"Username   :";
        getline(cin>>ws, username);
    }

    cout<<"Password   :";
    string password; getline(cin, password);

    // create user and add to seniorHelp
    Senior* senior = dynamic_cast<Senior*>
            (senHelp.createUser(username, password, 'S'));

    // initialize data member value
    cout<<"Full Name  :";
    string fullName; getline(cin, fullName);
    senior->setFullName(fullName);

    cout<<"Mobile No  :";
    string mobileNo; getline(cin, mobileNo);
    senior->setMobileNo(mobileNo);

    cout<<"Address    :";
    string address; getline(cin, address);
    senior->setAddress(address);

    cout<<".\n.\n.\n\n";
    cout<<*senior;
    cout<<"Your data has been successfully recorded to the system!\n\n";
    cout<<"Enter 1 to go to main menu\n";
    cout<<"Enter 2 to go back to welcome page\n\n";
    char login = inChoice();

    if (login == '1') {seniorMenu(senior);}
}

/**A function to access Senior user's menu*/
void seniorMenu(Senior* senior) {
    cout<<endl;
    char menu;
    do{
        nextIs("go to main menu");
        cout<<"\n\n";
        // display Senior menu
        senior->mainMenu();
        inputmenu:
        menu = inChoice();
        cout<<endl;

        int code, reqID;

        // REQUEST SERVICE
        if (menu == '1') {
            if (senHelp.getNumOfService() > 0) {
                cout << "Available service\n";
                cout << "--------------------\n\n";
                senHelp.allService();
                cout << "\nWhich service do you want to request?\n";

                bool ready = true; ServiceType* type; char proceed = 'Y';
                do {
                    cout << "Enter service code :";
                    cin >> code;

                    // validate service code
                    while (!senHelp.findService(code)) {
                        errMsg("Service doesn't exist");
                        cout << "Enter service code :";
                        cin >> code;
                    }
                    type = senHelp.returnService(code);

                    // give side note and option if there are no provider
                    // currently offering the chosen service type
                    if (type->getNumOfProvider() == 0) {
                        cout<<endl;
                        cout<<"NOTE: Nobody is able to provide that "
                              "service for you right now\n";
                        cout<<"Do you still want to "
                              "make request (Y/N)?\n";
                        proceed = inChoice();
                        ready = (proceed == 'N');
                        if (!ready) {cout<<endl;}
                    }

                } while(!ready && proceed != 'Y');

                if (proceed != 'N') {
                    cout << ".\n.\n";
                    cout << "Chosen Service => " <<
                    senHelp.returnService(code)->getServiceDesc()
                    << "\n";

                    // create new serviceRequest
                    reqID = senHelp.returnService(code)
                            ->createRequest(senior);
                    // add details
                    cout << "\nPlease fill out "
                            "the details for your request\n";
                    cout << "---------------------------"
                            "-----------------------\n";
                    cout << "Required Date (dd/mm/yyyy)\n";
                    cout << "==>";
                    string date;
                    getline(cin >> ws, date);
                    cout << "Additional Note\n";
                    cout << "==>";
                    string notes;
                    getline(cin, notes);
                    cout << ".\n.\n\n";
                    senHelp.returnService(code)
                    ->addRequestDetail(reqID, date, notes);
                    senior->addRequest(senHelp.returnService(code)
                    ->returnRequest(reqID));
                    cout << "Your request has successfully been sent!"
                            "\n\n";
                    cout << "In the meantime, "
                            "you can check whether your request\n";
                    cout << "has been accepted or not by our "
                            "Service Provider in menu 2\n";
                    cout << "Thank you!\n";
                }

            } else
                errMsg("Sorry, "
                       "currently there is no service available for you");
        }

        // VIEW REQUESTED SERVICE
        else if (menu == '2') {
            if (senior->getNumOfRequest() > 0) {
                cout<<"Requested Service\n";
                cout<<"----------------------\n\n";
                // display list collection of service request
                // (regardless of status)
                senior->showRequest();
            } else
                errMsg("You haven't requested any service yet");
        }

        // MANAGE REQUESTED SERVICE
        else if (menu == '3') {
            if (senior->getNumOfRequest() > 0) {
                cout << "Manage Request Menu\n";
                cout << "----------------------------------\n";
                senior->requestedService();
                cout<<endl;
                cout << "Enter request ID   :";
                cin >> reqID;

                // validate request ID
                while (!senior->findRequest(reqID)) {
                    errMsg("Invalid request ID");
                    cout << "Enter request ID   :";
                    cin >> reqID;
                }

                ServiceRequest* request = senior->getRequest(reqID);
                cout<<endl<<*request<<endl;
                cout << "1. Remove request\n";

                // manage request menu below can be seen and accessed
                // only if the chosen request status is "pending"
                if (request->getStatus() == "PENDING") {
                    cout << "2. Change required date\n";
                    cout << "3. Update request note\n";
                }

                cout << "0. Back to main menu\n\n";
                char manage = inChoice();
                cout<<endl;

                // REMOVE
                if (manage == '1') {
                    cout<<"Are you sure "
                          "you want do remove this request (Y/N)?\n";
                    char sure = inChoice();

                    if (sure == 'Y') {
                        senior->removeRequest
                        (request->getType(), request->getRequestID());
                        cout<<"\nRequest successfully "
                              "removed from system.\n";

                    } else {cout<<"\nCanceled...\n";}
                }

                // CHANGE DATE (only accessible to "pending" request)
                else if (manage == '2' &&
                request->getStatus() == "PENDING") {

                    cout<<"New required date (dd/mm/yyyy) :";
                    string date; getline(cin>>ws, date);
                    request->setDate(date);
                    cout<<"\nDate successfully updated!\n";
                }

                // UPDATE NOTE (only accessible to "pending" request)
                else if (manage == '3' &&
                request->getStatus() == "PENDING") {
                    cout<<"Enter 1 to change note\n";
                    cout<<"Enter 2 to add additional note\n";
                    cout<<"Enter 0 to cancel\n";
                    char note = inChoice();
                    cout<<endl;

                    if (note == '0') {cout<<"\nCanceled...\n";}
                    else {
                        cout << "Notes\n";
                        cout << "------------------------------\n";
                        cout <<request->getNotes() << "\n";

                        string newNote;

                        // change the whole note
                        if (note == '1') {
                            cout << "\nNew note\n";
                            cout << "==>";
                            getline(cin >> ws, newNote);
                            request->setNotes("\t - " + newNote);
                        }

                        // add additional note to existing note
                        if (note == '2') {
                            cout<<"\t -";
                            getline(cin >> ws, newNote);
                            string oldNote = request->getNotes();
                            string change = oldNote + "\n\t - "+newNote;
                            request->setNotes(change);
                        }
                        cout<<"\nNotes successfully updated!\n";
                    }

                } else {cout<<"Canceled...\n\n";}

            } else {errMsg("You don't have "
                           "any service request right now");}
        }

        // COMPLETE REQUEST
        else if (menu == '4') {
            // only request with status "active" can be set to complete
            if (senior->checkRequestList("ACTIVE")) {
                cout << "List of Active Service\n";
                cout << "----------------------------\n\n";
                senior->showRequest("ACTIVE");

                // validation loop
                bool ready = true; ServiceRequest* newRequest;
                do {
                    cout << "Enter request ID   :";
                    cin >> reqID;

                    // validate request ID
                    while (!senior->findRequest(reqID)) {
                        errMsg("Invalid request ID");
                        cout << "Enter request ID   :";
                        cin >> reqID;
                    }

                    // validate request status
                    // (must be an "active" request)
                    newRequest = senior->getRequest(reqID);
                    ready = (newRequest->getStatus() == "ACTIVE");
                    if (!ready) {errMsg("Invalid request ID");}

                } while(!ready);

                // set service request status to "completed"
                newRequest->setStatus('C');
                cout << ".\n.\n\n"
                        "Service request status successfully updated!\n";

            } else
                errMsg("No active service at the moment");
        }

        // GIVE REVIEW
        else if (menu == '5') {
            // can only give review to "completed" request
            if (senior->checkRequestList("COMPLETED")) {

                cout << "List of Completed Service Request\n";
                cout << "---------------------------------------\n\n";
                senior->showRequest("COMPLETED");

                // validation loop
                bool ready = true; ServiceRequest* newRequest;
                do {
                    cout << "Enter request ID   :";
                    cin >> reqID;

                    // validate request ID
                    while (!senior->findRequest(reqID)) {
                        errMsg("Invalid request ID");
                        cout << "Enter request ID   :";
                        cin >> reqID;
                    }

                    // validate request status (must be "completed")
                    newRequest = senior->getRequest(reqID);
                    ready = (newRequest->getStatus() == "COMPLETED");
                    if (!ready) {errMsg("Invalid request ID");}

                } while(!ready);

                cout << endl;
                cout << "Request of "
                     << newRequest->getType()->getServiceDesc()
                     << " done by our kind provider "
                     << newRequest->getProvider()->getFullName()
                     << "\n\n";

                // create review
                cout << "Give thoughts for this service down below!\n";
                cout << "----------------------"
                        "------------------------\n";
                cout << "Review Date (dd/mm/yyyy) :";
                string date;
                getline(cin >> ws, date);
                cout << "Ratings (0-5)            :";
                double ratings; cin >> ratings;
                while (ratings < 0 || ratings > 5) {
                    errMsg("Please give "
                           "ratings on a scale of 0 to 5");
                    cout << "Ratings (0-5)            :";
                    cin >> ratings;
                }
                cout << "Give Comments\n";
                cout << "==>";
                string comments;
                getline(cin >> ws, comments);

                Review *newReview = senior->createReview(newRequest);
                newReview->setDate(date);
                newReview->setRatings(ratings);
                newReview->setComments(comments);

                cout << "\n\nThank you! Your review is sent to "
                     << newReview->getReviewedUser()
                     ->getFullName() << ".\n";
                cout << "We will keep improving "
                        "the quality of our service!\n";

            } else
                errMsg("There is no service "
                       "to be reviewed right now");

        }

        else if (menu == '0') {cout<<"\nLogging out...\n";}
        else {errMsg("Invalid menu"); goto inputmenu;}

    } while (menu != '0');
}

// -------------------- SERVICE PROVIDER -------------------- //

/**A function for signing up Provider user*/
void signUpProv() {

    // can only sign up as provider if service type already exist
    if (senHelp.getNumOfService() == 0) {
        errMsg("Please add service type through menu "
        "manage services before signing up");
        return;
    }
    cout<<"------ SIGN UP SERVICE PROVIDER ------\n\n";

    cout<<"Username      :";
    string username; getline(cin>>ws, username);

    // username must be unique
    while (senHelp.findUser(username)){
        errMsg("Username is already used. Try something else");
        cout<<"Username      :";
        getline(cin>>ws, username);
    }

    cout<<"Password      :";
    string password; getline(cin, password);

    Provider* provider = dynamic_cast<Provider*>
            (senHelp.createUser(username, password, 'P'));

    cout<<"Provider Name :";
    string name; getline(cin, name);
    provider->setFullName(name);

    cout<<"Mobile No     :";
    string mobileNo; getline(cin, mobileNo);
    provider->setMobileNo(mobileNo);

    // provider must add service type upon signing up
    for (;;){
        // display service type
        cout<<"\nList of service type\n";
        cout<<"---------------------------\n";
        senHelp.allService();
        cout<<"\nPlease choose service type to offer\n";
        cout<<"Enter service code :";
        int code; cin>>code;
        if (senHelp.findService(code)){

            // can't add the same service type twice
            if (provider->findServiceType(code)){
                errMsg("Service type already added");

            } else{
                cout<<".\n.\n";
                // add service type to provider
                provider->addServiceType(senHelp.returnService(code));
                // add provider to service type
                senHelp.returnService(code)->addProvider(provider);
                cout<<senHelp.returnService(code)->getServiceDesc()
                <<" added!\n";
            }
        } else {
            errMsg("Service doesn't exist");
        }

        // option to add more than one service type
        cout<<"\nDo you want to add another service (Y/N)?\n";
        char add = inChoice();
        if (add != 'Y') {break;}
    }

    cout<<".\n.\n.\n\n";
    cout<<*provider;
    cout<<"Your data has been successfully recorded to the system!\n\n";
    cout<<"Enter 1 to go to main menu\n";
    cout<<"Enter 2 to go back to welcome page\n\n";
    char login = inChoice();

    if (login == '1') {providerMenu(provider);}
}

/**A function to access menu of Provider user*/
void providerMenu(Provider* provider) {
    cout<<endl;
    int menu;
    do {
        nextIs("go to main menu");
        cout<<"\n\n";
        // display Provider menu
        provider->mainMenu();
        inputmenu:
        menu = inChoice();
        cout<<endl;

        int code, reqID;

        // ADD SERVICE
        if (menu == '1') {
            cout<<"Available service\n";
            senHelp.allService();

            cout<<"Enter service code :";
            cin>>code;

            // validate service code
            while (!senHelp.findService(code)) {
                errMsg("Service doesn't exist");
                cout<<"Enter service code :";
                cin>>code;
            }

            // can't add the same service type twice
            if (provider->findServiceType(code)){
                errMsg("Service type already added");

            } else {
                // add service type to provider
                provider->addServiceType(senHelp.returnService(code));
                // add provider to service type
                senHelp.returnService(code)->addProvider(provider);
                cout<<senHelp.returnService(code)->getServiceDesc()
                <<" successfully added!\n";
            }
        }

        // VIEW SERVICE
        else if (menu == '2') {
            cout<<"Service currently offered to senior\n";
            // display all service type in vector
            provider->allServiceType();
        }

        // STOP SERVICE
        else if (menu == '3') {

            // can only stop service if provider has 2 or more services
            // (provider must offer 1 service type to senior at minimum)
            if (provider->getNumOfServices() >= 2) {
                cout << "Service currently offered to senior\n";
                // display all service type in vector
                provider->allServiceType();

                cout << "\n\nWhich service do you "
                        "want to stop offering?\n";
                cout << "Enter service code :";
                cin >> code;

                // validate service code
                while (!senHelp.findService(code) &&
                !provider->findServiceType(code)) {
                    errMsg("Invalid service code");
                    cout << "Enter service code :";
                    cin >> code;
                }

                // display chosen service type
                ServiceType* type = provider->getServiceType(code);
                cout << "\n"<<type->getServiceDesc()
                     << " (Service Code <"<<type->getServiceCode()
                     <<">)\n\n";

                // give warning and option to cancel stopping if
                // there are active requests on the chosen type
                if(provider->checkStatusReqOnType(type
                    ->getServiceCode(), "ACTIVE")) {
                    cout<<"WARNING: There are still active "
                          "service requests of this type\n";
                }
                cout << "Do you want to "
                        "stop offering this service (Y/N)?\n";
                char stop = inChoice();

                if (stop == 'Y') {
                    provider->stopService(code);
                    cout << ".\n.\n\n"
                            "Service type successfully removed.\n";
                } else
                    cout << ".\n.\n\nCanceled...\n";

            } else
                errMsg("Stop service is not allowed. "
                       "You must have at least 1 service type to offer");
        }

        // VIEW SERVICE REQUEST
        else if (menu == '4') {
            if (provider->getNumOfRequest() > 0) {
                cout << "All Service Request\n";
                cout << "-------------------------\n\n";
                // display list of service request
                // (regardless of status) in own vector
                provider->showRequest();
            } else
                errMsg("You haven't accepted any request");
        }

        // ACCEPT SERVICE REQUEST
        else if (menu == '5') {
            // check whether there are pending request or not
            if (provider->requestAvailable()) {
                cout << "All pending request in pool\n";
                cout << "-----------------------------------------\n\n";
                // show all pending request
                provider->showRequestPool();

                // validation loop
                bool typeReady = true; ServiceType* type;
                do {
                    cout << "Enter service code :";
                    cin >> code;

                    // validate service code
                    while (!senHelp.findService(code) &&
                        !provider->findServiceType(code)) {
                        errMsg("Invalid service code");
                        cout << "Enter service code :";
                        cin >> code;
                    }

                    // validate service type's
                    // "pending" request availability
                    type = senHelp.returnService(code);
                    typeReady = (type->checkReqAvailability());
                    if (!typeReady) {errMsg("Invalid service code");}

                } while (!typeReady);

                // validation loop
                bool reqReady = true; ServiceRequest* newRequest;
                do {
                    cout << "Enter request ID   :";
                    cin >> reqID;

                    // validate request ID
                    while (!type->findRequest(reqID)) {
                        errMsg("Invalid request ID");
                        cout << "Enter request ID   :";
                        cin >> reqID;
                    }

                    // validate request status (must be "pending")
                    newRequest = type->returnRequest(reqID);
                    reqReady = (newRequest->getStatus() == "PENDING");
                    if (!reqReady) {errMsg("Invalid request ID");}

                } while(!reqReady);

                // add service request to provider vector
                // and set request status to 'active'
                cout << ".\n.\n\n";
                provider->addRequest(newRequest);
                newRequest->setStatus('A');
                cout << "Request ID ["
                     << newRequest->getRequestID() << "] of "
                     << newRequest->getType()->getServiceDesc() << " by "
                     << newRequest->getRequestSender()->getFullName()
                     << " accepted!\n";
            } else
                errMsg("There is no request to be accepted yet. "
                       "Please come back later");
        }

        // VIEW ASSIGNED SERVICE
        else if (menu == '6') {
            // display all service request in provider vector
            // that has "active" status
            if (provider->checkRequestList("ACTIVE")) {
                cout<<"Current assigned service\n";
                cout << "-----------------------------\n\n";
                provider->showRequest("ACTIVE");
            } else
                errMsg("There is no active service at the moment");
        }

        // CANCEL ASSIGNED SERVICE
        else if (menu == '7') {
            if (provider->checkRequestList("ACTIVE")) {
                cout << "Current assigned service\n";
                cout << "-----------------------------\n\n";
                // display all service request that has 'active' status
                provider->showRequest("ACTIVE");

                // validation loop
                bool reqReady = true; ServiceRequest* newRequest;
                do {
                    cout << "Enter request ID   :";
                    cin >> reqID;

                    // validate request ID
                    while (!provider->findRequest(reqID)) {
                        errMsg("Invalid request ID");
                        cout << "Enter request ID   :";
                        cin >> reqID;
                    }

                    // validate request status (must be "active")
                    newRequest = provider->getRequest(reqID);
                    reqReady = (newRequest->getStatus() == "ACTIVE");
                    if (!reqReady) {errMsg("Invalid request ID");}

                } while(!reqReady);

                // delete request from own vector
                provider->deleteRequest(reqID);
                // reset request provider
                newRequest->setProvider(NULL);
                // reset request status  to "pending"
                newRequest->setStatus('P');

                cout<<".\n.\n\n";
                cout << "Active service canceled. \n"
                        "Now, other provider can accept this request\n"
                        "or you can re-accept it again in menu 5\n";
            } else
                errMsg("There is no active service at the moment");
        }

        // SEE PORTFOLIO REVIEW
        else if (menu == '8') {
            // can only display portofolio review if senior has sent
            // review to provider
            if (provider->checkRequestList("REVIEWED")){
                provider->portofolioReview();
            } else
                errMsg("There is no reviewed service yet");
        }

        else if (menu == '0') {cout<<"\nLogging out...\n";}
        else {errMsg("Invalid menu"); goto inputmenu;}

    } while (menu != '0');
}

// ------------------------   INPUT METHOD   --------------------------- //

/**A function to trigger input for a charachter
 * and return the input value (capitalized)*/
char inChoice() {
    cout<<"Your choice :";
    char choice; cin>>choice;
    return toupper(choice);
}

// ------------------------   MISC METHOD   ---------------------------- //

/**A function to format and display error message*/
void errMsg(string errText) {cout<<"-- ERROR: "<<errText<<".\n\n";}

/**A function to trigger user to press enter
 * before continuing the program*/
void nextIs(string whatNext) {
    cout<<". . .";
    cin.ignore();
    cout<<"\npress <Enter> to "<<whatNext;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}



