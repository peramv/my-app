#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_this_fund_has_no_mgt_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_this_fund_has_no_mgt_fee() { }
		~CIFast_IFast_ifastcbo_err_this_fund_has_no_mgt_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_THIS_FUND_HAS_NO_MGT_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This fund has no management fee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Fonds hat keine Management-Provision.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este fondo no tiene una comisión por administración.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce fonds n'a pas de frais de gestion.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit fonds heeft geen beheerkosten")); }

        // Actions
	};
}



