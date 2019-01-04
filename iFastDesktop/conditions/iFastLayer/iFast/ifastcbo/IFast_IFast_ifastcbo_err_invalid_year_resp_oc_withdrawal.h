#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_year_resp_oc_withdrawal : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_year_resp_oc_withdrawal() { }
		~CIFast_IFast_ifastcbo_err_invalid_year_resp_oc_withdrawal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_YEAR_RESP_OC_WITHDRAWAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot apply RESP OC withdrawal to invalid year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'appliquer le retrait des coûts d'exploitation REEE à une année invalide.")); }

        // Actions
	};
}



