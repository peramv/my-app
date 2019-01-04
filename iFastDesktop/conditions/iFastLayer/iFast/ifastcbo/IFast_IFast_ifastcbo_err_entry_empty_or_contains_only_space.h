#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entry_empty_or_contains_only_space : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entry_empty_or_contains_only_space() { }
		~CIFast_IFast_ifastcbo_err_entry_empty_or_contains_only_space() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The entry is empty or contains only space.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La valeur saisie est vide ou ne contient que des espaces. Veuillez ressaisir une valeur.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Eintrag ist leer oder enthält nur Leerzeichen. Bitte geben Sie ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La entrada está vacía o sólo contiene espacios. Por favor introduzca los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La saisie est vierge ou ne contient que de l'espacement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De invoer is leeg of bevat alleen spaties. Vul in")); }

        // Actions
	};
}



