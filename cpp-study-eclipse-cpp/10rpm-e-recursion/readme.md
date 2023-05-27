rpm-e-recursion 递归移除rpm文件  
移除文件的过程如下
```
[root@node1 yum.repos.d]# rpm -e php72w-common-7.2.22-1.w7.x86_64
error: Failed dependencies:
  php72w-common(x86-64) = 7.2.22-1.w7 is needed by (installed) php72w-cli-7.2.22-1.w7.x86_64
  php72w-common(x86-64) = 7.2.22-1.w7 is needed by (installed) php72w-pdo-7.2.22-1.w7.x86_64
  php72w-common(x86-64) = 7.2.22-1.w7 is needed by (installed) php72w-fpm-7.2.22-1.w7.x86_64
  php72w-common(x86-64) = 7.2.22-1.w7 is needed by (installed) php72w-gd-7.2.22-1.w7.x86_64
  php72w-common(x86-64) = 7.2.22-1.w7 is needed by (installed) php72w-mbstring-7.2.22-1.w7.x86_64
  php72w-common(x86-64) = 7.2.22-1.w7 is needed by (installed) php72w-bcmath-7.2.22-1.w7.x86_64
[root@node1 yum.repos.d]# rpm -e php72w-cli-7.2.22-1.w7.x86_64
error: Failed dependencies:
  php72w-cli(x86-64) = 7.2.22-1.w7 is needed by (installed) php72w-devel-7.2.22-1.w7.x86_64
[root@node1 yum.repos.d]# rpm -e php72w-devel-7.2.22-1.w7.x86_64
```
再次尝试移除将会出现下面的错误提示  
```
[root@node1 yum.repos.d]# rpm -e php72w-devel-7.2.22-1.w7.x86_64
error: package php72w-devel-7.2.22-1.w7.x86_64 is not installed
```

1.执行命令  
2.如果执行失败,使用  is needed by (installed)  拆分,前后各有空格   
3.进行移除

后来发现网上有个脚本,工程宣告报废
rpm-e-recursion.sh
```
#!/bin/sh

do_once(){
  rpm -e "$@"
  rpm -e "$@" 2>&1 | grep '(installed)'
}

for ((I=1; I<=5; ++I))
do
  #NEWDEPS="$(do_once "$@" $DEPS | awk '{print $6 $8}')"
  NEWDEPS="$(do_once "$@" $DEPS | sed -e 's/^.*(installed)//')"
  DEPS="$DEPS $NEWDEPS"
  echo $I $NEWDEPS
  if [ ! "$NEWDEPS" ]; then
    break
  fi
done
```
usage
```
./rpm-e-recursion.sh php72w-common-7.2.22-1.w7.x86_64
```