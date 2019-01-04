#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_street_name_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_street_name_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_street_name_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STREET_NAME_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Street name not found in Postal Code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Street name not found in Postal Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Straßenname nicht in Postleitzahl gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el nombre de la calle en el código postal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Nom de rue introuvable pour le code postal")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Straatnaam is niet gevonden in postcode")); }

        // Actions
	};
}



