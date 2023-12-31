[TOC]

# `NVIC Configuration`

## FTM和PWT

FTM(FlexTimer Module)和PWT(Pulse Width Timer)都是XL6600微控制器中的重要定时模块,主要用于定时和输入捕捉功能。

FTM的主要特点:

- 包含2个全功能FTM(FTM0/FTM1)和1个基本FTM(FTM2)
- 每个FTM包含4个通道,可配置为输入捕捉或输出比较
- 支持边沿对齐PWM,中心对齐PWM,以及组合模式
- 16位可重载计数器,支持各种计数模式
- 支持多个硬件触发源
- 可产生中断

PWT的主要特点:

- 包含1个16位定时计数器
- 4个脉冲宽度捕捉通道
- 支持正脉冲和负脉冲的宽度捕捉
- 可编程触发沿选择
- 2个可选时钟源
- 可设定溢出和脉冲宽度中断

综上,FTM可用于精确定时和波形输出控制,而PWT专门用于捕捉和测量脉冲宽度,两者互补。在汽车电子中,可用于电机控制、采集传感器信号等场景。需要根据具体要求选择使用。

## FTM1

根据XL6600DE用户手册DOC1中的相关章节,对FTM1的解读如下:

1. **FTM1属于定时器模块,是FlexTimer模块的一种,用于提供定时/计数、输入捕捉、输出比较、PWM等功能。**

2. FTM1 contains 4 channels, numbered 0-3. 每个通道都可以独立配置为输入捕捉或输出比较模式。

3. FTM1可以选择不同的时钟源:

    - 内部总线时钟

    - 内部固定频率时钟(ICSFFCLK) 

    - 外部时钟(通过TCLK引脚输入)

4. FTM1支持以下功能:

    - 16位可重载计数器,支持计数溢出中断

    - 输入捕捉模式,可捕捉通道引脚上的脉冲时间

    - 输出比较模式,比较匹配时可输出不同级别电平

    - 支持边沿对齐PWM和中间对齐PWM

    - 多个FTM可以通过硬件同步产生联合的PWM

    - 支持断路检测等故障保护功能

5. FTM1可以触发ADC转换,通过配置SIM_SOPT1[ADHWT]实现。

6. FTM1的中断优先级通过NVIC配置。

7. FTM1需要先通过SIM_SCGC寄存器打开模块时钟,然后配置控制寄存器实现需求功能。

以上是根据用户手册对FTM1外设的简要解读。

## FTM和CH

CH在FTM模块中代表通道(Channel)。每个FTM包含一定数量的CH,这些通道可以配置为不同的工作模式。

FTM和CH的关系如下:

1. FTM包含多个CH, XL6600的FTM0/1包含4个CH,FTM2包含8个CH。

2. 每个CH都可以独立配置为输入捕捉或输出比较模式。

3. 在输出比较模式下,CH可产生PWM输出波形。

4. 在输入捕捉模式下,CH可捕捉外部信号的脉冲边沿并产生中断。

5. 多个CH可配合实现联合PWM输出、复杂波形输出等功能。

6. 每个CH都有匹配标志可以触发中断。

7. CH共享FTM的计数器和时钟源。

总之,FTM的通道CH是FTM实现定时捕捉和波形输出的基本单元。

正确配置和运用FTM的CH,可以实现输出PWM控制马达、生成三角波等多种功能,是FTM的核心部件。

CH为FTM提供了独立可编程的时间/波形单元,使FTM的使用更加灵活。

## PTB8

根据 XL6600DE 用户手册,我对 PTB8 引脚的解读如下:

1. **PTB8 是 XL6600DE 的一个通用 I/O 口,可配置为数字输入或数字输出。**

2. PTB8 默认映射为 GPIO 功能,可以通过端口数据方向寄存器 (PTB_PDDR) 控制其方向。

3. PTB8 可配置为外部中断输入(IRQ),通过配置引脚中断模块的请求状态和控制寄存器(IRQSC)来实现。

4. 配置为外部中断输入时,中断请求由 PTB8 的下降沿、上升沿或高/低电平触发。

5. PTB8 外部中断可映射到中断请求源 IRQ1,通过 NVIC 设置中断优先级进行服务。

6. PTB8 还可以映射到 KBI0 模块,配置为键盘中断输入引脚。

7. PTB8 可以在低功耗模式下唤醒芯片。

8. PTB8 支持配置数字滤波器,滤除毛刺干扰。

