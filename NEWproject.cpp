#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Structs
struct JobListing
{
    int jobId;
    string jobTitle;
    string description;
    string location;
    string qualifications;
    int companyId;
    int applicants[100];
    int applicantsCount = 0;

};

struct Applicant
{
    int id;
    string username;
    string password;
    string fullName;
    string email;
    string phoneNumber;
    string description;
    string jobPreferences[3];
    string dateOfBirth;
    string location;
    JobListing savedjobs[5];
    int savedJobsCount = 0;
};

struct Company
{
    int id;
    string username;
    string password;
    string companyName;
    string email;
    string phoneNumber;
    string description;
    string location;
    JobListing jobListings[100];
    int jobListingsCount = 0;

};

// Global variables
Applicant applicant[100];
Company companies[100];
JobListing jobListings[100];


int numApplicants = 0;
int numCompanies = 0;
int numJobListings = 0;
int numUsers = 0;

//Applicant File System
void writeApplicantDataToFile() {
    ofstream outFile("applicants_data", ios::out | ios::trunc);
    if (!outFile) {
        // Error opening file
        cerr << "File not found!" << endl;
        return;
    }

    for (int i = 0; i < numUsers; ++i) {

        outFile << applicant[i].id << '\t'
            << applicant[i].username << '\t'
            << applicant[i].password << '\t'
            << applicant[i].fullName << '\t'
            << applicant[i].email << '\t'
            << applicant[i].phoneNumber << '\t'
            << applicant[i].description << '\t'
            << applicant[i].dateOfBirth << '\t'
            << applicant[i].location << '\t';
        for (int j = 0; j < 3; ++j) {
            outFile << applicant[i].jobPreferences[j] << '\t';
        }
        outFile << endl;
    }

    outFile.close();
}

void loadApplicantDataFromFile() {

    ifstream inFile("applicants_data");
    if (!inFile) {
        // Error opening file
        cerr << "Error: Unable to open file '" << "applicant_data" << "' for reading." << endl;

        return;
    }

    int saved_id;
    string saved_username, saved_password, saved_fullName, saved_email, saved_phoneNumber, saved_description, saved_dateOfBirth, saved_location;
    string saved_jobPreferences[3];

    while (inFile >> saved_id >> saved_username >> saved_password >> saved_fullName >> saved_email >> saved_phoneNumber >> saved_description >> saved_dateOfBirth >> saved_location >> saved_jobPreferences[0] >> saved_jobPreferences[1] >> saved_jobPreferences[2]) {
        Applicant newApplicant;
        newApplicant.id = saved_id;
        newApplicant.username = saved_username;
        newApplicant.password = saved_password;
        newApplicant.fullName = saved_fullName;
        newApplicant.email = saved_email;
        newApplicant.phoneNumber = saved_phoneNumber;
        newApplicant.description = saved_description;
        newApplicant.dateOfBirth = saved_dateOfBirth;
        newApplicant.location = saved_location;
        for (int i = 0; i < 3; ++i) {
            newApplicant.jobPreferences[i] = saved_jobPreferences[i];
        }
        applicant[numUsers++] = newApplicant;
    }
    inFile.close();

}

//Company File System
void writeCompanyDataToFile( Company companies[], int newCompanies) {
    ofstream outFile("company_data", ios::out | ios::trunc);
    if (!outFile) {
        // Error opening file
        cerr << "File not found!" << endl;
        return;
    }

    for (int i = 0; i < numCompanies; ++i) {
        outFile << companies[i].id << '\t'
            << companies[i].username << '\t'
            << companies[i].password << '\t'
            << companies[i].companyName << '\t'
            << companies[i].email << '\t'
            << companies[i].phoneNumber << '\t'
            << companies[i].description << '\t'
            << companies[i].location << '\t';
        outFile << endl;
    }
    outFile.close();
}
void writingJobDataToFIle( Company companies[], int newCompanies) {
    ofstream jobFile("job_data.txt", ios::out | ios::trunc);
    if (!jobFile) {
        cerr << "Error: Unable to open job data file for writing." << endl;
        return;
    }

    for (int j = 0; j < numCompanies; ++j) {
        jobFile << companies[j].id << '\t'
            << jobListings[j].jobId << '\t'
            << jobListings[j].jobTitle << '\t'
            << jobListings[j].description << '\t'
            << jobListings[j].location << '\t'
            <<jobListings[j].qualifications << '\t';
        jobFile << endl;
    }
    jobFile.close();
}

