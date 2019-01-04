#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_broker_not_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_broker_not_entered() { }
		~CIFast_IFast_ifastdbrkr_err_broker_not_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_NOT_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse un corredor")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaar moet worden ingevoerd")); }

        // Actions
	};
}



