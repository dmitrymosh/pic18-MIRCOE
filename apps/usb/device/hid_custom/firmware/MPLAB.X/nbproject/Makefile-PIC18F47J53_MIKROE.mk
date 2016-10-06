#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-PIC18F47J53_MIKROE.mk)" "nbproject/Makefile-local-PIC18F47J53_MIKROE.mk"
include nbproject/Makefile-local-PIC18F47J53_MIKROE.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC18F47J53_MIKROE
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic18f47j53_microe/system.c ../src/app_device_custom_hid.c ../src/app_led_usb_status.c ../src/main.c ../src/usb_descriptors.c ../src/files.c ../../../../../../bsp/pic18f47j53_microe/buttons.c ../../../../../../bsp/pic18f47j53_microe/leds.c ../../../../../../bsp/pic18f47j53_microe/rtcc.c ../../../../../../bsp/pic18f47j53_microe/Stepper.c ../../../../../../framework/fileio/src/fileio.c ../../../../../../framework/driver/fileio/src/internal_flash.c ../../../../../../framework/usb/src/usb_device.c ../../../../../../framework/usb/src/usb_device_hid.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1820240409/system.p1 ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1 ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 ${OBJECTDIR}/_ext/1360937237/files.p1 ${OBJECTDIR}/_ext/1084567808/buttons.p1 ${OBJECTDIR}/_ext/1084567808/leds.p1 ${OBJECTDIR}/_ext/1084567808/rtcc.p1 ${OBJECTDIR}/_ext/1084567808/Stepper.p1 ${OBJECTDIR}/_ext/1706142600/fileio.p1 ${OBJECTDIR}/_ext/691844211/internal_flash.p1 ${OBJECTDIR}/_ext/838585624/usb_device.p1 ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1820240409/system.p1.d ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1.d ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d ${OBJECTDIR}/_ext/1360937237/main.p1.d ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d ${OBJECTDIR}/_ext/1360937237/files.p1.d ${OBJECTDIR}/_ext/1084567808/buttons.p1.d ${OBJECTDIR}/_ext/1084567808/leds.p1.d ${OBJECTDIR}/_ext/1084567808/rtcc.p1.d ${OBJECTDIR}/_ext/1084567808/Stepper.p1.d ${OBJECTDIR}/_ext/1706142600/fileio.p1.d ${OBJECTDIR}/_ext/691844211/internal_flash.p1.d ${OBJECTDIR}/_ext/838585624/usb_device.p1.d ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1820240409/system.p1 ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1 ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 ${OBJECTDIR}/_ext/1360937237/files.p1 ${OBJECTDIR}/_ext/1084567808/buttons.p1 ${OBJECTDIR}/_ext/1084567808/leds.p1 ${OBJECTDIR}/_ext/1084567808/rtcc.p1 ${OBJECTDIR}/_ext/1084567808/Stepper.p1 ${OBJECTDIR}/_ext/1706142600/fileio.p1 ${OBJECTDIR}/_ext/691844211/internal_flash.p1 ${OBJECTDIR}/_ext/838585624/usb_device.p1 ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1

