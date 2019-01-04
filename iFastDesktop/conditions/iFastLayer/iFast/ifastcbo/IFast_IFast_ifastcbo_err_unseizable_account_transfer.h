#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unseizable_account_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unseizable_account_transfer() { }
		~CIFast_IFast_ifastcbo_err_unseizable_account_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNSEIZABLE_ACCOUNT_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unseizable account: This transfer is restricted to authorized personnel only.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nicht pfändbares Konto: Dieser Transfer ist auf autorisiertes Personal beschränkt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cuenta no confiscable: esta transferencia se restringe a personal autorizado solamente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte insaisissable : ce transfert est restreint au personnel autorisé seulement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Niet-confiscabel account: Deze overdracht mag alleen door gemachtigde werknemers worden uitgevoerd")); }

        // Actions
	};
}



