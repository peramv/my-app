#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pnd_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pnd_redemption() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pnd_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PND_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to add/update record.  Account Entity already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to add/update record.  Account Entity already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht hinzugefügt/aktualisiert werden, Konto-Objekt existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible añadir/actualizar registro. La entidad de cuenta ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter/de mettre à jour l'enregistrement. Entité du compte déjà existante.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kan niet worden toegevoegd of bijgewerkt, de accounteenheid bestaat al")); }

        // Actions
	};
}



