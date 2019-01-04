#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_address : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_address() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_address() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ADDRESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Address.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Address.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Adresse.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Dirección no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Adresse invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig adres")); }

        // Actions
	};
}