void loadCompanyDataFromFile() {

    ifstream inFile("company_data");
    if (!inFile) {
        cerr << "Error: Unable to open file '" << "company_data" << "' for reading." << endl;
        return;
    }

    int saved_id;
    string saved_username, saved_password, saved_CompanyName, saved_email, saved_phoneNumber, saved_description, saved_location;

    while (inFile >> saved_id >> saved_username >> saved_password >> saved_CompanyName >> saved_email >> saved_phoneNumber >> saved_description >> saved_location)
    {
        Company newCompany;
        newCompany.id = saved_id;
        newCompany.username = saved_username;
        newCompany.password = saved_password;
        newCompany.companyName = saved_CompanyName;
        newCompany.email = saved_email;
        newCompany.phoneNumber = saved_phoneNumber;
        newCompany.description = saved_description;
        newCompany.location = saved_location;

        // Add the new company to the array of companies
        companies[numCompanies++] = newCompany;
    }
    inFile.close();


    ifstream jobFile("job_data.txt");
    if (!jobFile) {
        cerr << "Error: Unable to open file 'job_data.txt' for reading." << endl;
        return;
    }


    int companyId, jobId;
    string jobTitle, description, location, qualifications;
    while (jobFile >> companyId >> jobId >> jobTitle >> description >> location >> qualifications) {
        // Find the company associated with the companyId
        bool foundCompany = false;
        for (int i = 0; i < numCompanies; ++i) {
            if (companies[i].id == companyId) {
                foundCompany = true;
                // Check if the company's job list is full
                if (companies[i].jobListingsCount < 100) {
                    // Create a new JobListing and add it to the company's job list
                    JobListing newJob;
                    newJob.jobId = jobId;
                    newJob.jobTitle = jobTitle;
                    newJob.description = description;
                    newJob.location = location;
                    newJob.qualifications = qualifications;
                    companies[i].jobListings[companies[i].jobListingsCount++] = newJob;
                    numJobListings++;
                }
                else {
                    cerr << "Error: Maximum number of job listings reached for company '" << companies[i].companyName << "'. Cannot add more jobs." << endl;
                }
                break; // Exit loop once job is added to the company
            }
        }
        if (!foundCompany) {
            cerr << "Error: Company with ID '" << companyId << "' not found. Skipping job listing." << endl;
        }
    }

    jobFile.close();
}

// Function to register a new user
void registerApplicant()
{
    Applicant newapplicant;
    cout << "Enter Applicant ID:";
    cin >> newapplicant.id;
    cin.ignore();
    cout << "Enter username: ";
    getline(cin, newapplicant.username);
    cout << "Enter password: ";
    getline(cin, newapplicant.password);
    cout << "Enter full Name: ";
    getline(cin, newapplicant.fullName);
    cout << "Enter Email: ";
    getline(cin, newapplicant.email);
    cout << "Enter phoneNumber: ";
    getline(cin, newapplicant.phoneNumber);
    cout << "Enter description: ";
    getline(cin, newapplicant.description);
    cout << "Enter jobPreferences: ";
    for (int i = 0; i < 3; i++)
    {
        getline(cin, newapplicant.jobPreferences[i]);
    }

    cout << "Enter dateOfBirth:";
    getline(cin, newapplicant.dateOfBirth);
    cout << "Enter location:";
    getline(cin, newapplicant.location);

    // Check if username already exists
    for (int i = 0; i < numUsers; ++i)
    {
        if (applicant[i].username == newapplicant.username)
        {
            cout << "Username already exists. Please choose a different one.\n";
            return;
        }
    }

    // Add the new user
    applicant[numUsers] = newapplicant;
    cout << "Registration successfully!\n";
    numUsers++;
}

// Function for Applicant login
bool ApplicantLogin(string& loggedInapplicant)
{
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    // Find the user and check password
    for (int i = 0; i < numUsers; ++i)
    {
        if (applicant[i].username == username && applicant[i].password == password)
        {
            loggedInapplicant = username;
            cout << "Login successful!\n";
            return true;
        }
    }
    cout << "Invalid username or password.\n";
    return false;
}

