#ifndef CREED_INCLUDED_BREGMAN_H
#define CREED_INCLUDED_BREGMAN_H

namespace Creed {
namespace Bregman {

class Ball {
public:
  Ball(){}
  ~Ball(){}
};

inline bool overlap(Ball &ball1, Ball &ball2) {
  return false;
}

inline float distance() { return 1.0f; }

}
}

#endif