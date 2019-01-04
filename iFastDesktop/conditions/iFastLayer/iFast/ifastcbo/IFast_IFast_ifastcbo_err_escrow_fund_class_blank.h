#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrow_fund_class_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrow_fund_class_blank() { }
		~CIFast_IFast_ifastcbo_err_escrow_fund_class_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROW_FUND_CLASS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow/Assigned Fund and Class must be entered with non-zero units specified.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Escrow Fund or Class can not be blank for Escrow Representative and AmountType is unit.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Escrow-Fonds oder  Escrow-Klasse müssen mit spezifizierten Nicht-Null-Einheiten eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("EscrowFund o EscrowClass deben introducirse con unidades que no sean cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds et la classe mis en garantie doivent être saisis avec des unités non nulles spécifiées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pandfonds of categorie moeten worden ingevoerd met opgegeven niet-nul eenheden")); }

        // Actions
	};
}



