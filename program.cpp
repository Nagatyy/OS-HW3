//CMP310 HW3
#include <iostream>
#include <fstream>
#include <QThread>
#include <QMutex>
#include <thread>
#include <string>

using namespace std;

ifstream fin;



class Thread : public QThread {
    private:
        int ID;
        std::string target;

    public:
        Thread(int ID, string target, int startPos, int endPos){
            this -> ID = ID;
            this -> target = target;
        }

        void run(){
            string currentLine;

        }



};



int main(int argc, char** argv){

    int numberOfProcessors = (int) thread::hardware_concurrency();

    cout << numberOfProcessors << std::endl;

    // if (argc != 3){
    //     std::cout << "Incorrect Number of Arguments!" <<std::endl;
    //     return 0; //exit
    // }

    string target = argv[1];
    string fileName = argv[2];

    // fin.open(fileName);

    // if(fin.fail())


    return 0;
}
