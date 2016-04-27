#include "mtable.h"

using namespace Creed::Index;

Node::Node(const Node &node) {}

// std::unique_ptr<Entry> Node::operator[](int index) {
//   return std::unique_ptr<Entry>(new Entry);
// }

NodeId Node::nearest(entry_cupr &entry) const { return NodeId(); }

Node *Node::partition(routingEntry_upr const &pentryl, routingEntry_upr const &pentryr) {
  size_t sizel, sizer;
  Entry **clusterl, **clusterr;
  twoMeans(clusterl, clusterr, &sizel, &sizer);

  Node *rnode = newNode(this->id.level);
  rnode->entries = clusterr;
  rnode->numEntries = sizer;

  delete[] this->entries;
  this->entries = clusterl;
  this->numEntries = sizel;

  pentryl->subtree = this->id;
  pentryr->subtree = rnode->id;

  return rnode;
}

void Node::insert(entry_cupr entry) {}
void replace(NodeId id, entry_cupr entry) {}

void Node::twoMeans(Entry **&clusterl, Entry **&clusterr, size_t * const sizel, size_t * const sizer) {}