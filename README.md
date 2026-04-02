# Embedded_C_2026

## Project_P1 -- CAN Message Transmission Simulator

Simulator scris in C care reproduce comportamentul unui transmitter CAN (Controller Area Network), afisand continut-ul frame-urilor CAN in consola. Proiectul urmeaza conventiile din domeniul automotive/embedded (tipuri de date fixe, bucla infinita in `main`, structuri CAN clasice).

### Structura proiectului

```
Project_P1/
  C/
    Start_ide.bat                  -- Script pentru deschiderea VS Code
    .vscode/                       -- Configurari VS Code (build, IntelliSense)
    sw/
      main.c                       -- Punct de intrare in aplicatie
      DataTypes/inc/Types.h        -- Tipuri de date cu dimensiune fixa (uint8, uint16, etc.)
      FlowControl/
        inc/
          Fcontrol.h               -- Definitia structurii CANFrame + declaratii functii
          Messages.h               -- Definitii mesaje CAN, initializare
        src/
          Fcontrol.c               -- Logica de transmisie (afisare frame CAN)
          MessagesGen.c            -- Datele mesajelor CAN (LDA_FC1, LDA_FC2)
```

### Module

**DataTypes (`Types.h`)**
Defineste aliasuri pentru tipuri intregi cu dimensiune fixa, dupa modelul AUTOSAR:
`uint8`, `uint16`, `uint32`, `uint64`, `bool`.

**FlowControl**
Modulul principal, responsabil de definirea si transmisia mesajelor CAN:

- **`CANFrame`** -- structura care contine: `id` (identificator CAN), `data[8]` (payload de 8 octeti), `dlc` (Data Length Code).
- **`LDA_FC1`** -- mesaj CAN cu ID `0x12`, date: `{0x00, 0x00, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}`.
- **`LDA_FC2`** -- mesaj CAN cu ID `0xAB`, date: `{0x00, 0x00, 0xFF, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE}`.
- **`send_can_frame()`** -- afiseaza un frame CAN in format: `Tx: ID=0x12 DLC = 8 Data=[ 00 00 03 04 ... ]`.
- **`sendMessages()`** -- itereaza prin toate mesajele CAN si le transmite cu o pauza de 150ms intre ele (`Sleep(150)`).
- **`initializeMessages()`** -- copiaza mesajele definite (`LDA_FC1`, `LDA_FC2`) in array-ul global `CAN_MESSAGES[]`.

### Flux de executie

```
main()
  |-> initializeMessages()        -- Populeaza CAN_MESSAGES[] cu LDA_FC1 si LDA_FC2
  |-> printf("Sending messages:")
  |-> Bucla infinita:
        |-> sendMessages()
              |-> Pentru fiecare mesaj din CAN_MESSAGES[]:
                    |-> send_can_frame()   -- Afiseaza frame-ul in consola
                    |-> Sleep(150)         -- Pauza 150ms
```

Programul ruleaza continuu (bucla infinita), simuland un nod CAN care transmite periodic doua mesaje.

### Build

Proiectul se compileaza cu GCC (MSYS2/UCRT64) prin VS Code:
- Deschide proiectul: `Project_P1\C\Start_ide.bat`
- Build: `Ctrl+Shift+B`

Comanda de compilare configurata in `tasks.json`:
```
gcc main.c FlowControl/src/Fcontrol.c FlowControl/src/MessagesGen.c -I DataTypes/inc -I FlowControl/inc -o main.exe
```