#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>


class StudentInterface {
public:
    virtual std::vector<std::string> viewSchedule() = 0;
};

class FacultyInterface {
public:
    virtual void addEvent(std::string event) = 0;
    virtual void removeEvent(std::string event) = 0;
};

class AdminInterface {
public:
    virtual void addStudent(StudentInterface* student) = 0;
    virtual void removeStudent(StudentInterface* student) = 0;
};


class Schedule {
private:
    std::vector<std::string> events;
public:
    void addEvent(std::string event) {
        events.push_back(event);
    }
    void removeEvent(std::string event) {
        events.erase(std::remove(events.begin(), events.end(), event), events.end());
    }
    std::vector<std::string> getEvents() {
        return events;
    }
};


class Student : public StudentInterface {
private:
    std::string name;
    Schedule* schedule;
public:
    Student(std::string name, Schedule* schedule) : name(name), schedule(schedule) {}
    std::vector<std::string> viewSchedule() override {
        return schedule->getEvents();
    }
};

class Faculty : public FacultyInterface {
private:
    std::string name;
    Schedule* schedule;
public:
    Faculty(std::string name, Schedule* schedule) : name(name), schedule(schedule) {}
    void addEvent(std::string event) override {
        schedule->addEvent(event);
    }
    void removeEvent(std::string event) override {
        schedule->removeEvent(event);
    }
};

class Admin : public AdminInterface {
private:
    std::vector<StudentInterface*> students;
public:
    void addStudent(StudentInterface* student) override {
        students.push_back(student);
    }
    void removeStudent(StudentInterface* student) override {
        students.erase(std::remove(students.begin(), students.end(), student), students.end());
    }
};


class University {
private:
    Schedule* schedule;
    std::vector<Student*> students;
    std::vector<Faculty*> faculty;
    Admin* admin;
public:
    University() : schedule(new Schedule()), admin(new Admin()) {}
    void addStudent(std::string name) {
        Student* student = new Student(name, schedule);
        students.push_back(student);
        admin->addStudent(student);
    }
    void removeStudent(std::string name) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i]->getName() == name) {
                admin->removeStudent(students[i]);
                delete students[i];
                students.erase(students.begin() + i);
                break;
            }
        }
    }
    void addFaculty(std::string name) {
        Faculty* faculty_member = new Faculty(name, schedule);
        faculty.push_back(faculty_member);
    }
    void removeFaculty(std::string name) {
        for (int i = 0; i < faculty.size(); i++) {
            if (faculty[i]->getName() == name) {
                delete faculty[i];
                faculty.erase(faculty.begin() + i);
                break;
            }
        }
    }
    void addEvent(std::string event, std::string name) {
        for (int i= 0; i < faculty.size(); i++) {
            if (faculty[i]->getName() == name) {
                faculty[i]->addEvent(event);
                break;
            }
        }
    }
    void removeEvent(std::string event, std::string name) {
        for (int i = 0; i < faculty.size(); i++) {
            if (faculty[i]->getName() == name) {
                faculty[i]->removeEvent(event);
                break;
            }
        }
    }
    std::vectorstd::string viewSchedule(std::string name) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i]->getName() == name) {
                return students[i]->viewSchedule();
            }
        }
        for (int i = 0; i < faculty.size(); i++) {
            if (faculty[i]->getName() == name) {
                return faculty[i]->viewSchedule();
            }
        }
        return {};
    }
};

int main() {
    University university;
    university.addStudent("John Doe");
    university.addStudent("Jane Smith");
    university.addFaculty("Professor Johnson");

    university.addEvent("Math class", "Professor Johnson");
    university.addEvent("History class", "Professor Johnson");

    std::vector<std::string> john_schedule = university.viewSchedule("John Doe");
    std::cout << "John's schedule: ";
    for (auto& event : john_schedule) {
        std::cout << event << ", ";
    }
    std::cout << std::endl;

    university.removeStudent("Jane Smith");
    university.removeFaculty("Professor Johnson");

    return 0;
}
    
