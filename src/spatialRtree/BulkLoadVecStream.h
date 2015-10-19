/*
 * BulkLoadStream.h
 *
 *  Created on: Oct 6, 2015
 *      Author: zhoujingbo
 */

#ifndef SPATIALRTREE_BULKLOADVECSTREAM_H_
#define SPATIALRTREE_BULKLOADVECSTREAM_H_

#include <vector>
#include <iostream>
using namespace std;


// include library header file.
#include <spatialindex/SpatialIndex.h>

using namespace SpatialIndex;

#define INSERT 1
#define DELETE 0
#define QUERY 2

class BulkLoadVecStream : public IDataStream
{
public:
	BulkLoadVecStream(vector<vector<double> >& inData) : m_pNext(0),data(inData), vec_idx(0)
	{
		readNextEntry();


	}

	virtual ~BulkLoadVecStream()
	{
		if (m_pNext != 0) delete m_pNext;
	}

	virtual IData* getNext()
	{
		if (m_pNext == 0) return 0;

		RTree::Data* ret = m_pNext;
		m_pNext = 0;
		readNextEntry();
		return ret;
	}

	virtual bool hasNext()
	{
		return (m_pNext != 0);
	}

	virtual uint32_t size()
	{
		throw Tools::NotSupportedException("Operation not supported.");
	}

	virtual void rewind()
	{
		if (m_pNext != 0)
		{
			delete m_pNext;
			m_pNext = 0;
		}
		vec_idx = 0;
		readNextEntry();
	}

	void readNextEntry()
	{
		if(vec_idx<data.size()){
			size_t dim = data[vec_idx].size();
			id_type id = vec_idx;
			Point p(data[vec_idx].data(),dim);
			Region r(p, p);
			m_pNext = new RTree::Data(0, NULL, r, id);

		}
		vec_idx++;
	}

	std::ifstream m_fin;
	size_t vec_idx;
	vector<vector<double> >& data;
	RTree::Data* m_pNext;
};


#endif /* SPATIALRTREE_BULKLOADVECSTREAM_H_ */
