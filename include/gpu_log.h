#ifndef __graphic_engine_include_gpu_log_H__
#define __graphic_engine_include_gpu_log_H__

/* gpu_log.h
 *
 * gpu日志相关代码： 覆盖common部分关于Log_XXX系定义
 *
 *
 * 作者: ke.zhonghua@o-film.com
 * 日期: 2017/06/01
 * 版权: 上海欧菲智能车联
 *
 */

#include <log/log.h>

extern LogCtrlConfig Gpu_Global_Logctrl_cfg; //全局日志控制配置

//取消之前的宏定义，取代为新的
#undef Log_Error
#undef Log_Warning
#undef Log_Message
#undef Log_Debug

//定义新的宏块时，只取更改以下定义块中引用的控制块名称Gpu_Global_Logctrl_cfg
#define Log_Error(fmt, arg...) _Log_String(DEBUG_LEVEL_ERROR, Gpu_Global_Logctrl_cfg, fmt, ##arg)
#define Log_Warning(fmt, arg...) _Log_String(DEBUG_LEVEL_WARNING, Gpu_Global_Logctrl_cfg, fmt, ##arg)
#define Log_Message(fmt, arg...) _Log_String(DEBUG_LEVEL_MESSAGE, Gpu_Global_Logctrl_cfg, fmt, ##arg)
#define Log_Debug(fmt, arg...) _Log_String(DEBUG_LEVEL_DEBUG, Gpu_Global_Logctrl_cfg, fmt, ##arg)


#endif
