#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool test(const string& inputFile, const string& outputFile, bool err = false);
bool testForError(const string& outputFile);
bool matchFiles(const string& outputFile);

int main(){
    bool test1_result = test("input1.csv", "output1.xml", true);
    bool test2_result = test("input2.csv", "output2.xml");
    bool test3_result = test("input3.csv", "output3.xml");
    bool test4_result = test("input4.csv", "output4.xml", true);
    bool test5_result = test("input5.csv", "output5.xml");
    bool test6_result = test("input6.csv", "output6.xml", true);
    cout << "\n";
    printf("Test 1: %s \n", test1_result ? "Pass" : "--Fail--");
    printf("Test 2: %s \n", test2_result ? "Pass" : "--Fail--");
    printf("Test 3: %s \n", test3_result ? "Pass" : "--Fail--");
    printf("Test 4: %s \n", test4_result ? "Pass" : "--Fail--");
    printf("Test 5: %s \n", test5_result ? "Pass" : "--Fail--");
    printf("Test 6: %s \n", test6_result ? "Pass" : "--Fail--");
    cout << "Enter any string to escape.\n";
    getchar();
}

bool test(const string& inputFile, const string& outputFile, bool err){
    string jarFilePath = "";
    string javaJar = "java -jar ";
    string inputLoc = "TestInputs\\" + inputFile + ' ';
    string outputLoc = "TestOutputs\\" + outputFile + ' ';
    string jarFile = "csvxmlconverter.jar ";
    string xslFile = "transform.xsl ";
    string stylizedOutputFile = "TestOutputs\\s_" + outputFile;

    jarFilePath.assign(javaJar);
    jarFilePath.append(jarFile + inputLoc + outputLoc + jarFile + xslFile + stylizedOutputFile + " > file.txt");

    printf("Jar execution path: %s\n\n", jarFilePath.c_str());
    system(jarFilePath.c_str());
    if (err) {
        return testForError(outputFile);
    } else {
        return matchFiles(outputFile); 
    }
}

bool testForError(const string& outputFile) {
    ifstream file;
    file.open("TestOutputs\\" + outputFile);
    if(file.fail()) {
        return true;
    }
    file.close();
    return false;
    
}

bool matchFiles(const string& outputFile) {
    ifstream file1;
    ifstream file2;
    ofstream file3;
    string line1, line2;

    file1.open("TestOutputs\\" + outputFile);
    file2.open("ExpectedOutputs\\exp_" + outputFile);
    if (file1.fail()) { cerr << "Error opening file !!" << endl; return false; }
    if (file2.fail()) { cerr << "Error opening file !!" << endl; return false; }

    while (!file1.eof()){
        getline(file1, line1);
        getline(file2, line2);
        if (line1.compare(line2) != 0) {
            cout << "Not the same line: \n";
            cout << line1 << "\n";
            cout << line2 << "\n\n";
            file1.close();
            file2.close();
            return false;
        }
    }

    if (!file2.eof()) {
        printf("Not thee same length\n");
        file1.close();
        file2.close();
        return false;
    }

    file1.close();
    file2.close();

    return true;
}