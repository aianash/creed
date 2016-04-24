EXTRA_DIST +=\
	include/Makefile\
	include/creed/Makefile

creedincludedir = $(incdir)/creed

inc_HEADERS =\
	include/creed.h

xapianinclude_HEADERS =\
	include/creed/attributes.h\
	include/creed/compactor.h\
	include/creed/constants.h\
	include/creed/constinfo.h\
	include/creed/database.h\
	include/creed/dbfactory.h\
	include/creed/deprecated.h\
	include/creed/derefwrapper.h\
	include/creed/document.h\
	include/creed/enquire.h\
	include/creed/errorhandler.h\
	include/creed/expanddecider.h\
	include/creed/intrusive_ptr.h\
	include/creed/iterator.h\
	include/creed/keymaker.h\
	include/creed/matchspy.h\
	include/creed/mset.h\
	include/creed/positioniterator.h\
	include/creed/postingiterator.h\
	include/creed/postingsource.h\
	include/creed/query.h\
	include/creed/queryparser.h\
	include/creed/registry.h\
	include/creed/stem.h\
	include/creed/termgenerator.h\
	include/creed/termiterator.h\
	include/creed/types.h\
	include/creed/unicode.h\
	include/creed/valueiterator.h\
	include/creed/valuesetmatchdecider.h\
	include/creed/geospatial.h\
	include/creed/visibility.h\
	include/creed/weight.h

nodist_xapianinclude_HEADERS =\
	include/xapian/version.h

# Regenerate include/xapian/version.h if its template has been changed.
all-local: include/xapian/version.h.timestamp

include/xapian/version.h.timestamp: include/xapian/version_h.cc
	$(SHELL) ./config.status --recheck

EXTRA_DIST +=\
	include/xapian/version_h.cc

DISTCLEANFILES +=\
	include/xapian/version.h\
	include/xapian/version.h.timestamp
