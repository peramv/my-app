#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_trans_backed_out : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_trans_backed_out() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_trans_backed_out() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_TRANS_BACKED_OUT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction backed out.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transaction backed out.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion nicht ausgeführt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se canceló la transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction annulée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De transactie is gestopt")); }

        // Actions
	};
}



