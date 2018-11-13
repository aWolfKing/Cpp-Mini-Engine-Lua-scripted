#include "framework_Lua.h"
//#include "rendering.h"
#include <iostream>


namespace mini_engine {
	namespace rendering {
		void draw_background(unsigned char r, unsigned char g, unsigned char b);
		void draw_sprite(int x, int y, int id);
		void draw_square(int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b);
	}
}


namespace framework {
	namespace Lua {


		int Lua_print(lua_State* Lua_state) {
			if (0 < lua_gettop(Lua_state)) {
				std::cout << lua_tostring(Lua_state, -1) << std::endl;
			}
			return 0;
		}


		int Lua_background(lua_State* Lua_state) {

			int r{ 0 }, g{ 0 }, b{0};

			if (Lua_state) {
				//If at least 3 parameters
				if (3 <= lua_gettop(Lua_state)) {
					//All 3 parameters are numbers
					if (lua_isnumber(Lua_state, -1) && lua_isnumber(Lua_state, -2) && lua_isnumber(Lua_state, -3)) {
						r = lua_tonumber(Lua_state, -3);
						g = lua_tonumber(Lua_state, -2);
						b = lua_tonumber(Lua_state, -1);
					}
				}
			}

			mini_engine::rendering::draw_background(r, g, b);

			return 0;
		}

		int Lua_drawsprite(lua_State* Lua_state) {

			int x{ 0 }, y{ 0 }, id{ 0 };

			if (Lua_state) {
				//If at least 3 parameters
				if (3 <= lua_gettop(Lua_state)) {
					//All 3 parameters are numbers
					if (lua_isnumber(Lua_state, -1) && lua_isnumber(Lua_state, -2) && lua_isnumber(Lua_state, -3)) {
						x = lua_tonumber(Lua_state, -3);
						y = lua_tonumber(Lua_state, -2);
						id = lua_tonumber(Lua_state, -1);
						mini_engine::rendering::draw_sprite(x, y, id);
					}
				}
			}

			return 0;
		}

		int Lua_drawsquare(lua_State* Lua_state) {

			int x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 }, r{ 0 }, g{ 0 }, b{ 0 };

			if (Lua_state) {
				if (7 <= lua_gettop(Lua_state)) {
					if (lua_isnumber(Lua_state, -1) && lua_isnumber(Lua_state, -2) && lua_isnumber(Lua_state, -3) && lua_isnumber(Lua_state, -4) && lua_isnumber(Lua_state, -5) && lua_isnumber(Lua_state, -6) && lua_isnumber(Lua_state, -7)) {
						x = lua_tonumber(Lua_state, -7);
						y = lua_tonumber(Lua_state, -6);
						width = lua_tonumber(Lua_state, -5);
						height = lua_tonumber(Lua_state, -4);
						r = lua_tonumber(Lua_state, -3);
						g = lua_tonumber(Lua_state, -2);
						b = lua_tonumber(Lua_state, -1);						
						mini_engine::rendering::draw_square(x, y, width, height, r, g, b);
					}
				}
			}

			return 0;
		}


	}
}