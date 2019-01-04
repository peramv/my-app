#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_invalid_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_invalid_fund() { }
		~CIFast_IFast_ifastbp_bp_err_invalid_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_INVALID_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund code is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondscode ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de fondo no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de fonds invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondscode is ongeldig")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please re-enter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Pleas re-enter")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
	};
}



