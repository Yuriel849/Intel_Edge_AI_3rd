cmd_/home/ubuntu/pi_bsp/drivers/p369_irq_kmalloc_complete/ledkey_dev.mod := printf '%s\n'   ledkey_dev.o | awk '!x[$$0]++ { print("/home/ubuntu/pi_bsp/drivers/p369_irq_kmalloc_complete/"$$0) }' > /home/ubuntu/pi_bsp/drivers/p369_irq_kmalloc_complete/ledkey_dev.mod
