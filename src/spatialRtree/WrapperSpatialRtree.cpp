/*
 * WrapperSpatialRtree.cpp
 *
 *  Created on: Oct 6, 2015
 *      Author: zhoujingbo
 */

#include "WrapperSpatialRtree.h"

#include <vector>
#include <iostream>
using namespace std;

#include "SpatialRtree.h"

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

void WrapperSpatialRtree:: run_spatialRtree(){
	test_toy();

}
