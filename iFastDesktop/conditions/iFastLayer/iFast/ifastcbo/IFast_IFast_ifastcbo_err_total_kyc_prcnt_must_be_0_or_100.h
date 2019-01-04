#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_total_kyc_prcnt_must_be_0_or_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_total_kyc_prcnt_must_be_0_or_100() { }
		~CIFast_IFast_ifastcbo_err_total_kyc_prcnt_must_be_0_or_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOTAL_KYC_PRCNT_MUST_BE_0_OR_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total percentage must either be 0 or 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Total percentage of Growth, Income and Safety must either be 0 or 100.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Total percentage of Growth, Income and Safety must either be 0 or 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage total doit être 0 ou 100.")); }

        // Actions
	};
}



