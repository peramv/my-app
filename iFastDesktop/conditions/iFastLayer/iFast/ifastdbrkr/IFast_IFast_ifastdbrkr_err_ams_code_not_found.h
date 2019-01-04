#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ams_code_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ams_code_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_ams_code_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code record not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS-Code-Eintrag nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro de código AMS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de code de service de gestion de portefeuille est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record BBD-code is niet gevonden")); }

        // Actions
	};
}



