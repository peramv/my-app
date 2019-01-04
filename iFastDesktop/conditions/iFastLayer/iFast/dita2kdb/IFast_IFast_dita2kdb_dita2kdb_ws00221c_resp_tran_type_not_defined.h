#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_type_not_defined : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_type_not_defined() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_type_not_defined() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_TRAN_TYPE_NOT_DEFINED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Red must be off.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'indicateur Arreter rachat doit être desactive.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stopp-Tilgung muss deaktiviert sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Detener rescate debe estar desactivado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de rachat doit être désactivé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossing beëindigen moet zijn uitgezet")); }

        // Actions
	};
}



