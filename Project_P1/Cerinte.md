# Cerinte -- Project_P1

## CR-01: Adaugare mesaje CAN noi cu transmisie ciclica independenta

### Descriere generala

Se cere extinderea simulatorului CAN existent cu doua mesaje noi, fiecare avand ciclicitate proprie de transmisie, independenta de mesajele deja existente. Noile mesaje introduc suport pentru CAN FD (Flexible Data-rate) si necesita generare dinamica de date la runtime.

---

### CR-01.1: Mesaj CAN Classic -- ID 0x40

| Proprietate       | Valoare                          |
|--------------------|----------------------------------|
| CAN ID             | `0x40`                           |
| Tip frame          | CAN Classic (Standard ID, 11-bit)|
| DLC                | 16                               |
| Ciclicitate        | 40 ms                            |

**Observatie:** Un DLC de 16 depaseste limita CAN Classic (max 8 bytes). Aceasta implica necesitatea utilizarii **CAN FD** (DLC 16 corespunde unui payload de 16 bytes in CAN FD). Structura `CANFrame` existenta trebuie adaptata sau extinsa pentru a suporta payload-uri mai mari de 8 bytes.

---

### CR-01.2: Mesaj CAN FD -- ID 0x12DD5528

| Proprietate       | Valoare                                  |
|--------------------|------------------------------------------|
| CAN ID             | `0x12DD5528`                             |
| Tip frame          | CAN FD (Extended ID, 29-bit)             |
| DLC                | 64                                       |
| Ciclicitate        | 80 ms                                    |

**Observatie:** ID-ul `0x12DD5528` este un identificator extins pe 29 de biti. Campul `id` din structura `CANFrame` (actualmente `uint8`) trebuie extins la `uint32` pentru a putea reprezenta ID-uri extinse. DLC 64 corespunde payload-ului maxim CAN FD.

---

### CR-01.3: Generare aleatorie a datelor incepand cu byte-ul 3

**Se aplica ambelor mesaje noi (0x40 si 0x12DD5528).**

- Incepand cu **byte-ul 3** (indexare de la 0, adica `data[3]`), toate datele pana la sfarsitul payload-ului trebuie **generate aleatoriu** la fiecare transmitere.
- Byte-ii `data[0]` si `data[1]` raman cu valorile initiale (statice).
- Byte-ul `data[2]` are comportament special (vezi CR-01.4).
- Generarea aleatorie trebuie sa produca valori in intervalul `0x00` -- `0xFF` pentru fiecare byte.
- Seed-ul generatorului random trebuie initializat la pornirea programului (ex. `srand(time(NULL))`).

**Exemplu** pentru mesajul cu DLC 16 (la doua transmisii consecutive):
```
Tx #1: Data=[ XX XX XX 3A 7F B2 01 C8 9D 44 E1 5B 0C 73 A6 2E ]
Tx #2: Data=[ XX XX XX 91 D4 08 6C FF 23 B7 50 E9 1A 8F C3 47 ]
                       ^--- data[3]: de aici incep datele random
```

---

### CR-01.4: Contor ciclic in nibble-ul inferior al byte-ului 2

**Se aplica ambelor mesaje noi (0x40 si 0x12DD5528).**

- **Nibble-ul inferior** (bitii 3..0, "jumatatea din dreapta") al byte-ului `data[2]` trebuie **incrementat cu 1** la fiecare transmitere a mesajului respectiv.
- Contorul cicleaza in intervalul `0x1` -- `0xF` (dupa `0xF` revine la `0x1`).
- **Nibble-ul superior** (bitii 7..4) al byte-ului `data[2]` ramane nemodificat (zero sau valoarea initiala).
- Fiecare mesaj isi mentine propriul contor, independent de celalalt.

**Secventa de valori pentru `data[2]`** (presupunand nibble-ul superior = 0):
```
0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x02, ...
```

---

### Rezumat impactului asupra codului existent

1. **`CANFrame` (Fcontrol.h)**
   - Campul `id` trebuie extins de la `uint8` la `uint32` pentru a suporta Extended ID pe 29 de biti.
   - Campul `data[]` si constanta `CAN_CLS_SIZE` trebuie adaptate pentru a suporta payload pana la 64 bytes (CAN FD).
   - Campul `dlc` trebuie sa suporte valori pana la 64.

2. **Mesaje noi (MessagesGen.c / Messages.h)**
   - Definirea a doua mesaje noi cu datele initiale corespunzatoare.
   - Actualizarea `MESSAGES_COUNT` si a array-ului `CAN_MESSAGES[]`.

3. **Logica de transmisie (Fcontrol.c)**
   - Implementarea ciclicitatii independente per mesaj (40ms, 80ms) in locul pauzei fixe de 150ms.
   - Generarea aleatorie a byte-ilor `data[3]` -- `data[DLC-1]` inainte de fiecare transmitere.
   - Incrementarea contorului ciclic (`0x1`--`0xF`) in nibble-ul inferior al `data[2]`.

4. **`send_can_frame()` (Fcontrol.c)**
   - Adaptarea afisarii pentru a printa ID-uri pe 32 de biti si payload-uri de lungime variabila (nu doar 8 bytes).

5. **`main.c`**
   - Initializarea generatorului de numere aleatoare (`srand`).
   - Posibila reorganizare a buclei principale pentru a gestiona ciclicitati diferite per mesaj.
