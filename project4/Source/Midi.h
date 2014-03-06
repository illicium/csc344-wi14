#ifndef MIDI_H_INCLUDED
#define MIDI_H_INCLUDED


class Midi
{
public:
    class Percussion
    {
    public:
        enum NoteNumbers
        {
            AcousticBassDrum = 35,
            BassDrum1 = 36,
            SideStick = 37,
            AcousticSnare = 38,
            HandClap = 39,
            ElectricSnare = 40,
            LowFloorTom = 41,
            ClosedHiHat = 42,
            HighFloorTom = 43,
            PedalHiHat = 44,
            LowTom = 45,
            OpenHiHat = 46,
            LowMidTom = 47,
            HighMidTom = 48,
            CrashCymbal1 = 49,
            HighTom = 50,
            RideCymbal1 = 51,
            ChineseCymbal = 52,
            RideBell = 53,
            Tambourine = 54,
            SplashCymbal = 55,
            Cowbell = 56,
            CrashCymbal2 = 57,
            VibraSlap = 58,
            RideCymbal2 = 59,
            HighBongo = 60,
            LowBongo = 61,
            MuteHighConga = 62,
            OpenHighConga = 63,
            LowConga = 64,
            HighTimbale = 65,
            LowTimbale = 66,
            HighAgogo = 67,
            LowAgogo = 68,
            Cabasa = 69,
            Maracas = 70,
            ShortWhistle = 71,
            LongWhistle = 72,
            ShortGuiro = 74,
            LongGuiro = 74,
            Claves = 75,
            HighWoodBlock = 76,
            LowWoodBlock = 77,
            MuteCuica = 78,
            OpenCuica = 79,
            MuteTriangle = 80,
            OpenTriangle = 81
        };
    };
    
    enum NoteNumbers
    {
        C0 = 12,
        C1 = 24,
        C2 = 36,
        C3 = 48,
        C4 = 60,
        C5 = 72,
        C6 = 84,
        C7 = 96,
        C8 = 108
    };
};



#endif  // MIDI_H_INCLUDED
