#include <iostream>
#include <sstream>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

//Create a problem node
struct problem
{
    //Basic information
    int id = 0;
    string name = "";
    string difficulty = "";

    //Link to the next problem
    problem* next = nullptr;
};

//Create a problem link
class problemList
{
private:
    //Head pointer points to the first problem
    problem* head;

    //Linked list size
    int size;

public:
    //Constructor
    problemList()
    {
        head = nullptr;
        size = 0;
    }

    //Accessor
    problem* getHead()
    {
        return head;
    }

    int getSize()
    {
        return size;
    }

    //Create a function to check if the problem id is repeated
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

    //Create a function to check if the problem list is empty
    bool isEmpty()
    {
        if (size <= 0)
        {
            return true;
        }

        return false;
    }

    //Create a function to return difficulty level
    int difficultyLevel(string difficulty)
    {
        if (difficulty == "Easy")
        {
            return 1;
        }
        else if (difficulty == "Medium")
        {
            return 2;
        }
        else if (difficulty == "Hard")
        {
            return 3;
        }

        return 0;
    }

    void swapValue(problem* first, problem* second)
    {
        //Create temperary variable
        int tempID;
        string tempName;
        string tempDifficulty;

        //Store current to temp
        tempID = first->id;
        tempName = first->name;
        tempDifficulty = first->difficulty;

        //Swap current and next
        first->id = second->id;
        first->name = second->name;
        first->difficulty = second->difficulty;

        second->id = tempID;
        second->name = tempName;
        second->difficulty = tempDifficulty;

        return;
    }

    //-------------------------------------------------------- ADD FUNCTION -----------------------------------------------

    //Add problem at the beginning of the linked list
    void addAtBeg(int id, string name, string difficulty)
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
        temp->next = head;
        head = temp;

        //Increment the list size
        size++;

