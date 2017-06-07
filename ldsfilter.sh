#!/bin/bash
#
#临时性方案，在输入流的rodata1后追加指定内容

found=""
filled=""
prefix=""

if [ $# -ge 1 ] ; then
    prefix=$1
else
    prefix="Logctrl"
fi

while read line; do
    if [ "${line:1:1}" == "=" ] ; then
        if [ "$found" == "true" ]; then
            break
        fi
        found="true"
    else
        if [ ! -z "$found" ] ; then
            echo "$line"
            got=`echo $line|sed -n '/\.rodata1/p'`
            if [ ! -z "$got" ] ; then
    
                if [ -z "$filled" ] ; then
                echo ".logctrl :"
                echo "{"
                echo "  ${prefix}_Start = .;"
                echo "  *(.logctrl)"
                echo "  ${prefix}_End = .;"
                echo "}"
                fi
            fi
        fi
    fi
done