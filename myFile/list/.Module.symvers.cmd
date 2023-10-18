cmd_/home/yys/myFile/list/Module.symvers := sed 's/\.ko$$/\.o/' /home/yys/myFile/list/modules.order | scripts/mod/modpost -m -a  -o /home/yys/myFile/list/Module.symvers -e -i Module.symvers   -T -
