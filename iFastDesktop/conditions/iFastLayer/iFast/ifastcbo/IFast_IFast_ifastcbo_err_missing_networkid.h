#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_networkid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_networkid() { }
		~CIFast_IFast_ifastcbo_err_missing_networkid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_NETWORKID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing Network ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Missing Network ID.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de réseau manquant")); }

        // Actions
	};
}



