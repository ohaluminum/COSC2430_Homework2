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

    //Linked list size
    int size;

public:
    //Constructor
    problemList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    //Accessor
    problem* getHead()
    {
        return head;
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

        //Increment the list size
        size++;
    }

    //Create a function to check if the id is repeated
    bool isRepeated(int id)
    {
        problem* temp = head;
        while (temp != nullptr)
        {
            if (temp->id == id)
            {
                return true;
            }
           
            temp = temp->next;
        }

        return false;
    }

    void addProblem(int location, int id, string name, string difficulty)
    {
        //Check if the problem id is repeated
        if (isRepeated(id) == true)
        {
            return;
        }
        
        //1.Create a temperary problem
        problem* temp = new problem;

        //2.Fill the problem information
        temp->id = id;
        temp->name = name;
        temp->difficulty = difficulty;

        //3.Update the pointer
        //If the index is negative, add the problem at the begining of the list
        if (location <= 0)
        {
            temp->next = head;
            head = temp;
        }
        //If the index is greater than list size, add it at the end of the list
        else if (location >= size)
        {
            temp->next = nullptr;
            tail->next = temp;
            tail = temp;
        }
        //The index is in the right range
        else
        {
            problem* prev = new problem;
            prev = head;

            for (int i = 0; i < location - 1; i++)
            {
                prev = prev->next;
            }

            temp->next = prev->next;
            prev->next = temp;
        }

        //Increment the list size
        size++;
    }

    void removeProblem()
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
    istringstream inSS;

    //Open input file
    inFS.open(input);

    //Check if the input is open
    if (!inFS.is_open())
    {
        cout << "Could not open input file." << endl;
        return 1;
    }

    int id;
    string id_str;
    string name;
    string difficulty;
    string line;
    string bin;

    //Create a probelm linked list
    problemList QList;

    //Read the input file line by line
    while (getline(inFS, line))
    {
        //Check if the line is empty (if so continue to read next line)
        if (line.empty())
        {
            continue;
        }

        //Clear input string stream
        inSS.clear();

        //Using input string stream to read problem line
        inSS.str(line);

        //Read useless information
        getline(inSS, bin, ':');

        //Read problem ID
        getline(inSS, id_str, ',');
        id = stoi(id_str);

        //Read useless information
        getline(inSS, bin, ':');

        //Read problem name
        getline(inSS, name, ',');

        //Read useless information
        getline(inSS, bin, ':');

        //Read problem difficulty
        getline(inSS, difficulty);

        QList.inputProblem(id, name, difficulty);
    }

    //Close input file
    inFS.close();

    //Create variable for parsing command file
    string condition;
    int location;
    string location_str;

    //Open command file
    inFS.open(command);

    //Check if the command is open
    if (!inFS.is_open())
    {
        cout << "Could not open input file." << endl;
        return 1;
    }

    //Read command file line by line
    while (getline(inFS, line))
    {
        //Check if the line is empty (if so continue to read next line)
        if (line.empty())
        {
            continue;
        }

        //Clear input string stream
        inSS.clear();

        //Using input string stream to read problem line
        inSS.str(line);

        //Read the condition: add/remove/sort
        getline(inSS, condition, ' ');

        if (condition == "add")
        {
            //Read useless information
            getline(inSS, bin, ':');

            //Read insert location
            getline(inSS, location_str, ' ');
            location = stoi(location_str);

            //Read useless information
            getline(inSS, bin, ':');

            //Read problem ID
            getline(inSS, id_str, ',');
            id = stoi(id_str);

            //Read useless information
            getline(inSS, bin, ':');

            //Read problem name
            getline(inSS, name, ',');

            //Read useless information
            getline(inSS, bin, ':');

            //Read problem difficulty
            getline(inSS, difficulty);

            //Add to the problem list
            QList.addProblem(location, id, name, difficulty);
        }
        else if (condition == "remove")
        {

        }
        else if (condition == "sort")
        {

        }
        else
        {
            cout << "Invail condition." << endl;
        }




    }



    //add pos:2 problem_id:440445, problem_name:Unknown, difficulty:Hard




    //Test
    problem* temp = QList.getHead();
    while (temp != nullptr)
    {
        cout << temp->id << temp->name << temp->difficulty << endl;
        temp = temp->next;
    }

























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
