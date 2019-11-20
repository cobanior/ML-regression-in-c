/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: orest
 *
 * Created on November 14, 2019, 5:05 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include "trainingData.h"

    
using namespace std;
/*
 * 
 */

float hypothesis(float* param, float Xi, int n);//our hypothesis
void training(float* param, trainingData*, int, int);//the training of our parameters is done by this function
void initialize(float*, int);//this function is used to initialize the array of parameters
float sum(int m, int n, float* param, trainingData* XY, int j);//takes a specific summation needed for the training

int main() {

    
    int n = 0; // degree of the polynomial 
    int m = 0; // the number of training examples
    int x = 0; //counts the x-s
    int y = 0; //counts the y-s
    
    ifstream countStream;
    countStream.open("trainingdata.txt");//this stream will be used to count the training examples
    for(int i=0; i<2; i++)//for two lines of entry
    {
        countStream.ignore(10,':');
        while (countStream.peek()!='\n')
        {
            if(i==0){
                float temp;
                countStream>>temp;
                x++;
            }
                
            else{
                float temp;
                countStream>>temp;
                y++;
            }
        }
    }
    
    countStream.close();
    cout<<"number of x training examples is: "<<x<<endl;
    cout<<"number of y training examples is: "<<y<<endl;
    
    if(x==y)
        m = x;
    else
    {
        cout<<"The number of x-s entered is not the same with the number of y-s entered!"<<endl;
        return 1;
    }
    
    trainingData *XY;
    XY = new trainingData[m];
    
    cout<<"Enter the degree of the polynomial: \n";
    cout<<"Note: The degree of the polynomial needs to be at most one less than the number of training examples! \n";
    cin>>n;
    
    float *param = nullptr;
    param = new float[n+1];
    
    ifstream inputStream; 
    inputStream.open("trainingdata.txt");
    
    for(int i=0; i<2; i++)//for two lines of entry
    {
        int c=0;
        inputStream.ignore(10,':');
        while (c<m)
        {
            if(i==0){
                float temp;
                inputStream>>temp;
                XY[c].set_x(temp);
            }
                
            else{
                float temp;
                inputStream>>temp;
                XY[c].set_y(temp);
            }
            c++;
        }
    }
    
    inputStream.close();
    
    int prnt = 0;
    while (prnt < m)
    {
        cout<<XY[prnt].get_x()<<" ";
        cout<<XY[prnt].get_y()<<endl;  
        prnt++;
    }
    cout<<"Number of training examples is: "<<prnt<<endl;
    
    cout<<"Beginning to train the parameters... \n";
    training(param, XY, n, m);
    cout<<"Ended training the parameters: \n";
    
    for (int c=0; c<=n; c++)
    {
        cout<<param[c]<<" ";
    }
    return 0;
}

float hypothesis(float* param, float Xi, int n)
{
    
    float h = 0; //the value of our function will be stored here;
    
    for(int i=0; i<=n; i++)
    {
        h += param[i]*pow(Xi,i);
    }
    
    return h;
}

float sum(int m, int n, float* param, trainingData* XY, int j)
{
    float h = 0;
    float sum = 0;
    
    for (int i=0; i<m; i++)
    {
        h = hypothesis(param, XY[i].get_x(), n);
        sum += ((h - XY[i].get_y())*pow(XY[i].get_x(),j));
    }
    
    return sum;
}

void initialize(float* param, int n)
{
    for(int i=0; i<=n; i++)
    {
        param[i] = i;
    } 
}

void training(float* param, trainingData* XY, int n, int m)
{
   initialize(param, n);//initialize the values of the parameter array
   float alpha = 0.5;//scaling factor
   
   cout<<"We start with parameters that are all initialized to one, \n";
   cout<<"with a scaling factor (alpha) of 0.5 \n";
   
   for (int i=0; i<100; i++)
   {
        
        for (int j=0; j<=n; j++)
        {
            float L = (alpha/m)*sum(m,n,param,XY,j);
            param[j] = param[j] - L;
            float theta = param[j];
            cout<<theta<<" ";
        }
        cout<<"*";
   }
   cout<<endl;
}


