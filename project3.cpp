#include <iostream>
#include <list>

//============================_TASK_1_============================
void pushBackEndAverage(std::list<float>& n)
{
	float sum = 0;
	for (const float& v : n)
	{
		sum += v;
	}

	n.push_back(sum / n.size());

	std::cout << "{";
	for (auto print : n)
		std::cout << " " << print << " ";
	std::cout << "}" << std::endl;

}

//============================_TASK_2_============================





int main()
{
	//============================_TASK_1_============================

	std::list<float> n{ 33.2, 2.45, 72.44, 13.12, 5.0 };
	pushBackEndAverage(n);
	
	//============================_TASK_2_============================	
	
	
	return 0;
}

