#pragma once

namespace core_input {
	/* Printable keys */
#define KEYBOARD_KEY_SPACE              32
#define KEYBOARD_KEY_APOSTROPHE         39  /* ' */
#define KEYBOARD_KEY_COMMA              44  /* , */
#define KEYBOARD_KEY_MINUS              45  /* - */
#define KEYBOARD_KEY_PERIOD             46  /* . */
#define KEYBOARD_KEY_SLASH              47  /* / */
#define KEYBOARD_KEY_0                  48
#define KEYBOARD_KEY_1                  49
#define KEYBOARD_KEY_2                  50
#define KEYBOARD_KEY_3                  51
#define KEYBOARD_KEY_4                  52
#define KEYBOARD_KEY_5                  53
#define KEYBOARD_KEY_6                  54
#define KEYBOARD_KEY_7                  55
#define KEYBOARD_KEY_8                  56
#define KEYBOARD_KEY_9                  57
#define KEYBOARD_KEY_SEMICOLON          59  /* ; */
#define KEYBOARD_KEY_EQUAL              61  /* = */
#define KEYBOARD_KEY_A                  65
#define KEYBOARD_KEY_B                  66
#define KEYBOARD_KEY_C                  67
#define KEYBOARD_KEY_D                  68
#define KEYBOARD_KEY_E                  69
#define KEYBOARD_KEY_F                  70
#define KEYBOARD_KEY_G                  71
#define KEYBOARD_KEY_H                  72
#define KEYBOARD_KEY_I                  73
#define KEYBOARD_KEY_J                  74
#define KEYBOARD_KEY_K                  75
#define KEYBOARD_KEY_L                  76
#define KEYBOARD_KEY_M                  77
#define KEYBOARD_KEY_N                  78
#define KEYBOARD_KEY_O                  79
#define KEYBOARD_KEY_P                  80
#define KEYBOARD_KEY_Q                  81
#define KEYBOARD_KEY_R                  82
#define KEYBOARD_KEY_S                  83
#define KEYBOARD_KEY_T                  84
#define KEYBOARD_KEY_U                  85
#define KEYBOARD_KEY_V                  86
#define KEYBOARD_KEY_W                  87
#define KEYBOARD_KEY_X                  88
#define KEYBOARD_KEY_Y                  89
#define KEYBOARD_KEY_Z                  90
#define KEYBOARD_KEY_LEFT_BRACKET       91  /* [ */
#define KEYBOARD_KEY_BACKSLASH          92  /* \ */
#define KEYBOARD_KEY_RIGHT_BRACKET      93  /* ] */
#define KEYBOARD_KEY_GRAVE_ACCENT       96  /* ` */
#define KEYBOARD_KEY_WORLD_1            161 /* non-US #1 */
#define KEYBOARD_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEYBOARD_KEY_ESCAPE             256
#define KEYBOARD_KEY_ENTER              257
#define KEYBOARD_KEY_TAB                258
#define KEYBOARD_KEY_BACKSPACE          259
#define KEYBOARD_KEY_INSERT             260
#define KEYBOARD_KEY_DELETE             261
#define KEYBOARD_KEY_RIGHT              262
#define KEYBOARD_KEY_LEFT               263
#define KEYBOARD_KEY_DOWN               264
#define KEYBOARD_KEY_UP                 265
#define KEYBOARD_KEY_PAGE_UP            266
#define KEYBOARD_KEY_PAGE_DOWN          267
#define KEYBOARD_KEY_HOME               268
#define KEYBOARD_KEY_END                269
#define KEYBOARD_KEY_CAPS_LOCK          280
#define KEYBOARD_KEY_SCROLL_LOCK        281
#define KEYBOARD_KEY_NUM_LOCK           282
#define KEYBOARD_KEY_PRINT_SCREEN       283
#define KEYBOARD_KEY_PAUSE              284
#define KEYBOARD_KEY_F1                 290
#define KEYBOARD_KEY_F2                 291
#define KEYBOARD_KEY_F3                 292
#define KEYBOARD_KEY_F4                 293
#define KEYBOARD_KEY_F5                 294
#define KEYBOARD_KEY_F6                 295
#define KEYBOARD_KEY_F7                 296
#define KEYBOARD_KEY_F8                 297
#define KEYBOARD_KEY_F9                 298
#define KEYBOARD_KEY_F10                299
#define KEYBOARD_KEY_F11                300
#define KEYBOARD_KEY_F12                301
#define KEYBOARD_KEY_F13                302
#define KEYBOARD_KEY_F14                303
#define KEYBOARD_KEY_F15                304
#define KEYBOARD_KEY_F16                305
#define KEYBOARD_KEY_F17                306
#define KEYBOARD_KEY_F18                307
#define KEYBOARD_KEY_F19                308
#define KEYBOARD_KEY_F20                309
#define KEYBOARD_KEY_F21                310
#define KEYBOARD_KEY_F22                311
#define KEYBOARD_KEY_F23                312
#define KEYBOARD_KEY_F24                313
#define KEYBOARD_KEY_F25                314
#define KEYBOARD_KEY_KP_0               320
#define KEYBOARD_KEY_KP_1               321
#define KEYBOARD_KEY_KP_2               322
#define KEYBOARD_KEY_KP_3               323
#define KEYBOARD_KEY_KP_4               324
#define KEYBOARD_KEY_KP_5               325
#define KEYBOARD_KEY_KP_6               326
#define KEYBOARD_KEY_KP_7               327
#define KEYBOARD_KEY_KP_8               328
#define KEYBOARD_KEY_KP_9               329
#define KEYBOARD_KEY_KP_DECIMAL         330
#define KEYBOARD_KEY_KP_DIVIDE          331
#define KEYBOARD_KEY_KP_MULTIPLY        332
#define KEYBOARD_KEY_KP_SUBTRACT        333
#define KEYBOARD_KEY_KP_ADD             334
#define KEYBOARD_KEY_KP_ENTER           335
#define KEYBOARD_KEY_KP_EQUAL           336
#define KEYBOARD_KEY_LEFT_SHIFT         340
#define KEYBOARD_KEY_LEFT_CONTROL       341
#define KEYBOARD_KEY_LEFT_ALT           342
#define KEYBOARD_KEY_LEFT_SUPER         343
#define KEYBOARD_KEY_RIGHT_SHIFT        344
#define KEYBOARD_KEY_RIGHT_CONTROL      345
#define KEYBOARD_KEY_RIGHT_ALT          346
#define KEYBOARD_KEY_RIGHT_SUPER        347
#define KEYBOARD_KEY_MENU               348

#define KEYBOARD_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define KEYBOARD_MOD_CONTROL         0x0002
 /*! @brief If this bit is set one or more Alt keys were held down.
  *
  *  If this bit is set one or more Alt keys were held down.
  */
#define KEYBOARD_MOD_ALT             0x0004
  /*! @brief If this bit is set one or more Super keys were held down.
   *
   *  If this bit is set one or more Super keys were held down.
   */
#define KEYBOARD_MOD_SUPER           0x0008
   /*! @brief If this bit is set the Caps Lock key is enabled.
	*
	*  If this bit is set the Caps Lock key is enabled and the @ref
	*  KEYBOARD_LOCK_KEY_MODS input mode is set.
	*/
#define KEYBOARD_MOD_CAPS_LOCK       0x0010
	/*! @brief If this bit is set the Num Lock key is enabled.
	 *
	 *  If this bit is set the Num Lock key is enabled and the @ref
	 *  KEYBOARD_LOCK_KEY_MODS input mode is set.
	 */
#define KEYBOARD_MOD_NUM_LOCK        0x0020
}
