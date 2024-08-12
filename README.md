# Ball Balancer

This repo hosts the code for our final project for EE2361 Spring 2024.
As the name implies, this balances a ball on a 1-dimensional strip by
slanting a platform accordingly. The code in the project is written so
it is highly configurable (mainly by editing `config.h`).

The `nbproject` directory holds files managed by the MPLAB X IDE, which
is what we use to program a PIC24 microcontroller with the code.
(We specifically used the PIC24FJ64GA002 model.) Some of the files in
that directory may have been gitignore-able, but we were not sure so we
included them.

### Credits

- Chandan Sankar ([@jahndan](https://github.com/jahndan))
    - PID buffer code
- Jibril Mamo ([@JibrilMamo](https://github.com/JibrilMamo))
    - Servo PWM code
    - Joystick ADC code
- Ayokanmi Bobas ([@kanmiibobas](https://github.com/kanmiibobas))
    - Touchpad SPI code

Hardware setup achieved collaboratively between the three of us.
