#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_address_code_not_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_address_code_not_effective() { }
		~CIFast_IFast_ifastcbo_warn_address_code_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ADDRESS_CODE_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address code %CODE% is no longer effective.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'adresse %CODE% n'est plus en vigueur.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please assign another code, or create an effective address with this code.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez allouer un autre code ou créer une adresse en vigueur avec ce code.")); }
	};
}



