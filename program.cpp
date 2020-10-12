//CMP310 HW3
#include <iostream>
#include <fstream>
#include <QThread>
#include <QMutex>
#include <thread>
#include <string>

using namespace std;

QMutex key1;
ifstream fin;
int occurences = 0;



class Thread : public QThread {
    private:
        int ID;
        string target;

    public:
        Thread(int ID, string target){
            this -> ID = ID;
            this -> target = target;
        }

        void run(){

            if(fin.eof()){
                return;
            }
            cout << "Thread " << ID  << " is running\n";
            string currentLine;
            key1.lock();
            getline(fin, currentLine);
            cout << "Line: " << currentLine << "\n";
            key1.unlock();
            int currentCount = 0;

            
            // to search the line for the number of occurences of target
            int pos = currentLine.find(target, 0); 
            while(pos != -1){
                currentCount++;
                pos = currentLine.find(target, (pos + target.size()));
            }
            key1.lock();
            occurences+=currentCount;
            key1.unlock();

            // key1.lock();
            // cout << "Thread " << ID << " found " << currentCount << " occurences\n";
            // key1.unlock();
            
        }

};



int main(int argc, char** argv){

    int numberOfProcessors = (int) thread::hardware_concurrency();
    Thread* threads[numberOfProcessors];
    bool* isDone = new bool[numberOfProcessors];
    // the above array is used to prevent threads leaking. A new thread will only be made if its
    // status in the above array is "true". It is set to true when a thread is finished executing


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


    // all threads will have a status of done by default
    for(int i = 0; i < numberOfProcessors; i++){
        isDone[i] = true;
        threads[i] = new Thread(i+1, target);
        threads[i] -> start();

    }
    

    while(!fin.eof()){
        for(int i = 0; i < numberOfProcessors; i++){

            isDone[i] = threads[i] -> isFinished() ? true : false;


            // only create a new thread with ID n once thread with ID n is finished executing
            if(isDone[i]){
                threads[i] = new Thread(i+1, target);
                threads[i] -> start();

            }


            // if((threads[i] -> isFinished()))
            //     threads[i] -> wait();
        }

    }

    for(int i = 0; i < numberOfProcessors; i++)
        threads[i] -> wait();

    fin.close();
    delete[] isDone;
    //delete[] threads;




        


    cout << "Count: " << occurences << "\n";


    return 0;
}
