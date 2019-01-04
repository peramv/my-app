#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_commission_rebate_not_allowed_for_this_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_commission_rebate_not_allowed_for_this_fund() { }
		~CIFast_IFast_ifastcbo_err_commission_rebate_not_allowed_for_this_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMMISSION_REBATE_NOT_ALLOWED_FOR_THIS_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Commission rebate not allowed for fund %FUND%, class %CLASS%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Commission rebate not allowed for fund %FUND%, class %CLASS%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La ristourne sur la commission n'est pas autorisée pour le fonds %FUND% et la classe %CLASS%.")); }

        // Actions
	};
}



