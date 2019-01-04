#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_broker_slsrep_not_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_broker_slsrep_not_entered() { }
		~CIFast_IFast_ifastdbrkr_err_broker_slsrep_not_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_SLSREP_NOT_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker and Sales Representative must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker und Verkaufsvertreter müssen eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben introducirse un corredor y un representante de ventas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier et le représentant des ventes sont requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaar en vertegenwoordiger moeten worden ingevoerd")); }

        // Actions
	};
}



