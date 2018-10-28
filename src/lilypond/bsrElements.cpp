/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include "bsrElements.h"

#include "bsrOptions.h"


using namespace std;

namespace MusicXML2 
{

//_______________________________________________________________________________
S_bsrElement bsrElement::create (
  int inputLineNumber)
{
  bsrElement* o =
    new bsrElement (
      inputLineNumber);
  assert(o!=0);
  return o;
}

bsrElement::bsrElement (
  int inputLineNumber)
    : msrElement (inputLineNumber)
{}

bsrElement::~bsrElement ()
{}

void bsrElement::acceptIn (basevisitor* v)
{
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrElement::acceptIn ()" <<
      endl;
  }
  
  if (visitor<S_bsrElement>*
    p =
      dynamic_cast<visitor<S_bsrElement>*> (v)) {
        S_bsrElement elem = this;
        
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrElement::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void bsrElement::acceptOut (basevisitor* v)
{
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrElement::acceptOut ()" <<
      endl;
  }

  if (visitor<S_bsrElement>*
    p =
      dynamic_cast<visitor<S_bsrElement>*> (v)) {
        S_bsrElement elem = this;
      
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrElement::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

void bsrElement::browseData (basevisitor* v)
{}


}
