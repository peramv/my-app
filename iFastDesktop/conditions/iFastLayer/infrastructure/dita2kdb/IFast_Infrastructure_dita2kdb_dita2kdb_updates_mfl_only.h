#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_updates_mfl_only : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_updates_mfl_only() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_updates_mfl_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_UPDATES_MFL_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Updates are only allowed on MFL management system!")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Updates are only allowed on MFL management system!")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktualisierungen sind nur auf dem MFL-Management-System möglich!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("¡Sólo se permiten actualizaciones en el sistema de administración MFL!")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les mises à jour ne sont autorisées que dans le système de gestion de la liste des anomalies de la maintenance!")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijwerken is alleen toegestaan op een MFL-beheersysteem!")); }

        // Actions
	};
}



