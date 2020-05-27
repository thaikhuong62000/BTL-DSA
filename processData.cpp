/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

	int _N = 0;
	void* pOut = nullptr;
	int*  dOut = nullptr;
	string* sOut = nullptr;
void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
	
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
	int k = findRequest(pRequest);
	switch (k)
	{
	case 1:
		CL(pData,pOutput);
		break;
	case 2:
		CL(pData,pOutput, *sOut);
		break;
	case 3:
		LSC(pData,pOutput, *sOut);
		break;
	case 4:
		LLC(pData,pOutput, *sOut);
		break;
	case 5:
		LSL(pData,pOutput,stoi(*sOut));
		break;
	case 6:
		FC(pData, pOutput, *sOut);
		break;
	case 7:
		FS(pData, pOutput, *sOut);
		break;
	case 8:
		SLP(pData, pOutput, stoi(*sOut++), stoi(*sOut--));
		break;
	case 9:
		IS(pData, pOutput, *sOut);
		break;
	case 10:
		ISL(pData, pOutput, stoi(*sOut), stoi(*(sOut + 1)), stoi(*(sOut + 2)));
		break;
	case 11:
		RS(pData, pOutput, stoi(*sOut));
		break;
	case 12:
		RSL(pData, pOutput, stoi(*sOut++), stoi(*sOut--));
		break;
	case 13:
		US(pData, pOutput, stoi(*sOut++), *sOut--);
		break;
	default:
		break;
	}
	N = _N;
	delete[] sOut;
}

void countLine(L1Item<TCity>*& city)
{
	if (city->data.lineCity != NULL)
	{
		*dOut += city->data.lineCity->getSize();
	}
}
void CL(void* pData, void*& pOutput)
{
	_N = 1;
	dOut = new int(0);
	pOut = dOut;
	DATA->city->traverse(countLine);
	pOutput = pOut;
}

void countLineCity(L1Item<TCity>*& city, void* pParam)
{
	if (city->data.cityName == *(string*)pParam)
	{
		*dOut = city->data.lineCity->getSize();
	}
}
void CL(void* pData, void*& pOutput, string city_name)
{
	_N = 1;
	dOut = new int(-1);
	pOut = &dOut;
	void* pParam = &city_name;
	DATA->city->traverse(countLineCity, pParam);
	pOutput = (int*)dOut;
}

void countStation(L1Item<TStation>*& station, void* pID)
{
	if (station->data.cityID == *(int*)pID)
	{
		_N++;
	}
}
void addStation(L1Item<TStation>*& station, void* pID)
{
	if (station->data.cityID == *(int*)pID)
	{
		*dOut = station->ID;
		dOut++;
	}
}
void LSC(void* pData, void*& pOutput, string city_name)
{
	int ID = 0;
	for (int i = 0; i < DATA->city->getSize(); i++)
	{
		if (DATA->city->at(i).cityName == city_name)
		{
			ID = DATA->city->getID(i);
			break;
		}
	}
	_N = 0;
	void* pID = &ID;
	DATA->station->traverse(countStation, pID);
	dOut = new int[_N];
	DATA->station->traverse(addStation, pID);
	dOut -= _N;
	pOutput = (int**)dOut;
}

void addLine(L1Item<TLine>*& line)
{
	*dOut = line->ID;
	dOut++;
}
void findCityName(L1Item<TCity>*& city, void* pParam)
{
	if (city->data.cityName == *(string*)pParam)
	{
		_N = city->data.lineCity->getSize();
		dOut = new int[_N];
		city->data.lineCity->traverse(addLine);
		dOut -= _N;
		city = NULL;
	}
}
void LLC(void* pData, void*& pOutput, string city_name)
{
	_N = 0;
	void* pParam = &city_name;
	DATA->city->traverse(findCityName, pParam);
	pOutput = (int**)dOut;

}

void addStationLine(L1Item<int>*& station)
{
	*dOut = station->ID;
	dOut++;
}
void findLineID(L1Item<TLine>*& line, void* pParam)
{
	if (line->ID == *(int*)pParam)
	{
		_N = line->data.stationLine->getSize();
		dOut = new int[_N];
		line->data.stationLine->traverse(addStationLine);
		dOut -= _N;
		line = NULL;
	}
}
void findLineID(L1Item<TCity>*& city, void* pParam)
{
	if (city->data.lineCity != NULL)
	{
		city->data.lineCity->traverse(findLineID, pParam);
	}
}
void LSL(void* pData, void*& pOutput, int line_id)
{
	_N = 0;
	void* pParam = &line_id;
	DATA->city->traverse(findLineID, pParam);
	pOutput = (int**)dOut;
}

void _FC(L1Item<TCity>*& city, void* pParam)
{
	if (city->data.cityName == *(string*)pParam)
	{
		*dOut = city->ID;
		city = NULL;
	}
}
void FC(void* pData, void*& pOutput, string city_name)
{
	_N = 1;
	dOut = new int(-1);
	void* pParam = &city_name;
	DATA->city->traverse(_FC, pParam);
	pOutput = (int*)dOut;
}

