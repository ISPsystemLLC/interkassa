MGR = billmgr
PLUGIN = pminterkassa

CFLAGS += -I/usr/local/mgr5/include/billmgr
CXXFLAGS += -I/usr/local/mgr5/include/billmgr

PKGNAMES = billmanager-plugin-pminterkassa
RPM_PKGNAMES ?= $(PKGNAMES)
DEB_PKGNAMES ?= $(PKGNAMES)

WRAPPER += pminterkassa interkassapayment interkassaresult

pminterkassa_SOURCES = pminterkassa.cpp
pminterkassa_LDADD = -lbase -lpaymentmodule
pminterkassa_FOLDER = paymethods

interkassapayment_SOURCES = interkassapayment.cpp
interkassapayment_LDADD = -lpaymentcgi
interkassapayment_FOLDER = cgi

interkassaresult_SOURCES = interkassaresult.cpp
interkassaresult_LDADD = -lpaymentcgi
interkassaresult_FOLDER = cgi

BASE ?= /usr/local/mgr5
include $(BASE)/src/isp.mk
