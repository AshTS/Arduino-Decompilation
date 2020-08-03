# Arduino-Decompilation

The results of a project to decompile the assembly gathered from `avr-objdump`.

## Procedure:

1. Compile the text.ino project with the Arduino IDE
2. Use `avr-objdump` to disassemble the `code.hex`* file (`avr-objdump code.hex -D -m avr5 > asm.txt`)
3. Go through the assembly code and find usable patterns
4. Convert the generated notes to C code
5. Clean up C code and transfer notes

\* `code.hex` is the version of the binary output which includes the bootloader, however that output has been removed from the `asm.txt` file because the main source contained enough interesting parts.
