# this is used for compile the user defined oc demo
################################################################################

#if you have defined multiple demos by yourself, modify this file to compile the chosen demo.

#example for lwm2m

	#example for oc_agriculture_template
	ifeq ($(CONFIG_USER_DEMO), "oc_agriculture_template")	
		user_demo_src  = ${wildcard $(TARGET_DIR)/Demos/oc_agriculture_template/*.c}
		user_demo_inc = -I $(TARGET_DIR)/Demos/oc_agriculture_template
		user_hardware_src = ${wildcard $(TARGET_DIR)/Hardware/E53_IA1/*.c} 
		user_hardware_inc = -I ${wildcard $(TARGET_DIR)/Hardware/E53_IA1}
		user_demo_defs = -D CONFIG_OC_ARRICULTURE_DEMO_ENABLE=1
		
	endif

	C_SOURCES += $(user_demo_src)
	C_INCLUDES += $(user_demo_inc)
	C_SOURCES += $(user_hardware_src)
	C_INCLUDES += $(user_hardware_inc)
	C_DEFS += $(user_demo_defs)
