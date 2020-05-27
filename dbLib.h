/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H
#define DATA						((*(TDataset * *)pData))
#define DTemp(TStruct,pTemp)		((*(TStruct  * *)pTemp))

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

struct TStation
{
	// The structure to store station information
	int cityID, build, opening, closure;
	string name, geo;
	TStation() :cityID(0), build(0), opening(0), closure(0) {};
};
struct TTrack {
	// The structure to store track information
	L1List<string>* geometry;
	TTrack() :geometry(NULL) {};
	~TTrack()
	{
		if (geometry != NULL)
		{
			delete geometry;
		}
	}
};
struct TLine
{
	// The structure to store line information
	L1List<int>* stationLine;
	TLine() :stationLine(NULL) {};
	~TLine()
	{
		if (stationLine != NULL)
		{
			delete stationLine;
		}
	}
};
struct TCity
{
	// The structure to store city information
	string cityName;
	L1List<TLine>* lineCity;
	L1List<TTrack>* trackCity;
	TCity() :lineCity(NULL), trackCity(NULL) {};
	~TCity()
	{
		if (lineCity != NULL)
		{
			delete lineCity;
		}
		if (trackCity != NULL)
		{
			delete trackCity;
		}
	}
};
class TDataset
{
public:
	L1List<TCity>* city;
	L1List<TStation>* station;
	int maxStationID;
	TDataset() :city(NULL), station(NULL), maxStationID(0) {};
	~TDataset()
	{
		delete station;
		delete city;
	}
};

// Please add more or modify as needed

extern TDataset* _pData;
void LoadGeo(TTrack*& trackCity, string geoRaw);
void LoadTrack(TDataset*& pData);
void LoadStationLine(TDataset*& pData);
void LoadLine(TDataset*& pData);
void LoadCity(TDataset*& pData);
void LoadStation(TDataset*& pData);
void LoadData(void*&);
void ReleaseData(void*&);

#endif //DSA191_A1_DBLIB_H
