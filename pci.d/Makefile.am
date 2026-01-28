NULL =

repair_scripts = $(sort $(wildcard *.sh))

install-pci-scripts:
	for name in $(repair_scripts); do \
		mkdir -p $(DESTDIR)$(datadir)/pci.d/; \
		$(INSTALL_SCRIPT) $(srcdir)/$$name $(DESTDIR)$(datadir)/pci.d/check7200.sh; \
	done;

uninstall-pci-scripts:
	-for name in $(repair_scripts); do \
		rm -f $(DESTDIR)$(datadir)/pci.d/check7200.sh; \
	done;

install-data-local: install-pci-scripts

uninstall-local: uninstall-pci-scripts

EXTRA_DIST = $(repair_scripts)

-include $(top_srcdir)/git.mk

