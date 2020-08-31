#pragma once

#include <WString.h>

#define ConfigReg1 0x00
#define ConfigReg2 0x01
#define Polarity 0x02
#define TimerConfig 0x03
#define Seconds 0x06
#define Minutes 0x07
#define Hours 0x08
#define Day 0x09
#define Date 0x0A
#define Month 0x0B
#define Year 0x0C

class MAX31341
{
    public:
        MAX31341(bool AD0);

        String GetSeconds();
        void SetSeconds(int sec);

        String GetMinutes();
        void SetMinutes(int min);

        String GetHours();
        void SetHours(int H);

        String GetDay();
        void SetDay(int D);

        String GetMonth();
        void SetMonth(int D);
};