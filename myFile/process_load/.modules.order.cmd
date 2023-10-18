cmd_/home/yys/myFile/process_load/modules.order := {   echo /home/yys/myFile/process_load/load_monitor.ko; :; } | awk '!x[$$0]++' - > /home/yys/myFile/process_load/modules.order
