#include "packagejson.hpp"
#include "rapidjson/document.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using std::string;

bool packageJson::validate::name(string name) {
  return std::regex_match(
      name.c_str(),
      std::regex("^(@[a-z0-9-~][a-z0-9-._~]*\\/)?[a-z0-9-~][a-z0-9-._~]*$"));
}

bool packageJson::validate::semver(string version) {
  return std::regex_match(
      version.c_str(),
      std::regex(
          "^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:-((?:0|[1-9]\\d*|"
          "\\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\\.(?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-"
          "zA-Z-]*))*))?(?:\\+([0-9a-zA-Z-]+(?:\\.[0-9a-zA-Z-]+)*))?$"));
}

bool packageJson::validate::license(string license) {
  // SPDX
  string licenses[] = {"LPL-1.02",
                       "DOC",
                       "GFDL-1.1-only",
                       "OFL-1.1-RFN",
                       "APAFML",
                       "Unlicense",
                       "LiLiQ-P-1.1",
                       "iMatix",
                       "D-FSL-1.0",
                       "GFDL-1.1-no-invariants-or-later",
                       "CECILL-1.0",
                       "Zed",
                       "RHeCos-1.1",
                       "eGenix",
                       "Glulxe",
                       "bzip2-1.0.5",
                       "GPL-3.0-only",
                       "xinetd",
                       "Qhull",
                       "UCL-1.0",
                       "Dotseqn",
                       "CC-BY-1.0",
                       "psutils",
                       "MulanPSL-2.0",
                       "NIST-PD-fallback",
                       "DSDP",
                       "OGL-UK-1.0",
                       "XFree86-1.1",
                       "CC-BY-NC-ND-3.0",
                       "xpp",
                       "LAL-1.3",
                       "Bitstream-Vera",
                       "Zend-2.0",
                       "CC-BY-NC-SA-1.0",
                       "GFDL-1.1-no-invariants-only",
                       "mpi-permissive",
                       "OPL-1.0",
                       "bzip2-1.0.6",
                       "CECILL-1.1",
                       "TCP-wrappers",
                       "OLDAP-2.0.1",
                       "ErlPL-1.1",
                       "CC-BY-3.0-US",
                       "JasPer-2.0",
                       "MIT-advertising",
                       "CC-BY-NC-SA-3.0",
                       "QPL-1.0",
                       "SWL",
                       "Wsuipa",
                       "CC-BY-2.5-AU",
                       "NPL-1.1",
                       "SugarCRM-1.1.3",
                       "LiLiQ-R-1.1",
                       "Hippocratic-2.1",
                       "XSkat",
                       "MIT-feh",
                       "CC-BY-NC-1.0",
                       "LGPL-2.0-only",
                       "GFDL-1.1-invariants-only",
                       "SGI-B-2.0",
                       "curl",
                       "VOSTROM",
                       "MITNFA",
                       "Mup",
                       "OGC-1.0",
                       "LGPL-3.0-only",
                       "Newsletr",
                       "libselinux-1.0",
                       "SMPPL",
                       "RPL-1.5",
                       "CC-BY-3.0-IGO",
                       "Jam",
                       "ANTLR-PD-fallback",
                       "OFL-1.1-no-RFN",
                       "AMDPLPA",
                       "PDDL-1.0",
                       "Beerware",
                       "Unicode-DFS-2015",
                       "AGPL-1.0",
                       "Eurosym",
                       "Aladdin",
                       "Baekmuk",
                       "BSD-2-Clause-FreeBSD",
                       "MPL-1.1",
                       "MIT-CMU",
                       "SimPL-2.0",
                       "Latex2e",
                       "Intel-ACPI",
                       "BSD-3-Clause-Modification",
                       "O-UDA-1.0",
                       "GFDL-1.3",
                       "CERN-OHL-W-2.0",
                       "CERN-OHL-1.2",
                       "SSPL-1.0",
                       "Plexus",
                       "W3C-20150513",
                       "GFDL-1.1-or-later",
                       "GFDL-1.3-invariants-or-later",
                       "PolyForm-Noncommercial-1.0.0",
                       "OGTSL",
                       "CC-BY-ND-2.5",
                       "Net-SNMP",
                       "SHL-0.5",
                       "TU-Berlin-1.0",
                       "Leptonica",
                       "OpenSSL",
                       "PostgreSQL",
                       "Community-Spec-1.0",
                       "MPL-2.0-no-copyleft-exception",
                       "CDLA-Permissive-2.0",
                       "CC-BY-NC-SA-2.0",
                       "BSD-3-Clause-Attribution",
                       "Watcom-1.0",
                       "NLOD-2.0",
                       "SGI-B-1.1",
                       "eCos-2.0",
                       "ODC-By-1.0",
                       "CECILL-C",
                       "OGL-UK-2.0",
                       "IBM-pibs",
                       "NICTA-1.0",
                       "CC-BY-ND-3.0-DE",
                       "CATOSL-1.1",
                       "Caldera",
                       "wxWindows",
                       "Fair",
                       "PHP-3.01",
                       "CC-BY-NC-2.5",
                       "UPL-1.0",
                       "CC-PDDC",
                       "Borceux",
                       "SNIA",
                       "Info-ZIP",
                       "ECL-2.0",
                       "dvipdfm",
                       "Cube",
                       "CERN-OHL-P-2.0",
                       "OFL-1.0",
                       "ZPL-2.0",
                       "LGPL-2.1-or-later",
                       "NCGL-UK-2.0",
                       "MIT",
                       "NIST-PD",
                       "HPND-sell-variant",
                       "CECILL-2.0",
                       "LPPL-1.3c",
                       "Glide",
                       "CC-BY-3.0-AT",
                       "MS-LPL",
                       "Arphic-1999",
                       "GD",
                       "OLDAP-2.7",
                       "JSON",
                       "CC-BY-SA-3.0-AT",
                       "CDLA-Permissive-1.0",
                       "Vim",
                       "Barr",
                       "PolyForm-Small-Business-1.0.0",
                       "TU-Berlin-2.0",
                       "CPAL-1.0",
                       "CC-BY-SA-1.0",
                       "OPUBL-1.0",
                       "NLPL",
                       "HPND",
                       "Saxpath",
                       "BUSL-1.1",
                       "GPL-2.0+",
                       "Imlib2",
                       "Parity-7.0.0",
                       "CrystalStacker",
                       "TCL",
                       "diffmark",
                       "CC-BY-NC-3.0-DE",
                       "ADSL",
                       "OLDAP-2.4",
                       "Zimbra-1.4",
                       "GFDL-1.3-no-invariants-only",
                       "IPA",
                       "Rdisc",
                       "NTP",
                       "AGPL-3.0",
                       "WTFPL",
                       "TORQUE-1.1",
                       "GPL-2.0-with-autoconf-exception",
                       "BSD-2-Clause-Views",
                       "OLDAP-2.5",
                       "BSD-1-Clause",
                       "CC-BY-ND-2.0",
                       "LGPL-2.0+",
                       "EFL-1.0",
                       "BSD-4-Clause-Shortened",
                       "CC0-1.0",
                       "OGL-UK-3.0",
                       "Elastic-2.0",
                       "MTLL",
                       "LGPL-3.0-or-later",
                       "OGL-Canada-2.0",
                       "Unicode-TOU",
                       "copyleft-next-0.3.1",
                       "FTL",
                       "NGPL",
                       "CC-BY-NC-ND-1.0",
                       "Apache-1.1",
                       "BSL-1.0",
                       "AML",
                       "SCEA",
                       "GFDL-1.3-invariants-only",
                       "EPL-1.0",
                       "LAL-1.2",
                       "APSL-1.2",
                       "MPL-1.0",
                       "IJG",
                       "C-UDA-1.0",
                       "Artistic-1.0",
                       "GFDL-1.3-only",
                       "Multics",
                       "CC-BY-NC-ND-3.0-IGO",
                       "NRL",
                       "LPPL-1.3a",
                       "CC-BY-ND-1.0",
                       "SchemeReport",
                       "checkmk",
                       "NPL-1.0",
                       "ODbL-1.0",
                       "LGPLLR",
                       "CC-BY-NC-ND-2.5",
                       "GPL-2.0-with-font-exception",
                       "Artistic-1.0-cl8",
                       "FreeBSD-DOC",
                       "NCSA",
                       "gSOAP-1.3b",
                       "LiLiQ-Rplus-1.1",
                       "EUPL-1.0",
                       "Naumen",
                       "CNRI-Jython",
                       "MulanPSL-1.0",
                       "BSD-2-Clause-Patent",
                       "Condor-1.1",
                       "Apache-1.0",
                       "LPPL-1.1",
                       "copyleft-next-0.3.0",
                       "CC-BY-SA-2.5",
                       "FSFULLR",
                       "Adobe-2006",
                       "APSL-1.0",
                       "AFL-1.1",
                       "Adobe-Glyph",
                       "LGPL-3.0",
                       "libutil-David-Nugent",
                       "CECILL-B",
                       "AMPAS",
                       "SAX-PD",
                       "OFL-1.0-RFN",
                       "Python-2.0",
                       "CC-BY-NC-SA-4.0",
                       "psfrag",
                       "BSD-3-Clause-No-Nuclear-License-2014",
                       "SISSL-1.2",
                       "LGPL-3.0+",
                       "Sleepycat",
                       "OCCT-PL",
                       "Sendmail-8.23",
                       "RPL-1.1",
                       "CNRI-Python-GPL-Compatible",
                       "YPL-1.0",
                       "PHP-3.0",
                       "BSD-Source-Code",
                       "MS-RL",
                       "Crossword",
                       "CDL-1.0",
                       "BSD-3-Clause-No-Military-License",
                       "EPICS",
                       "PSF-2.0",
                       "W3C-19980720",
                       "NTP-0",
                       "GPL-1.0-or-later",
                       "Ruby",
                       "Zimbra-1.3",
                       "ZPL-2.1",
                       "OLDAP-2.2.2",
                       "0BSD",
                       "Sendmail",
                       "CC-BY-NC-SA-3.0-DE",
                       "GPL-2.0",
                       "GFDL-1.1-invariants-or-later",
                       "CC-BY-SA-2.0-UK",
                       "EUPL-1.2",
                       "LGPL-2.0-or-later",
                       "OGDL-Taiwan-1.0",
                       "gnuplot",
                       "SISSL",
                       "NOSL",
                       "LPL-1.0",
                       "MS-PL",
                       "OSET-PL-2.1",
                       "GPL-2.0-with-classpath-exception",
                       "FDK-AAC",
                       "GL2PS",
                       "OML",
                       "GPL-1.0-only",
                       "OFL-1.1",
                       "SGI-B-1.0",
                       "CERN-OHL-1.1",
                       "BSD-3-Clause",
                       "NetCDF",
                       "CC-BY-SA-2.0",
                       "AGPL-3.0-or-later",
                       "CC-BY-SA-4.0",
                       "SSH-short",
                       "CC-BY-4.0",
                       "Afmparse",
                       "CC-BY-NC-SA-2.0-UK",
                       "X11",
                       "CC-BY-3.0-NL",
                       "zlib-acknowledgement",
                       "Frameworx-1.0",
                       "GPL-2.0-with-bison-exception",
                       "SHL-0.51",
                       "GPL-2.0-only",
                       "GPL-3.0-with-GCC-exception",
                       "LGPL-2.0",
                       "GPL-3.0-or-later",
                       "libpng-2.0",
                       "ISC",
                       "YPL-1.1",
                       "OSL-1.1",
                       "ANTLR-PD",
                       "FSFUL",
                       "GFDL-1.2",
                       "Python-2.0.1",
                       "CC-BY-ND-3.0",
                       "MPL-2.0",
                       "GFDL-1.2-or-later",
                       "Parity-6.0.0",
                       "App-s2p",
                       "mplus",
                       "Giftware",
                       "CC-BY-NC-SA-3.0-IGO",
                       "OLDAP-2.3",
                       "W3C",
                       "AAL",
                       "CUA-OPL-1.0",
                       "CERN-OHL-S-2.0",
                       "CDLA-Sharing-1.0",
                       "BSD-4-Clause-UC",
                       "DRL-1.0",
                       "CNRI-Python",
                       "Apache-2.0",
                       "libtiff",
                       "CC-BY-SA-3.0-DE",
                       "AGPL-1.0-only",
                       "CDDL-1.1",
                       "X11-distribute-modifications-variant",
                       "OLDAP-2.2.1",
                       "CC-BY-NC-SA-2.5",
                       "CC-BY-NC-2.0",
                       "MakeIndex",
                       "GPL-3.0-with-autoconf-exception",
                       "AFL-2.1",
                       "CDDL-1.0",
                       "AGPL-1.0-or-later",
                       "GFDL-1.2-no-invariants-only",
                       "CC-BY-SA-2.1-JP",
                       "etalab-2.0",
                       "BSD-Protection",
                       "DL-DE-BY-2.0",
                       "OLDAP-1.1",
                       "SSH-OpenSSH",
                       "FSFAP",
                       "CC-BY-NC-ND-4.0",
                       "LZMA-SDK-9.11-to-9.20",
                       "LGPL-2.1-only",
                       "CC-BY-2.5",
                       "NBPL-1.0",
                       "ICU",
                       "ECL-1.0",
                       "GPL-3.0+",
                       "FreeImage",
                       "Nokia",
                       "GFDL-1.2-only",
                       "NASA-1.3",
                       "GFDL-1.2-invariants-or-later",
                       "CC-BY-NC-SA-2.0-FR",
                       "CC-BY-2.0",
                       "VSL-1.0",
                       "CC-BY-SA-3.0",
                       "Motosoto",
                       "GFDL-1.2-no-invariants-or-later",
                       "OLDAP-1.2",
                       "OSL-2.0",
                       "ClArtistic",
                       "MirOS",
                       "GPL-2.0-or-later",
                       "BitTorrent-1.1",
                       "CC-BY-3.0",
                       "Intel",
                       "GLWTPL",
                       "ZPL-1.1",
                       "RSA-MD",
                       "Linux-OpenIB",
                       "SPL-1.0",
                       "MIT-enna",
                       "GPL-1.0",
                       "Linux-man-pages-copyleft",
                       "AGPL-3.0-only",
                       "OSL-2.1",
                       "CPOL-1.02",
                       "ImageMagick",
                       "BSD-2-Clause",
                       "Xerox",
                       "EUPL-1.1",
                       "LGPL-2.1+",
                       "NLOD-1.0",
                       "OLDAP-2.2",
                       "OLDAP-2.0",
                       "CC-BY-NC-ND-3.0-DE",
                       "EFL-2.0",
                       "Bahyph",
                       "Abstyles",
                       "EUDatagrid",
                       "GFDL-1.3-no-invariants-or-later",
                       "mpich2",
                       "RPSL-1.0",
                       "CECILL-2.1",
                       "LPPL-1.2",
                       "APSL-1.1",
                       "CC-BY-3.0-DE",
                       "HTMLTIDY",
                       "Noweb",
                       "CAL-1.0-Combined-Work-Exception",
                       "GPL-1.0+",
                       "RSCPL",
                       "CPL-1.0",
                       "blessing",
                       "EPL-2.0",
                       "BSD-3-Clause-Open-MPI",
                       "OCLC-2.0",
                       "HaskellReport",
                       "GFDL-1.1",
                       "Xnet",
                       "OLDAP-2.8",
                       "Nunit",
                       "BitTorrent-1.0",
                       "CC-BY-NC-4.0",
                       "AFL-3.0",
                       "OLDAP-2.6",
                       "Libpng",
                       "AFL-1.2",
                       "FSFULLRWD",
                       "LZMA-SDK-9.22",
                       "Knuth-CTAN",
                       "APSL-2.0",
                       "Artistic-2.0",
                       "Spencer-99",
                       "SMLNJ",
                       "OFL-1.0-no-RFN",
                       "CC-BY-NC-ND-2.0",
                       "Zlib",
                       "GPL-3.0",
                       "Artistic-1.0-Perl",
                       "OLDAP-1.3",
                       "Unicode-DFS-2016",
                       "LPPL-1.0",
                       "GFDL-1.2-invariants-only",
                       "BSD-2-Clause-NetBSD",
                       "TAPR-OHL-1.0",
                       "BSD-3-Clause-No-Nuclear-License",
                       "CC-BY-ND-4.0",
                       "Entessa",
                       "TMate",
                       "Spencer-86",
                       "NAIST-2003",
                       "BSD-3-Clause-No-Nuclear-Warranty",
                       "GPL-2.0-with-GCC-exception",
                       "OSL-3.0",
                       "MIT-Modern-Variant",
                       "AFL-2.0",
                       "OLDAP-1.4",
                       "OSL-1.0",
                       "OLDAP-2.1",
                       "IPL-1.0",
                       "MIT-open-group",
                       "Spencer-94",
                       "APL-1.0",
                       "TOSL",
                       "BlueOak-1.0.0",
                       "GFDL-1.3-or-later",
                       "MIT-0",
                       "JPNIC",
                       "BSD-3-Clause-LBNL",
                       "BSD-3-Clause-Clear",
                       "CC-BY-NC-3.0",
                       "COIL-1.0",
                       "NPOSL-3.0",
                       "Interbase-1.0",
                       "Minpack",
                       "LGPL-2.1",
                       "StandardML-NJ",
                       "BSD-4-Clause",
                       "CAL-1.0"};

  // Multiple
  std::regex multipleRegex("\\(([A-Za-z0-9\\.-]+) OR ([A-Za-z0-9\\.-]+)\\)");
  std::smatch multipleMatches;
  bool isMultiple = false;
  if (std::regex_search(license, multipleMatches, multipleRegex)) {
    for (int i = 1; i < multipleMatches.size(); i++) {
      bool matchSpdx = false;
      // Is the license SPDX
      for (int j = 0; j < 500; j++) {
        if (licenses[j] == multipleMatches[i].str()) {
          matchSpdx = true;
          std::cout << "matched";
          break;
        }
      }
      if (!matchSpdx) {
        isMultiple = false;
        break;
      } else
        isMultiple = true;
    }
  }
  if (isMultiple)
    return true;

  // Is the license SPDX
  bool matchSpdx = false;
  for (int i = 0; i < 500; i++) {
    if (licenses[i] == license) {
      matchSpdx = true;
      break;
    }
  }
  if (matchSpdx)
    return true;

  // Is it unlicensed
  if (license == "UNLICENSED")
    return true;

  // Otherwise, is it in a file
  return std::regex_match(license.c_str(),
                          std::regex("SEE LICENSE IN [A-Za-z0-9-_\\. ]+"));
}
