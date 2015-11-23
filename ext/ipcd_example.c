/******************************************************************************
 * Copyright (C) 2014-2015
 * file:    ipcd_example.c
 * author:  gozfree <gozfree@163.com>
 * created: 2015-11-23 21:46
 * updated: 2015-11-23 21:46
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
#include "ipcd_example.h"
#include "ipcd.h"
#include "libipc_stub.h"

static int on_test(struct ipc *r, void *in_arg, size_t in_len,
                void *out_arg, size_t out_len)
{
    logi("on_test\n");
    return 0;
}

static int on_get_connect_list(struct ipc *r, void *in_arg, size_t in_len,
                void *out_arg, size_t out_len)
{
    logi("on_test\n");
    return 0;
}

BEGIN_IPC_MAP(EXAMPLE_IPC_API)
IPC_ACTION(IPC_TEST, on_test)
IPC_ACTION(IPC_GET_CONNECT_LIST, on_get_connect_list)
END_IPC_MAP()

int ipcd_group_register()
{
    IPC_REGISTER_MAP(EXAMPLE_IPC_API);
    return 0;
}
