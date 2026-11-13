/*
 * Name : Muhammad Rayan Zulfiqar
 * Registration Number : 543021
 * Section             : BScs 15-D

 * DESIGN EXPLANATION
 *  1) Binary Search Tree- stores the student records (unique roll number + name).
 *     Roll number is the key, so add and search discard half of the remaining
 *     records at each step (O(log n) on a balanced tree), duplicates are easy to
 *     detect, and an in-order traversal prints the records sorted by roll number
 *     without any extra sorting. Nodes are allocated dynamically, so there is no
 *     fixed capacity and no "full" condition unlike an array.
 *  2) Stack - the additional feature is Search History. After every
 *     successful search the roll number is pushed. The most recent search is the
 *     one on top, so it is shown/removed first.
 *     Removing a history entry only pops the stack; the student record stays in
 *     the BST.
 *
 * COMPLEXITY (n = number of students, h = height of the BST)
 *  - Add student    : worst case O(n)
 *                     O(log n) on average / balanced tree.
 *  - Search student : worst case O(n) unbalanced tree ; O(log n) on average.
 *  - Display all    : O(n)  - every node is visited once (in-order).
 *  - History push / top / pop : O(1).
 *
 * A linked list is a good alternative to the BST for the student records, but it is slower for searching.
 * Add: inserting at the head takes O(1). However, the program must reject duplicate roll numbers, so it first scans the whole list, and that makes add O(n). Inserting at the tail also costs O(n) unless you keep a tail pointer.
   Search: it must check nodes one by one, so a missing roll number always costs n comparisons. The BST only degrades to O(n) when the roll numbers arrive already sorted.
   Display: the list shows records in the order they were added. To get sorted output you would need a sorted insert  or a separate sort.

 */
#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node
{
    int rollNum;
    string name;
    Node *left;
    Node *right;
    Node(int roll, string name)
    { // constructor for a node
        rollNum = roll;
        this->name = name;
        left = right = NULL;
    }
};

Node *root = NULL;
stack<int> history; // roll numbers of successful searches (top = most recent)

Node *add(Node *root, int RollNo, string name)
{
    if (root == NULL)
    {
        root = new Node(RollNo, name);
    }
    else if (RollNo < root->rollNum)
    {
        root->left = add(root->left, RollNo, name);
    }
    else if (RollNo > root->rollNum)
    {
        root->right = add(root->right, RollNo, name);
    }
    return root;
}

// Returns the node with the given roll number, or NULL if not present.
Node *findStudent(Node *root, int rollNo)
{
    if (root == NULL || root->rollNum == rollNo)
    {
        return root;
    }
    if (rollNo < root->rollNum)
    {
        return findStudent(root->left, rollNo);
    }
    return findStudent(root->right, rollNo);
}

// Searches by roll number, prints the result and records successful searches.
void search(Node *root, int val)
{
    Node *found = findStudent(root, val);
    if (found == NULL)
    {
        cout << "There is no record" << endl;
        return;
    }
    cout << "Found" << endl;
    cout << "Roll No : " << found->rollNum << endl;
    cout << "Name : " << found->name << endl;
    history.push(found->rollNum);
}

// In-order traversal
void display(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    display(root->left);
    cout << "Roll Number : " << root->rollNum << endl;
    cout << "Name : " << root->name << endl;
    display(root->right);
}

void destroyTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

void History()
{
    if (history.empty())
    {
        cout << "Search history is empty." << endl;
        return;
    }

    int option;
    cout << "1. Display most recent search\n2. Remove most recent search from history\n";
    cout << "Enter option: ";
    cin >> option;

    if (option == 1)
    {
        cout << "Most recent searched roll number: " << history.top() << endl;
    }
    else if (option == 2)
    {
        cout << "Removed roll number " << history.top() << " from search history." << endl;
        cout << "The student record was not deleted." << endl;
        history.pop();
    }
    else
    {
        cout << "Invalid history option." << endl;
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\nStudent Menu" << endl;
        cout << "1. Add the student" << endl;
        cout << "2. Search the student" << endl;
        cout << "3. Display all students" << endl;
        cout << "4. Search History" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int roll;
            string name;
            cout << "Enter Roll Number : ";
            cin >> roll;
            if (findStudent(root, roll) != NULL)
            {
                cout << "A student with that roll number already exists." << endl;
                break;
            }
            cout << "Enter the name : ";
            cin.ignore();
            getline(cin, name);
            root = add(root, roll, name);
            cout << "Student added." << endl;
            break;
        }
        case 2:
        {
            int val;
            cout << "Enter the Roll Number : ";
            cin >> val;
            search(root, val);
            break;
        }
        case 3:
        {
            if (root == NULL)
            {
                cout << "There are no student records." << endl;
            }
            else
            {
                display(root);
            }
            break;
        }
        case 4:
        {
            History();
            break;
        }
        case 5:
        {
            cout << "Exiting menu." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
        }
    } while (choice != 5);

    destroyTree(root); // release all dynamically allocated memory
    root = NULL;
    return 0;
}