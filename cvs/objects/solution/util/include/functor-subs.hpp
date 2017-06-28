#ifndef FUNCTOR_SUBS_HPP_
#define FUNCTOR_SUBS_HPP_


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
 * @file functor-subs.hpp
 * @ingroup Solution
 * @brief Some specific functor subclasses for use in GCAM
 */

#include "functor.hpp"
#include "solution/util/include/ublas-helpers.hpp"

#define UBLAS boost::numeric::ublas

/*!
 * Template for a scalar function formed by taking the magnitude of a vector function.  This
 * class evaluates the vector function F, computes and returns the dot product, and also stores
 * the original vector function value.
 * @author Robert Link
 * @tparam Tr: return type
 * @tparam Ta: argument type
 */
template <class Tr, class Ta>
class FdotF : public SclFVec<Tr,Ta> {
protected:
  VecFVec<Tr,Ta> &F;
  UBLAS::vector<Tr> lstF;
public:
  FdotF(VecFVec<Tr,Ta> &Fin) : F(Fin), lstF(Fin.nrtn()) {this->na = Fin.narg();}
  void lastF(UBLAS::vector<Tr> &v) {v = lstF;}
  virtual Tr operator()(const UBLAS::vector<Ta> &x) {
    F(x,lstF);
    return inner_prod(lstF,lstF);
  }
  virtual void prn_diagnostic(std::ostream *out) {
    int ifmax=0;
    double fmax=fabs(lstF[0]);
    for(int i=1;i<lstF.size();++i) {
      if(fabs(lstF[i]) > fmax) {
        fmax = fabs(lstF[i]);
        ifmax = i;
      }
    }

    (*out) << "last F: " << lstF << "\n\tfmax = " << fmax
           << "  ifmax = " << ifmax << "\n";
  }
};

#undef UBLAS

#endif
