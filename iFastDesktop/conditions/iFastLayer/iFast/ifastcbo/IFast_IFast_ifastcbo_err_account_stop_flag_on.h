#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_stop_flag_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_stop_flag_on() { }
		~CIFast_IFast_ifastcbo_err_account_stop_flag_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_STOP_FLAG_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account has %TRADE_TYPE% stop flag turned on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'indicateur d'arret %TRADE_TYPE% est active pour le compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für das Konto ist das %TRADE_TYPE%-Stopp-Kennzeichen aktiviert")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta tiene el flag de dentición %TRADE_TYPE% activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt %TRADE_TYPE% du fonds est activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor het account is de %TRADE_TYPE% eindvlag aangezet")); }

        // Actions
	};
}



