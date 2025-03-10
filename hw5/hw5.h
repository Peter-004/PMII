// Your name here: Opemipo Adebayo Peter
// Your NetID here: opa15
//
// IMPORTANT NOTE:
// In your submission, you are only allowed to make modifications where it is indicated,
// and you must provide your implementation in those designated areas.
// You are not permitted to make changes to the code in any other location.
//
#ifndef HW5B_H
#define HW5B_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <algorithm>

class Course {
public:
    std::string descName;
    std::string courseNum;

    // e.g., PM2 has prerequisite requirement PM1, so the size of this vector will be 1
    // 14:332:322 has two prerequisite requirements, 226 and 345, so the size of this vector will be 2
    std::vector<Course*> prerequisites;

    // this vector will be updated by the createAdjacencyList() function in the CourseGraph class
    // think of this as the adjacency list representation of the course graph
    // e.g., finishing PM1 satisfies one prerequisite for PM2
    // so we can add a directed "edge" from PM1 to PM2
    std::vector<Course*> postrequisites;

    Course(const std::string& courseNum, const std::string& courseName) :
            courseNum(courseNum), descName(courseName) {}

    void addPrerequisite(Course* prerequisite) {
        prerequisites.push_back(prerequisite);
    }
};


class CourseGraph {
public:
    std::unordered_map<std::string, Course*> courseMap;
    // e.g., "14:332:221" -> a pointer to Course("14:332:221", "Principles of Electrical Engineering I")

    // vector to store per-course topologically-sorted list of courses
    std::vector<const Course*> perCourseTopoResult;

    // 2D vector to store per-semester topologically-sorted list of courses
    // e.g., perSemesterTopoResult[0] gives a list of courses that should be taken in the 1st semester
    std::vector<std::vector<const Course*>> perSemesterTopoResult;

    void addCourse(const std::string& courseNum, const std::string& courseName) {
        const auto& pair = courseMap.emplace(courseNum, nullptr); // https://cplusplus.com/reference/unordered_map/unordered_map/emplace/
        if (pair.second) {
            pair.first->second = new Course(courseNum, courseName); // note the "new" keyword
        }
    }

    void addPrerequisite(const std::string& courseNum, const std::string& prerequisiteNum) {
        if ( courseMap.count(courseNum) && courseMap.count(prerequisiteNum) )
            courseMap[courseNum]->addPrerequisite( courseMap[prerequisiteNum] );
        else
            std::cerr << courseNum << " or " << prerequisiteNum  << " does/do not exist" << std::endl;
    }

    ~CourseGraph() {
        for (auto& pair : courseMap)
            delete pair.second; // note the "delete" keyword
    }

