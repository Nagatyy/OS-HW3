#include <QThread>
#include <iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

vector<vector<int> > vec;
int total = 0;

void add(vector< vector<int> > &vec, int line , int word){

        vector<int> v1;
        v1.push_back(line);
        v1.push_back(word);
        vec.push_back(v1);

}


bool available(vector< vector<int> > &vec, int line, int word){

    bool var = false;
    for (int i = 0; i < vec.size(); i++) {

        if(vec[i][0] == line && vec[i][1] == word){

         return true;
         break;
        }

        else continue;
    }
    return var;

}

class MyThread: public QThread {
  private:
  int ID;
  string filename;
  string word;

  public:
  MyThread(int i, string filename, string word)  {
  ID = i;
  this->filename = filename;
  this->word = word;
  }
   ifstream file;
   int count = 0;

        //int lineNum = 0;
        //int wordNum= 0;

  void run() {

          int lineNum = 0;
        int wordNum= 0;

         cout << "Thread " << ID << " is running\n";

        file.open(filename.c_str());

        lineNum++;
        string readWord;

        while (file >> readWord)
    {

			if(file.get() == '\n'){
                lineNum++;
                wordNum = 0;
                continue;

			}

           wordNum++;

			if(available(vec,lineNum,wordNum)){
                    continue;
			}

			if(readWord == word){
					count++;
					total++;
					add(vec,lineNum,wordNum);
					sleep(2);
			}

    }
        cout << "total searches found by Thread " << ID << " are " << count << endl;

  }


};



int main() {

        string filename = "searchfile.txt";
        string word = "raza";

  MyThread * x[4];
  for (int i = 0; i < 4; i++) {
    x[i] = new MyThread(i, filename, word);
    x[i] -> start();
 //   x[i]->wait();
  }

   for(int i=0;i<4;i++)
        x[i]->wait();

cout << "final num of  matches found = " << total << endl;

  return 0;
}