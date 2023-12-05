# nema17-planetary

A 2-stage, 28:1 Planetary Gearbox made for the NEMA 17 standard.
Uses mainly 3D-printed parts as well as some additional hardware to make a simple and inexpensive gearbox.

## Mechanical Overview


#### Motor Selection
For the motor to be compatible, it should have similar dimensions to this base diagram:

#### Features and internal gearing

- Decent backlash/repeatability

- All gears are helical with a helix angle of 20°

Stage 1 
7:1 Ratio 

- Planet Teeth - 30
- Sun Teeth - 12
- Ring Teeth - 72


Small teeth at higher speed -> reduce backlash inherent in multistage planetary gearings.

Stage 2
4:1 Ratio
- Planet Teeth - 12
- Sun Teeth - 12
- Ring Teeth - 36


Larger teeth at a lower speed -> higher mechanical strength, increase in max torque without damage bottleneck.



## 3D printing and settings
- All parts are confirmed to be 3D-printable in PLA with a 0.4mm nozzle

- Depending on the size and stall torque of your motor, parts such as the carriers and gears should ideally be printed at a high infill (50%-100%)
  - This version was tested with a smaller motor of length 42mm and achieved around 4Nm output torque (where skipped steps ocurr)

- For ideal performance and smooth operation, use a minimal layer height (0.1mm - 0.2mm) for all components which contain gears)

- Support required on carrier components which transmit rotation to next stage or output


## Additional Components
19x m3 Bolts of various sizes:
- 4x m3 x 10
- 10x m3 x 12
- 5x m3 x 20

5x heat-set inserts for M3 bolts on output hub, must fit rough size of 4.3mm diameter by 6.5mm depth


Grease
- Ideally, use lithium grease on all gears and shafts

## Notes/Future Plans
Additions coming soon:
Motor-mounted driver/encoder combo for active feedback


