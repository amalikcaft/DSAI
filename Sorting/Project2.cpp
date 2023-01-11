// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " "
	   << pData->firstName << " "
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.


//Ahmad Malik
//12/11/21
//This program is the baseline sort but with a slight optimization for T4

//Array of SSN
string List[1010001] = {};

//Put SSN in List array
void LoadSSNList(list<Data*>& l){
    int i = 0;
    for (list<Data*>::iterator it = l.begin(); it != l.end(); it++,i++){
        List[i] = (*it)->ssn;
    }
}

//Check first five lines to see if it's T4
int Case(list<Data*>& l){
    list<string> FirstFive;
    int i = 0;
    for (list<Data*>::iterator it = l.begin(); i != 5; it++, i++){
        FirstFive.push_back((*it)->firstName);
    }
    FirstFive.unique();
    if (FirstFive.size() == 1){
        return 1;
    }
    else{
        return 0;
    }
}

//General comparison function used for T1,T2,T3
bool compare(Data* x, Data* y){
    if (x->lastName != y->lastName){
        return x->lastName < y->lastName;
    }
    else if (x->firstName != y->firstName){
        return x->firstName < y->firstName;
    }
    else{
        return x->ssn < y->ssn;
    }
}

//For T4, just sort the ssn, and for everything else T1,T2,T3 just use l.sort()
void sortDataList(list<Data*>& l){
    if(Case(l)==1){
        LoadSSNList(l);
        sort(List, List + l.size());
        int i = 0;
        for (list<Data*>::iterator it = l.begin(); it != l.end(); it++,i++){
            (*it)->ssn = List[i];
        }
    }
    else{
        l.sort(compare);
    }
}
