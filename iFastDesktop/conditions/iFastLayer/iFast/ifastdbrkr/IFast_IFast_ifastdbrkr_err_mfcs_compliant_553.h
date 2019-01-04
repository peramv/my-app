#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_mfcs_compliant_553 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_mfcs_compliant_553() { }
		~CIFast_IFast_ifastdbrkr_err_mfcs_compliant_553() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MFCS_COMPLIANT_553")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("MFCS Compliant trades cannot be settled individually")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("MFCS Compliant trades cannot be settled individually")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transactions conformes aux sociétés de fonds communs de placement ne peuvent être réglées individuellement.")); }

        // Actions
	};
}



