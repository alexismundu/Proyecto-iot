#ifndef SENSORCONTROL
#define SENSORCONTROL

class sensorControl {
    public:
        static bool init(void);
        static int getMoisture(void);
        static int getLight(void);
        static int getMoistureAvg(void);
        static int getLightAvg(void);
};
#endif
