#!/bin/bash
conf_file=/etc/X11/xorg.conf.d/20-intel.conf

create_cfg() {
	cat > $conf_file <<EOF
Section "Device"
Identifier "Intel Graphics"
Driver "intel"
Option "DRI" "2"
EndSection
EOF
}

if [ -f /etc/X11/xorg.conf.d/20-intel.conf ];then
	if grep DRI $conf_file|grep 2;then
		exit 0
	else
		create_cfg
	fi
else
		create_cfg
fi

exit 0
