#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fundcode_settle_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fundcode_settle_currency() { }
		~CIFast_IFast_ifastcbo_err_fundcode_settle_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDCODE_SETTLE_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Code and Currency can not be empty at the same time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondscode und Währung können nicht beide leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de fondo y la divisa no pueden estar vacíos al mismo tiempo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Code de fonds et Monnaie du fonds ne peuvent être tous deux vides.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondscode en valuta kunnen niet tegelijkertijd leeg zijn")); }

        // Actions
	};
}



