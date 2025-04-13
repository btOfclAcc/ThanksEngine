#include <ThanksEngine/Inc/ThanksEngine.h>

using namespace ThanksEngine;
using namespace ThanksEngine::Core;

static int sUniqueId = 0;
class Student
{
public:
    Student()
    {
        mId = ++sUniqueId;
        mName = "NoName" + std::to_string(mId);
    }

    Student(const std::string& name)
        : mName(name)
        , mId(++sUniqueId)
    {
    }

    void Log()
    {
        LOG("Name: %s - Id: %d", mName.c_str(), mId);
    }

private:
    int mId = 0;
    std::string mName;
};

static int sTeacherId = 0;
class Teacher
{
public:
    Teacher()
    {
        mId = ++sTeacherId;
        mName = "NoName" + std::to_string(mId);
    }

    Teacher(const std::string& name)
        : mName(name)
        , mId(++sTeacherId)
    {
    }

    void Log()
    {
        LOG("Name: %s - Id: %d", mName.c_str(), mId);
    }

private:
    int mId = 0;
    std::string mName;
};

static int sStaffId = 0;
class Staff
{
public:
    Staff()
    {
        mId = ++sStaffId;
        mName = "NoName" + std::to_string(mId);
    }

    Staff(const std::string& name)
        : mName(name)
        , mId(++sStaffId)
    {
    }

    void Log()
    {
        LOG("Name: %s - Id: %d", mName.c_str(), mId);
    }

private:
    int mId = 0;
    std::string mName;
};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);
    std::vector<Student*> students;

#pragma region student
    // test new
    for (uint32_t i = 0; i < 100; ++i)
    {
        Student* student = studentPool.New();
        student->Log();
        students.push_back(student);
    }

    // test deletion
    for (uint32_t i = 0; i < 60; ++i)
    {
        Student* student = students.back();
        studentPool.Delete(student);
        students.pop_back();
    }

    // test adding more
    for (uint32_t i = 0; i < 55; ++i)
    {
        Student* student = studentPool.New("New_Student" + std::to_string(i));
        student->Log();
        students.push_back(student);
    }

    // clear all
    for (Student* student : students)
    {
        studentPool.Delete(student);
    }
    students.clear();
#pragma endregion

#pragma region teacher
    TypedAllocator teacherPool = TypedAllocator<Teacher>("TeacherPool", 10);
    std::vector<Teacher*> teachers;

    for (uint32_t i = 0; i < 3; ++i)
    {
        Teacher* teacher = teacherPool.New();
        teacher->Log();
        teachers.push_back(teacher);
    }

    for (uint32_t i = 0; i < 1; ++i)
    {
        if (teachers.empty())
        {
            break;
        }

        Teacher* teacher = teachers.back();
        teacherPool.Delete(teacher);
        teachers.pop_back();
    }

    for (uint32_t i = 0; i < 100; ++i)
    {
        Teacher* teacher = teacherPool.New("New_Teacher" + std::to_string(i));
        if (teacher == nullptr)
        {
            break;
        }
        teacher->Log();
        teachers.push_back(teacher);
    }

    for (Teacher* teacher : teachers)
    {
        teacherPool.Delete(teacher);
    }
    teachers.clear();

#pragma endregion


#pragma region staff
    TypedAllocator staffPool = TypedAllocator<Staff>("StaffPool", 25);
    std::vector<Staff*> staffs;

    for (uint32_t i = 0; i < 20; ++i)
    {
        Staff* staff = staffPool.New();
        staff->Log();
        staffs.push_back(staff);
    }

    for (uint32_t i = 0; i < 15; ++i)
    {
        if (staffs.empty())
        {
            break;
        }

        Staff* staff = staffs.back();
        staffPool.Delete(staff);
        staffs.pop_back();
    }

    for (uint32_t i = 0; i < 5; ++i)
    {
        Staff* staff = staffPool.New("New_Staff" + std::to_string(i));
        if (staff == nullptr)
        {
            break;
        }
        staff->Log();
        staffs.push_back(staff);
    }

    for (Staff* staff : staffs)
    {
        staffPool.Delete(staff);
    }
    staffs.clear();

#pragma endregion

    return(0);
}