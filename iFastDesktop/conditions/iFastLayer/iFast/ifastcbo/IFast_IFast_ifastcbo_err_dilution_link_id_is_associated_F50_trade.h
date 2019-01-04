#pragma once

#include "ConditionObject.h"

namespace CND
{
  class CIFast_IFast_ifastcbo_err_dilution_link_id_is_associated_F50_trade : public CConditionObject
  {
    public:
      CIFast_IFast_ifastcbo_err_dilution_link_id_is_associated_F50_trade() { }
      ~CIFast_IFast_ifastcbo_err_dilution_link_id_is_associated_F50_trade() { }

    public:
      // General
      virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE")); }
      virtual DString GetGroupName() const { return DString(I_("iFast")); }
      virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
      virtual int GetSeverity() const { return 6; }
      
      // Messages
      virtual DString GetMessage_EN_US() const { return DString(I_("iFast Link ID is associated with a Fundserv F50 trade.")); }
      virtual DString GetMessage_FR_CA() const { return DString(I_("L'identifiant du lien iFast est associé à une transaction F50 Fundserv.")); }
  };
}