//Ahmad Malik
//DSA1
//Project 1
//FALL 2021

//This program reads commands from an input file "Sample_Input", builds singly linked lists
// and performs pop and push operations on the created lists. The output
//is shown by the log file "Sample_Output" that keeps track of the completed commands.

#include<iostream>
#include<fstream>
#include<list>
#include<string>
using namespace std;

//SimpleList template class
template <typename T>
class SimpleList{
private:    //Nested private Node class
	class Node {
	private:
		friend class SimpleList<T>;
		T value;
		Node* next;
	};
          //protected memeber functions that manipulate Stacks and Queues
protected:
	void insertAtStart(T data);
    void insertAtEnd(T data);
    T removeFromStart();
	Node* head;
	Node* tail;
	string listName;

public:   //Cosntructor for Simplelist
	SimpleList(): head(nullptr), tail(nullptr){};

	string print_name() {
		return listName;
	}
	virtual void push(T data) = 0;    //Pure virtual pop/push functions defined
	virtual T pop() = 0;

	bool empty() {     //checks if List is empty
		return head;
	}
};
//Insert node at front of list
template <typename T>
void SimpleList<T>::insertAtStart(T data){
	Node* newNode = new Node;
	newNode->value = data;
	newNode->next = head;
	head = newNode;
}
//Insert node at end of list
template <typename T>
void SimpleList<T>::insertAtEnd(T data){
	Node* newNode = new Node;
	newNode->value = data;
	if (head == nullptr){
		tail = newNode;
		head = newNode;
		newNode = nullptr;
	}
	else{
		tail->next = newNode;
		tail = newNode;
	};
}
//Remove node at front of list
template <typename T>
T SimpleList<T>::removeFromStart(){
		T value;
		Node* tempNode = head;
		head = head->next;
		value = tempNode->value;
		delete tempNode;
		return value;
}
//Derived class that implements pop/push for Stacks
template <typename T>
class Stack:public SimpleList<T> {
public:
	Stack(string name) {
		this->listName = name;
	}
	void push(T data) {
		this->insertAtStart(data);
	}
	T pop() {
		return this->removeFromStart();
	}
};
//Derived class that implements pop/push for Queues
template<typename T>
class Queue:public SimpleList<T> {
public:
	Queue(string name){
		this->listName = name;
	}
	void push(T data) {this->insertAtEnd(data);
	}
	T pop() {
		return this->removeFromStart();
	}
};

//Template class that searches through list names of similar list types
template <typename T>
SimpleList<T>* Search(list<SimpleList<T>*>& ltype, string listName){
	class list<SimpleList<T>*> ::iterator it;
	for (it = ltype.begin(); it != ltype.end(); ++it){
		if (listName == (*it)->print_name()){
			return *it;
		}
	}
	return nullptr;
}

//Class that builds lists and maintains pop and push commands
class Parse {
private:
    list<SimpleList<int>*> listSLi;    //Integer stacks and queues lists
	list<SimpleList<double>*> listSLd; //Double stacks and queues lists
	list<SimpleList<string>*> listSLs; //String stacks and queues lists
public:
    string ifile, ofile;
    ifstream input;
    ofstream output;
    //Constructor that handles input/output file stream
    Parse(){
    cout << "Enter name of input file: ";
    cin >> ifile;
    cout << "Enter name of output file: ";
    cin >> ofile;
    input.open(ifile);
    output.open(ofile);
	}

