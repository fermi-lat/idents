#ifndef _H_Acd_Id
#define _H_Acd_Id

#include "facilities/bitmanip.h"
#include "idents/VolumeIdentifier.h"
#include <iostream>
#include <string>

/** @class AcdId 
@brief Encapsulate the id for an ACD tile, ribbon or not-attached electronics

@verbatim
 ACD tile numbering
 Layer 0 or 1, where 0 corresponds to the inner layer
 N/A 0 or 1, where 0 is a connected detector and 1 is N/A
 Face 0 - 4 
          Face 0 == top  (hat)
          Face 1 == -X side 
          Face 2 == -Y side
          Face 3 == +X side
          Face 4 == +Y side
          Face 5, 6 == ribbon

 Row 0 - 9
          On Face 0 (top) rows are numbering along +x axis
          On the sides, the rows are numbered from the front of the instrument (closest to the top)
          If this is a ribbon, then row is zero.

 Column 0 - 9
          On Face 0 (top), columns are numbered along the +y axis
          On the sides, columns are numbered along +x (or +y) axis
          If this is a ribbon, then column is the number of the ribbon along increasing X or Y.

 One could imagine that an ACD id could be represented by 12 bits.
 
  __ __       __ __ __     __ __ __ __      __ __ __ __
  N/A           FACE           ROW            COLUMN
                 OR                             OR
           RIBBON ORIENTATION               RIBBON NUMBER
 where N/A is the most significant bit
 This is the internal represenation of the AcdId in this class.
 @endverbatim

  @author Heather Kelly based on initial version by Sawyer Gillespie
  $Header: /nfs/slac/g/glast/ground/cvs/idents/idents/AcdId.h,v 1.16 2007/08/24 04:30:31 heather Exp $
*/

namespace idents {
class   AcdId {
public:
    AcdId ();
    AcdId ( const AcdId& );
    AcdId ( const idents::VolumeIdentifier &volId );
    AcdId ( unsigned int id ) : m_id (id) { }
    AcdId (short l, short f, short r, short c);
    AcdId (short ribOrient, short ribbonNum);

    /** 
        AcdId's may be represented by a 4 (or fewer) digit base 10 number
        where the digits have the following meanings:
        1000's place:  0 for tiles and ribbons; 1 for N/A 
         100's place:  0-4 for tiles (face); 5 or 6 for ribbons (orientation);
                       not used for N/A (0)
          10's place:  0-4 for tiles (row); not used for ribbons; 0 or 1
                       for N/A 
           1's place:  0-4 for tiles (col); 0-3 for ribbons (ribbon 3);
                       0-9 for N/A
  
          N/A use the 10's and 1's place together to represent N/A channel,
          which ranges from 0 to 10.
    */
    AcdId (const std::string& base10);

    virtual ~AcdId ();

    /// Allows user to check a volumeId to see if it is a valid tile or ribbon
    /// before attempting to convert it to an AcdId
    static bool checkVolId(const idents::VolumeIdentifier &volId);

    /// access the internal representation of the AcdId
    operator const unsigned int& () const { return m_id; }

    void write (std::ostream& out) const
    {
        out << m_id;
    }

    void read (std::istream& in)
    {
        in >> m_id;
    }

    /// access the id in matrix format LayerFaceRowColumn
    inline unsigned int id () const;
    /// construct a VolumeIdentifier using the AcdId
    inline const idents::VolumeIdentifier volId(bool bent=false);
    /// is this a tile?
    inline bool tile() const;
    /// is this a ribbon?
    inline bool ribbon() const;
    /// is this a top tile?
    inline bool    top () const;  
    /// is this a side tile?
    inline bool    side () const;   
    /// which layer is this tile in (1st(0 - closer to center of GLAST) or 2nd (1))
    inline short   layer () const;     
    /// replacing layer, to denote PMTs that are N/A
    inline short   na () const;     
    /// which face number? 
    inline short   face() const;
    /// which row number?  returns -1 if this id is a ribbon and not a tile
    inline short   row() const;     
    /// which column? returns -1 if this id is a ribbon and not a tile
    inline short   column () const;  
    /// Number of the ribbon starting from 0 and increasing along increasing X or Y
    inline short ribbonNum() const;
    /// Does this ribbon extend along the X or Y axis?
    inline short ribbonOrientation() const;

    /// returns face or ribbon orientation (value = 5 or 6 for the latter)
    inline short faceLike() const;

    /// returns row for tiles, 0 for ribbons
    inline short rowLike() const; 

    /// returns col for tiles, ribbon # for ribbons
    inline short colLike() const; 

    /// Allow client to set the na bit
    inline void na( unsigned int val );

