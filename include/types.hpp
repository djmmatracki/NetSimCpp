#ifndef SIECI_TYPES_HPP
#define SIECI_TYPES_HPP

#include <list>
#include <iterator>
#include <set>
#include <functional>

using ElementID = unsigned int;

using assigned_IDs = std::set<ElementID>;
using freed_IDs = std::set<ElementID>;

using ID = std::pair<assigned_IDs, freed_IDs>;
using Time = double;
using TimeOffset = double;
using ProbabilityGenerator = std::function<double()>;

#endif
