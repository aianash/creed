#include "mtable.h"

Creed::Index::MTable::MTable(const std::string& path, int flags) {}
Creed::Index::MTable::~MTable() {}
void Creed::Index::MTable::nnSearch(Creed::Query::NNQuery const &nnquery, Creed::Query::Collector &collector) {}
void Creed::Index::MTable::insert(Entry &entry) {}
void Creed::Index::MTable::remove(Entry &entry) {}
void Creed::Index::MTable::update(Entry &entry) {}
bool Creed::Index::MTable::empty() {}
bool Creed::Index::MTable::exists() const {}
void Creed::Index::MTable::flush() {}
bool Creed::Index::MTable::sync() {}