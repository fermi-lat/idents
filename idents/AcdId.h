//
// Interface for the AcdId class.

#ifndef _H_Acd_Id
#define _H_Acd_Id

#include "facilities/bitmanip.h"
#include "idents/ModuleId.h"
/*!
\class AcdId 
\brief encapsulate the id for an ACD tile.

 ACD tile numbering
 Layer 0 or 1, where 0 corresponds to the inner layer
 Face 0 - 4 
          Face 0 == top  (hat)
          Face 1 == -X side 
          Face 2 == -Y side
          Face 3 == +X side
          Face 4 == +Y side
 Row 0 - 9
          On Face 0 (top) rows are numbering along +x (or +y) axis
          On the sides, the rows are numbered from the front of the instrument (closest to the top)

 Column 0 - 9
          On the sides, columns are numbered along +x (or +y) axis

 One could imagine that an ACD id could be represented by 12 bits.
 
  __ __       __ __ __     __ __ __ __      __ __ __ __
  LAYER         FACE           ROW            COLUMN
 where the layer is the most significant bit
*/

namespace idents {
class   AcdId {
public:
    AcdId ();
    AcdId ( const AcdId& );
    AcdId ( unsigned int id ) : m_id (id) { }
    AcdId (short l, short f, short r, short c);
    virtual ~AcdId ();

    // access
    operator const unsigned int& () const { return m_id; }

    void write (std::ostream& out) const
    {
        out << m_id;
    }

    void read (std::istream& in)
    {
        in >> m_id;
    }

    // all tile access methods
    /// access the id in matrix format LayerFaceRowColumn
    inline unsigned int id () const;
    /// is this a top tile?
    inline bool    top () const;  
    /// is this a side tile?
    inline bool    side () const;   
    /// which layer is this tile in (1st(0 - closer to center of GLAST) or 2nd (1))
    inline short   layer () const;     
    /// which face number?
    inline short   face() const;
    /// which row number?
    inline short   row() const;     
    /// which column?
    inline short   column () const;   

private:
    /// set layer
    inline void layer( unsigned int val );
    /// set the face number
    inline void face (unsigned int f);
    /// set the row
    inline void row( unsigned int r );
    /// set the column
    inline void column( unsigned int c );
    
    enum {
        _layermask = 0x1800,
        _facemask  = 0x0700,
        _rowmask   = 0x00F0,
        _colmask   = 0x000F,
        layerShift = 11
    };

    unsigned int    m_id;   // id value (4 byte word)

};

// inline declarations

inline AcdId::AcdId () : m_id (0) {}
inline AcdId::AcdId ( const AcdId& r ) : m_id (r.m_id) {}
inline AcdId::AcdId (short l, short f, short r, short c)  {
    m_id = 0;
    layer(l);
    face(f);
    row(r);
    column(c);
}
inline AcdId::~AcdId () {}

inline unsigned int AcdId::id() const 
{ return (layer() * 1000 + face() * 100 + row() * 10 + column()); }

inline bool AcdId::top () const 
{ return (face() == 0); }

inline bool AcdId::side () const 
{ return (face() != 0); }

inline short AcdId::layer () const 
{ return (m_id & _layermask) >> layerShift; }

inline short AcdId::face () const
{ return bitmanip::word(2, (m_id & _facemask)); }

inline short AcdId::row () const 
{ return bitmanip::word (1, m_id); }

inline short AcdId::column () const 
{ return bitmanip::word (0, m_id); }

inline void AcdId::layer( unsigned int val)
{ 
  short two = 2;

  bitmanip::set_word<unsigned int>( 
      two, m_id, 
      ((val == 0) ? 0 : 8) | ((_facemask & m_id) >> 8) );
}

inline void AcdId::face( unsigned int f )
{
    short two = 2;
    bitmanip::set_word<unsigned int> (
        two, m_id, 
        f | ((_layermask & m_id ) >> 8) );
}

inline void AcdId::row( unsigned int r ) 
{ 
  short one = 1;
  bitmanip::set_word<unsigned int>( one, m_id, r );
}

inline void AcdId::column( unsigned int c ) 
{ 
  short zero = 0;
  bitmanip::set_word<unsigned int>( zero, m_id, c ); 
}


inline std::ostream& operator<<(std::ostream& out,const AcdId& id){id.write(out); return out;}
inline std::istream& operator>>(std::istream&  in, AcdId& id){id.read(in); return in;}
} // namespace idents

#endif // _H_Acd_Id
