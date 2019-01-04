#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_sts_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_sts_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_sts_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_STS_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

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



