#ifndef IR_COMMANDS_DEFINATION_H
#define IR_COMMANDS_DEFINATION_H

#define ON 0
#define OFF 1
#define MUTE 2
#define CABLE / SAT 3
#define STB 4
#define TV 5
#define DISC 6
#define MHL 7
#define AUX 8
#define AUDIO 9
#define GAME 10
#define AVR 11
#define USB 12
#define NETWORK 13
#define RADIO 14
#define SURR_MODE 15
#define OSD / MENU 16
#define UP 17
#define LEFT 18
#define OK 19
#define RIGHT 20
#define DOWN 21
#define BACK / EXIT 22
#define HOME 23
#define _1 24
#define _2 25
#define _3 26
#define _4 27
#define _5 28
#define _6 29
#define _7 30
#define _8 31
#define CLEAR 32
#define _9 33
#define _0 34
#define TEST 35
#define VOL_UP 36
#define VOL_DOWN 37
#define DELAY 38
#define SLEEP 39
#define CH / TUNER_UP 40
#define CH / TUNER_DOWN 41
#define INFO 42
#define DIM 43
#define P -SCAN 44
#define DIRECT 45
#define MEM 46
#define RDS 47
#define _ | < 48
#define _ << 49
#define _ >> 50
#define _ > | 51
#define STOP 52
#define PLAY 53
#define PAUSE 54
#define PREV .CH 55

struct Command
{
   String name;
   int address;
   int command;
};

// keys
Command keyOn = {"On", 0x7080, 0xC0};
Command keyOff = {"Off", 0x7080, 0x9F};
Command keyVolUp = {"Vol_UP", 0x7080, 0xC7};
Command keyVolDown = {"Vol_DOWN", 0x7080, 0xC8};
Command keyMute = {"Mute", 0x7080, 0xC1};
Command keyCableSat = {"Cable/Sat", 0x7080, 0xB0};
Command keySTB = {"STB", 0x7080, 0xD3};
Command keyTV = {"TV", 0x7080, 0xB1};
Command keyDisc = {"Disc", 0x7080, 0xD0};
Command keyMHL = {"MHL", 0x7080, 0xEF};
Command keyAux = {"Aux", 0x7080, 0xCD};
Command keyAudio = {"Audio", 0x7080, 0xB4};
Command keyGame = {"Game", 0x7080, 0xB2};

struct Command avr161_commands_set[] = {keyOn, keyOff, keyVolUp, keyVolDown};

#endif
