#ifndef TERMINATOR_H
#define TERMINATOR_H

#include "statistics_mc.h"
#include "wrapper.h"
#include "conf_limits.h"

class Terminator : public StatisticsMC
{
public:
    Terminator(const Wrapper<StatisticsMC> &Inner_, double target_stddev);

    virtual StatisticsMC *clone() const;
    virtual void dump_one_result(double result);
    virtual std::vector<std::vector<double>> get_results_so_far() const;

    bool converged();
    double get_current_stddev();

private:
    Wrapper<StatisticsMC> Inner;
    std::vector<std::vector<double>> results_so_far;
    double current_stddev;
    double target_stddev;
    unsigned long paths_done;
};

#endif
