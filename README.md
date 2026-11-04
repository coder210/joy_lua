# joy_lua

> **状态:已合并回 joy 主仓,本仓归档。**
>
> 代码现位于 `joy/modules/lua`,通过
> `joy_add_sources(<target> MODULES lua)` 启用(默认关闭,可用
> `-DJOY_MODULE_LUA=ON` 打开);引擎头引用已统一为 `<joy/xxx.h>`。
> 本仓不再接收更新,仅作历史归档。

joy 引擎的可选 **Lua 脚本后端**,从 joy 核心拆出的独立仓库。

## 定位
- joy 核心本身**不依赖**本模块、也不携带 Lua 虚拟机。
- 只有想让 Lua 脚本驱动引擎的项目,才把它作为可选依赖接入。
- 依赖:joy 公共 API(`<src/joy.h>`)、SDL3、msgpack(部分绑定用到)。

## 内容
- `joy_lua.h` —— 对外 API(`luax_*`,承接原 `joy.h` 里的 Lua 宿主声明)。
- `jluax.c` —— Lua 运行时宿主(创建 state、加载脚本、事件分发、热重载)。
- `luaclib/` —— Lua 绑定层(`luaopen_*`,把 joy 接口暴露给脚本)。
- `external/lua/` —— Lua 5.4 虚拟机(amalgamation 源码)。
- `external/lua_cjson/` —— 给 Lua 提供 JSON 的 C 模块。

绑定/宿主源码直接以 `<src/joy.h>`、`<src/jmath.h>`、`<src/jconfig.h>`、
`<src/external/kcp.h>` 包含 joy 核心头(由 CMake 的 include 目录解析),本仓不再放置转发头。

## joy 子模块
本仓通过 git submodule 引用 joy 核心,检出于 `joy/`:
```powershell
git clone --recursive https://github.com/coder210/joy_lua.git
# 已 clone 过(或想同步最新 joy):
git submodule update --init --recursive
```
`JOY_SOURCE_DIR` 默认即指向本仓 `joy/src`(含 `joy.h`),通常无需手动设置。

## 接入方式(下游工程)
```cmake
add_subdirectory(third_party/joy_lua)
target_link_libraries(<game> PRIVATE joy_lua)
```
`joy_lua` 会自行链接 SDL3 与 msgpack(随 joy 子模块提供,若目标存在则链接)。

> 注:关卡加载已改用 `jtilemap` 的 JSON 后端,不再需要 Lua 来解析 Tiled 地图。
