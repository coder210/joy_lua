#ifndef JOY_LUA_JOY_SHIM_H
#define JOY_LUA_JOY_SHIM_H

/*
 * 兼容转发头。
 * luaclib/*.c、jluax.c 使用 `#include "../joy.h"` / `"joy.h"`，相对本仓根解析到本文件；
 * 这里转发到 joy 核心的真实头 <joy/joy.h>，从而保持绑定/宿主源码零改动。
 */
#include <joy/joy.h>

#endif /* JOY_LUA_JOY_SHIM_H */
