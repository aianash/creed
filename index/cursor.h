#ifndef CREED_INCLUDED_CURSOR_H
#define CREED_INCLUDED_CURSOR_H

namespace Creed {
namespace Index {

class Cursor {
public:
  Cursor(MTable *M);
  ~Cursor();
};

}
}

#endif