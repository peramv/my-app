#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unknown_address_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unknown_address_code() { }
		~CIFast_IFast_ifastcbo_err_unknown_address_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_ADDRESS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown address code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unbekannter Adresscode")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("código de dirección desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'adresse inconnu")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("onbekende adrescode")); }

        // Actions
	};
}



