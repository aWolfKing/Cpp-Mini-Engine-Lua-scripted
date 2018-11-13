#pragma once
#ifndef FRAMEWORK_LUA_H
#define FRAMEWORK_LUA_H

extern "C" {
#include "Lua/lua.h"
#include "Lua/lauxlib.h"
#include "Lua/lualib.h"
}


namespace framework {
	namespace Lua {


		int Lua_print(lua_State* Lua_state);

		/* Clear the texture that was drawn. */
		int Lua_background(lua_State* Lua_state);

		/* Draw a sprite to the texture to draw. */
		int Lua_drawsprite(lua_State* Lua_state);

		/* Draw a square to te texture to draw. */
		int Lua_drawsquare(lua_State* Lua_state);


	}
}



#endif // !FRAMEWORK_LUA_H