#ifndef idents_CALXTALID_H
#define idents_CALXTALID_H 1


// Include files
#include <iostream>

// #include "GaudiKernel/Kernel.h"
// #include "GaudiKernel/ContainedObject.h"


/*!
//------------------------------------------------------------------------------
//
// ClassName:   CalXtalId        
//  
// Description: ID class for CAL Xtals                                
//		Supports both packed Xtal ID = (tower*8 + layer)*16 + column and
//			unpacked ID, i.e. tower, layer, and column.
//		Serialize methods give i/o for packed ID.
//		Extractor/inserter give i/o for unpacked ID.
//		Input methods ensure that packed and unpacked IDs stay in sync.
//
//    Retrieve packed ID or unpacked tower, layer, and column 
//        inline int getPackedId() const 
//        void getUnpackedId(short& tower, short& layer, short& column); 
// 
//    Retrieve tower, layer, and column numbers individually from packed ID 
//        inline short getTower() const 
//        inline short getLayer() const 
//        inline short getColumn() const 

//              
// Author:  J. Eric Grove	22 Mar 2001                      
//------------------------------------------------------------------------------
 */
namespace idents {
class CalXtalId {


public:

	          /// Xtal ends are labeled by POSitive or NEGative face
          typedef enum
          {
              POS = 0,
                  NEG
          } XtalFace;
    
    
    /// each Xtal end can report four energy ranges
    typedef enum
    {
        LEX8 = 0,
            LEX1,
            HEX8,
            HEX1
    } AdcRange;
    
    /// readout can be either best-of-four energy ranges or all energy ranges
    typedef enum
    {
        BESTRANGE = 0,
            ALLRANGE = 2
    } CalTrigMode;


      CalXtalId(int packedId=0) :
	        m_packedId(packedId) {};

	CalXtalId(short tower, short layer, short column) 
	{
		packId(tower, layer, column);
	};
    
    ~CalXtalId() {};

	void init();

	// get packed ID or unpacked tower, layer, and column
        inline int getPackedId() const {return m_packedId;};
        void getUnpackedId(short& tower, short& layer, short& column);

	// get tower, layer, and column numbers individually from packed ID
        inline short getTower() const {return (m_packedId >> 0x7) & 0xf;};
        inline short getLayer() const {return (m_packedId >> 0x4) & 0x7;};
        inline short getColumn() const {return m_packedId & 0xf;};

        operator int() const {return m_packedId;};

       	friend std::ostream& operator<< (std::ostream &stream, CalXtalId XtalId);
    	friend std::istream& operator>> (std::istream &stream, CalXtalId &XtalId);

		void write( std::ostream& stream) const;
		void read( std::istream& stream);

private:

	// Packed word containing Xtal ID = (tower*8 + layer)*16 + column
        unsigned int m_packedId;

	inline void packId(short tower, short layer, short column) 
		{m_packedId = (((tower<<3) + layer)<<4) + column;};
};

inline std::ostream& operator<<(std::ostream &stream, CalXtalId XtalId) { XtalId.write(stream);return stream;}

inline std::istream& operator>> (std::istream &stream, CalXtalId &XtalId) {XtalId.read(stream);return stream;}


} // namespace idents
#endif    // idents_CALXTALID_H
