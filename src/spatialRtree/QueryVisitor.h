/*
 * QueryVisitor.h
 *
 *  Created on: Oct 7, 2015
 *      Author: zhoujingbo
 */

#ifndef SPATIALRTREE_QUERYVISITOR_H_
#define SPATIALRTREE_QUERYVISITOR_H_

// include library header file.
#include <spatialindex/SpatialIndex.h>
using namespace SpatialIndex;

#include <iostream>
using namespace std;


class QueryVisitor : public IVisitor{
public:
	QueryVisitor(std::vector<id_type>& outRes): m_indexIO(0), m_leafIO(0), res(outRes){

	}
	virtual ~QueryVisitor(){

	}

	void visitNode(const INode& n){
		if (n.isLeaf()) m_leafIO++;
			else m_indexIO++;
	}

	void visitData(const IData& d) {

		res.push_back(d.getIdentifier());

	}

	void visitData(std::vector<const IData*>& v){
		for (size_t i=0;i<v.size();i++){
			res.push_back(v[i]->getIdentifier());
		}

	}


public:
	size_t m_indexIO;
	size_t m_leafIO;

	std::vector<id_type>& res;
};

#endif /* SPATIALRTREE_QUERYVISITOR_H_ */
