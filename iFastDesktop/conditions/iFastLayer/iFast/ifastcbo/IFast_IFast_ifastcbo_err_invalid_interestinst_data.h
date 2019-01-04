#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_interestinst_data : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_interestinst_data() { }
		~CIFast_IFast_ifastcbo_err_invalid_interestinst_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_INTERESTINST_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For the Instruction type Interest, the only valid Rollover type is Cash and the valid Pay Types are Cheque and EFT.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour les instruction de l'intérêt, le seul type de roulement valide est Comptant et les types de paiement valides sont Chèque et TEF.")); }

        // Actions
	};
}



