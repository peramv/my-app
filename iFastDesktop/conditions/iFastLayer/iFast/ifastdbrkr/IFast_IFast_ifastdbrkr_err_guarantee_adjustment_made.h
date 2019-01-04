#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_guarantee_adjustment_made : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_guarantee_adjustment_made() { }
		~CIFast_IFast_ifastdbrkr_err_guarantee_adjustment_made() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GUARANTEE_ADJUSTMENT_MADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There has been a guarantee adjustment since the original Trade Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("There has been a guarantee adjustment since the original Trade Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a eu un ajustement de garantie depuis la date de transaction d'origine.")); }

        // Actions
	};
}



