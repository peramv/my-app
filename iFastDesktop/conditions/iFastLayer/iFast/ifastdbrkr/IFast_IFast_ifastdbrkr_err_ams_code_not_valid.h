#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ams_code_not_valid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ams_code_not_valid() { }
		~CIFast_IFast_ifastdbrkr_err_ams_code_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code not valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS-Code nicht gültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código AMS no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("BBD-code is ongeldig")); }

        // Actions
	};
}



