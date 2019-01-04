#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_invalid_field_tag : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_invalid_field_tag() { }
		~CIFast_IFast_dicbocore_err_invalid_field_tag() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FIELD_TAG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New account may not be created with a Terminated or Deleted status.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de creer un nouveau compte au statut Cloture ou Supprime.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Neues Konto kann mit einem Beendet- oder Gelöscht-Status nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No puede crearse una cuenta nueva con estado Terminada o Eliminada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un nouveau compte ne peut être créé avec un statut Fermé ou Supprimé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kan geen nieuw account worden gemaakt met de status beëindigd of gewist")); }

        // Actions
	};
}



