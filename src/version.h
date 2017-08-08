#ifndef __app_host_inc_version_h__
#define __app_host_inc_version_h__

#ifdef __cplusplus
extern "C"
{
#endif

//获取版本号
 __attribute__ ((visibility ("hidden"))) const char* get_version();

//获取SHA号
 __attribute__ ((visibility ("hidden"))) const char* get_git_sha();

//获取作者
 __attribute__ ((visibility ("hidden"))) const char* get_git_author();

//获取提交时间
 __attribute__ ((visibility ("hidden"))) const char* get_git_date();

//获取分支名
 __attribute__ ((visibility ("hidden"))) const char* get_git_branch();

//测试代码是否干净，即是否是最新版，是否有修改
 __attribute__ ((visibility ("hidden"))) int is_git_clean();

//是否有本地提交
 __attribute__ ((visibility ("hidden"))) int has_locale_commit();

//获取build时间:使用本脚本构建
 __attribute__ ((visibility ("hidden"))) const char* get_build_time();

#ifdef __cplusplus
};
#endif

#endif
