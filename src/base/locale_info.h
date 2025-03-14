﻿/**
 * File:   locale_info.h
 * Author: AWTK Develop Team
 * Brief:  locale_info
 *
 * Copyright (c) 2018 - 2025 Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-05-02 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_LOCALE_H
#define TK_LOCALE_H

#include "tkc/emitter.h"
#include "base/events.h"
#include "base/types_def.h"
#include "base/assets_manager.h"

BEGIN_C_DECLS

typedef const char* (*locale_info_tr_with_context_t)(void* ctx, const char* text);
typedef const char* (*locale_info_tr_t)(const char* text);

/**
 * @class locale_info_t
 * @annotation ["scriptable"]
 * 本地化信息。提供字符串翻译数据管理，当前语言改变的事件通知等等。
 *
 */
struct _locale_info_t {
  /**
   * @property {char*} country
   * @annotation ["readable"]
   * 国家或地区。如：CN
   */
  char country[3];
  /**
   * @property {char*} language
   * @annotation ["readable"]
   * 语言。如：zh
   */
  char language[3];
  /**
   * @property {assets_manager_t*} assets_manager
   * @annotation ["private"]
   * 资源管理器。
   */
  assets_manager_t* assets_manager;

  /*private*/
  char* name;
  int32_t refcount;
  const asset_info_t* strs;
  emitter_t* emitter;
  locale_info_tr_t fallback_tr;
  void* fallback_tr_ctx;
  locale_info_tr_with_context_t fallback_tr2;
  void* custom_tr_ctx;
  locale_info_tr_with_context_t custom_tr;
};

/**
 * @method locale_info
 * 获取缺省locale_info。
 * @alias locale_info_instance
 * @annotation ["constructor", "scriptable"]
 *
 * @return {locale_info_t*} 返回locale_info对象。
 */
locale_info_t* locale_info(void);

/**
 * @method locale_info_set
 * 设置缺省locale_info。
 * @param {locale_info_t*} locale_info locale_info对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_set(locale_info_t* locale_info);

/**
 * @method locale_info_create
 * 创建locale_info。
 * @annotation ["constructor"]
 * @param {const char*} language 语言。
 * @param {const char*} country 国家或地区。
 *
 * @return {locale_info_t*} 返回locale_info对象。
 */
locale_info_t* locale_info_create(const char* language, const char* country);

/**
 * @method locale_info_create_ex
 * 创建locale_info。
 * @annotation ["constructor"]
 * @param {const char*} language 语言。
 * @param {const char*} country 国家或地区。
 * @param {assets_manager_t*} am 资源管理器。
 *
 * @return {locale_info_t*} 返回locale_info对象。
 */
locale_info_t* locale_info_create_ex(const char* language, const char* country,
                                     assets_manager_t* am);

/**
 * @method locale_info_tr
 * 翻译字符串。
 * @annotation ["scriptable"]
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {const char*} text 待翻译的文本。
 *
 * @return {const char*} 返回翻译之后的字符串。
 */
const char* locale_info_tr(locale_info_t* locale_info, const char* text);

/**
 * @method locale_info_change
 * 设置当前的国家和语言。
 * @annotation ["scriptable"]
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {const char*} language 语言。
 * @param {const char*} country 国家或地区。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_change(locale_info_t* locale_info, const char* language, const char* country);

/**
 * @method locale_info_on
 * 注册指定事件的处理函数。
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {event_type_t} type 事件类型，目前固定为EVT_LOCALE_CHANGED。
 * @param {event_func_t} on_event 事件处理函数。
 * @param {void*} ctx 事件处理函数上下文。
 *
 * @return {uint32_t} 返回id，用于locale_info_off。
 */
uint32_t locale_info_on(locale_info_t* locale_info, event_type_t type, event_func_t on_event,
                        void* ctx);

