/*
 * SpatialRtree.h
 *
 *  Created on: Oct 5, 2015
 *      Author: zhoujingbo
 */

#ifndef SPATIALRTREE_SPATIALRTREE_H_
#define SPATIALRTREE_SPATIALRTREE_H_

#include <vector>
using namespace std;

// include library header file.
#include <spatialindex/SpatialIndex.h>
using namespace SpatialIndex;

//This is a Rstar Tree
class SpatialRtree {
public:
	SpatialRtree();
	virtual ~SpatialRtree();

	void loadData(vector<vector<double> > data);

	void rangeQuery(vector<double>& low, vector<double>& high, vector<id_type>& res);
	void rangeQueries(vector<vector<double> >& lows, vector<vector<double> >& high, vector<vector<id_type> >& res);

	IStorageManager* msm;
	ISpatialIndex* stree;

};

#endif /* SPATIALRTREE_SPATIALRTREE_H_ */
