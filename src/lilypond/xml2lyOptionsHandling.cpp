/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <sstream>

#include <climits>      // INT_MIN, INT_MAX
#include <iomanip>      // setw, setprecision, ...

#include "libmusicxml.h"

#include "xml2lyOptionsHandling.h"

#include "generalOptions.h"

#include "setTraceOptionsIfDesired.h"
#include "traceOptions.h"

#include "musicXMLOptions.h"
#include "msrOptions.h"
#include "lpsrOptions.h"
#include "lilypondOptions.h"

#include "extraOptions.h"

#include "version.h"
#include "msr.h"
#include "lpsr.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_xml2lyOptionsVersionAtom xml2lyOptionsVersionAtom::create (
  string shortName,
  string longName,
  string description)
{
  xml2lyOptionsVersionAtom* o = new
    xml2lyOptionsVersionAtom (
      shortName,
      longName,
      description);
  assert(o!=0);
  return o;
}

xml2lyOptionsVersionAtom::xml2lyOptionsVersionAtom (
  string shortName,
  string longName,
  string description)
  : oahAtom (
      shortName,
      longName,
      description)
{}

xml2lyOptionsVersionAtom::~xml2lyOptionsVersionAtom ()
{}

void xml2lyOptionsVersionAtom::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "xml2lyOptionsVersionAtom:" <<
    endl;

  gIndenter++;

  oahOption::printOptionEssentials (
    os, fieldWidth);

  gIndenter++;
  os <<
    gIndenter.indentMultiLineString (
      fDescription) <<
    endl;
  gIndenter--;

  gIndenter--;
}

void xml2lyOptionsVersionAtom::printVersion (ostream& os) const
{
  os <<
    endl <<
    "This is xml2ly" <<
    " version " << currentVersionNumber () <<
    endl <<
    endl;

  // print versions history
  printVersionsHistory (os);
}

void xml2lyOptionsVersionAtom::printOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  // nothing to print here
}

ostream& operator<< (ostream& os, const S_xml2lyOptionsVersionAtom& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_xml2lyOptionsAboutAtom xml2lyOptionsAboutAtom::create (
  string shortName,
  string longName,
  string description)
{
  xml2lyOptionsAboutAtom* o = new
    xml2lyOptionsAboutAtom (
      shortName,
      longName,
      description);
  assert(o!=0);
  return o;
}

xml2lyOptionsAboutAtom::xml2lyOptionsAboutAtom (
  string shortName,
  string longName,
  string description)
  : oahAtom (
      shortName,
      longName,
      description)
{}

xml2lyOptionsAboutAtom::~xml2lyOptionsAboutAtom ()
{}

void xml2lyOptionsAboutAtom::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "xml2lyOptionsAboutAtom:" <<
    endl;

  gIndenter++;

  oahOption::printOptionEssentials (
    os, fieldWidth);

  gIndenter++;
  os <<
    gIndenter.indentMultiLineString (
      fDescription) <<
    endl;
  gIndenter--;

  gIndenter--;
}

void xml2lyOptionsAboutAtom::printAbout (ostream& os) const
{
  os <<
    endl <<
R"(What xml2ly does:

    This multi-pass translator basically performs 5 passes:
        Pass 1:  reads the contents of MusicXMLFile or stdin ('-')
                 and converts it to a MusicXML tree;
        Pass 2a: converts that MusicXML tree into to
                 a Music Score Representation (MSR) skeleton;
        Pass 2b: converts that tree and the skeleton into a
                 Music Score Representation (MSR);
        Pass 3:  converts the MSR into a
                 LilyPond Score Representation (LPSR);
        Pass 4:  converts the LPSR to LilyPond source code
                 and writes it to standard output.

    Other passes are performed according to the options, such as
    printing views of the internal data or printing a summary of the score.

    The activity log and warning/error messages go to standard error.)" <<
    endl <<
    endl;
}

void xml2lyOptionsAboutAtom::printOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  // nothing to print here
}

