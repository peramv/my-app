#pragma once

#include "ConditionObject.h"

namespace CND
{
  class CIFast_IFast_ifastcbo_warn_dilution_nsm_external_nsm_only_one_yes : public CConditionObject
  {
    public:
      CIFast_IFast_ifastcbo_warn_dilution_nsm_external_nsm_only_one_yes() { }
      ~CIFast_IFast_ifastcbo_warn_dilution_nsm_external_nsm_only_one_yes() { }

    public:
      // General
      virtual DString GetConditionName() const { return DString(I_("WARN_DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES")); }
      virtual DString GetGroupName() const { return DString(I_("iFast")); }
      virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
      virtual int GetSeverity() const { return 5; }
      
      // Messages
      virtual DString GetMessage_EN_US() const { return DString(I_("Fundserv (Settle) Dilution and External Sys Pymt via N$M are mutually exclusive; only one can be set to \"Yes\".")); }
      virtual DString GetMessage_FR_CA() const { return DString(I_("La dilution (versement) Fundserv et le paiement système externe par MRN s’excluent mutuellement; la case « oui » ne peut être cochée que pour une seule proposition.")); }
  };
}