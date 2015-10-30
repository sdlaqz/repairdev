/* vi: set sw=4 ts=4 wrap ai: */
/*
 * main.c: This file is part of ____
 *
 * Copyright (C) 2015 yetist <yetist@yetioffice>
 *
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * */

#include <stdio.h>
#include <sys/wait.h> 
#include <unistd.h>

#include <pci/pci.h>

static struct pci_access *pacc;

int runsh(char* scriptpath)
{
	int ret = 0;
	pid_t pid;
	pid=fork();
	if (pid < 0) {
		printf("call fork error\n");
		ret = 1;
	} else if (pid == 0) {
		//setreuid(user->pw_uid, 0);
		//setregid(user->pw_gid, 0);
		execl(scriptpath, scriptpath, NULL);
	} else {
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			printf("child exited normal exit status=%d\n", WEXITSTATUS(status));
			ret = WEXITSTATUS(status);
		} else if (WIFSIGNALED(status)) {
			printf("child exited abnormal signal number=%d\n", WTERMSIG(status));
			ret = WTERMSIG(status);
		} else if (WIFSTOPPED(status)) {
			printf("child stopped signal number=%d\n", WSTOPSIG(status));
			ret = WSTOPSIG(status);
		}

	}
	return ret;
}

int fixdev(struct pci_dev *dev)
{
	//unsigned int c;
	//char namebuf[1024], *name;
	char path[1024];

	//pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);	/* Fill in header info we need */
	//c = pci_read_byte(dev, PCI_INTERRUPT_PIN);				/* Read config register directly */
	//printf("%04x:%02x:%02x.%d vendor=%04x device=%04x class=%04x irq=%d (pin %d) base0=%lx",
	//		dev->domain, dev->bus, dev->dev, dev->func, dev->vendor_id, dev->device_id,
	//		dev->device_class, dev->irq, c, (long) dev->base_addr[0]);

	///* Look up and print the full name of the device */
	//name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
	//printf(" (%s)\n", name);

	snprintf(path, sizeof(path), "%s/pci.d/%04x/%04x/repair.sh", SYSCONFDIR, dev->vendor_id, dev->device_id);
	if (access(path, F_OK & X_OK) == 0) {
		runsh(path);
	}

	return 0;
}

int main(void)
{
	struct pci_dev *dev;

	pacc = pci_alloc();		/* Get the pci_access structure */
	/* Set all options you want -- here we stick with the defaults */
	pci_init(pacc);		/* Initialize the PCI library */
	pci_scan_bus(pacc);		/* We want to get the list of devices */
	for (dev=pacc->devices; dev; dev=dev->next)	/* Iterate over all devices */
	{
		fixdev(dev);
	}
	pci_cleanup(pacc);		/* Close everything */
	return 0;
}
