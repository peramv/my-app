#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_guaguard_not_same_between_to_ti : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_guaguard_not_same_between_to_ti() { }
		~CIFast_IFast_ifastcbo_err_guaguard_not_same_between_to_ti() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GUAGUARD_NOT_SAME_BETWEEN_TO_TI")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Guarantee Guard not same between TO/TI accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le gardien de la garantie n'est pas le même pour les comptes de transfert sortant/transfert entrant.")); }

        // Actions
	};
}



