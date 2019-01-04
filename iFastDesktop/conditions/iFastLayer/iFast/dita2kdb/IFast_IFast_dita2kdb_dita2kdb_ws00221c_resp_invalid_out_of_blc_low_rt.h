#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_out_of_blc_low_rt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_out_of_blc_low_rt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_out_of_blc_low_rt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_OUT_OF_BLC_LOW_RT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract record not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Contract record not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertragseintrag nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro Contract")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement de contrat introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Overeenkomst is niet gevonden")); }

        // Actions
	};
}



