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

#include "MDfragmentBM.h"
#include "MDdataWordBM.h"

using namespace std;

void MDfragmentBM::SetDataPtr( void *d, uint32_t aSize ) {
  MDdataContainer::SetDataPtr(d);
  this->Init();
}

void MDfragmentBM::Clean() {
  this->UnValidate();

  int nTr = _trigEvents.size();
  for (int i=0; i<nTr; ++i) {
    delete _trigEvents[i];
  }
  _trigEvents.resize(0);
}

void MDfragmentBM::Init() {
//     cout << " Calling MDfragmentBM::Init() " << endl;
  this->Clean();
  _size = 4;

  unsigned int * ptr = this->Get32bWordPtr(0);
  MDdataWordBM dw(ptr);
  if ( dw.IsValid() ) {
       
    if (dw.GetDataType() != MDdataWordBM::SpillHeader && dw.GetSpillHeadId() !=1) { 
        throw MDexception("ERROR in MDfragmentBM::Init() : 1st word is not a spill header.");
    } else {
        _spillDAQType = dw.GetSpillDAQType(); 
        _spillTimeGTrig = dw.GetSpillTimeGTRIG();
        _boardId = dw.GetBoardId();
        cout <<"BM spill Header \"B\" DAQ Type: "<< _spillDAQType<< " Spill Time from GTRIG (10ns res.): " << _spillTimeGTrig<<endl;
        _size += 4;
        ++ptr;
        dw.SetDataPtr(ptr);
      
        if (dw.GetDataType() != MDdataWordBM::SpillTrailer2) {
             throw MDexception("ERROR in MDfragmentBM::Init() : 2nd word is not a spill spill time.");
        } else {
            _spillTime = dw.GetSpillTime();
            ++ptr;
            dw.SetDataPtr(ptr);
            _size += 4;
            bool done(false);
            while (!done) {
                //cout   <<_size/4 <<" "<<dw<<endl;
                dw.SetDataPtr(ptr);
                //cout   <<_size/4<<endl;
                //if (dw.GetDataType() != MDdataWordBM::TrigHeader )
                if (dw.GetDataType() == MDdataWordBM::TrigHeader) {
                    //cout   <<_size/4 <<" " << dw.GetDataType()<<endl;
                    MDpartEventBM *xPe = new MDpartEventBM(ptr);
                    xPe->SetTriggerEvents(&_trigEvents);
                    xPe->Init();
                    unsigned int pe_size = xPe->GetSize();
                    _size += pe_size;
                    ptr += pe_size/4;
                    if (xPe->getNumDataWords() > 3) {
                        _trigEvents.push_back( xPe );
                        //cout<< dw.GetSpillTag()<< " " <<GetBoardId()<<endl;
                        if(xPe->spillHeaderAExists()) {
                            _spillTag = xPe->GetSpillHeaderA();
                            if (_boardId == xPe->GetSpillHeaderABoardID())
                                _boardId=xPe->GetSpillHeaderABoardID();
                            else 
                                return;
                        }
                    } else {
                        delete xPe;
                        }
                } else if (dw.GetDataType() == MDdataWordBM::SpillHeader && dw.GetSpillHeadId() == 0){
                     _spillTag = dw.GetSpillTag();
                     _boardId = dw.GetBoardId();
                     cout   <<"1: BM spill Header \"A\" Board ID "<< _boardId <<" SpillTag: "<< dw.GetSpillTag()<<endl;
                      ++ptr;
                     dw.SetDataPtr(ptr);
                     _size += 4;
                } else if (dw.GetDataType() == MDdataWordBM::SpillTrailer1 ) {
                    
                    dw.SetDataPtr(--ptr);
                    if (dw.GetDataType() == MDdataWordBM::SpillTrailer1 && dw.GetSpillHeadId() == 0) {
                        if (_spillTag == dw.GetSpillTag()){
                            //cout<< "a: "<<dw<<endl;
                            done = true;
                        } else {
                            cout << dw.GetSpillTag() << "!=" << _spillTag<<endl;
                            throw MDexception("ERROR in MDfragmentBM::Init() :  The Spill trailer is not consistent.");
                        }
                    }
                    else {
                        throw MDexception("ERROR in MDfragmentBM::Init() : Wrong data type.");
                    }
                    
                    dw.SetDataPtr(++ptr);
                    if (dw.GetDataType() == MDdataWordBM::SpillTrailer1 && dw.GetSpillHeadId() == 1) {
                        _spillHumidity = dw.GetHumidity();
                        _spillTemp = dw.GetTemperature();
                        _size += 4;
                        //cout<< "b: "<<dw<<endl<<" Humidity: "<<_spillHumidity<< " Temperature " <<_spillTemp<<endl;
                    }
                    else {
                        throw MDexception("ERROR in MDfragmentBM::Init() : Wrong data type.");
                    }
                    
                    dw.SetDataPtr(++ptr);
                    if (dw.GetDataType() == MDdataWordBM::SpillTrailer2 ){
                        _spillTrailTime = dw.GetSpillTime();
                        _size += 4;
                        //cout<< "c: "<<dw<<endl;
                    }
                    else {
                        throw MDexception("ERROR in MDfragmentBM::Init() : Wrong data type.");
                    }
                    
                } else {
                    //cout << dw << endl;
                    ++ptr;
                    _size += 4;
                    dw.SetDataPtr(ptr);
                    //throw MDexception("ERROR in MDfragmentBM::Init() : Wrong data type.");
                }
            }
            
        }
    }
    cout<<"\n";
  }
}

MDpartEventBM* MDfragmentBM::GetTriggerEventPtr(unsigned int evId) {
  if ( evId >= _trigEvents.size() ) {
    stringstream ss;
    ss << "ERROR in MDfragmentBM::GetTriggerEventPtr() : ";
    ss << "Wrong Event Id: " << evId << ". Exceeds the total number of triggers." ;
    throw MDexception( ss.str() );
  }

  return _trigEvents[evId];
}

void MDfragmentBM::Dump() {

}
