#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_blank_freqency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_blank_freqency() { }
		~CIFast_IFast_ifastcbo_err_blank_freqency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BLANK_FREQENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Frequency field cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La fréquence est requise.")); }

        // Actions
	};
}



