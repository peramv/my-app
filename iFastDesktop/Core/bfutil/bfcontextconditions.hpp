#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <condition.hpp>
#include <frame.hpp>
#include <bfutil/bfexecutioncontext.hpp>

class BFUTIL_LINKAGE BFContextConditions : public BFExecutionContextImpl
{
public:
   static BFContextConditions* get();

   void clear();  // remove all conditions from vector
   void add( const Condition* pCondition );
   void add( const CONDITIONVECTOR& rvConditions );

   CONDITIONVECTOR getConditions() const;

private:
   BFContextConditions();
   virtual ~BFContextConditions();
   
   CONDITIONVECTOR   vConditions_;
   mutable BFCritSec cs_;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfcontextconditions.hpp-arc  $
//
//   Rev 1.0   Aug 12 2003 10:16:10   PURDYECH
//Initial Revision
//
