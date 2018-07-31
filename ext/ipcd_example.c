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
#include <libipc.h>
#include "ipcd_example.h"
#include "ipcd.h"
#include "libipc_stub.h"

struct calc_args {
    int32_t left;
    int32_t right;
    int32_t opcode;
};

static int on_test(struct ipc *r, void *in_arg, size_t in_len,
                void *out_arg, size_t *out_len)
{
    logi("on_test\n");
    return 0;
}

static int on_get_connect_list(struct ipc *r, void *in_arg, size_t in_len,
                void *out_arg, size_t *out_len)
{
    logi("on_test\n");
    return 0;
}

static int on_calc(struct ipc *r, void *in_arg, size_t in_len,
                void *out_arg, size_t *out_len)
{
    int val = 0;
    struct calc_args *args = (struct calc_args *)in_arg;
    logi("in_len = %d, calc left = %d, right = %d, opcode = %c\n", in_len, args->left, args->right, args->opcode);
    switch (args->opcode) {
    case '+':
        val = args->left + args->right;
        break;
    case '-':
        val = args->left - args->right;
        break;
    case '*':
        val = args->left * args->right;
        break;
    case '/':
        if (args->right == 0) {
            loge("div zero error!\n");
            break;
        }
        val = args->left / args->right;
        break;
    default:
        loge("unknown\n");
        break;
    }
    logi("after calc, val = %d\n", val);
    memcpy(out_arg, &val, sizeof(val));
    *out_len = sizeof(val);
    return 0;
}

static int on_shell_help(struct ipc *r, void *in_arg, size_t in_len,
                void *out_arg, size_t *out_len)
{
    char buf[1024];
    char *cmd = (char *)in_arg;
    memset(buf, 0, sizeof(buf));
    system_with_result(cmd, buf, sizeof(buf));
    memcpy(out_arg, buf, strlen(buf));
    *out_len = strlen(buf);
    return 0;
}

BEGIN_IPC_MAP(EXAMPLE_IPC_API)
IPC_MAP(IPC_TEST, on_test)
IPC_MAP(IPC_GET_CONNECT_LIST, on_get_connect_list)
IPC_MAP(IPC_SHELL_HELP, on_shell_help)
IPC_MAP(IPC_CALC, on_calc)
END_IPC_MAP()

int ipcd_group_register()
{
    IPC_REGISTER_MAP(EXAMPLE_IPC_API);
    return 0;
}
