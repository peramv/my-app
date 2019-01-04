#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_cumdisc : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_cumdisc() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_cumdisc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_CUMDISC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No related CHUI functions available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No related CHUI functions available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine verwandten CHUI-Funktionen verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay funciones CHUI relacionadas disponibles")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune fonction CHUI n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen verwante CHUI-functies beschikbaar")); }

        // Actions
	};
}



