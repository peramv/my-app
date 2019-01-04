#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_fund_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_fund_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_fund_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_TO_FUND_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only Good records can be modified.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only Good records can be modified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur sofort verfügbare Einträge können geändert werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo pueden modificase los registros válidos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls les enregistrements Bons peuvent être modifiés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kunnen alleen Goed-records worden gewijzigd")); }

        // Actions
	};
}



