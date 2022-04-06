#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Neural.h"
using namespace std;

vector<vector<double>> datasheet;
vector<double> answers;

const int N = 5000; //Amount of data strings
const int K = 3; //Number of input neurons

//Function to transfer datasheet from file to vector<>
void makeDatasheet(){
    ifstream fileInput;
    fileInput.open("C:\\sem4cpp\\neuralNetwork\\datasheet.txt");
    double data[N][K];
    double ans[N];

    bool print = 1;
    while (print){
        for (int i = 0 ; i < N; i++){
            for (int j = 0 ; j < K; j++){
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
        for (int j = 0; j < K; j++){
            datasheet[i][j] = data[i][j];
        }
        answers[i] = ans[i];
    }

}


int main() {
    NeuralNetwork net {K};
    net.setWeights();
    
    datasheet.resize(N);
    for (int i = 0; i < N; i++){
        datasheet[i].resize(3);
    }
    answers.resize(N);

    makeDatasheet();
    //Example for XOR
    vector<vector<double>> d = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<double> a = {0, 1, 1, 0};
    net.train(&d, &a);
    
    net.print();

    vector<vector<double>> test = {{1, 0}};
    net.feedForward(&test[0]);
    net.print();
    cout << "\n\n" << net.MSE({1});


/*
    vector<double> test1 = {-3.07276, 3.2815, 3.95383};
    vector<double> test2 = {3.07276, -3.2815, 3.95383};
    vector<double> test3 = {3.07276, 3.2815, -3.95383};
    vector<double> test4 = {-3.07276, -3.2815, 3.95383};
    vector<double> test5 = {3.07276, -3.2815, -3.95383};
    vector<double> test6 = {-3.07276, 3.2815, -3.95383};

    net.feedForward(&test1);
    cout << "\n\n\n";
    net.print();
    cout << endl << "MSE >>> " << net.MSE({1}) << "\n\n\n";
    net.feedForward(&test2);
    cout << "\n\n\n";
    net.print();
    cout << endl << "MSE >>> " << net.MSE({1}) << "\n\n\n";
    net.feedForward(&test3);
    cout << "\n\n\n";
    net.print();
    cout << endl << "MSE >>> " << net.MSE({1}) << "\n\n\n";
    net.feedForward(&test4);
    cout << "\n\n\n";
    net.print();
    cout << endl << "MSE >>> " << net.MSE({1}) << "\n\n\n";
    net.feedForward(&test5);
    cout << "\n\n\n";
    net.print();
    cout << endl << "MSE >>> " << net.MSE({1}) << "\n\n\n";
    net.feedForward(&test6);
    cout << "\n\n\n";
    net.print();
    cout << endl << "MSE >>> " << net.MSE({1}) << "\n\n\n";
*/

    return 0;
}