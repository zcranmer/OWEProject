/*
* LEGAL NOTICE
* This computer software was prepared by Battelle Memorial Institute,
* hereinafter the Contractor, under Contract No. DE-AC05-76RL0 1830
* with the Department of Energy (DOE). NEITHER THE GOVERNMENT NOR THE
* CONTRACTOR MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY
* LIABILITY FOR THE USE OF THIS SOFTWARE. This notice including this
* sentence must appear on any copies of this computer software.
* 
* EXPORT CONTROL
* User agrees that the Software will not be shipped, transferred or
* exported into any country or used in any manner prohibited by the
* United States Export Administration Act or any other applicable
* export laws, restrictions or regulations (collectively the "Export Laws").
* Export of the Software may require some form of license or other
* authority from the U.S. Government, and failure to obtain such
* export control license may result in criminal liability under
* U.S. laws. In addition, if the Software is identified as export controlled
* items under the Export Laws, User represents and warrants that User
* is not a citizen, or otherwise located within, an embargoed nation
* (including without limitation Iran, Syria, Sudan, Cuba, and North Korea)
*     and that User is not otherwise prohibited
* under the Export Laws from receiving the Software.
* 
* Copyright 2011 Battelle Memorial Institute.  All Rights Reserved.
* Distributed as open-source under the terms of the Educational Community 
* License version 2.0 (ECL 2.0). http://www.opensource.org/licenses/ecl2.php
* 
* For further details, see: http://www.globalchange.umd.edu/models/gcam/
*
*/

/*! 
* \file absolute_cost_logit.cpp
* \ingroup objects
* \brief AbsoluteCostLogit class source file
* \author Robert Link
*/

#include "util/base/include/definitions.h"
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <string>
#include <numeric>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>


#include "functions/include/absolute_cost_logit.hpp"
#include "util/base/include/xml_helper.h"
#include "util/logger/include/ilogger.h"

using namespace std;
using namespace xercesc;

//! constructor: arg values <= 0 (including default) will get filled in with the default
AbsoluteCostLogit::AbsoluteCostLogit():
mLogitExponent( 1 ),
mBaseCost( 0 ),
mParsedBaseCost( false )
{
}

//! destructor: nothing to clean up
AbsoluteCostLogit::~AbsoluteCostLogit() {
}

const string& AbsoluteCostLogit::getXMLNameStatic() {
    const static string XML_NAME = "absolute-cost-logit";
    return XML_NAME;
}

bool AbsoluteCostLogit::XMLParse( const DOMNode *aNode ) {
    /*! \pre Make sure we were passed a valid node. */
    assert( aNode );

    const Modeltime* modeltime = scenario->getModeltime();

    // get the children of the node
    DOMNodeList* nodeList = aNode->getChildNodes();

    bool parsingSuccessful = true;

    // loop over the child nodes
    for( unsigned int i = 0; i < nodeList->getLength(); ++i ) {
        DOMNode* curr = nodeList->item( i );
        string nodeName = XMLHelper<string>::safeTranscode( curr->getNodeName() );

        if( nodeName == XMLHelper<void>::text() ) {
            continue;
        }
        else if( nodeName == "logit-exponent" ) {
            double value = XMLHelper<double>::getValue( curr );
            if( value > 0 ) {
                ILogger& mainlog = ILogger::getLogger( "main_log" );
                mainlog.setLevel( ILogger::WARNING );
                mainlog << "Skipping invalid value for logit exponent: " << value
                        << " while parsing " << getXMLNameStatic() << "."
                        << endl;
                parsingSuccessful = false;
            }
            else {
                XMLHelper<double>::insertValueIntoVector( curr, mLogitExponent, modeltime );
            }
        }
        else if( nodeName == "base-cost" ) {
            double value = XMLHelper<double>::getValue( curr );
            if( value <= 0 ) {
                ILogger& mainlog = ILogger::getLogger( "main_log" );
                mainlog.setLevel( ILogger::WARNING );
                mainlog << "Ignoring invalid value for base cost: " << value
                        << " while parsing " << getXMLNameStatic() << "." << endl;
                parsingSuccessful = false;
                // skip the rest of the loop.  Don't set base cost.
                continue;
            }
            else if( value < 1.0e-2 ) {
                ILogger& mainlog = ILogger::getLogger( "main_log" );
                mainlog.setLevel( ILogger::WARNING );
                mainlog << "Parsed value for base cost:  " << value
                        << " is very low.  This may produce questionable results."
                        << endl;
                // fall through to set base cost to the input value.
            }
            mBaseCost = value;
            mParsedBaseCost = true;
        }
        else {
            ILogger& mainlog = ILogger::getLogger( "main_log" );
            mainlog.setLevel( ILogger::WARNING );
            mainlog << "Unknown text string: " << nodeName
                    << " found while parsing " << getXMLNameStatic() << "."
                    << endl;
            parsingSuccessful = false;
        }
    }

    return parsingSuccessful;
}

