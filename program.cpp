//CMP310 HW3
#include <iostream>
#include <fstream>
#include <QThread>
#include <QMutex>
#include <thread>
#include <string>
#include<vector>


using namespace std;

QMutex key1, key2;
ifstream fin;
int occurences = 0;



class Thread : public QThread {
    private:
        int ID;
        string target;
        //string line;

    public:
        Thread(int ID, string target){
            this -> ID = ID;
            this -> target = target;
            // this -> line = line;
        }

        void run(){
            cout << "Thread " << ID << " is running\n";
            string currentLine;
            key1.lock();
            getline(fin, currentLine);
            cout << "Line: " << currentLine << "\n";
            key1.unlock();

            if(fin.eof()){
                cout << "EOF Reached\n";
            }
            else {
                int pos = 0;

                // to search the line for the number of occurences of target
                while ((pos = currentLine.find(target, pos)) != std::string::npos) {
                    key2.lock();
                    occurences++;
                    key1.unlock();
                    pos += target.length();
                }

                key1.lock();
                cout << "Thread " << ID << " found " << occurences << " occurences\n";
                key1.unlock();
            }
        }

};



int main(int argc, char** argv){

    int numberOfProcessors = (int) thread::hardware_concurrency();
    Thread* threads[numberOfProcessors];



    if (argc != 3){
        std::cout << "Incorrect Number of Arguments!" <<std::endl;
        return 0; //exit
    }

    string target = argv[1];
    string fileName = argv[2];

    fin.open(fileName);

    if(fin.fail()){
        cout << "Failed to open file" << endl;
        return 0;
    }


    while(!fin.eof()){
        for(int i = 1; i <= numberOfProcessors; i++){
            threads[i] = new Thread(i, target);
            threads[i] -> start();

            if((threads[i] -> isFinished()))
                threads[i] -> wait();
        }

    }

    for(int i = 1; i <= numberOfProcessors; i++)
            threads[i] -> wait();

        


    cout << "Count: " << occurences << "\n";


    return 0;
}
