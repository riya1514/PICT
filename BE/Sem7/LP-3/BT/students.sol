// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {
    // Structure to hold student information
    struct Student {
        uint id;
        string name;
        uint age;
    }

    // Dynamic array to store multiple students
    Student[] public students;

    // Function to add a new student
    function addStudent(uint _id, string memory _name, uint _age) public {
        students.push(Student(_id, _name, _age));
    }

    // Function to get a student by index
    function getStudentById(uint _id) public view returns (uint, string memory, uint) {
        for (uint i = 0; i < students.length; i++) {
            if (students[i].id == _id) {
                return (students[i].id, students[i].name, students[i].age);
            }
        }
        revert("Student with given ID not found");
    }

    // ✅ Function to delete a student by index
     function deleteStudentById(uint _id) public {
        for (uint i = 0; i < students.length; i++) {
            if (students[i].id == _id) {
                students[i] = students[students.length - 1]; // Move last element to this index
                students.pop(); // Remove last
                return;
            }
        }
        revert("Student with given ID not found");
    }
    
    // ✅ Function to get all students
    function getAllStudents() public view returns (Student[] memory) {
        return students;
    }

    // ✅ Function to edit a student's data
    function editStudentById(uint _id, string memory _name, uint _age) public {
        for (uint i = 0; i < students.length; i++) {
            if (students[i].id == _id) {
                students[i].name = _name;
                students[i].age = _age;
                return;
            }
        }
        revert("Student with given ID not found");
    }

    // Function to get total number of students
    function getStudentCount() public view returns (uint) {
        return students.length;
    }

    // Fallback function - called when no function matches
    fallback() external payable {}

    // Receive function - handles plain Ether transfers
    receive() external payable {}
}