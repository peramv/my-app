#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_code_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_code_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_redemption_code_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_CODE_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Code is not allowed for transfers.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgungs-Code für Transfers nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el código de rescate para transferencias.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de rachat non autorisé pour les transferts")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode is niet toegestaan voor overdrachten")); }

        // Actions
	};
}



