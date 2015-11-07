/*
 * InvertedIndex.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: zhoujingbo
 */

#include "InvertedIndexTweet.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>

InvertedIndexTweet::InvertedIndexTweet() {
	// TODO Auto-generated constructor stub
	//this->max_word_perTweet = max_word_perTweet;
}

InvertedIndexTweet::~InvertedIndexTweet() {
	// TODO Auto-generated destructor stub
}

T_KEY inline getKey(uint32 val){

	T_KEY key = val;

	return key;
}

void InvertedIndexTweet::buildIndex(vector<vector<int> > data){

	std::map<T_KEY,vector<T_ID> >::iterator it;

	for(size_t i=0;i<data.size();i++){
		for(size_t j=0;j<data[i].size();j++){
			T_KEY key = getKey(data[i][j]);
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


void InvertedIndexTweet::scanIndex(vector<int>& query, map<T_ID,uint32>& counter){

	std::map<T_KEY,vector<T_ID> >::iterator it;
	std::map<T_ID,uint32>::iterator cit;

	for(int qk=0;qk<query.size();qk++){

		T_KEY key = getKey(query[qk]);
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



bool compfunc_count(pair<const T_ID, uint32> const & l,
        pair<const T_ID, uint32> const & r) {
         return l.second > r.second;
 }

vector<pair<T_ID, uint32> > InvertedIndexTweet::topkQuery(vector<int> query, uint32 k){

	map<T_ID,uint32> counter;
	scanIndex(query, counter);

	vector<pair<T_ID, uint32> > topk(k);

	partial_sort_copy(counter.begin(),
					counter.end(),
					topk.begin(),
					topk.end(),
					compfunc_count);

	//cout<<"topk.size():"<<topk.size()<<endl;
	//cout<<"print results:"<<endl;
	//print result
	//printf("order	id	count\n");
	//for(int i=0;i<topk.size();i++){
	//	printf("[%d]	%d	%d\n",i,topk[i].first,topk[i].second);
	//}
	//end print result

	return topk;
}



vector<vector<pair<T_ID, uint32> > > InvertedIndexTweet::topkQueries(vector<vector<int> >& queries,
		 uint32 k){

	vector<vector<pair<T_ID, uint32> > > res;
	for(uint32 i=0;i<queries.size();i++){
		res.push_back(topkQuery(queries[i], k));
	}
	return res;
}
