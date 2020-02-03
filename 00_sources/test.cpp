/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.cpp
 * Author: osboxes
 *
 * Created on 02 February 2018, 13:33
 */

#include <cstdlib>
#include <iostream>
#include "measurement.h"

using namespace std;

/*
 * 
 */
int test_case(int a, int b);

int main(int argc, char** argv) {
    //measurement::preMain();
    
    unsigned int m;
    static unsigned int i;
    static unsigned int n = 1024 * 1024;
    char a[n];
    static char *b;
    for (i=0;  i < n; i++)
    {
        b = a + i;
        //cout<<i<<": "<< (void *)b <<endl;
        *b = 0xAA;
    }
    static unsigned int *p = &m;
    static unsigned int r = 200000;
    
    cout<<i<<"I am the Middle !!! : "<<endl;
    
    for (i=0;  i < r; i++)
    {
        //cout<<i<<": "<<p<<endl;
        //*p = 0xDEADBEEF;
        p++;
        r = test_case(i, i);

    }
    
    //measurement::postMain();
    void *k = malloc(600);
    return 0;
}

int test_case(int a, int b)
{
    void *k = malloc(60);
    cout<<k<<endl;
    return a + b;
    free(k);
}
