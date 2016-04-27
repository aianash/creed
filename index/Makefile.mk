noinst_HEADERS +=\
	index/datastore.h\
	index/mtable.h

EXTRA_DIST +=\
	index/Makefile

lib_src +=\
	index/datastore.cc\
	index/mtable.cc\
	index/node.cc\
	index/entry.cc