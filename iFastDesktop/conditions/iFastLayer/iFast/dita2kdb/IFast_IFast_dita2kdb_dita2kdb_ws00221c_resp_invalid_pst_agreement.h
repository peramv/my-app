#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pst_agreement : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pst_agreement() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pst_agreement() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PST_AGREEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to locate the pending trade banking information.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to locate the pending trade banking information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Schwebende Handels-Banking-Information kann nicht lokalisiert werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible localizar la información bancaria de la operación pendiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de repérer l'information bancaire de la transaction en suspens.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bankgegevens over in behandeling zijnde transacties zijn niet gevonden")); }

        // Actions
	};
}



