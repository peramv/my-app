#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_address_not_verify : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_address_not_verify() { }
		~CIFast_IFast_ifastcbo_err_address_not_verify() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_NOT_VERIFY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to %OPERATION% due to payment address is not verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de %OPERATION% parce que l'adresse de paiement n'est pas vérifiée.")); }

        // Actions
	};
}