// Function to display all job listings
void viewJobListings(JobListing jobListings[], int numListings, int companyId)
{
    cout << "All Job Listings:" << endl;
    for (int i = 0; i < numListings; ++i)
    {
        
        cout << "Job ID: " << jobListings[i].jobId << endl;
        cout << "Title: " << jobListings[i].jobTitle << endl;
        cout << "Description: " << jobListings[i].description << endl;
        cout << "Location: " << jobListings[i].location << endl;
        cout << "Qualifications: " << jobListings[i].qualifications << endl << endl;
    }
    cout << "Your Job Listings:" << endl;
    for (int i = 0; i < companies[companyId].jobListingsCount; i++)
    {
        JobListing& job = companies[companyId].jobListings[i];

        cout << "Job ID: " << job.jobId << " | Title: " << job.jobTitle << " | Location: " << job.location <<" | Qualifications: "<<job.qualifications<< endl;
    }
}

// Function to search for jobs by keyword
void Jobsearchfunctionality(JobListing jobs[], int numJobs, string& keyword)
{
    bool found = false;
    for (int i = 0; i < numJobs; i++)
    {
        if (jobs[i].jobTitle.find(keyword) != string::npos || jobs[i].description.find(keyword) != string::npos)
        {
            cout << "Title: " << jobs[i].jobTitle << endl;
            cout << "Description: " << jobs[i].description << endl << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No jobs found matching the keyword." << endl;
    }
}

// Function to display detailed information about a job
void displayJobDetail(JobListing& job)
{
    cout << "Job Title: " << job.jobTitle << endl;
    cout << "Description: " << job.description << endl;
    cout << "Location: " << job.location << endl;
    cout << "Qualifications: " << job.qualifications << endl;
}

//Function to apply for a job
void applyForJob(JobListing& job, int companyId) {

    cout << "Applying for job: " << job.jobTitle << " at  " << companies[companyId].companyName << endl;
    int ID;
    int i;
    bool isFound = false;
    // Displaying the Applicant's information
    cout << "Enter your Applicant ID: ";
    cin >> ID;
    for (i = 0; i < 100; i++)
    {
        if (ID == applicant[i].id) {

            cout << "Applicant FullName: " << applicant[i].fullName << endl;
            cout << "Contact Email: " << applicant[i].email << endl;
            cout << "Contact Phone: " << applicant[i].phoneNumber << endl;
            isFound = true;
        }
    }

    if (isFound) {

        //check if the job can accept more applicants
        if (job.applicantsCount < 100)
        {
            //Add applicant  ID to the job's list of applicants 
            job.applicants[job.applicantsCount] = applicant[i].id;
            job.applicantsCount++;

            cout << "Applicant submitted successfully!" << endl;
        }
        else
        {
            cout << "Maximum number of applicants reached for this job." << endl;
        }
    }
    else {
        cout << " Invalid  Applicant ID" << endl;
    }
}

// Function to save a job for future reference
void saveJob(Applicant& applicant, JobListing& job) {
    // Ensure that savedJobsCount is within bounds
    if (applicant.savedJobsCount >= 0 && applicant.savedJobsCount < 5) {
        // Add the job to the applicant's list of saved jobs
        applicant.savedjobs[applicant.savedJobsCount++] = job;
        cout << "Job saved successfully." << endl;
    }
    else {
        cout << "You have reached the maximum limit of saved jobs." << endl;
    }
}

// Function to update user profile
void updateUserProfile(Applicant& applicant) {
    cout << "Enter new username: ";
    getline(cin, applicant.username);
    cout << "Enter password: ";
    getline(cin, applicant.password);
    cout << "Enter full Name: ";
    getline(cin, applicant.fullName);
    cout << "Enter new email: ";
    getline(cin, applicant.email);
    cout << "Enter new phone: ";
    getline(cin, applicant.phoneNumber);
    cout << "Enter new preferred location: ";
    getline(cin, applicant.location);
}

// Function for company login
bool companyLogin(string username, string password, int& companyIndex) {
    for (int i = 0; i < numCompanies; i++) {
        if (companies[i].username == username && companies[i].password == password) {
            companyIndex = i;
            return true; // Company found
        }
    }
    return false; // Company not found
}

// Function to register a new company
void registerCompany()
{
    Company newCompany;
    cout << "Enter Company Username: ";
    getline(cin, newCompany.username);
    cout << "Enter Company Password: ";
    getline(cin, newCompany.password);
    cout << "Enter Company Name: ";
    getline(cin, newCompany.companyName);
    cout << "Enter Company Email: ";
    getline(cin, newCompany.email);
    cout << "Enter Company Phone Number: ";
    getline(cin, newCompany.phoneNumber);
    cout << "Enter Company Description: ";
    getline(cin, newCompany.description);
    cout << "Enter Company Location: ";
    getline(cin, newCompany.location);

    newCompany.id = numCompanies + 1; // Generate unique ID
    newCompany.jobListingsCount = 0; // Initialize job listings count

    companies[numCompanies++] = newCompany;

    cout << "Registration successfully!" << endl;
}

// Function to post a job
void postJob(int companyId)
{
    JobListing newJob;
    cout << "Enter Job Title: ";
    getline(cin, newJob.jobTitle);
    cout << "Enter Job Description: ";
    getline(cin, newJob.description);
    cout << "Enter Job Location: ";
    getline(cin, newJob.location);
    cout << "Enter Job Qualifications: ";
    getline(cin, newJob.qualifications);

    newJob.jobId = numJobListings + 1;
    newJob.companyId = companies[companyId].id;
    newJob.applicantsCount = 0;

    companies[companyId].jobListings[companies[companyId].jobListingsCount++] = newJob;
    jobListings[numJobListings++] = newJob;
    cout << "Job Posted Successfully!" << endl;
}

// Function to manage job listings
void manageJobListings(int companyId)
{
    cout << "Your Job Listings:" << endl;
    for (int i = 0; i < companies[companyId].jobListingsCount; i++)
    {
        JobListing& job = companies[companyId].jobListings[i];
        cout << "Job ID: " << job.jobId << " | Title: " << job.jobTitle << " | Location: " << job.location << endl;
    }

    cout << "Enter Job ID to Edit/Delete (0 to go back): ";
    int jobId;
    cin >> jobId;
    cin.ignore();

    if (jobId == 0)
    {
        return;
    }

    for (int i = 0; i < companies[companyId].jobListingsCount; i++)
    {
        if (companies[companyId].jobListings[i].jobId == jobId)
        {
            cout << "1. Edit Job" << endl;
            cout << "2. Delete Job" << endl;
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
            {
                // Edit job
                JobListing& job = companies[companyId].jobListings[i];
                cout << "Enter New Job Title: ";
                getline(cin, job.jobTitle);
                cout << "Enter New Job Description: ";
                getline(cin, job.description);
                cout << "Enter New Job Location: ";
                getline(cin, job.location);
                cout << "Enter New Job Qualifications: ";
                getline(cin, job.qualifications);
                cout << "Job Updated Successfully!" << endl;
                break;
            }
            case 2: {
                // Delete job
                for (int j = i; j < companies[companyId].jobListingsCount - 1; j++)
                {
                    companies[companyId].jobListings[j] = companies[companyId].jobListings[j + 1];
                }
                companies[companyId].jobListingsCount--;
                cout << "Job Deleted Successfully!" << endl;
                break;
            }
            default:
                cout << "Invalid choice." << endl;
            }
            return;
        }
    }

    cout << "Job ID not found." << endl;
}

