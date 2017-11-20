#!/bin/bash
ps aux|grep ans_server|awk '{print $2}'|xargs kill
echo 'ans_server kill sucess......'
