#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_red_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_red_code() { }
		~CIFast_IFast_ifastcbo_err_invalid_red_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_RED_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Redemption Code for this transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Tilgungscode für diese Transaktion.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de rescate no válido para esta transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de rachat invalide pour cette transaction")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige aflossingscode voor deze transactie")); }

        // Actions
	};
}



