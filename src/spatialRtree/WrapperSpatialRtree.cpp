/*
 * WrapperSpatialRtree.cpp
 *
 *  Created on: Oct 6, 2015
 *      Author: zhoujingbo
 */

#include "WrapperSpatialRtree.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <sys/time.h>
using namespace std;

#include "SpatialRtree.h"
using namespace SpatialIndex;

#include "../tools/DataProcess.h"

WrapperSpatialRtree::WrapperSpatialRtree() {
	// TODO Auto-generated constructor stub

}

WrapperSpatialRtree::~WrapperSpatialRtree() {
	// TODO Auto-generated destructor stub
}

void test_toy(){
	cout<<"prepare toy data for testing"<<endl;
	int dim = 500;
	int N = 50000;

	vector<vector<double> > data;

	vector<double> qup;
	vector<double> qlow;
	vector<id_type> qres;

	int qid = 100;
	for (int i=0;i<N;i++){
		vector<double> vi;
		for(int j=0;j<dim;j++){
			vi.push_back(j+i);

			if(i==qid){
				qlow.push_back(j-10+i);
				qup.push_back(j+10+i);

			}
		}
		data.push_back(vi);
	}

	SpatialRtree rt;
	cout<<"start loading data"<<endl;
	rt.loadData(data);
	cout<<"end loading data"<<endl;



//	int qid = 100;
//	for(size_t i=0;i<dim;i++){
//		qup.push_back(i+10+qid);
//		qlow.push_back(i-10+qid);
//	}
	rt.rangeQuery(qlow,qup,qres);

	cout<<"finish single query with res.size():"<<qres.size()<<endl;


}

void RangeQuery(vector<vector<double> >& data, vector<vector<double> >& queriesLow, vector<vector<double> >& queriesHigh){
	SpatialRtree rt;

	struct timeval tim;
	double t_start, t_end;
	gettimeofday(&tim, NULL);
	t_start = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout<<"start loading data with size:"<<data.size()<<endl;
	rt.loadData(data);
	cout<<"end loading data"<<endl;
	gettimeofday(&tim, NULL);
	t_end = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout << "running time of loading data is:" << t_end - t_start << " s" << endl;


	gettimeofday(&tim, NULL);
	t_start = tim.tv_sec + (tim.tv_usec / 1000000.0);
	for(int i=0;i<queriesLow.size();i++){
		vector<id_type> qres;
		rt.rangeQuery(queriesLow[i],queriesHigh[i],qres);
		//if(i%100==0){
			cout<<"\r processed query:"<<i<<" with query results size:"<<qres.size();
		//}
	}
	gettimeofday(&tim, NULL);
	t_end = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout << "total query number:"<<queriesLow.size() <<" running time is:" << t_end - t_start << " s" << endl;
}


void RangeQuery(vector<vector<double> >& data, vector<vector<double> >& queries, double delta){
	vector<vector<double> > queriesLow(queries.size());
	vector<vector<double> > queriesHigh(queries.size());

	for(size_t i=0;i<queries.size();i++){
		for(size_t j=0;j<queries[i].size();j++){
			queriesLow[i].push_back(queries[i][j]-delta);
			queriesHigh[i].push_back(queries[i][j]+delta);
		}
	}

	RangeQuery(data, queriesLow, queriesHigh);
}

void RangeQueryonData(){

	string prefix = "/media/hd1/home/zhoujingbo/data/";
	string dataFile = prefix+"pascal/ocr/hashed/numCF25/ocr_trn_dataSize-3400000_numCF-25_numDim-1155_r-2.65_domainBits-13.csv";
	string queryFile = prefix+"pascal/ocr/hashed/numCF25/ocr_tst_dataSize-100000_numCF-25_numDim-1155_r-2.65_domainBits-13.csv";
	double delta = 3072; //0.1*2^13/2

	vector<vector<double> > data;
	vector<vector<double> > queries;

	DataProcess dp;
	dp.ReadFileDouble(dataFile.c_str(), data);
	dp.ReadFileDouble(dataFile.c_str(), queries, 2500);

	RangeQuery(data, queries,delta);


}

void WrapperSpatialRtree:: run_spatialRtree(){
	//test_toy();

	RangeQueryonData();

}
