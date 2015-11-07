/*
 * InvertedIndex.h
 *
 *  Created on: Oct 20, 2015
 *      Author: zhoujingbo
 */

#ifndef INVERTEDINDEX_INVERTEDINDEXMULDIMMULDIM_H_
#define INVERTEDINDEX_INVERTEDINDEXMULDIMMULDIM_H_

#include <vector>
#include <map>
#include <stdint.h>
#include <utility>


using namespace std;

typedef unsigned int T_KEY;
typedef unsigned int T_ID;
typedef unsigned int uint32;


class InvertedIndexTweet {
public:
	InvertedIndexTweet( );
	virtual ~InvertedIndexTweet();


	void buildIndex(vector<vector<int> > data);

	void scanIndex(vector<int>& query, map<T_ID,uint32>& counter);

	vector<pair<T_ID, uint32> > topkQuery(vector<int> query, uint32 k);
	vector<vector<pair<T_ID, uint32> > > topkQueries(vector<vector<int> >& queries,
			 uint32 k);

private:


	map<T_KEY, vector<T_ID> > invIdx;

	//uint32 valBits;
};

#endif /* INVERTEDINDEX_INVERTEDINDEXMULDIMMULDIM_H_ */
