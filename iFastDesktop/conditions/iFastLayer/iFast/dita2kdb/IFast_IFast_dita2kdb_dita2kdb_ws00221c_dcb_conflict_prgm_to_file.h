#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_dcb_conflict_prgm_to_file : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_dcb_conflict_prgm_to_file() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_dcb_conflict_prgm_to_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_DCB_CONFLICT_PRGM_TO_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Users batch is not active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("User has no active batch.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer hat keinen aktiven Batch.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario no tiene un lote activo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le lot d'utilisateurs est inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker heeft geen actieve batch")); }

        // Actions
	};
}



