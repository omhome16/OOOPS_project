#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Staff;
class Permanent;
class Adhoc;
class Patient;
class Room;
class Bed;
class RoomManager;

// Base Person class
class Person {
public:
    string name;
    int age;
    string date_of_birth;
    string gender;
    string address;
    int category;
    long long int mob;
    Person(string name, int age, string dob, string sex, string address, int cat, long long mob)
        : name(name), age(age), date_of_birth(dob), gender(sex), address(address), category(cat), mob(mob) {}
    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Date of Birth: " << date_of_birth << endl;
        cout << "Gender: " << gender << endl;
        cout << "Address: " << address << endl;
        cout << "Mobile No.: " << mob << endl;
        cout << "Category: " << (category == 1 ? "Doctor" : category == 2 ? "Patient" : category == 3 ? "Nurse" : category == 4 ? "Driver" : "Non-Medical Staff") << endl;
    }
    
     // Function to write a person's data to a file
    virtual void writeToFile(ofstream& outFile) const {
        outFile << name << "," << age << endl;
    }

    // Function to read a person's data from a file
    virtual void readFromFile(ifstream& inFile) {
        getline(inFile, name, ',');
        inFile >> age;
        inFile.ignore();  // Ignore the newline character
    }
};

// Staff class inherits Person
class Staff : public Person {
protected:
    string department;
    string date_of_joining;
    int experience;
    string qualifications;
    string location;
    string post;
    vector<string> work_schedule;  //type of dynamic array
    vector<string> benefits;

public:
    Staff(string name, int age, string dob, string sex, string address, int cat, long long mob, string dept, string doj,
          int exp, string qual, string loc, string post, vector<string> schedule, vector<string> ben)
        : Person(name, age, dob, sex, address, cat, mob), department(dept), date_of_joining(doj), experience(exp),
          qualifications(qual), location(loc), post(post), work_schedule(schedule), benefits(ben) {}

    virtual void display() const {
        Person::display();
        cout << "Department: " << department << endl;
        cout << "Date of Joining: " << date_of_joining << endl;
        cout << "Experience: " << experience << " years" << endl;
        cout << "Qualifications: " << qualifications << endl;
        cout << "Location: " << location << endl;
        cout << "Post: " << post << endl;
        cout << "Work Schedule: ";
        for (const string& day : work_schedule) {
            cout << day << " ";
        }
        cout << endl;
        cout << "Benefits: ";
        for (const string& benefit : benefits) {
            cout << benefit << " ";
        }
        cout << endl;
    }

     void writeToFile(ofstream& outFile) const override {
        outFile << name << "," << age << "," <<department << endl;
    }

    void readFromFile(ifstream& inFile) override {
        getline(inFile, name, ',');
        inFile >> age;
        inFile.ignore();  // Ignore the comma
        getline(inFile, department);
    }
};

// Permanent Staff class inherits Staff
class Permanent : public Staff {
private:
    double base_salary;
    int leaves_allocated;
public:
    Permanent(string name, int age, string dob, string sex, string address, int cat, long long mob, string dept,
              string doj, int exp, string qual, string loc, string post, vector<string> schedule, vector<string> ben,
              double sal, int leaves_alloc)
        : Staff(name, age, dob, sex, address, cat, mob, dept, doj, exp, qual, loc, post, schedule, ben),
          base_salary(sal), leaves_allocated(leaves_alloc) {}
    void display() const override {
        Staff::display();
        cout << "Base Salary: " << base_salary << endl;
        cout << "Leaves Allocated: " << leaves_allocated << endl;
    }
   
};

