#pragma once

#include "SmallestCostFlow.h"
#include "GenerateIntialSolutions.h"
#include <sys/timeb.h>
#include <time.h>

struct Solution
{
	FlowSolution flowSolution;
	UIntTable servers; // node id

	std::string to_string(const Graph &g) const;
};

namespace GeneticAlgorithm
{
	Solution generateSolution(std::vector<BoolTable> intialSolutions, unsigned long interval_ms, const Graph &g);

	namespace SubFun
	{
		inline unsigned long timeb2ms(const timeb &t);
		// to do
		static const unsigned long limit_time = 84000;
		static const double mutation_rate = 0.1;
		static const double cross_rate = 0.9;
		static const int pop_size = 50;
		static const int iteration = 30;
		static const int opt = 5;
	};
};