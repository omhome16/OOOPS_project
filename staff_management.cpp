#include <iostream>
#include <vector>
#include <string>
using namespace std;

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
    virtual double calculateSalary(int leave_taken = 0, int hours_worked = 0) = 0; // Pure virtual function for salary calculation
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
    vector<string> work_schedule;
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
    double calculateSalary(int leave_taken, int hours_worked = 0) override {
        double salary_after_leave_deduction = base_salary;
        if (leave_taken > leaves_allocated) {
            salary_after_leave_deduction -= (leave_taken - leaves_allocated) * (base_salary / 30);  // Assuming 30 days in a month
        }
        return salary_after_leave_deduction;
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
    double calculateSalary(int leave_taken = 0, int hours_worked = 0) override {
        return base_salary + (hourly_rate * hours_worked);
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
    // Work schedule and benefits input
    vector<string> schedule;
    string day;
    cout << "Enter work schedule (enter 'done' to stop): ";
    while (true) {
        cin >> day;
        if (day == "done") break;
        schedule.push_back(day);
    }
    // Benefits allocation for Permanent
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
    cout << "Enter contract duration in months: ";
    cin >> contract_duration;
    // Work schedule and benefits input
    vector<string> schedule;
    string day;
    cout << "Enter work schedule (enter 'done' to stop): ";
    while (true) {
        cin >> day;
        if (day == "done") break;
        schedule.push_back(day);
    }
    // Benefits allocation for Adhoc
    vector<string> benefits = {"Health Care"};
    Adhoc a(name, age, dob, sex, address, cat, mob, dept, doj, exp, qual, loc, post, schedule, benefits, hourly_rate, base_salary, contract_duration);
    adhocStaff.push_back(a);
    cout << "Adhoc staff added successfully." << endl;
}

// Function to calculate salary based on type (Permanent/Adhoc)
void  calculateSalaryFunction( vector<Permanent>& permanentStaff,  vector<Adhoc>& adhocStaff) {
    int staff_type;
    cout << "Select Staff Type:\n";
    cout << "1. Permanent\n";
    cout << "2. Adhoc\n";
    cout << "Enter your choice: ";
    cin >> staff_type;
    if (staff_type == 1) {
        int staff_index, leave_taken;
        cout << "Enter staff index for permanent staff: ";
        cin >> staff_index;
        cout << "Enter leave taken for salary calculation: ";
        cin >> leave_taken;
        double salary = permanentStaff[staff_index].calculateSalary(leave_taken);
        cout << "Permanent staff salary: " << salary << endl;
    } else if (staff_type == 2) {
        int staff_index, hours_worked;
        cout << "Enter staff index for adhoc staff: ";
        cin >> staff_index;
        cout << "Enter hours worked for salary calculation: ";
        cin >> hours_worked;
        double salary = adhocStaff[staff_index].calculateSalary(0, hours_worked);
        cout << "Adhoc staff salary: " << salary << endl;
    } else {
        cout << "Invalid choice.\n";
    }
}

// Main function to drive the application
int main() {
    vector<Permanent> permanentStaff;
    vector<Adhoc> adhocStaff;
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Permanent Staff\n";
        cout << "2. Add Adhoc Staff\n";
        cout << "3. View Permanent Staff\n";
        cout << "4. View Adhoc Staff\n";
        cout << "5. Calculate Salary\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addPermanentStaff(permanentStaff);
                break;
            case 2:
                addAdhocStaff(adhocStaff);
                break;
            case 3:
                for (int i = 0; i < permanentStaff.size(); i++) {
                    permanentStaff[i].display();
                    cout << endl;
                }
                break;
            case 4:
                for (int i = 0; i < adhocStaff.size(); i++) {
                    adhocStaff[i].display();
                    cout << endl;
                }
                break;
            case 5:
                calculateSalaryFunction(permanentStaff, adhocStaff);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 6);
    return 0;
}
