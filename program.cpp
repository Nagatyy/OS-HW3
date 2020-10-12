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
            cout << "Thread " + ID + " is running\n";
            string currentLine;
            getline(fin, currentLine);
        }



};



int main(int argc, char** argv){

    int numberOfProcessors = (int) thread::hardware_concurrency();
    int count = 0;
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
            threads[i] -> start()

            if(fin.eof()) // for the case where number of lines is not divisible by number of threads
                break;
        }

    }











    return 0;
}
