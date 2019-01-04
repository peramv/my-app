#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_account_tax_jurisdiction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_account_tax_jurisdiction() { }
		~CIFast_IFast_ifastcbo_err_ams_account_tax_jurisdiction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_ACCOUNT_TAX_JURISDICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS portfolio can not be set up for the account tax jurisdiction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Group number is a required field for record update.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS portfolio can not be set up for the account tax jurisdiction.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de grupo es un campo obligatorio para la actualización del registro. Por favor introduzca un valor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de groupe est requis pour la mise à jour de l'enregistrement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Groepsnummer is een verplicht veld voor het bijwerken van het record. Vul een waarde in")); }

        // Actions
	};
}



