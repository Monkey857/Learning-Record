cmd_/home/yys/myFile/cmp/modules.order := {   echo /home/yys/myFile/cmp/cmp.ko; :; } | awk '!x[$$0]++' - > /home/yys/myFile/cmp/modules.order
