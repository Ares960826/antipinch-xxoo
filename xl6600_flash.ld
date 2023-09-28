/*
*****************************************************************************
**
**  File        : xl6600x_flash.ld
**
**  Abstract    : Linker script for xl6600x Device with
**                256KByte FLASH, 24KByte DRAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : CHIPWAYS xl6600
**
**  Environment : Chipways Code Editor(R)
**
**  Distribution: The file is distributed as is, without any warranty
**                of any kind.
**
**  (c)Copyright Chipways.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Chipways permit registered Chipways Code Editor(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Chipways Code Editor(R) toolchain.
**
*****************************************************************************
*/


/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20001800;    /* end of 6K DRAM */

/* Generate a link error if heap and stack don't fit into DRAM */
_Min_Heap_Size  = DEFINED(__heap_size__)  ? __heap_size__  : 0x00000200;      /* required amount of heap  */
_Min_Stack_Size = DEFINED(__stack_size__) ? __stack_size__ : 0x00000800; /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
  /*Flash Storage = 128K*/
  m_vector (rx)				: ORIGIN = 0x00000000, LENGTH = 0x800	/*Align 2k = 0x800 6000forAPP 0000forboot*/ 
  m_factory_data (rx)				: ORIGIN = 0x00006800, LENGTH = 1K	/*BOOT APP FLAG1k = 0x400*/
  m_static_data (rx)				: ORIGIN = 0x00006C00, LENGTH = 1K	/*1k = 0x400*/
  m_dynamic_data0 (rx)			: ORIGIN = 0x00007000, LENGTH = 2K	/* eeprom size DYNAMIC */
  m_code (rx)				: ORIGIN = 0x00007800, LENGTH = 0x16800 /*84+6 k Rest = (0x18000 - 7000) */ 
  m_dynamic_data1 (rx)			: ORIGIN = 0x0001E000, LENGTH = 8K	/*BOOT FLAG eeprom size = size * 4 FROM END ADDRESS*/

  
  
  CRAM (xrw)      				 : ORIGIN = 0x1FFFE800, LENGTH = 0x1600
  C1RAM(xrw) 				 : ORIGIN = 0x1FFFFE00, LENGTH = 0x200
  DRAM (xrw)      				 : ORIGIN = 0x20000000, LENGTH = 10K  
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(8);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(8);
  } >m_vector
  
  .factory_data : AT(0x00006800)
  {
    _factory_data_start = .;
    . = ALIGN(8);
    *(.factory_data)
    . = _factory_data_start + 0x400;
  } >m_factory_data =0x0000
  . = ALIGN(8);
  
  .static_data : AT(0x00006C00)
  {
  	_static_data_start = .;
  	. = ALIGN(8);
  	*(.check_data) 
  	*(.static_data)
  	. = _static_data_start + 0x400;
  } >m_static_data =0x0000
 . = ALIGN(8);

 .dynamic_data0 : AT(0x00007000)
  {
  	_dynamic_data0_start = .;
  	. = ALIGN(8);  	
  	*(.dynamic_data0)
  	. = _dynamic_data0_start + 0x800;
  } >m_dynamic_data0 =0x0000
  . = ALIGN(8);  

  _flash_sidata = _dynamic_data0_start + 0x800;
  	
   .flash_ram : AT(_flash_sidata)
	{
		. = ALIGN(8);
		_flash_start = .;
	} >CRAM
	_flash_end1 = SIZEOF(.flash_ram);
	_flash_end = _flash_start + _flash_end1;

 .save_ram : AT(_flash_sidata + _flash_end1)
	{
		. = ALIGN(8);
		*( .save_ram) 
		 . = ALIGN(8);
	} >C1RAM
	_save_ram_size = SIZEOF(.save_ram );
 
  /* The program code and other data goes into FLASH */
  
  .text (_flash_sidata + _flash_end1 + _save_ram_size): 
  {
    . = ALIGN(8);
    *(.text)           /* .text sections (code) */
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(8);
    _etext = .;        /* define a global symbols at end of code */
  } >m_code
  . = ALIGN(8);
   .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >m_code
   . = ALIGN(8);
    .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
    } >m_code

	. = ALIGN(8);
  .ARM.attributes : { *(.ARM.attributes) } > m_code

	. = ALIGN(8);
  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >m_code
  	. = ALIGN(8);
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >m_code
  . = ALIGN(8);
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array*))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >m_code
  

     
  /* used by the startup to initialize data */
  . = ALIGN(8);
  _sidata = .;
  
	
  /* Initialized data sections goes into DRAM, load LMA copy after code */
  .data : AT ( _sidata )
  {
    . = ALIGN(8);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    . = ALIGN(8);
    _edata = .;        /* define a global symbol at data end */
  } >DRAM
  /* Uninitialized data section */
  . = ALIGN(8);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(8);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >DRAM

  PROVIDE ( end = _ebss );
  PROVIDE ( _end = _ebss );

  /* User_heap_stack section, used to check that there is enough DRAM left */
  ._user_heap :
  {
    . = ALIGN(8);
    . = . + _Min_Heap_Size;
    . = ALIGN(8);
    __HeapLimit = .;
  } >DRAM





  /* Initializes stack on the end of block */
  _estack   = ORIGIN(DRAM) + LENGTH(DRAM);
  __StackLimit = _estack - _Min_Stack_Size;
  __RAM_END = _estack;
  
  ._user_stack __StackLimit :
  {
    . = ALIGN(8);
    __stack_start__ = .;
    . += _Min_Stack_Size;
    __stack_end__ = .;
  } >DRAM
  
  ASSERT(__StackLimit >= __HeapLimit, "region DRAM overflowed with stack and heap")
  /* ASSERT(__stack_end__ <= 0x00018000, "region code overflowed") */
 
 .dynamic_data1 :
  {
    . = ALIGN(8);
  } >m_dynamic_data1  

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }
}
