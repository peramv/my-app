#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stock_split_rate : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stock_split_rate() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stock_split_rate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_STOCK_SPLIT_RATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batches do not match.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batches do not match.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batches stimmen nicht überein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los lotes no coinciden")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les lots ne correspondent pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batches komen niet overeen")); }

        // Actions
	};
}



