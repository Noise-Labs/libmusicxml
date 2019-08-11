/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <climits>      // INT_MIN, INT_MAX
#include <iomanip>      // setw, setprecision, ...
#include <sstream>

#include <regex>

#include "utilities.h"

#include "generalOah.h"

#include "setTraceOahIfDesired.h"
#ifdef TRACE_OAH
  #include "traceOah.h"
#endif

#include "msrOah.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_msrRenamePartAtom msrRenamePartAtom::create (
  string               shortName,
  string               longName,
  string               description,
  string               valueSpecification,
  string               variableName,
  map<string, string>& stringStringMapVariable)
{
  msrRenamePartAtom* o = new
    msrRenamePartAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      variableName,
      stringStringMapVariable);
  assert(o!=0);
  return o;
}

msrRenamePartAtom::msrRenamePartAtom (
  string               shortName,
  string               longName,
  string               description,
  string               valueSpecification,
  string               variableName,
  map<string, string>& stringStringMapVariable)
  : oahValuedAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      variableName),
    fStringStringMapVariable (
      stringStringMapVariable)
{}

msrRenamePartAtom::~msrRenamePartAtom ()
{}

S_oahValuedAtom msrRenamePartAtom::handleOptionUnderName (
  string   optionName,
  ostream& os)
{
  // an option value is needed
  return this;
}

void msrRenamePartAtom::handleValue (
  string   theString,
  ostream& os)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "==> oahAtom is of type 'msrRenamePartAtom'" <<
      endl;
  }
#endif

  // theString contains the part rename specification
  // decipher it to extract the old and new part names

#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "==> oahAtom is of type 'msrRenamePartAtom'" <<
      endl;
  }
#endif

  string regularExpression (
    "[[:space:]]*([^[:space:]]*)[[:space:]]*"
    "="
    "[[:space:]]*([^[:space:]]*)[[:space:]]*");

  regex  e (regularExpression);
  smatch sm;

  regex_match (theString, sm, e);

  unsigned smSize = sm.size ();

#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "There are " << smSize << " matches" <<
      " for part rename string '" << theString <<
      "' with regex '" << regularExpression <<
      "'" <<
      endl;
  }
#endif

  if (smSize == 3) {
#ifdef TRACE_OAH
    if (gExecutableOah->fTraceOah) {
      for (unsigned i = 0; i < smSize; ++i) {
        os <<
          "[" << sm [i] << "] ";
      } // for
      os << endl;
    }
#endif
  }

  else {
    stringstream s;

    s <<
      "-msrPartRename argument '" << theString <<
      "' is ill-formed";

    oahError (s.str ());
    exit (4);
  }

  string
    oldPartName = sm [1],
    newPartName = sm [2];

#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "--> oldPartName = \"" << oldPartName << "\", " <<
      "--> newPartName = \"" << newPartName << "\"" <<
      endl;
  }
#endif

  // is this part name in the part renaming map?
  map<string, string>::iterator
    it =
      fStringStringMapVariable.find (oldPartName);

  if (it != fStringStringMapVariable.end ()) {
    // yes, issue error message
    stringstream s;

    s <<
      "Part \"" << oldPartName << "\" occurs more that one" <<
      "in the '--partName' option";

    oahError (s.str ());
    exit (4);
  }

  else {
    fStringStringMapVariable [oldPartName] = newPartName;
  }
}

void msrRenamePartAtom::acceptIn (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrRenamePartAtom::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_msrRenamePartAtom>*
    p =
      dynamic_cast<visitor<S_msrRenamePartAtom>*> (v)) {
        S_msrRenamePartAtom elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrRenamePartAtom::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void msrRenamePartAtom::acceptOut (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrRenamePartAtom::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_msrRenamePartAtom>*
    p =
      dynamic_cast<visitor<S_msrRenamePartAtom>*> (v)) {
        S_msrRenamePartAtom elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrRenamePartAtom::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void msrRenamePartAtom::browseData (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrRenamePartAtom::browseData ()" <<
      endl;
  }
#endif
}

string msrRenamePartAtom::asShortNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fShortName << " ";

  if (! fStringStringMapVariable.size ()) {
    s << "none";
  }
  else {
    map<string, string>::const_iterator
      iBegin = fStringStringMapVariable.begin (),
      iEnd   = fStringStringMapVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      s << (*i).first << "=" << (*i).second;
      if (++i == iEnd) break;
      s << ",";
    } // for
  }

  return s.str ();
}

string msrRenamePartAtom::asLongNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fLongName << " ";

  if (! fStringStringMapVariable.size ()) {
    s << "none";
  }
  else {
    map<string, string>::const_iterator
      iBegin = fStringStringMapVariable.begin (),
      iEnd   = fStringStringMapVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      s << (*i).first << "=" << (*i).second;
      if (++i == iEnd) break;
      s << ",";
    } // for
  }

  return s.str ();
}

void msrRenamePartAtom::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "msrRenamePartAtom:" <<
    endl;

  gIndenter++;

  printValuedAtomEssentials (
    os, fieldWidth);

  os << left <<
    setw (fieldWidth) <<
    "fVariableName" << " : " <<
    fVariableName <<
    setw (fieldWidth) <<
    "fStringStringMapVariable" << " : " <<
    endl;

  if (! fStringStringMapVariable.size ()) {
    os << "none";
  }
  else {
    map<string, string>::const_iterator
      iBegin = fStringStringMapVariable.begin (),
      iEnd   = fStringStringMapVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os << (*i).first << " --> " << (*i).second;
      if (++i == iEnd) break;
      os << endl;
    } // for
  }

  os << endl;
}

