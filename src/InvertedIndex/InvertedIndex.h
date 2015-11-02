/*
 * InvertedIndex.h
 *
 *  Created on: Oct 20, 2015
 *      Author: zhoujingbo
 */

#ifndef INVERTEDINDEX_INVERTEDINDEX_H_
#define INVERTEDINDEX_INVERTEDINDEX_H_

#include <vector>
#include <map>
#include <stdint.h>
#include <utility>


using namespace std;

typedef unsigned int T_KEY;
typedef unsigned int T_ID;
typedef unsigned int uint32;


class InvertedIndex {
public:
	InvertedIndex();
	virtual ~InvertedIndex();

	void buildIndex(vector<vector<int> > data);

	vector<pair<T_ID, uint32> > topkQuery(vector<int>& queryLow, vector<int>& queryHigh, uint32 k);
	vector<vector<pair<T_ID, uint32> > > topkQueries(vector<vector<int> >& queriesLow,
			vector<vector<int> >& queriesHigh, uint32 k);

	vector<pair<T_ID, uint32> > topkQuery(vector<int>& query, int range, uint32 k);
	vector<vector<pair<T_ID, uint32> > > topkQueries(vector<vector<int> >& queries,
			int range, uint32 k);

	vector<pair<T_ID, uint32> > rangeQuery(vector<int>& queryLow, vector<int>& queryHigh, uint32 threshold);
	vector<vector<pair<T_ID, uint32> > > rangeQueries(vector<vector<int> >& queriesLow,
			vector<vector<int> >& queriesHigh, uint32 threshold);

	vector<pair<T_ID, uint32> > rangeQuery(vector<int>& query, int range, uint32 threshold);
	vector<vector<pair<T_ID, uint32> > > rangeQueries(vector<vector<int> >& query,
			int range, uint32 threshold);

private:

	void scanIndex(vector<int>& queryLow, vector<int>& queryHigh, map<T_ID,uint32>& counter);

	map<T_KEY, vector<T_ID> > invIdx;

	uint32 valBits;
};

#endif /* INVERTEDINDEX_INVERTEDINDEX_H_ */
