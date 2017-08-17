#!/bin/bash

#自动提取版本号相关信息，生成version.c

#版本号
label_version="version(str):"
version=`grep -iEo "^\s*version\s*=\s*([0-9,A-F]*\.[0-9]*\.[0-9]*\.[0-9])\s*" version.txt |awk '{print $3}'`

#git SHA号
label_git_sha="git-sha(str):"
sha=`git log -n 1 2>/dev/null |head -n1 |grep -i "commit"|awk '{print $2}'`

#提交者，一旦有本地未提交，可追溯
label_git_author="git-author(str):"
git_author=`git log -n 1 2>/dev/null|grep -i "Author"|awk '{print $2}'`

#提交时间，快速找到代码日期
label_git_date="git-date(str):"
git_date1=`git log -n 1 2>/dev/null|grep -i "Date:"|sed 's/Date:\s*//'|awk '{print $2" " $3" " $4" "$5}'`
git_date=`date "+%Y/%m/%d %H:%M" -d "${git_date1}"`

#是否是库上最新版本并且没有修改
label_git_modified="git-modified(char):"
modified=`git status 2>/dev/null|grep -io "Changes not staged for commit"`
if [ -z "$modified" ] ; then
  modified=`git status 2>/dev/null|grep -io "Untracked files"`
  if [ -z "$modified" ] ; then
      modified=`git status 2>/dev/null|grep -io "Changes to be committed:"` #有add过，未commit的修改
  fi
fi

#检查是否有本地提交
label_git_locale="git-locale(char):"
locale=`git cherry 2>/dev/null`
if [ -z "$locale" ] ; then
  locale="0" #无本地提交
else
  locale="1" #有本地提交
fi

#分支
label_git_branch="git-branch(str):"
branch=`git branch 2>/dev/null|grep "\*"|awk '{print $NF}'`

if [ -z "$modified" ] ; then
  modified=0
else
  modified=1
fi

#构建时间
label_build_time="build-time(str):"
build_time=`date "+%Y/%m/%d %H:%M"`

#version_src="${dir_name}/version.c"

attribute=' __attribute__((section(".gitvsec"))) '

#生成版本文件
cat<<EOF
#include "version.h"
#include "reuse.h"
#include <string.h>
#include <stdio.h>

/* This file is generate automatelly, please donot touch it
 * This file will be deleted if the application was build successfully
 */
static const char label_version[] = "$label_version";
static const char version[] $attribute= "$label_version$version";
static const char label_git_branch[] = "$label_git_branch";
static const char branch[] $attribute= "$label_git_branch$branch";
static const char label_git_sha[] = "$label_git_sha";
static const char sha[] $attribute= "$label_git_sha$sha";
static const char label_git_modified[] = "$label_git_modified";
static const char modified[] $attribute= "$label_git_modified$modified";
static const char label_git_locale[] = "$label_git_locale";
static const char locale[] $attribute="$label_git_locale$locale";
static const char label_git_author[] ="$label_git_author";
static const char git_author[] $attribute="$label_git_author$git_author";
static const char label_git_date[] = "$label_git_date";
static const char git_date[] $attribute="$label_git_date$git_date";
static const char label_build_time[] = "$label_build_time";
static const char build_time[] $attribute="$label_build_time$build_time";


__attribute__ ((visibility ("hidden"))) const char* get_version()
{
  return version + sizeof(label_version) - 1;
}

__attribute__ ((visibility ("hidden"))) const char* get_build_time()
{
    return build_time + sizeof(label_build_time) - 1;
}

__attribute__ ((visibility ("hidden"))) const char* get_git_branch()
{
  return branch + sizeof(label_git_branch) - 1;
}

__attribute__ ((visibility ("hidden"))) const char* get_git_sha()
{
  return sha + sizeof(label_git_sha) - 1;
}

__attribute__ ((visibility ("hidden"))) const char* get_git_author()
{
    return git_author + sizeof(label_git_author) - 1;
}

__attribute__ ((visibility ("hidden"))) const char* get_git_date()
{
    return git_date + sizeof(label_git_date) - 1;
}

__attribute__ ((visibility ("hidden"))) int is_git_clean()
{
  return *(modified + sizeof(label_git_modified) - 1) == '0';
}

__attribute__ ((visibility ("hidden"))) int has_locale_commit()
{
    return *(locale + sizeof(label_git_locale) - 1) == '1';
}



EOF

