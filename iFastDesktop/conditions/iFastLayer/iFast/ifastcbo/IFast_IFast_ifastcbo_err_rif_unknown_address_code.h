#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_unknown_address_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_unknown_address_code() { }
		~CIFast_IFast_ifastcbo_err_rif_unknown_address_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_UNKNOWN_ADDRESS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Address Code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Address Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Adresscode.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de dirección no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'adresse invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige adrescode")); }

        // Actions
	};
}



