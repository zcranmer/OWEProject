#ifndef _WORLD_H_
#define _WORLD_H_
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
* \file world.h
* \ingroup Objects
* \brief The World class header file.
* \author Sonny Kim
*/

#include <map>
#include <vector>
#include <list>
#include <memory>
#include <xercesc/dom/DOMNode.hpp>
#include "util/base/include/ivisitable.h"
#include "util/base/include/iround_trippable.h"

// Forward declarations
class Region;
class ILogger;
class Curve;
class CalcCounter;
class IClimateModel;
class GHGPolicy;
class GlobalTechnologyDatabase;
class IActivity;

#if GCAM_PARALLEL_ENABLED
class GcamFlowGraph;
#endif

/*! 
* \ingroup Objects
* \brief A class which contains all the model's regions.  These regions may be MiniCAM (partial
* equilibrium) regions or SGM (general equilibrium) regions as they are derived
* from the Region base class.
*
* The World class object is contained by the Scenario class object.  The world object controls
* the calling of the regions which it has been told to solve (passed in an
* argument of the method world.calc()) by calling region.calc() to run the model
* for one iteration for these regions.
*
* \author Sonny Kim
*/

class World: public IVisitable, public IRoundTrippable
{
public:
    World();
    ~World();
    void XMLParse( const xercesc::DOMNode* node );
    void completeInit();
    void toInputXML( std::ostream& out, Tabs* tabs ) const;
    void toDebugXML( const int period, std::ostream& out, Tabs* tabs ) const;
	static const std::string& getXMLNameStatic();
    const std::string& getName() const;
    void initCalc( const int period );
    void postCalc( const int aPeriod );

    void calc( const int period );
    void calc( const int period, const std::vector<IActivity*>& aRegionsToCalc );
    void updateSummary( const std::list<std::string> aPrimaryFuelList, const int period ); 
    void setEmissions( int period );
    void runClimateModel();
    void runClimateModel( int period );
    void csvOutputFile() const; 
    void dbOutput( const std::list<std::string>& aPrimaryFuelList ) const; 
    const std::map<std::string,int> getOutputRegionMap() const;
    bool isAllCalibrated( const int period, double calAccuracy, const bool printWarnings ) const;
    void setTax( const GHGPolicy* aTax );
    const IClimateModel* getClimateModel() const;
    std::map<std::string, const Curve*> getEmissionsQuantityCurves( const std::string& ghgName ) const;
    std::map<std::string, const Curve*> getEmissionsPriceCurves( const std::string& ghgName ) const;
    CalcCounter* getCalcCounter() const;
    const GlobalTechnologyDatabase* getGlobalTechnologyDatabase() const;

	void accept( IVisitor* aVisitor, const int aPeriod ) const;
    void csvSGMOutputFile( std::ostream& aFile, const int period ) const;
    void csvSGMGenFile( std::ostream& aFile ) const;

#if GCAM_PARALLEL_ENABLED
  private:
    //! TBB flow graph for a complete model evaluation
    GcamFlowGraph* mTBBGraphGlobal;
  public:
    void calc( const int aPeriod, GcamFlowGraph *aWorkGraph, const std::vector<IActivity*>* aCalcList = 0 );
    /*!
     * \brief Return a pointer to the global flow graph
     * \details The flow graph structure is opaque to everything but World and GcamParallel, so
     *         it is safe to return as a non-const reference
     * \warning It appears not to be safe to copy a TBB flow graph structure (the TBB documentation
     *         is a little sparse, so it's hard to be sure).  To be on the safe side, all instances
     *         of GcamFlowGraph should be passed around as pointers or references.
     */
    GcamFlowGraph *getGlobalFlowGraph() {return mTBBGraphGlobal;}
#endif
private:
    //! The type of an iterator over the Region vector.
    typedef std::vector<Region*>::iterator RegionIterator;

    //! The type of a constant iterator over the Region vector.
    typedef std::vector<Region*>::const_iterator CRegionIterator;
    
    std::map<std::string, int> regionNamesToNumbers; //!< Map of region name to indice used for XML parsing.
    std::vector<Region*> regions; //!< array of pointers to Region objects
    std::auto_ptr<IClimateModel> mClimateModel; //!< The climate model.

    //! An object which maintains a count of the number of times
    //! calc() has been called.
    std::auto_ptr<CalcCounter> mCalcCounter;
    
    //! The global ordering of activities which can be used to calculate the model.
    std::vector<IActivity*> mGlobalOrdering;

    //! The global technology database.
    std::auto_ptr<GlobalTechnologyDatabase> mGlobalTechDB;

    void clear();

    void csvGlobalDataFile() const;
 public:
    //! Number of activities in the global activity list
    int global_size(void) {return mGlobalOrdering.size();}
};

#endif // _WORLD_H_
