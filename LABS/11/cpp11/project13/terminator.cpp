#include "terminator.h"
#include <iostream>

Terminator::Terminator(const Wrapper<StatisticsMC> &Inner_, double target_stddev_)
	: Inner(Inner_), target_stddev(target_stddev_)
{
	current_stddev = target_stddev_ + 1.0;
	paths_done = 0;
}

StatisticsMC *Terminator::clone() const
{
	return new Terminator(*this);
}

void Terminator::dump_one_result(double result)
{
	Inner->dump_one_result(result);
	results_so_far = Inner->get_results_so_far();
	current_stddev = results_so_far[1][0];
	++paths_done;
}

bool Terminator::converged()
{
	if (current_stddev < target_stddev)
		return true;
	else
		return false;
}

std::vector<std::vector<double>> Terminator::get_results_so_far() const
{

	std::vector<std::vector<double>> tmp(results_so_far);

	for (unsigned long i = 0; i < tmp.size(); i++)
	{
		tmp[i].push_back(paths_done);
	}

	return tmp;
}

double Terminator::get_current_stddev()
{
	return current_stddev;
}
