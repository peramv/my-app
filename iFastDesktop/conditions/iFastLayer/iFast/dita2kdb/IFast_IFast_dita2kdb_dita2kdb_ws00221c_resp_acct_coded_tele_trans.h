#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_tele_trans : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_tele_trans() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_tele_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACCT_CODED_TELE_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mandatory Annual Amount should be 0 or %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mandatory Annual Amount should be 0 or %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Obligatorischer jährlicher Betrag sollte 0 oder %MAND_AMT_YR_SYS_CALC% sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto anual obligatorio debe ser 0 o %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant annuel requis devrait être 0 ou %MAND_AMT_YR_SYS_CALC%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verplicht jaarbedrag moet 0 zijn of %MAND_AMT_YR_SYS_CALC%")); }

        // Actions
	};
}



