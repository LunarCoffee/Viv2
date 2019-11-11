#ifndef VIV2_KEYBOARD_H
#define VIV2_KEYBOARD_H

#include "../../lib/alias.h"

typedef enum {
    K_ESCAPE = 0x1,
    K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, K_0,
    K_DASH, K_EQUALS,
    K_BACKSPACE,
    K_TAB,
    K_Q, K_W, K_E, K_R, K_T, K_Y, K_U, K_I, K_O, K_P, K_LBRACKET, K_RBRACKET,
    K_RETURN, K_LCONTROL,
    K_A, K_S, K_D, K_F, K_G, K_H, K_J, K_K, K_L, K_SEMICOLON, K_SQUOTE, K_BACKTICK, 
    K_LSHIFT, 
    K_BACKSLASH,
    K_Z, K_X, K_C, K_V, K_B, K_N, K_M, K_COMMA, K_DOT, K_SLASH,
    K_RSHIFT,
    K_ASTERISK,
    K_LALT, 
    K_SPACE,
    K_CAPSLOCK,
    K_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10,
    K_NUMLOCK, K_SCROLLLOCK,
    K_K7, K_K8, K_K9, K_KDASH,
    K_K4, K_K5, K_K6, K_KPLUS,
    K_K1, K_K2, K_K3, K_K0, K_KDOT,
    K_F11 = 0x57, K_F12,

    SK_ESCAPE = 0x100,
    SK_1, SK_2, SK_3, SK_4, SK_5, SK_6, SK_7, SK_8, SK_9, SK_0,
    SK_Q, SK_W, SK_E, SK_R, SK_T, SK_Y, SK_U, SK_I, SK_O, SK_P, SK_LBRACKET, SK_RBRACKET,
    SK_RETURN, SK_LCONTROL,
    SK_A, SK_S, SK_D, SK_F, SK_G, SK_H, SK_J, SK_K, SK_L, SK_SEMICOLON, SK_SQUOTE, SK_BACKTICK, 
    SK_LSHIFT, 
    SK_BACKSLASH,
    SK_Z, SK_X, SK_C, SK_V, SK_B, SK_N, SK_M, SK_COMMA, SK_DOT, SK_SLASH,
    SK_RSHIFT,
    SK_ASTERISK,
    SK_LALT, 
    SK_SPACE,
    SK_CAPSLOCK,
    SK_F1, SK_F2, SK_F3, SK_F4, SK_F5, SK_F6, SK_F7, SK_F8, SK_F9, SK_F10,
    SK_NUMLOCK, SK_SCROLLLOCK,
    SK_K7, SK_K8, SK_K9, SK_KDASH,
    SK_K4, SK_K5, SK_K6, SK_KPLUS,
    SK_K1, SK_K2, SK_K3, SK_K0, SK_KDOT,
    SK_F11 = 0x157, SK_F12
} key_code;

u8 get_char(key_code kc);

void enable_keyboard(void);
void disable_keyboard(void);

#endif
