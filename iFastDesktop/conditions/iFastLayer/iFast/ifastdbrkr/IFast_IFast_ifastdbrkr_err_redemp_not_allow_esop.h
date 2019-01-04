#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_redemp_not_allow_esop : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_redemp_not_allow_esop() { }
		~CIFast_IFast_ifastdbrkr_err_redemp_not_allow_esop() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMP_NOT_ALLOW_ESOP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Code not allowed for ESoP.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgungscode für EsoP nicht erlaubt .")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el código de rescate para ESoP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de rachat non autorisé pour le RADE")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode is niet toegestaan voor ESoP")); }

        // Actions
	};
}



