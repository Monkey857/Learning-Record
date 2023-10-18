cmd_/home/yys/myFile/cmp/Module.symvers := sed 's/\.ko$$/\.o/' /home/yys/myFile/cmp/modules.order | scripts/mod/modpost -m -a  -o /home/yys/myFile/cmp/Module.symvers -e -i Module.symvers   -T -
