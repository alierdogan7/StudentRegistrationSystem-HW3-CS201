#ifndef STUDENT_H_
#define STUDENT_H_

struct Course
{
    int courseId;
    string courseName;
    Course* next;
};

class Student
{


public:
    Student(const int id, const string firstName, const string lastName);
    ~Student();
    void addCourse( const int courseId, const string courseName );
    void withdrawCourse( const int courseId );
    //bool findIfCourseExists( const int courseId );
    Course* getCourse( const int courseId );
    void show();
    void showTabbedRepresentation();
    int getStudentId();

private:
    string studentFirstName;
    string studentLastName;
    int studentId;
    Course *courseHead;
    int numCourses;
};

#endif