        return;
    }

    //Add problem at the middle of the linked list
    void addAtMid(int pos, int id, string name, string difficulty)
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
        problem* prev = new problem;
        prev = head;

        for (int i = 0; i < pos - 1; i++)
        {
            prev = prev->next;
        }

        temp->next = prev->next;
        prev->next = temp;

        //Increment the list size
        size++;

        return;
    }

    //Add problem at the end of the linked list
    void addAtEnd(int id, string name, string difficulty)
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
        temp->next = nullptr;

        if (head == nullptr)
        {
            head = temp;
        }
        else
        {
            problem* prev = new problem;
            prev = head;

            while (prev->next != nullptr)
            {
                prev = prev->next;
            }

            prev->next = temp;
        }
      
        //Increment the list size
        size++;

        return;
    }

    //Add more problem to the problem list
    void addProblem(int pos, int id, string name, string difficulty)
    {
        //If the index is negative, add the problem at the begining of the list
        if (pos <= 0)
        {
            addAtBeg(id, name, difficulty);
        }
        //If the index is greater than list size, add it at the end of the list
        else if (pos >= size)
        {
            addAtEnd(id, name, difficulty);
        }
        //The index is in the right range
        else
        {
            addAtMid(pos, id, name, difficulty);
        }
        return;
    }

    //----------------------------------------------------- REMOVE FUNCTION -----------------------------------------------

    //Remove problem from the beginning of the linked list
    void removeFromBeg()
    {
        //NOTICE: the size will be positive number

        //1.Create a temperary problem
        problem* temp = new problem;

        //2.Update the pointer
        temp = head;

        //If the linked list has only one problem, the list will be empty after removing (head will become nullptr)
        if (size == 1)
        {
            head = nullptr;
        }
        else if (size > 1)
        {
            head = head->next;
        }

        //3.Delete the temperary problem
        delete temp;

        //Decrement the list size
        size--;
    }

    //Remove problem from the middle of the linked list
    void removeFromMid(int pos)
    {
        //NOTICE: the size will be positive number and only if size >= 3 this member function will be called (have middle problem)  

        //1.Create a temperary problem and previous problem
        problem* temp = new problem;
        problem* prev = new problem;

        //Initialize the previous pointer 
        prev = head;

        //Point to the right position (before the remove position)
        for (int i = 0; i < pos - 1; i++)
        {
            prev = prev->next;
        }

        //2.Update the pointer
        temp = prev->next;
        prev->next = temp->next;

        //3.Remove the temperary problem
        delete temp;

        //Decrement the list size
        size--;
    }

    //Remove problem from the end of the linked list
    void removeFromEnd()
    {
        //NOTICE: the size will be positive number

        //1.Create a temperary problem
        problem* temp = new problem;

        //2.Update the pointer

        //If the linked list has only one problem, the list will be empty after removing (head will become nullptr)
        if (size == 1)
        {
            head = nullptr;
        }
        else if (size > 1)
        {
            //Create a previous problem
            problem* prev = new problem;

            //Initialize the previous pointer
            prev = head;

            //Point to the right position (before the remove position)
            while (prev->next->next != nullptr)
            {
                prev = prev->next;
            }

            temp = prev->next;
            prev->next = nullptr;
        }

        //3.Delete the temperary problem
        delete temp;

        //Decrement the list size
        size--;
    }

    //Remove problem by position
    void removeByPos(int pos)
    {
        //Check if the linked list is empty
        if (isEmpty() == true)
        {
            return;
        }

        //Check position index (if it is out of bound)
        if ((pos >= size) || (pos < 0))
        {
            return;
        }

        //Remove from the beginning of the list (index: 0)
        if (pos == 0)
        {
            removeFromBeg();
        }
        //Remove from the end of the list (index: position)
        else if (pos == size - 1)
        {
            removeFromEnd();
        }
        //Remove from the middle of the list
        else
        {
            removeFromMid(pos);
        }

        return;
    }

    //Remove problem by problem ID
    void removeByID(int id)
    {
        //Create a temperary problem
        problem* temp = new problem;
        temp = head;

        //Create a position counter
        int pos = 0;

        while (temp != nullptr)
        {
            if (temp->id == id)
            {
                removeByPos(pos);
                break;
            }

            //Move temp pointer
            temp = temp->next;
            pos++;
        }

        return;
    }

    //Remove problem by problem name
    void removeByName(string name)
    {
        //Create a temperary problem
        problem* temp = new problem;
        temp = head;

        //Create a counter
        int counter = 0;

        //Count frequency
        while (temp != nullptr)
        {
            if (name == temp->name)
            {
                counter++;
            }

            //Move pointer
            temp = temp->next;
        }

        //Reset temp pointer
        temp = head;

        //Create a position counter
        int pos = 0;

        for (int i = 0; i < counter; i++)
        {
            while (temp != nullptr)
            {
                if (name == temp->name)
                {
                    removeByPos(pos);
                    break;
                }

                //Move temp pointer
                temp = temp->next;
                pos++;
            }

            //Reset temp pointer
            temp = head;
        }

        return;
    }

    //Remove problem by problem difficulty
    void removeByDifficulty(string difficulty)
    {
        //Create a temperary problem
        problem* temp = new problem;
        temp = head;

        //Create a counter
        int counter = 0;

        //Count frequency
        while (temp != nullptr)
        {
            if (difficulty == temp->difficulty)
            {
                counter++;
            }

            //Move pointer
            temp = temp->next;
        }

        //Reset temp pointer
        temp = head;

        //Create a position counter
        int pos = 0;

        for (int i = 0; i < counter; i++)
        {
            while (temp != nullptr)
            {
                if (difficulty == temp->difficulty)
                {
                    removeByPos(pos);
                    break;
                }

                //Move temp pointer
                temp = temp->next;
                pos++;
            }

            //Reset temp pointer
            temp = head;
        }

        return;
    }

    //----------------------------------------------------- SORT FUNCTION -----------------------------------------------

    //Sort problem
    void sortProblem(string sortBy, string order)
    {
        if (size > 1)
        {
            //Create a previous question and current question
            problem* prev = new problem;
            problem* curr = new problem;

            //Bubble sort
            for (int i = 0; i < size - 1; i++)
            {
                //Reset the previous question and current question
                prev = head;
                curr = head->next;

                for (int j = 0; j < size - 1 - i; j++)
                {
                    //Sort order: increasing
                    //Sort by problem ID
                    if ((sortBy == "problem_id") && (order == "increasing"))
                    {
                        if (prev->id > curr->id)
                        {
                            swapValue(prev, curr);
                        }
                    }
                    //Sort by problem name
                    else if ((sortBy == "problem_name") && (order == "increasing"))
                    {
                        if (prev->name.compare(curr->name) > 0)
                        {
                            swapValue(prev, curr);
                        }
                    }
                    else if ((sortBy == "difficulty") && (order == "increasing"))
                    {
                        if (difficultyLevel(prev->difficulty) > difficultyLevel(curr->difficulty))
                        {
                            swapValue(prev, curr);
                        }
                    }
                    //Sort order: decreasing
                    //Sort by problem ID
                    else if ((sortBy == "problem_id") && (order == "decreasing"))
                    {
                        if (prev->id < curr->id)
                        {
                            swapValue(prev, curr);
                        }
                    }
                    //Sort by problem name
                    else if ((sortBy == "problem_name") && (order == "decreasing"))
                    {
                        if (prev->name.compare(curr->name) < 0)
                        {
                            swapValue(prev, curr);
                        }
                    }
                    //Sort by problem name
                    else if ((sortBy == "difficulty") && (order == "decreasing"))
                    {
                        if (difficultyLevel(prev->difficulty) < difficultyLevel(curr->difficulty))
                        {
                            swapValue(prev, curr);
                        }
                    }

                    //Move pointer
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
        return;
    }
};

    //----------------------------------------------------- MAIN FUNCTION -----------------------------------------------

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    string input = am.get("input");
    string output = am.get("output");
    string command = am.get("command");

    //Test
    //string input = "input23.txt";
    //string output = "output23.txt";
    //string command = "command23.txt";

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

        QList.addAtEnd(id, name, difficulty);
    }

    //Close input file
    inFS.close();

    //Create variable for parsing command file
    string condition;
    int position;
    string position_str;
    string sortBy;
    string order;

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
            getline(inSS, position_str, ' ');
            position = stoi(position_str);

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
            QList.addProblem(position, id, name, difficulty);
        }
        else if (condition == "remove")
        {
            //Check further condition: id/name/difficulty/pos
            getline(inSS, bin, ':');

            //Remove by position
            if (bin == "pos")
            {
                //Read remove location
                getline(inSS, position_str);
                position = stoi(position_str);

                //Call function remove by position
                QList.removeByPos(position);
            }
            //Remove by problem ID
            else if (bin == "problem_id")
            {
                //Read problem ID
                getline(inSS, id_str);
                id = stoi(id_str);

                //Call function remove by problem ID
                QList.removeByID(id);
            }
            //Remove by problem name
            else if (bin == "problem_name")
            {
                //Read problem name
                getline(inSS, name);

                //Call function remove by problem name
                QList.removeByName(name);
            }
            //Remove by problem difficulty
            else if (bin == "difficulty")
            {
                //Read problem difficulty
                getline(inSS, difficulty);

                //Call funtion remove by problem difficulty
                QList.removeByDifficulty(difficulty);
            }
        }
        else if (condition == "sort")
        {
            //Check further condition: id/name/difficulty/pos and incresing/decreasing
            getline(inSS, sortBy, ' ');
            getline(inSS, order);

            QList.sortProblem(sortBy, order);
        }
    }

    //Close command file
    inFS.close();

    //Open output file
    outFS.open(output);

    //Check if the output file is open
    if (!outFS.is_open())
    {
        cout << "Could not open output file." << endl;
        return 1;
    }

    problem* outputProblem = QList.getHead();
    while (outputProblem != nullptr)
    {
        //write output file
        outFS << "problem_id:" << outputProblem->id 
              << ", problem_name:" << outputProblem->name 
              << ", difficulty:" << outputProblem->difficulty << endl;

        outputProblem = outputProblem->next;
    }

    //Close output file
    outFS.close();

    return 0;
}
