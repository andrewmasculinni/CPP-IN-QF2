#ifndef PATH_DEPENDENT_BARRIER_ASIAN_STRADDLE_H
#define PATH_DEPENDENT_BARRIER_ASIAN_STRADDLE_H

#include "path_dependent.h"
#include <cmath>

// this class inherits after PathDependent class
class PathDependentBarrierAsianStraddle : public PathDependent
{
public:
    // constructor takes five arguments
    PathDependentBarrierAsianStraddle(const MJArray &look_at_times_,
                                      double delivery_time_,
                                      double strike_,
                                      double b_upper_,
                                      double b_lower_);


    virtual unsigned long max_number_of_cash_flows() const;
    virtual MJArray possible_cash_flow_times() const;
    virtual unsigned long cash_flows(const MJArray &spot_values,
                                     std::vector<CashFlow> &generated_flows) const;
    virtual ~PathDependentBarrierAsianStraddle() {}
    virtual PathDependent *clone() const;

private:
    double delivery_time;
    double strike;
    double b_upper;
    double b_lower;
    unsigned long number_of_times;
};

#endif
