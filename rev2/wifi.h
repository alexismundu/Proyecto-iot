#ifndef WIFI
#define WIFI 

class wifi {
    private:
        static bool setup_wifi(void);
    
    public:
        static bool init(void);
        static bool reconnect_wifi(void);
       };
#endif
