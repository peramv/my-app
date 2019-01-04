#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_shareholder_family_record_not_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_shareholder_family_record_not_exists() { }
		~CIFast_IFast_ifastdbrkr_err_shareholder_family_record_not_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHAREHOLDER_FAMILY_RECORD_NOT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder Family record doesn't exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de la famille du détenteur n'existe pas.")); }

        // Actions
	};
}



