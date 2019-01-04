#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_ioerr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_ioerr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_ioerr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_IOERR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date must be a valuation date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La date d'operation doit être une date d'evaluation")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handelsdatum muss ein Bewertungsstichtag sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de transacción debe ser una fecha de valuación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction doit être une date d'évaluation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handelsdatum moet een waarderingsdatum zijn")); }

        // Actions
	};
}