void _FS(L1Item<TStation>*& station, void* pParam)
{
	if (station->data.name == *(string*)pParam)
	{
		*dOut = station->ID;
		station = NULL;
	}
}
void FS(void* pData, void*& pOutput, string station_name)
{
	_N = 1;
	dOut = new int(-1);
	void* pParam = &station_name;
	DATA->station->traverse(_FS, pParam);
	pOutput = (int*)dOut;
}

void findGeoID(L1Item<string>*& geo, void* pParam)
{
	if (geo->data == *(string*)pParam)
	{
		*dOut = geo->ID;
		geo = NULL;
	}
}
void findStationID(L1Item<TStation>*& station, void* pParam)
{
	if (station->ID == *(int*)pParam)
	{
		_N = station->data.cityID;
		*sOut = station->data.geo;
		station = NULL;
	}
}
void SLP(void* pData, void*& pOutput, int station_id, int track_id)
{
	string geoTemp;
	void* pParam = &station_id;
	DATA->station->traverse(findStationID, pParam);
	string geo = *sOut;
	pParam = &geo;
	int cityID = _N;
	_N = 1;
	dOut = new int(-1);
	try
	{
		DATA->city->atID(cityID).trackCity->atID(track_id).geometry->traverse(findGeoID, pParam);
	}
	catch (const DSAException)
	{
		return;
	}
	pOutput = (int*)dOut;
}

TStation readCsv(void* pData, string csv)
{
	TStation newStation;
	if (csv.empty())
	{
		throw "Empty Line!";
	}
	string tmp;
	tmp = csv.substr(0, csv.find(','));
	if (tmp[0] == '\"')
	{
		tmp.replace(0, 1, "");
		tmp.pop_back();
	}
	newStation.name = tmp;
	csv.replace(0, csv.find(",P") + 7, "");
	tmp = csv.substr(0, csv.find("),"));
	newStation.geo = tmp;
	csv.replace(0, csv.find("),") + 2, "");
	tmp = csv.substr(0, csv.find(','));
	newStation.build = tmp.empty() ? 0 : stoi(tmp);
	csv.replace(0, csv.find(',') + 1, "");
	tmp = csv.substr(0, csv.find(','));
	newStation.opening = tmp.empty() ? 0 : stoi(tmp);
	csv.replace(0, csv.find(',') + 1, "");
	tmp = csv.substr(0, csv.find(','));
	newStation.closure = tmp.empty() ? 0 : stoi(csv);
	return newStation;
}
void IS(void* pData, void*& pOutput, string csv)
{
	_N = 1;
	TStation newStation;
	try
	{
		newStation = readCsv(pData, csv);
	}
	catch (const char*)
	{
		dOut = new int(-1);
		pOutput = &dOut;
		return;
	}
	DATA->maxStationID++;
	int stationID = DATA->maxStationID;
	DATA->station->push_back(newStation, stationID);
	dOut = new int(stationID);
	pOutput = (int*)dOut;
}

void fStaionID(L1Item<TLine>*& line, void* pParam)
{
	int idx = -1;
	if (line->data.stationLine != NULL)
	{
		idx = line->data.stationLine->findIDX(*(int*)pParam);
		if (idx == -1)
		{
			return;
		}
		else
		{
			line->data.stationLine->remove(idx);
			line = NULL;
		}
	}
}
void RS(void* pData, void*& pOutput, int station_id)
{
	_N = 1;
	int idx = DATA->station->findIDX(station_id);
	int cityID = DATA->station->atID(station_id).cityID;
	dOut = new int(-1);
	pOutput = (int*)dOut;
	if (idx == -1)
	{
		return;
	}
	*dOut = DATA->station->remove(idx);
	if (station_id == DATA->maxStationID)
	{
		DATA->maxStationID = DATA->station->maxID();
	}
	void* pParam = &station_id;
	DATA->city->atID(cityID).lineCity->traverse(fStaionID, pParam);
	pOutput = (int*)dOut;
}

void US(void* pData, void*& pOutput, int station_id, string csv)
{
	_N = 1;
	TStation newStation;
	try
	{
		newStation = readCsv(pData, csv);
	}
	catch (const char*)
	{
		dOut = new int(-1);
		pOutput = (int*)dOut;
		return;
	}
	try
	{
		void* pTemp = &DATA->station->atID(station_id);
		(*(TStation*)pTemp).build = newStation.build;
		(*(TStation*)pTemp).geo = newStation.geo;
		(*(TStation*)pTemp).closure = newStation.closure;
		(*(TStation*)pTemp).name = newStation.name;
		(*(TStation*)pTemp).opening = newStation.opening;
		dOut = new int(0);
		pOutput = (int*)dOut;
	}
	catch (const DSAException)
	{
		dOut = new int(-1);
		pOutput = (int*)dOut;
		return;
	}

}

