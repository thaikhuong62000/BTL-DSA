/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Declaration of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_PROCESSDATA_H
#define DSA191_A1_PROCESSDATA_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cassert>
#include "dbLib.h"

using namespace std;
/// Prototype declaration

extern int N;
extern int* dOut;
extern void* pOut;
extern string* sOut;
void Initialization();
void Finalization();
void CL(void* pData, void*& pOutput);
void CL(void* pData, void*& pOutput, string city_name);
void LSC(void* pData, void*& pOutput, string city_name);
void LLC(void* pData, void*& pOutput, string city_name);
void LSL(void* pData, void*& pOutput, int line_id);
void FC(void* pData, void*& pOutput, string city_name);
void FS(void* pData, void*& pOutput, string station_name);
void SLP(void* pData, void*& pOutput, int station_id, int track_id);
void IS(void* pData, void*& pOutput, string csv);
void RS(void* pData, void*& pOutput, int station_id);
void US(void* pData, void*& pOutput, int station_id, string csv);
void ISL(void* pData, void*& pOutput, int station_id, int line_id, int p_i);
void RSL(void* pData, void*& pOutput, int station_id, int line_id);
int  findRequest(string pRequest);
void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &);


template <typename T>
void PrintReqOutput(const char* pRequest, T* pOutput, int N) {
    cout << pRequest << ":";
    if (pOutput == nullptr) {
        cout << " error\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        cout << ' ' << *pOutput++;
    }
    cout << '\n';
}

#endif //DSA191_A1_PROCESSDATA_H
