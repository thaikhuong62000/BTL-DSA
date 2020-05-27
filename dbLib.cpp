/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */
#include <codecvt>
#include "dbLib.h"

 /* TODO: You can implement methods, functions that support your data structures here.
  * */
TDataset* _pData = new TDataset();
void LoadGeo(TTrack*& trackCity, string geoRaw)
{
	if (!geoRaw.empty())
	{
		trackCity->geometry = new L1List<string>();
		int ID = 0;
		while (true)
		{
			if (geoRaw.find(',') == -1)
			{
				trackCity->geometry->insertHead(geoRaw, ID);
				break;
			}
			string newGeo = geoRaw.substr(0, geoRaw.find(','));
			geoRaw.replace(0, geoRaw.find(',') + 1, "");
			trackCity->geometry->insertHead(newGeo, ID);
			ID++;
		}
	}
}
void LoadTrack(TDataset*& pData)
{
	int citySize = pData->city->getSize();
	fstream infile;
	infile.open("tracks.csv");
	string line;
	getline(infile, line);
	while (!infile.eof())
	{
		TTrack* newTrack = new TTrack();
		getline(infile, line, ',');
		if (line.empty())
		{
			break;
		}
		int trackID = stoi(line);
		string geoRaw;
		getline(infile, line);
		if (line.find(")\",") != -1)
		{
			geoRaw = line.substr(12, line.find(")\","));
			line.replace(0, line.find(")\",") + 3, "");
		}
		else
		{
			line.replace(0, line.find(',') + 1, "");
		}
		line.replace(0, line.find(',') + 1, "");
		line.replace(0, line.find(',') + 1, "");
		line.replace(0, line.find(',') + 1, "");
		line.replace(0, line.find(',') + 1, "");
		int cityID = stoi(line);
		void* pTemp = &(pData->city->atID(cityID).trackCity);
		if (DTemp(L1List<TTrack>, pTemp) == NULL)
		{
			DTemp(L1List<TTrack>, pTemp) = new L1List<TTrack>();
		}
		LoadGeo(newTrack, geoRaw);
		DTemp(L1List<TTrack>, pTemp)->insertHead(*newTrack, trackID);
	}
	infile.close();
	for (int i = 0; i < citySize; i++)
	{
		void* pTemp = &(pData->city->at(i).trackCity);
		if (DTemp(L1List<TTrack>, pTemp) != NULL)
		{
			DTemp(L1List<TTrack>, pTemp)->reverse();
		}
	}
}
void LoadStationLine(TDataset*& pData)
{
	int citySize = pData->city->getSize();
	fstream infile;
	infile.open("station_lines.csv");
	string line;
	getline(infile, line);
	while (!infile.eof())
	{
		getline(infile, line, ',');
		if (line.empty())
		{
			continue;
		}
		getline(infile, line, ',');
		int stationID = stoi(line);
		getline(infile, line, ',');
		int lineID = stoi(line);
		getline(infile, line, ',');
		int cityID = stoi(line);
		void* pLine = &(pData->city->atID(cityID).lineCity->atID(lineID).stationLine);
		if (DTemp(L1List<int>, pLine) == NULL)
		{
			DTemp(L1List<int>, pLine) = new L1List<int>();
		}
		DTemp(L1List<int>, pLine)->insertHead(stationID, stationID);
		getline(infile, line);
	}
	for (int i = 0; i < citySize; i++)
	{
		void* pCity = &pData->city->at(i).lineCity;
		if (DTemp(L1List<TLine>, pCity) != NULL)
		{
			for (int j = 0; j < DTemp(L1List<TLine>, pCity)->getSize(); j++)
			{
				void* pLine = &DTemp(L1List<TLine>, pCity)->at(j).stationLine;
				if (DTemp(L1List<int>, pLine) != NULL)
				{
					DTemp(L1List<int>, pLine)->reverse();
				}
			}
		}
	}
}
void LoadLine(TDataset*& pData)
{
	int citySize = pData->city->getSize();
	fstream infile;
	infile.open("lines.csv");
	string line;
	getline(infile, line);
	while (!infile.eof())
	{
		TLine newLine;
		getline(infile, line, ',');
		if (line.empty())
		{
			continue;
		}
		int lineID = stoi(line);
		getline(infile, line, ',');
		int cityID = stoi(line);
		void* pTemp = &(pData->city->atID(cityID).lineCity);
		if (DTemp(L1List<TLine>, pTemp) == NULL)
		{
			DTemp(L1List<TLine>, pTemp) = new L1List<TLine>();
		}
		DTemp(L1List<TLine>, pTemp)->insertHead(newLine, lineID);
		getline(infile, line);
	}
	infile.close();
	for (int i = 0; i < citySize; i++)
	{
		void* pTemp = &(pData->city->at(i).lineCity);
		if (DTemp(L1List<TLine>, pTemp) != NULL)
		{
			DTemp(L1List<TLine>, pTemp)->reverse();
		}
	}
}
void LoadCity(TDataset*& pData)
{
	fstream infile;
	infile.open("cities.csv");
	string line;
	getline(infile, line);
	while (!infile.eof())
	{
		TCity newCity;
		getline(infile, line);
		if (line.empty())
		{
			break;
		}
		string tmp;
		tmp = line.substr(0, line.find(','));
		int cityID = stoi(tmp);
		line.replace(0, line.find(',') + 1, "");
		tmp = line.substr(0, line.find(",P"));
		if (tmp[0] == '\"')
		{
			tmp.replace(0, 1, "");
			tmp.pop_back();
		}
		newCity.cityName = tmp;
		pData->city->insertHead(newCity, cityID);
	}
	infile.close();
	pData->city->reverse();
}
void LoadStation(TDataset*& pData)
{
	fstream infile;
	infile.open("stations.csv",ios::in);
	string line;
	getline(infile, line);
	while (!infile.eof())
	{
		TStation newStation;
		getline(infile, line);
		if (line.empty())
		{
			continue;
		}
		string tmp;
		tmp = line.substr(0, line.find(','));
		int stationID = stoi(tmp);
		line.replace(0, line.find(',') + 1, "");
		tmp = line.substr(0, line.find(",P"));
		if (tmp[0] == '\"')
		{
			tmp.replace(0, 1, "");
			tmp.pop_back();
		}
		newStation.name = tmp;
		line.replace(0, line.find(",P") + 7, "");
		tmp = line.substr(0, line.find("),"));
		newStation.geo = tmp;
		line.replace(0, line.find("),") + 2, "");
		tmp = line.substr(0, line.find(','));
		newStation.build = tmp.empty() ? 0 : stoi(tmp);
		line.replace(0, line.find(',') + 1, "");
		tmp = line.substr(0, line.find(','));
		newStation.opening = tmp.empty() ? 0 : stoi(tmp);
		line.replace(0, line.find(',') + 1, "");
		tmp = line.substr(0, line.find(','));
		newStation.closure = tmp.empty() ? 0 : stoi(tmp);
		line.replace(0, line.find(',') + 1, "");
		newStation.cityID = tmp.empty() ? 0 : stoi(line);
		pData->station->insertHead(newStation, stationID);
	}
	infile.close();
	pData->station->reverse();
}
void LoadData(void*& pData)
{
	pData = &_pData;
	DATA->station = new L1List<TStation>();
	LoadStation(DATA);
	DATA->maxStationID = DATA->station->maxID();
	DATA->city = new L1List<TCity>();
	LoadCity(DATA);
	LoadLine(DATA);
	LoadStationLine(DATA);
	LoadTrack(DATA);
}
void ReleaseData(void*& pData) { delete DATA; }
