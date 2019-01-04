#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_system_admin_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_system_admin_fee() { }
		~CIFast_IFast_ifastcbo_warn_system_admin_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SYSTEM_ADMIN_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("System generated Admin Fee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("System generated Admin Fee.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Frais d'administration générés par le système")); }

        // Actions
	};
}