void msrRenamePartAtom::printAtomOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  os << left <<
    setw (valueFieldWidth) <<
    fVariableName <<
    " : ";

  if (! fStringStringMapVariable.size ()) {
    os <<
      "none" <<
      endl;
  }
  else {
    os << endl;
    gIndenter++;

    map<string, string>::const_iterator
      iBegin = fStringStringMapVariable.begin (),
      iEnd   = fStringStringMapVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os <<
        "\"" <<
        (*i).first <<
        "\" --> \"" <<
        (*i).second <<
        "\"" <<
        endl;
      if (++i == iEnd) break;
    } // for

    gIndenter--;
  }
}

ostream& operator<< (ostream& os, const S_msrRenamePartAtom& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_msrTransposePartAtom msrTransposePartAtom::create (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             variableName,
  map<string, S_msrSemiTonesPitchAndOctave>&
                     stringMsrSemiTonesPitchAndOctaveVariable)
{
  msrTransposePartAtom* o = new
    msrTransposePartAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      variableName,
      stringMsrSemiTonesPitchAndOctaveVariable);
  assert(o!=0);
  return o;
}

msrTransposePartAtom::msrTransposePartAtom (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             variableName,
  map<string, S_msrSemiTonesPitchAndOctave>&
                     stringMsrSemiTonesPitchAndOctaveVariable)
  : oahValuedAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      variableName),
    fStringMsrSemiTonesPitchAndOctaveVariable (
      stringMsrSemiTonesPitchAndOctaveVariable)
{}

msrTransposePartAtom::~msrTransposePartAtom ()
{}

S_oahValuedAtom msrTransposePartAtom::handleOptionUnderName (
  string   optionName,
  ostream& os)
{
  // an option value is needed
  return this;
}

void msrTransposePartAtom::handleValue (
  string   theString,
  ostream& os)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "==> oahAtom is of type 'msrTransposePartAtom'" <<
      endl;
  }
#endif

  // theString contains the part transpose specification
  // decipher it to extract the old and new part names

  string regularExpression (
    "[[:space:]]*(.*)[[:space:]]*"
    "="
    "[[:space:]]*(.*)[[:space:]]*");

  regex  e (regularExpression);
  smatch sm;

  regex_match (theString, sm, e);

  unsigned smSize = sm.size ();

#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "There are " << smSize << " matches" <<
      " for part transpose string '" << theString <<
      "' with regex '" << regularExpression <<
      "'" <<
      endl;
  }
#endif

  if (smSize == 3) {
#ifdef TRACE_OAH
    if (gExecutableOah->fTraceOah) {
      for (unsigned i = 0; i < smSize; ++i) {
        os <<
          "[" << sm [i] << "] ";
      } // for
      os << endl;
    }
#endif
  }

  else {
    stringstream s;

    s <<
      "-marTransposePart argument '" << theString <<
      "' is ill-formed";

    oahError (s.str ());
    exit (4);
  }

  string
    originalPitchName    = sm [1],
    destinationPitchName = sm [2];

#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "--> originalPitchName = \"" << originalPitchName << "\", " <<
      "--> destinationPitchName = \"" << destinationPitchName << "\"" <<
      endl;
  }
#endif

  // is this part name in the part renaming map?
  map<string, S_msrSemiTonesPitchAndOctave>::iterator
    it =
      fStringMsrSemiTonesPitchAndOctaveVariable.find (originalPitchName);

  if (it != fStringMsrSemiTonesPitchAndOctaveVariable.end ()) {
    // yes, issue error message
    stringstream s;

    s <<
      "Part \"" << originalPitchName << "\" occurs more that one" <<
      "in the '--transpose-part' option";

    oahError (s.str ());
    exit (4);
  }

  else {
    fStringMsrSemiTonesPitchAndOctaveVariable [originalPitchName] =
      msrSemiTonesPitchAndOctave::createFromString (
        K_NO_INPUT_LINE_NUMBER,
        destinationPitchName);
  }
}

void msrTransposePartAtom::acceptIn (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrTransposePartAtom::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_msrTransposePartAtom>*
    p =
      dynamic_cast<visitor<S_msrTransposePartAtom>*> (v)) {
        S_msrTransposePartAtom elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrTransposePartAtom::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void msrTransposePartAtom::acceptOut (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrTransposePartAtom::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_msrTransposePartAtom>*
    p =
      dynamic_cast<visitor<S_msrTransposePartAtom>*> (v)) {
        S_msrTransposePartAtom elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrTransposePartAtom::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void msrTransposePartAtom::browseData (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrTransposePartAtom::browseData ()" <<
      endl;
  }
#endif
}

string msrTransposePartAtom::asShortNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fShortName << " ";

  if (! fStringMsrSemiTonesPitchAndOctaveVariable.size ()) {
    s << "none";
  }
  else {
    map<string, S_msrSemiTonesPitchAndOctave>::const_iterator
      iBegin = fStringMsrSemiTonesPitchAndOctaveVariable.begin (),
      iEnd   = fStringMsrSemiTonesPitchAndOctaveVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      s << (*i).first << "=" << (*i).second;
      if (++i == iEnd) break;
      s << ",";
    } // for
  }

  return s.str ();
}