// Function to view job applications
void viewJobApplications(int companyId)
{
    cout << "Your Job Listings:" << endl;
    for (int i = 0; i < companies[companyId].jobListingsCount; i++)
    {
        JobListing& job = companies[companyId].jobListings[i];
        cout << "Job ID: " << job.jobId << " | Title: " << job.jobTitle << " | Location: " << job.location << endl;
    }

    cout << "Enter Job ID to View Applications (0 to go back): ";
    int jobId;
    cin >> jobId;
    cin.ignore(); // Consume newline

    if (jobId == 0)
    {
        return; // Go back
    }

    for (int i = 0; i < numJobListings; i++)
    {
        if (jobListings[i].jobId == jobId)
        {
            cout << "Job Title: " << jobListings[i].jobTitle << endl;
            cout << "Received Applications (" << jobListings[i].applicantsCount << "):" << endl;
            if (jobListings[i].applicantsCount == 0) {
                cout << "No applications yet." << endl;
            }
            else
            {
                for (int j = 0; j < jobListings[i].applicantsCount; j++)
                {
                    int applicantId = jobListings[i].applicants[j];
                    for (int k = 0; k < numApplicants; k++)
                    {
                        if (applicant[k].id == applicantId)
                        {
                            cout << "Applicant ID: " << applicant[k].id << " | Name: " << applicant[k].fullName << endl;
                            // Display more applicant info if needed
                        }
                    }
                }
            }
            return;
        }
    }

    cout << "Job ID not found." << endl;
}

