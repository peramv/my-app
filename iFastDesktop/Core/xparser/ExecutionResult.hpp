#pragma once

#include "xparsercommon.hpp"
#include <list>

namespace xp {

   //*********************************************
   class ExecResult {
   public:
      ExecResult() 
         : successful_(false)
         , criticalErrorCount_(0)
         , severeErrorCount_(0)
         , warningCount_(0)
         ,informationalCount_(0) {}

         virtual ~ExecResult() {}

      void setSuccessful( bool value ) { successful_= value; }
      bool isSuccessful() const { return successful_; }

      unsigned int getCriticalErrorCount() const { return criticalErrorCount_; }
      unsigned int getSevereErrorCount() const { return severeErrorCount_; }
      unsigned int getWarningCount() const { return warningCount_; }
      unsigned int getInformationalCount() const { return informationalCount_; }

      void incrementConditionCount( SEVERITY severity );

   private:
      bool successful_;

      unsigned int criticalErrorCount_;
      unsigned int severeErrorCount_;
      unsigned int warningCount_;
      unsigned int informationalCount_;
   };

   //*********************************************
   template<typename _R> class CompositeExecResult : public ExecResult {
   public:
      typedef _R SubResultType;
      typedef std::list<SubResultType> SubResultList; 

      CompositeExecResult() 
      : ExecResult()
      , subResults_() 
      {
      }

      virtual ~CompositeExecResult() {}

   protected:
      SubResultType &addSubResult(const SubResultType &r) { 
         subResults_.push_back( r );
         return subResults_.back();
      }

      const SubResultList &getSubResultList() const { return subResults_; }
   private:
      SubResultList subResults_;

   };

   //*********************************************
   class ProcessResult : public ExecResult {
   public:
      ProcessResult( xp::ProcessAction action );

      virtual ~ProcessResult() {}

      xp::ProcessAction getAction() const { return action_; }
      unsigned int getCBOActionCount( xp::CBOAction action ) const { return cboActionCount_[action]; }
      void incrementCBOActionCount(xp::CBOAction action) { ++cboActionCount_[action]; }

   private:
      xp::ProcessAction action_;
      unsigned int cboActionCount_[CBO_ACTION_COUNT];
   };

   //*********************************************
   class BatchResult : public CompositeExecResult<ProcessResult> {
   public:
      BatchResult() : CompositeExecResult<ProcessResult>() {}
      virtual ~BatchResult() {}

      typedef std::list<ProcessResult> ProcessResultList;
      const ProcessResultList &getProcessResults() const { return getSubResultList(); }

      ProcessResult &createProcessResult(xp::ProcessAction action) { 
         return addSubResult(ProcessResult(action));
      }

   private:
   };

   //*********************************************
   class ExecutionResult : public CompositeExecResult<BatchResult> {
   public:
      ExecutionResult() : CompositeExecResult<BatchResult>() {}
      virtual ~ExecutionResult() {}

      typedef std::list<BatchResult> BatchResultList;
      const BatchResultList &getBatchResults() const { return getSubResultList(); }
      BatchResult &createBatchResult() { return addSubResult(BatchResult()); }

   };
}