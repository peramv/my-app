#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_array_rows : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_array_rows() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_array_rows() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_ARRAY_ROWS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An error occured while attempting to disconnect from host.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Benutzer hat keinen Unternehmenszugriff")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("An error occured while attempting to disconnect from host.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de la tentative de déconnexion de l'hôte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("An error occured while attempting to disconnect from host.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



