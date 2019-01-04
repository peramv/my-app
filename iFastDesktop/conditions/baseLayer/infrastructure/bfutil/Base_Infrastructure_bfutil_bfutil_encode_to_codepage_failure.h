#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfutil_bfutil_encode_to_codepage_failure : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfutil_bfutil_encode_to_codepage_failure() { }
		~CBase_Infrastructure_bfutil_bfutil_encode_to_codepage_failure() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BFUTIL_ENCODE_TO_CODEPAGE_FAILURE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfutil")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No view data objects registered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No view data objects registered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Ansicht-Datenobjekte registriert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay objetos de datos de view registrados.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun objet de données d'affichage n'est enregistré.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen gegevensobjecten view geregistreerd")); }

        // Actions
	};
}



