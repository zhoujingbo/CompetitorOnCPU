/*
 * InvertedIndex.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: zhoujingbo
 */

#include "InvertedIndex.h"

#include <algorithm>
#include <iostream>

InvertedIndex::InvertedIndex() {
	// TODO Auto-generated constructor stub
	valBits = 22;
}

InvertedIndex::~InvertedIndex() {
	// TODO Auto-generated destructor stub
}

T_KEY inline getKey(uint32 dim, uint32 val, uint32 valBits){

	T_KEY key = (dim<<valBits)+val;

	return key;
}

void InvertedIndex::buildIndex(vector<vector<int> > data){

	std::map<T_KEY,vector<T_ID> >::iterator it;

	for(size_t i=0;i<data.size();i++){
		for(size_t j=0;j<data[i].size();j++){
			T_KEY key = getKey(j,data[i][j],this->valBits);
			it=this->invIdx.find(key);
			if(it!=invIdx.end()){
				it->second.push_back(i);
			}else{
				vector<T_ID> list;
				list.push_back(i);
				invIdx[key] = list;
			}
		}
	}

}


void InvertedIndex::scanIndex(vector<int>& queryLow, vector<int>& queryHigh, map<T_ID,uint32>& counter){

	std::map<T_KEY,vector<T_ID> >::iterator it;
	std::map<T_ID,uint32>::iterator cit;


		for(size_t i=0;i<queryLow.size();i++){

			for(int qk=queryLow[i];qk<=queryHigh[i];qk++){

				if(qk<0) continue;

				T_KEY key = getKey(i,qk,this->valBits);
				it = this->invIdx.find(key);

				if(it!=invIdx.end()){
					vector<T_ID>& list = it->second;
					for(size_t j = 0;j<it->second.size();j++){
						cit = counter.find(list[j]);
						if(cit!=counter.end()){
							counter[list[j]]+=1;
						}else{
							counter[list[j]]=1;
						}

					}
				}
			}

		}

}

vector<pair<T_ID, uint32> > InvertedIndex::rangeQuery(vector<int>& queryLow, vector<int>& queryHigh, uint32 threshold){

	map<T_ID,uint32> counter;
	scanIndex(queryLow, queryHigh, counter);
	std::map<T_ID,uint32>::iterator cit;
	vector<pair<T_ID, uint32> > res;

	for(cit=counter.begin();cit!=counter.end();cit++){
		if(cit->second>=threshold){
			res.push_back(pair<T_ID,uint32>(cit->first,cit->second));
		}
	}

	cout<<"topk.size():"<<res.size()<<endl;

	return res;
}

vector<pair<T_ID, uint32> > InvertedIndex::rangeQuery(vector<int>& query, int range, uint32 threshold){

	vector<int> queryLow(query.size());
	vector<int> queryHigh(query.size());

	for(uint i=0;i<query.size();i++){
		queryLow[i] = query[i] - range;
		queryHigh[i] = query[i] +range;
	}

	return rangeQuery(queryLow, queryHigh, threshold);
}

vector<pair<T_ID, uint32> > InvertedIndex::topkQuery(vector<int>& query, int range, uint32 k){

	vector<int> queryLow(query.size());
	vector<int> queryHigh(query.size());

	for(uint i=0;i<query.size();i++){
		queryLow[i] = query[i] - range;
		queryHigh[i] = query[i] +range;
	}

	return topkQuery(queryLow, queryHigh, k);
}



bool compfunc(pair<const T_ID, uint32> const & l,
        pair<const T_ID, uint32> const & r) {
         return l.second > r.second;
 }

vector<pair<T_ID, uint32> > InvertedIndex::topkQuery(vector<int>& queryLow, vector<int>& queryHigh, uint32 k){

	map<T_ID,uint32> counter;
	scanIndex(queryLow, queryHigh, counter);

	vector<pair<T_ID, uint32> > topk(k);

	partial_sort_copy(counter.begin(),
					counter.end(),
					topk.begin(),
					topk.end(),
					compfunc);

	cout<<"topk.size():"<<topk.size()<<endl;

	return topk;
}

vector<vector<pair<T_ID, uint32> > > InvertedIndex::topkQueries(vector<vector<int> >& queriesLow,
		vector<vector<int> >& queriesHigh, uint32 k){

	vector<vector<pair<T_ID, uint32> > > res;
	for(uint32 i=0;i<queriesLow.size();i++){
		res.push_back(topkQuery(queriesLow[i],queriesHigh[i], k));
	}
	return res;
}

vector<vector<pair<T_ID, uint32> > > InvertedIndex::topkQueries(vector<vector<int> >& queries,
		int range, uint32 k){

	vector<vector<pair<T_ID, uint32> > > res;
	for(uint32 i=0;i<queries.size();i++){
		res.push_back(topkQuery(queries[i],range, k));
	}
	return res;
}

vector<vector<pair<T_ID, uint32> > > InvertedIndex::rangeQueries(vector<vector<int> >& queriesLow,
		vector<vector<int> >& queriesHigh, uint32 threshold){

	vector<vector<pair<T_ID, uint32> > > res;
	for(uint32 i=0;i<queriesLow.size();i++){
			res.push_back(rangeQuery(queriesLow[i],queriesHigh[i], threshold));
		}
	return res;

}


vector<vector<pair<T_ID, uint32> > > InvertedIndex::rangeQueries(vector<vector<int> >& query,
		int range, uint32 threshold){
	vector<vector<pair<T_ID, uint32> > > res;
		for(uint32 i=0;i<query.size();i++){
				res.push_back(rangeQuery(query[i],range, threshold));
		}
	return res;
}
