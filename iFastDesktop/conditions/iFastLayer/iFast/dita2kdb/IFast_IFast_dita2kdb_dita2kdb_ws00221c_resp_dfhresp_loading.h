#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_loading : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_loading() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_loading() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_LOADING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% must fall on a business day.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FIELDNAME% doit correspondre a un jour ouvrable")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% muss auf einen Geschäftstag fallen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% debe caer en un día hábil")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELDNAME% doit tomber un jour ouvrable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% moet op een werkdag vallen")); }

        // Actions
	};
}



