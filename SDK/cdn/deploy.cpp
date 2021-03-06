#include "deploy.h"
#include "graph.h"
#include "GenerateIntialSolutions.h"
#include "GeneticAlgorithm.h"
#include <stdio.h>

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num, char * filename)
{
	timeb startTime;
	ftime(&startTime);
	unsigned int interval_ms(timeb2ms(startTime));
	Graph graph(topo);
	std::vector<BoolTable> intialSolutions(GenerateIntialSolutions::getIntialSolutions(graph));
	ftime(&startTime);
	interval_ms += timeb2ms(startTime);
	Solution solution(GeneticAlgorithm::generateSolution(intialSolutions, interval_ms, graph));
	/*Solution solution{ SmallestCostFlow::getSmallestCostFlow(intialSolutions[0], graph) };
	for (unsigned int i(0), j(intialSolutions[0].size()); i != j; ++i)
	{
		if (intialSolutions[0][i])
			solution.servers.push_back(i);
	}*/
	std::string solution_str(solution.to_string(graph));

	// 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
	write_result(solution_str.c_str(), filename);
}

unsigned long timeb2ms(const timeb & t)
{
	static int ms = t.millitm;
	static unsigned long s = t.time;
	int out_ms = t.millitm - ms;
	unsigned long out_s = t.time - s;
	ms = t.millitm;
	s = t.time;

	return out_s * 1000 + out_ms;
}