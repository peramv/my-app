#pragma once

#include "ConditionObject.h"

namespace CND
{
  class CIFast_IFast_ifastcbo_err_only_one_rec_with_100_percent_allowed : public CConditionObject
  {
    public:
      CIFast_IFast_ifastcbo_err_only_one_rec_with_100_percent_allowed() { }
      ~CIFast_IFast_ifastcbo_err_only_one_rec_with_100_percent_allowed() { }
  
    public:
      // General
      virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED")); }
      virtual DString GetGroupName() const { return DString(I_("iFast")); }
      virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
      virtual int GetSeverity() const { return 6; }
      
      // Messages
      virtual DString GetMessage_EN_US() const { return DString(I_("Only one record with 100% accountability is allowed for a dealer or an intermediary.")); }
      virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul enregistrement à 100 % d'imputabilité est autorisé pour un courtier ou un intermédiaire.")); }
  };
}