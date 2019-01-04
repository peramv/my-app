#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_brkbrrep_inactive_currbusdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_brkbrrep_inactive_currbusdate() { }
		~CIFast_IFast_ifastcbo_warn_brkbrrep_inactive_currbusdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BRKBRREP_INACTIVE_CURRBUSDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker/Branch/Rep is not active as of current business date")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker/Branch/Rep is not active as of current business date")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier/l'unité de service/le représentant est inactif/inactive èa la date opérationnelle actuelle.")); }

        // Actions
	};
}



