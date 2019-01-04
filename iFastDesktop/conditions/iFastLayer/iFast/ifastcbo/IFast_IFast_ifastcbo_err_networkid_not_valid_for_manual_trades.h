#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_networkid_not_valid_for_manual_trades : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_networkid_not_valid_for_manual_trades() { }
		~CIFast_IFast_ifastcbo_err_networkid_not_valid_for_manual_trades() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NETWORKID_NOT_VALID_FOR_MANUAL_TRADES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Network order not valid for manual trades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ordre de réseau invalide pour les transactions manuelles")); }

        // Actions
	};
}