ostream& operator<< (ostream& os, const S_xml2lyOptionsAboutAtom& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_xml2lyOptionsContactAtom xml2lyOptionsContactAtom::create (
  string shortName,
  string longName,
  string description)
{
  xml2lyOptionsContactAtom* o = new
    xml2lyOptionsContactAtom (
      shortName,
      longName,
      description);
  assert(o!=0);
  return o;
}

xml2lyOptionsContactAtom::xml2lyOptionsContactAtom (
  string shortName,
  string longName,
  string description)
  : oahAtom (
      shortName,
      longName,
      description)
{}

xml2lyOptionsContactAtom::~xml2lyOptionsContactAtom ()
{}

void xml2lyOptionsContactAtom::print (ostream& os) const
{
  const int fieldWidth = K_OPTIONS_FIELD_WIDTH;

  os <<
    "xml2lyOptionsContactAtom:" <<
    endl;

  gIndenter++;

  oahOption::printOptionEssentials (
    os, fieldWidth);

  gIndenter++;
  os <<
    gIndenter.indentMultiLineString (
      fDescription) <<
    endl;
  gIndenter--;

  gIndenter--;
}

void xml2lyOptionsContactAtom::printContact (ostream& os) const
{
  os <<
    endl <<
R"(To contact xml2ly maintainers:

    Send a mail to mailto:lilypond-user@gnu.org describing the problem
    and error messages you obtain if relevant.)" <<
    endl <<
    endl;
}

void xml2lyOptionsContactAtom::printOptionsValues (
  ostream& os,
  int      valueFieldWidth) const
{
  // nothing to print here
}

ostream& operator<< (ostream& os, const S_xml2lyOptionsContactAtom& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_xml2lyOptionsHandler xml2lyOptionsHandler::create (
  string           executableName,
  indentedOstream& ios)
{
  xml2lyOptionsHandler* o = new
    xml2lyOptionsHandler (
      executableName,
      ios);
  assert(o!=0);
  return o;
}

xml2lyOptionsHandler::xml2lyOptionsHandler (
  string           executableName,
  indentedOstream& ios)
  : oahHandler (
    "Available options",
    "Options values",
    "h", "help",
    "hs", "helpSummary",
R"(
                      Welcome to xml2ly,
              the MusicXML to LilyPond translator
          delivered as part of the libmusicxml2 library.
      https://github.com/grame-cncm/libmusicxml/tree/lilypond

Usage:
    xml2ly [options] [MusicXMLFile|-] [options]
)",
R"(
Option '-h, -help' prints the full help,
  while '-hs, -helpSummary' only prints a help summary.)",
    ios)
{
  initializeOptionsHandler (executableName);

  // append the help options prefixes
  S_oahPrefix
    helpPrefix =
      oahPrefix::create (
        "help",
        "help-",
        "'-help=abc,xywx-yz' is equivalent to '-help-abc, -help-xywx-yz'");
  appendPrefixToHandler (helpPrefix);

  S_oahPrefix
    hPrefix =
      oahPrefix::create (
        "h",
        "h",
        "'-h=abc,wxyz' is equivalent to '-habc, -hwxyz'");
  appendPrefixToHandler (hPrefix);

  // append the trace options prefixes
  S_oahPrefix
    tracePrefix =
      oahPrefix::create (
        "trace",
        "trace-",
        "'-trace=abc,xywx-yz' is equivalent to '-trace-abc, -trace-xywx-yz'");
  appendPrefixToHandler (tracePrefix);

  S_oahPrefix
    tPrefix =
      oahPrefix::create (
        "t",
        "t",
        "'-t=abc,wxyz' is equivalent to '-tabc, -twxyz'");
  appendPrefixToHandler (tPrefix);
}

xml2lyOptionsHandler::~xml2lyOptionsHandler ()
{}

void xml2lyOptionsHandler::initializeOptionsHandler (
  string executableName)
{
  // initialize options handling, phase 1
  // ------------------------------------------------------

#ifdef TRACE_OPTIONS
  initializeTraceOptionsHandling (
    this);
#endif

  initializeOahBasicOptionsHandling (
    executableName,
    this);

  initializeGeneralOptionsHandling (
    this);

  // initialize the library
  // ------------------------------------------------------

  initializeMSR ();
  initializeLPSR ();

  // initialize options handling, phase 2
  // ------------------------------------------------------

  initializeMusicXMLOptionsHandling (
    this);

  initializeMsrOptionsHandling (
    this);

  initializeLpsrOptionsHandling (
    this);

  initializeLilypondOptionsHandling (
    this);

#ifdef EXTRA_OPTIONS
  initializeExtraOptionsHandling (
    this);
#endif

  initializeXml2lyOptionsHandling (
    this);

#ifdef TRACE_OPTIONS
  if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
    // print the options handler initial state
    fHandlerLogOstream <<
      "xml2lyOptionsHandler has been initialized as:" <<
      endl;

    gIndenter++;

    print (
      fHandlerLogOstream);
    fHandlerLogOstream <<
      endl <<
      endl;

    gIndenter--;
  }
