#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Neural.h"
using namespace std;

vector<vector<double>> datasheet;
vector<double> answers;

const int N = 5000; //Number of strings in dataset
const int K = 3; //Number of input neurons

//For moving dataset from file to a vector<>
void makeDatasheet(){
    ifstream fileInput;
    fileInput.open("C:\\sem4cpp\\neuralNetwork\\datasheet.txt");
    double data[N][3];
    double ans[N];

    bool print = 1;
    while (print){
        for (int i = 0 ; i < N; i++){
            for (int j = 0 ; j < 3; j++){
                fileInput >> data[i][j];
            }
        }
        print = 0;
    }
    fileInput.close();

    print = 1;
    fileInput.open("C:\\sem4cpp\\neuralNetwork\\answers.txt");
    while(print){
        for (int i = 0 ; i < N; i++){
                fileInput >> ans[i];
        }
        print = 0;
    }
    fileInput.close();

    for (int i = 0; i < N; i++){
        for (int j = 0; j < 3; j++){
            datasheet[i][j] = data[i][j];
        }
        answers[i] = ans[i];
    }
}

int main() {
    int layers;
    double eta, alpha;

    cout << "Enter number of Layers >>> ";
    cin >> layers;

    cout << "Enter Eta & Alpha >>> ";
    cin >> eta >> alpha;

    NeuralNetwork net {layers, eta, alpha};

    net.setWeights();
    //!! Example of working XOR
    //!! Good working with 4 layers, 2 3 3 1.
    //!! Eta = 1 | Alpha = 0.1 | Epochs = 1500
    vector<vector<double>> data = {{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 0}};
    vector<double> ans = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    
    cout << "START TRAINING\n";
    net.train(&data, &ans);
    
    cout << "STOP TRAINING\n";
    net.print();


    vector<double> test;
    double trueAnswer = 0;
    bool go = 1;
    while (go){
        int a = 0, b = 0;
        cout << "Enter data for test >>> ";
        cin >> a >> b;
        test.push_back(a);
        test.push_back(b);

        cout << "Enter the right answer >>> ";
        cin >> trueAnswer;

        cout << "FORWARDING...\n";
        net.feedForward(&test);
        cout << "DONE!\n";

        net.print();

        cout << "\n MSE == " << net.MSE({trueAnswer}) << endl;

        cout << "Want to try again?\n1 - YES\n0 - NO\n";
        cin >> go;
        test.clear();
    }

    return 0;
}