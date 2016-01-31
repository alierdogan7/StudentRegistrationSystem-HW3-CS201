#include <iostream>
#include <string>
using namespace std;

#include "Student.h"

Student::Student(const int id, const string firstName, const string lastName)
{
    this->studentFirstName = firstName;
    this->studentLastName = lastName;
    this->studentId = id;
    courseHead = NULL;
    numCourses = 0;
}

Student::~Student()
{
    Course* cur = courseHead;
    while(cur != NULL)
    {
        Course* tmp = cur;
        cur = cur->next;
        tmp->next = NULL;
        delete tmp;
        tmp = NULL;
    }
}

void Student::addCourse( const int courseId, const string courseName )
{
   if( this->getCourse(courseId) != NULL ) //if course doesnt exist
    {
        cout << "Student " << this->studentId << " is already enrolled in class "<< courseId << endl;
    }
    else
    {
        Course* tmp = new Course;
        tmp->courseId = courseId;
        tmp->courseName = courseName;

        if(this->courseHead == NULL)
        {
            courseHead = tmp;
            courseHead->next = NULL;
        }
        //add it simply to the head since list is unordered
        else
        {
            Course* oldHead = courseHead;
            courseHead = tmp;
            courseHead->next = oldHead;
        }

        this->numCourses++;

        cout << "Course " << courseId << " has been added to student " << this->studentId << endl;
    }
}

/*bool Student::findIfCourseExists( const int courseId )
{
    bool result;

    Course* cur = courseHead;
    while( cur != NULL)
    {
        if(cur->courseId == courseId)
        {
            result = true;
            break;
        }
        cur = cur->next;
    }

    return result;
}*/

void Student::withdrawCourse( const int courseId )
{
    Course* cur = courseHead;
    Course* prev = NULL;
    bool withdrawn = false;

    while(cur != NULL)
    {
        //if it is found and it is the head of the list
        if(cur->courseId == courseId && cur == courseHead && prev == NULL)
        {
            Course* tmp = cur;
            this->courseHead = cur->next;
            tmp->next = NULL;
            delete tmp;
            tmp = NULL;

            withdrawn = true;
            break; //we found it, that's enough, let's get outta here
        }
        //if it's found and it's not the head of the list
        else if (cur->courseId == courseId)
        {
            Course* tmp = cur;
            prev->next = cur->next;
            tmp->next = NULL;
            delete tmp;
            tmp = NULL;

            withdrawn = true;
            break; //we found it, that's enough, let's get outta here
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }

    if(withdrawn)
    {
        this->numCourses--;
        cout << "Student " << this->studentId << " has been withdrawn from course " << courseId << endl;
    }
    else
        cout << "Student " << this->studentId << " isn't enrolled in course " << courseId << endl;

}

void Student::show()
{
    cout << "Student id\tFirst Name\tLast name" << endl;
    cout << this->studentId << "\t" << this->studentFirstName << "\t" << this->studentLastName << endl;
    cout << "\tCourse id\tCourse name" << endl;

    for(Course* cur = this->courseHead; cur != NULL; cur = cur->next)
    {
        cout << "\t" << cur->courseId << "\t" << cur->courseName << endl;
    }
}

Course* Student::getCourse( const int courseId )
{
    Course* cur = courseHead;
    while( cur != NULL)
    {
        if(cur->courseId == courseId)
        {
            break;
        }

        cur = cur->next;
    }

    return cur; //returns NULL if not found
}

void Student::showTabbedRepresentation()
{
    cout << this->studentId << "\t" << this->studentFirstName << "\t" << this->studentLastName << endl;
}

int Student::getStudentId()
{
    return this->studentId;
}
