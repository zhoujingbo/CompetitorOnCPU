//============================================================================
// Name        : RtreeIndex.cpp
// Author      : zhou jingbo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "spatialRtree/WrapperSpatialRtree.h"
#include "InvertedIndex/WrapperInvertedIndexMulDimMulDim.h"
#include "InvertedIndex/WrapperInvertedIndexTweet.h"

int main() {

	//WrapperSpatialRtree wsr;
	//wsr.run_spatialRtree();

	//WrapperInvertedIndexMulDim wii;
	//wii.run_topk();

	WrapperInvertedIndexTweet wit;
	wit.run_topk();



	return 0;
}