string msrTransposePartAtom::asLongNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fLongName << " ";

  if (! fStringMsrSemiTonesPitchAndOctaveVariable.size ()) {
    s << "none";
  }
  else {
    map<string, S_msrSemiTonesPitchAndOctave>::const_iterator
      iBegin = fStringMsrSemiTonesPitchAndOctaveVariable.begin (),
      iEnd   = fStringMsrSemiTonesPitchAndOctaveVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      s << (*i).first << "=" << (*i).second;
      if (++i == iEnd) break;
      s << ",";
    } // for
  }

  return s.str ();
}

void msrTransposePartAtom::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "msrTransposePartAtom:" <<
    endl;

  gIndenter++;

  printValuedAtomEssentials (
    os, fieldWidth);

  os << left <<
    setw (fieldWidth) <<
    "fVariableName" << " : " <<
    fVariableName <<
    setw (fieldWidth) <<
    "fStringMsrSemiTonesPitchAndOctaveVariable" << " : " <<
    endl;

  if (! fStringMsrSemiTonesPitchAndOctaveVariable.size ()) {
    os << "none";
  }
  else {
    map<string, S_msrSemiTonesPitchAndOctave>::const_iterator
      iBegin = fStringMsrSemiTonesPitchAndOctaveVariable.begin (),
      iEnd   = fStringMsrSemiTonesPitchAndOctaveVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os << (*i).first << " --> " << (*i).second;
      if (++i == iEnd) break;
      os << endl;
    } // for
  }

  os << endl;
}

void msrTransposePartAtom::printAtomOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  os << left <<
    setw (valueFieldWidth) <<
    fVariableName <<
    " : ";

  if (! fStringMsrSemiTonesPitchAndOctaveVariable.size ()) {
    os <<
      "none" <<
      endl;
  }
  else {
    os << endl;

    gIndenter++;

    map<string, S_msrSemiTonesPitchAndOctave>::const_iterator
      iBegin = fStringMsrSemiTonesPitchAndOctaveVariable.begin (),
      iEnd   = fStringMsrSemiTonesPitchAndOctaveVariable.end (),
      i      = iBegin;
    for ( ; ; ) {
      os <<
        "\"" <<
        (*i).first <<
        "\" --> \"" <<
        (*i).second <<
        "\"" <<
        endl;
      if (++i == iEnd) break;
    } // for

    gIndenter--;
  }
}

ostream& operator<< (ostream& os, const S_msrTransposePartAtom& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_msrPitchesLanguageAtom msrPitchesLanguageAtom::create (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             variableName,
  msrQuarterTonesPitchesLanguageKind&
                     optionsMsrPitchesLanguageKindVariable)
{
  msrPitchesLanguageAtom* o = new
    msrPitchesLanguageAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      variableName,
      optionsMsrPitchesLanguageKindVariable);
  assert(o!=0);
  return o;
}

msrPitchesLanguageAtom::msrPitchesLanguageAtom (
  string             shortName,
  string             longName,
  string             description,
  string             valueSpecification,
  string             variableName,
  msrQuarterTonesPitchesLanguageKind&
                     optionsMsrPitchesLanguageKindVariable)
  : oahValuedAtom (
      shortName,
      longName,
      description,
      valueSpecification,
      variableName),
    fMsrQuarterTonesPitchesLanguageKindVariable (
      optionsMsrPitchesLanguageKindVariable)
{}

msrPitchesLanguageAtom::~msrPitchesLanguageAtom ()
{}

S_oahValuedAtom msrPitchesLanguageAtom::handleOptionUnderName (
  string   optionName,
  ostream& os)
{
  // an option value is needed
  return this;
}

void msrPitchesLanguageAtom::handleValue (
  string   theString,
  ostream& os)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "==> oahAtom is of type 'msrPitchesLanguageAtom'" <<
      endl;
  }
#endif

  // theString contains the language name:
  // is it in the pitches languages map?

#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah) {
    os <<
      "==> oahAtom is of type 'msrPitchesLanguageAtom'" <<
      endl;
  }
#endif

  map<string, msrQuarterTonesPitchesLanguageKind>::const_iterator
    it =
      gQuarterTonesPitchesLanguageKindsMap.find (
        theString);

  if (it == gQuarterTonesPitchesLanguageKindsMap.end ()) {
    // no, language is unknown in the map

    stringstream s;

    s <<
      "MSR pitches language '" << theString <<
      "' is unknown" <<
      endl <<
      "The " <<
      gQuarterTonesPitchesLanguageKindsMap.size () <<
      " known MSR pitches languages are:" <<
      endl;

    gIndenter++;

    s <<
      existingQuarterTonesPitchesLanguageKinds ();

    gIndenter--;

    oahError (s.str ());
    exit (4); // JMI
  }

  setMsrQuarterTonesPitchesLanguageKindVariable (
    (*it).second);
}

void msrPitchesLanguageAtom::acceptIn (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrPitchesLanguageAtom::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_msrPitchesLanguageAtom>*
    p =
      dynamic_cast<visitor<S_msrPitchesLanguageAtom>*> (v)) {
        S_msrPitchesLanguageAtom elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrPitchesLanguageAtom::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void msrPitchesLanguageAtom::acceptOut (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrPitchesLanguageAtom::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_msrPitchesLanguageAtom>*
    p =
      dynamic_cast<visitor<S_msrPitchesLanguageAtom>*> (v)) {
        S_msrPitchesLanguageAtom elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrPitchesLanguageAtom::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void msrPitchesLanguageAtom::browseData (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrPitchesLanguageAtom::browseData ()" <<
      endl;
  }
#endif
}

string msrPitchesLanguageAtom::asShortNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fShortName << " " <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fMsrQuarterTonesPitchesLanguageKindVariable);

  return s.str ();
}

