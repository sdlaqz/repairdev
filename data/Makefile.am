servicedir = $(libdir)/systemd/system
service_in_files = repairdev.service.in
service_DATA = $(service_in_files:.service.in=.service)

$(service_DATA): $(service_in_files)
	$(AM_V_GEN) $(SED) 's#@BIN_DIR@#$(datadir)/pci.d#' $^ > $@

EXTRA_DIST = $(service_in_files)

CLEANFILES = $(service_DATA)

DISTCLEANFILES = $(service_DATA)
