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
	char path[1024];

	snprintf(path, sizeof(path), "%s/pci.d/%04x-%04x/repair.sh", SYSCONFDIR, dev->vendor_id, dev->device_id);
	if (access(path, F_OK & X_OK) == 0) {
		runsh(path);
	}

	return 0;
}

int main(void)
{
	struct pci_dev *dev;

	pacc = pci_alloc();
	pci_init(pacc);
	pci_scan_bus(pacc);
	for (dev=pacc->devices; dev; dev=dev->next)
	{
		fixdev(dev);
	}
	pci_cleanup(pacc);
	return 0;
}