9. PTB8 支持配置内部上拉电阻。

10. PTB8 支持配置为大电流驱动输出。

11. 在使用 PTB8 功能前,需要通过 SIM 时钟模块使能端口时钟。

以上是我根据 XL6600DE 用户手册对 PTB8 引脚的解读,提供了该引脚的主要特性、功能和配置方法。

---

# `FTM_InputCaptureInit`

根据代码注释和文档,这段代码是用来初始化FTM的输入捕获功能的。

首先 disables FTM 计数器:
```c
FTMx->SC  = 0x0;     /* disable counter */
```

然后将 FTM 模数寄存器设置为最大值0xFFFF,让 FTM 以自由运行模式运行:
```c 
FTMx->MOD = 0xFFFF;  /* free running */
```

接着根据传入的捕获沿选择配置指定通道的状态和控制寄存器CnSC:
- 如果选择上升沿捕获,则置位CnSC的CHIE和ELSA位:

  ```c
  FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSA_MASK;
  ```
  
- 如果选择下降沿捕获,则置位CnSC的CHIE和ELSB位:  
    ```c
    FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSB_MASK;
    ```
- 如果选择双边沿捕获,则同时置位CnSC的CHIE、ELSA和ELSB位:
    ```c  
    FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK;
    ```

其中CHIE位用于使能输入捕获中断,ELSA和ELSB位用于配置捕获沿。

总之,该函数实现了配置FTM指定通道为输入捕获模式并设置捕获沿的功能。

# `BatFilter()`

BatFilter 是XL6600系列MCU中的一个输入滤波器,全称为去抖滤波器(Debouncing Filter)。

它的作用是对MCU的某些输入引脚(如GPIO、FTM、I2C、PWT、IRQ等)进行滤波,以滤除输入信号中的毛刺干扰。 

BatFilter的工作原理是:

1. 它可以配置输入信号的脉冲宽度阈值,一般配置为1~4096个总线时钟周期。

2. 当输入信号的脉冲宽度小于配置的阈值,会被判断为毛刺而被滤除。

3. 如果输入信号的脉冲宽度大于2倍的 configured 阈值,则会被保留作为有效信号输入。

4. 在1~2倍阈值范围内的信号会不确定被滤除或保留。

BatFilter 的好处是可以过滤出短暂的毛刺干扰,避免这些毛刺导致MCU误判输入信号的电平变化。它可以提高MCU对输入信号变化边沿的检测精度。

BatFilter 通过PORT模块的两个寄存器PORT_IOFLT0和PORT_IOFLT1来配置。每个端口的输入信号可以配置不同的滤波时间阈值。

正确配置BatFilter有助于提高MCU在恶劣环境下的抗干扰能力和稳定性。但过滤时间过长也会增加输入信号的延迟。所以需要根据应用场景需求来权衡配置滤波时间的长短。

## Batt(to)AD

在 XL6600 MCU 中,Bat 信号到 AD 的转换主要通过模数转换器(ADC)模块来实现。

1. Bat信号需要连接到ADC模块的模拟输入引脚。XL6600 的ADC模块有多达24个模拟输入通道,其中通道AD22是连接到内部温度传感器,通道AD23连接到内部基准电压。所以Bat信号可以连接到AD0到AD21之間的任意一个模拟输入通道。

2. 配置ADC模块,选择Bat信号对应的模拟输入通道作为转换通道,配置ADC的时钟来源、采样时间等参数。

3. 配置ADC的转换触发来源,可以选择软件触发、硬件定时触发、或外部事件触发等。

4. 启动ADC转换,当ADC完成模数转换后,转换结果会自动传输到ADC数据寄存器。

5. 读取ADC数据寄存器,即可获得Bat电压转换后的数字量化值。

6. 根据ADC模块的参考电压和转换精度参数,可以计算出Bat的模拟电压值。

XL6600的ADC模块支持12位分辨率,最大转换率为1Msps。通过配置采样时间,可以适用于不同频率的Bat输入信号。

ADC同时也支持硬件平均值滤波、中断检测等功能,可以实现复杂的Bat信号分析和处理。

总之,XL6600通过ADC模块提供了将Bat信号准确而灵活地转换为数字量的完整流程和功能支持。配合单片机强大的计算能力,可以实现精确的电池电压检测与管理。

---

# LIN

---

## NAD

NAD在LIN协议中代表节点地址(Node Address)。它是LIN网络中每个节点的唯一地址标识。

NAD的主要作用有:

