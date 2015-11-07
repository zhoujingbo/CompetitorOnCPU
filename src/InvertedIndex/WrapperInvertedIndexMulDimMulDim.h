/*
 * WrapperInvertedIndex.h
 *
 *  Created on: Oct 23, 2015
 *      Author: zhoujingbo
 */

#ifndef INVERTEDINDEX_WRAPPERINVERTEDINDEXMULDIMMULDIM_H_
#define INVERTEDINDEX_WRAPPERINVERTEDINDEXMULDIMMULDIM_H_

class WrapperInvertedIndexMulDim {
public:
	WrapperInvertedIndexMulDim();
	virtual ~WrapperInvertedIndexMulDim();

	void run_topk();
	void run_range();
};

#endif /* INVERTEDINDEX_WRAPPERINVERTEDINDEXMULDIMMULDIM_H_ */
