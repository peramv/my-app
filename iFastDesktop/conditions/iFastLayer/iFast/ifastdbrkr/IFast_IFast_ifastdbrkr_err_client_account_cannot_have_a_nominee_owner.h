#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner() { }
		~CIFast_IFast_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLIENT_ACCOUNT_CANNOT_HAVE_A_NOMINEE_OWNER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client Account can not have a Nominee Owner.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Client Account can not have a Nominee Owner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kunden-Konto kann keinen Bevollmächtigten Inhaber haben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta de cliente no puede tener un propietario nominatario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un compte client ne peut avoir de propriétaire nominé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Klantaccount mag geen gevolmachtigde eigenaar hebben")); }

        // Actions
	};
}



