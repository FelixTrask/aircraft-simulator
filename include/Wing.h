#ifndef Wing_H
#define Wing_H

class Wing {
public:
    Wing(float wingspan, float wing_area);
    
    float wingspan;
    float wing_area;

    float get_aspect_ratio();
};

#endif