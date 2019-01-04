#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_ath_dealer : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_ath_dealer() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_ath_dealer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_OPERATOR_NOT_ATH_DEALER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
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



