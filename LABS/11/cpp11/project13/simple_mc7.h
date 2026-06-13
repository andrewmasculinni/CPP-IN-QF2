#ifndef SIMPLE_MC7_H
#define SIMPLE_MC7_H

#include "vanilla3.h"
#include "parameters.h"
#include "statistics_mc.h"
#include "terminator.h"

void simple_monte_carlo7b(const VanillaOption &the_option,
						  double spot,
						  const Parameters &vol,
						  const Parameters &r,
						  unsigned long number_of_paths,
						  Terminator &gatherer);

#endif