string msrPitchesLanguageAtom::asLongNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fLongName << " " <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fMsrQuarterTonesPitchesLanguageKindVariable);

  return s.str ();
}

void msrPitchesLanguageAtom::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "msrPitchesLanguageAtom:" <<
    endl;

  gIndenter++;

  printValuedAtomEssentials (
    os, fieldWidth);

  os << left <<
    setw (fieldWidth) <<
    "fVariableName" << " : " <<
    fVariableName <<
    endl <<
    setw (fieldWidth) <<
    "fmsrPitchesLanguageVariable" << " : \"" <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fMsrQuarterTonesPitchesLanguageKindVariable) <<
      "\"" <<
    endl;
}

void msrPitchesLanguageAtom::printAtomOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  os << left <<
    setw (valueFieldWidth) <<
    fVariableName <<
    " : \"" <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fMsrQuarterTonesPitchesLanguageKindVariable) <<
    "\"" <<
    endl;
}

ostream& operator<< (ostream& os, const S_msrPitchesLanguageAtom& elt)
{
  elt->print (os);
  return os;
}

//_______________________________________________________________________________
S_msrOah gMsrOah;
S_msrOah gMsrOahUserChoices;
S_msrOah gMsrOahWithDetailedTrace;

S_msrOah msrOah::create (
  S_oahHandler handlerUpLink)
{
  msrOah* o = new msrOah(
    handlerUpLink);
  assert(o!=0);
  return o;
}

msrOah::msrOah (
  S_oahHandler handlerUpLink)
  : oahGroup (
    "MSR",
    "hmsr", "help-msr",
R"(These options control the way MSR data is handled.)",
    kElementVisibilityAlways,
    handlerUpLink)
{
  // append this options group to the options handler
  // if relevant
  if (handlerUpLink) {
    handlerUpLink->
      appendGroupToHandler (this);
  }

  // initialize it
  initializeMsrOah (false);
}

msrOah::~msrOah ()
{}

#ifdef TRACE_OAH
void msrOah::initializeMsrTraceOah (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup subGroup =
    oahSubGroup::create (
      "Trace",
      "hmsrt", "help-msr-trace",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (subGroup);

  // MSR

  fTraceMsr          = boolOptionsInitialValue;

  subGroup->
    appendAtom (
      oahBooleanAtom::create (
        "tmsr", "trace-msr",
R"(Write a trace of the LPSR graphs visiting activity to standard error.)",
        "traceMsr",
        fTraceMsr));

  // MSR visitors

  fTraceMsrVisitors  = boolOptionsInitialValue;

  subGroup->
    appendAtom (
      oahBooleanAtom::create (
        "tmsrv", "trace-msr-visitors",
R"(Write a trace of the MSR graphs visiting activity to standard error.)",
        "traceMsrVisitors",
        fTraceMsrVisitors));
}
#endif

void msrOah::initializeMsrDisplayOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup displaySubGroup =
    oahSubGroup::create (
      "Display",
      "hmsrtd", "help-msr-trace-and-display",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (displaySubGroup);

  // partgroups

  fDisplayPartGroups = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dpg", "display-partgroups",
R"(Write the structure of the part groups to standard error.)",
        "displayPartGroups",
        fDisplayPartGroups));

  // MSR

  fDisplayMsr        = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dmsr", "display-msr",
R"(Write the contents of the MSR data to standard error.)",
        "displayMsr",
        fDisplayMsr));

  // MSR details

  fDisplayMsrDetails = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahTwoBooleansAtom::create (
        "dmsrd", "display-msr-details",
R"(Write the contents of the MSR data with more details to standard error.)",
        "displayMsrDetails",
        fDisplayMsrDetails,
        fDisplayMsr));

  // MSR names

  fDisplayMsrNames   = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dmnames", "display-msr-names",
R"(Only write a view of the names in the MSR to standard error.
This implies that no LilyPond code is generated.)",
        "displayMsrNames",
        fDisplayMsrNames));

  // MSR summary

  fDisplayMsrSummary = boolOptionsInitialValue;

  displaySubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "dmsum", "display-msr-summary",
R"(Only write a summary of the MSR to standard error.
This implies that no LilyPond code is generated.)",
        "displayMsrSummary",
        fDisplayMsrSummary));
}

void msrOah::initializeMsrLanguagesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup languagesSubGroup =
    oahSubGroup::create (
      "Languages",
      "hmsrlang", "help-msr-languages",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (languagesSubGroup);

  // notes pitches

  if (! setMsrQuarterTonesPitchesLanguage ("nederlands")) {
    stringstream s;

    s <<
      "INTERNAL INITIALIZATION ERROR: "
      "MSR pitches language 'nederlands' is unknown" <<
      endl <<
      "The " <<
      gQuarterTonesPitchesLanguageKindsMap.size () <<
      " known MSR pitches languages are:" <<
      endl;

    gIndenter++;

    s <<
      existingQuarterTonesPitchesLanguageKinds ();

    gIndenter--;

    oahError (s.str ());
  }

  const msrQuarterTonesPitchesLanguageKind
    msrQuarterTonesPitchesLanguageKindDefaultValue =
      kNederlands; //LilyPond default value

  languagesSubGroup->
    appendAtom (
      msrPitchesLanguageAtom::create (
        "mplang", "msr-pitches-language",
        replaceSubstringInString (
          replaceSubstringInString (
            replaceSubstringInString (
R"(Use LANGUAGE to display note pitches in the MSR logs and text views.
The NUMBER LilyPond pitches languages available are:
PITCHES_LANGUAGES.
The default is 'DEFAULT_VALUE'.)",
              "NUMBER",
              to_string (gQuarterTonesPitchesLanguageKindsMap.size ())),
            "PITCHES_LANGUAGES",
            existingQuarterTonesPitchesLanguageKinds ()),
          "DEFAULT_VALUE",
          msrQuarterTonesPitchesLanguageKindAsString (
            msrQuarterTonesPitchesLanguageKindDefaultValue)),
        "LANGUAGE",
        "msrPitchesLanguage",
        fMsrQuarterTonesPitchesLanguageKind));
}

