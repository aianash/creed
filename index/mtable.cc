#include "mtable.h"

using namespace Creed::Index;

MTable::MTable(const std::string &path, int flags) {}
MTable::~MTable() {}

//
void MTable::insert(entry_cupr entry) {
  insert(std::move(entry), 0);
}

//
void MTable::insert(entry_cupr entry, int level) {
  auto node = root;

  for(;;) {
    if(node->level() == level || node->isLeaf()) break;
    auto cand = node->nearest(entry);
    node = readNode(cand);
  }

  if(!node->isFull()) node->insert(std::move(entry));
  else split(node, std::move(entry));
  writeNode(node);
}

//
void MTable::split(const node_spr &node, entry_cupr entry) {
  node->insert(std::move(entry)); // Note: This is only a temporary insertion

  node_spr tnode = node;
  auto pentryl = std::make_unique<RoutingEntry>();
  auto pentryr = std::make_unique<RoutingEntry>();

  node_spr rNode = node->partition(pentryl, pentryr);

  if(node->isRoot()) {
    auto root = makeNewRoot();
    root->insert(std::move(pentryl));
    root->insert(std::move(pentryr));
  } else {
    node_spr pnode = readNode(node->parent);
    pnode->replace(node->id, std::move(pentryl));
    if(pnode->isFull()) split(pnode, std::move(pentryr));
    else writeNode(pnode);
  }
}

void MTable::remove(Entry &entry) {}
void MTable::update(Entry &entry) {}
bool MTable::empty() { return true; }
bool MTable::exists() const { return true; }
void MTable::flush() {}
bool MTable::sync() { return true; }


node_spr MTable::readNode(nodeid_t id) const {
  return std::make_shared<Node>(id);
}

void MTable::writeNode(const node_spr &node) {}

node_spr MTable::makeNewRoot() {
  // uint16_t segno = 1;
  // uint16_t pageno = 1;
  // uuid_t uuid;
  // uuid_generate(uuid);
  this->levels += 1;
  root = std::make_shared<Node>(nodeid_t::create(levels, 1, 1));
  return root;
}