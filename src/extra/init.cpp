/*
 * init.cpp
 *
 * graphic_engin初始化代码，目标是完成预处理
 * 功能:(持续修改)
 *   1. 日志初始化
 *
 * 作者: ke.zhonghua@o-film.com
 * 日期: 2017/06/01
 * 版权: 上海欧菲智能车联科技
 *
 */

#include <stdio.h>
#include <log/log.h>
#include <config/libconfig.h>
#include <utils/utils_func.h>
#include <gpu_log.h>

extern "C"
{
    extern LogCtrlConfig GpuLogctrl_Start[];
    extern LogCtrlConfig GpuLogctrl_End[];
};

//定义GPU的日志控制结构
LogCtrlConfig Gpu_Global_Logctrl_cfg = {0, -1, "GPU", "Graphic_Engine"};

//注册所有的日志控制块
void InitStaticLogctrls()
{
    //获得全局日志级别做为默认日志级别
    uint32_t global_debug_level = GetCurrentGlobalDebugLevel();
    config_t config;

    config_init(&config);
    config_read_file(&config, "app.cfg");

    //初始化全局
//    UpdateNamedLogctrlFromConfig(&Gpu_Global_Logctrl_cfg, &config, global_debug_level);
    //注册全局
    RegisterLogctrlConfig(&Gpu_Global_Logctrl_cfg);

    LogCtrlConfig* cfg = GpuLogctrl_Start;
    while(cfg < GpuLogctrl_End)
    {
//        UpdateNamedLogctrlFromConfig(cfg, &config, global_debug_level);
        RegisterLogctrlConfig(cfg);
        cfg++;
    }
}

void __attribute__((constructor)) setup(void)
{
    InitStaticLogctrls();
}
