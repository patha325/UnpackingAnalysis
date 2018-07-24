/* This file is part of BabyMINDdaq software package. This software
 * package is designed for internal use for the Baby MIND detector
 * collaboration and is tailored for this use primarily.
 *
 * BabyMINDdaq is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BabyMINDdaq is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BabyMINDdaq.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MDFRAGMENT_BM_H
#define __MDFRAGMENT_BM_H

#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iostream>

#include "MDdataContainer.h"
#include "MDpartEventBM.h"

class MDfragmentBM : public MDdataContainer {

 public:

  MDfragmentBM( void *d = 0 ) : MDdataContainer(d) {}
  virtual ~MDfragmentBM() { this->Clean(); }

  void SetDataPtr( void *d, uint32_t aSize=0 );
  void Dump();
  void Init();
  void Clean();

  unsigned int GetBoardId()             {return _boardId;}
  unsigned int GetSpillTag()            {return _spillTag;}
  unsigned int GetHumidity()            {return _humidity;}
  unsigned int GetTemperature()         {return _temperature;}
  unsigned int GetSpillTime()           {return _spillTime;}
  
  unsigned int GetSpillDAQType()        {return _spillDAQType;}
  unsigned int GetSpillTimeGTrig()      {return _spillTimeGTrig;}
  
  unsigned int GetSpillTrailTad()       {return _spillTrailTag;}
  unsigned int GetSpillTrailHumidity()  {return _spillHumidity;}
  unsigned int GetSpillTrailTemp()      {return _spillTemp;}
  unsigned int GetSpillTrailTime()      {return _spillTrailTime;}
  
  unsigned int GetNumOfTriggers()       {return _trigEvents.size();}
  MDpartEventBM*    GetTriggerEventPtr(unsigned int evId);

 private:
     
  unsigned int _boardId;
  unsigned int _spillTag;
  unsigned int _humidity;
  unsigned int _temperature;
  unsigned int _spillTime;
  
  unsigned int _spillHeaderID;
  unsigned int _spillDAQType;
  unsigned int _spillTimeGTrig;
  
  unsigned int _spillTrailTag;
  unsigned int _spillHumidity;
  unsigned int _spillTemp;
  unsigned int _spillTrailTime;
  
  std::vector <MDpartEventBM*> _trigEvents;
};

// ostream &operator<<(std::ostream &s, MDfragmentBM &df);

#endif
