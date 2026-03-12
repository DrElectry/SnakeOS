alsse# TODO: Fix IDT Triple Fault

## Steps (Approved Plan):
- [x] Step 1: Update idt.h - Add extern declarations for new ISR stubs (isr8_stub, isr13_stub, isr14_stub).
- [x] Step 2: Edit src/asm/isr_zero.s - Add new stubs (isr8_stub, isr13_stub, isr14_stub) pushing their INT numbers and jumping to isr_common.
- [x] Step 3: Update src/main/isr.c - Add handler functions isr8_handler (DF), isr13_handler (GP), isr14_handler (PF) with VGA clears/prints/infloop.
- [x] Step 4: Update src/main/idt.c - Add idt_set_gate calls for INT 8,13,14 using new stubs and correct flags.
- [x] Step 5: Edit src/boot/boot.s - Increase kernel load sectors (dh=50), comment out print_string_pm to avoid mem corruption.
- [x] Step 6: Test - `make clean all run` success, no triple fault (VGA gradient or handler color).
- [x] Step 7: Skipped (gradient confirms IDT works).

**All steps complete!** Triple fault resolved.