#endif

  // register options handler in itself,
  // so that the 'global' help options can be handled
  this->
    registerHandlerInItself ();

#ifdef TRACE_OPTIONS
  if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
    fHandlerLogOstream <<
      "xml2lyOptionsHandler help:" <<
      endl;

    this->
      printHelp (
        fHandlerLogOstream);
  }
#endif
}

void xml2lyOptionsHandler::checkOptionsAndArguments ()
{
  unsigned int argumentsNumber =
    fHandlerArgumentsVector.size ();

#ifdef TRACE_OPTIONS
  if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
    if (argumentsNumber > 0) {
      fHandlerLogOstream <<
        singularOrPluralWithoutNumber (
          argumentsNumber, "There is", "There are") <<
        " " <<
        argumentsNumber <<
        " " <<
        singularOrPluralWithoutNumber (
          argumentsNumber, "argument", "arguments") <<
        ":" <<
        endl;

      gIndenter++;

      for (unsigned int i = 0; i < argumentsNumber; i++) {
        fHandlerLogOstream <<
          i << " : " << fHandlerArgumentsVector [i] <<
            endl;
      } // for

      fHandlerLogOstream << endl;

      gIndenter--;
    }
    else {
      fHandlerLogOstream <<
        "There are no arguments to " <<
        gOahBasicOptions->fHandlerExecutableName <<
        endl;
    }
  }
#endif

  // input source name
  // ------------------------------------------------------

  switch (argumentsNumber) {
    case 0:
      fHandlerLogOstream <<
        endl <<
        "Input file name or '-' for standard input expected" <<
        endl <<
        endl;

      exit (1);
      break;

    case 1:
      // register intput file name
      gOahBasicOptions->fInputSourceName =
        fHandlerArgumentsVector [0];
      break;

    default:
      fHandlerLogOstream <<
        endl <<
        "Several input file name supplied, only the first one, \"" <<
        fHandlerArgumentsVector [0] <<
        "\", will be translated" <<
        endl <<
        endl;

      // register intput file name
      gOahBasicOptions->fInputSourceName =
        fHandlerArgumentsVector [0];
      break;
  } //  switch

  // build potential output file name
  // ------------------------------------------------------

  string potentialOutputFileName;

  if (gOahBasicOptions->fInputSourceName != "-") {
    // determine potential output file name,
    // may be set differently by '--ofn, --outputFileName' option
    potentialOutputFileName =
      baseName (
        gOahBasicOptions->fInputSourceName);

    // set '.ly' suffix
    size_t
      posInString =
        potentialOutputFileName.rfind ('.');

    if (posInString != string::npos) {
      potentialOutputFileName.replace (
        posInString,
        potentialOutputFileName.size () - posInString,
        ".ly");
    }
  }

  // check auto output file option usage
  // ------------------------------------------------------

  if (gXml2lyOptions->fAutoOutputFileName) {
    if (gXml2lyOptions->fOutputFileName.size ()) {
      stringstream s;

      s <<
        "options '-aofn, -auto-output-file-name' and '-o, -output-file-name'"  <<
        endl <<
        "cannot be chosen simultaneously";

      optionError (s.str ());

      exit (3);
    }

    else if (gOahBasicOptions->fInputSourceName == "-") {
      stringstream s;

      s <<
        "option '-aofn, -auto-output-file-name'"  <<
        endl <<
        "cannot be used when reading from standard input";

      optionError (s.str ());

      exit (4);
    }

    else {
      gXml2lyOptions->fOutputFileName =
        potentialOutputFileName;
    }
  }

  // register command line informations in gGeneralOptions
  // ------------------------------------------------------

/* JMI ???
  gGeneralOptions->fCommandLineWithShortOptions =
    fCommandLineWithShortOptions;
  gGeneralOptions->fCommandLineWithShortOptions =
    fCommandLineWithShortOptions;
    */
}

//______________________________________________________________________________
void xml2lyOptionsHandler::enforceOptionsHandlerQuietness ()
{
#ifdef TRACE_OPTIONS
  gGeneralOptions->
    enforceQuietness ();
#endif

  gGeneralOptions->
    enforceQuietness ();

  gMusicXMLOptions->
    enforceQuietness ();

  gMsrOptions->
    enforceQuietness ();

  gLpsrOptions->
    enforceQuietness ();

  gLilypondOptions->
    enforceQuietness ();

#ifdef EXTRA_OPTIONS
  gExtraOptions->
    enforceQuietness ();
#endif

  gXml2lyOptions->
    enforceQuietness ();
}