// Function to update company profile
void updateCompanyProfile(int companyId)
{
    cout << "Update Company Profile" << endl;
    cout << "Current Company Name: " << companies[companyId].companyName << endl;
    cout << "Enter New Company Name: ";
    getline(cin, companies[companyId].companyName);
    cout << "Current Email: " << companies[companyId].email << endl;
    cout << "Enter New Email: ";
    getline(cin, companies[companyId].email);
    cout << "Current Phone Number: " << companies[companyId].phoneNumber << endl;
    cout << "Enter New Phone Number: ";
    getline(cin, companies[companyId].phoneNumber);
    cout << "Current Description: " << companies[companyId].description << endl;
    cout << "Enter New Description: ";
    getline(cin, companies[companyId].description);
    cout << "Current Location: " << companies[companyId].location << endl;
    cout << "Enter New Location: ";
    getline(cin, companies[companyId].location);
    cout << "Profile Updated Successfully!" << endl;
}

// Function to search applicants based on job title
void viewApplicants(int companyId)
{
    cout << "Your Job Listings:" << endl;
    for (int i = 0; i < companies[companyId].jobListingsCount; i++)
    {
        JobListing& job = companies[companyId].jobListings[i];
        cout << "Job ID: " << job.jobId << " | Title: " << job.jobTitle << " | Location: " << job.location << endl;
    }

    cout << "Enter Job ID to View Applicants (0 to go back): ";
    int jobId;
    cin >> jobId;
    cin.ignore(); // Consume newline

    if (jobId == 0)
    {
        return; // Go back
    }

    for (int i = 0; i < numJobListings; i++)
    {
        if (jobListings[i].jobId == jobId)
        {
            cout << "Job Title: " << jobListings[i].jobTitle << endl;
            cout << "Received Applications (" << jobListings[i].applicantsCount << "):" << endl;
            cout << "Applicant Fullname: " << applicant[i].fullName << endl;
            cout << "Applicant Phone number: " << applicant[i].phoneNumber << endl;
            cout << "Applicant Email: " << applicant[i].email << endl;
            if (jobListings[i].applicantsCount == 0) {
                cout << "No applications yet." << endl;
            }
            else
            {
                for (int j = 0; j < jobListings[i].applicantsCount; j++)
                {
                    int applicantId = jobListings[i].applicants[j];
                    for (int k = 0; k < numApplicants; k++)
                    {
                        if (applicant[k].id == applicantId)
                        {
                            cout << "Applicant ID: " << applicant[k].id << " | Name: " << applicant[k].fullName << endl;
                            // Display more applicant info if needed
                        }
                    }
                }
            }
            return;
        }
    }

    cout << "Job ID not found." << endl;
}