# Source Files
SOURCEFILES=../src/system_config/pic18f47j53_microe/system.c ../src/app_device_custom_hid.c ../src/app_led_usb_status.c ../src/main.c ../src/usb_descriptors.c ../src/files.c ../../../../../../bsp/pic18f47j53_microe/buttons.c ../../../../../../bsp/pic18f47j53_microe/leds.c ../../../../../../bsp/pic18f47j53_microe/rtcc.c ../../../../../../bsp/pic18f47j53_microe/Stepper.c ../../../../../../framework/fileio/src/fileio.c ../../../../../../framework/driver/fileio/src/internal_flash.c ../../../../../../framework/usb/src/usb_device.c ../../../../../../framework/usb/src/usb_device_hid.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-PIC18F47J53_MIKROE.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F47J53
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1820240409/system.p1: ../src/system_config/pic18f47j53_microe/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820240409" 
	@${RM} ${OBJECTDIR}/_ext/1820240409/system.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1820240409/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1820240409/system.p1  ../src/system_config/pic18f47j53_microe/system.c 
	@-${MV} ${OBJECTDIR}/_ext/1820240409/system.d ${OBJECTDIR}/_ext/1820240409/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1820240409/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1: ../src/app_device_custom_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1  ../src/app_device_custom_hid.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.d ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1: ../src/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1  ../src/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.d ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/main.p1  ../src/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/main.d ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1: ../src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1  ../src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.d ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/files.p1: ../src/files.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/files.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/files.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/files.p1  ../src/files.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/files.d ${OBJECTDIR}/_ext/1360937237/files.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/files.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/buttons.p1: ../../../../../../bsp/pic18f47j53_microe/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/buttons.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/buttons.p1  ../../../../../../bsp/pic18f47j53_microe/buttons.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/buttons.d ${OBJECTDIR}/_ext/1084567808/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/leds.p1: ../../../../../../bsp/pic18f47j53_microe/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/leds.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/leds.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/leds.p1  ../../../../../../bsp/pic18f47j53_microe/leds.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/leds.d ${OBJECTDIR}/_ext/1084567808/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/rtcc.p1: ../../../../../../bsp/pic18f47j53_microe/rtcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/rtcc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/rtcc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/rtcc.p1  ../../../../../../bsp/pic18f47j53_microe/rtcc.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/rtcc.d ${OBJECTDIR}/_ext/1084567808/rtcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/rtcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/Stepper.p1: ../../../../../../bsp/pic18f47j53_microe/Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/Stepper.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/Stepper.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/Stepper.p1  ../../../../../../bsp/pic18f47j53_microe/Stepper.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/Stepper.d ${OBJECTDIR}/_ext/1084567808/Stepper.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/Stepper.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1706142600/fileio.p1: ../../../../../../framework/fileio/src/fileio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1706142600" 
	@${RM} ${OBJECTDIR}/_ext/1706142600/fileio.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1706142600/fileio.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1706142600/fileio.p1  ../../../../../../framework/fileio/src/fileio.c 
	@-${MV} ${OBJECTDIR}/_ext/1706142600/fileio.d ${OBJECTDIR}/_ext/1706142600/fileio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1706142600/fileio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/691844211/internal_flash.p1: ../../../../../../framework/driver/fileio/src/internal_flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/691844211" 
	@${RM} ${OBJECTDIR}/_ext/691844211/internal_flash.p1.d 
	@${RM} ${OBJECTDIR}/_ext/691844211/internal_flash.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/691844211/internal_flash.p1  ../../../../../../framework/driver/fileio/src/internal_flash.c 
	@-${MV} ${OBJECTDIR}/_ext/691844211/internal_flash.d ${OBJECTDIR}/_ext/691844211/internal_flash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/691844211/internal_flash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device.p1: ../../../../../../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device.p1  ../../../../../../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device.d ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device_hid.p1: ../../../../../../framework/usb/src/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device_hid.p1  ../../../../../../framework/usb/src/usb_device_hid.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device_hid.d ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1820240409/system.p1: ../src/system_config/pic18f47j53_microe/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820240409" 
	@${RM} ${OBJECTDIR}/_ext/1820240409/system.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1820240409/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1820240409/system.p1  ../src/system_config/pic18f47j53_microe/system.c 
	@-${MV} ${OBJECTDIR}/_ext/1820240409/system.d ${OBJECTDIR}/_ext/1820240409/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1820240409/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1: ../src/app_device_custom_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1  ../src/app_device_custom_hid.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.d ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_device_custom_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1: ../src/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1  ../src/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.d ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/main.p1  ../src/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/main.d ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1: ../src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1  ../src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.d ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/files.p1: ../src/files.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/files.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/files.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/files.p1  ../src/files.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/files.d ${OBJECTDIR}/_ext/1360937237/files.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/files.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/buttons.p1: ../../../../../../bsp/pic18f47j53_microe/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/buttons.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/buttons.p1  ../../../../../../bsp/pic18f47j53_microe/buttons.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/buttons.d ${OBJECTDIR}/_ext/1084567808/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/leds.p1: ../../../../../../bsp/pic18f47j53_microe/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/leds.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/leds.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/leds.p1  ../../../../../../bsp/pic18f47j53_microe/leds.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/leds.d ${OBJECTDIR}/_ext/1084567808/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/rtcc.p1: ../../../../../../bsp/pic18f47j53_microe/rtcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/rtcc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/rtcc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/rtcc.p1  ../../../../../../bsp/pic18f47j53_microe/rtcc.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/rtcc.d ${OBJECTDIR}/_ext/1084567808/rtcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/rtcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1084567808/Stepper.p1: ../../../../../../bsp/pic18f47j53_microe/Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1084567808" 
	@${RM} ${OBJECTDIR}/_ext/1084567808/Stepper.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1084567808/Stepper.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1084567808/Stepper.p1  ../../../../../../bsp/pic18f47j53_microe/Stepper.c 
	@-${MV} ${OBJECTDIR}/_ext/1084567808/Stepper.d ${OBJECTDIR}/_ext/1084567808/Stepper.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1084567808/Stepper.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1706142600/fileio.p1: ../../../../../../framework/fileio/src/fileio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1706142600" 
	@${RM} ${OBJECTDIR}/_ext/1706142600/fileio.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1706142600/fileio.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1706142600/fileio.p1  ../../../../../../framework/fileio/src/fileio.c 
	@-${MV} ${OBJECTDIR}/_ext/1706142600/fileio.d ${OBJECTDIR}/_ext/1706142600/fileio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1706142600/fileio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/691844211/internal_flash.p1: ../../../../../../framework/driver/fileio/src/internal_flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/691844211" 
	@${RM} ${OBJECTDIR}/_ext/691844211/internal_flash.p1.d 
	@${RM} ${OBJECTDIR}/_ext/691844211/internal_flash.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/691844211/internal_flash.p1  ../../../../../../framework/driver/fileio/src/internal_flash.c 
	@-${MV} ${OBJECTDIR}/_ext/691844211/internal_flash.d ${OBJECTDIR}/_ext/691844211/internal_flash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/691844211/internal_flash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device.p1: ../../../../../../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device.p1  ../../../../../../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device.d ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device_hid.p1: ../../../../../../framework/usb/src/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device_hid.p1  ../../../../../../framework/usb/src/usb_device_hid.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device_hid.d ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=pro -P -N255 -I"../src" -I"../../../../../../bsp/pic18f47j53_microe" -I"../../../../../../framework/usb/inc" -I"../src/system_config/pic18f47j53_microe" -I"../../../../../../framework/driver/fileio" -I"../../../../../../framework/fileio/inc" -I"../../../../../../framework" --warn=0 --asmlist -DXPRJ_PIC18F47J53_MIKROE=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC18F47J53_MIKROE
	${RM} -r dist/PIC18F47J53_MIKROE

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
