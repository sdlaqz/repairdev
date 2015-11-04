NULL =

repair_scripts = $(sort $(wildcard *.sh))

install-pci-scripts:
	for name in $(repair_scripts); do \
		DEVID=`echo $$name | cut -d. -f1`; \
		mkdir -p $(DESTDIR)$(sysconfdir)/pci.d/$$DEVID; \
		$(INSTALL_SCRIPT) $(srcdir)/$$name $(DESTDIR)$(sysconfdir)/pci.d/$$DEVID/repair.sh; \
	done;

uninstall-pci-scripts:
	-for name in $(repair_scripts); do \
		DEVID=`echo $$name | cut -d. -f1`; \
		rm -f $(DESTDIR)$(sysconfdir)/pci.d/$$DEVID/repair.sh; \
	done;

install-data-local: install-pci-scripts

uninstall-local: uninstall-pci-scripts

EXTRA_DIST = $(repair_scripts)

-include $(top_srcdir)/git.mk