// Adhoc Staff class inherits Staff
class Adhoc : public Staff {
private:
    double hourly_rate;
    double base_salary;
    int contract_duration;
public:
    Adhoc(string name, int age, string dob, string sex, string address, int cat, long long mob, string dept,
          string doj, int exp, string qual, string loc, string post, vector<string> schedule, vector<string> ben,
          double rate, double base_sal, int duration)
        : Staff(name, age, dob, sex, address, cat, mob, dept, doj, exp, qual, loc, post, schedule, ben),
          hourly_rate(rate), base_salary(base_sal), contract_duration(duration) {}
    void display() const override {
        Staff::display();
        cout << "Hourly Rate: " << hourly_rate << endl;
        cout << "Base Salary: " << base_salary << endl;
        cout << "Contract Duration: " << contract_duration << " months" << endl;
    }
   
};

// Patient class
class Patient {
public:
    string name;
    int age;
    string medical_history;
    string room_assigned;
    double bill;
    int patientId;
    static int nextPatientId;
    

    Patient(string name, int age)
        : name(name), age(age), medical_history("Not provided"), room_assigned("Not assigned"), bill(0.0) {
            patientId = ++nextPatientId;
        }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Medical History: " << medical_history << endl;
        cout << "Room Assigned: " << room_assigned << endl;
        
    }

   
};
int Patient::nextPatientId = 0;

// Room class
class Room
{
    public:
    int Room_no;
    string Roomtype;
    bool isavailable;
    int capacity;
    int occupiedbeds;

   Room(int number, const string& type, int capacity)
   : Room_no(number), Roomtype(type), isavailable(true), capacity(capacity), occupiedbeds(0) {}
   Room(int number)
   : Room_no(number), isavailable(true), occupiedbeds(0),capacity(0) {
    cout << "Enter Room type :";
    cin >> Roomtype;
    cout <<"Enter capacity : ";
    cin >> capacity;
   }
   Room() : Room_no(0), isavailable(true), occupiedbeds(0), capacity(5), Roomtype("General"){}
   int getRoomNumber() const { return Room_no; }
    string getRoomType() const { return Roomtype; }
    bool getAvailability() const { return isavailable; }
    void setAvailability(bool availability) { isavailable = true; }
    int getOccupiedBeds() const { return occupiedbeds; }
    int getCapacity() const { return capacity; }
    void display() const {
        cout << "Room Number: " << Room_no << endl;
        cout << "Room Type: " << Roomtype << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Occupied Beds: " << occupiedbeds << endl;
    }

};

class Bed
{
    private:
    int bedId;
    bool isoccupied;

public:
   Bed(int id) : bedId(id), isoccupied(false) {}

    int getBedId() const { return bedId; }
    bool getoccupiedStatus() const { return isoccupied; }

    void occupyBed() { isoccupied = true; }
    void releaseBed() { isoccupied = false; }

};

class RoomManager {
private:
    vector<Room> rooms;
    map<int, vector<Bed>> beds;

    public:
    RoomManager() {
        rooms.push_back(Room());
    }

    void addRoom(int roomNumber, const string& roomType, int capacity) {
        rooms.emplace_back(roomNumber, roomType, capacity);
    }

    Room* findAvailableRoom(const string& roomType) {
        for (auto& room : rooms) {
            if (room.getRoomType() == roomType && room.getAvailability()) {
                return &room;
            }
        }
        return nullptr; 
    }

    bool assignRoomToPatient(int roomNumber, Patient& patient) {
        for (auto& room : rooms) {
             if (room.getRoomNumber() == roomNumber && room.getAvailability()) {
                 room.setAvailability(false); // Mark the room as occupied
                 patient.room_assigned = "Room " + to_string(roomNumber); // Assign the room to the patient
                return true; // Room assigned successfully
             }
         }
        return false; // Room not available
    }

    bool releaseRoom(int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                return true; 
            }
        }
        return false;
    }
};