int main()
{
    // Load applicant data from file
    loadCompanyDataFromFile();
    loadApplicantDataFromFile();


    int choice;
    int companyId = 0;

    while (true)
    {

        cout << "\n****************************** WELCOME TO JOB PORTAL APPLICATION ******************************" << endl;
        cout << "1. Login as Applicant" << endl;
        cout << "2. Register as Applicant" << endl;
        cout << "3. Login as Company" << endl;
        cout << "4. Register as Company" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Consume newline

        switch (choice)
        {
        case 1: {
            system("cls");
            // Applicant Login
            string loggedInapplicant;
            if (ApplicantLogin(loggedInapplicant)) {
                cout << "Welcome, " << loggedInapplicant << "!" << endl;
                while (true) {
                    cout << "\n******************** APPLICANT MENU ********************" << endl;
                    cout << "1. View Job Listings" << endl;
                    cout << "2. Job Search Functionality" << endl;
                    cout << "3. Display Job Detail" << endl;
                    cout << "4. Apply For Job" << endl;
                    cout << "5. Save Job" << endl;
                    cout << "6. Update Applicant Profile" << endl;
                    cout << "7. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cin.ignore();

                    switch (choice) {
                    case 1:
                        system("cls");
                        viewJobListings(jobListings, numJobListings, companyId);
                        break;
                    case 2:
                        system("cls"); {
                            string keyword;
                            cout << "Enter keyword: ";
                            cin >> keyword;
                            cin.ignore();
                            Jobsearchfunctionality(jobListings, numJobListings, keyword);
                            break;
                        }
                    case 3:  system("cls"); {
                        int jobId;
                        cout << "Enter Job ID: ";
                        cin >> jobId;
                        cin.ignore();
                        if (jobId >= 1 && jobId <= numJobListings) {
                            displayJobDetail(jobListings[jobId - 1]);
                        }
                        else {
                            cout << "Invalid Job ID." << endl;
                        }
                        break;
                    }
                    case 4: system("cls"); {
                        int jobId;
                        cout << "Enter Job ID to apply: ";
                        cin >> jobId;
                        cin.ignore();
                        if (jobId >= 1 && jobId <= numJobListings) {
                            applyForJob(jobListings[jobId - 1], companyId);
                        }
                        else {
                            cout << "Invalid Job ID." << endl;
                        }
                        break;
                    }
                    case 5: {
                        system("cls");
                        int jobId;
                        cout << "Enter Job ID to save: ";
                        cin >> jobId;
                        cin.ignore();
                        if (jobId >= 1 && jobId <= numJobListings) {
                            saveJob(applicant[numApplicants], jobListings[jobId - 1]);
                        }
                        else {
                            cout << "Invalid Job ID." << endl;
                        }
                        break;
                    }

                    case 6:
                        system("cls");
                        updateUserProfile(applicant[numApplicants]);
                        break;
                    case 7:
                        cout << "Logged out. Goodbye!" << endl;
                        main();
                        return 0;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            else {
                cout << "Invalid username or password. Please try again." << endl;
            }
            break;
        }
        case 2:
        {
            system("cls");
            // Applicant Registration
            registerApplicant();
            writeApplicantDataToFile();
            break;

        }

        case 3: {
            system("cls");
            // Company Login
            string username, password;
            cout << "Enter Company Username: ";
            getline(cin, username);
            cout << "Enter Company Password: ";
            getline(cin, password);

            int companyIndex;
            if (companyLogin(username, password, companyIndex)) {
                cout << "Login successfully!" << endl;

                while (true)
                {
                    cout << "\n******************** COMPANY MENU ********************" << endl;
                    cout << "1. Post Job" << endl;
                    cout << "2. Manage Job Listings" << endl;
                    cout << "3. View Job Applications" << endl;
                    cout << "4. Update Company Profile" << endl;
                    cout << "5. Search for Applicants" << endl;
                    cout << "6. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cin.ignore(); // Consume newline

                    switch (choice) {
                    case 1:
                        system("cls");
                        postJob(companyIndex);
                        break;
                    case 2:
                        system("cls");
                        manageJobListings(companyIndex);
                        break;
                    case 3:
                        system("cls");
                        viewJobApplications(companyIndex);
                        break;
                    case 4:
                        updateCompanyProfile(companyIndex);
                        break;
                    case 5:
                        system("cls");
                        viewApplicants(companyIndex);
                        break;
                    case 6:
                        system("cls");
                        cout << "Logged out. Goodbye!" << endl;

                        main();
                        return 0;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            else {
                cout << "Invalid username or password. Please try again." << endl;
            }
            break;
        }
        case 4: {
            system("cls");
            // Company Registration
            registerCompany();

            break;
        }
        case 5: {
            system("cls");


            writeCompanyDataToFile(companies, numCompanies);
            writingJobDataToFIle(companies, numCompanies);
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }


    }

    return 0;
}
