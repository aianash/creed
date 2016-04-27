#ifndef CREED_INDEX_MTABLE_H
#define CREED_INDEX_MTABLE_H

#include <memory>
#include <string>
#include <cstring>
#include <vector>
#include <stdint.h>
#include <uuid/uuid.h>
#include <sys/types.h>

#include "search/query.h"
#include "search/collector.h"
#include "common/bregman.h"

namespace Creed {
namespace Index {

#define MAX_ENTRIES 100
#define BREGMAN_VECTOR_SIZE 100
#define MAX_KMEANS_ITR 10
#define KMEANS_TOL 0.5

class Entry;
class RoutingEntry;
class Node;
class MTable;
struct nodeid_t;

using entry_upr        = std::unique_ptr<Entry>;
using entry_cupr       = std::unique_ptr<const Entry>;
using entry_spr        = std::shared_ptr<Entry>;
using entries_spr      = std::shared_ptr<std::vector<entry_spr>>;

using routingEntry_upr = std::unique_ptr<RoutingEntry>;

using node_spr         = std::shared_ptr<Node>;
using nodeid_upr       = std::unique_ptr<nodeid_t>;

using bregman_vector   = std::array<float, BREGMAN_VECTOR_SIZE>;

struct bregman_ball {
  float radius;
  bregman_vector center;

  bregman_ball(): radius(0.0) { center.fill(0.0); }
  bregman_ball(float radius_, bregman_vector center_): radius(radius_), center(center_) {}

  bregman_ball &operator+=(const bregman_vector &v) {
    for(int i = 0; i != BREGMAN_VECTOR_SIZE; i++)
      center[i] += v[i];
    return *this;
  }

  bregman_ball &operator+=(const bregman_ball &bball) {
    for(int i = 0; i != BREGMAN_VECTOR_SIZE; i++)
      center[i] += bball.center[i];
    return *this;
  }

  bregman_ball &operator/=(const float v) {
    for(int i = 0; i != BREGMAN_VECTOR_SIZE; i++)
      center[i] /= v;
    return *this;
  }


  float distance(bregman_ball) {
    return 1.0;
  }

};

//
struct nodeid_t {
  uuid_t id;
  uint16_t level;
  uint16_t segno;
  uint16_t pageno;

  nodeid_t() {}

  nodeid_t(uuid_t id_, uint16_t level_, uint16_t segno_, uint16_t pageno_):
    level(level_), pageno(pageno_), segno(segno_) {
      uuid_copy(id, id_);
    }

  static nodeid_t create(uuid_t id, uint16_t level, uint16_t segno, uint16_t pageno) {
    return nodeid_t(id, level, segno, pageno);
  }

  static nodeid_t create(uint16_t level, uint16_t segno, uint16_t pageno) {
    uuid_t uuid;
    uuid_generate(uuid);
    return nodeid_t(uuid, level, segno, pageno);
  }
};

//
class Entry {
friend Node;
public:
  Entry() {}
  ~Entry() {}

  virtual float distance(entry_spr &entry) = 0;

  float distance(bregman_ball &from) {
    return bball.distance(from);
  }

private:
  bregman_ball bball;
};

//
class ObjectEntry : public Entry {
friend Node;
public:
  ObjectEntry(uuid_t objid_) {
    uuid_copy(objid, objid_);
  }

  float distance(entry_spr &entry) {
    return 1.0;
  }

private:
  uuid_t objid;

};

//
class RoutingEntry : public Entry {
friend Node;
public:
  float distance(entry_spr &entry) {
    return 1.0;
  }

private:
  nodeid_t subtree;
};

//
class Node {
friend MTable;
public:
  Node() {}
  Node(nodeid_t id_): id(id_) {}
  Node(const Node &node);

  nodeid_t nearest(entry_cupr &entry) const;
  node_spr partition(routingEntry_upr const &pentryl, routingEntry_upr const &pentryr);

  inline uint16_t level() { return id.level; }
  inline uint16_t segno() { return id.segno; }
  inline uint16_t pageno() { return id.pageno; }

  inline bool isFull() { return false; }
  inline bool isLeaf() { return id.level == 0; }
  inline bool isRoot() { return !isLeaf(); }
  inline size_t size() { return entries->size(); }

  void insert(entry_cupr entry);
  void replace(nodeid_t id, entry_cupr entry);

  ~Node() {}

private:
  nodeid_t parent;
  nodeid_t sibling;
  nodeid_t id;

  entries_spr entries;

  void twoMeans(entries_spr &clusterl, entries_spr &clusterr);

  // Node *newNode(uint16_t level, segno, level) {
  //   return new Node(nodeid_t::create(level, segno, pageno));
  // }

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

  void split(const node_spr &node, entry_cupr entry);
  void insert(entry_cupr entry, int level);

  node_spr readNode(nodeid_t nodeId) const;
  void writeNode(const node_spr &node);

  node_spr makeNewRoot();
};

}
}

#endif