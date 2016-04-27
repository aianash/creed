#ifndef CREED_INCLUDED_SEARCHER_H
#define CREED_INCLUDED_SEARCHER_H

namespace Creed {
namespace Search {

class Searcher {
public:
  Searcher();
  ~Searcher();

  void nnSearch(NNQuery &query);

};

}
}

#endif