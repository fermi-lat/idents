// File and Version information
// $Header: /nfs/slac/g/glast/ground/cvs/idents/src/AcdId.cxx,v 1.1 2004/10/21 18:20:45 heather Exp $
//
// ClassName:   AcdId
//  
// Description: ID class for ACD components
//
//              
// Author:  H. Kelly     20 Oct 2004

// Include files
#include "idents/AcdId.h"
#include <stdexcept>
#include <iostream>
#include <ios>

using namespace idents; 

/** Constructor from VolumeIdentifier.  Assuming a particular form for
    fields within VolumeIdentifier (correct as of Oct 20, 2004):
*/
AcdId::AcdId(const VolumeIdentifier& vId) : m_id(0) {
  constructorGuts(vId);
}

void AcdId::constructorGuts(const VolumeIdentifier& volId)   {

    na(0);
    if (!checkVolId(volId)) throw std::invalid_argument("VolumeIdentifier");

    if (volId[2] == tileVolId) {
        face(volId[1]);
        /* as of revised ACD geometry (nov ?? 2002) row and column
        are always in the right order, but there is an intervening
        field which has to be thrown away. For now it should always
        have value 40 (tile).  When ribbons are sensitive, will also see
        41 if volume refers to a ribbon.  */
        row(volId[3]);
        column(volId[4]);
    } else if (volId[2] == ribbonVolId) {
        ribbonNum(volId[4]);
        ribbonOrientation(6-volId[3]);
    }


}





