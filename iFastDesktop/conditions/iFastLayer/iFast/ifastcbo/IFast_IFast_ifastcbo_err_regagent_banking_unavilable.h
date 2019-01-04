#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_regagent_banking_unavilable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_regagent_banking_unavilable() { }
		~CIFast_IFast_ifastcbo_err_regagent_banking_unavilable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REGAGENT_BANKING_UNAVILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Banking Instruction Available for the Account to redirect to Reg Agent")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune instruction bancaire n'est disponible pour le compte pour le réacheminement vers l'agent d'enregistrement.")); }

        // Actions
	};
}



