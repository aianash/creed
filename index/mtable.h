#ifndef CREED_INDEX_MTABLE_H
#define CREED_INDEX_MTABLE_H

#include <memory>
#include <string>
#include <cstring>
#include <stdint.h>
#include <uuid/uuid.h>
#include <sys/types.h>

#include "search/query.h"
#include "search/collector.h"
#include "common/bregman.h"

namespace Creed {
namespace Index {

class Entry;
class RoutingEntry;
class Node;
class MTable;

using entry_upr        = std::unique_ptr<Entry>;
using entry_cupr       = std::unique_ptr<const Entry>;
using routingEntry_upr = std::unique_ptr<RoutingEntry>;
using node_spr         = std::shared_ptr<Node>;

//
struct NodeId {
  uuid_t id;
  uint16_t level;
  uint16_t segno;
  uint16_t pageno;

  NodeId() {}

  NodeId(uuid_t id_, uint16_t level_, uint16_t segno_, uint16_t pageno_):
    level(level_), pageno(pageno_), segno(segno_) {
      std::memcpy(&id, id_, sizeof(uuid_t));
    }
};

//
class Entry {
friend Node;
public:
  Entry() {}
  ~Entry() {}
};

//
class ObjectEntry : public Entry {
friend Node;
};

//
class RoutingEntry : public Entry {
friend Node;
private:
  NodeId subtree;
};

//
class Node {
friend MTable;
public:
  Node() {}
  Node(NodeId id_): id(id_) {}
  Node(const Node &node);

  NodeId nearest(entry_cupr &entry) const;
  Node *partition(routingEntry_upr const &pentryl, routingEntry_upr const &pentryr);

  inline bool isFull() { return false; }
  inline int level() { return id.level; }
  inline bool isLeaf() { return id.level == 0; }
  inline bool isRoot() { return !isLeaf(); }

  void insert(entry_cupr entry);
  void replace(NodeId id, entry_cupr entry);

  ~Node() {}

private:
  NodeId parent;
  NodeId sibling;
  NodeId id;

  size_t numEntries;
  Entry **entries;

  void twoMeans(Entry **&clusterl, Entry **&clusterr, size_t * const sizel, size_t * const sizer);

  Node *newNode(uint16_t level) { return new Node(*newNodeId(level)); }
  NodeId *newNodeId(uint16_t level) {
    uuid_t uid;
    uuid_generate(uid);
    return new NodeId(uid, level, 1, 1);
  }
};


//
class MTable {
public:
  explicit MTable(const std::string &path, int flags);
  ~MTable();

  bool isOpen = false;
  bool isWritable = false;

  void insert(entry_cupr entry);
  void remove(Entry &entry);
  void update(Entry &entry);

  bool empty();
  bool exists() const;
  void flush();

  bool sync();

private:
  node_spr root;
  uint16_t levels;

  void split(node_spr &node, entry_cupr entry);
  void insert(entry_cupr entry, int level);

  node_spr readNode(NodeId nodeId) const;
  void writeNode(node_spr &node);

  Entry *createEntry();
  node_spr makeNewRoot();
};

}
}

#endif