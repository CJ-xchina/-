struct Sdata {
    unsigned char id;
    // 违背
    struct Sinner1
    {
        unsigned int a;
        unsigned char b;
    };
    // 遵循
    struct Sinner2
    {
        unsigned int a;
        unsigned char b;
    } coor;
    struct Sinner3
    {
        // 遵循
        struct Sinner4 {
            unsigned int a;
            unsigned char b;
        } sInner4;
        // 违背
        struct Sinner5 {
            unsigned int a;
            unsigned char b;
        };
    } coor2;
    // 违背
    struct Sinner6
    {
        unsigned int a;
        unsigned char b;
                // 违背
        struct Sinner9
        {
            unsigned int a;
            unsigned char b;
        };
    };
};


struct Sinner7 {
        // 违背
    struct Sinner8
    {
        unsigned int a;
        unsigned char b;
    };
};