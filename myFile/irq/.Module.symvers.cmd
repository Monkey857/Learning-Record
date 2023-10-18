cmd_/home/yys/myFile/Module.symvers := sed 's/\.ko$$/\.o/' /home/yys/myFile/modules.order | scripts/mod/modpost -m -a  -o /home/yys/myFile/Module.symvers -e -i Module.symvers   -T -
