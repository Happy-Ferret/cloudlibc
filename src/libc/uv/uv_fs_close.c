// Copyright (c) 2017 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <cloudabi_syscalls.h>
#include <uv.h>

#include "uv_impl.h"

static ssize_t do_close(uv_fs_t *req) {
  return -cloudabi_sys_fd_close(req->__arguments.__close.__file);
}

int uv_fs_close(uv_loop_t *loop, uv_fs_t *req, uv_file file, uv_fs_cb cb) {
  req->__arguments.__close.__file = file;
  return __uv_fs_execute(loop, req, UV_FS_CLOSE, do_close, cb);
}