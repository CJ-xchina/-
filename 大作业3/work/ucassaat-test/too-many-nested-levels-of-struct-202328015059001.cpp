struct A {
    int num1;
    struct B {
        int num2;
        struct C {
            int num3;
            // struct D 违背规则
            struct D {
                int num4;
                // E 背规则
                struct E {
                    int num5;
                } e;
                // F 背规则
                struct F
                {
                    int num6;
                    // H 背规则
                    struct H
                    {
                        int num8;
                    };
                    
                };
                
            } d;
            // G 背规则
            struct G{
                int num7;
            };
        } c;
    } b;
};