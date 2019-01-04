#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_auth_functions_disabled : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_auth_functions_disabled() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_auth_functions_disabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_AUTH_FUNCTIONS_DISABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one active Accountholder entity with sequence 1 must be created.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins une entite Titulaire de compte (01) active avec sequence 1 doit être creee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein aktives Kontoinhaber ( 01 )-Objekt mit Sequenz 1 muss erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe crearse al menos una entidad de titular de cuenta activa (01) con secuencia 1.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins une entité actionnaire active avec la séquence 1 doit être créée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één actieve accounthouderseenheid (01) zijn gemaakt met volgorde 1")); }

        // Actions
	};
}



