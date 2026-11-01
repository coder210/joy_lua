# joy_lua

joy 引擎的可选 **Lua 脚本后端**,从 joy 核心拆出的独立仓库。

## 定位
- joy 核心本身**不依赖**本模块、也不携带 Lua 虚拟机。
- 只有想让 Lua 脚本驱动引擎的项目,才把它作为可选依赖接入。
- 依赖:joy 公共 API(`<joy/joy.h>`)、SDL3、msgpack(部分绑定用到)。

## 内容
- `joy_lua.h` —— 对外 API(`luax_*`,承接原 `joy.h` 里的 Lua 宿主声明)。
- `jluax.c` —— Lua 运行时宿主(创建 state、加载脚本、事件分发、热重载)。
- `luaclib/` —— Lua 绑定层(`luaopen_*`,把 joy 接口暴露给脚本)。
- `external/lua/` —— Lua 5.4 虚拟机(amalgamation 源码)。
- `external/lua_cjson/` —— 给 Lua 提供 JSON 的 C 模块。
- `joy.h` / `jmath.h` / `jconfig.h` / `external/kcp.h` —— 兼容转发头:
  让 `luaclib/*.c`、`jluax.c` 内部的相对 include 无需改动即可解析到 joy 核心;
  从而保持绑定/宿主源码与上游一致。

## 接入方式(下游工程)
```cmake
set(JOY_SOURCE_DIR "${CMAKE_SOURCE_DIR}/third_party/joy/joy")
add_subdirectory(third_party/joy_lua)
target_link_libraries(<game> PRIVATE joy_lua)
```
`joy_lua` 会自行链接 SDL3 与 msgpack(若目标存在),并排除 Lua 独立解释器(`lua.c`)避免 main 冲突。

> 注:关卡加载已改用 `jtilemap` 的 JSON 后端,不再需要 Lua 来解析 Tiled 地图。
