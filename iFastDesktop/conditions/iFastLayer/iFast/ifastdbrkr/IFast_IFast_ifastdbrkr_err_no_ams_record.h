#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_ams_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_ams_record() { }
		~CIFast_IFast_ifastdbrkr_err_no_ams_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_AMS_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No AMS Code record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein AMS-Code-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro AMS disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de code de service de gestion de portefeuille n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen BBD-coderecord beschikbaar")); }

        // Actions
	};
}