void msrOah::initializeMsrPartsOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup partsSubGroup =
    oahSubGroup::create (
      "Parts",
      "hmsrp", "help-msr-parts",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (partsSubGroup);

  // MSR part rename

  partsSubGroup->
    appendAtom (
      msrRenamePartAtom::create (
        "mrp", "msr-rename-part",
        replaceSubstringInString (
R"(Rename part ORIGINAL_NAME to NEW_NAME, for example after displaying
the names in the score or a summary of the latter in a first run with options
'-dmnames, -display-msr-names' or 'dmsum, -display-msr-summary'.
PART_RENAME_SPEC can be:
'ORIGINAL_NAME = NEW_NAME'
or
"ORIGINAL_NAME = NEW_NAME"
The single or double quotes are used to allow spaces in the names
and around the '=' sign, otherwise they can be dispensed with.
Using double quotes allows for shell variables substitutions, as in:
DESSUS="Cor anglais"
EXECUTABLE -msr-rename-part "P1 = ${DESSUS}" .
There can be several occurrences of this option.)",
         "EXECUTABLE",
          gExecutableOah->fHandlerExecutableName),
        "PART_RENAME_SPEC",
        "partsRenamingMap",
        fPartsRenamingMap));

  // MSR part transpose

  partsSubGroup->
    appendAtom (
      msrTransposePartAtom::create (
        "mtp", "msr-transpose-part",
R"(Transpose part ORIGINAL_NAME using TRANSPOSITION to tranpose in the MSR data.
PART_TRANSPOSITION_SPEC can be:
'ORIGINAL_NAME = TRANSPOSITION'
or
"ORIGINAL_NAME = TRANSPOSITION"
The single or double quotes are used to allow spaces in the names
and around the '=' sign, otherwise they can be dispensed with.
TRANSPOSITION should contain a diatonic pitch, followed if needed
by a sequence of ',' or '\'' octave indications.
Such indications cannot be mixed, and they are relative to c\', i.e. middle C.
For example, 'a', 'f' and 'bes,' can be used respectively
for instruments in 'a', 'f' and B flat respectively.
Using double quotes allows for shell variables substitutions, as in:
SAXOPHONE="bes,"
EXECUTABLE -msr-transpose-part "P1 ${SAXOPHONE}" .
There can be several occurrences of this option.)",
        "PART_TRANSPOSITION_SPEC",
        "partsTranspositionMap",
        fPartsTranspositionMap));
}

void msrOah::initializeMsrStavesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup stavesSubGroup =
    oahSubGroup::create (
      "Staves",
      "hmsrs", "help-msr-staves",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (stavesSubGroup);

  // single line staves

  fCreateVoicesStaffRelativeNumbers = boolOptionsInitialValue;

  stavesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "cslsar", "create-single-line-staves-as-rythmic",
R"(Create staves with a single line as rythmic staves.
By default, drum staves are created in this case.)",
        "createSingleLineStavesAsRythmic",
        fCreateSingleLineStavesAsRythmic));
}

void msrOah::initializeMsrVoicesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup voicesSubGroup =
    oahSubGroup::create (
      "Voices",
      "hmsrv", "help-msr-voices",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (voicesSubGroup);

  // staff relative numbers

  fCreateVoicesStaffRelativeNumbers = boolOptionsInitialValue;

  voicesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "cvsrvn", "create-voices-staff-relative-numbers",
R"(Generate voices names with numbers relative to their staff.
By default, the voice numbers found are used,
which may be global to the score.)",
        "createVoicesStaffRelativeNumbers",
        fCreateVoicesStaffRelativeNumbers));
}

void msrOah::initializeMsrRepeatsOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup repeatsSubGroup =
    oahSubGroup::create (
      "Repeats",
      "hmsrr", "help-msr-repeats",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (repeatsSubGroup);

  // barlines

  fCreateImplicitInitialRepeatBarline = boolOptionsInitialValue;

  repeatsSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "ciirb", "create-implicit-initial-repeat-barline",
R"(Create an implicit repeat barline at the beginning of the stave
in case there is none, as is usual in scores.
By default, no such barline is added.)",
        "createImplicitInitialRepeatBarline",
        fCreateImplicitInitialRepeatBarline));
}

void msrOah::initializeMsrNotesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup notesSubGroup =
    oahSubGroup::create (
      "Notes",
      "hmsrn", "help-msr-notes",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (notesSubGroup);

  // delay rests dynamics

  fDelayRestsDynamics = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drdyns", "delay-rests-dynamics",
R"()",
        "delayRestsDynamics",
        fDelayRestsDynamics));

  // delay rests words

  fDelayRestsWords = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drwords", "delay-rests-words",
R"()",
        "delayRestsWords",
        fDelayRestsWords));

  // delay rests beams

  fDelayRestsBeams = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drbeams", "delay-rests-beams",