// Function to add permanent staff
void addPermanentStaff(vector<Permanent>& permanentStaff) {
    string name, dob, sex, address, dept, doj, qual, loc, post;
    int age, cat, exp, leaves_allocated;
    long long mob;
    double salary;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter date of birth (dd/mm/yyyy): ";
    cin >> dob;
    cout << "Enter gender: ";
    cin >> sex;
    cout << "Enter address: ";
    cin >> address;
    cout << "Enter category (1-Doctor, 2-Patient, 3-Nurse, 4-Driver, 5-Non-Medical Staff): ";
    cin >> cat;
    cout << "Enter mobile number: ";
    cin >> mob;
    cout << "Enter department: ";
    cin >> dept;
    cout << "Enter date of joining (dd/mm/yyyy): ";
    cin >> doj;
    cout << "Enter experience in years: ";
    cin >> exp;
    cout << "Enter qualifications: ";
    cin >> qual;
    cout << "Enter location: ";
    cin >> loc;
    cout << "Enter post: ";
    cin >> post;
    cout << "Enter salary: ";
    cin >> salary;
    cout << "Enter leaves allocated: ";
    cin >> leaves_allocated;
    vector<string> schedule;
    string day;
    cout << "Enter work schedule (enter 'done' to stop): ";
    while (true) {
        cin >> day;
        if (day == "done") break;
        schedule.push_back(day);
    }
    vector<string> benefits = {"Health Care"};
    Permanent p(name, age, dob, sex, address, cat, mob, dept, doj, exp, qual, loc, post, schedule, benefits, salary, leaves_allocated);
    permanentStaff.push_back(p);
    cout << "Permanent staff added successfully." << endl;
}

// Function to add adhoc staff
void addAdhocStaff(vector<Adhoc>& adhocStaff) {
    string name, dob, sex, address, dept, doj, qual, loc, post;
    int age, cat, exp, contract_duration;
    long long mob;
    double hourly_rate, base_salary;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter date of birth (dd/mm/yyyy): ";
    cin >> dob;
    cout << "Enter gender: ";
    cin >> sex;
    cout << "Enter address: ";
    cin >> address;
    cout << "Enter category (1-Doctor, 2-Patient, 3-Nurse, 4-Driver, 5-Non-Medical Staff): ";
    cin >> cat;
    cout << "Enter mobile number: ";
    cin >> mob;
    cout << "Enter department: ";
    cin >> dept;
    cout << "Enter date of joining (dd/mm/yyyy): ";
    cin >> doj;
    cout << "Enter experience in years: ";
    cin >> exp;
    cout << "Enter qualifications: ";
    cin >> qual;
    cout << "Enter location: ";
    cin >> loc;
    cout << "Enter post: ";
    cin >> post;
    cout << "Enter hourly rate: ";
    cin >> hourly_rate;
    cout << "Enter base salary: ";
    cin >> base_salary;
    cout << "Enter contract duration (in months): ";
    cin >> contract_duration;
    vector<string> schedule;
    string day;
    cout << "Enter work schedule (enter 'done' to stop): ";
    while (true) {
        cin >> day;
        if (day == "done") break;
        schedule.push_back(day);
    }
    vector<string> benefits = {"Health Care"};
    Adhoc a(name, age, dob, sex, address, cat, mob, dept, doj, exp, qual, loc, post, schedule, benefits, hourly_rate, base_salary, contract_duration);
    adhocStaff.push_back(a);
    cout << "Adhoc staff added successfully." << endl;
}

