// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <climits>
#include <chrono>
#include <queue>
#include <bitset>
#include <sparsehash/dense_hash_map>
#include <boost\chrono.hpp>


#include "MyTimer.h"
#include "PairRecord.h"
#include "SymbolRecord.h"
#include "PairTracker.h"
#include "Pair.h"
#include "TestSuite.h"
#include "Conditions.h"
#include "CompactPair.h"
#include "GammaCode.h"
#include "Initializer.h"
#include "MyTest.h"
#include "Compaction.h"
#include "Dictionary.h"
#include "AlgorithmP.h"
#include "Algorithm.h"
#include "MyBitset.h"
#include "HuffmanNode.h"
#include "Huffman.h"
#include "Outputter.h"
#include "Decoder.h"

//Constants
const unsigned long initialSymbolValue = 130561;//max of Cantor is 2*x*(x+1) which is 130560 for x = 256
const int cutoffValue = 28; //Must be >= 2