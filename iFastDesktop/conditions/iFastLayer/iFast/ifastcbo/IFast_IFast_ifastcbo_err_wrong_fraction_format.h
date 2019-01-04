#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_wrong_fraction_format : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_wrong_fraction_format() { }
		~CIFast_IFast_ifastcbo_err_wrong_fraction_format() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_FRACTION_FORMAT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Wrong fraction format.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Falsches Bruchformat.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Formato de fracción incorrecto.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de fraction incorrect")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verkeerde breukopmaak")); }

        // Actions
	};
}



