#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_whereuse_must_be_01_03 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_whereuse_must_be_01_03() { }
		~CIFast_IFast_ifastdbrkr_err_whereuse_must_be_01_03() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WHEREUSE_MUST_BE_01_03")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("WhereUse code must be 01 (fund broker) or 03 (client) or 04 (fund).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("WhereUse code must be 01 (fund broker) or 03 (client).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de contrats associés doit être 01 (courtier en fonds), 03 (client) ou 04 (fonds).")); }

        // Actions
	};
}



