cmd_/home/yys/myFile/list/modules.order := {   echo /home/yys/myFile/list/list.ko; :; } | awk '!x[$$0]++' - > /home/yys/myFile/list/modules.order
