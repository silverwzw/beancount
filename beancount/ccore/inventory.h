// A container for an inventory of positions.
//
// This module provides a container class that can hold positions. An inventory is
// a mapping of positions, where each position is keyed by
//
//   (currency: str, cost: Cost) -> position: Position
//
// where
//
//   'currency': The commodity under consideration, USD, CAD, or stock units such
//      as HOOL, MSFT, AAPL, etc.;
//
//   'cost': None or a Cost instance existing of cost currency, number, date, and
//      label;
//
//   'position': A Position object, whose 'units' attribute is guaranteed to have
//     the same currency as 'currency' and whose 'cost' attribute is equal to the
//     'cost' key. It basically stores the number of units.
//
// This is meant to accommodate both booked and non-booked amounts. The clever
// trick that we pull to do this is that for positions which aren't booked, we
// simply leave the 'cost' as None. This is the case for most of the transactions.
//
// = Conversions =
//
// If it often desired to convert this inventory into an equivalent position for
// its cost, or to just flatten all the positions with the same currency and count
// the number of units, or to compute the market value for the inventory at a
// specific date. You do these conversions using the reduce() method:
//
//   inventory.reduce(convert.get_cost)
//   inventory.reduce(convert.get_units)
//   inventory.reduce(convert.get_value, price_map, date)
//
// Copyright (C) 2020  Martin Blais"
// GNU GPLv2"

#ifndef _BEANCOUNT_CCORE_INVENTORY_H_
#define _BEANCOUNT_CCORE_INVENTORY_H_

#include <string>
#include <unordered_map>

#include "beancount/defs.h"
#include "beancount/ccore/data.pb.h"

namespace beancount {

// Result of booking a new lot to an existing inventory.
enum MatchResult {
  // A new lot was created.
  CREATED = 1,
  // An existing lot was reduced.
  REDUCED = 2,
  // An existing lot was augmented.
  AUGMENTED = 3,
  // No change was applied.
  IGNORED = 4,
};


// An Inventory is a set of positions.
// Positions are indexed by (currency, cost) for efficiency.
class Inventory {
public:
  Inventory();


private:
  // std::unordered_map<string, Decimal> positions_;
  // std::unordered_map<Cost, Decimal> positions_;
  //std::unordered_map<pair<string, Cost>, Decimal> positions_;
};

}  // namespace beancount

namespace std {

// Hashing function for Cost type.
template<>
struct hash<beancount::Cost> {
  size_t operator()(const beancount::Cost& cost) const {
    return (hash(cost.number()) ^
            hash(cost.currency()) ^
            hash(cost.date()) ^
            hash(cost.label()));
  }
};

}  // namespace std


#endif // _BEANCOUNT_CCORE_ACCOUNT_H_
