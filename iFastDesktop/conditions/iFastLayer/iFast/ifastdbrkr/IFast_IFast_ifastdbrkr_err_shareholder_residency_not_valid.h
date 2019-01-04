#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_shareholder_residency_not_valid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_shareholder_residency_not_valid() { }
		~CIFast_IFast_ifastdbrkr_err_shareholder_residency_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHAREHOLDER_RESIDENCY_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder does not have a valid residency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Shareholder does not have a valid residency.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Shareholder does not have a valid residency.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'actionnaire n'a pas de résidence valide.")); }

        // Actions
	};
}