    static void convertToTilePmt(unsigned int  cable, unsigned int  channel, unsigned int& tile, unsigned int& pmt);
    static void convertToGarcGafe(unsigned int tile, unsigned int pmt, unsigned int& garc, unsigned int& gafe);
    static unsigned int           tileFromGemIndex(unsigned int gemIndex);
    static unsigned int           gemIndexFromTile(unsigned int tile);
    static unsigned int           tileFromIndex(unsigned int gemIndex);
    static unsigned int           indexFromTile(unsigned int tile);


private:
    void constructorGuts(const idents::VolumeIdentifier &volid);
    /// set layer
    inline void layer( unsigned int val );
    /// set the face number
    inline void face (unsigned int f);
    /// set the row
    inline void row( unsigned int r );
    /// set the column
    inline void column( unsigned int c );
    /// set the ribbon number
    inline void ribbonNum( unsigned int r);
    /// set the ribbon orientation
    inline void ribbonOrientation( unsigned int r);
    
    enum {
        _layermask = 0x1800,
        _namask = 0x1800,
        _facemask  = 0x0700,
        _rowmask   = 0x00F0,
        _colmask   = 0x000F,
        _ribbonmask = 0x0007,
        _ribbonorientmask = 0x0700,
        layerShift = 11,
        colShift = 0,
        rowShift = 4,
        faceShift = 8,
        naShift = 11,
        maxAcdTileFace = 4,
        tileVolId = 40,
        ribbonVolId = 41,
        ribbonX = 5,  // ribbons that extend along x-axis
        ribbonY = 6   // ribbons that extend along y-axis
    };

    /// internal representation of the id, 4 byte word
    unsigned int    m_id;

};

// inline declarations

inline AcdId::AcdId () : m_id (0) {}
inline AcdId::AcdId ( const AcdId& r ) : m_id (r.m_id) {}
inline AcdId::AcdId (short l, short f, short r, short c)  {
    m_id = 0;
    na(l);
    face(f);
    row(r);
    column(c);
}
inline AcdId::AcdId(short ribbonOrient, short r) {
    m_id = 0;
    ribbonNum(r);
    ribbonOrientation(ribbonOrient);
}
inline AcdId::~AcdId () {}


inline bool AcdId::checkVolId(const idents::VolumeIdentifier &volId) {
    if (volId[0] != 1) return false;
    if ((volId[2] != tileVolId) && (volId[2] != ribbonVolId)) return false;
    return true;
}

inline unsigned int AcdId::id() const 
{ 
    if (tile()) 
        return (na() * 1000 + face() * 100 + row() * 10 + column()); 
    return (na() * 1000 + ribbonOrientation() * 100 + ribbonNum());
}

inline const idents::VolumeIdentifier AcdId::volId(bool bent) {

    idents::VolumeIdentifier vId;
    vId.append(1); 
    if (na()) return vId;
    vId.append(face()); 
    if (tile()) {
        vId.append(tileVolId);
        vId.append(row());
        vId.append(column()); 
        if (bent) // signifies the bent portion of the detector
            vId.append(1);
        else
            vId.append(0);
    } else {
        vId.append(ribbonVolId);
        vId.append(6-ribbonOrientation());
        vId.append(ribbonNum());
    }

    return vId;
}

inline bool AcdId::tile () const
{ return ((!na()) && (face() <= maxAcdTileFace)); }

inline bool AcdId::ribbon () const
{ return ((!na()) && (face() > maxAcdTileFace)); }

inline bool AcdId::top () const 
{ return ((!na()) && (face() == 0)); }

inline bool AcdId::side () const 
{ return ((!na()) && (!ribbon()) && (face() != 0)); }

inline short AcdId::layer () const 
{ return (na()); }

inline short AcdId::na () const 
{ return (m_id & _namask) >> naShift; }

inline short AcdId::face () const
{ 
    return bitmanip::word(2, (m_id & _facemask)); 
}

inline short AcdId::row () const 
{ 
    if (tile()) return bitmanip::word (1, m_id); 
    return -1;
}

inline short AcdId::ribbonNum () const
{ 
    if (ribbon()) return bitmanip::word(0, (m_id & _ribbonmask)); 
    return -1;
}

inline short AcdId::ribbonOrientation () const
{
    if (ribbon()) return bitmanip::word(2, (m_id & _ribbonorientmask));
    return -1;
}

inline short AcdId::column () const 
{ 
    if (tile()) return bitmanip::word (0, m_id); 
    return -1;
}

inline short AcdId::faceLike() const 
{
  if (!na()) return ((m_id & _facemask) >> faceShift);
  return -1;
}

inline short AcdId::rowLike() const
{
  if (!na()) return ((m_id & _rowmask) >> rowShift);
  return -1;
}

// This one makes sense even for N/A
inline short AcdId::colLike() const
{
  return ((m_id & _colmask) >> colShift);
}

// set routines

inline void AcdId::layer( unsigned int val)
{ 
    na(val);
}

inline void AcdId::na( unsigned int val)
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
        f | ((_namask & m_id ) >> 8) );
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

inline void AcdId::ribbonNum( unsigned int r )
{
    bitmanip::set_word<unsigned int>( 0, m_id, r );
}

inline void AcdId::ribbonOrientation( unsigned int orient) 
{
    bitmanip::set_word<unsigned int>( 2, m_id, orient);
}

inline std::ostream& operator<<(std::ostream& out,const AcdId& id){id.write(out); return out;}
inline std::istream& operator>>(std::istream&  in, AcdId& id){id.read(in); return in;}
} // namespace idents

#endif // _H_Acd_Id
