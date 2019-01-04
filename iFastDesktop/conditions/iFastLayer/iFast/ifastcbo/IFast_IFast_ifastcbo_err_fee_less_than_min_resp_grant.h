#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_less_than_min_resp_grant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_less_than_min_resp_grant() { }
		~CIFast_IFast_ifastcbo_err_fee_less_than_min_resp_grant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_LESS_THAN_MIN_RESP_GRANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee less than minimum fee allowed for fund %FUND% class %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais sont inférieurs aux frais minimaux autorisés pour le fonds %FUND% et la classe %CLASS%.")); }

        // Actions
	};
}



