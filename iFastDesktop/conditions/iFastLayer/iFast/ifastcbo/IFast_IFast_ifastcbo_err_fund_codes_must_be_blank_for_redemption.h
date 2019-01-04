#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_codes_must_be_blank_for_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_codes_must_be_blank_for_redemption() { }
		~CIFast_IFast_ifastcbo_err_fund_codes_must_be_blank_for_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CODES_MUST_BE_BLANK_FOR_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund code must be blank for redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds-Code muss für Tilgung leer sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código del fondo debe estar en blanco para el rescate")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Code de fonds doit être vide pour effectuer un rachat.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondscode moet leeg zijn voor aflossing")); }

        // Actions
	};
}



