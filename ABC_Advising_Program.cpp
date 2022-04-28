//============================================================================
// Name        : ABC_Advising_Program.cpp
// Author      : Andreas Galatis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <string>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// define a structure to hold course information
struct Course {
    string courseNum; // unique identifier
    string title;
    string preReqOne, preReqTwo;

};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
    	left = nullptr;
    	right = nullptr;
    }

    // initialize with a given course
    Node(Course aCourse) : Node() {
    	this->course = aCourse;
    }

};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    void RemoveSubTree(Node* node);
    Node* removeNode(Node* node, string courseNum);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();

    void Insert(Course course);
    void Remove(string courseNum);
    Course Search(string courseNum);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //initialize housekeeping variables
    //root is equal to nullptr
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
	RemoveSubTree(root);
}

void BinarySearchTree::RemoveSubTree(Node* node) {
	if (node != nullptr) {
		if(node->left != nullptr) {
			RemoveSubTree(node->left);
		}
		if(node->right != nullptr) {
			RemoveSubTree(node->right);
		}
		delete node;
	}
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root
	this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
	this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
	this->preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equal to null ptr
	if (root == nullptr) {
		// root is equal to new node course
		root = new Node(course);
	}
    // else
	else {
		// add Node root and course
		this->addNode(root, course);
	}

}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseNum) {
	// remove node root courseNum
	this->removeNode(root, courseNum);

}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNum) {
    // set current node equal to root
	Node* current = root;

    // keep looping downwards until bottom reached or matching courseNum found
	while (current != nullptr) {
		// if match found, return current bid
		if (current->course.courseNum.compare(courseNum) == 0) {
			return current->course;
		}
		// if course is smaller than current node then traverse left
		if (courseNum.compare(current->course.courseNum) < 0) {
			current = current->left;
		}
		// else larger so traverse right
		else {
			current = current->right;
		}
	}

    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
	if (node->course.courseNum.compare(course.courseNum) > 0) {
		// if no left node
		if (node->left == nullptr) {
			// this node becomes left
			node->left = new Node(course);
		}
		else{
			// else recurse down the left node
			this->addNode(node->left, course);
		}
	}
    // else
	else{
		// if no right node
		if (node->right == nullptr) {
			// this node becomes right
			node->right = new Node(course);
		}
		else{
			// else recurse down the right node
			this->addNode(node->right, course);
		}

	}
}

Node* BinarySearchTree::removeNode(Node* node, string courseNum) {
	// if this node is null then return  (avoid crashing)
	if (node == nullptr) {
		return node;
	}
	// recurse down left subtree
	if (courseNum.compare(node->course.courseNum) < 0) {
		node->left = removeNode(node->left, courseNum);
	}
	else if (courseNum.compare(node->course.courseNum) > 0){
		node->right = removeNode(node->right, courseNum);
	}
	else {
		// no children this is a leaf node
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
		}
		// one child to the left
		else if (node->left != nullptr && node->right == nullptr) {
			Node* temp = node;
			node = node->left;
			delete temp;
		}
		// one child to the right
		else if (node->right != nullptr && node->right == nullptr) {
			Node* temp = node;
			node = node->right;
			delete temp;
		}
		// two children
		else {
			Node* temp = node->right;
			while (temp->left != nullptr) {
				temp = temp->left;
			}
			node->course = temp->course;
			node->right = removeNode(node->right, temp->course.courseNum);
		}
	}
	return node;
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
	if (node != nullptr) {
		//InOrder left
		inOrder(node->left);
		//output courseNum and title
		cout << node->course.courseNum << ", "
		     << node->course.title << endl;
		//InOder right
		inOrder(node->right);
	}
}

void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
	if (node != nullptr) {
		//postOrder left
		postOrder(node->left);
		//postOrder right
		postOrder(node->right);
		//output courseNum and title
		cout << node->course.courseNum << ": "
			 << node->course.title << endl;
	}

}

void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
	if (node != nullptr) {
		//output courseNum and title
		cout << node->course.courseNum << ": "
			 << node->course.title << endl;
		//preOrder left
		preOrder(node->left);
		//preOrder right
		preOrder(node->right);
	}

}



/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
	cout << course.courseNum << ", " << course.title <<  endl;
	if (!course.preReqTwo.empty()) {
		cout << "Prerequisites: " << course.preReqOne << ", " << course.preReqTwo << endl;
	}else if (!course.preReqOne.empty()){
		cout << "Prerequisites: " << course.preReqOne << endl;
	}
    cout << endl;

    return;
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            course.courseNum = file[i][0];
            course.title = file[i][1];
            course.preReqOne = file[i][2];
            course.preReqTwo = file[i][3];

            // push this course to the end
            bst->Insert(course);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}



/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "CSCI100";
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    default:
        csvPath = "/Users/andreasgalatis/eclipse-workspace/ABC_Advising_Program/Debug/src/ABCU_Advising_Program_Input.csv";
        courseKey = "CSCI100";
    }


    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;

    Course course;

    cout << "Welcome to the course planner \n" << endl;

    int choice = 0;
    while (choice != 4) {
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  4. Exit \n" << endl;
        cout << "What would you like to do? \n";
        cin >> choice;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Complete the method call to load the courses
            loadCourses(csvPath, bst);

            break;

        case 2:
        	cout << "Here is a sample schedule: \n";
        	cout << endl;
            bst->InOrder();
            cout << endl;
            break;

        case 3:

            cout << "What course do you want to know about? ";
            cin >> courseKey;
            std::for_each(courseKey.begin(), courseKey.end(), [](char & c){
            c = ::toupper(c);
            });


            course = bst->Search(courseKey);

            if (!course.courseNum.empty()) {
                displayCourse(course);
            } else {
            	cout << "Course Number " << courseKey << " not found." << endl;
            }

            break;

        case 4:
        	break;

        default:
        	cout << "That is not a valid option. \n" << endl;

        	break;
        }
    }

    cout << "Thank you for using the course planner!" << endl;

	return 0;
}
