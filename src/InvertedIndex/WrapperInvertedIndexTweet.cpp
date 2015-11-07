/*
 * WrapperInvertedIndexTweet.cpp
 *
 *  Created on: Nov 7, 2015
 *      Author: zhoujingbo
 */

#include "WrapperInvertedIndexTweet.h"


#include <vector>
#include <iostream>
#include <time.h>
#include <sys/time.h>

#include "../tools/DataProcess.h"
#include "InvertedIndexTweet.h"

WrapperInvertedIndexTweet::WrapperInvertedIndexTweet() {
	// TODO Auto-generated constructor stub

}

WrapperInvertedIndexTweet::~WrapperInvertedIndexTweet() {
	// TODO Auto-generated destructor stub
}



void topkQueryTweet(vector<vector<int> >& data, vector<vector<int> >& queries, uint k){

	InvertedIndexTweet invIdx;

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
	invIdx.topkQueries(queries,k);
	gettimeofday(&tim, NULL);
	t_end = tim.tv_sec + (tim.tv_usec / 1000000.0);
	cout << "total query number:"<<queries.size() <<" running time is:" << t_end - t_start << " s" << endl;
}

void topkQueryonTweetData(){

	string prefix = "data/tweet/";
	string dataFile = prefix+"tweets_4k.csv";
	string queryFile = prefix+"tweets_4k.csv";
	int queryNum = 5;
	uint topk = 5;

	vector<vector<int> > data;
	vector<vector<int> > queries;

	DataProcess dp;
	cout<<"start loading data"<<endl;
	dp.ReadFileInt(dataFile.c_str(), data);
	dp.ReadFileInt(dataFile.c_str(), queries, queryNum);
	cout<<"end loading data"<<endl;
	topkQueryTweet(data, queries,topk);
}


void WrapperInvertedIndexTweet::runTweetMatchKNNOnCPU_exp(){
		int topk = 100;
		int queryNum[] = {1,5,10,1000};//if set queryNum, set two 1, because first lanch of GPU require large time


		string datafile =  "data/tweet/tweets_4k.csv";//the tweets data
		string queryfile = "data/tweet/tweets_4k.csv";

		DataProcess dp;
		vector<vector<int> > data;
		cout<<"start loading data"<<endl;
		dp.ReadFileInt(datafile.c_str(), data);
		cout<<"end loading data"<<endl;

		for(int i=0;i<sizeof(queryNum)/sizeof(int);i++){
			cout<<endl<<"//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
			cout<<" query number:"<<queryNum[i]<<endl;
			vector<vector<int> > queries;
			dp.ReadFileInt(queryfile.c_str(), queries, queryNum[i]);

			topkQueryTweet( data,  queries, topk );
			cout<<"//++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		}
		cout<<"//**************************************************************"<<endl<<endl;



}


void WrapperInvertedIndexTweet:: run_topk(){
	//test_toy();
	//topkQueryonTweetData();
	runTweetMatchKNNOnCPU_exp();


}
