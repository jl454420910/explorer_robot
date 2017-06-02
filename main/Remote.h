#ifndef Remote_h 
#define Remote_h

#include "Move.h"
#include "Test.h"

class Remote : public Move, Test
{
    public:
      Remote();
    
      boolean control();

    private:
};

#endif

