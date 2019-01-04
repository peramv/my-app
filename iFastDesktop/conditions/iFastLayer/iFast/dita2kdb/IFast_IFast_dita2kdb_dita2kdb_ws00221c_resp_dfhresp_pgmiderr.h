#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_pgmiderr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_pgmiderr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_pgmiderr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_PGMIDERR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountability code is mandatory for backdated trades.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le code de responsabilite est obligatoire pour les operations antidatees")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verantwortlichkeits-Code ist obligatorisch für zurückdatierte Handel.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de responsabilidad es obligatorio para las operaciones antedatadas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code comptable est requis pour les transactions antidatées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Rekenplichtigheidscode is verplicht voor geantedateerde transacties")); }

        // Actions
	};
}



