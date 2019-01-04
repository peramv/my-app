#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unable_get_fee_value_resp_grant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unable_get_fee_value_resp_grant() { }
		~CIFast_IFast_ifastcbo_err_unable_get_fee_value_resp_grant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_GET_FEE_VALUE_RESP_GRANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to get fee information for RESP GRANT.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'obtenir l'information sur les frais pour la SUBVENTION REEE.")); }

        // Actions
	};
}



