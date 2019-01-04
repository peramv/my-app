#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tpa_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tpa_invalid() { }
		~CIFast_IFast_ifastcbo_err_tpa_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TPA_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("TPA must equal to Broker if it is not blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("TPA must equal to Broker if it is not blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le TPA doit être identique au courtier si son champ n'est pas vide.")); }

        // Actions
	};
}



