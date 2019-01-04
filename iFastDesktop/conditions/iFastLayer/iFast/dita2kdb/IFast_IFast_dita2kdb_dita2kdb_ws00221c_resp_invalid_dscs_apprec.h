#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dscs_apprec : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dscs_apprec() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dscs_apprec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_DSCS_APPREC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% must be a business date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FIELDNAME% doit contenir une date ouvrable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% muss ein Geschäftsdatum sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% debe ser una fecha hábil.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FIELDNAME% doit être une date ouvrable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% moet een werkdag zijn")); }

        // Actions
	};
}