//______________________________________________________________________________
void xml2lyOptions::enforceQuietness ()
{}

//______________________________________________________________________________
void xml2lyOptions::checkOptionsConsistency ()
{
  gLogOstream <<
    "xml2lyOptions::checkOptionsConsistency ()" <<
    endl;

#ifdef TRACE_OPTIONS
  gGeneralOptions->
    checkOptionsConsistency ();
#endif
  gGeneralOptions->
    checkOptionsConsistency ();

  gMusicXMLOptions->
    checkOptionsConsistency ();

  gMsrOptions->
    checkOptionsConsistency ();

  gLpsrOptions->
    checkOptionsConsistency ();

  gLilypondOptions->
    checkOptionsConsistency ();

#ifdef EXTRA_OPTIONS
  gExtraOptions->
    checkOptionsConsistency ();
#endif

/* JMI TICINO
  gXml2lyOptions->
    checkOptionsConsistency ();
    */
}

//______________________________________________________________________________
void xml2lyOptionsHandler::print (ostream& os) const
{
  const int fieldWidth = 27;

  os <<
    "xml2lyOptionsHandler:" <<
    endl;

  gIndenter++;

  os << left <<
    setw (fieldWidth) <<
    "fShortName" << " : " << fShortName <<
    endl <<
    setw (fieldWidth) <<
    "fLongName" << " : " << fLongName <<
    endl <<
    setw (fieldWidth) <<
    "fDescription" << " : " << fDescription <<
    endl <<
    endl;

  os <<
    "Options groups (" <<
    singularOrPlural (
      fHandlerGroupsList.size (), "element",  "elements") <<
    "):" <<
    endl;

  if (fHandlerGroupsList.size ()) {
    os << endl;

    gIndenter++;

    list<S_oahGroup>::const_iterator
      iBegin = fHandlerGroupsList.begin (),
      iEnd   = fHandlerGroupsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      // print the element
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for

    gIndenter--;
  }

  gIndenter--;

  os << endl;
}

ostream& operator<< (ostream& os, const S_xml2lyOptionsHandler& elt)
{
  elt->print (os);
  return os;
}

//_______________________________________________________________________________
S_xml2lyOptions gXml2lyOptions;

S_xml2lyOptions xml2lyOptions::create (
  S_oahHandler handler)
{
  xml2lyOptions* o = new xml2lyOptions (
    handler);
  assert(o!=0);

  return o;
}

xml2lyOptions::xml2lyOptions (
  S_oahHandler handler)
  : oahGroup (
    "xml2ly",
    "hxl", "help-xml2ly",
R"(Options that are used by xml2ly are grouped here.)",
    kElementVisibilityAlways,
    handler)
{
  // append this options group to the options handler
  // if relevant
  if (handler) {
    handler->
      appendGroupToHandler (this);
  }

  // initialize it
  initializeXml2lyOptions ();
}

xml2lyOptions::~xml2lyOptions ()
{}

