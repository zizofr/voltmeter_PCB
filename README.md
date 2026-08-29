# ⚡ Digital Voltmeter (Custom PCB & Hardware Design)

A compact digital voltmeter designed around a custom Printed Circuit Board (PCB) created in KiCad. This repository contains the complete hardware design files, schematics, Gerber manufacturing outputs, and board renders prior to final firmware integration.

---

## 🖼️ Hardware & PCB Gallery

### Board Renders & Views
| Top View | Bottom View |
| :---: | :---: |
| ![Top View](images/top.png) | ![Bottom View](images/bottom.png) |

| Perspective View 1 | Perspective View 2 |
| :---: | :---: |
| ![Perspective View 1](images/view_1.png) | ![Perspective View 2](images/view_2.png) |

---

## 🛠️ Project Specifications & Features

- **EDA Tool:** KiCad
- **Board Architecture:** Custom 2-layer PCB
- **Hardware Features:**
  - Dedicated analog front-end voltage divider circuit for signal attenuation.
  - Onboard microcontroller interface for ADC sampling and processing.
  - Display interface output.
  - Optimized trace routing with solid ground plane shielding.
- **Manufacturing Package:** Full Gerber layer generation (F_Cu, B_Cu, Solder Masks, Silkscreens, and Drill files).

---

## 📂 Repository Structure

```text
├── gerber/              # Production Gerber and drill files (.gbr, .drl)
├── view_1.png              # High-resolution 3D renders (top, bottom, view_1, view_2)
├──view_2.png
├──top.png
├──bottom.png
├── voltmeter.kicad_pcb  # KiCad PCB board layout source file
├── voltmeter.kicad_sch  # KiCad schematic design source file
└── README.md            # Project documentation
