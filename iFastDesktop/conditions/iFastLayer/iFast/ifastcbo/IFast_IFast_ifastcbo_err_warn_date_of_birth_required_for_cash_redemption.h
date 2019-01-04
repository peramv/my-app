#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_date_of_birth_required_for_cash_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_date_of_birth_required_for_cash_redemption() { }
		~CIFast_IFast_ifastcbo_err_warn_date_of_birth_required_for_cash_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_DATE_OF_BIRTH_REQUIRED_FOR_CASH_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client's date of birth is required to process Cash Redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Geburtsdatum des Kunden ist erforderlich, um die Bargeldtilgung zu verarbeiten")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere la fecha de nacimiento del cliente para procesar el rescate en efectivo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du client est requise pour le traitement du rachat comptant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum klant is vereist voor de verwerking van contante aflossing")); }

        // Actions
	};
}



