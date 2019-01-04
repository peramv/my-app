#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rollover_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rollover_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_rollover_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ROLLOVER_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rollover from fund %FROMFUND%, class %FROMCLASS% to fund %TOFUND%, class %TOCLASS% is not allowed")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rollover from fund %FROMFUND%, class %FROMCLASS% to fund %TOFUND%, class %TOCLASS% is not allowed")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La reconduction du fonds %FROMFUND% et de la classe %FROMCLASS% au fonds %TOFUND% et à la classe %TOCLASS% n'est pas autorisée.")); }

        // Actions
	};
}



