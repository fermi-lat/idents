// $Header: /nfs/slac/g/glast/ground/cvs/idents/src/test/test_idents.cxx,v 1.1 2002/04/26 08:50:03 frailis Exp $


#include "idents/VolumeIdentifier.h"
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

int main() 
{
  idents::VolumeIdentifier id1, id2, id3;
  id1.append(1); id1.append(1);
  id2.append(1); id2.append(1); id2.append(0);id2.append(0);
  id3.append(1);id3.append(1);id3.append(0);

  std::vector< idents::VolumeIdentifier > idVect;
  idVect.push_back(id1);
  idVect.push_back(id3);
  idVect.push_back(id2);

  std::sort(idVect.begin(), idVect.end());
  
  std::vector< idents::VolumeIdentifier >::iterator i;
  std::cout << "Sorted vector of volume identifiers: "<< std::endl;
  for (i=idVect.begin(); i != idVect.end(); i++)
    {
    std::cout << i->name() << std::endl;
    }
  std::cout << std::endl;

  std::map<idents::VolumeIdentifier,double> idMap;
  idMap[id1] = 1.5;
  idMap[id2] = 2.5;
  idMap[id3] = 3.5;

  std::map<idents::VolumeIdentifier,double>::iterator m;
  std::cout << "Map elements: " << std::endl;
  for (m = idMap.begin(); m != idMap.end();m++)
    {
      std::cout << "Id = " << (*m).first.name();
      std::cout << "   Value = " << (*m).second << std::endl;
    }
  
  return 0;
}
