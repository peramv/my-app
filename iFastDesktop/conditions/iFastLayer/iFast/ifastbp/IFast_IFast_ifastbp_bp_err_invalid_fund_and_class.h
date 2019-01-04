#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_invalid_fund_and_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_invalid_fund_and_class() { }
		~CIFast_IFast_ifastbp_bp_err_invalid_fund_and_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_INVALID_FUND_AND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The fund code (%FUND%) and class code (%CLASS%) combination is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The fund code (%FUND%) and class code (%CLASS%) combination is invalid.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The fund code (%FUND%) and class code (%CLASS%) combination is invalid.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La combinaison de code de fonds (%FUND%) et de code de classe (%CLASS%) est invalide.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please re-enter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
	};
}



