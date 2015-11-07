/*
 * WrapperInvertedIndexTweet.h
 *
 *  Created on: Nov 7, 2015
 *      Author: zhoujingbo
 */

#ifndef INVERTEDINDEX_WRAPPERINVERTEDINDEXTWEET_H_
#define INVERTEDINDEX_WRAPPERINVERTEDINDEXTWEET_H_

class WrapperInvertedIndexTweet {
public:
	WrapperInvertedIndexTweet();
	virtual ~WrapperInvertedIndexTweet();

	void runTweetMatchKNNOnCPU_exp();
	void run_topk();
};

#endif /* INVERTEDINDEX_WRAPPERINVERTEDINDEXTWEET_H_ */
