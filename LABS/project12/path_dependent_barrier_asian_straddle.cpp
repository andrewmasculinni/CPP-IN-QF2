#include "path_dependent_barrier_asian_straddle.h"
#include <cmath>

PathDependentBarrierAsianStraddle::PathDependentBarrierAsianStraddle(const MJArray &look_at_times_,
                                       double delivery_time_,
                                       double strike_,
                                    double b_upper_,
                                       double b_lower_)
    : PathDependent(look_at_times_),
      delivery_time(delivery_time_),
      strike(strike_),
      b_upper(b_upper_),
      b_lower(b_lower_),
      number_of_times(look_at_times_.size())
{
}

// definitions of methods
unsigned long PathDependentBarrierAsianStraddle::max_number_of_cash_flows() const
{
    return 1UL; // 1UL stands for 'one unsigned long'
}

MJArray PathDependentBarrierAsianStraddle::possible_cash_flow_times() const
{
    MJArray tmp(1UL);
    tmp[0] = delivery_time;
    return tmp;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ! this method is responsible for determining payments of the option
// it checks if the path hit either barrier at any point during its life.
// if hit, payoff is zero (knock-out). otherwise, straddle payoff = |mean - strike|
unsigned long PathDependentBarrierAsianStraddle::cash_flows(const MJArray &spot_values,
                                             std::vector<CashFlow> &generated_flows) const
{
    for (unsigned long i = 0; i < number_of_times; i++)
    {
        if (spot_values[i] >= b_upper || spot_values[i] <= b_lower)
        {
            generated_flows[0].time_index = 0UL;
            generated_flows[0].amount = 0.0;
            return 1UL;
        }
    }
    double mean = spot_values.sum() / number_of_times;
    generated_flows[0].time_index = 0UL;
    generated_flows[0].amount = fabs(mean - strike);

    return 1UL;
}

// standard method for cloning (making a copy of this object)
PathDependent *PathDependentBarrierAsianStraddle::clone() const
{
    return new PathDependentBarrierAsianStraddle(*this);
}
