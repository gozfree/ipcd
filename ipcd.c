/******************************************************************************
 * Copyright (C) 2014-2015
 * file:    ipcd.c
 * author:  gozfree <gozfree@163.com>
 * created: 2015-11-22 18:42
 * updated: 2015-11-22 18:42
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <liblog.h>
#include <libgevent.h>
#include <libdict.h>
#include <libskt.h>
#include <libipc.h>
#include "ext/ipcd_example.h"

static struct ipc *g_ipcd = NULL;
static bool run = false;

int ipcd_init()
{
    g_ipcd = ipc_create(IPC_SERVER, IPC_SERVER_PORT);
    if (g_ipcd == NULL) {
        loge("ipc_create failed!\n");
        return -1;
    }

    ipcd_group_register();
    return 0;
}

int ipcd_dispatch()
{
    run = true;
    while (run) {
        sleep(1);
    }

    return 0;
}

void ipcd_deinit()
{
    ipc_destroy(g_ipcd);
}

void usage()
{
    printf("usage: run as daemon: ./ipcd -d\n"
            "      run for debug: ./ipcd\n");
}

void ctrl_c_op(int signo)
{
    run = false;
    printf("xxx\n");
    ipcd_deinit();
}

int main(int argc, char **argv)
{
    if (argc > 2) {
        usage();
        exit(-1);
    }
    if (argc == 2) {
        if (!strcmp(argv[1], "-d")) {
            daemon(0, 0);
            log_init(LOG_RSYSLOG, "local2");
        }
    } else {
        log_init(LOG_STDERR, NULL);
    }
    log_set_level(LOG_INFO);
    signal(SIGINT , ctrl_c_op);
    if (-1 == ipcd_init()) {
        loge("ipcd_init failed!\n");
    }
    logi("ipcd is running...\n");
    ipcd_dispatch();
    ipcd_deinit();
    return 0;
}
