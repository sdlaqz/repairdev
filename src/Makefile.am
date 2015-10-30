NULL =
bin_PROGRAMS = repairdev

common_CFLAGS = -Wall	

repairdev_CFLAGS = -Wall $(PCI_CFLAGS)
repairdev_LDADD = $(PCI_LIBS) 
repairdev_SOURCES = main.c

-include $(top_srcdir)/git.mk