1. 标识网络节点:每个节点都有一个唯一的NAD,用于区分网络中的不同节点。
2. 地址识别:当主节点发送报文时,会在报文的标识符字段包含目标节点的NAD,被地址识别的节点会解析该报文。
3. 区分报文类型:NAD为0x3C或0x3D时,表示诊断报文;NAD为0x7F时,表示配置报文。
4. 起始字节:所有LIN报文的第一个字节都是NAD字节。
5. 同步标志:只有收到包含自己NAD的报文,节点才会重新同步自己的时间基准。
6. 网络管理:可以通过NAD识别网络拓扑,设置节点属性等。
7. 错误检测:接收非法NAD会记录在接收错误计数器中。

所以NAD是每个LIN节点的网络身份标识,所有节点必须有唯一的NAD才能加入LIN网络,并正确进行LIN通信。它类似于以太网中的MAC地址,对LIN协议实现起关键作用。

## PID

PID在LIN协议中代表报文标识符(Packet Identifier)。它用来表示LIN网络中的不同类型的报文。

PID的主要作用有:

1. 区分报文内容:不同PID表示不同的报文数据内容和格式。

2. 地址过滤:节点可以根据PID来过滤和接收自己需要处理的报文。

3. 优先级区分:PID的数值代表了报文的优先级,数值越小优先级越高。

4. 网络识别:PID可以标识网络的不同分段,如诊断、运动控制等。

5. 标识类型:如enhanced PID在60-7F表示诊断报文,F0-FF表示配置报文。

6. 检错标志:接收错误的PID会记录在接收错误计数器中。

7. 同步标志:只有收到PID在自己的接收列表中,节点才重新同步时间基准。

PID与NAD一起,构成了LIN报文的标识符,表示报文的地址和内容。正确解析PID非常重要,否则节点无法知道报文是属于自己的,也无法判断报文类型。

所以PID让节点可以有选择性地接收自己需要的报文,滤除无用报文,提高 LIN 网络的实时性和效率。是LIN协议不可或缺的一部分。

---

## SBC

SBCModule通常指System Basis Chip Module,即系统基础芯片模块。

在XL6600微控制器中,SBCModule对应的是SBC(System Basis Controller)系统基础控制器模块。

SBC模块的主要作用包括:

1. 系统状态控制:
通过状态标志控制器件的不同状态,如上电复位、看门狗复位等。

2. 系统时钟控制:
包含时钟门控寄存器,可以控制各外设时钟的使能。

3. 引脚复用控制:
可以通过复用寄存器配置引脚的不同功能。

4. 调试模式控制:
可配置微控制器进入调试模式。

5. 系统配置管理:
包含器件配置信息的只读寄存器,如Flash大小等。

6. 总线时钟输出控制:
可将系统时钟输出到引脚,供外部器件使用。

7. 系统保护控制:
包含系统写保护等功能。

8. 中断控制:
可 Mask 和 Unmask 中断。

SBC模块对XL6600的系统级控制非常关键,需要在开发初期进行SBC的正确配置,实现对MCU的初始化。

所以SBC可以看作是XL6600的系统管理模块,对MCU执行控制非常重要。

# ARM

## BAT

BAT(Block Address Translation) 是 ARM 中的一种地址转换机制,用于在不同的地址空间之间进行地址映射。

BAT 主要包含下面两个寄存器:

- DBAT 寄存器(Data BAT Registers):用于数据地址转换
- IBAT 寄存器(Instruction BAT Registers):用于指令地址转换

每个 BAT 寄存器包含输入地址的高低位、块大小以及输出地址的高低位。

BAT 的工作原理如下:

当 CPU 发出数据或指令访问时,会比较输入地址的高位与 DBAT/IBAT 中的输入地址范围是否匹配。

如果匹配成功,则会使用 DBAT/IBAT 中配置的输出地址高低位,结合输入地址低位,计算出最终的物理地址。

如果不匹配,则表示这个地址不需要转换,直接将输入地址作为物理地址输出。

通过 BAT,可以很方便地在不同地址空间中进行地址映射,使用不连续的物理地址对连续的逻辑地址进行映射。

BAT 常用于嵌入式系统中实现内存映射,或者处理器与外设之间的内存映射。它可以减少地址转换的开销,提高地址转换的性能。

# SysTick

SysTick 是 ARM Cortex-M 系列处理器中的一个特殊定时器。它提供了一个方便的方式来生成固定间隔的中断，并用于实现操作系统的任务调度、时钟管理等功能。

