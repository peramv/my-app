#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_exceed_max_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_exceed_max_limit() { }
		~CIFast_IFast_ifastcbo_err_amount_exceed_max_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_EXCEED_MAX_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The amount must be between zero and %Amount%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le montant doit être compris entre zéro et %Amount%. Veuillez ressaisir un montant.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Betrag muss zwischen Null und %Amount% liegen. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe encontrarse entre cero y %Amount%. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être situé entre zéro et %Amount%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het bedrag moet tussen nul en %Amount% liggen. Vul opnieuw in")); }

        // Actions
	};
}



