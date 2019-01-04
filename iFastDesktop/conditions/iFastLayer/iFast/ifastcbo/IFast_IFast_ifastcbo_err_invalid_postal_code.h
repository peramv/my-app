#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_postal_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_postal_code() { }
		~CIFast_IFast_ifastcbo_err_invalid_postal_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_POSTAL_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Postal Code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Postal Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Postleitzahl")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código postal no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code postal invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige postcode")); }

        // Actions
	};
}



