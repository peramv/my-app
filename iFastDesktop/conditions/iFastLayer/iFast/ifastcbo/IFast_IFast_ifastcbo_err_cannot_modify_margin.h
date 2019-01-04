#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_modify_margin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_modify_margin() { }
		~CIFast_IFast_ifastcbo_err_cannot_modify_margin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_MODIFY_MARGIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Margin feature cannot be modified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Margin feature cannot be modified.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Margin feature cannot be modified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les caractéristiques de la marge ne peuvent être modifiées.")); }

        // Actions
	};
}



