#ifndef _POLICY_GHG_H_
#define _POLICY_GHG_H_
#if defined(_MSC_VER)
#pragma once
#endif

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
* \file policy_ghg.h
* \ingroup Objects
* \brief The GHGPolicy class header file.
* \author Sonny Kim
*/

#include <vector>
#include <xercesc/dom/DOMNode.hpp>
#include <string>
#include "util/base/include/iround_trippable.h"

/*! 
* \ingroup Objects
* \brief Class which defines greenhouse gas mitigation policy. 
* \author Sonny Kim
*/
class GHGPolicy: public IRoundTrippable {
public:
    GHGPolicy();
    GHGPolicy( const std::string aName,
               const std::string aMarket );
    GHGPolicy( const std::string aName,
               const std::string aMarket,
               const std::vector<double>& aFixedTaxes );
    virtual GHGPolicy* clone() const;
    virtual const std::string& getName() const;
    virtual const std::string& getXMLName() const;
    static const std::string& getXMLNameStatic();
    virtual void XMLParse( const xercesc::DOMNode* node );
    virtual void toInputXML( std::ostream& out, Tabs* tabs ) const;
    virtual void toDebugXML( const int period, std::ostream& out, Tabs* tabs ) const;
    virtual void completeInit( const std::string& aRegionName );
    virtual bool isApplicable( const std::string& aRegion ) const;
    virtual void setConstraint( const std::vector<double>& aConstraint );
protected:
    std::string mName; //!< GHG name
    std::string mMarket; //!< Name of the market
    bool isFixedTax; //!< Boolean to use fixed tax or constraint
    std::vector<double> mConstraint; //!< Emissions constraint by year(tgC or MTC)
    std::vector<double> mFixedTax; //!< Fixed tax on Emissions by year($/TC)
};

#endif // _POLICY_GHG_H_


