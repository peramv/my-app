#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_allowed_to_exchange : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_allowed_to_exchange() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_allowed_to_exchange() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FRMFUND% \\ %FRMCLASS% is not allowed to exchange to Fund %TOFUND% \\ %TOCLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il est interdit de transférer de %FRMFUND% \\ %FRMCLASS% au fonds %TOFUND% \\ %TOCLASS%.")); }

        // Actions
	};
}