void xml2lyOptions::initializeXml2lyOptions ()
{
  // version
  // --------------------------------------

  {
    S_oahSubGroup
      versionSubGroup =
        oahSubGroup::create (
          "Version",
          "hxv", "help-xml2ly-version",
R"()",
        kElementVisibilityAlways,
        this);

    appendSubGroup (versionSubGroup);

    // version

    versionSubGroup->
      appendAtom (
        xml2lyOptionsVersionAtom::create (
          "v", "version",
R"(Display xml2ly's version number and history and exit.)"));
  }


  // about
  // --------------------------------------

  {
    S_oahSubGroup
      aboutSubGroup =
        oahSubGroup::create (
          "About",
          "hxa", "help-xml2ly-about",
R"()",
        kElementVisibilityAlways,
        this);

    appendSubGroup (aboutSubGroup);

    // about

    aboutSubGroup->
      appendAtom (
        xml2lyOptionsAboutAtom::create (
          "a", "about",
R"(Display information about xml2ly and exit.)"));
  }


  // contact
  // --------------------------------------

  {
    S_oahSubGroup
      contactSubGroup =
        oahSubGroup::create (
          "Contact",
          "hxc", "help-xml2ly-contact",
R"()",
        kElementVisibilityAlways,
        this);

    appendSubGroup (contactSubGroup);

    // contact

    contactSubGroup->
      appendAtom (
        xml2lyOptionsContactAtom::create (
          "c", "contact",
R"(Display information about how to contacct xml2ly maintainers and exit.)"));
  }


  // output file
  // --------------------------------------

  {
    S_oahSubGroup
      outputFileSubGroup =
        oahSubGroup::create (
          "Output file",
          "hxof", "help-xml2ly-output-file",
R"()",
        kElementVisibilityAlways,
        this);

    appendSubGroup (outputFileSubGroup);

    // output filename

    outputFileSubGroup->
      appendAtom (
        oahStringAtom::create (
          "o", "output-file-name",
R"(Write LilyPond code to file FILENAME instead of standard output.)",
          "FILENAME",
          "outputFileName",
          fOutputFileName));

    // auto output filename

    fAutoOutputFileName = false;

    outputFileSubGroup->
      appendAtom (
        oahBooleanAtom::create (
          "aofn", "auto-output-file-name",
R"(This option can only be used when reading from a file.
Write LilyPond code to a file in the current working directory.
The file name is derived from that of the input file,
replacing any suffix after the the '.' by 'ly'
or adding '.ly' if none is present.)",
          "autoOutputFileName",
          fAutoOutputFileName));
  }
}

void xml2lyOptions::printXml2lyOptionsValues (int fieldWidth)
{
  gLogOstream <<
    "The xml2ly options are:" <<
    endl;

  gIndenter++;

  // output file
  // --------------------------------------

  gLogOstream << left <<
    setw (fieldWidth) << "Output file:" <<
    endl;

  gIndenter++;

  gLogOstream << left <<
    setw (fieldWidth) << "outputFileName" << " : \"" <<
    fOutputFileName <<
    "\"" <<
    endl;

  gIndenter--;
}

S_oahValuedAtom xml2lyOptions::handleAtom (
  ostream&  os,
  S_oahAtom atom)
{
  S_oahValuedAtom result;

#ifdef TRACE_OPTIONS
  if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
    os <<
      "---> Handling options atom '" <<
      atom <<
      "'" <<
      endl;
  }
#endif

  if (
    // version atom?
    S_xml2lyOptionsVersionAtom
      versionAtom =
        dynamic_cast<xml2lyOptionsVersionAtom*>(&(*atom))
    ) {
#ifdef TRACE_OPTIONS
    if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
      os <<
        "==> oahAtom is of type 'optionsVersionAtom'" <<
        endl;
    }
#endif

    // handle it at once
    versionAtom->
      printVersion (os);

    // exit
    exit (0);
  }

  else if (
    // about atom?
    S_xml2lyOptionsAboutAtom
      aboutAtom =
        dynamic_cast<xml2lyOptionsAboutAtom*>(&(*atom))
    ) {
#ifdef TRACE_OPTIONS
    if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
      os <<
        "==> oahAtom is of type 'optionsAboutAtom'" <<
        endl;
    }
#endif

    // handle it at once
    aboutAtom->
      printAbout (os);

    // exit
    exit (0);
  }

  else if (
    // contact atom?
    S_xml2lyOptionsContactAtom
      contactAtom =
        dynamic_cast<xml2lyOptionsContactAtom*>(&(*atom))
    ) {
#ifdef TRACE_OPTIONS
    if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
      os <<
        "==> oahAtom is of type 'optionsContactAtom'" <<
        endl;
    }
#endif

    // handle it at once
    contactAtom->
      printContact (os);

    // exit
    exit (0);
  }

  return result;
}

//______________________________________________________________________________
void initializeXml2lyOptionsHandling (
  S_oahHandler handler)
{
#ifdef TRACE_OPTIONS
  if (gOahBasicOptions->fTraceOptions && ! gGeneralOptions->fQuiet) {
    gLogOstream <<
      "Initializing xml2ly options handling" <<
      endl;
  }
#endif

  // enlist versions information
  // ------------------------------------------------------

  enlistVersion (
    "Initial", "early 2016",
    "Start as xml2lilypond, a clone of xml2guido");

  enlistVersion (
    musicxml2lilypondVersionStr (), "October 2018",
    "First draft version");

  // create the options variables
  // ------------------------------------------------------

  gXml2lyOptions = xml2lyOptions::create (
    handler);
  assert (gXml2lyOptions != 0);
}


}
