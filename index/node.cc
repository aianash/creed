#include <array>
#include "mtable.h"

using namespace Creed::Index;

//
Node::Node(const Node &node) {}

//
nodeid_t Node::nearest(entry_cupr &entry) const { return nodeid_t(); }

//
void Node::insert(entry_cupr entry) {
  std::shared_ptr<const Entry> tmp(std::move(entry));
  entries->emplace_back(std::const_pointer_cast<Entry>(tmp));
}

//
void replace(nodeid_t id, entry_cupr entry) {}

//
node_spr Node::partition(routingEntry_upr const &pentryl, routingEntry_upr const &pentryr) {
  entries_spr clusterr = std::make_shared<std::vector<entry_spr>>();
  entries_spr clusterl = std::make_shared<std::vector<entry_spr>>();
  twoMeans(clusterl, clusterr);

  this->entries = clusterl;

  auto rnode = std::make_shared<Node>(nodeid_t::create(level(), segno(), pageno()));
  rnode->entries = clusterr;

  pentryl->subtree = this->id;
  pentryr->subtree = rnode->id;

  return rnode;
}

//
void Node::twoMeans(entries_spr &clusterl, entries_spr &clusterr) {
  const int MEMT = MAX_ENTRIES + 1;
  std::array<int, MEMT> allocIdx;

  int li = std::rand() % MEMT;
  int ri = std::rand() % MEMT;

  auto lbball = entries->at(li)->bball;
  auto rbball = entries->at(ri)->bball;

  int ln = 0;
  int rn = 0;

  float loss = 0.0;
  float ploss = loss;

  for(int itr = 0; itr < MAX_KMEANS_ITR; itr++) {
    loss = 0.0;
    for(std::size_t i = 0; i != entries->size(); i++) {
      auto entry = entries->at(i);
      auto ld = entry->distance(lbball);
      auto rd = entry->distance(rbball);

      if(ld <= rd) {
        lbball += entry->bball;
        ln += 1;
        loss += ld;
        if(ld > lbball.radius) lbball.radius = ld;
      } else {
        rbball += entry->bball;
        rn += 1;
        loss += rd;
        if(rd > rbball.radius) rbball.radius = rd;
      }
    }
    lbball /= ln;
    rbball /= rn;
    loss /= (ln + rn);

    if(loss - ploss < KMEANS_TOL * ploss) break;
    else ploss = loss;
  }

  for(auto const &entry: *entries) {
    if(entry->distance(lbball) <= entry->distance(rbball)) clusterl->emplace_back(entry);
    else clusterr->emplace_back(entry);
  }
}