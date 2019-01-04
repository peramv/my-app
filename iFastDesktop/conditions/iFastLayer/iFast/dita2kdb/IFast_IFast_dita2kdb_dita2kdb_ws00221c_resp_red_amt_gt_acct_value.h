#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_red_amt_gt_acct_value : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_red_amt_gt_acct_value() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_red_amt_gt_acct_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_RED_AMT_GT_ACCT_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid fund for Foreign sweeps excess transfer.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid fund for Foreign sweeps excess transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Fonds für Auslands-Giro-Überschuss-Transfer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fondo no válido para transferencias automáticas de excedente extranjero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds invalide pour le transfert d'excédent du niveau de contenu étranger")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig fonds voor surplusoverdracht buitenlandse ?Sweep-accounts?")); }

        // Actions
	};
}



