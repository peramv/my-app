#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_w8_w9_cannot_create_manually : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_w8_w9_cannot_create_manually() { }
		~CIFast_IFast_ifastcbo_err_w8_w9_cannot_create_manually() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_W8_W9_CANNOT_CREATE_MANUALLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("W8/W9 tax exemption authorization cannot be created manually.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n’est pas possible d’obtenir manuellement une autorisation d’exonération fiscale pour les formulaires W8/W9.")); }

        // Actions
	};
}



