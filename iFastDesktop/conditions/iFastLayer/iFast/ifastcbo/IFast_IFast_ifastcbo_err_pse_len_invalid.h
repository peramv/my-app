#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pse_len_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pse_len_invalid() { }
		~CIFast_IFast_ifastcbo_err_pse_len_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PSE_LEN_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please Input PSE Program Length Value Between 0 to 9.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez entrer une valeur de durée de programme d'EPS située entre 0 et 9.")); }

        // Actions
	};
}



