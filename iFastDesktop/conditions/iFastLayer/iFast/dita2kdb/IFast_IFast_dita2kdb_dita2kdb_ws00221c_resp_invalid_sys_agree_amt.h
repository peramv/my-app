#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agree_amt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agree_amt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agree_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SYS_AGREE_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reset has been done since trade date %EffectiveDate%.  This trade will not settle.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Reset has been done since trade date %EffectiveDate%.  This trade will not settle.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wurde ab diesem Handelsdatum %EffectiveDate% zurückgesetzt; dieser Handel wird nicht abgerechnet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha reconfigurado desde esta fecha de transacción %EffectiveDate%, esta operación no se liquidará.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une revalorisation a été effectuée depuis la date de transaction du %EffectiveDate%. Cette transaction ne sera pas réglée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn instellingen gewijzigd sinds deze handelsdatum %EffectiveDate%, deze transactie kan niet worden betaald")); }

        // Actions
	};
}



