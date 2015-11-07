/*
 * WrapperInvertedIndex.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: zhoujingbo
 */

#include "WrapperInvertedIndexMulDimMulDim.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <sys/time.h>

#include "../tools/DataProcess.h"
#include "InvertedIndexMulDimMulDim.h"

WrapperInvertedIndexMulDim::WrapperInvertedIndexMulDim() {
	// TODO Auto-generated constructor stub

}

WrapperInvertedIndexMulDim::~WrapperInvertedIndexMulDim() {
	// TODO Auto-generated destructor stub
}





void topkQuery(vector<vector<int> >& data, vector<vector<int> >& queries, int range, uint k){

	InvertedIndexMulDim invIdx;

	struct timeval tim;
	double t_start, t_end;
	gettimeofday(&tim, NULL);
	t_start = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout<<"start building index with data size:"<<data.size()<<endl;
	invIdx.buildIndex(data);
	cout<<"end building index"<<endl;
	gettimeofday(&tim, NULL);
	t_end = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout << "running time of building index is:" << t_end - t_start << " s" << endl;

	gettimeofday(&tim, NULL);
	t_start = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout<<"start query with query size:"<<queries.size()<<endl;
	invIdx.topkQueries(queries,range,k);
	gettimeofday(&tim, NULL);
	t_end = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout << "total query number:"<<queries.size() <<" running time is:" << t_end - t_start << " s" << endl;
}

void rangeQuery(vector<vector<int> >& data, vector<vector<int> >& queries, int range, int threshold){

	InvertedIndexMulDim invIdx;

	struct timeval tim;
	double t_start, t_end;
	gettimeofday(&tim, NULL);
	t_start = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout<<"start building index with data size:"<<data.size()<<endl;
	invIdx.buildIndex(data);
	cout<<"end building index"<<endl;
	gettimeofday(&tim, NULL);
	t_end = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout << "running time of building index is:" << t_end - t_start << " s" << endl;

	gettimeofday(&tim, NULL);
	t_start = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout<<"start query with query size:"<<queries.size()<<endl;
	invIdx.rangeQueries(queries,range,threshold);
	gettimeofday(&tim, NULL);
	t_end = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout << "total query number:"<<queries.size() <<" running time is:" << t_end - t_start << " s" << endl;
}


void topkQueryonData(){

	string prefix = "/media/hd1/home/zhoujingbo/data/";
	string dataFile = prefix+"pascal/ocr/hashed/numCF25/ocr_trn_dataSize-3400000_numCF-25_numDim-1155_r-2.65_domainBits-13.csv";
	string queryFile = prefix+"pascal/ocr/hashed/numCF25/ocr_tst_dataSize-100000_numCF-25_numDim-1155_r-2.65_domainBits-13.csv";
	uint topk = 100;
	int range = 3072;

	vector<vector<int> > data;
	vector<vector<int> > queries;

	DataProcess dp;
	cout<<"start loading data"<<endl;
	dp.ReadFileInt(dataFile.c_str(), data);
	dp.ReadFileInt(dataFile.c_str(), queries, 10);
	cout<<"end loading data"<<endl;
	topkQuery(data, queries,range,topk);
}



void rangeQueryOnData(){
	string prefix = "/media/hd1/home/zhoujingbo/data/";
	string dataFile = prefix+"pascal/ocr/hashed/numCF25/ocr_trn_dataSize-3400000_numCF-25_numDim-1155_r-2.65_domainBits-13.csv";
	string queryFile = prefix+"pascal/ocr/hashed/numCF25/ocr_tst_dataSize-100000_numCF-25_numDim-1155_r-2.65_domainBits-13.csv";
	uint threshold = 25;
	int range = 3072;
	uint queryNum = 10;

	vector<vector<int> > data;
	vector<vector<int> > queries;

	DataProcess dp;
	cout<<"start loading data"<<endl;
	dp.ReadFileInt(dataFile.c_str(), data);
	dp.ReadFileInt(dataFile.c_str(), queries, queryNum);
	cout<<"end loading data"<<endl;
	rangeQuery(data, queries,range,threshold);
}

void WrapperInvertedIndexMulDim:: run_range(){
	//test_toy();
	rangeQueryOnData();

}

void WrapperInvertedIndexMulDim:: run_topk(){
	//test_toy();
	topkQueryonData();


}