void lineID2cityID(L1Item<TCity>*& city, void* pParam)
{
	if (city->data.lineCity != NULL)
	{
		_N = city->data.lineCity->findIDX(*(int*)pParam);
		if (_N != -1)
		{
			_N = city->ID;
			city = NULL;
			return;
		}
	}
}
void ISL(void* pData, void*& pOutput, int station_id, int line_id, int p_i)
{
	_N = -1;
	dOut = new int(-1);
	void* pParam = &line_id;
	DATA->city->traverse(lineID2cityID, pParam);
	if (_N == -1)
	{
		_N = 1;
		pOutput = (int*)dOut;
		*dOut = 0;
		return;
	}
	void* pTemp = &DATA->city->atID(_N).lineCity->atID(line_id).stationLine;
	_N = 1;
	if (DTemp(L1List<int>, pTemp) == NULL)
	{
		if (p_i == 0)
		{
			DTemp(L1List<int>, pTemp) = new L1List<int>();
		}
		else
		{
			pOutput = (int*)dOut;
			return;
		}
	}
	if (DTemp(L1List<int>,pTemp)->at(p_i) != station_id)
	{
		DTemp(L1List<int>, pTemp)->insert(p_i, station_id, station_id);
	}
	else
	{
		pOutput = (int*)dOut;
		return;
	}
	*dOut = 0;
	pOutput = (int*)dOut;
}

void RSL(void* pData, void*& pOutput, int station_id, int line_id)
{
	dOut = new int(-1);
	void* pParam = &line_id;
	DATA->city->traverse(lineID2cityID, pParam);
	if (_N == -1)
	{
		_N = 1;
		*dOut = -1;
		pOutput = (int*)dOut;
		return;
	}
	void* pTemp = &DATA->city->atID(_N).lineCity->atID(line_id).stationLine;
	int idx = DTemp(L1List<int>, pTemp)->findIDX(station_id);
	*dOut = DTemp(L1List<int>, pTemp)->remove(idx);
	pOutput = (int*)dOut;
	_N = 1;
}

string findInfo(string& pRequest)
{
	int pos1 = pRequest.find('<') + 1;
	int pos2 = pRequest.find('>') - pos1;
	string info = pRequest.substr(pos1,pos2);
	pRequest.replace(0, pos2 + pos1 + 1,"");
	return info;
}
int  findRequest(string pRequest)
{
	string _pRequest = pRequest;
	if (pRequest[0] == 'C')
	{
		if (pRequest[3] == '<')
		{
			sOut = new string(findInfo(_pRequest));
			return 2;
		}
		return 1;
	}
	else if (pRequest[0] == 'L')
	{
		sOut = new string(findInfo(_pRequest));
		if (pRequest[1] == 'S')
		{
			if (pRequest[2] == 'C')
			{
				return 3;
			}
			else if (pRequest[2] == 'L')
			{
				return 5;
			}
		}
		else if ((pRequest[1] == 'L') && (pRequest[2] == 'C'))
		{
			return 4;
		}
	}
	else if (pRequest[0] == 'F')
	{
		sOut = new string(findInfo(_pRequest));
		if (pRequest[1] == 'C')
		{
			return 6;
		}
		else if (pRequest[1] == 'S')
		{
			return 7;
		}
	}
	else if (pRequest[0] == 'S' && pRequest[1] == 'L' && pRequest[2] == 'P')
	{
		sOut = new string[2];
		sOut[0] = findInfo(_pRequest);
		sOut[1] = findInfo(_pRequest);
		return 8;
	}
	else if (pRequest[0] == 'I')
	{
		if (pRequest[1] == 'S' && pRequest[2] != 'L')
		{
			sOut = new string(findInfo(_pRequest));
			return 9;
		}
		if (pRequest[1] == 'S' && pRequest[2] == 'L')
		{
			sOut = new string[3];
			sOut[0] = findInfo(_pRequest);
			sOut[1] = findInfo(_pRequest);
			sOut[2] = findInfo(_pRequest);
			return 10;
		}
	}
	else if (pRequest[0] == 'R')
	{
		if (pRequest[1] == 'S' && pRequest[2] != 'L')
		{
			sOut = new string(findInfo(_pRequest));
			return 11;
		}
		if (pRequest[1] == 'S' && pRequest[2] == 'L')
		{
			sOut = new string[2];
			sOut[0] = findInfo(_pRequest);
			sOut[1] = findInfo(_pRequest);
			return 12;
		}
	}
	else if (pRequest[0] == 'U' && pRequest[1] == 'S')
	{
		sOut = new string[2];
		sOut[0] = findInfo(_pRequest);
		sOut[1] = findInfo(_pRequest);
		return 13;
	}
	return 0;
}
