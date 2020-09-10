#include <iostream>
#include <sstream>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

//Create a problem node
struct problem
{
    //Basic information
    int id;
    string name;
    string difficulty;

    //Link to the next problem
    problem* next;
};

//Create a problem link
class problemList
{
private:
    //Head pointer points to the first problem
    problem* head;

    //Tail pointer points to the last problem
    problem* tail;

public:
    //Constructor
    problemList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void inputProblem(int id, string name, string difficulty)
    {
        //1.Create a temperary problem
        problem* temp = new problem;

        //2.Fill the problem information
        temp->id = id;
        temp->name = name;
        temp->difficulty = difficulty;

        //3.Update the pointer
        temp->next = nullptr;

        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }

    void addProblem(int location, int id, string name, string difficulty)
    {
        //1.Create a temperary problem
        problem* temp = new problem;

        //2.Fill the problem information
        temp->id = id;
        temp->name = name;
        temp->difficulty = difficulty;

        //3.Update the pointer
        //temp->next = head;
        //head = temp;
    }

    void deleteProblem()
    {

    }

    void sortProblem()
    {

    }





};


int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    //string input = am.get("input");
    //string output = am.get("output");
    //string command = am.get("command");

    //Test
    string input = "input21.txt";
    string output = "output21.txt";
    string command = "command21.txt";

    ifstream inFS;
    ofstream outFS;

    inFS.open(input);

    //Check if the input is open
    if (!inFS.is_open())
    {
        cout << "Could not open input file." << endl;
        return 1;
    }

    //Read the input file: problem list


    //Write a new function to create linked list


























}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
