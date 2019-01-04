#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_margin_cannot_be_removed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_margin_cannot_be_removed() { }
		~CIFast_IFast_ifastcbo_err_margin_cannot_be_removed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MARGIN_CANNOT_BE_REMOVED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Margin feature cannot be removed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Margin feature cannot be removed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Margin feature cannot be removed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les caractéristiques de la marge ne peuvent être supprimées.")); }

        // Actions
	};
}



