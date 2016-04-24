noinst_HEADERS +=\
	query/collector.h\
	query/query.h

EXTRA_DIST +=\
	query/Makefile

lib_src +=\
	query/collector.cc\
	query/nnquery.cc