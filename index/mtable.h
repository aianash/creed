#ifndef CREED_INCLUDED_TABLE_H
#define CREED_INCLUDED_TABLE_H

#include <string>

#include "query/query.h"
#include "query/collector.h"

namespace Creed {
namespace Index {

class Entry {
public:
  Entry() {}
  ~Entry() {}
};


class MTable {
public:
  explicit MTable(const std::string &path, int flags);
  ~MTable();

  bool isOpen = false;
  bool isWritable = false;

  void nnSearch(Creed::Query::NNQuery const &nnquery, Creed::Query::Collector &collector);
  void insert(Entry &entry);
  void remove(Entry &entry);
  void update(Entry &entry);

  bool empty();
  bool exists() const;
  void flush();

  bool sync();
};

}
}

#endif