#include <iostream>
#include <string>
using namespace std;

#include "Student.h"
#include "RegistrationSystem.h"

RegistrationSystem::RegistrationSystem()
{
    this->studentHead = NULL;
    this->numStudents = 0;
}

RegistrationSystem::~RegistrationSystem()
{
    StudentNode* cur = this->studentHead;
    while( cur != NULL )
    {
        StudentNode* tmp = cur;
        cur = cur->next;

        delete tmp->self;
        tmp->next = NULL;
        tmp->prev = NULL;
        tmp->self = NULL;
        delete tmp;
    }
}

void RegistrationSystem::addStudent( const int studentId, const string firstName, const string lastName )
{
    if( this->getStudent(studentId) == NULL)
    {
        StudentNode* cur = studentHead;

        //creating new student node and initiliazing its data with Student pointer
        StudentNode* st = new StudentNode;
        st->self = new Student(studentId, firstName, lastName);

        // if the list is empty make it head
        if( this->studentHead == NULL )
        {
            this->studentHead = st;
            st->prev = NULL;
            st->next = NULL;
        }
        else
        {
            //it exits from loop when the student is bigger or cur is the last item
            while(cur->next != NULL && (cur->self->getStudentId() <= studentId) )
            {
                cur = cur->next;
            }

            //cur is the first student who has a bigger id than given or the last item
            //if cur is gonna be placed on the first index
            if ( cur == studentHead )
            {
                st->next = cur;
                st->prev = NULL;
                cur->prev = st;
                this->studentHead = st;
            }
            //if the list is not empty, and the cur has no item next, and the item is not the head
            else if ( cur->next == NULL)
            {
                cur->next = st;
                st->prev = cur;
                st->next = NULL;
            }
            else
            {
                st->prev = cur->prev;
                st->next = cur;
                cur->prev = st;
                st->prev->next = st;
            }
        }
        this->numStudents++;
        cout << "Student " << st->self->getStudentId() << " has been added " << endl;
    }
    else
    {
        cout << "Student " << studentId << " already exists " << endl;
    }
}

StudentNode* RegistrationSystem::getStudent( const int studentId)
{
    StudentNode* cur = studentHead;
    while( cur != NULL)
    {
        if(cur->self->getStudentId() == studentId)
        {
            break;
        }

        cur = cur->next;
    }

    return cur; //returns NULL if not found
}

void RegistrationSystem::deleteStudent( const int studentId )
{
    StudentNode* st = this->getStudent(studentId);

    //if not found
    if( st == NULL )
    {
        cout << "Student " << studentId << " is not found " << endl;
    }
    //if it is found and it's head and it has an item next
    else
    {
        if( st == studentHead && st->next != NULL)
        {
            st->next->prev = NULL;
            studentHead = st->next;

            st->next = NULL;
            st->prev = NULL;
            delete st->self;
            st->self = NULL;
            delete st;
        }
        // if it's the only item in the list
        else if( st == studentHead && st->next == NULL)
        {
            delete st->self;
            st->self = NULL;
            delete st;
            studentHead = NULL;
        }
        // if it's the last item on the list
        else if( st->next == NULL )
        {
            st->prev->next = NULL;
            st->prev = NULL;
            delete st->self;
            st->self = NULL;
            delete st;
        }
        //if it's between two items
        else
        {
            st->prev->next = st->next;
            st->next->prev = st->prev;
            st->next = NULL;
            st->prev = NULL;
            delete st->self;
            st->self = NULL;
            delete st;
        }

        this->numStudents--;
        cout << "Student " << studentId << " is deleted" << endl;
    }
}

void RegistrationSystem::addCourse( const int studentId, const int courseId, const string courseName )
{
    StudentNode* st = this->getStudent(studentId);

    if ( st == NULL)
    {
        cout << "Student " << studentId << " does not exist " << endl;
    }
    else
    {
        st->self->addCourse(courseId, courseName);
    }
}

void RegistrationSystem::withdrawCourse( const int studentId, const int courseId )
{
    StudentNode* st = this->getStudent(studentId);

    if ( st == NULL)
    {
        cout << "Student " << studentId << " does not exist " << endl;
    }
    else
    {
        st->self->withdrawCourse(courseId);
    }
}

void RegistrationSystem::cancelCourse( const int courseId )
{
    bool isFound = false;
    Course* tmpCourse;
    for(StudentNode* cur = studentHead; cur != NULL; cur = cur->next)
    {
        tmpCourse = cur->self->getCourse(courseId);
        if( tmpCourse != NULL )
        {
            isFound = true;
            break;
        }
    }

    if(isFound)
    {
        for(StudentNode* cur = studentHead; cur != NULL; cur = cur->next)
        {
            cur->self->withdrawCourse(courseId);
        }
    }
    else
        cout << "Course " << courseId << " doesn't exist" << endl;
}

void RegistrationSystem::showStudent( const int studentId )
{
    StudentNode* st = this->getStudent(studentId);
    if( st != NULL)
        st->self->show();
    else
        cout << "Student " << studentId << " does not exist" << endl;
}

void RegistrationSystem::showCourse( const int courseId )
{
    bool isFound = false;
    Course* tmpCourse;
    for(StudentNode* cur = studentHead; cur != NULL; cur = cur->next)
    {
        tmpCourse = cur->self->getCourse(courseId);
        if( tmpCourse != NULL )
        {
            isFound = true;
            break;
        }
    }

    if(isFound)
    {
        cout << "Course id\tCourse name" << endl;
        cout << tmpCourse->courseId << "\t" << tmpCourse->courseName << endl;

        for(StudentNode* cur = studentHead; cur != NULL; cur = cur->next)
        {
            tmpCourse = cur->self->getCourse(courseId);
            if( tmpCourse != NULL )
            {
                cout << "\t";
                cur->self->showTabbedRepresentation();
            }
        }
    }
    else
        cout << "Course " << courseId << " does not exist" << endl;

}

void RegistrationSystem::showAllStudents()
{
    if( numStudents > 0)
    {
        cout << "Student id\tFirst Name\tLast Name" << endl;

        for(StudentNode* cur = studentHead; cur != NULL; cur = cur->next)
        {
            cur->self->showTabbedRepresentation();
        }
    }
    else
        cout << "There is not any student" << endl;
}
