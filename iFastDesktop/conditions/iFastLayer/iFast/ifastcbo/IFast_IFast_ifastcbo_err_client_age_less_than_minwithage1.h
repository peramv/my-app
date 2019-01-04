#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_client_age_less_than_minwithage1 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_client_age_less_than_minwithage1() { }
		~CIFast_IFast_ifastcbo_err_client_age_less_than_minwithage1() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLIENT_AGE_LESS_THAN_MINWITHAGE1")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Client age is less than minimum Withdrawal Age set in Pension Information.  Cannot process Cash Redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The Client age is less than minimum Withdrawal Age set in Pension Information.  Cannot process Cash Redemption.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The Client age is less than minimum Withdrawal Age set in Pension Information.  Cannot process Cash Redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge du client est inférieur à l'âge de retrait minimal réglé dans l'information sur le fonds de pension. Impossible de procéder au rachat au comptant.")); }

        // Actions
	};
}



