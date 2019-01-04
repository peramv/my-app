#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_link_cannot_be_del : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_link_cannot_be_del() { }
		~CIFast_IFast_ifastdbrkr_err_link_cannot_be_del() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LINK_CANNOT_BE_DEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Link for Fund Broker cannot be deleted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Link for Fund Broker cannot be deleted.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le lien vers le courtier en fonds ne peut être supprimé.")); }

        // Actions
	};
}



