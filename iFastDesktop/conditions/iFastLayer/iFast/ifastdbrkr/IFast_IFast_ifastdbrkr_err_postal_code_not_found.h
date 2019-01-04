#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_postal_code_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_postal_code_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_postal_code_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_POSTAL_CODE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Postal Code not found in Code-1 Database.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Postal Code not found in Code-1 Database.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Postleitzahl nicht in Code-1-Datenbank gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el código postal en la base de datos Código 1")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code postal introuvable dans la base de données Code-1")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Postcode is niet gevonden in database Code-1")); }

        // Actions
	};
}



