#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
    public:
    string name;
    int age;
    string date_of_birth; // date/month/year
    string gender; // male, female, intersex
    string address;
    int category; // 1.doctor 2.patient 3.nurse 4.driver 5.non-medical staff
    long long int mob;
     Person(string sex, int cat){    // for a random person in need of medical history
        name = "";
        age = 0 ;
        date_of_birth = "" ;
        gender = sex;
        address = "";
        category = cat;
        mob = 0 ;
    }

    Person(string name, int age, string dob, string sex, string address, int cat, long long int mob){  //for a person which have full knowledge like doctor, nurse, staff, 
        this->name = name ;
        this->age = age ;
        this->date_of_birth = dob;
        this->gender = sex ;
        this->address = address;
        this->category = cat;
        this->mob = mob;
    }

    void displayPerson() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Date of Birth: " << date_of_birth << endl;
        cout << "Gender: " << gender << endl;
        cout << "Address: " << address << endl;
        cout << "Mobile No.: " << mob << endl;
        cout << "Category: " << (category == 1 ? "Doctor" : category == 2 ? "Patient" : category == 3 ? "Nurse" : category == 4 ? "Driver" : "Non-Medical Staff") << endl;
    }
};

class MedicalHistory {
private:
    string treatment;
    string doctor;
    string date;

public:
    MedicalHistory(const string& treatment, const string& doctor, const string& date){
        this->treatment=treatment; 
        this->doctor=doctor; 
        this->date=date;
        }

    void display() const {
        cout << "Treatment: " << treatment << ", Doctor: " << doctor << ", Date: " << date << endl;
    }
};

class Patient : public Person {
public:
    string disease;
    string blood_group;
    int reg_number;
    int weight;
    vector<MedicalHistory> medical_histories; // Use vector to store multiple medical history entries
    int status; // 0. discharge 1. admit
    string discharge_date;
    string discharge_timing;
    string live_status; // dead or alive
    string death_timing;
    string death_date;

public:
    Patient(string name, int age, string dob, string sex, string address, int cat, long long int mob, 
        string disease, string bg, int reg, int wt)
    : Person(name, age, dob, sex, address, cat, mob) {
    this->disease = disease;
    this->blood_group = bg;
    this->reg_number = reg; 
    this->weight = wt;
    this->status = 0; 
    this->discharge_date = ""; 
    this->discharge_timing = ""; 
    this->live_status = "alive";
    this->death_timing = "";
    this->death_date = ""; 
}

    void addMedicalHistory(const MedicalHistory& history) {
        medical_histories.push_back(history);
    }

     void displayPatientInfo() const {
        displayPerson();
        cout << "Disease: " << disease << endl;
        cout << "Blood Group: " << blood_group << endl;
        cout << "Registration Number: " << reg_number << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Status: " << (status == 0 ? "Discharged" : "Admitted") << endl;
        cout << "Live Status: " << live_status << endl;
        if (live_status == "dead") {
            cout << "Death Date: " << death_date << endl;
            cout << "Death Timing: " << death_timing << endl;
        }
    }
};

class Patient_Management_System {
private:
    vector<Patient> patients;
    int nextRegNumber;

public:
    Patient_Management_System(){
        this->nextRegNumber=1;
        }

    void registerPatient() {
        string name, dob, sex, address, disease, blood_group, medical_history;
        int age, weight;
        medical_history="";

        cout << "Enter patient name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter patient age: ";
        cin >> age;
        
        cout << "Enter date of birth (DD/MM/YYYY): ";
        cin.ignore();
        getline(cin, dob);
        
        cout << "Enter gender (Male/Female/Intersex): ";
        getline(cin, sex);
        
        cout << "Enter address: ";
        getline(cin, address);
        
        cout << "Enter blood group: ";
        getline(cin, blood_group);
        
        cout << "Enter weight (in kg): ";
        cin >> weight;

        cout << "Enter disease: ";
        cin.ignore();
        getline(cin, disease);

        Patient newPatient( name, age, dob, sex, address, 2, 0, disease, blood_group, nextRegNumber++, weight);
        patients.push_back(newPatient);
        cout << "Patient registered successfully with Registration Number: " << newPatient.reg_number << endl;
    }

    void displayPatients() const {
        if (patients.empty()) {
                        cout << "No patients to display." << endl;
            return;
        }

        cout << "Patient List:" << endl;
        for (const auto& patient : patients) {
            patient.displayPatientInfo();
            cout << "-----------------------------------" << endl;
        }
    }

    void addMedicalHistory() {
    int reg_number;
    cout << "Enter registration number to add medical history: ";
    cin >> reg_number;

    for (auto& patient : patients) {
        if (patient.reg_number == reg_number) {
            string treatment, doctor, date;

            cout << "Enter treatment: ";
            cin.ignore();
            getline(cin, treatment);
            cout << "Enter doctor name: ";
            getline(cin, doctor);
            cout << "Enter date (DD/MM/YYYY): ";
            getline(cin, date);

            // Create a new MedicalHistory object and add it to the patient's history
            MedicalHistory history(treatment, doctor, date);
            patient.addMedicalHistory(history);
            cout << "Medical history added for registration number: " << reg_number << endl;
            return;
        }
    }
    cout << "Registration number not found!" << endl;
}

   void dischargePatient() {
    int reg_number;
    cout << "Enter registration number to discharge: ";
    cin >> reg_number;

    for (auto& patient : patients) {
        if (patient.reg_number == reg_number) {
            patient.status = 0; // 0 means discharged
            cout << "Patient ID: " << reg_number << " has been discharged." << endl;
            return;
        }
    }
    cout << "Registration number not found!" << endl;
}

    void menu() {
        int choice;
        do {
            cout << "\n--- Patient Management System ---" << endl;
            cout << "1. Register Patient" << endl;
            cout << "2. Add Medical History" << endl;
            cout << "3. Discharge Patient" << endl;
            cout << "4. Display Patients" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    registerPatient();
                    break;
                case 2:
                    addMedicalHistory();
                    break;
                case 3:
                    dischargePatient();
                    break;
                case 4:
                    displayPatients();
                    break;
                case 5:
                    cout << "Exiting the system." << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    Patient_Management_System pms;
    pms.menu();
    return 0;
}