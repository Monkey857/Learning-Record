cmd_/home/yys/myFile/addr_raddr/Module.symvers := sed 's/\.ko$$/\.o/' /home/yys/myFile/addr_raddr/modules.order | scripts/mod/modpost -m -a  -o /home/yys/myFile/addr_raddr/Module.symvers -e -i Module.symvers   -T -
