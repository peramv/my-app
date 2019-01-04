#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_reversal_code_top_up_incorrect : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_reversal_code_top_up_incorrect() { }
		~CIFast_IFast_ifastdbrkr_err_reversal_code_top_up_incorrect() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REVERSAL_CODE_TOP_UP_INCORRECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reversal code for Top-Up cancellation is incorrect.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Reversal code for Top-Up cancellation is incorrect.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de renversement pour l'annulation du dépôt complémentaire est incorrect.")); }

        // Actions
	};
}