/**
 * @method locale_info_off
 * 注销指定事件的处理函数。
 * @annotation ["scriptable"]
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {uint32_t} id locale_info_on返回的ID。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_off(locale_info_t* locale_info, uint32_t id);

/**
 * @method locale_info_set_assets_manager
 * 设置资源管理器对象。
 *
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {assets_manager_t*} assets_manager 资源管理器。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_set_assets_manager(locale_info_t* locale_info, assets_manager_t* assets_manager);

/**
 * @method locale_info_reload
 * 重新加载字符串资源。
 *
 * @param {locale_info_t*} locale_info locale_info对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_reload(locale_info_t* locale_info);

/**
 * @method locale_info_set_fallback_tr
 * 设置候补翻译函数。
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {locale_info_tr_t} tr fallback翻译函数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_set_fallback_tr(locale_info_t* locale_info, locale_info_tr_t tr);

/**
 * @method locale_info_set_fallback_tr2
 * 设置候补翻译函数。
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {locale_info_tr_with_context_t} tr fallback翻译函数。
 * @param {void*} ctx 翻译函数的上下文。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_set_fallback_tr2(locale_info_t* locale_info, locale_info_tr_with_context_t tr,
                                   void* ctx);

/**
 * @method locale_info_set_custom_tr
 * 设置自定义的候补翻译函数。
 * > 有时我们需要优先加载用户自定义的翻译，加载失败才加载系统缺省的，可用设置一个函数去实现这类功能。
 * @param {locale_info_t*} locale_info locale_info对象。
 * @param {locale_info_tr_with_context_t} tr 自定义的翻译函数。
 * @param {void*} ctx 翻译函数的上下文。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_set_custom_tr(locale_info_t* locale_info, locale_info_tr_with_context_t tr,
                                void* ctx);

/**
 * @method locale_info_destroy
 * 释放全部资源并销毁locale_info对象。
 * @param {locale_info_t*} locale_info locale_info对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_info_destroy(locale_info_t* locale_info);

/**
 * @class locale_infos_t
 * @annotation ["fake", "scriptable"]
 * 在某些情况下，需要多个资源管理器。比如在手表系统里，每个应用或表盘，可能放在独立的资源包中，
 * 此时优先加载应用自己的资源，如果没有就加载系统的资源。
 */

/**
 * @method locale_infos_ref
 * 获取指定小应用程序(applet)的locale_info。
 * @annotation ["constructor", "scriptable", "static"]
 * @param {const char*} name 小应用程序(applet)的名称。
 *
 * @return {locale_info_t*} 返回locale_info对象。
 */
locale_info_t* locale_infos_ref(const char* name);

/**
 * @method locale_infos_unref
 * 释放指定小应用程序(applet)的locale_info。
 * @annotation ["deconstructor", "scriptable", "static"]
 * @param {locale_info_t*} locale_info locale_info对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_infos_unref(locale_info_t* locale_info);

/**
 * @method locale_infos_change
 * 设置全部locale_info的当前国家和语言。
 * @annotation ["scriptable", "static"]
 * @param {const char*} language 语言。
 * @param {const char*} country 国家或地区。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_infos_change(const char* language, const char* country);

/**
 * @method locale_infos_on
 * 注册指定事件的处理函数。
 * @annotation ["scriptable:custom", "static"]
 * @param {event_type_t} type 事件类型，目前有EVT_LOCALE_INFOS_LOAD_INFO、EVT_LOCALE_INFOS_UNLOAD_INFO。
 * @param {event_func_t} on_event 事件处理函数。
 * @param {void*} ctx 事件处理函数上下文。
 *
 * @return {uint32_t} 返回id，用于locale_infos_off。
 */
uint32_t locale_infos_on(event_type_t type, event_func_t on_event, void* ctx);

/**
 * @method locale_infos_off
 * 注销指定事件的处理函数。
 * @annotation ["scriptable", "static"]
 * @param {uint32_t} id locale_infos_on返回的ID。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_infos_off(uint32_t id);

/**
 * @method locale_infos_reload_all
 * 重新加载全部字符串资源。
 * @annotation ["scriptable", "static"]
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t locale_infos_reload_all(void);

typedef struct _str_pair_t {
  uint32_t key;
  uint32_t value;
} str_pair_t;

typedef struct _str_table_t {
  uint16_t version;
  uint16_t nr;
  str_pair_t strs[1];
} str_table_t;

const char* str_table_lookup(const str_table_t* table, const char* key);

END_C_DECLS

#endif /*TK_LOCALE_H*/
