#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entry_both_fields : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entry_both_fields() { }
		~CIFast_IFast_ifastcbo_err_entry_both_fields() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTRY_BOTH_FIELDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You must enter strings in both fields.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Vous devez saisir des chaines de caracteres dans les deux zones. Veuillez ressaisir.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie müssen in beide Felder Zeichenketten eingeben. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducir cadenas en ambos campos. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez entrer des chaînes dans chaque champ.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("U moet strings in beide velden invoeren. Vul opnieuw in")); }

        // Actions
	};
}



