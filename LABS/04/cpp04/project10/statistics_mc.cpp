#include "statistics_mc.h"
#include <cmath>
using namespace std;

StatisticsMean::StatisticsMean() : running_sum(0.0), paths_done(0UL)
{
}

void StatisticsMean::dump_one_result(double result)
{
    paths_done++;
    running_sum += result;
}

vector<vector<double>> StatisticsMean::get_results_so_far() const
{
    vector<vector<double>> Results(1);

    Results[0].resize(1);
    Results[0][0] = running_sum / paths_done;

    return Results;
}

StatisticsMC *StatisticsMean::clone() const
{
    return new StatisticsMean(*this);
}

StatisticsSD::StatisticsSD() : running_sum(0.0), running_sum_sq(0.0), paths_done(0UL)
{
}

void StatisticsSD::dump_one_result(double result)
{
    paths_done++;
    running_sum += result;
    running_sum_sq += result * result;
}

vector<vector<double>> StatisticsSD::get_results_so_far() const
{
    vector<vector<double>> Results(1);
    Results[0].resize(4);

    double mean = running_sum / paths_done;
    double variance = (running_sum_sq - paths_done * mean * mean) / (paths_done - 1);
    double sd = sqrt(variance / paths_done);

    Results[0][0] = mean;
    Results[0][1] = sd;
    Results[0][2] = mean - 1.96 * sd;
    Results[0][3] = mean + 1.96 * sd;

    return Results;
}

StatisticsMC *StatisticsSD::clone() const
{
    return new StatisticsSD(*this);
}