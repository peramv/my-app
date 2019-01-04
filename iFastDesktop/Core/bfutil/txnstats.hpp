#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <list>
#include <map>

class BFUTIL_LINKAGE TxnStatsException
{
};

#include <bfutil\txnstatelement.hpp>
#include <bfutil\bfexecutioncontext.hpp>
#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfhrtimer.hpp>
#include <bfutil\bffiletime.hpp>

#include <bfutil\elementwriter.hpp>

// this is a list of Transaction Statistic Element objects.
typedef std::list< TxnStatElement* > TXNSTATELEM_LIST;
typedef std::list< TxnStatElement* >::iterator TXNSTATELEM_ITER;
#if _MSC_VER >= 1300
typedef std::list< TxnStatElement* >::const_iterator TXNSTATELEM_CONST_ITER;
#else
typedef std::list< TxnStatElement* >::iterator TXNSTATELEM_CONST_ITER;
#endif

class BFUTIL_LINKAGE TxnStats : public BFExecutionContextImpl
{
public:
   // get the TxnStats object for the current ExecutionContext
   static TxnStats* get();

   static bool autoEnable( bool bAutoEnable );


   void startTimeChop();
   DWORD endTimeChop();

   DWORD timeSinceAccept() const;
   void resetAcceptTime();
   void setAcceptTime( const BFHRTimer& t )
   {
      acceptTime_ = t;
   }


   // reset all counters, etc. in this transaction stats object
   void reset();

   void addElementGroup( const DString& strGroup );
   const TXNSTATELEM_LIST& getElementGroup( const DString& strGroup );

   void addElement( const DString& strGroup, TxnStatElement* pElement );

   DString getAsIDIString() const;
//PMI-20020918   DString getAsXML( int iIndentLevel, int iIndentSize ) const;
   void writeXML( BFDocument& out ) const;

   bool isEnabled() const;
   bool enable( bool bEnabled );

   bool getThreadTimes( DWORD& msKernel, DWORD& msUser ) const;

protected:
   virtual DString formatXMLElement( const DString &Tag, const DString &value ) const
   {
      DString xml = beginXMLTag( Tag );
      xml += value;
      xml += endXMLTag( Tag );
      return( xml );
   }
   virtual DString beginXMLTag( const DString &Tag ) const
   {
      DString xml = I_( "<" );
      xml += Tag;
      xml += I_( ">" );
      return( xml );
   }
   virtual DString endXMLTag( const DString &Tag ) const
   {
      DString xml = I_( "</" );
      xml += Tag;
      xml += I_( ">" );
      return( xml );
   }

private:
   TxnStats();
   virtual ~TxnStats();

   // this is a map of Transaction Statistic Element Group objects
   // the key is an arbitrary user-supplied string
   typedef std::map< DString, TXNSTATELEM_LIST* > TXNSTATELEMGROUP_MAP;
   typedef std::map< DString, TXNSTATELEM_LIST* >::iterator TXNSTATELEMGROUP_ITER;
#if _MSC_VER >= 1300
   typedef std::map< DString, TXNSTATELEM_LIST* >::const_iterator TXNSTATELEMGROUP_CONST_ITER;
#else
   typedef std::map< DString, TXNSTATELEM_LIST* >::iterator TXNSTATELEMGROUP_CONST_ITER;
#endif

   TXNSTATELEMGROUP_MAP _mapElemGroup;
   mutable BFCritSec    _cs;
   bool                 _bEnabled;
   BFHRTimer            startTime_;
   BFHRTimer            acceptTime_;

   mutable BFFileTime   kernelTime_;   // kernel time of primary thread at last snapshot
   mutable BFFileTime   userTime_;     // user time of primary thread at last snapshot

   static bool          s_bAutoEnable;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/txnstats.hpp-arc  $
//
//   Rev 1.9   Oct 22 2004 09:01:24   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.8   Oct 09 2002 17:41:34   PURDYECH
//New PVCS Database
//
//   Rev 1.7   Sep 19 2002 09:28:16   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
