#ifndef TETRAEDRE_HPP
#define TETRAEDRE_HPP

#include "objetGeometrique.hpp"

class Tetraedre : public objetGeometrique {
private:
    float cote;
    float* colors;

public:
    Tetraedre(float =0.5);
    ~Tetraedre();
    virtual void CreateVertexBuffer();
    void CreateColorBuffer();
    inline float* returnColors() const { return colors; }

};

#endif
