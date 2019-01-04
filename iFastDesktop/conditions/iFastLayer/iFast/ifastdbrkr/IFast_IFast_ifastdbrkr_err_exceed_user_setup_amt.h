#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_exceed_user_setup_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_exceed_user_setup_amt() { }
		~CIFast_IFast_ifastdbrkr_err_exceed_user_setup_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCEED_USER_SETUP_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exceed user's setup amount.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Überschreitung des vom Benutzer erstellten Betrags")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Excede el monto configurado del usuario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Supérieur au montant réglé par l'utilisateur")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingestelde bedrag van gebruiker overschrijden")); }

        // Actions
	};
}



