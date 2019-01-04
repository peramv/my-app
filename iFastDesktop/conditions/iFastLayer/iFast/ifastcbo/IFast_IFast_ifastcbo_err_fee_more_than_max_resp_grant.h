#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_more_than_max_resp_grant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_more_than_max_resp_grant() { }
		~CIFast_IFast_ifastcbo_err_fee_more_than_max_resp_grant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MORE_THAN_MAX_RESP_GRANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee greater than maximum fee allowed for fund %FUND% class %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais sont supérieurs aux frais maximaux autorisés pour le fonds %FUND% et la classe %CLASS%.")); }

        // Actions
	};
}