// Main function
int main() {
    vector<Permanent> permanentStaff;
    vector<Adhoc> adhocStaff;
    vector<Patient> patients;
    vector<Room> rooms;
    RoomManager roomManager;
    

    // Add some rooms to the hospital
    rooms.push_back(Room(1,"Single", 1));
    rooms.push_back(Room(2,"Double", 2));
    rooms.push_back(Room(3,"General", 15));
    rooms.push_back(Room(4,"Vip",1));
    rooms.push_back(Room(5,"ICU",1));
    rooms.push_back(Room(6,"Icu",1));

    patients.push_back(Patient("Alice Smith", 30));
    patients.back().medical_history = "Diabetes, Hypertension";

    patients.push_back(Patient("Bob Johnson", 45));
    patients.back().medical_history = "Asthma, Allergies";

    patients.push_back(Patient("Charlie Brown", 50));
    patients.back().medical_history = "Heart Disease";

    patients.push_back(Patient("Diana Prince", 28));
    patients.back().medical_history = "No known allergies";

    patients.push_back(Patient("Ethan Hunt", 35));
    patients.back().medical_history = "Previous surgery on knee";

    
    permanentStaff.push_back(Permanent("Dr. John Doe", 40, "01/01/1983", "Male", "123 Main St", 1, 1234567890, "Cardiology", "01/01/2010", 15, "MD", "City Hospital", "Senior Cardiologist", {"Mon", "Tue", "Wed", "Thu", "Fri"}, {"Health Care"}, 100000, 30));
    permanentStaff.push_back(Permanent("Nurse Mary Jane", 35, "02/02/1988", "Female", "456 Elm St", 3, 9876543210, "Emergency", "01/02/2015", 10, "BSN", "City Hospital", "Head Nurse", {"Mon", "Tue", "Wed", "Thu", "Fri"}, {"Health Care"}, 60000, 20));
    adhocStaff.push_back(Adhoc("Dr. Bruce Wayne", 42, "03/03/1981", "Male", "789 Oak St", 1, 2345678901, "Pediatrics", "01/03/2020", 12, "MD", "City Hospital", "Pediatrician", {"Sat", "Sun"}, {"Health Care"}, 150, 3000, 6));
    adhocStaff.push_back(Adhoc("Nurse Selina Kyle", 30, "04/04/1993", "Female", "321 Pine St", 3, 3456789012, "Pediatrics", "01/04/2021", 5, "ADN", "City Hospital", "Nurse", {"Sat", "Sun"}, {"Health Care"}, 100, 2000, 12));


    int choice;
while (true) {
    cout << "\nMenu:\n";
    cout << "1. Register Patient\n";
    cout << "2. Add Medical History\n";
    cout << "3. Assign Room to Patient\n";
    cout << "4. Display Patients\n";
    cout << "5. Display Rooms\n";
    cout << "6. Add Permanent Staff\n";
    cout << "7. Add Adhoc Staff\n";
    cout << "8. View Permanent Staff\n";
    cout << "9. View Adhoc Staff\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            string name;
            int age;
            cout << "Enter patient's name: ";
            cin >> name;
            cout << "Enter patient's age: ";
            cin >> age;
            patients.push_back(Patient(name, age));
            cout << "Patient registered successfully.\n";
            break;
        }
        case 2: {
            string name, history;
            cout << "Enter patient's name: ";
            cin >> name;
            cout << "Enter medical history: ";
            cin >> history;
            for (auto& p : patients) {
                if (p.name == name) {
                    p.medical_history = history;
                    cout << "Medical history added.\n";
                    break;
                }
            }
            break;
        }
        case 3: {
            string name;
            int room_number;
            cout << "Enter patient's name: ";
            cin >> name;
            cout << "Enter room number: ";
            cin >> room_number;

            for (auto& p : patients) {
                if (p.name == name) {
                    if (roomManager.assignRoomToPatient(room_number, p)) {
                        cout << "Room assigned to patient.\n";
                    } else {
                        cout << "Room is not available.\n";
                    }
                    break;
                }
            }
            break;
        }
        case 4: {
            for (const auto& p : patients) {
                p.display();
            }
            break;
        }
        case 5: {
            for (const auto& room : rooms) {
                room.display();
                cout << "--------------------------------------------" << endl;
            }
            break;
        }
        case 6: {
            addPermanentStaff(permanentStaff);
            break;
        }
        case 7: {
            addAdhocStaff(adhocStaff);
            break;
        }
        case 8:
            for (int i = 0; i < permanentStaff.size(); i++) {
                permanentStaff[i].display();
                cout << endl;
            }
            break;
        case 9:
            for (int i = 0; i < adhocStaff.size(); i++) {
                adhocStaff[i].display();
                cout << endl;
            }
            break;
        case 10:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}

return 0;
}
