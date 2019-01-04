#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_retmail_must_be_no_when_address_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_retmail_must_be_no_when_address_changed() { }
		~CIFast_IFast_ifastcbo_err_retmail_must_be_no_when_address_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RETMAIL_MUST_BE_NO_WHEN_ADDRESS_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address 1 or 2 has been changed, Return Mail flag must be No.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Address 1 or 2 has been changed, Return Mail flag must be No.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Address 1 or 2 has been changed, Return Mail flag must be No.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse 1 ou 2 a été changée, le signal de retour de courrier doit être désactivé.")); }

        // Actions
	};
}



