#ifndef XTALID_H
#define XTALID_H 1

#include "idents/ModuleId.h"

namespace idents {

/**
*  Crystal identifier
*
*  @version $Id: XtalId.h,v 1.2 2000/08/17 15:13:33 burnett Exp $
*/

class XtalId 
{
public:
    //! construct from given tower, layer, crystal
    XtalId (ModuleId m, unsigned int l, unsigned int xtal)
        : m_layer(l), m_xtal(xtal), m_id(m) 
    {}
    
    //! construct from an unsigned in, presumably a crystal id
    XtalId (unsigned int id = 0)
        : m_layer( id%1000/100 ), m_xtal(id%100), m_id(id/1000)
    {}
    
    //! integer representation used for comparison, etc.
    operator unsigned int () const
    {  return m_id*1000+m_layer*100+m_xtal;
    }
    
private:
    unsigned int m_layer;
    unsigned int m_xtal;
    ModuleId m_id;
};

}

#endif
