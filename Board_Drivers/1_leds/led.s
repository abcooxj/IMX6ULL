.global _start/* 全局标号*/
_start:
    /*使能所有外设 */
    ldr r0, =0x020c4068 @CCGR0
    ldr r1, =0xffffffff @要向CCGR0写入数据
    str r1, [r0]        @将0xffffffff写入到CCGR0中

    ldr r0, =0x020c406c @CCGR1
    str r1, [r0]

    ldr r0, =0x020c4070 @CCGR2
    str r1, [r0]

    ldr r0, =0x020c4074 @CCGR3
    str r1, [r0]

    ldr r0, =0x020c4078 @CCGR4
    str r1, [r0]

    ldr r0, =0x020c407c @CCGR5
    str r1, [r0]

    ldr r0, =0x020c406c @CCGR6
    str r1, [r0]


/* 配置GPIO_IO03 pin的 复用GPIO,也就是设置*/
/* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03=5 */
/* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03寄存器地址为0x020E0068 */
    ldr r0, =0x020E0068 @IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03
    ldr r1, =0x5 @要写入数据
    str r1, [r0]        @将5写入到IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03CCGR0中


  /*配置GPIO1_IO03的电气属性 ，也就是寄存器
  * IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 
  * IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03的寄存器地址是0x020e2f4
  *
  * bit0:  0低速率
  * bit5:3: 110 R0/6驱动能力
  * bit7:6： 10 100MHZ速度 
  * bit11: 0关闭开漏输出
  * bit12: 1 使能pull/kepper
  * bit13: 0 kepper
  * bit15:14: 00 100k下拉
  * bit16:0 关闭 hys 
  * 通过以上bit可以得出bit0-bit16为0001 0000 1011 0000，十六进制为10B0
  */
    ldr r0, =0x020e02f4
    ldr r1,=0x10b0
    str r1,[r0]

/*设置GPIO
 *设置GPIO1_GDIR寄存器，设置GPIO1_GPIO3为输出
 *GPIO1_GDIR寄存器地址为0先09出，设置GPIO1_GDIR寄存器bit3为1，
 *也就是GPIO1_GPIO3为输出
 */
    ldr r0, =0x0209c004
    ldr r1, =0x8
    str r1,[r0]

/*打开LED，也就是设置GPIO1_GPIO3为0
 *GPIO1_DR寄存器地址为0x0209C000
 */
    ldr r0, =0x0209c000
    ldr r1, =0
    str r1,[r0]

loop:
    b loop
