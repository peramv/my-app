#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fr_to_clearing_method_not_same_and_not_rlg : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fr_to_clearing_method_not_same_and_not_rlg() { }
		~CIFast_IFast_ifastcbo_err_fr_to_clearing_method_not_same_and_not_rlg() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FR_TO_CLEARING_METHOD_NOT_SAME_AND_NOT_RLG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Clearing Method are not the same between clearing account for realignment transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les méthodes de compensation ne sont pas les mêmes entre les comptes de compensation pour le transfert de réalignement.")); }

        // Actions
	};
}



