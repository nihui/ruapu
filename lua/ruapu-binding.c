#include<lua.h>
#include<lauxlib.h>

#define RUAPU_IMPLEMENTATION
#include"../ruapu.h"

static int supports(lua_State *l)
{
    luaL_checktype(l, 1, LUA_TSTRING);
    lua_pushboolean(l, ruapu_supports(luaL_checkstring(l, 1)));
    return 1;
}

static int rua(lua_State *l)
{
    const char * const *s = ruapu_rua();
    lua_newtable(l);
    for (int i = 0; s[i]; i++) {
        lua_pushstring(l, s[i]);
        lua_rawseti(l, -2, i + 1);
    }
    return 1;
}

static const struct luaL_Reg modRuapu[] = {
    { "supports", supports },
    { "rua", rua },
    { NULL, NULL }
};

int luaopen_ruapu(lua_State *l)
{
    ruapu_init();
    luaL_newlib(l, modRuapu);
    return 1;
}
