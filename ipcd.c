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
#include <libgzf.h>
#include <libworkq.h>
#include <libipc.h>

//static struct ipc *_ipcd = NULL;

int ipcd_init()
{
    struct ipc *ipc = NULL;
    ipc = ipc_create(IPC_RECVER);

    return 0;
}

int ipcd_dispatch()
{
    while (1) {
        sleep(1);
        logi("wait message\n");
    }

    return 0;
}

void ipcd_deinit()
{

}

void usage()
{
    printf("usage: run as daemon: ./ipcd -d\n"
            "      run for debug: ./ipcd\n");
}

void ctrl_c_op(int signo)
{
    exit(0);
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
    ipcd_init();
    ipcd_dispatch();
    ipcd_deinit();
    return 0;
}