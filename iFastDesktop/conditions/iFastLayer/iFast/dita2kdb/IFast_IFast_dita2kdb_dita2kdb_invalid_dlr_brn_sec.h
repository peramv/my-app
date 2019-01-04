#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_brn_sec : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_brn_sec() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_brn_sec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_DLR_BRN_SEC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entity not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la entidad")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Entité introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid is niet gevonden")); }

        // Actions
	};
}



