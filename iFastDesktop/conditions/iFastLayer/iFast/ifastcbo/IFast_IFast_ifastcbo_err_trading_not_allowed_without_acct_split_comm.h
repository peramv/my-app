#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trading_not_allowed_without_acct_split_comm : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trading_not_allowed_without_acct_split_comm() { }
		~CIFast_IFast_ifastcbo_err_trading_not_allowed_without_acct_split_comm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADING_NOT_ALLOWED_WITHOUT_ACCT_SPLIT_COMM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading not allowed without Account Level Split Commission.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handel ohne Geteilte Agenturvergütung auf Konto-Level  nicht erlaub.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten operaciones sin una comisión dividida a nivel de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction n'est pas autorisée sans partage de commission au niveau du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handel is niet toegestaan zonder gedeelde commissie op accountniveau")); }

        // Actions
	};
}