void AbsoluteCostLogit::toInputXML( ostream& aOut, Tabs* aTabs ) const {
    const Modeltime* modeltime = scenario->getModeltime();

    XMLWriteOpeningTag( getXMLNameStatic(), aOut, aTabs );
    XMLWriteVector( mLogitExponent, "logit-exponent", aOut, aTabs, modeltime );
    if( mParsedBaseCost ) {
        XMLWriteElement( mBaseCost, "base-cost", aOut, aTabs );
    }
    XMLWriteClosingTag( getXMLNameStatic(), aOut, aTabs );
}


void AbsoluteCostLogit::toDebugXML( const int aPeriod, ostream& aOut, Tabs* aTabs ) const {
    XMLWriteOpeningTag( getXMLNameStatic(), aOut, aTabs );
    XMLWriteElement( mLogitExponent[ aPeriod ], "logit-exponent", aOut, aTabs );
    XMLWriteElement( mBaseCost, "base-cost", aOut, aTabs );
    XMLWriteElement( mParsedBaseCost, "parsed-base-cost", aOut, aTabs );
    XMLWriteClosingTag( getXMLNameStatic(), aOut, aTabs );
}

/*!
 * \brief Absolute cost logit discrete choice function.
 * \details Calculate the log of the numerator of the discrete choice (i.e., the unnormalized version) 
 *          function being used to calculate subsector shares in this sector.  The normalization 
 *          factor will be calculated later.
 * \param aShareWeight share weight for the choice for which the share is being calculated.
 * \param aCost cost for the choice for which the share is being calculated.
 * \param aPeriod model time period for the calculation.
 * \return log of the unnormalized share.
 */
double AbsoluteCostLogit::calcUnnormalizedShare( const double aShareWeight, const double aCost,
                                                 const int aPeriod ) const
{
    /*!
     * \pre A valid logit exponent has been set.
     */
    assert( mLogitExponent[ aPeriod ] <= 0 );

    /*!
     * \pre A valid base cost has been set.
     */
    assert( mBaseCost != 0 );

    // Zero share weight implies no share which is signaled by negative infinity.
    const double minInf = -std::numeric_limits<double>::infinity();
    double logShareWeight = aShareWeight > 0.0 ? log( aShareWeight ) : minInf; // log(alpha)
    //           v--- log(alpha * exp(beta*p/p0))  ---v
    return logShareWeight + mLogitExponent[ aPeriod ] * aCost / mBaseCost;
}

/*!
 * \brief Share weight calculation for the absolute cost logit.
 * \details Given an an "anchor" subsector with observed share and cost and another choice
 *          also with observed share and cost, compute the inverse of the discrete choice function
 *          to produce a share weight.
 * \param aShare observed share for the current choice.
 * \param aCost observed cost for the current choice.
 * \param aAnchorShare observed share for the anchor choice.
 * \param aAnchorCost observed cost for the anchor choice.
 * \param aPeriod model time period for the calculation.
 * \return share weight for the current choice.
 */
double AbsoluteCostLogit::calcShareWeight( const double aShare, const double aCost, const double aAnchorShare,
                                           const double aAnchorCost, const int aPeriod ) const
{
    double coef = mLogitExponent[ aPeriod ] / mBaseCost;
    return ( aShare / aAnchorShare ) * exp( coef * ( aAnchorCost - aCost ) );
}


/*!
 * \brief Set the cost scale for the logit choice function
 * \details This parameter determines the cost range in which the
 *          logit parameter will have the same behavior as a logit
 *          exponent with the same numerical value in the
 *          relative-cost variant.  The purpose of this parameter is
 *          to allow us to easily work out the numerical values of the
 *          choice function parameters that will give behavior similar
 *          to a relative-cost-logit with known parameters (at least,
 *          over a limited range of cost values).  This function is
 *          called by the calibration subroutines, which use a set of
 *          heuristics to set the cost scale automatically.  If a
 *          value for the cost scale parameter was specified
 *          explicitly in the input, then the value suggested by the
 *          calibration subroutine is ignored, and the parsed value is
 *          used instead.
 * \param aBaseCost Value to set as the cost scale parameter.
 */
void AbsoluteCostLogit::setBaseCost( const double aBaseCost, const std::string &aFailMsg ) {
  if( !mParsedBaseCost ) {
      if(aBaseCost <= 0.0) {
          // Illegal value.  Log an error and set to a default value
          ILogger &calibrationLog = ILogger::getLogger("calibration_log");
          ILogger::WarningLevel oldlvl = calibrationLog.setLevel(ILogger::WARNING);
          calibrationLog << aFailMsg << ":  invalid or uninitialized base cost parameter. "
                         << "Setting baseCost = 1.0\n";
          calibrationLog.setLevel(oldlvl);
          mBaseCost = 1.0;
      }
      else {
          mBaseCost = aBaseCost;
      }
  } // This function is a no-op if mParsedBaseCost is set.
}
