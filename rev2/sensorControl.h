#ifndef SENSORCONTROL
#define SENSORCONTROL

class sensorControl {
    private:
        static int getMoisture(void);
        static int getLight(void);
    
    public:
        static bool init(void);
        static int getMoistureAvg(void);
        static int getLightAvg(void);
        static float getTemp(void);
};
#endif
