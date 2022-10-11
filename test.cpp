#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool test(const string& inputFile, const string& outputFile);
bool matchFiles(const string& outputFile);

int main(){
    // TODO print whether test failed or passed

    test("input1.csv", "output1.xml");
    test("input2.csv", "output2.xml");
    //test("input3.csv", "output3.xml");
    //test("input4.csv", "output4.xml");
    //test("input5.csv", "output5.xml");
    //test("input6.csv", "output6.xml");
}

bool test(const string& inputFile, const string& outputFile){
    string jarFilePath = "";
    string javaJar = "java -jar ";
    string inputLoc = ".\\TestInputs\\" + inputFile + ' ';
    string outputLoc = ".\\TestOutputs\\" + outputFile + ' ';
    string jarFile = "csvxmlconverter.jar ";
    string xslFile = "transform.xsl ";
    string stylizedOutputFile = ".\\TestOutputs\\s_" + outputFile;

    jarFilePath.assign(javaJar);
    jarFilePath.append(jarFile + inputLoc + outputLoc + jarFile + xslFile + stylizedOutputFile + " > file.txt");

    printf("Jar execution path: %s\n\n", jarFilePath.c_str());
    system(jarFilePath.c_str());

    return matchFiles(outputFile); // TODO should return fail if the system call didn't create the output file
}

bool matchFiles(const string& outputFile) {
    ifstream file1;
    ifstream file2;
    ofstream file3;
    string line1, line2;

    file1.open(".\\TestOutputs\\exp_" + outputFile);
    file2.open(".\\ExpectedOutputs\\exp_" + outputFile);
    if (file1.fail()) { cerr << "Error opening file !!" << endl; return false; }
    if (file2.fail()) { cerr << "Error opening file !!" << endl; return false; }

    while (!file1.eof()){
        getline(file1, line1);
        getline(file2, line2);
        if (line1 != line2) {
            return false;
        }
    }

    /*if (!file2.eof()) {
        printf("File 2 not finished");
    }*/

    file1.close();
    file2.close();

    return true;
}