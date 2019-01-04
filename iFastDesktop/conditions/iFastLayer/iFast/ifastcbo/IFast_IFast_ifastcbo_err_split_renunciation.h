#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_split_renunciation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_split_renunciation() { }
		~CIFast_IFast_ifastcbo_err_split_renunciation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPLIT_RENUNCIATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Renunciation amount is not zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Renunciation amount is not zero.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Renunciation amount is not zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de renonciation n'est pas zéro.")); }

        // Actions
	};
}