R"()",
        "delayRestsBeams",
        fDelayRestsBeams));

  // delay rests slurs

  fDelayRestsSlurs = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drslurs", "delay-rests-slurs",
R"()",
        "delayRestsSlurs",
        fDelayRestsSlurs));

  // delay rests ligatures

  fDelayRestsLigatures = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drligs", "delay-rests-ligatures",
R"(<bracket/> in MusicXML, '\[... \}' in LilyPond)",
        "delayRestsLigatures",
        fDelayRestsLigatures));

  // delay rests pedals

  fDelayRestsPedals = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drpeds", "delay-rests-pedals",
R"()",
        "delayRestsPedals",
        fDelayRestsPedals));

  // delay rests slashes

  fDelayRestsSlashes = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drslashes", "delay-rests-slashes",
R"('<slash/>' in MusicXML)",
        "delayRestsSlashes",
        fDelayRestsSlashes));

  // delay rests wedges

  fDelayRestsWedges = false;

  notesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "drwedges", "delay-rests-wedges",
R"('<wedge/>' in MusicXML, '<!' in LilyPond)",
        "delayRestsWedges",
        fDelayRestsWedges));
}

void msrOah::initializeMsrLyricsOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup lyricsSubGroup =
    oahSubGroup::create (
      "Lyrics",
      "hmsrlyrd", "help-msr-lyrics",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (lyricsSubGroup);

  // stanzas numbers

  fAddStanzasNumbers  = false;

  lyricsSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "asn", "add-stanzas-numbers",
R"(Add stanzas numbers to lyrics.)",
        "addStanzasNumbers",
        fAddStanzasNumbers));
}

void msrOah::initializeMsrHarmoniesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup harmoniesSubGroup =
    oahSubGroup::create (
      "Harmonies",
      "hmsrh", "help-msr-harmonies",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (harmoniesSubGroup);

  // show harmony voices

  fShowHarmonyVoices      = boolOptionsInitialValue;

  harmoniesSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "shv", "show-harmony-voices",
R"(Show the parts harmony voices in the MSR data
even though it does not contain music.)",
        "showHarmonyVoices",
        fShowHarmonyVoices));
}

void msrOah::initializeMsrFiguredBassOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup figuredBassSubGroup =
    oahSubGroup::create (
      "Figured bass",
      "hmsrfb", "help-msr-figured-bass",
R"()",
    kElementVisibilityAlways,
    this);

  appendSubGroup (figuredBassSubGroup);

  // show figured bass voices

  fShowFiguredBassVoices      = boolOptionsInitialValue;

  figuredBassSubGroup->
    appendAtom (
      oahBooleanAtom::create (
        "sfbv", "show-figured-bass-voices",
R"(Show the figured bass harmony voices in the MSR data
even though they do not contain music.)",
        "showFiguredBassVoices",
        fShowFiguredBassVoices));
}

void msrOah::initializeMsrExitAfterSomePassesOptions (
  bool boolOptionsInitialValue)
{
  S_oahSubGroup
    exitAfterSomePassesSubGroup =
      oahSubGroup::create (
        "Exit after some passes",
        "hme", "help-msr-exit",
R"()",
      kElementVisibilityAlways,
      this);

  appendSubGroup (exitAfterSomePassesSubGroup);

  // exit after pass 2a

  fExit2a = boolOptionsInitialValue;

  S_oahBooleanAtom
    exit2aOahBooleanAtom =
      oahBooleanAtom::create (
        "e2a", "exit-2a",
R"(Exit after pass 2a, i.e. after conversion
of the MusicXML tree to an MSR skeleton.)",
        "exit2a",
        fExit2a);

  exitAfterSomePassesSubGroup->
    appendAtom (
      exit2aOahBooleanAtom);

  // exit after pass 2b

  fExit2b = boolOptionsInitialValue;

  S_oahBooleanAtom
    exit2bOahBooleanAtom =
      oahBooleanAtom::create (
        "e2b", "exit-2b",
R"(Exit after pass 2b, i.e. after conversion
of the MusicXML tree to MSR.)",
        "exit2b",
        fExit2b);

  exitAfterSomePassesSubGroup->
    appendAtom (
      exit2bOahBooleanAtom);
}

void msrOah::initializeMsrOah (
  bool boolOptionsInitialValue)
{
#ifdef TRACE_OAH
  // trace
  // --------------------------------------
  initializeMsrTraceOah (
    boolOptionsInitialValue);
#endif

  // display
  // --------------------------------------
  initializeMsrDisplayOptions (
    boolOptionsInitialValue);

  // languages
  // --------------------------------------
  initializeMsrLanguagesOptions (
    boolOptionsInitialValue);

  // parts
  // --------------------------------------
  initializeMsrPartsOptions (
    boolOptionsInitialValue);

  // staves
  // --------------------------------------
  initializeMsrStavesOptions (
    boolOptionsInitialValue);

  // voices
  // --------------------------------------
  initializeMsrVoicesOptions (
    boolOptionsInitialValue);

  // repeats
  // --------------------------------------
  initializeMsrRepeatsOptions (
    boolOptionsInitialValue);

  // notes
  // --------------------------------------
  initializeMsrNotesOptions (
    boolOptionsInitialValue);

  // lyrics
  // --------------------------------------
  initializeMsrLyricsOptions (
    boolOptionsInitialValue);

  // harmonies
  // --------------------------------------
  initializeMsrHarmoniesOptions (
    boolOptionsInitialValue);

  // figured bass
  // --------------------------------------
  initializeMsrFiguredBassOptions (
    boolOptionsInitialValue);

  // exit after some passes
  // --------------------------------------
  initializeMsrExitAfterSomePassesOptions (
    boolOptionsInitialValue);
}

