#ifndef CREED_INCLUDED_QUERY_H
#define CREED_INCLUDED_QUERY_H

#include "common/bregman.h"

namespace Creed {
namespace Search {

class NNQuery {
public:
  NNQuery();
  ~NNQuery();

  bool overlap(Bregman::Ball ball) {
    return Bregman::overlap(this->ball, ball);
  }

  float distance() { return 1.0; }

private:
  Bregman::Ball ball;
};

}
}

#endif