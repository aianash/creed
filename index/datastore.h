#ifndef CREED_INCLUDED_DATASTORE_H
#define CREED_INCLUDED_DATASTORE_H

#include <string>

namespace Creed {
namespace Index {

class Datastore {
public:
  explicit Datastore(const std::string &filename, int flags, unsigned int blockSize);
  ~Datastore();
};

}
}

#endif