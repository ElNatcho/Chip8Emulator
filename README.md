# Chip8Emulator

Ein einfacher Emulater der Chip8-Programme ausführen kann. Zurzeit können nur Programme ausgeführt werden, welche mit dem Chip8Compiler
compiliert wurden!

Man kann eine ROM mithilfe von Kommandozeilenparametern starten:  
  Chip8.exe <ROM>
  
# Chip8Compiler

Ein einfacher Compiler der Source-Code zu einer ROM compiliert. Der Source-Code muss aus dem speziellen Instruktionsset des Compilers
bestehen.

Eine ROM kann mithilfe von Kommandozeilenparametern erstellt werden:  
  Chip8Compiler <SRC_FILE> <ROM_NAME>
  
# HexConv

Ein Hilfsprogramm, dass Strings(Hexzahlen) zu einem Int32 konvertiert und in eine Datei schreibt.
