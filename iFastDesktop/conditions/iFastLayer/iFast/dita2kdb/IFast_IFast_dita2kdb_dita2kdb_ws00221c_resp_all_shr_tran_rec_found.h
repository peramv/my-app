#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_all_shr_tran_rec_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_all_shr_tran_rec_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_all_shr_tran_rec_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ALL_SHR_TRAN_REC_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Pension Jurisdiction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Pension Jurisdiction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Rentenzuständigkeit.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Jurisdicción de jubilación no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Juridiction de retraite invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig rechtsgebied pensioen")); }

        // Actions
	};
}



