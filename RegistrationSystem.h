#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Student.h"

struct StudentNode
{
    StudentNode* next;
    StudentNode* prev;
    Student* self;
};

class RegistrationSystem
{


public:
    RegistrationSystem();
    ~RegistrationSystem();
    void addStudent( const int studentId, const string firstName, const string lastName );
    void deleteStudent( const int studentId );
    void addCourse( const int studentId, const int courseId, const string courseName );
    void withdrawCourse( const int studentId, const int courseId );
    void cancelCourse( const int courseId );
    void showStudent( const int studentId );
    void showCourse( const int courseId );
    void showAllStudents();
    StudentNode* getStudent( const int studentId );

private:
    StudentNode* studentHead;
    int numStudents;
};

#endif