以下是一些与 SysTick 相关的操作：

1. 初始化 SysTick：在启用 SysTick 之前，需要对其进行初始化设置。主要包括设置 SysTick 加载值（Load Value）和使能 SysTick。

   `````c
   SysTick->LOAD = SystemCoreClock / desired_frequency - 1;   // 设置 SysTick 加载值
   SysTick->VAL = 0;                                          // 清零当前值
   SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |                // 选择处理器时钟作为 SysTick 时钟源
                   SysTick_CTRL_TICKINT_Msk |                  // 使能 SysTick 中断
                   SysTick_CTRL_ENABLE_Msk;                    // 使能 SysTick
   ```

2. SysTick 中断处理：当 SysTick 计数器达到零时，将触发 SysTick 中断。在中断处理函数中，可以执行一些任务调度或其他操作。

   ````c
   void SysTick_Handler(void) {
       // 执行任务调度或其他操作
   }
   ```

3. 获取 SysTick 当前值：可以通过读取 SysTick 计数器的当前值来获取经过的时间。

   ````c
   uint32_t current_value = SysTick->VAL;
   ```

4. 延时函数：通过使用 SysTick 定时器，可以实现一定的延时功能。

   ````c
   void delay_ms(uint32_t milliseconds) {
       uint32_t start_time = SysTick->VAL;
       uint32_t time_difference;
   
       do {
           time_difference = start_time - SysTick->VAL;
       } while (time_difference < (SystemCoreClock / 1000u) * milliseconds);
   }
   ```

这些是与 SysTick 相关的一些基本操作。SysTick 可以根据具体的应用来使用，例如用于实现操作系统的时钟节拍、任务调度、精确延时等功能。

希望这个梳理对你有帮助！如果你还有其他问题，请随时提问。

# PWM

PWM(脉宽调制)是一种重要的调制方式,经常被使用在许多微控制器和嵌入式系统中。

PWM 的主要特点是:

1. PWM信号具有固定频率,但变化占空比。通过改变PWM波形的占空比来调节其效果。

2. 占空比是PWM波形在一个周期内高电平时间与周期时间比值。一般用百分比表示。

3. 通过平均电压来调控其连续参数,例如电机的转速。

4. PWM不会影响PWM信号频率成分,只会改变PWM信号的幅值成分。

5. PWM信号易于通过数字电路来产生,只需要计数器和比较器。

PWM的典型应用有:

1. 电机速度控制 - 通过改变PWM占空比控制电机工作电压从而改变转速。

2. LED亮度控制 - 通过改变PWM占空比来改变LED平均电流从而改变亮度。

3. 电源电压调节 - 通过PWM控制开关管的导通时间来调节输出电压大小。

4. 音量控制 - 改变PWM占空比以改变音频放大器的增益。

5. 馈电控制 - 改变占空比以控制变压器的驱动信号。

XL6600 MCU通过FTM(灵活定时器模块)可以方便生成pwm信号,来实现对电机、LED等负载的控制。

## PWM和继电器或MOSFET

PWM信号可以用于驱动继电器或MOSFET,从而对负载进行控制。PWM和继电器/MOSFET的关系主要体现在以下几点:

1. PWM信号可以用来驱动继电器的触点开关。通过PWM信号的占空比来控制继电器接通时间比例,从而调节继电器输出的平均电压/电流。

2. PWM信号可以用来驱动MOSFET的栅极。MOSFET工作在线性区时,PWM占空比决定MOS管的导通时间,从而控制MOS管的平均输出电流。

3. PWM信号可以通过低通滤波生成类似模拟电压信号,用来驱动继电器或者MOSFET的栅极。这种方法可以获得比PWM数字信号更平滑的模拟控制。

4. 对于需要较大输出功率的应用,可以使用PWM信号驱动MOSFET或者IGBT,再由MOSFET/IGBT驱动继电器实现大功率加载的控制。

5. 在开关电源等应用中,PWM信号用于直接驱动MOSFET实现DC-DC转换。通过改变PWM占空比可以调节输出电压。

6. 可以使用PWM与MOSFET组合来实现无刷DC电机的驱动。

7. PWM信号还可以通过光耦节电路驱动隔离栅极驱动器或MOS管驱动器。

综上所述,PWM技术通过对MOSFET和继电器的控制,可以实现对各种负载电压、电流的连续可调控制,是XL6600系列MCU中非常重要的控制方式。

```

```

