#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCViewTimeTxnStatElement.hpp
// ^AUTHOR : Chris P.
// ^DATE   : 2001
//
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

#include <bfutil\txnstats.hpp>
#include <bfutil\txnstatelement.hpp>
#include <bfdbrkr\bfrequest.hpp>
#include <bfdbrkr\bfrequestor.hpp>

class IFASTCBO_LINKAGE DSTCViewTimeTxnStatElement : public TxnStatElement
{
public:
   DSTCViewTimeTxnStatElement( const BFRequest &request,
                               const BFRequestor &requestor );

   DSTCViewTimeTxnStatElement( const DString& viewName );

   virtual const DString& getName() const;

   virtual DString getAsIDIString() const;
   virtual void writeXML( BFDocument& out );

   unsigned long getElapsed() const
   {
      return(_elapsed);
   }
   unsigned long getAssignTime() const
   {
      return(_assignTime);
   }

private:
   DString        _name;
   unsigned long  _elapsed;
   unsigned long  _assignTime;
   DString        _timeStamp;

   DString timeStamp();
};

