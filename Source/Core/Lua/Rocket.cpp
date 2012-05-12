/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
 
#include "precompiled.h"
#include "Rocket.h"
#include <Rocket/Core/Core.h>
#include <Rocket/Core/Input.h>

namespace Rocket {
namespace Core {
namespace Lua {

template<> void ExtraInit<rocket>(lua_State* L, int metatable_index)
{
    //because of the way LuaType::Register is done, we know that the methods table is directly
    //before the metatable 
    int method_index = metatable_index - 1;

    lua_pushcfunction(L,rocketCreateContext);
    lua_setfield(L,method_index,"CreateContext");

    lua_pushcfunction(L,rocketLoadFontFace);
    lua_setfield(L,method_index,"LoadFontFace");

    lua_pushcfunction(L,rocketRegisterTag);
    lua_setfield(L,method_index,"RegisterTag");

    rocketEnumkey_identifier(L);
    lua_setfield(L,method_index,"key_identifier");

    lua_pushcfunction(L,rocketGetAttrcontexts);
    lua_setfield(L,method_index,"contexts");

    return;
}

int rocketCreateContext(lua_State* L)
{
    const char* name = luaL_checkstring(L,1);
    Vector2i* dimensions = LuaType<Vector2i>::check(L,2);
    Context* new_context = CreateContext(name, *dimensions);
    if(new_context == NULL || dimensions == NULL)
    {
        lua_pushnil(L);
        return 1;
    }
    else
    {
        LuaType<Context>::push(L, new_context);
        return 1;
    }
}

int rocketLoadFontFace(lua_State* L)
{
    const char* file = luaL_checkstring(L,1);
    FontDatabase::LoadFontFace(file);
    return 0;
}

int rocketRegisterTag(lua_State* L)
{
    //this may take some thought
    return 0;
}

int rocketGetAttrcontexts(lua_State* L)
{
    lua_newtable(L);
    int tbl = lua_gettop(L);
    int numcontexts = GetNumContexts();
    Context* cont;
    for(int i = 0; i < numcontexts; i++)
    {
        cont = GetContext(i);
        if(cont != NULL)
        {
            LuaType<Context>::push(L,cont,false);
            lua_pushvalue(L,-1); //duplicate the top of the stack, because we are indexing by string and integral key so we need two
            lua_rawseti(L,tbl,i);
            lua_setfield(L,tbl,cont->GetName().CString());
        }
    }
    return 1;
}

void rocketEnumkey_identifier(lua_State* L)
{
    lua_newtable(L);
    int tbl = lua_gettop(L);
	ROCKETLUA_INPUTENUM(UNKNOWN,tbl)
	ROCKETLUA_INPUTENUM(SPACE,tbl)
	ROCKETLUA_INPUTENUM(0,tbl)
	ROCKETLUA_INPUTENUM(1,tbl)
	ROCKETLUA_INPUTENUM(2,tbl)
	ROCKETLUA_INPUTENUM(3,tbl)
	ROCKETLUA_INPUTENUM(4,tbl)
	ROCKETLUA_INPUTENUM(5,tbl)
	ROCKETLUA_INPUTENUM(6,tbl)
	ROCKETLUA_INPUTENUM(7,tbl)
	ROCKETLUA_INPUTENUM(8,tbl)
	ROCKETLUA_INPUTENUM(9,tbl)
	ROCKETLUA_INPUTENUM(A,tbl)
	ROCKETLUA_INPUTENUM(B,tbl)
	ROCKETLUA_INPUTENUM(C,tbl)
	ROCKETLUA_INPUTENUM(D,tbl)
	ROCKETLUA_INPUTENUM(E,tbl)
	ROCKETLUA_INPUTENUM(F,tbl)
	ROCKETLUA_INPUTENUM(G,tbl)
	ROCKETLUA_INPUTENUM(H,tbl)
	ROCKETLUA_INPUTENUM(I,tbl)
	ROCKETLUA_INPUTENUM(J,tbl)
	ROCKETLUA_INPUTENUM(K,tbl)
	ROCKETLUA_INPUTENUM(L,tbl)
	ROCKETLUA_INPUTENUM(M,tbl)
	ROCKETLUA_INPUTENUM(N,tbl)
	ROCKETLUA_INPUTENUM(O,tbl)
	ROCKETLUA_INPUTENUM(P,tbl)
	ROCKETLUA_INPUTENUM(Q,tbl)
	ROCKETLUA_INPUTENUM(R,tbl)
	ROCKETLUA_INPUTENUM(S,tbl)
	ROCKETLUA_INPUTENUM(T,tbl)
	ROCKETLUA_INPUTENUM(U,tbl)
	ROCKETLUA_INPUTENUM(V,tbl)
	ROCKETLUA_INPUTENUM(W,tbl)
	ROCKETLUA_INPUTENUM(X,tbl)
	ROCKETLUA_INPUTENUM(Y,tbl)
	ROCKETLUA_INPUTENUM(Z,tbl)
	ROCKETLUA_INPUTENUM(OEM_1,tbl)
	ROCKETLUA_INPUTENUM(OEM_PLUS,tbl)
	ROCKETLUA_INPUTENUM(OEM_COMMA,tbl)
	ROCKETLUA_INPUTENUM(OEM_MINUS,tbl)
	ROCKETLUA_INPUTENUM(OEM_PERIOD,tbl)
	ROCKETLUA_INPUTENUM(OEM_2,tbl)
	ROCKETLUA_INPUTENUM(OEM_3,tbl)
	ROCKETLUA_INPUTENUM(OEM_4,tbl)
	ROCKETLUA_INPUTENUM(OEM_5,tbl)
	ROCKETLUA_INPUTENUM(OEM_6,tbl)
	ROCKETLUA_INPUTENUM(OEM_7,tbl)
	ROCKETLUA_INPUTENUM(OEM_8,tbl)
	ROCKETLUA_INPUTENUM(OEM_102,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD0,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD1,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD2,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD3,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD4,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD5,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD6,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD7,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD8,tbl)
	ROCKETLUA_INPUTENUM(NUMPAD9,tbl)
	ROCKETLUA_INPUTENUM(NUMPADENTER,tbl)
	ROCKETLUA_INPUTENUM(MULTIPLY,tbl)
	ROCKETLUA_INPUTENUM(ADD,tbl)
	ROCKETLUA_INPUTENUM(SEPARATOR,tbl)
	ROCKETLUA_INPUTENUM(SUBTRACT,tbl)
	ROCKETLUA_INPUTENUM(DECIMAL,tbl)
	ROCKETLUA_INPUTENUM(DIVIDE,tbl)
	ROCKETLUA_INPUTENUM(OEM_NEC_EQUAL,tbl)
	ROCKETLUA_INPUTENUM(BACK,tbl)
	ROCKETLUA_INPUTENUM(TAB,tbl)
	ROCKETLUA_INPUTENUM(CLEAR,tbl)
	ROCKETLUA_INPUTENUM(RETURN,tbl)
	ROCKETLUA_INPUTENUM(PAUSE,tbl)
	ROCKETLUA_INPUTENUM(CAPITAL,tbl)
	ROCKETLUA_INPUTENUM(KANA,tbl)
	ROCKETLUA_INPUTENUM(HANGUL,tbl)
	ROCKETLUA_INPUTENUM(JUNJA,tbl)
	ROCKETLUA_INPUTENUM(FINAL,tbl)
	ROCKETLUA_INPUTENUM(HANJA,tbl)
	ROCKETLUA_INPUTENUM(KANJI,tbl)
	ROCKETLUA_INPUTENUM(ESCAPE,tbl)
	ROCKETLUA_INPUTENUM(CONVERT,tbl)
	ROCKETLUA_INPUTENUM(NONCONVERT,tbl)
	ROCKETLUA_INPUTENUM(ACCEPT,tbl)
	ROCKETLUA_INPUTENUM(MODECHANGE,tbl)
	ROCKETLUA_INPUTENUM(PRIOR,tbl)
	ROCKETLUA_INPUTENUM(NEXT,tbl)
	ROCKETLUA_INPUTENUM(END,tbl)
	ROCKETLUA_INPUTENUM(HOME,tbl)
	ROCKETLUA_INPUTENUM(LEFT,tbl)
	ROCKETLUA_INPUTENUM(UP,tbl)
	ROCKETLUA_INPUTENUM(RIGHT,tbl)
	ROCKETLUA_INPUTENUM(DOWN,tbl)
	ROCKETLUA_INPUTENUM(SELECT,tbl)
	ROCKETLUA_INPUTENUM(PRINT,tbl)
	ROCKETLUA_INPUTENUM(EXECUTE,tbl)
	ROCKETLUA_INPUTENUM(SNAPSHOT,tbl)
	ROCKETLUA_INPUTENUM(INSERT,tbl)
	ROCKETLUA_INPUTENUM(DELETE,tbl)
	ROCKETLUA_INPUTENUM(HELP,tbl)
	ROCKETLUA_INPUTENUM(LWIN,tbl)
	ROCKETLUA_INPUTENUM(RWIN,tbl)
	ROCKETLUA_INPUTENUM(APPS,tbl)
	ROCKETLUA_INPUTENUM(POWER,tbl)
	ROCKETLUA_INPUTENUM(SLEEP,tbl)
	ROCKETLUA_INPUTENUM(WAKE,tbl)
	ROCKETLUA_INPUTENUM(F1,tbl)
	ROCKETLUA_INPUTENUM(F2,tbl)
	ROCKETLUA_INPUTENUM(F3,tbl)
	ROCKETLUA_INPUTENUM(F4,tbl)
	ROCKETLUA_INPUTENUM(F5,tbl)
	ROCKETLUA_INPUTENUM(F6,tbl)
	ROCKETLUA_INPUTENUM(F7,tbl)
	ROCKETLUA_INPUTENUM(F8,tbl)
	ROCKETLUA_INPUTENUM(F9,tbl)
	ROCKETLUA_INPUTENUM(F10,tbl)
	ROCKETLUA_INPUTENUM(F11,tbl)
	ROCKETLUA_INPUTENUM(F12,tbl)
	ROCKETLUA_INPUTENUM(F13,tbl)
	ROCKETLUA_INPUTENUM(F14,tbl)
	ROCKETLUA_INPUTENUM(F15,tbl)
	ROCKETLUA_INPUTENUM(F16,tbl)
	ROCKETLUA_INPUTENUM(F17,tbl)
	ROCKETLUA_INPUTENUM(F18,tbl)
	ROCKETLUA_INPUTENUM(F19,tbl)
	ROCKETLUA_INPUTENUM(F20,tbl)
	ROCKETLUA_INPUTENUM(F21,tbl)
	ROCKETLUA_INPUTENUM(F22,tbl)
	ROCKETLUA_INPUTENUM(F23,tbl)
	ROCKETLUA_INPUTENUM(F24,tbl)
	ROCKETLUA_INPUTENUM(NUMLOCK,tbl)
	ROCKETLUA_INPUTENUM(SCROLL,tbl)
	ROCKETLUA_INPUTENUM(OEM_FJ_JISHO,tbl)
	ROCKETLUA_INPUTENUM(OEM_FJ_MASSHOU,tbl)
	ROCKETLUA_INPUTENUM(OEM_FJ_TOUROKU,tbl)
	ROCKETLUA_INPUTENUM(OEM_FJ_LOYA,tbl)
	ROCKETLUA_INPUTENUM(OEM_FJ_ROYA,tbl)
	ROCKETLUA_INPUTENUM(LSHIFT,tbl)
	ROCKETLUA_INPUTENUM(RSHIFT,tbl)
	ROCKETLUA_INPUTENUM(LCONTROL,tbl)
	ROCKETLUA_INPUTENUM(RCONTROL,tbl)
	ROCKETLUA_INPUTENUM(LMENU,tbl)
	ROCKETLUA_INPUTENUM(RMENU,tbl)
	ROCKETLUA_INPUTENUM(BROWSER_BACK,tbl)
	ROCKETLUA_INPUTENUM(BROWSER_FORWARD,tbl)
	ROCKETLUA_INPUTENUM(BROWSER_REFRESH,tbl)
	ROCKETLUA_INPUTENUM(BROWSER_STOP,tbl)
	ROCKETLUA_INPUTENUM(BROWSER_SEARCH,tbl)
	ROCKETLUA_INPUTENUM(BROWSER_FAVORITES,tbl)
	ROCKETLUA_INPUTENUM(BROWSER_HOME,tbl)
	ROCKETLUA_INPUTENUM(VOLUME_MUTE,tbl)
	ROCKETLUA_INPUTENUM(VOLUME_DOWN,tbl)
	ROCKETLUA_INPUTENUM(VOLUME_UP,tbl)
	ROCKETLUA_INPUTENUM(MEDIA_NEXT_TRACK,tbl)
	ROCKETLUA_INPUTENUM(MEDIA_PREV_TRACK,tbl)
	ROCKETLUA_INPUTENUM(MEDIA_STOP,tbl)
	ROCKETLUA_INPUTENUM(MEDIA_PLAY_PAUSE,tbl)
	ROCKETLUA_INPUTENUM(LAUNCH_MAIL,tbl)
	ROCKETLUA_INPUTENUM(LAUNCH_MEDIA_SELECT,tbl)
	ROCKETLUA_INPUTENUM(LAUNCH_APP1,tbl)
	ROCKETLUA_INPUTENUM(LAUNCH_APP2,tbl)
	ROCKETLUA_INPUTENUM(OEM_AX,tbl)
	ROCKETLUA_INPUTENUM(ICO_HELP,tbl)
	ROCKETLUA_INPUTENUM(ICO_00,tbl)
	ROCKETLUA_INPUTENUM(PROCESSKEY,tbl)
	ROCKETLUA_INPUTENUM(ICO_CLEAR,tbl)
	ROCKETLUA_INPUTENUM(ATTN,tbl)
	ROCKETLUA_INPUTENUM(CRSEL,tbl)
	ROCKETLUA_INPUTENUM(EXSEL,tbl)
	ROCKETLUA_INPUTENUM(EREOF,tbl)
	ROCKETLUA_INPUTENUM(PLAY,tbl)
	ROCKETLUA_INPUTENUM(ZOOM,tbl)
	ROCKETLUA_INPUTENUM(PA1,tbl)
	ROCKETLUA_INPUTENUM(OEM_CLEAR,tbl)
}


RegType<rocket> rocketMethods[] = 
{
    { NULL, NULL },
};

luaL_reg rocketGetters[] = 
{
    LUAGETTER(rocket,contexts)
    { NULL, NULL },
};

luaL_reg rocketSetters[] = 
{
    { NULL, NULL },
};

LUATYPEDEFINE(rocket,false)
}
}
}