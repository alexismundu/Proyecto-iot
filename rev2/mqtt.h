#ifndef MQTT
#define MQTT 

class mqtt {
    private:
        static bool setup_mqtt(void);
    
    public:
        static bool init(void);
        static bool reconnect_mqtt(void);
        static void publish(const char *msg, const char* topic);
        static void publishPeriodically(const char *msg, const char* topic, long period);
        static void loop(void);

       };
#endif
