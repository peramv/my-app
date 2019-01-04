#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_b07_rec_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_b07_rec_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_b07_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_B07_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown start date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unknown start date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unbekanntes Startdatum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de inicio desconocida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de début inconnue")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onbekende startdatum")); }

        // Actions
	};
}



