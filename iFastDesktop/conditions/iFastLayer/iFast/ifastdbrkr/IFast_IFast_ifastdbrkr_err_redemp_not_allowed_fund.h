#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_redemp_not_allowed_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_redemp_not_allowed_fund() { }
		~CIFast_IFast_ifastdbrkr_err_redemp_not_allowed_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMP_NOT_ALLOWED_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Not Allowed for Fund & Class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgung für Fonds & Klasse nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el rescate para este fondo y clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Rachat non autorisé pour le fonds et la classe")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossing is niet toegestaan voor fonds en categorie")); }

        // Actions
	};
}



