#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_delete_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_delete_entity() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_delete_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_DELETE_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to delete entity record, version numbers are different.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de supprimer l'enregistrement de l'entite, les numeros de version sont differents")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt-Eintrag konnte nicht gelöscht werden, die Versionsnummer sind verschieden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible eliminar el registro de entidad, los números de versiones son diferentes")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer l'enregistrement de l'entité, les numéros de version sont différents.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheidrecord kon niet worden gewist, de versienummers zijn verschillend")); }

        // Actions
	};
}



