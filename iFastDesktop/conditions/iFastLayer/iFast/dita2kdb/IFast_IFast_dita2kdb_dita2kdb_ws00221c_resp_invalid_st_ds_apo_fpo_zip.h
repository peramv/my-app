#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_ds_apo_fpo_zip : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_ds_apo_fpo_zip() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_ds_apo_fpo_zip() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ST_DS_APO_FPO_ZIP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract must be created for the account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Contract must be created for the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für das Konto muss ein Vertrag erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe crearse un contrato para la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un contrat doit être créé pour le compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet een overeenkomst worden gemaakt voor het account")); }

        // Actions
	};
}