S_msrOah msrOah::createCloneWithDetailedTrace ()
{
/* JMI
  S_msrOah
    clone =
      msrOah::create (0);
      // 0 not to have it inserted twice in the option handler

  // set the options handler upLink
  clone->fHandlerUpLink =
    fHandlerUpLink;


  // trace and display
  // --------------------------------------

  clone->fTraceMsr =
    true;

  clone->fTraceMsrVisitors =
    true;

  clone->fDisplayPartGroups =
    true;

  clone->fDisplayMsr =
    fDisplayMsr;
  clone->fDisplayMsrDetails =
    fDisplayMsrDetails;

  clone->fDisplayMsrNames =
    fDisplayMsrNames;
  clone->fDisplayMsrSummary =
    fDisplayMsrSummary;


  // languages
  // --------------------------------------

  clone->fMsrQuarterTonesPitchesLanguageKind =
    fMsrQuarterTonesPitchesLanguageKind;


  // parts
  // --------------------------------------

  clone->fPartsRenamingMap =
    fPartsRenamingMap;
  clone->fPartsTranspositionMap =
    fPartsTranspositionMap;


  // staves
  // --------------------------------------

  clone->fCreateSingleLineStavesAsRythmic =
    fCreateSingleLineStavesAsRythmic;


  // voices
  // --------------------------------------

  clone->fCreateVoicesStaffRelativeNumbers =
    fCreateVoicesStaffRelativeNumbers;


  // repeats
  // --------------------------------------

  clone->fCreateImplicitInitialRepeatBarline =
    fCreateImplicitInitialRepeatBarline;


  // notes
  // --------------------------------------

  clone->fDelayRestsDynamics =
    fDelayRestsDynamics;
  clone->fDelayRestsWords =
    fDelayRestsWords;
  clone->fDelayRestsSlurs =
    fDelayRestsSlurs;
  clone->fDelayRestsLigatures =
    fDelayRestsLigatures;
  clone->fDelayRestsPedals =
    fDelayRestsPedals;
  clone->fDelayRestsSlashes =
    fDelayRestsSlashes;
  clone->fDelayRestsWedges =
    fDelayRestsWedges;


  // lyrics
  // --------------------------------------

  clone->fAddStanzasNumbers =
    fAddStanzasNumbers;

  // harmonies
  // --------------------------------------

  clone->fShowHarmonyVoices =
    fShowHarmonyVoices;


  // figured bass
  // --------------------------------------

  clone->fShowFiguredBassVoices =
    fShowFiguredBassVoices;

  return clone;
  */
}

//______________________________________________________________________________
bool msrOah::setMsrQuarterTonesPitchesLanguage (string language)
{
  // is language in the pitches languages map?
  map<string, msrQuarterTonesPitchesLanguageKind>::const_iterator
    it =
      gQuarterTonesPitchesLanguageKindsMap.find (language);

  if (it == gQuarterTonesPitchesLanguageKindsMap.end ()) {
    // no, language is unknown in the map
    return false;
  }

  fMsrQuarterTonesPitchesLanguageKind = (*it).second;

  return true;
}

//______________________________________________________________________________
void msrOah::enforceQuietness ()
{
  fTraceMsr = false;
  fTraceMsrVisitors = false;
  fDisplayPartGroups = false;
  fDisplayMsr = false;
  fDisplayMsrDetails = false;
  fDisplayMsrNames = false;
  fDisplayMsrSummary = false;
}

//______________________________________________________________________________
void msrOah::checkOptionsConsistency ()
{
  // JMI
}