    //returns false until input file reaches EOF
	bool fileEnd() {
		return input.eof();
    }
    //function that searches if existing list types exists, then creates it.
	void createList(char datatype, string listName) {
		string listType;
		input >> listType;
		output << "PROCESSING COMMAND: create " << listName << " " << listType << endl;

		//Searches and creates list of datatype int
        if (datatype == 'i'){
			SimpleList<int>* findList = Search(listSLi, listName);
			if (findList==nullptr){
                SimpleList<int>* pSLi;
                if (listType == "stack"){
                    pSLi = new Stack<int>(listName);}
                else {
                    pSLi = new Queue<int>(listName);}
                listSLi.push_front(pSLi);
			}
			else{
                output << "ERROR: This name already exists!"<<endl;	}
		}

        //Searches and creates list of datatype double
		else if (datatype == 'd') {
            SimpleList<double>* findList = Search(listSLd, listName);
			if (findList==nullptr){
                SimpleList<double>* pSLd;
                if (listType == "stack"){
                    pSLd = new Stack<double>(listName);}
                else {
                    pSLd = new Queue<double>(listName);}
                listSLd.push_front(pSLd);
			}
			else{
                output << "ERROR: This name already exists!"<<endl;}
		}

        //Searches and creates list of datatype String
		else {
            SimpleList<string>* findList = Search(listSLs, listName);
			if (findList==nullptr){
                SimpleList<string>* pSLs;
                if (listType == "stack"){
                    pSLs = new Stack<string>(listName);}
                else {
                    pSLs = new Queue<string>(listName);}
                listSLs.push_front(pSLs);
			}
			else{
                output << "ERROR: This name already exists!"<< endl;}
		}
	}
    //Pop function for ints/doubles/strings
    void pop(char datatype, string listName) {
        output << "PROCESSING COMMAND: pop " << listName << endl;

		//Pop function for ints
        if (datatype == 'i'){
            SimpleList<int>* findList = Search(listSLi, listName);
            if (findList != nullptr){
                if (findList->empty()){
                    output << "Value popped: " << findList->pop() << endl;}
                else{
                    output << "ERROR: This list is empty!" << endl;}
                }
            else{
                 output << "ERROR: This name does not exist!" << endl;}
            }

	    //Pop function for doubles
        else if (datatype == 'd') {
            SimpleList<double>* findList = Search(listSLd, listName);
            if (findList != nullptr){
                if (findList->empty()){
                    output << "Value popped: " << findList->pop() << endl;}
                else{
                    output << "ERROR: This list is empty!" << endl ;}
                }
            else{
                 output << "ERROR: This name does not exist!" << endl ;}
            }

        //Pop function for strings
        else if (datatype == 's') {
            SimpleList<string>* findList = Search(listSLs, listName);
            if (findList!=nullptr){
                if (findList->empty()){
                    output << "Value popped: " << findList->pop() << endl;}
                else {
                    output << "ERROR: This list is empty!" << endl;}
                }
            else{
                output << "ERROR: This name does not exist!" << endl;}
        }
    }
    //Push function for ints/doubles/strings
	void push(char datatype, string listName){
		output << "PROCESSING COMMAND: push " << listName << " ";

		//Push function for ints
		if (datatype == 'i') {
			int data;
			input >> data;
			output << data << endl;
			SimpleList<int>* findList= Search(listSLi, listName);
			if (findList != nullptr) {
				findList->push(data);
			}
			else {
				output << "ERROR: This name does not exist!"<<endl;}
		}

		//Push function for doubles
		else if (datatype == 'd') {
			double data;
			input >> data;
			output << data << endl;
			SimpleList<double>* findList = Search(listSLd, listName);
			if (findList != nullptr) {
				findList->push(data);}
			else {
				output << "ERROR: This name does not exist!"<<endl;}
		}

		//Push function for strings
		else if(datatype == 's'){
			string data;
			input >> data;
			output << data << endl;
			SimpleList<string>* findList = Search(listSLs, listName);
			if (findList != nullptr){
				findList->push(data);}
			else {
				output << "ERROR: This name does not exist!"<<endl;}
		}
	}
};

int main() {
	Parse file;
	if (file.input.is_open()){
		while (!file.fileEnd()){   //loop through file until EOF
            char datatype;
			string command, listName;
			file.input >> command;
			file.input >> listName;
            string c = listName.substr(0, 1);
            //check which letter is infront of listName
            if (c == "i") {
				datatype = 'i';}
			else if (c == "d") {
				datatype = 'd';}
			else {
				datatype = 's';}
			if (command == "create") {
				file.createList(datatype, listName);}
            else if (command == "pop") {
				file.pop(datatype, listName);}
            else if (command == "push") {
				file.push(datatype, listName);}
		}
		file.input.close();
	}
	else{     				// Error if traget input file is not retrieved correctly
        file.output << "TARGET INPUT FILE: READ ERROR" << endl;
	}
}
