CROSS_COMPILE 	?= arm-linux-gnueabihf-
TARGET		  	?= touch

CC 				:= $(CROSS_COMPILE)gcc -fgnu89-inline
LD				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump

LIBPATH			:=  -lgcc -L /usr/local/arm/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/7.5.0


INCDIRS 		:= imx6u \
				   bsp/clk \
				   bsp/led \
				   bsp/delay \
				   bsp/beep \
				   bsp/key \
				   bsp/gpio \
				   bsp/int \
				   bsp/exit \
				   bsp/epit \
				   bsp/keyfilter \
				   bsp/uart \
				   bsp/lcd \
				   bsp/rtc \
				   bsp/i2c \
				   bsp/ap3216c \
				   bsp/spi \
				   bsp/icm20608 \
				   bsp/touchscreen \
				   stdio/include

				   			   
SRCDIRS			:= project \
				   bsp/clk \
				   bsp/led \
				   bsp/delay \
				   bsp/beep \
				   bsp/key \
				   bsp/gpio \
				   bsp/int \
				   bsp/exit \
				   bsp/epit \
				   bsp/keyfilter \
				   bsp/uart \
				   bsp/lcd \
				   bsp/rtc\
				   bsp/i2c \
				   bsp/ap3216c \
				   bsp/spi \
				   bsp/icm20608 \
				   bsp/ft5426 \
				   bsp/touchscreen \
				   stdio/lib
				   
				   
INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))

SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR		:= $(notdir  $(SFILES))
CFILENDIR		:= $(notdir  $(CFILES))

SOBJS			:= $(patsubst %, obj/%, $(SFILENDIR:.S=.o))
COBJS			:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))
OBJS			:= $(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS)

.PHONY: clean
	
$(TARGET).bin : $(OBJS)
	$(LD) -Timx6u.lds -o $(TARGET).elf $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -fno-builtin -c -O2  $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
		$(CC) -Wall -march=armv7-a -mfpu=neon-vfpv4 -mfloat-abi=hard -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O2  $(INCLUDE) -o $@ $<

	
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)

	
print:
	@echo INCLUDE = $(INCLUDE)
	@echo SFILES=$(SFILES)
	@echo CFILES=$(CFILES)
	@echo SFILENDIR=$(SFILENDIR)
	@echo CFILENDIR=$(CFILENDIR)
	@echo SOBJS=$(SOBJS)
	@echo COBJS=$(COBJS)
	@echo OBJS=$(OBJS)


