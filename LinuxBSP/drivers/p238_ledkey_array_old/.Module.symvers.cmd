cmd_/home/ubuntu/pi_bsp/drivers/p238_ledkey_array/Module.symvers :=  sed 's/ko$$/o/'  /home/ubuntu/pi_bsp/drivers/p238_ledkey_array/modules.order | scripts/mod/modpost -m -a    -o /home/ubuntu/pi_bsp/drivers/p238_ledkey_array/Module.symvers -e -i Module.symvers -T - 