//______________________________________________________________________________
void msrOah::acceptIn (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrOah::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_msrOah>*
    p =
      dynamic_cast<visitor<S_msrOah>*> (v)) {
        S_msrOah elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrOah::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void msrOah::acceptOut (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrOah::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_msrOah>*
    p =
      dynamic_cast<visitor<S_msrOah>*> (v)) {
        S_msrOah elem = this;

#ifdef TRACE_OAH
        if (gExecutableOah->fTraceOahVisitors) {
          gLogOstream <<
            "% ==> Launching msrOah::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void msrOah::browseData (basevisitor* v)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOahVisitors) {
    gLogOstream <<
      "% ==> msrOah::browseData ()" <<
      endl;
  }
#endif
}

//______________________________________________________________________________
void msrOah::printMsrOahValues (int fieldWidth)
{
  gLogOstream <<
    "The MSR options are:" <<
    endl;

  gIndenter++;


  // trace and display
  // --------------------------------------

  gLogOstream <<
    "Trace and display:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "traceMsr" << " : " <<
    booleanAsString (fTraceMsr) <<
    endl <<

    setw (fieldWidth) << "traceMsrVisitors" << " : " <<
    booleanAsString (fTraceMsrVisitors) <<
    endl <<

    setw (fieldWidth) << "displayPartGroups" << " : " <<
    booleanAsString (fDisplayPartGroups) <<
    endl <<

    setw (fieldWidth) << "displayMsr" << " : " <<
    booleanAsString (fDisplayMsr) <<
    endl <<
    setw (fieldWidth) << "displayMsrDetails" << " : " <<
    booleanAsString (fDisplayMsrDetails) <<
    endl <<

    setw (fieldWidth) << "displayMsrNames" << " : " <<
    booleanAsString (fDisplayMsrNames) <<
    endl <<

    setw (fieldWidth) << "displayMsrSummary" << " : " <<
    booleanAsString (fDisplayMsrSummary) <<
    endl;

  gIndenter--;


  // languages
  // --------------------------------------

  gLogOstream <<
     "Languages:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "msrPitchesLanguage" << " : \"" <<
    msrQuarterTonesPitchesLanguageKindAsString (
      fMsrQuarterTonesPitchesLanguageKind) <<
      "\"" <<
    endl;

  gIndenter--;


  // parts
  // --------------------------------------

  gLogOstream <<
     "Parts:" <<
    endl;

  gIndenter++;

  // parts renaming

  gLogOstream << left <<
    setw (fieldWidth) << "parts renaming" << " : ";

  if (! fPartsRenamingMap.size ()) {
    gLogOstream <<
      "none";
  }

  else {
    for (
      map<string, string>::const_iterator i =
        fPartsRenamingMap.begin ();
      i != fPartsRenamingMap.end ();
      i++
  ) {
        gLogOstream <<
          "\"" << ((*i).first) << "\" -> \"" << ((*i).second) << "\"";
    } // for
  }

  gLogOstream << endl;

  // parts transposition

  gLogOstream << left <<
    setw (fieldWidth) << "parts transposition" << " : ";

  if (! fPartsTranspositionMap.size ()) {
    gLogOstream <<
      "none";
  }

  else {
    for (
      map<string, S_msrSemiTonesPitchAndOctave>::const_iterator i =
        fPartsTranspositionMap.begin ();
      i != fPartsTranspositionMap.end ();
      i++
  ) {
        gLogOstream <<
          "\"" << ((*i).first) <<
          " = " <<
          ((*i).second->asString ()) <<
          "\" ";
    } // for
  }

  gLogOstream << endl;

  gIndenter--;


  // staves
  // --------------------------------------

  gLogOstream <<
    "Staves:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) <<
    "createSingleLineStavesAsRythmic" << " : " <<
    booleanAsString (fCreateSingleLineStavesAsRythmic) <<
    endl;

  gIndenter--;


  // voices
  // --------------------------------------

  gLogOstream <<
    "Voices:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) <<
    "createVoicesStaffRelativeNumbers" << " : " <<
    booleanAsString (fCreateVoicesStaffRelativeNumbers) <<
    endl;

  gIndenter--;


  // repeats
  // --------------------------------------

  gLogOstream <<
    "Repeats:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) <<
    "createImplicitInitialRepeatBarline" << " : " <<
    booleanAsString (fCreateImplicitInitialRepeatBarline) <<
    endl;

  gIndenter--;


  // notes
  // --------------------------------------

  gLogOstream <<
     "Notes:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "delayRestsDynamics" << " : " <<
    booleanAsString (fDelayRestsDynamics) <<
    endl <<

    setw (fieldWidth) << "delayRestsWords" << " : " <<
    booleanAsString (fDelayRestsWords) <<
    endl <<

    setw (fieldWidth) << "delayRestsSlurs" << " : " <<
    booleanAsString (fDelayRestsSlurs) <<
    endl <<

    setw (fieldWidth) << "delayRestsLigatures" << " : " <<
    booleanAsString (fDelayRestsLigatures) <<
    endl <<

    setw (fieldWidth) << "delayRestsPedals" << " : " <<
    booleanAsString (fDelayRestsPedals) <<
    endl <<

    setw (fieldWidth) << "delayRestsSlashes" << " : " <<
    booleanAsString (fDelayRestsSlashes) <<
    endl <<

    setw (fieldWidth) << "delayRestsWedges" << " : " <<
    booleanAsString (fDelayRestsWedges) <<
    endl;

  gIndenter--;


  // lyrics
  // --------------------------------------

  gLogOstream <<
    "Lyrics:" <<
    endl;

  gIndenter++;

  gLogOstream <<
    setw (fieldWidth) << "addStanzasNumbers" << " : " <<
    booleanAsString (fAddStanzasNumbers) <<
    endl;

  gIndenter--;


  // harmonies
  // --------------------------------------

  gLogOstream <<
    "Harmonies:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "showHarmonyVoices" << " : " <<
    booleanAsString (fShowHarmonyVoices) <<
    endl;

  gIndenter--;


  // figured bass
  // --------------------------------------

  gLogOstream <<
    "Figured bass:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "showFiguredBassVoices" << " : " <<
    booleanAsString (fShowFiguredBassVoices) <<
    endl;

  gIndenter--;

  gIndenter--;


  // exit after some passes
  // --------------------------------------

  gLogOstream <<
    "Exit after some passes:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "exit2a" << " : " <<
    booleanAsString (fExit2a) <<
    endl <<
    setw (fieldWidth) << "exit2b" << " : " <<
    booleanAsString (fExit2b) <<
    endl;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_msrOah& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
void initializeMsrOahHandling (
  S_oahHandler handler)
{
#ifdef TRACE_OAH
  if (gExecutableOah->fTraceOah && ! gGeneralOah->fQuiet) {
    gLogOstream <<
      "Initializing MSR options handling" <<
      endl;
  }
#endif

  // MSR options
  // ------------------------------------------------------

  gMsrOahUserChoices = msrOah::create (
    handler);
  assert(gMsrOahUserChoices != 0);

  gMsrOah =
    gMsrOahUserChoices;

  // prepare for measure detailed trace
  // ------------------------------------------------------

/* JMI
  gMsrOahWithDetailedTrace =
    gMsrOah->
      createCloneWithDetailedTrace ();
      */
}


}
