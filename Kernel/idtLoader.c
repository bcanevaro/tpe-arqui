#include <stdint.h>
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */



DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

static void setup_IDT_entry (int index, uint64_t offset);

// Funcion que carga la IDT: Interrupt Descriptor Table
void load_idt() {
  // Desactivo todas las interrupciones
  _cli();

  // Cargamos las Interrupt Request
  // Cargamos la Interrupcion del timer
  setup_IDT_entry (0x20, (uint64_t)&_irq00Handler);
  // Cargamos la Interrupcion del teclado
  setup_IDT_entry (0x21, (uint64_t)&_irq01Handler);
  // Syscall interruption
  setup_IDT_entry (0x80, (uint64_t)&_irq80Handler);
  
  // Cargamos las Excepciones
  setup_IDT_entry (0x00, (uint64_t)&_exception0Handler);


  //Solo interrupcion timer tick habilitadas
  picMasterMask(0xFD); 
  picSlaveMask(0xFF);
      
  // Activo todas las interrupciones
  _sti();
}

// Seteamos las entradas de la IDT
// El offset es el puntero a la funcion
static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}
