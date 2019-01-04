#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_duplicate_systematic : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_duplicate_systematic() { }
		~CIFast_IFast_ifastcbo_err_warn_duplicate_systematic() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_DUPLICATE_SYSTEMATIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Warning duplicate systematic.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Warnung: doppelter Systematischer Plan")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Advertencia: plan sistemático repetido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Avertissement de copie de systématique")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarschuwing: dubbel systeemplan")); }

        // Actions
	};
}