    void printTopologicalSortedOrder() {
        std::cout << std::endl;
        std::cout << "Per-Course Topological Sorted Order:" << std::endl;
        for (const Course* course : perCourseTopoResult) {
            std::cout << course->courseNum << " " << course->descName << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Per-Semester Topological Sorted Order:" << std::endl;
        for (int i = 0; i < perSemesterTopoResult.size(); ++i) {
            std::cout << "Semester: " << i+1 << std::endl;
            for (const Course* course : perSemesterTopoResult[i]) {
                std::cout << "  " << course->courseNum << " " << course->descName << std::endl;
            }
        }
    }

    // For each course, its adjacency list should be stored in the class member variable
    // std::vector<Course*> postrequisites of the Course Class
    void createAdjacencyList() {
        // Provide your implementation here
        //
        for (const auto& pair : courseMap) {
            Course* course = pair.second;
            for (Course* prereq : course->prerequisites) {
                prereq->postrequisites.push_back(course);
            }
        }
        // End of your implementation
    }

    // check if the per-course topological sorted order stored in perCourseTopoResult is valid
    // e.g., if a course is selected before the prerequisite requirement, then return false
    bool isValidPerCourseTopologicalSort() {
        // Provide your implementation here
        std::unordered_map<const Course*, int> prereqs;

        for (const auto& pair : courseMap) {
            Course* course = pair.second;
            prereqs[course] = course->prerequisites.size();
        }

        std::unordered_set<const Course*> completed;

        for (const Course* course : perCourseTopoResult) {
            for (const Course* preReq : course->prerequisites) {
                if (completed.find(preReq) == completed.end()) {
                    return false;//not completed
                }
            }
            completed.insert(course);//insert into completed courses
        }

        return true;
        // End of your implementation
    }

    // the per-course sorted results should be stored in the class member variable
    // std::vector<const Course*> perCourseTopoResult of the CourseGraph class
    void perCourseTopologicalSort() {
        // Provide your implementation here
        perCourseTopoResult.clear();
        DFS();//call depthfirstsearch
        std::reverse(perCourseTopoResult.begin(), perCourseTopoResult.end());
        // End of your implementation
    }

    // following the algorithm we discussed in class, perCourseTopologicalSort() calls DFS()
    void DFS() {
        // unordered_set for marking if a course has been visited in DFS()
        std::unordered_set<const Course*> visited;

        // Provide your implementation here

        std::vector<const Course*> courses;
        for (const auto& pair : courseMap) {
            courses.push_back(pair.second);
        }

        // Sort the courses
        std::sort(courses.begin(), courses.end(), [](const Course* a, const Course* b) -> bool {
            return a->courseNum > b->courseNum;//tHIS IS for C++ newer versions
        });

        for (const Course* c : courses) {
            if (visited.find(c) == visited.end()) {
                DFSVisit(c, visited);
            }
        }
        // End of your implementation
    }

    void DFSVisit(const Course* course, std::unordered_set<const Course*>& visited) {
        // Provide your implementation here
        visited.insert(course);

        std::vector<const Course*> sortedPReqs;
        sortedPReqs.reserve(course->postrequisites.size());
        for (Course* prereq : course->postrequisites) {
            sortedPReqs.emplace_back(prereq); // Convdrt Course* to const Course*
        }

        // Sort the pReqs
        std::sort(sortedPReqs.begin(), sortedPReqs.end(),
                  [](const Course* a, const Course* b) -> bool {
                      return a->courseNum > b->courseNum;
                  });

        for (const Course* relative : sortedPReqs) {
            if (visited.find(relative) == visited.end()) {
                DFSVisit(relative, visited);
            }
        }

        perCourseTopoResult.push_back(course);
        // End of your implementation
    }

    // this method creates an ordering for which courses to take in each semester
    // the results should be stored in the class member variable
    // std::vector<std::vector<const Course*>> perSemesterTopoResult of the CourseGraph class
    void perSemesterTopologicalSort() {
        // Provide your implementation here
        perSemesterTopoResult.clear();
        // Calculate in-deg
        std::unordered_map<const Course*, int> inDeg;
        for (const auto& pair : courseMap) {
            const Course* course = pair.second;
            inDeg[course] = course->prerequisites.size();
        }

        std::queue<const Course*> q;
        for (const auto& pair : courseMap) {
            const Course* course = pair.second;
            if (inDeg[course] == 0) {
                q.push(course);
            }
        }
        // Arrange courses by semester
        while (!q.empty()) {
            std::vector<const Course*> semesterCourses;
            int size = q.size();
            std::vector<const Course*> tempCourses;
            for (int i = 0; i < size; ++i) {
                const Course* course = q.front();
                q.pop();
                semesterCourses.push_back(course);
                tempCourses.push_back(course);
            }
            // Sort the semester courses by courseNum in ascending order
            std::sort(semesterCourses.begin(), semesterCourses.end(), [](const Course* a, const Course* b) -> bool {
                return a->courseNum < b->courseNum;
            });
            perSemesterTopoResult.push_back(semesterCourses);
            // Decrement in-degree of postrequisites
            for (const Course* course : tempCourses) {
                for (const Course* relative : course->postrequisites) {
                    inDeg[relative]--;
                    if (inDeg[relative] == 0) {
                        q.push(relative);
                    }
                }
            }
        }
        // End of your implementation
    }
};
#endif
