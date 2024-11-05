	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList(): head(nullptr), tail(nullptr), size(0) {}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return size;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* newNode = new Node(s);
		newNode -> next = head;
		head = newNode;
		if (tail == nullptr){
			tail = head;
		}
		size++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node* newNode = new Node(s);
		if(tail != nullptr){
			tail->next = newNode;
		}
		tail = newNode;
		if (head == nullptr){
			head = tail;
		}
		size++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		Node* current = head;
		while (current != nullptr) {
			cout << current->student.getName() << endl;
			current = current->next;
			}
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if (head == nullptr) { 
			cout << "Error: List is empty." << endl;
			return;
		}
		if (head == tail) { 
			delete head;
			head = tail = nullptr;
		} else {
			Node* current = head;
			while (current->next != tail) {
				current = current->next;
			}
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    size--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if (head == nullptr) { 
        cout << "Error: List is empty." << endl;
        return;
		}
		 Node* temp = head;
		 head = head->next;
		 if (head == nullptr) { 
			tail = nullptr;
		}
		delete temp;
		size--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.

	void StudentList::insertStudent(Student s, int index) {
    if (index <= 0) {
        addFront(s);
    } else if (index >= size) {
        addBack(s);
    } else {
        Node* newNode = new Node(s);
        Node* current = head;
        for (int i = 1; i < index; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
    	Node* current = head;
    	while (current != nullptr) {
        	if (current->student.getId() == idNum) {
            	return current->student;
        	}
        	current = current->next;
    	}
    cout << "Student not found. Returning a dummy student." << endl;
    return Student();
}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		if (head == nullptr) return;
    	if (head->student.getId() == idNum) {
			popFront();
			return;
    	}
		Node* current = head;
    	while (current->next != nullptr && current->next->student.getId() != idNum) {
        	current = current->next;
  		}
    	if (current->next != nullptr) {
        	Node* temp = current->next;
        	current->next = temp->next;
        	if (temp == tail) {
            	tail = current;
        	}
        	delete temp;
        	size--;
    } else {
        cout << "Student not found." << endl;
    }
}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		 Node* current = head;
    	while (current != nullptr) {
    	    if (current->student.getId() == idNum) {
        	    current->student.setGPA(newGPA); // Assuming Student has a setGPA method
            	return;
       		 }
        	current = current->next;
    	}
    	cout << "Student not found." <<endl;
}
	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList& otherList) {
		if (otherList.head == nullptr) return;
		if (tail != nullptr) {
        	tail->next = otherList.head;
    	} else {
        	head = otherList.head;
    	}
    	tail = otherList.tail;
    	size += otherList.size;
    	otherList.head = otherList.tail = nullptr;
    	otherList.size = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
    	StudentList honorList;
    	Node* current = head;
    	while (current != nullptr) {
        	if (current->student.getGPA() >= minGPA) {
            	honorList.addBack(current->student);
        	}
        	current = current->next;
    	}
    	return honorList;
	}